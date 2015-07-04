del y_tab.c
' for checking of the grammar has problems
' redir -eo bison -d -y wxbasic.y > err
' edit err

' when there are no grammar problems
bison -d -y wxbasic.y

rename y.tab.c y_tab.c

redir -eo gcc core.c -owxbasic.exe > err
edit err

