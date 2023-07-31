#ifndef LEX_H
#define LEX_H

#define EOI         0       /* End of Input */
#define SEMI        1       /* ; */
#define PLUS        2       /* + */
#define TIMES       3       /* * */
#define LP          4       /* ( */
#define RP          5       /* ) */
#define NUM_OR_ID   6       /* Decimal number or identifier */

/*
 * text apunta al actual lexema el cual no es '\0'
*/
extern char *text;

/*
 * len es el numero de caracteres en el lexema
*/
extern int len;

/*
 * line es el numero de lineas de la entrada actual
*/
extern int line;

static int lookahead;

/*
 * Esta funcion usa un simple, y almacenado, sistema de entrada, obtener caracteres una línea a la vez desde la entrada estándar, y luego aislando tokens uno a uno de la linea.
 * @return {int} - Codigo del token
*/
int lex();

int match(int token);

void advance();

#endif