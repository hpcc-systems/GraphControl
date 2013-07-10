#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for HPCC Systems Graph View Control
#
#\**********************************************************/

include ( "${FB_PROJECTS_DIR}/version.cmake" )

set(PLUGIN_NAME "HPCCSystemsGraphViewControl")
set(PLUGIN_PREFIX "HSGVC")
set(COMPANY_NAME "HPCCSystems")

# ActiveX constants:
set(FBTYPELIB_NAME HPCCSystemsGraphViewControlLib)
set(FBTYPELIB_DESC "HPCCSystemsGraphViewControl 1.0 Type Library")
set(IFBControl_DESC "HPCCSystemsGraphViewControl Control Interface")
set(FBControl_DESC "HPCCSystemsGraphViewControl Control Class")
set(IFBComJavascriptObject_DESC "HPCCSystemsGraphViewControl IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "HPCCSystemsGraphViewControl ComJavascriptObject Class")
set(IFBComEventSource_DESC "HPCCSystemsGraphViewControl IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID ADDF58CE-A46A-42CB-BCFC-F28C4D7F950F)
set(IFBControl_GUID 457AFBF6-B5DF-41F6-8BC2-C9E8135150D2)
set(FBControl_GUID 2FF57548-1DE4-4F32-B133-2B3FBDDBF909)
set(IFBComJavascriptObject_GUID 19170988-05B7-4A75-B249-3F3F18533CDF)
set(FBComJavascriptObject_GUID 8D2D03E7-DE42-4902-B3EA-A16FBE863BEF)
set(IFBComEventSource_GUID E0C8280C-4448-45DF-A750-F1C5A8ED7C40)
if ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 1DD0D554-E642-402E-8330-88B8199562F8)
else ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 199562F8-E642-402E-8330-88B81DD0D554)
endif ( FB_PLATFORM_ARCH_32 )

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "HPCCSystems.HPCCSystemsGraphViewControl")
if ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "hpccsystems.com/HPCCSystemsGraphViewControl") # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "hpccsystems.com/HPCCSystemsGraphViewControl_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )

# strings
set(FBSTRING_CompanyName "HPCC Systems")
set(FBSTRING_PluginDescription "HPCC Systems Graph View Control")
set(FBSTRING_PLUGIN_VERSION "${HPCC_VERSION}")
set(FBSTRING_LegalCopyright "Copyright 2012 HPCC Systems")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}.dll")
set(FBSTRING_ProductName "HPCCSystemsGraphViewControl")
set(FBSTRING_FileExtents "")
if ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "HPCCSystemsGraphViewControl") # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "HPCCSystemsGraphViewControl_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )
set(FBSTRING_MIMEType "application/x-hpccsystemsgraphviewcontrol")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

#set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 1)
set(FBMAC_USE_COCOA 1)
set(FBMAC_USE_COREGRAPHICS 1)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
