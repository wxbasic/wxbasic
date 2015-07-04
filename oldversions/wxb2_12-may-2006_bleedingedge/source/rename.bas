OPEN "out" FOR INPUT AS #1
OPEN "tmp.bat" FOR OUTPUT AS #2
WHILE NOT EOF(1)
    LINE INPUT #1, a$
    b$ = LCASE$(a$)
    IF a$ <> b$ THEN
        PRINT #2, "rename " + CHR$(34) + a$ + CHR$(34) + " " + CHR$(34) + b$ + CHR$(34)
    END IF
WEND
CLOSE

