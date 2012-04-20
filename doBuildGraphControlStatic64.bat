@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" amd64

set ROOT_DIR=D:\hpccsystems
set SRC_DIR=%ROOT_DIR%\src
set BUILD_DIR=%ROOT_DIR%\build
set EXTERNALS_DIR=%ROOT_DIR%\externals2
echo %SRC_DIR%
echo %BUILD_DIR%
echo %EXTERNALS_DIR%

md %BUILD_DIR%\GraphControlStatic64
cd %BUILD_DIR%\GraphControlStatic64

cmake -G"Visual Studio 10 Win64" -DWITH_STATIC_RUNTIME=1 -DBOOST_INCLUDEDIR="%EXTERNALS_DIR%/Boost/include/boost-1_46_1" -DBOOST_LIBRARYDIR="%EXTERNALS_DIR%/Boost/lib64" -DFIREBREATH_DIR="%EXTERNALS_DIR%/FireBreath" -DFIREBREATH_BUILD_DIR="%EXTERNALS_DIR%/build/FireBreathStatic64" -DGRAPHVIZSRC_DIR="%EXTERNALS_DIR%/graphviz-2.26.3" -DAGGSRC_DIR="%EXTERNALS_DIR%/agg" -DWTL_INCLUDE_DIR="%EXTERNALS_DIR%/wtl81_11324" -DEXPAT_INCLUDE_DIR="%EXTERNALS_DIR%/expat-2.0.1" -DEXPAT_LIBRARY="%EXTERNALS_DIR%/expat-2.0.1" -DFREETYPE_INCLUDE_DIR_freetype2="%EXTERNALS_DIR%/ft248/freetype-2.4.8/include" -DFREETYPE_INCLUDE_DIR_ft2build="%EXTERNALS_DIR%/ft248/freetype-2.4.8/include" -DFREETYPE_LIBRARY:FILEPATH="%EXTERNALS_DIR%/ft248/freetype-2.4.8/objs/win64/vc2010/freetype248MT.lib" "%SRC_DIR%/GraphControl"

set CONFIG_MODE=RelWithDebInfo
call :DOBUILD
goto :EOF

:DOBUILD
msbuild /m /p:Configuration=%CONFIG_MODE% /nologo /noconsolelogger /fl /flp:logfile=%BUILD_DIR%\GraphControlStatic64_%CONFIG_MODE%.txt;ErrorsOnly SIGN.vcxproj 
if not errorlevel 0 goto :ERROR 
goto :EOF

cd ..\..

goto :EOF

:ERROR
echo Build "GraphControlStatic64_%CONFIG_MODE%" Failed!
pause