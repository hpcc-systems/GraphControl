@echo off
cd build
cmake ..
msbuild GraphControl.sln /m /p:Configuration=Release
cd ..