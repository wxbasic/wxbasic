' -- create the lexer
 del y_tab.c

' for checking of the grammar has problems
' redir -eo bison -d -y wxbasic.y > err
' edit err

' when there are no grammar problems
bison -d -y wxbasic.y
rename y.tab.c y_tab.c

' -- create the wrappers
qbasic /run wrap

' -- compile the program
make -f makefile.b32 clean
redir -eo make -f makefile.b32 FINAL=1 > err
edit err
