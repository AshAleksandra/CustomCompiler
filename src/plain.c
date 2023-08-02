#include "includes/plain.h"
#include "includes/lex.h"
#include "includes/name.h"
#include <stdio.h>

void statements()
{
    /*
     * statements  -> expresion SEMI
     *              | expresion SEMI statements
     */
    char *tempvar;
    while (!match(EOI))
    {
        expressions(tempvar = newname());
        freename(tempvar);
        if (match(SEMI))
        {
            advance();
        }
        else
        {
            fprintf(stderr, "%d: Inserting missing semicolon\n", line);
        }
    }
}

void expressions(char *tempvar)
{
    /* expression -> term expression */
    char *tempvar2;
    term(tempvar);
    while (match(PLUS))
    {
        advance();
        term(tempvar2 = newname());
        printf(" %s += %s \n", tempvar, tempvar2);
        freename(tempvar2);
    }
}

void term(char *tempvar)
{
    /* term -> factor term*/
    char *tempvar2;
    factor(tempvar);
    while (match(TIMES))
    {
        advance();
        factor(tempvar2 = newname());
        printf(" %s += %s \n", tempvar, tempvar2);
        freename(tempvar2);
    }
}

void factor(char *tempvar)
{
    /* factor -> NUM_OR_ID
     *         | LP expression RP
     */
    if (match(NUM_OR_ID))
    {
        printf(" %s = %0.*s\n", tempvar, len, text);
        advance();
    }
    else if (match(LP))
    {
        advance();
        expressions(tempvar);
        if (match(RP))
        {
            advance();
        }
        else
        {
            fprintf(stderr, "%d: Mismatched parenthesis\n", line);
        }
    }
    else
    {
        fprintf(stderr, "%d: Number or identifier expected\n", line);
    }
}
