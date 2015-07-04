' redir -eo bcc32 main.c > out
bcc32 -g255 main.c > out
del wxb.exe
rename main.exe wxb.exe
edit out
