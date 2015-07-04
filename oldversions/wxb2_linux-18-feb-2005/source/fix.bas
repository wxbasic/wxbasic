OPEN "junk" FOR INPUT AS #1
OPEN "out" FOR OUTPUT AS #2
WHILE NOT EOF(1)
    LINE INPUT #1, a$
    a$ = MID$(a$, 56)
    a = INSTR(a$, ");")
    a$ = MID$(a$, 1, a - 1)
    PRINT a$
    PRINT #2, "%enum " + a$
WEND
CLOSE

