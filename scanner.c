#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"

TokenType Token;
int Num;
char Id[MAX_IDENT_LEN + 1];

FILE *f;
char ch;

TokenType checkKeyword(char *str)
{
    int i;
    for (i = 0; i < 15; ++i)
    {
        if (strcmp(keywords[i], str) == 0)
        {
            return keywords[i];
        }
    }
    return IDENT;
}

char getCh()
{
    return fgetc(f);
}

TokenType getToken()
{
    while (ch == ' ' || ch == '\n') ch = getCh();
    if (isalpha(ch))
    {
        int l = 0;
        do
        {
            Id[l++] = ch;
            ch = getCh();
        } while (isalpha(ch));
        Id[l] = '\0';
        return checkKeyword(Id);
    }
    else if (isdigit(ch))
    {
        Num = ch - 48;
        do
        {
            ch = getCh();
            Num = Num * 10 + ch - 48;
        } while (isdigit(ch));
        return NUMBER;
    }
    else if (ch == ':')
    {
        if (ch == '=') return ASSIGN;
        return NONE;
    }
    else if (ch == '+') return PLUS;
    else if (ch == '-') return MINUS;
    else if (ch == '*') return TIMES;
    else if (ch == '/') return SLASH;
    else if (ch == '<')
    {
        if (ch == '>') return NEQ;
        else if (ch == '=') return LEQ;
        else return LSS;
    }
    else if (ch == '>')
    {
        if (ch == '=') return GEQ;
        return GTR;
    }
    else if (ch == ',') return COMMA;
    else if (ch == '.') return PERIOD;
    else if (ch == '[') return LBRACK;
    else if (ch == ']') return RBRACK;
    else if (ch == '%') return PERCENT;
    else if (ch == '(') return LPARENT;
    else if (ch == ';') return SEMICOLON;

    return NONE;
}

void compile(char *filename)
{
    if ((f = fopen(filename, "rt")) == NULL)
        printf("File %s not found", filename);
    else
    {
        ch = ' ';
        do
        {
            Token = getToken();
            printf(" %s", TabToken[Token]);
            if (Token == IDENT)
                printf("(%s) \n", Id);
            else if (Token == NUMBER)
                printf("(%d) \n", Num);
            else
                printf("\n");
        } while (Token != NONE);
    }
    fclose(f);
}
