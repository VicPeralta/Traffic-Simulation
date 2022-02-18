SET INCLUDEOPENCV=C:\Users\Victor\Downloads\vcpkg\packages\opencv4_x86-windows\include
SET LIBPATHOPENCV=C:\Users\Victor\Downloads\vcpkg\packages\opencv4_x86-windows\debug\lib
SET VC_LibraryPath_x86=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.16.27023\lib\x86
SET WindowsSDK_LibraryPath_x86=C:\Program Files (x86)\Windows Kits\10\lib\10.0.17763.0\ucrt\x86
SET COMPILEROPTIONS= -EHsc /W3 -std:c++17 /D "_CRT_SECURE_NO_WARNINGS" /MDd /Z7 /Fobuild\
SET SOURCEFILES=..\src\*.cpp
cl %SOURCEFILES% %COMPILEROPTIONS% /I %INCLUDEOPENCV% /link /LIBPATH:"%LIBPATHOPENCV%" /LIBPATH:"%VC_LibraryPath_x86%" /LIBPATH:"%WindowsSDK_LibraryPath_x86%" opencv_cored.lib opencv_imgprocd.lib opencv_imgcodecsd.lib opencv_highguid.lib /OUT:traffic_simulation.exe