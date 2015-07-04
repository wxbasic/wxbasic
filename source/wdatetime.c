/*************************************************************
    Name:       wdatetime.c
    Purpose:    W_TYPE_DATETIME datatype
	Author:     David Cuny
	Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
	Licence:    LGPL
*************************************************************/

void wDateTimeRegisterMethods()
{
    /* register the routines */
    wTheHandler[W_TYPE_DATETIME]->isNumeric         = W_FALSE;
    wTheHandler[W_TYPE_DATETIME]->ref               = NULL;
    wTheHandler[W_TYPE_DATETIME]->deref             = NULL;
    wTheHandler[W_TYPE_DATETIME]->copy              = wDateTimeCopy;
    wTheHandler[W_TYPE_DATETIME]->clone             = wDateTimeCopy;
    wTheHandler[W_TYPE_DATETIME]->fromNumber        = NULL;
    wTheHandler[W_TYPE_DATETIME]->toNumber          = NULL;
    wTheHandler[W_TYPE_DATETIME]->fromChar          = wDateTimeFromChar;
    wTheHandler[W_TYPE_DATETIME]->toChar            = wDateTimeToChar;
    wTheHandler[W_TYPE_DATETIME]->compare           = wDateTimeCompare;
    wTheHandler[W_TYPE_DATETIME]->equal             = NULL;
    wTheHandler[W_TYPE_DATETIME]->isTrue            = NULL;
    wTheHandler[W_TYPE_DATETIME]->count             = NULL;
    wTheHandler[W_TYPE_DATETIME]->index             = NULL;
    wTheHandler[W_TYPE_DATETIME]->find              = NULL;
    wTheHandler[W_TYPE_DATETIME]->remove            = NULL;
    wTheHandler[W_TYPE_DATETIME]->append            = NULL;
    wTheHandler[W_TYPE_DATETIME]->prepend           = NULL;
    wTheHandler[W_TYPE_DATETIME]->slice             = NULL;
    wTheHandler[W_TYPE_DATETIME]->iterate           = NULL;
}

/* copy data from src to dst */
void wDateTimeCopy( wVariant *dst, wVariant *src )
{
	dst->value.time = src->value.time;
}

/* convert char buffer to datetime */
int wDateTimeFromChar( wVariant *dst, char *buffer )
{
	char c;
	char token[16];
	int at, i, j, n, timeField, len;
    int monthSet, daySet, yearSet, hourSet, minuteSet, secondSet;
	time_t t;
    struct tm   *theTime;

	/* FIXME: I suspect this isn't working correctly... */

    /* move current date into time structure */
    t = time(NULL);
    theTime = localtime(&t);

    /* zap the time */
    theTime->tm_sec = 0;
    theTime->tm_min = 0;
    theTime->tm_hour = 0;

    /* flag nothing has been set */
    monthSet = W_FALSE;
    daySet = W_FALSE;
    yearSet = W_FALSE;
    hourSet = W_FALSE;
    minuteSet = W_FALSE;
    secondSet = W_FALSE;

	/* clear timefield flag */
	timeField = W_FALSE;

    /* scan through the buffer */
    len = strlen( buffer );
	for ( i = 0; i < len; i++ ) {
		c = buffer[i];

        /* number? */
		if (isdigit(c)) {
			/* read while it's a digit */
			n = 0;
			while (isdigit(c)) {
                n = (n*10) + (int)(c - '0');
				i++;
				c = buffer[i];
			}

			/* in a hh:mm:ss field? */
			if (c == ':') {
				timeField = W_TRUE;
			}

			/* hh:mm:ss */
			if (timeField) {
                /* which field hasn't been set yet? */
                if (!hourSet) {
                    theTime->tm_hour = n;
                    hourSet = W_TRUE;

                } else if (!minuteSet) {
                    theTime->tm_min = n;
                    minuteSet = W_TRUE;

				} else {
                    theTime->tm_sec = n;
                    secondSet = W_TRUE;

				}

				/* end of field? */
				timeField = (c == ':');

			/* mm/dd/yy */
			} else {
                /* which field hasn't been set yet? */
                if (!monthSet) {
                    theTime->tm_mon = n-1;
                    monthSet = W_TRUE;
                } else if (!daySet) {
                    theTime->tm_mday = n;
                    daySet = W_TRUE;
                } else if (!yearSet) {
				    /* date is relative to 1900 */
				    if (n < 32) {
				        n += 100;
				    } else if (n < 100){
				        /* leave alone */
                    } else {
				            n -= 1900;
                    }
                    theTime->tm_year = n;
                    yearSet = W_TRUE;
                    
				} else {
					/* error */
					return W_FALSE;
				}

			}

		/* month name, am/pm */
		} else if (isalpha(c)) {

			/* extract the token */
			at = 0;
			while (1) {
			    /* get a character */
				c = tolower( buffer[i] );

                /* end of the token? */			     	
                if (!isalpha(c)) {
                    token[at] = '\0';
				    break;
                }
                
                /* add to the token */
				token[at++] = c;
				
				/* exceeded token size? */
				if (at >= 16) {
					/* error */
					return W_FALSE;
				}
				
				/* move to next char */
				i++;
			}

			if (strcmp( token, "am") == 0 ) {
				/* nothing to do */
			} else if (strcmp( token, "pm") == 0 ) {
                theTime->tm_hour = theTime->tm_hour + 12;

			} else {
				/* check against names of months */
				for ( j = 0; j < 12; j++ ) {
					if (strcmp( token, wDateTimeShortMonthName[j]) == 0
					||  strcmp( token, wDateTimeLongMonthName[j] ) == 0 ) {
						/* dd-month-yy? */
                        if (monthSet) {
                            /* move month value to day */
                            theTime->tm_mday = theTime->tm_mon;
                            daySet = W_TRUE;

                        } else {
                            /* default to the first of the month */
                            theTime->tm_mday = 1;
                        }

						/* set the month an exit loop */
                        theTime->tm_mon = j;
                        monthSet = W_TRUE;
						break;
					}
				}

				/* no match? */
                if (!monthSet) {
					/* error */
					return W_FALSE;
				}
			}
		}

	}

	/* nothing? */
    if (!monthSet && !hourSet) {
		/* error */
		return W_FALSE;
	}

	/* convert with mktime */
    dst->value.time = mktime( theTime );
	if (dst->value.time == -1) {
        return W_FALSE;
     }
     
     /* success */
     return W_TRUE;
}


