

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Mar 22 09:55:19 2011
 */
/* Compiler settings for D:/@gjs/develop/gui/firebreath/build/projects/HPCCSystemsGraphViewControl/gen/FireBreathWin.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_HPCCSystemsGraphViewControlLib,0xADDF58CE,0xA46A,0x42CB,0xBC,0xFC,0xF2,0x8C,0x4D,0x7F,0x95,0x0F);


MIDL_DEFINE_GUID(IID, IID_IFBControl,0x457AFBF6,0xB5DF,0x41F6,0x8B,0xC2,0xC9,0xE8,0x13,0x51,0x50,0xD2);


MIDL_DEFINE_GUID(IID, IID_IFBComJavascriptObject,0x19170988,0x05B7,0x4A75,0xB2,0x49,0x3F,0x3F,0x18,0x53,0x3C,0xDF);


MIDL_DEFINE_GUID(IID, DIID_IFBComEventSource,0xE0C8280C,0x4448,0x45DF,0xA7,0x50,0xF1,0xC5,0xA8,0xED,0x7C,0x40);


MIDL_DEFINE_GUID(CLSID, CLSID_FBControl0,0x2FF57548,0x1DE4,0x4F32,0xB1,0x33,0x2B,0x3F,0xBD,0xDB,0xF9,0x09);


MIDL_DEFINE_GUID(CLSID, CLSID_FBComJavascriptObject,0x8D2D03E7,0xDE42,0x4902,0xB3,0xEA,0xA1,0x6F,0xBE,0x86,0x3B,0xEF);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



