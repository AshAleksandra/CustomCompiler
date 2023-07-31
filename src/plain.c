#include "includes/plain.h"
#include "includes/lex.h"
#include <stdio.h>

void statements()
{
    /*
     * statements  -> expresion SEMI
     *              | expresion SEMI statements
     */
    expressions();
    if (match(SEMI))
    {
        advance();
    }
    else
    {
        fprintf(stderr, "%d: Inserting missing semicolon\n", line);
    }
    if (!match(EOI))
    {
        statements(); /* Do another statements */
    }
}

void expressions()
{
    /* expression -> term expression */
    term();
    expr_prime();
}

void expr_prime()
{
    /* expresson -> PLUS term expression
     *            | epsilon
     */
    if (match(PLUS))
    {
        advance();
        term();
        expr_prime();
    }
}

void term()
{
    /* term -> factor term*/
    factor();
}

void term_prime()
{
    /* expresson -> TIMES factor expression
     *            | epsilon
     */
    if (match(TIMES))
    {
        advance();
        factor();
        term_prime();
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