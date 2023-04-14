#ifndef extern_
 #define extern_ extern
#endif

#include <stdio.h>

struct Token{
    int token;
    int int_value;
};

extern_ int Line;
extern_ int Putback;
extern_ FILE *Infile;
extern_ FILE *Outfile;
extern_ struct Token token;