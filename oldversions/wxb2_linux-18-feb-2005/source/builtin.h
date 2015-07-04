/*************************************************************
    Name:       builtin.c
    Purpose:    builtin routine for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

void wNotYet( char *name );
void wBuiltinAbs(void);
void wBuiltinACos(void);
void wBuiltinAndBits(void);
void wBuiltinAppend(void);
void wBuiltinArgc(void);
void wBuiltinArgv(void);
void wBuiltinArrayBound( int getLower );
void wBuiltinAsc(void);
void wBuiltinASin(void);
void wBuiltinATan(void);
void wBuiltinChDir(void);
void wBuiltinChr(void);
void wBuiltinClone(void);
void wBuiltinCommand(void);
void wBuiltinConcat(void);
void wBuiltinConnect(void);
void wBuiltinCos(void);
void wBuiltinCount(void);
void wBuiltinDate(void);
void wBuiltinDay(void);
void wBuiltinDir(void);
void wBuiltinDirExists(void);
void wBuiltinDisconnect(void);
void wBuiltinEof(void);
void wBuiltinExp(void);
void wBuiltinFClose(void);
void wBuiltinFGets(void);
void wBuiltinFileExists(void);
void wBuiltinFix(void);
void wBuiltinFOpen(void);
void wBuiltinFormat(void);
void wBuiltinFPuts(void);
void wBuiltinFrac(void);
void wBuiltinFreeFile(void);
void wBuiltinGetWxApp(void);
void wBuiltinGetWxHandle(void);
void wBuiltinHasKey(void);
void wBuiltinHex(void);
void wBuiltinHour(void);
void wBuiltinIndexes(void);
void wBuiltinInsert(void);
void wBuiltinInsertAt(void);
void wBuiltinIsNothing(void);
void wBuiltinIsNumeric(void);
void wBuiltinInstr(void);
void wBuiltinInt(void);
void wBuiltinKill(void);
void wBuiltinLCase(void);
void wBuiltinLeft(void);
void wBuiltinLen(void);
void wBuiltinLoc(void);
void wBuiltinLof(void);
void wBuiltinLog(void);
void wBuiltinLBound(void);
void wBuiltinLTrim(void);             
void wBuiltinMid(void);
void wBuiltinMinute(void);
void wBuiltinMkDir(void);
void wBuiltinMonth(void);
void wBuiltinMonthName(void);
void wBuiltinNotBits(void);
void wBuiltinNow(void);
void wBuiltinOrBits(void);
void wBuiltinPrepend(void);
void wBuiltinQuickSort(void);
void wBuiltinRandomize(void);
void wBuiltinReadByte(void);
void wBuiltinRename(void);
void wBuiltinRepeat(void);
void wBuiltinReplace(void);
void wBuiltinResource(void);
void wBuiltinResourceCount(void);
void wBuiltinReverse(void);  
void wBuiltinRight(void);   
void wBuiltinRInstr(void);
void wBuiltinRmDir(void);
void wBuiltinRnd(void);
void wBuiltinRound(void);
void wBuiltinRTrim(void);
void wBuiltinRun(void);
void wBuiltinSecond(void);
void wBuiltinSeek(void);
void wBuiltinSgn(void);
void wBuiltinShell(void);
void wBuiltinSin(void);
void wBuiltinSlice(void);
void wBuiltinSpace(void);
void wBuiltinSqr(void);
void wBuiltinStr(void);
void wBuiltinStrF(void);
void wBuiltinSubStr(void);
void wBuiltinTally(void);
void wBuiltinTan(void);
void wBuiltinTicks(void);
void wBuiltinTime(void);
void wBuiltinTimeValue(void);
void wBuiltinTrace(void);
void wBuiltinTrim(void);
void wBuiltinTypeOf(void);
void wBuiltinUBound(void);
void wBuiltinUCase(void);
void wBuiltinVal(void);
void wBuiltinWeekday(void);
void wBuiltinWeekdayName(void);
void wBuiltinWriteByte(void);
void wBuiltinXorBits(void);
void wBuiltinYear(void);

wSymbol *wBuiltinNew( char *name, void (*routine)(void), int args, int optArgs );
void wBuiltinInit(void);

static struct {     /* builtin routines */
    char    *name;
    void    (*routine)(void);
    int     args;
    int     optArgs;
} wBuiltin[] = {
    {"abs",             wBuiltinAbs,             1,  0},
    {"acos",            wBuiltinACos,            1,  0},
    {"andbits",         wBuiltinAndBits,         2,  0},
    {"append",          wBuiltinAppend,          2,  0},
    {"append$",         wBuiltinAppend,          2,  0},
    {"argc",            wBuiltinArgc,            0,  0},
    {"argv",            wBuiltinArgv,            1,  0},
    {"asc",             wBuiltinAsc,             1,  0},
    {"asin",            wBuiltinASin,            1,  0},
    {"atan",            wBuiltinATan,            1,  0},
    {"chdir",           wBuiltinChDir,           1,  0},
    {"chr",             wBuiltinChr,             1,  0},
    {"chr$",            wBuiltinChr,             1,  0},
    {"clone",           wBuiltinClone,           1,  0},
    {"command",         wBuiltinCommand,         0,  1},
    {"connect",         wBuiltinConnect,         3,  1},
    {"count",           wBuiltinCount,           1,  0},
    {"cos",             wBuiltinCos,             1,  0},
    {"date",            wBuiltinDate,            0,  0},
    {"datevalue",       wBuiltinTimeValue,       1,  0},
    {"day",             wBuiltinDay,             1,  0},
    {"hasdir",          wBuiltinDir,             0,  0},
    {"direxists",       wBuiltinDirExists,       1,  0},
    {"disconnect",      wBuiltinDisconnect,      2,  1},
    {"eof",             wBuiltinEof,             1,  0},
    {"exp",             wBuiltinExp,             1,  0},
    {"fclose",          wBuiltinFClose,          1,  0},
    {"fgets",           wBuiltinFGets,           1,  0},
    {"fileexists",      wBuiltinFileExists,      1,  0},
    {"fix",             wBuiltinFix,             1,  0},
    {"floor",           wBuiltinFix,             1,  0},
    {"fopen",           wBuiltinFOpen,           2,  0},
    {"format",          wBuiltinFormat,          1,  20},
    {"format$",         wBuiltinFormat,          1,  20},
    {"fputs",           wBuiltinFPuts,           2,  0},
    {"frac",            wBuiltinFrac,            1,  0},
    {"freefile",        wBuiltinFreeFile,        0,  0},
    {"gettype",          wBuiltinTypeOf,          1,  0},
    {"getwxapp",        wBuiltinGetWxApp,        0,  0},
    {"getwxhandle",     wBuiltinGetWxHandle,     1,  0},
    {"haskey",          wBuiltinHasKey,          2,  0},
    {"hex",             wBuiltinHex,             1,  0},
    {"hour",            wBuiltinHour,            1,  0},
    {"indexes",         wBuiltinIndexes,         1,  0},
    {"insert",          wBuiltinInsert,          3,  0},
    {"isnothing",       wBuiltinIsNothing,       1,  0},
    {"isnumeric",       wBuiltinIsNumeric,       1,  0},
    {"insertat",        wBuiltinInsert,          2,  0},
    {"instr",           wBuiltinInstr,           2,  1},
    {"instr$",          wBuiltinInstr,           2,  1},
    {"int",             wBuiltinInt,             1,  0},
    {"kill",            wBuiltinKill,            1,  0},
    {"lcase",           wBuiltinLCase,           1,  0},
    {"lcase$",          wBuiltinLCase,           1,  0},
    {"left",            wBuiltinLeft,            2,  0},
    {"left$",           wBuiltinLeft,            2,  0},
    {"len",             wBuiltinLen,             1,  0},
    {"length",          wBuiltinLen,             1,  0},
    {"loc",             wBuiltinLoc,             1,  0},
    {"lof",             wBuiltinLof,             1,  0},
    {"log",             wBuiltinLog,             1,  0},
    {"lbound",          wBuiltinLBound,          2,  0},
    {"ltrim",           wBuiltinLTrim,           1,  0},
    {"ltrim$",          wBuiltinLTrim,           1,  0},
    {"mid",             wBuiltinMid,             2,  1},
    {"mid$",            wBuiltinMid,             2,  1},
    {"minute",          wBuiltinMinute,          1,  0},
    {"mkdir",           wBuiltinMkDir,           1,  0},
    {"month",           wBuiltinMonth,           1,  0},
    {"monthname",       wBuiltinMonthName,       1,  0},
    {"monthname$",      wBuiltinMonthName,       1,  0},
    {"notbits",         wBuiltinNotBits,         1,  0},
    {"now",             wBuiltinNow,             0,  0},
    {"orbits",          wBuiltinOrBits,          2,  0},
    {"prepend",         wBuiltinPrepend,         2,  0},
    {"quicksort",       wBuiltinQuickSort,       3,  0},
    {"randomize",       wBuiltinRandomize,       0,  1},
    {"readbyte",        wBuiltinReadByte,        1,  0},
    {"rename",          wBuiltinRename,          2,  0},
    {"repeat",          wBuiltinRepeat,          2,  0},
    {"repeat$",         wBuiltinRepeat,          2,  0},
    {"replace",         wBuiltinReplace,         3,  1},
    {"replace$",        wBuiltinReplace,         3,  1},
    {"reverse",         wBuiltinReverse,         1,  0},
    {"reverse$",        wBuiltinReverse,         1,  0},
    {"rinstrev",        wBuiltinRInstr,          2,  1},
    {"right",           wBuiltinRight,           2,  0},
    {"right$",          wBuiltinRight,           2,  0},
    {"rinstr",          wBuiltinRInstr,          2,  1},
    {"rmdir",           wBuiltinRmDir,           2,  0},
    {"rnd",             wBuiltinRnd,             0,  1},
    {"round",           wBuiltinRound,           1,  0},
    {"rtrim",           wBuiltinRTrim,           1,  0},
    {"rtrim$",          wBuiltinRTrim,           1,  0},
    {"run",             wBuiltinRun,             1,  0},
    {"second",          wBuiltinSecond,          1,  0},
    {"seek",            wBuiltinSeek,            1,  1},
    {"sgn",             wBuiltinSgn,             1,  0},
    {"shell",           wBuiltinShell,           1,  0},
    {"sin",             wBuiltinSin,             1,  0},
    {"slice",           wBuiltinSlice,           3,  0},
    {"space",           wBuiltinSpace,           1,  0},
    {"space$",          wBuiltinSpace,           1,  0},
    {"sqr",             wBuiltinSqr,             1,  0},
    {"sqrt",            wBuiltinSqr,             1,  0},
    {"str",             wBuiltinStr,             1,  0},
    {"str$",            wBuiltinStr,             1,  0},
    {"strf",            wBuiltinStrF,            4,  0},
    {"substr",          wBuiltinSubStr,          3,  0},
    {"tally",           wBuiltinTally,           2,  0},
    {"tan",             wBuiltinTan,             1,  0},
    {"ticks",           wBuiltinTicks,           0,  0},
    {"time",            wBuiltinTime,            0,  0},
    {"tostring",        wBuiltinStr,             1,  0},
    {"tostring$",       wBuiltinStr,             1,  0},
    {"timevalue",       wBuiltinTimeValue,       1,  0},
    {"trace",           wBuiltinTrace,           1,  0},
    {"trim",            wBuiltinTrim,            1,  0},
    {"trim$",           wBuiltinTrim,            1,  0},
    {"typeof",          wBuiltinTypeOf,          1,  0},
    {"ubound",          wBuiltinUBound,          2,  0},
    {"ucase",           wBuiltinUCase,           1,  0},
    {"ucase$",          wBuiltinUCase,           1,  0},
    {"val",             wBuiltinVal,             1,  0},
    {"weekday",         wBuiltinWeekday,         1,  0},
    {"weekdayname",     wBuiltinWeekdayName,     1,  0},
    {"weekdayname$",    wBuiltinWeekdayName,     1,  0},
    {"writebyte",       wBuiltinWriteByte,       2,  0},
    {"xorbits",         wBuiltinXorBits,         2,  0},
    {"year",            wBuiltinYear,            1,  0},
    {NULL,              NULL,               0,  0}
};
                                             
