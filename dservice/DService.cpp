
#include "stdafx.h"

#include <wchar.h>
#include <string>
#include <locale>

#include "DService.h"

static const wchar_t* g_PropNames[] = { L"" };
static const wchar_t* g_PropNamesRu[] = { L"" };

static const wchar_t* g_MethodNamesRu[] = {
    L"Версия",
    L"ВыполнитьСкрипт"
};

static const wchar_t* g_MethodNames[] = {
    L"Version",
    L"ExecuteScript"
};

static const wchar_t g_kClassNames[] = L"DService";

uint32_t convToShortWchar(WCHAR_T** Dest, const wchar_t* Source, uint32_t len = 0);
uint32_t convFromShortWchar(wchar_t** Dest, const WCHAR_T* Source, uint32_t len = 0);
uint32_t getLenShortWcharStr(const WCHAR_T* Source);

const wchar_t* kComponentVersion = L"1.0";

long GetClassObject(const wchar_t* wsName, IComponentBase** pInterface)
{
    if(!*pInterface)
    {
        *pInterface= new DService();
        return (long)*pInterface;
    }
    return 0;
}

long DestroyObject(IComponentBase** pIntf)
{
   if(!*pIntf) {
      return -1;
   }

   delete *pIntf;
   *pIntf = 0;
   return 0;
}

const WCHAR_T* GetClassNames()
{
    static WCHAR_T* names = 0;

    if (!names) {
        ::convToShortWchar(&names, g_kClassNames);
    }

    return names;
}

DService::DService()
{
    m_iMemory = 0;
    m_iConnect = 0;
}

DService::~DService()
{
}

bool DService::Init(void* pConnection)
{ 
    m_iConnect = (IAddInDefBase*)pConnection;
    return m_iConnect != NULL;

    return false;
}

long DService::GetInfo()
{ 
    return 2000; 
}

void DService::Done()
{
}

bool DService::RegisterExtensionAs(WCHAR_T** wsExtensionName)
{ 
    const wchar_t* wsExtension = L"DSNativeExtension";
    int iActualSize = ::wcslen(wsExtension) + 1;
    WCHAR_T* dest = 0;

    if (m_iMemory)
    {
        if (m_iMemory->AllocMemory((void**)wsExtensionName, iActualSize * sizeof(WCHAR_T))) {
            ::convToShortWchar(wsExtensionName, wsExtension, iActualSize);
        }

        return true;
    }
    
    return false; 
}

long DService::GetNProps()
{ 
    return eLastProperties;
}

long DService::FindProp(const WCHAR_T* wsPropName)
{ 
    long plPropNum = -1;
    wchar_t* propName = 0;

    ::convFromShortWchar(&propName, wsPropName);
    plPropNum = findName(g_PropNames, propName, eLastProperties);

    if (plPropNum == -1) {
        plPropNum = findName(g_PropNamesRu, propName, eLastProperties);
    }

    delete[] propName;

    return plPropNum;
}

const WCHAR_T* DService::GetPropName(long lPropNum, long lPropAlias)
{ 
    if (lPropNum >= eLastProperties)
        return NULL;

    const wchar_t* wsCurrentName = NULL;
    WCHAR_T* wsPropName = NULL;
    int iActualSize = 0;

    switch (lPropAlias)
    {
    case 0: // First language
        wsCurrentName = g_PropNames[lPropNum];
        break;
    case 1: // Second language
        wsCurrentName = g_PropNamesRu[lPropNum];
        break;
    default:
        return 0;
    }

    iActualSize = wcslen(wsCurrentName) + 1;

    if (m_iMemory && wsCurrentName) {
        if (m_iMemory->AllocMemory((void**)&wsPropName, iActualSize * sizeof(WCHAR_T))) {
            ::convToShortWchar(&wsPropName, wsCurrentName, iActualSize);
        }
    }

    return wsPropName;
}

bool DService::GetPropVal(const long lPropNum, tVariant* pvarPropVal)
{ 
    return false;
}

bool DService::SetPropVal(const long lPropNum, tVariant* varPropVal)
{ 
    return false;
}

bool DService::IsPropReadable(const long lPropNum)
{ 
    return false;
}

bool DService::IsPropWritable(const long lPropNum)
{
    return false;
}

long DService::GetNMethods()
{ 
    return eLastMethod;
}

long DService::FindMethod(const WCHAR_T* wsMethodName)
{ 
    long plMethodNum = -1;
    wchar_t* name = 0;

    ::convFromShortWchar(&name, wsMethodName);

    plMethodNum = findName(g_MethodNames, name, eLastMethod);

    if (plMethodNum == -1)
        plMethodNum = findName(g_MethodNamesRu, name, eLastMethod);

    return plMethodNum;
}

