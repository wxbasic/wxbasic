#include <stdio.h>
#include "sqlite\sqlite3.h"
#include "sqlite\sqliteInt.h"


#include "sqlite/alter.c"
#include "sqlite/analyze.c"
#include "sqlite/attach.c"
#include "sqlite/auth.c"
#include "sqlite/btree.c"
#include "sqlite/build.c"
#include "sqlite/callback.c"
#include "sqlite/complete.c"
#include "sqlite/date.c"
#include "sqlite/delete.c"
#include "sqlite/expr.c"
#include "sqlite/func.c"
#include "sqlite/hash.c"
#include "sqlite/insert.c"
#include "sqlite/legacy.c"
#include "sqlite/main.c"
/* #include "sqlite/opcodes.c" */
#include "sqlite/os.c"
//#include "sqlite/os_unix.c"
//#include "sqlite/os_win.c"
#include "sqlite/pager.c"
#include "sqlite/parse.c"
#include "sqlite/pragma.c"
#include "sqlite/prepare.c"
#include "sqlite/printf.c"
#include "sqlite/random.c"
#include "sqlite/select.c"
#include "sqlite/shell.c"
#include "sqlite/table.c"
//#include "sqlite/tokenize.c"
#include "sqlite/trigger.c"
#include "sqlite/update.c"
#include "sqlite/utf.c"
#include "sqlite/util.c"
#include "sqlite/vacuum.c"
#include "sqlite/vdbeapi.c"
#include "sqlite/vdbeaux.c"
#include "sqlite/vdbe.c"
#include "sqlite/vdbefifo.c"
#include "sqlite/vdbemem.c"
#include "sqlite/where.c"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main(int argc, char **argv){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    if( argc!=3 ){
        fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
        exit(1);
    }
    rc = sqlite3_open(argv[1], &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);
    if( rc!=SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }
    sqlite3_close(db);
    return 0;
}
