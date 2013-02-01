@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" x86

set ROOT_DIR=D:\hpccsystems
set SRC_DIR=%ROOT_DIR%\src
set BUILD_DIR=%ROOT_DIR%\build
set EXTERNALS_DIR=%ROOT_DIR%\externals2
echo %SRC_DIR%
echo %BUILD_DIR%
echo %EXTERNALS_DIR%

md %BUILD_DIR%\GraphControlStatic_3_10
cd %BUILD_DIR%\GraphControlStatic_3_10

cmake -G"Visual Studio 10" -DWITH_SYSTEM_BOOST=1 -DFB_PROJECTS_DIR:PATH="%SRC_DIR%/GraphControl" -DBOOST_INCLUDEDIR="%EXTERNALS_DIR%/Boost/include/boost-1_46_1" -DBOOST_LIBRARYDIR="%EXTERNALS_DIR%/Boost/lib" -DGRAPHVIZSRC_DIR="%EXTERNALS_DIR%/graphviz-2.26.3" -DAGGSRC_DIR="%EXTERNALS_DIR%/agg" -DEXPAT_INCLUDE_DIR="%EXTERNALS_DIR%/expat-2.0.1" -DEXPAT_LIBRARY="%EXTERNALS_DIR%/expat-2.0.1" -DFREETYPE_INCLUDE_DIR_freetype2="%EXTERNALS_DIR%/ft248/freetype-2.4.8/include" -DFREETYPE_INCLUDE_DIR_ft2build="%EXTERNALS_DIR%/ft248/freetype-2.4.8/include" -DFREETYPE_LIBRARY:FILEPATH="%EXTERNALS_DIR%/ft248/freetype-2.4.8/objs/win32/vc2010/freetype248MT.lib" "%SRC_DIR%/FireBreath"

set CONFIG_MODE=RelWithDebInfo
call :DOBUILD
goto :EOF

:DOBUILD
cmake --build . --config %CONFIG_MODE%
if not errorlevel 0 goto :ERROR 
goto :EOF

cd ..\..

goto :EOF

:ERROR
echo Build "GraphControlStatic_3_10_%CONFIG_MODE%" Failed!
pause