const WCHAR_T* DService::GetMethodName(const long lMethodNum, const long lMethodAlias)
{ 
    if (lMethodNum >= eLastMethod) {
        return NULL;
    }

    const wchar_t* wsCurrentName = NULL;
    WCHAR_T* wsMethodName = NULL;
    int iActualSize = 0;

    switch (lMethodAlias)
    {
    case 0: // First language
        wsCurrentName = g_MethodNames[lMethodNum];
        break;
    case 1: // Second language
        wsCurrentName = g_MethodNamesRu[lMethodNum];
        break;
    default:
        return 0;
    }

    iActualSize = wcslen(wsCurrentName) + 1;

    if (m_iMemory && wsCurrentName)
    {
        if (m_iMemory->AllocMemory((void**)&wsMethodName, iActualSize * sizeof(WCHAR_T))) {
            ::convToShortWchar(&wsMethodName, wsCurrentName, iActualSize);
        }
    }

    return wsMethodName;
}

long DService::GetNParams(const long lMethodNum)
{ 
    switch (lMethodNum)
    {
    case eVersion:
        return 0;
    case psExec:
        return 1;
    default:
        return 0;
    }
    
    return 0;
}

bool DService::GetParamDefValue(const long lMethodNum, const long lParamNum, tVariant *pvarParamDefValue)
{ 
    TV_VT(pvarParamDefValue) = VTYPE_EMPTY;

    switch (lMethodNum)
    {
    case eVersion:
    case psExec:
        break;
    default:
        return false;
    }

    return false;
} 

bool DService::HasRetVal(const long lMethodNum)
{ 
    switch (lMethodNum)
    {
    case eVersion:
        return true;
    case psExec:
        return true;
    default:
        return false;
    }
    
    return false;
}

bool DService::CallAsProc(const long lMethodNum, tVariant* paParams, const long lSizeArray)
{ 
    return false;
}

bool DService::CallAsFunc(const long lMethodNum, tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray)
{ 

    switch (lMethodNum)
    {
    case eVersion:
    {
        if (pvarRetValue)
        {
            const size_t strLen = wcslen(kComponentVersion);
            if (m_iMemory->AllocMemory((void**)&pvarRetValue->pwstrVal, (strLen + 1) * sizeof(kComponentVersion[0])))
            {
                wcscpy_s((wchar_t*)(pvarRetValue->pwstrVal), strLen + 1, kComponentVersion);
                TV_VT(pvarRetValue) = VTYPE_PWSTR;
                pvarRetValue->wstrLen = strLen;
            }
        }

        break;
    }
    case psExec:
    {
        TV_VT(pvarRetValue) = VTYPE_BOOL;
        pvarRetValue->bVal = true;

        break;
    }
    default:
        return false;
    }

    return false; 
}

void DService::SetLocale(const WCHAR_T* loc)
{
    _wsetlocale(LC_ALL, (wchar_t*)loc);
}

void DService::SetUserInterfaceLanguageCode(const WCHAR_T* lang)
{
    m_userLang.assign(lang);
}

bool DService::setMemManager(void* mem)
{
    m_iMemory = (IMemoryManager*)mem;
    return m_iMemory != 0;
}

long DService::findName(const wchar_t* names[], const wchar_t* name, const uint32_t size) const
{
    long ret = -1;
    for (uint32_t i = 0; i < size; i++)
    {
        if (!wcscmp(names[i], name)) {
            ret = i;
            break;
        }
    }
    return ret;
}

uint32_t convToShortWchar(WCHAR_T** Dest, const wchar_t* Source, uint32_t len)
{
    if (!len) {
        len = ::wcslen(Source)+1;
    }

    if (!*Dest) {
        *Dest = new WCHAR_T[len];
    }

    WCHAR_T* tmpShort = *Dest;
    wchar_t* tmpWChar = (wchar_t*) Source;
    uint32_t res = 0;

    ::memset(*Dest, 0, len*sizeof(WCHAR_T));

    do {
        *tmpShort++ = (WCHAR_T)*tmpWChar++;
        ++res;
    }
    while (len-- && *tmpWChar);

    return res;
}

uint32_t convFromShortWchar(wchar_t** Dest, const WCHAR_T* Source, uint32_t len)
{
    if (!len) {
        len = getLenShortWcharStr(Source)+1;
    }

    if (!*Dest) {
        *Dest = new wchar_t[len];
    }

    wchar_t* tmpWChar = *Dest;
    WCHAR_T* tmpShort = (WCHAR_T*)Source;
    uint32_t res = 0;

    ::memset(*Dest, 0, len*sizeof(wchar_t));

    do {
        *tmpWChar++ = (wchar_t)*tmpShort++;
        ++res;
    }
    while (len-- && *tmpShort);

    return res;
}

uint32_t getLenShortWcharStr(const WCHAR_T* Source)
{
    uint32_t res = 0;
    WCHAR_T *tmpShort = (WCHAR_T*)Source;

    while (*tmpShort++) {
        ++res;
    }

    return res;
}

