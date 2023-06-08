#include "data.h"
#include "defs.h"


static int chrpos(char * s, int c){
    char * p;

    p = strchr(s,c);
    //s points to char[0] and p points char [>0] so you get the 
    return (p ? p - s: - 1 );
}

static int next(void){
    int c;

    if(Putback) {
        c = Putback;
        Putback = 0;
        return c;
    }

    c = fgetc(Infile);
    if('\n' == c){
        Line++;
    }
    return c;

}

static void putback(int c){
    Putback = c;
}


static int skip(void){

    int c;

    c = next();

    while (c == ' ' || c == ' \t' || c == '\n' || c == '\r' || c == '\f'){
        c = next();
    }
    return c;
}

static int scanint(int c){
    int k, val = 0;
    
    while((k = chrpos("0123456789", c)) >= 0){
        val = val * 10 + k;
        c = next();
    }
    putback(c);

    return val;
}

static int scan_ident(int c, char *buf, int lim)
{
    int i = 0;
    while(isalpha(c) || isdigit(c) || '_' == c)
    {
        if(i < lim - 1){
            buf[i++] = c;
            c = next();
        }else{
            printf("identifier too long on line %d\n", Line);
            exit(1);
        }

    }
    putback(c);
    buf[i] = '\0';
    return i;
}


static int keyword(char * s)
{
    switch (*s)
    {
    case ('p'):
        printf("KEYWORD %s\n", s);
        printf("strcmp result: %d\n", strcmp(s, "print"));
        if(!strcmp(s, "print"))
            return T_PRINT;
        break;
    case ('m'):
        if(!strcmp(s, "measure"))
            return T_MEASURE;
        break;
    }
    return 0;

}


int scan(struct Token *t)
{
    int c, tokentype;

    c = skip();

    switch(c)
    {
        case EOF:
            t->token = T_EOF;
            return (0);
        case '+':
            t->token = T_PLUS;
            break;
        case  '-':
            t->token = T_MINUS;
            break;
        case '*':
            t->token = T_STAR;
            break;
        case '/':
            t->token = T_SLASH;
            break;
        case ';':
            t->token = T_SEMI;
            break;
        default:
            if(isdigit(c)){
                t->int_value = scanint(c);
                t->token = T_INTLIT;
                break;
            }else if(isalpha(c) || '_' == c){
                int ident_len = scan_ident(c,Text, 50);
                tokentype = keyword(Text);
                printf("KEYWORD RESULT:  %d\n", tokentype);
                if(tokentype == 7){
                    printf("TOKENTYPE RECOGNIZED\n");
                    t->token = tokentype;
                }else{
                    // Not a recognised keyword, so an error for now
                    printf("Unrecognised symbol %s on line %d\n", Text, Line);
                    exit(1);
                }
                    

            }

    }

    return 1;
}


