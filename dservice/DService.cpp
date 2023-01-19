
#include "stdafx.h"

#include <wchar.h>
#include <string>
#include <locale>
#include "DService.h"

static const wchar_t g_kClassNames[] = L"DService"; //|OtherClass1|OtherClass2";

uint32_t convToShortWchar(WCHAR_T** Dest, const wchar_t* Source, uint32_t len = 0);
uint32_t convFromShortWchar(wchar_t** Dest, const WCHAR_T* Source, uint32_t len = 0);
uint32_t getLenShortWcharStr(const WCHAR_T* Source);

//---------------------------------------------------------------------------//
long GetClassObject(const wchar_t* wsName, IComponentBase** pInterface)
{
    if(!*pInterface)
    {
        *pInterface= new DService();
        return (long)*pInterface;
    }
    return 0;
}
//---------------------------------------------------------------------------//
long DestroyObject(IComponentBase** pIntf)
{
   if(!*pIntf)
      return -1;

   delete *pIntf;
   *pIntf = 0;
   return 0;
}
//---------------------------------------------------------------------------//
const WCHAR_T* GetClassNames()
{
    static WCHAR_T* names = 0;
    if (!names)
        ::convToShortWchar(&names, g_kClassNames);
    return names;
}
//---------------------------------------------------------------------------//
//DService
DService::DService()
{
}
//---------------------------------------------------------------------------//
DService::~DService()
{
}
//---------------------------------------------------------------------------//
bool DService::Init(void* pConnection)
{ 
    return false;
}
//---------------------------------------------------------------------------//
long DService::GetInfo()
{ 
    return 2000; 
}
//---------------------------------------------------------------------------//
void DService::Done()
{
}
//---------------------------------------------------------------------------//
bool DService::RegisterExtensionAs(WCHAR_T** wsLanguageExt)
{ 
    return false; 
}
//---------------------------------------------------------------------------//
long DService::GetNProps()
{ 
    return eLastProp;
}
//---------------------------------------------------------------------------//
long DService::FindProp(const WCHAR_T* wsPropName)
{ 
    return -1;
}
//---------------------------------------------------------------------------//
const WCHAR_T* DService::GetPropName(long lPropNum, long lPropAlias)
{ 
    return 0;
}
//---------------------------------------------------------------------------//
bool DService::GetPropVal(const long lPropNum, tVariant* pvarPropVal)
{ 
    return false;
}
//---------------------------------------------------------------------------//
bool DService::SetPropVal(const long lPropNum, tVariant* varPropVal)
{ 
    return false;
}
//---------------------------------------------------------------------------//
bool DService::IsPropReadable(const long lPropNum)
{ 
    return false;
}
//---------------------------------------------------------------------------//
bool DService::IsPropWritable(const long lPropNum)
{
    return false;
}
//---------------------------------------------------------------------------//
long DService::GetNMethods()
{ 
    return eLastMethod;
}
//---------------------------------------------------------------------------//
long DService::FindMethod(const WCHAR_T* wsMethodName)
{ 
    return -1;
}
//---------------------------------------------------------------------------//
const WCHAR_T* DService::GetMethodName(const long lMethodNum, 
                            const long lMethodAlias)
{ 
    return 0;
}
//---------------------------------------------------------------------------//
long DService::GetNParams(const long lMethodNum)
{ 
    return 0;
}
//---------------------------------------------------------------------------//
bool DService::GetParamDefValue(const long lMethodNum, const long lParamNum,
                          tVariant *pvarParamDefValue)
{ 
    return false;
} 
//---------------------------------------------------------------------------//
bool DService::HasRetVal(const long lMethodNum)
{ 
    return false;
}
//---------------------------------------------------------------------------//
bool DService::CallAsProc(const long lMethodNum,
                    tVariant* paParams, const long lSizeArray)
{ 
    return false;
}
//---------------------------------------------------------------------------//
bool DService::CallAsFunc(const long lMethodNum,
                tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray)
{ 
    return false; 
}
//---------------------------------------------------------------------------//
void DService::SetLocale(const WCHAR_T* loc)
{
    _wsetlocale(LC_ALL, (wchar_t*)loc);
}
//---------------------------------------------------------------------------//
void DService::SetUserInterfaceLanguageCode(const WCHAR_T* lang)
{
    m_userLang.assign(lang);
}
//---------------------------------------------------------------------------//
bool DService::setMemManager(void* mem)
{
    return false;
}
//---------------------------------------------------------------------------//
uint32_t convToShortWchar(WCHAR_T** Dest, const wchar_t* Source, uint32_t len)
{
    if (!len)
        len = ::wcslen(Source)+1;

    if (!*Dest)
        *Dest = new WCHAR_T[len];

    WCHAR_T* tmpShort = *Dest;
    wchar_t* tmpWChar = (wchar_t*) Source;
    uint32_t res = 0;

    ::memset(*Dest, 0, len*sizeof(WCHAR_T));
    do
    {
        *tmpShort++ = (WCHAR_T)*tmpWChar++;
        ++res;
    }
    while (len-- && *tmpWChar);

    return res;
}
//---------------------------------------------------------------------------//
uint32_t convFromShortWchar(wchar_t** Dest, const WCHAR_T* Source, uint32_t len)
{
    if (!len)
        len = getLenShortWcharStr(Source)+1;

    if (!*Dest)
        *Dest = new wchar_t[len];

    wchar_t* tmpWChar = *Dest;
    WCHAR_T* tmpShort = (WCHAR_T*)Source;
    uint32_t res = 0;

    ::memset(*Dest, 0, len*sizeof(wchar_t));
    do
    {
        *tmpWChar++ = (wchar_t)*tmpShort++;
        ++res;
    }
    while (len-- && *tmpShort);

    return res;
}
//---------------------------------------------------------------------------//
uint32_t getLenShortWcharStr(const WCHAR_T* Source)
{
    uint32_t res = 0;
    WCHAR_T *tmpShort = (WCHAR_T*)Source;

    while (*tmpShort++)
        ++res;

    return res;
}
//---------------------------------------------------------------------------//
