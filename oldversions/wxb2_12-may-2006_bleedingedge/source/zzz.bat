'copy \bin\lua.exe
'lua.exe wrap.lua > out

' compile a command line version of wxbasic
bcc32 main.c > out
del wxb.exe
rename main.exe wxb.exe

' use it to create the wrappers
wxb wrap.wxb

' compile the wxwidgets version
make -f makefile.b32 clean
copy manifest wxbasic.exe.manifest
del wxbasic.exe
'redir -eo make -f makefile.b32 FINAL=0 > out
make -f makefile.b32 FINAL=0 > out
edit out
