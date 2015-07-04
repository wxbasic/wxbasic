OPEN "test.bas" FOR OUTPUT AS #1
FOR i = 80 TO 255
PRINT #1, "' character" + STR$(i) + " " + CHR$(i)
PRINT #1, "Print " + CHR$(34) + CHR$(i) + CHR$(34)
NEXT
CLOSE


