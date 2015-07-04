/*
    Name:       builtin.h
    Purpose:    builtin routines for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

void wNotYet( char *name );
void wBasPrintStack(void);
void wBasAbs(void);
void wBasACos(void);
void wBasAndBits(void);
void wBasArgc(void);
void wBasArgv(void);
void wBasAsc(void);
void wBasASin(void);
void wBasATan(void);
void wBasChDir(void);
void wBasChr(void);
void wBasCommand(void);
void wBasConcat(void);
void wBasConnect(void);
void wBasConvBase(void);
void wBasCos(void);
void wBasDate(void);
void wBasDir(void);
void wBasDirExists(void);
void wBasEof(void);
void wBasExp(void);
void wBasFClose(void);
void wBasFGets(void);
void wBasFileExists(void);
void wBasFix(void);
void wBasFOpen(void);
void wBasFormat(void);
void wBasFPuts(void);
void wBasFrac(void);
void wBasFreeFile(void);
void wBasGetWxApp(void);
void wBasHex(void);
void wBasIndexes(void);
void wBasInsert(void);
void wBasInstr(void);
void wBasInt(void);
void wBasKill(void);
void wBasLCase(void);
void wBasLeft(void);
void wBasLen(void);
void wBasLoc(void);
void wBasLof(void);
void wBasLog(void);
void wBasLBound(void);
void wBasLTrim(void);             
void wBasMainLoop(void);
void wBasMid(void);
void wBasMkDir(void);
void wBasNotBits(void);
void wBasOrBits(void);
void wBasQuickSort(void);
void wBasRandomize(void);
void wBasReadByte(void);
void wBasRename(void);
void wBasReplace(void);
void wBasReplaceSubStr(void);
void wBasResource(void);
void wBasResourceCount(void);
void wBasReverse(void);  
void wBasRight(void);   
void wBasRInstr(void);
void wBasRmDir(void);
void wBasRnd(void);
void wBasRound(void);
void wBasRTrim(void);
void wBasRun(void);
void wBasSeek(void);
void wBasSgn(void);
void wBasShell(void);
void wBasSin(void);
void wBasSpace(void);
void wBasSqr(void);
void wBasStr(void);
void wBasStrF(void);
void wBasString(void);
void wBasTally(void);
void wBasTan(void);
void wBasTicks(void);
void wBasTime(void);
void wBasTypeOf(void);
void wBasUBound(void);
void wBasUCase(void);
void wBasVal(void);
void wBasWriteByte(void);
void wBasXorBits(void);

wSymbol *wAddBuiltin( char *name, void (*routine)(void), int args, int optArgs );
void wInitBuiltins(void);

static struct {     /* builtin routines */
    char    *name;
    void    (*routine)(void);
    int     args;
    int     optArgs;
} wBuiltin[] = {
    {"printstack",      wBasPrintStack,      0,  0},
    {"abs",             wBasAbs,             1,  0},
    {"acos",            wBasACos,            1,  0},
    {"andbits",         wBasAndBits,         2,  0},
    {"argc",            wBasArgc,            0,  0},
    {"argv",            wBasArgv,            1,  0},
    {"asc",             wBasAsc,             1,  0},
    {"asin",            wBasASin,            1,  0},
    {"atan",            wBasATan,            1,  0},
    {"chdir",           wBasChDir,           1,  0},
    {"chr",             wBasChr,             1,  0},
    {"chr$",            wBasChr,             1,  0},
    {"command",         wBasCommand,         0,  1},
    {"command$",        wBasCommand,         0,  1},
    {"connect",         wBasConnect,         3,  1},
    {"convbase",        wBasConvBase,        2,  0},
    {"convbase$",       wBasConvBase,        2,  0},
    {"cos",             wBasCos,             1,  0},
    {"date",            wBasDate,            0,  0},
    {"date$",           wBasDate,            0,  0},
    {"hasdir",          wBasDir,             0,  0},
    {"hasdir$",         wBasDir,             0,  0},
    {"direxists",       wBasDirExists,       1,  0},
    {"eof",             wBasEof,             1,  0},
    {"exp",             wBasExp,             1,  0},
    {"fclose",          wBasFClose,          1,  0},
    {"fgets",           wBasFGets,           1,  0},
    {"fileexists",      wBasFileExists,      1,  0},
    {"fix",             wBasFix,             1,  0},
    {"floor",           wBasFix,             1,  0},
    {"fopen",           wBasFOpen,           2,  0},
    {"format",          wBasFormat,          1,  20},
    {"format$",         wBasFormat,          1,  20},
    {"fputs",           wBasFPuts,           2,  0},
    {"frac",            wBasFrac,            1,  0},
    {"freefile",        wBasFreeFile,        0,  0},
    {"getwxapp",        wBasGetWxApp,        0,  0},
    {"hex",             wBasHex,             1,  0},
    {"hex$",            wBasHex,             1,  0},
    {"indexes",         wBasIndexes,         1,  0},
    {"insert",          wBasInsert,          3,  0},
    {"insert$",         wBasInsert,          3,  0},
    {"instr",           wBasInstr,           2,  1},
    {"int",             wBasInt,             1,  0},
    {"kill",            wBasKill,            1,  0},
    {"lcase",           wBasLCase,           1,  0},
    {"lcase$",          wBasLCase,           1,  0},
    {"left",            wBasLeft,            2,  0},
    {"left$",           wBasLeft,            2,  0},
    {"len",             wBasLen,             1,  0},
    {"length",          wBasLen,             1,  0},
    {"loc",             wBasLoc,             1,  0},
    {"lof",             wBasLof,             1,  0},
    {"log",             wBasLog,             1,  0},
    {"lbound",          wBasLBound,          2,  0},
    {"ltrim",           wBasLTrim,           1,  0},
    {"ltrim$",          wBasLTrim,           1,  0},
    {"mainloop",        wBasMainLoop,        0,  0},
    {"mid",             wBasMid,             3,  0},
    {"mid$",            wBasMid,             3,  0},
    {"mkdir",           wBasMkDir,           1,  0},
    {"notbits",         wBasNotBits,         1,  0},
    {"orbits",          wBasOrBits,          2,  0},
    {"quicksort",       wBasQuickSort,       3,  0},
    {"randomize",       wBasRandomize,       0,  1},
    {"readbyte",        wBasReadByte,        1,  0},
    {"rename",          wBasRename,          2,  0},
    {"replace",         wBasReplace,         2,  0},
    {"replace$",        wBasReplace,         2,  0},
    {"replacesubstr",   wBasReplaceSubStr,   3,  0},
    {"replacesubstr$",  wBasReplaceSubStr,   3,  0},
    {"reverse",         wBasReverse,         1,  0},
    {"reverse$",        wBasReverse,         1,  0},
    {"right",           wBasRight,           2,  0},
    {"right$",          wBasRight,           2,  0},
    {"rinstr",          wBasRInstr,          2,  1},
    {"rmdir",           wBasRmDir,           2,  0},
    {"rnd",             wBasRnd,             0,  1},
    {"round",           wBasRound,           1,  0},
    {"rtrim",           wBasRTrim,           1,  0},
    {"rtrim$",          wBasRTrim,           1,  0},
    {"run",             wBasRun,             1,  0},
    {"seek",            wBasSeek,            1,  1},
    {"sgn",             wBasSgn,             1,  0},
    {"shell",           wBasShell,           1,  0},
    {"sin",             wBasSin,             1,  0},
    {"space",           wBasSpace,           1,  0},
    {"space$",          wBasSpace,           2,  0},
    {"sqr",             wBasSqr,             1,  0},
    {"str",             wBasStr,             1,  0},
    {"str$",            wBasStr,             1,  0},
    {"strf",            wBasStrF,            4,  0},
    {"strf$",           wBasStrF,            4,  0},
    {"string",          wBasString,          2,  0},
    {"string$",         wBasString,          2,  0},
    {"tally",           wBasTally,           2,  0},
    {"tan",             wBasTan,             1,  0},
    {"ticks",           wBasTicks,           0,  0},
    {"time",            wBasTime,            0,  0},
    {"time$",           wBasTime,            0,  0},
    {"typeof$",         wBasTypeOf,          1,  0},
    {"typeof",          wBasTypeOf,          1,  0},
    {"ubound",          wBasUBound,          2,  0},
    {"ucase",           wBasUCase,           1,  0},
    {"ucase$",          wBasUCase,           1,  0},
    {"val",             wBasVal,             1,  0},
    {"writebyte",       wBasWriteByte,       2,  0},
    {"xorbits",         wBasXorBits,         2,  0},
    {NULL,              NULL,               0,  0}
};
                                             
