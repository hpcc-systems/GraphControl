

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __FireBreathWin_i_h__
#define __FireBreathWin_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IFBControl_FWD_DEFINED__
#define __IFBControl_FWD_DEFINED__
typedef interface IFBControl IFBControl;
#endif 	/* __IFBControl_FWD_DEFINED__ */


#ifndef __IFBComJavascriptObject_FWD_DEFINED__
#define __IFBComJavascriptObject_FWD_DEFINED__
typedef interface IFBComJavascriptObject IFBComJavascriptObject;
#endif 	/* __IFBComJavascriptObject_FWD_DEFINED__ */


#ifndef __IFBComEventSource_FWD_DEFINED__
#define __IFBComEventSource_FWD_DEFINED__
typedef interface IFBComEventSource IFBComEventSource;
#endif 	/* __IFBComEventSource_FWD_DEFINED__ */


#ifndef __FBControl0_FWD_DEFINED__
#define __FBControl0_FWD_DEFINED__

#ifdef __cplusplus
typedef class FBControl0 FBControl0;
#else
typedef struct FBControl0 FBControl0;
#endif /* __cplusplus */

#endif 	/* __FBControl0_FWD_DEFINED__ */


#ifndef __FBComJavascriptObject_FWD_DEFINED__
#define __FBComJavascriptObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class FBComJavascriptObject FBComJavascriptObject;
#else
typedef struct FBComJavascriptObject FBComJavascriptObject;
#endif /* __cplusplus */

#endif 	/* __FBComJavascriptObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "dispex.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __HPCCSystemsGraphViewControlLib_LIBRARY_DEFINED__
#define __HPCCSystemsGraphViewControlLib_LIBRARY_DEFINED__

/* library HPCCSystemsGraphViewControlLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_HPCCSystemsGraphViewControlLib;

#ifndef __IFBControl_INTERFACE_DEFINED__
#define __IFBControl_INTERFACE_DEFINED__

/* interface IFBControl */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IFBControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("457AFBF6-B5DF-41F6-8BC2-C9E8135150D2")
    IFBControl : public IDispatchEx
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IFBControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFBControl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFBControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFBControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFBControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFBControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFBControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFBControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetDispID )( 
            IFBControl * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *InvokeEx )( 
            IFBControl * This,
            /* [annotation][in] */ 
            __in  DISPID id,
            /* [annotation][in] */ 
            __in  LCID lcid,
            /* [annotation][in] */ 
            __in  WORD wFlags,
            /* [annotation][in] */ 
            __in  DISPPARAMS *pdp,
            /* [annotation][out] */ 
            __out_opt  VARIANT *pvarRes,
            /* [annotation][out] */ 
            __out_opt  EXCEPINFO *pei,
            /* [annotation][unique][in] */ 
            __in_opt  IServiceProvider *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteMemberByName )( 
            IFBControl * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteMemberByDispID )( 
            IFBControl * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE *GetMemberProperties )( 
            IFBControl * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE *GetMemberName )( 
            IFBControl * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE *GetNextDispID )( 
            IFBControl * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID *pid);
        
        HRESULT ( STDMETHODCALLTYPE *GetNameSpaceParent )( 
            IFBControl * This,
            /* [out] */ IUnknown **ppunk);
        
        END_INTERFACE
    } IFBControlVtbl;

    interface IFBControl
    {
        CONST_VTBL struct IFBControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFBControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFBControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFBControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFBControl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFBControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFBControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFBControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IFBControl_GetDispID(This,bstrName,grfdex,pid)	\
    ( (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid) ) 

#define IFBControl_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    ( (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller) ) 

#define IFBControl_DeleteMemberByName(This,bstrName,grfdex)	\
    ( (This)->lpVtbl -> DeleteMemberByName(This,bstrName,grfdex) ) 

#define IFBControl_DeleteMemberByDispID(This,id)	\
    ( (This)->lpVtbl -> DeleteMemberByDispID(This,id) ) 

#define IFBControl_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    ( (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex) ) 

#define IFBControl_GetMemberName(This,id,pbstrName)	\
    ( (This)->lpVtbl -> GetMemberName(This,id,pbstrName) ) 

#define IFBControl_GetNextDispID(This,grfdex,id,pid)	\
    ( (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid) ) 

#define IFBControl_GetNameSpaceParent(This,ppunk)	\
    ( (This)->lpVtbl -> GetNameSpaceParent(This,ppunk) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFBControl_INTERFACE_DEFINED__ */


#ifndef __IFBComJavascriptObject_INTERFACE_DEFINED__
#define __IFBComJavascriptObject_INTERFACE_DEFINED__

/* interface IFBComJavascriptObject */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IFBComJavascriptObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19170988-05B7-4A75-B249-3F3F18533CDF")
    IFBComJavascriptObject : public IDispatchEx
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IFBComJavascriptObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFBComJavascriptObject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFBComJavascriptObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFBComJavascriptObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFBComJavascriptObject * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFBComJavascriptObject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFBComJavascriptObject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFBComJavascriptObject * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetDispID )( 
            IFBComJavascriptObject * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex,
            /* [out] */ DISPID *pid);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *InvokeEx )( 
            IFBComJavascriptObject * This,
            /* [annotation][in] */ 
            __in  DISPID id,
            /* [annotation][in] */ 
            __in  LCID lcid,
            /* [annotation][in] */ 
            __in  WORD wFlags,
            /* [annotation][in] */ 
            __in  DISPPARAMS *pdp,
            /* [annotation][out] */ 
            __out_opt  VARIANT *pvarRes,
            /* [annotation][out] */ 
            __out_opt  EXCEPINFO *pei,
            /* [annotation][unique][in] */ 
            __in_opt  IServiceProvider *pspCaller);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteMemberByName )( 
            IFBComJavascriptObject * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD grfdex);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteMemberByDispID )( 
            IFBComJavascriptObject * This,
            /* [in] */ DISPID id);
        
        HRESULT ( STDMETHODCALLTYPE *GetMemberProperties )( 
            IFBComJavascriptObject * This,
            /* [in] */ DISPID id,
            /* [in] */ DWORD grfdexFetch,
            /* [out] */ DWORD *pgrfdex);
        
        HRESULT ( STDMETHODCALLTYPE *GetMemberName )( 
            IFBComJavascriptObject * This,
            /* [in] */ DISPID id,
            /* [out] */ BSTR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE *GetNextDispID )( 
            IFBComJavascriptObject * This,
            /* [in] */ DWORD grfdex,
            /* [in] */ DISPID id,
            /* [out] */ DISPID *pid);
        
        HRESULT ( STDMETHODCALLTYPE *GetNameSpaceParent )( 
            IFBComJavascriptObject * This,
            /* [out] */ IUnknown **ppunk);
        
        END_INTERFACE
    } IFBComJavascriptObjectVtbl;

    interface IFBComJavascriptObject
    {
        CONST_VTBL struct IFBComJavascriptObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFBComJavascriptObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFBComJavascriptObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFBComJavascriptObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFBComJavascriptObject_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFBComJavascriptObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFBComJavascriptObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFBComJavascriptObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IFBComJavascriptObject_GetDispID(This,bstrName,grfdex,pid)	\
    ( (This)->lpVtbl -> GetDispID(This,bstrName,grfdex,pid) ) 

#define IFBComJavascriptObject_InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller)	\
    ( (This)->lpVtbl -> InvokeEx(This,id,lcid,wFlags,pdp,pvarRes,pei,pspCaller) ) 

#define IFBComJavascriptObject_DeleteMemberByName(This,bstrName,grfdex)	\
    ( (This)->lpVtbl -> DeleteMemberByName(This,bstrName,grfdex) ) 

#define IFBComJavascriptObject_DeleteMemberByDispID(This,id)	\
    ( (This)->lpVtbl -> DeleteMemberByDispID(This,id) ) 

#define IFBComJavascriptObject_GetMemberProperties(This,id,grfdexFetch,pgrfdex)	\
    ( (This)->lpVtbl -> GetMemberProperties(This,id,grfdexFetch,pgrfdex) ) 

#define IFBComJavascriptObject_GetMemberName(This,id,pbstrName)	\
    ( (This)->lpVtbl -> GetMemberName(This,id,pbstrName) ) 

#define IFBComJavascriptObject_GetNextDispID(This,grfdex,id,pid)	\
    ( (This)->lpVtbl -> GetNextDispID(This,grfdex,id,pid) ) 

#define IFBComJavascriptObject_GetNameSpaceParent(This,ppunk)	\
    ( (This)->lpVtbl -> GetNameSpaceParent(This,ppunk) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFBComJavascriptObject_INTERFACE_DEFINED__ */


#ifndef __IFBComEventSource_DISPINTERFACE_DEFINED__
#define __IFBComEventSource_DISPINTERFACE_DEFINED__

/* dispinterface IFBComEventSource */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID_IFBComEventSource;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("E0C8280C-4448-45DF-A750-F1C5A8ED7C40")
    IFBComEventSource : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IFBComEventSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFBComEventSource * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFBComEventSource * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFBComEventSource * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFBComEventSource * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFBComEventSource * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFBComEventSource * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFBComEventSource * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IFBComEventSourceVtbl;

    interface IFBComEventSource
    {
        CONST_VTBL struct IFBComEventSourceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFBComEventSource_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFBComEventSource_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFBComEventSource_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFBComEventSource_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFBComEventSource_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFBComEventSource_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFBComEventSource_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IFBComEventSource_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_FBControl0;

#ifdef __cplusplus

class DECLSPEC_UUID("2FF57548-1DE4-4F32-B133-2B3FBDDBF909")
FBControl0;
#endif

EXTERN_C const CLSID CLSID_FBComJavascriptObject;

#ifdef __cplusplus

class DECLSPEC_UUID("8D2D03E7-DE42-4902-B3EA-A16FBE863BEF")
FBComJavascriptObject;
#endif
#endif /* __HPCCSystemsGraphViewControlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


