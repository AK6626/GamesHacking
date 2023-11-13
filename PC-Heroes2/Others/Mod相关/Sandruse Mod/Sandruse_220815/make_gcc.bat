g++ 3.cpp -shared -o 3.dll -Wl,--kill-at,--enable-stdcall-fixup,-output-def,3.def -L -l -mwindows -m32
pause