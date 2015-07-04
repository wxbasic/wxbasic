/*************************************************************
	Name:       call.c
	Purpose:    support for calling user defined routines
	Author:     David Cuny
	Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
	Licence:    LGPL
*************************************************************/


void wCallInit()
{
	/* set up the call stack */
	wTheCallStack = wGrowNew( 128 );

	/* set up the catch stack */
	wTheCatchStack = wGrowNew( 8 );

	/* the current call */
	wTheCall = NULL;
	wTheGlobal = NULL;

}

/* call a routine */
void wCallRoutine( wSymbol *sRoutine, int parmCount, int returnCount, wObject *o, wVariant *v )
{

    int i, diff, bytes, tos, totalCount, reqCount, optCount, extraCount;
	wVariant *src, *dst;
    wCall *priorCall;

	/* don't wMemTest here, it could be NULL */

    /* check for runaway recursion */
    if (wGrowCount( wTheCallStack ) > wTheMaxCallDepth) {
		/* error */
        wErrorThrow( W_ERROR_INTERNAL, "Maximum call depth of %d exceeded.",
            wTheMaxCallDepth );
    }

	/* push prior call onto the stack */
	wGrowAppend( wTheCallStack, (int)wTheCall );

    /* check args */
    wParseCheckArgCount( sRoutine, parmCount );

    /* size of call */
    bytes = sizeof( wCall );

    /* default number of locals */
    totalCount = 0;

    if (sRoutine->type == W_SYM_BUILTIN) {
        /* don't adjust size; things stay on the stack */

    } else {

        // FIXME: this is a mess. Can it be placed in a seperate routine?

        /* first time calling? */
        if (sRoutine->called == 0) {
            sRoutine->called = 1;
        } else {
            /* FIXME: declare this a double, so it won't overflow */
            /* don't count, because it could cause an overflow error */
            sRoutine->called = 2;
        }

        /* count of all locals, excluding "extras" */
        if (sRoutine->children == NULL) {
            /* don't need to allocate locals */
            totalCount = 0;
        } else {
            wMemTest( sRoutine->children, "wCallRoutine:sRoutine->children" );
            totalCount = sRoutine->children->count;
        }
    
        /* required args */
        reqCount = parmCount;
    
        /* optional args follow the required args */
        if (reqCount > sRoutine->args) {
            /* anything over the required amount is optional */
            optCount = parmCount - sRoutine->args;
            reqCount = sRoutine->args;
        } else {
            optCount = 0;
        }
    
        /* extra args follow the optional args */
        if (optCount > sRoutine->optArgs) {
            /* anything over the optional amount is extra */
            extraCount = optCount - sRoutine->optArgs;
            optCount = sRoutine->optArgs;
    
            /* add to the totalCount */
            totalCount += extraCount;
    
        } else {
            extraCount = 0;
        }
    
        /* need to allocate space for the locals? */    
        if (totalCount > 1) {
            bytes += (sizeof( wVariant ) * (totalCount-1));
        }

    }
	
	/* allocate the call and set values */
	wTheCall = (wCall *)wMalloc( bytes );
	wTheCall->parmCount = parmCount;
	wTheCall->returnCount = returnCount;
    wTheCall->routine = sRoutine;
	wTheCall->sourceLine = 0;
    wTheCall->self = o;
    wTheCall->vSelf = v;
	wTheCall->localCount = totalCount;

	/* FIXME: this should be more elegant */
	if (wTheGlobal == NULL) {
		wTheGlobal = wTheCall;
	}

	/* user defined or builtin? */
    if (sRoutine->type == W_SYM_BUILTIN ) {
		/* get the top of stack, less the parameters */
		tos = wTheStack->count - parmCount;

        /* if there's an error, use the error line of the caller */
        if (wGrowCount(wTheCallStack)) {
            priorCall = (wCall *)(wGrowPeek( wTheCallStack, 0 ));
            wTheCall->sourceLine = priorCall->sourceLine;
        }

		/* call to builtin */        
        (*sRoutine->builtin)();
		
    } else if ( sRoutine->type == W_SYM_FUNCTION
           ||   sRoutine->type == W_SYM_SUB ) {
        /* initialize all the locals */
        for ( i = 0; i < totalCount; i++ ) {
            /* set the type and typeCast to nothing */
            wTheCall->local[i].dataType = W_TYPE_NOTHING;
            wTheCall->local[i].typeCast = W_TYPE_VARIANT;
        }

        /* copy "extra" parameters from the stack */
        for ( i = 1; i <= extraCount; i++ ) {
            dst = &(wTheCall->local[totalCount-i]);
            wMemTest( dst, "wCallRoutine:dst (extra)" );
            wVariantMove( dst, wStackPop() );
        }

        /* copy "optional" parameters from the stack */
        for ( i = optCount; i > 0; i-- ) {
            dst = &(wTheCall->local[reqCount+i-1]);
            wMemTest( dst, "wCallRoutine:dst (optional)" );
            wVariantMove( dst, wStackPop() );
        }

        /* copy "required" parameters from the stack */
        for ( i = reqCount; i > 0; i-- ) {
            dst = &(wTheCall->local[i-1]);
            wMemTest( dst, "wCallRoutine:dst (required)" );
            wVariantMove( dst, wStackPop() );
        }

		/* get the stack count */
		tos = wTheStack->count;

		/* call to user defined routine */
        wVmExecute( sRoutine );

		/* clean up locals */
        for ( i = 0; i < totalCount; i++ ) {
            wVariantDeref( &(wTheCall->local[i]) );
		}
	
	} else {
		/* error */
		wErrorThrow( W_ERROR_NOTCODE, "Can't execute %s %s (wCallRoutine)",
            sRoutine->name, wSymbolName[sRoutine->type] );
	}


//wConsolePrintf("returned from %s with %d items on the stack\n", sRoutine->name, wTheStack->count );
	/* compare item count with expected item count */
	diff = wTheStack->count - tos;    

	/* more items than expected, drop some */
	if (diff > returnCount) {
//wConsolePrintf("popping off %d extra\n", diff-returnCount );
		/* pop extra items off the stack */
        wStackDropExtra( diff-returnCount );        

	/* less items that expected, push some undefined */
	} else if (diff < returnCount) {
//wConsolePrintf("pushing %d extra\n", returnCount-diff );
		/* push undefineds onto stack */
		for ( ; diff < returnCount; diff++ ) {
            wStackPushNothing();
		}
	}

	/* release the call */
	wFree( wTheCall );

	/* restore the prior call */
	wTheCall = (wCall *)(wGrowPop( wTheCallStack ));

}

