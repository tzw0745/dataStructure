#ifndef MATCHBRACKETS
#define MATCHBRACKETS

#include "stack_arr.h"

/* match brackets in a string. return 0 if not match */
/* include '(' or ')', '[' or ']', '{' or '}'  */
/* but the ElementType of stack should be 'char' not 'int' */
int matchBrackets( char *str )
{
    Stack s = CreateStack( 100 );
    while( *str ){
        switch( *str ){
            case '(': case '[': case '{':{
                Push( *str, s);
            }break;
            case ')':{
                if( isEmpty(s) || Top( s ) != '(' ){
                    DestroyStack( s );
                    return 0;
                }
                Pop( s );
            }break;
            case ']':{
                if( isEmpty(s) || Top( s ) != '[' ){
                    DestroyStack( s );
                    return 0;
                }
                Pop( s );
            }break;
            case '}':{
                if( isEmpty(s) || Top( s ) != '{' ){
                    DestroyStack( s );
                    return 0;
                }
                Pop( s );
            }break;
        }
        ++str;
    }
    int ans = isEmpty( s );
    DestroyStack( s );
    return ans;
}

#endif
