/*************************************************************
    Name:       wdatetime.h
    Purpose:    W_TYPE_DATETIME datatype
	Author:     David Cuny
	Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
	Licence:    LGPL
*************************************************************/

// used by wDateTimePart
enum {
	W_DATETIME_DAY,
	W_DATETIME_DAY_NAME,
	W_DATETIME_WEEKDAY,
	W_DATETIME_WEEKDAY_NAME,
	W_DATETIME_MONTH,
	W_DATETIME_MONTH_NAME,
	W_DATETIME_YEAR,
	W_DATETIME_HOUR,
	W_DATETIME_MINUTE,
	W_DATETIME_SECOND
};

// sorry, no internationalization...
char *wDateTimeLongMonthName[] = {
	"january",
	"february",
	"march",
	"april",
	"may",
	"june",
	"july",
	"august",
	"september",
	"october",
	"november",
	"december"
};

char *wDateTimeShortMonthName[] = {
	"jan",
	"feb",
	"mar",
	"apr",
	"may",
	"jun",
	"jul",
	"aug",
	"sep",
	"oct",
	"nov",
	"dec"
};

void wDateTimeRegisterMethods( void );
void wDateTimeCopy( wVariant *dst, wVariant *src );
int wDateTimeFromChar( wVariant *dst, char *buffer );
char *wDateTimeFormat( char *format, time_t t );
char *wDateTimeToChar( wVariant *src, int useQuotes, int limit );
int wDateTimeCompare( wVariant *v1, wVariant *v2 );
void wDateTimePush( char format, time_t t );