char *wDateTimeFormat( char *format, time_t t )
{
    struct tm   *theTime;
    char        *buffer;

    /* allocate the buffer */
    buffer = (char *)wMalloc(64);

    /* move into time structure */
     theTime = localtime(&t);

    /* format the time */
    strftime( buffer, 64, format, theTime );

    return buffer;
}


char *wDateTimeToChar( wVariant *src, int useQuotes, int limit )
{
    return wDateTimeFormat( "%A, %B %d, %H:%M:%S", src->value.time );
}



int wDateTimeCompare( wVariant *v1, wVariant *v2 )
{
    /* compare the dates */
	if (v1->value.time == v2->value.time) {
		return 0;
    } else if (v1->value.time < v2->value.time) {
		return -1;
	} else {
		return 1;
	}
}
	

/* push formatted time onto the stack */
void wDateTimePush( char format, time_t t )
{
    int         i;
	struct tm   *tmp;
    char        *buffer;
    wVariant    *variant;

    switch (format) {
    case 'd':
        /* day number */
        tmp = localtime(&t);
        wStackPushNumber( tmp->tm_mday );
        break;

    case 'D':
        /* full day name */
        variant = wStackPushNothing();
        buffer = wDateTimeFormat( "%A", variant->value.time );
        wStringNew( variant, buffer, -1 );
        wFree( buffer );
        break;

    case 'h':
        /* hour number */
        tmp = localtime(&t);
        wStackPushNumber( tmp->tm_hour );
        break;

    case 'm':
        /* month number */
        tmp = localtime(&t);
        wStackPushNumber( tmp->tm_mon+1 );
        break;

    case 'M':
        /* month name */
        variant = wStackPushNothing();
        buffer = wDateTimeFormat( "%B", variant->value.time );
        wStringNew( variant, buffer, -1 );
        wFree( buffer );
        break;

    case 'n':
        /* minute number */
        tmp = localtime(&t);
        wStackPushNumber( tmp->tm_min );
        break;

    case 's':
        /* second number */
        tmp = localtime(&t);
        wStackPushNumber( tmp->tm_sec );
        break;


    case 'w':
        /* weekday number */
        tmp = localtime(&t);
        wStackPushNumber( tmp->tm_wday );
        break;

    case 'W':
        /* weekday name */
        variant = wStackPushNothing();
        buffer = wDateTimeFormat( "%A", variant->value.time );
        wStringNew( variant, buffer, -1 );
        wFree( buffer );
        break;

    case 'y':
        /* year number */
        tmp = localtime(&t);
        wStackPushNumber( tmp->tm_year + 1900 );
        break;

    default:
        wErrorThrow( W_ERROR_CONVERT, "Unknown time format \"%c\" (wDateTimePush)", format );
    }
}