/* called on error to restore depth of call stack */
void wCallRestoreStack( int depth )
{
    int i;

    /* clear off any frames on the call stack */
    while (wGrowCount( wTheCallStack ) > depth ) {
        
		/* clean up locals */
        for ( i = 0; i < wTheCall->localCount; i++ ) {
            wVariantDeref( &(wTheCall->local[i]) );
		}

        /* release the call */
        wFree( wTheCall );
        
        /* make the prior call current */
		wTheCall = (wCall *)(wGrowPop( wTheCallStack ));
    }
}

/* concat trace information to the buffer */
char *wCallConcatTrace( char *buffer, int unroll, int showLocals )
{
    int         i, j, count, index;
    char        *tmpBuffer;
	wGrow       *children;
	wSource     *source;
	wSymbol     *routine, *child;
	wVariant    *variant;
    wCall       *priorCall;

    /* shouldn't happen */
    if (wTheCall == NULL) {
        return buffer;
    }

    /* save the current call */
    priorCall = wTheCall;

	/* depth of call stack */
    wMemTest( wTheCall, "wCallTrace:wTheCall (1)" );
	count = wTheCallStack->count;

    /* walk the call stack backwards */
    for ( i = -1 ; i < count-1; i++ ) {
        if (i != -1) {
            /* don't walk stack? */
            if (!unroll) {
                /* leave the loop */
                break;
            }

            /* peek at stack */
            wTheCall = (wCall *)(wGrowPeek( wTheCallStack, i ));
            wMemTest( wTheCall, "wCallTrace:wTheCall (2)" );
		}

        /* get the source line? */
        if (wTheCall->sourceLine == 0) {
            /* no trace code triggered */
            source = NULL;

        } else {
            source = wSourceGet( wTheCall->sourceLine );
            wMemTest( source, "wCallTrace:source" );
        }

		/* print routine name? */
		if (wTheCall->routine->index == wTheGlobalScope) {
            /* not in a routine */
            if (source != NULL) {
                /* display source information */
                buffer = wCharConcat( buffer, "In file \"" );
                buffer = wCharConcat( buffer, source->fileName );
                buffer = wCharConcat( buffer, "\", line " );
                buffer = wCharConcatInt( buffer, source->lineNum );
                buffer = wCharConcat( buffer, ":\n" );
            }
		} else {
			/* routine name */
            if (source == NULL) {
                /* name of routine only */
                buffer = wCharConcat( buffer, "In " );
                buffer = wCharConcat( buffer, wTheCall->routine->name );
                buffer = wCharConcat( buffer, "()\n" );
            } else {
                /* routine name, file name and  and line number */
                buffer = wCharConcat( buffer, wTheCall->routine->name );
                buffer = wCharConcat( buffer, "() in file \"" );
                buffer = wCharConcat( buffer, source->fileName );
                buffer = wCharConcat( buffer, "\", line " );
                buffer = wCharConcatInt( buffer, source->lineNum );
                buffer = wCharConcat( buffer, ":\n" );
            }
		}

        /* can add line? */
        if (source != NULL) {
            wMemTest( source->text, "wCallTrace:source->text" );
            buffer = wCharConcat( buffer, "> " );
            buffer = wCharConcat( buffer, source->text );
        }

		/* print the variables */
		children = wTheCall->routine->children;
        if (children != NULL && showLocals) {
			wMemTest( children, "wCallTrace:children" );
			for ( j = 1; j <= children->count; j++ ) {
				/* get a child */
				child = wSymbolGetChild( wTheCall->routine, j );
				wMemTest( child, "wCallTrace:child" );

				/* hide? */
				if (child->name[0] != '_') {
                    /* concat name */
                    buffer = wCharConcat( buffer, " " );
                    buffer = wCharConcat( buffer, child->name );
                    buffer = wCharConcat( buffer, " = " );

					/* is it an alias for a global? */
					if (child->alias) {
						/* get global variable */
                        variant = wVmGetVariable( -child->alias );
					} else {
						/* get local variable */
                        variant = wVmGetVariable( j );
					}
                    /* concat value */
                    tmpBuffer = wVariantToChar( variant, W_TRUE, 32 );
                    buffer = wCharConcat( buffer, tmpBuffer );
                    wFree( tmpBuffer );

                    buffer = wCharConcat( buffer, "\n" );
				}
			}
            buffer = wCharConcat( buffer, "\n" );
		}
	}
    /* restore the current call */
    wTheCall = priorCall;

    return buffer;
}

