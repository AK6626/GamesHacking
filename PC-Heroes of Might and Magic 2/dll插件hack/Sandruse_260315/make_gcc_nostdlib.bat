call mg492.bat
g++ 3.cpp -shared -o 3.dll -O2 -m32 -Wl,--kill-at,--enable-stdcall-fixup,-output-def,3.def -nostdlib -Wl,--entry=_DllMain@12 -lkernel32
pause
rem g++ 3.cpp -shared -o 3.dll -Wl,--kill-at,--enable-stdcall-fixup,-output-def,3.def -L -l -m32