' compile the wxwidgets version
make -f makefile.b32 clean
copy manifest wxbasic.exe.manifest
del wxbasic.exe
'redir -eo make -f makefile.b32 FINAL=0 > out
make -f makefile.b32 FINAL=0 > out
edit out

