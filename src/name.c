#include "includes/name.h"
#include "includes/lex.h"
#include <stdio.h>
#include <stdlib.h>

char *Names[] = {"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9"};
char **Namep = Names;

char *newname()
{
    if (Namep >= &Names[sizeof(Names)/sizeof(*Namep)])
    {
        fprintf(stderr, "%d: Expression too complex\n", line);
        exit(1);
    }
    printf("Newname: %s \n", *Namep++);
    return(*Namep++);
}

void freename(char *s)
{
    if (Namep > Names)
    {
        *--Namep = s;
    }
    else
    {
        fprintf(stderr, "%d: (Internal error) Name stack underflow\n",line ); 
    }
}