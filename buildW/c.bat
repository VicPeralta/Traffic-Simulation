SET INCLUDEOPENCV=C:\Users\Victor\Downloads\vcpkg\packages\opencv4_x86-windows\include
SET COMPILEROPTIONS= /c -EHsc /W3 -std:c++17 /D "_CRT_SECURE_NO_WARNINGS" /MDd /Z7 /Fobuild\
SET SOURCEFILES=..\src\%1
echo compiling
cl %SOURCEFILES% %COMPILEROPTIONS% /I %INCLUDEOPENCV% 