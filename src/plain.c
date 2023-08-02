#include "includes/plain.h"
#include "includes/lex.h"
#include <stdio.h>

void statements()
{
    /*
     * statements  -> expresion SEMI
     *              | expresion SEMI statements
     */
    while (match(SEMI))
    {
        expressions();
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

void expressions()
{
    /* expression -> term expression */
    term();
    while (match(PLUS))
    {
        advance();
        term();
    }
}

void term()
{
    /* term -> factor term*/
    factor();
    while (match(TIMES))
    {
        advance();
        factor();
    }
}

void factor()
{
    /* factor -> NUM_OR_ID
     *         | LP expression RP
     */
    if (match(NUM_OR_ID))
    {
        advance();
    }
    else if (match(LP))
    {
        advance();
        expressions();
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
