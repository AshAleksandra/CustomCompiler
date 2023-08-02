#include "includes/lex.h"
#include <stdio.h>
#include <stdbool.h>  
#include <ctype.h>

char *text = "";        /* Lexema (excluyendo terminales '\0') */
int len = 0;            /* Longitud del lexema */
int line = 0;           /* Numero de lineas de la entrada */
static int lookahead = -1;

int lex(){
    static char input_buffer[128];
    char *current;
    current = text + len;   /* Skip current lexeme */
    while (1)
    {
        while (!*current)
        {
            /* Get new lines, skipping any leading white space on the line until a nonblank line is found. 
            */
            current = input_buffer;
            if (!gets(input_buffer))
            {
                *current = '\0';
                return EOI;
            }
            ++line;
            while (isspace(*current))
            {
                ++current;
            }
        }
        for ( ; *current ; ++current)
        {
            /* Get the next token */
            text = current;
            len = 1;

            switch (*current)
            {
                case EOF: return EOI;
                case ';': return SEMI;
                case '+': return PLUS;
                case '*': return TIMES;
                case '(': return LP;
                case ')': return RP;
                case '\n':
                case '\t':
                case ' ': break;
                default:
                    if (!isalnum(*current))
                    {
                        fprintf(stderr, "Ignoring illegal input <%c>\n", *current);
                    }
                    else
                    {
                        while (isalnum(*current))
                        {
                            ++current;
                        }
                        len = current - text;
                        return NUM_OR_ID;
                    }
                    break;
            }
        }
    }
}

int match(int token){
    /* Return true if "token" matches the current lookahead symbol */
    if (lookahead == -1)
    {
        lookahead = lex();
    }
    return token == lookahead;
}

void advance(){
    /* Advance the lookahead to the next input symbol */
    lookahead = lex();
}