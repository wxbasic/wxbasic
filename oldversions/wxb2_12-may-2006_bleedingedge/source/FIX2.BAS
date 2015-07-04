OPEN "opengl.i" FOR INPUT AS #1
OPEN "out.txt" FOR OUTPUT AS #2
WHILE NOT EOF(1)
    LINE INPUT #1, a$
    IF MID$(a$, 1, 4) = "%num" THEN
        a = INSTR(a$, " ")
        b = INSTR(a + 1, a$, " ")
        PRINT #2, MID$(a$, 1, b)
    ELSE
        PRINT #2, a$
    END IF
WEND
CLOSE

