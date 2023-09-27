
#ifndef IVSCRIPT_HANDLES_H
#define IVSCRIPT_HANDLES_H

#include "public/vscript/ivscript.h"

class BaseScriptHandle
{
public:
    BaseScriptHandle(IScriptVM *pVM, HSCRIPT handle)
        m_pScriptVM(pVM),
        m_Handle(handle)
    {

    }

    bool Equals(BaseScriptHandle* other)
    {
        return m_pScriptVM.AreHandlesEqual(m_Handle, other->m_Handle);
    }

    //  Returns true if the handle is still alive.
    bool IsValid()
    {
        return m_Handle != INVALID_HANDLE;
    }

    //  Take a reference of this handle.
    //  If handle is invalid, then this will return null.
    template <class T>
    T* Reference()
    {
        if (m_Handle == INVALID_HANDLE)
            return nullptr;

        return new BaseScriptHandle(m_pScriptVM, m_pScriptVM.CopyHandle(m_Handle));
    }

    //  Free this handle and disable the handle
    void Release()
    {
        if (m_Handle == INVALID_HANDLE)
            return;

        m_pScriptVM.ReleaseScript(m_Handle);
        m_Handle = INVALID_HANDLE;
    }
protected:
    IScriptVM *m_pScriptVM;
    HSCRIPT m_Handle;
};

class TableHandle: public BaseScriptHandle
{
public:
    int	CountTableEntries()
    {
        return m_pScriptVM.GetNumTableEntries(m_Handle);
    }
    int CountElements()
    {
        return m_pScriptVM.GetNumElements(m_Handle);
    }

    bool GetValue(int nIndex, ScriptVariant_t *pValue )
    {
        return m_pScriptVM.GetValue(m_Handle, nIndex, pValue);
    }
    
    bool GetValue(const char *pszKey, ScriptVariant_t *pValue )
    {
        return m_pScriptVM.GetValue(m_Handle, pszKey, pValue);
    }
};

#endif // IVSCRIPT_HANDLES_H
