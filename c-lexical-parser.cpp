#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unordered_map>

#define false 0
#define true 1

#define TK_Id 1
#define TK_Void 2                  // void
#define TK_Int 3                   // int
#define TK_Float 4                 // float
#define TK_Comma 5                 // ,
#define TK_Colon 6                 // :
#define TK_Open_Round_Bracket 7    // (
#define TK_Close_Round_Bracket 8   // )
#define TK_Assignment 9            // =
#define TK_Semicolon 10            // ;
#define TK_Open_Curly_Bracket 11   // {
#define TK_Close_Curly_Bracket 12  // }
#define TK_Sum 13                  // +
#define TK_Increment 14            // ++
#define TK_Product 15              // *
#define TK_Char 16                 // char
#define TK_Subtraction 17          // -
#define TK_Open_Square_Bracket 18  // []
#define TK_Close_Square_Bracket 19 // ]
#define TK_Inc_Assignment 20       // +=
#define TK_Double 21               // double
#define TK_Int_Const 22            // Identify integer constant
#define TK_EOF 23                  // End Of File - Identifier
#define TK_Struct 24               // struct
#define TK_If 25                   // if
#define TK_Else 26                 // else
#define TK_Break 27                // break
#define TK_Continue 28             // continue
#define TK_Do 29                   // do
#define TK_For 30                  // for
#define TK_While 31                // while
#define TK_Decrement 32            // --
#define TK_Dec_Assignment 33       // -=
#define TK_Modulus 34              // %
#define TK_Division 35             // /
#define TK_Equal 36                // ==
#define TK_Switch 37               // switch
#define TK_Case 38                 // case
#define TK_Default 39              // default
#define TK_Less 40                 // <
#define TK_Less_Equal 41           // <=
#define TK_Greater 42              // >
#define TK_Greater_Equal 43        // >=
#define TK_Not 44                  // !
#define TK_Not_Equal 45            // !=
#define TK_Struct_Pointer 46       // ->
#define TK_Struct_Atribute 47      // .
#define TK_And 48                  // &&
#define TK_Bitwise_And 49          // &
#define TK_Or 50                   // ||
#define TK_Bitwise_Or 51           // |
#define TK_Shift_Left 52           // <<
#define TK_Shift_Right 53          // >>
#define TK_Bitwise_Exclusive_Or 54 // ^
#define TK_Ones_Complement 55      // ~

char c;
char lex[20];
int line = 0;
int column = 1;
int pos = 0;
int token;
FILE *file;

struct reserved_keyword
{
    char word[20];
    int token;
};

struct reserved_keyword words_list[] = {{"void", TK_Void},
                                        {"int", TK_Int},
                                        {"float", TK_Float},
                                        {"char", TK_Char},
                                        {"double", TK_Double},
                                        {"struct", TK_Struct},
                                        {"if", TK_If},
                                        {"else", TK_Else},
                                        {"break", TK_Break},
                                        {"continue", TK_Continue},
                                        {"do", TK_Do},
                                        {"while", TK_While},
                                        {"for", TK_For},
                                        {"switch", TK_Switch},
                                        {"case", TK_Case},
                                        {"default", TK_Default},
                                        {"end_of_table", TK_Id}};

int reserved_keyword(char lex[])
{
    int postab = 0;
    while (strcmp("end_of_table", words_list[postab].word) != 0)
    {
        if (strcmp(lex, words_list[postab].word) == 0)
            return words_list[postab].token;
        postab++;
    }
    return TK_Id;
}

void next_char()
{
    if (feof(file))
    {
        c = -1;
        return;
    }
    fread(&c, 1, 1, file);
}

void get_token()
{
    int state = 0;
    int end = 0;
    int posl = 0;
    while (!end)
    {
        // printf("Character: %c Line: %d\n", c, pos);
        lex[posl++] = c;
        switch (state)
        {
        case 0:
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_')
            {
                next_char();
                state = 1;
                break;
            }
            if (c >= '0' && c <= '9')
            {
                while (c >= '0' && c <= '9')
                    next_char();
                lex[posl] = '\0';
                token = TK_Int_Const;
                return;
            }
            if (c == '=')
            {
                next_char();
                if (c == '=')
                {
                    lex[posl++] = '=';
                    lex[posl] = '\0';
                    next_char();
                    token = TK_Equal;
                    return;
                }
                else
                {
                    lex[posl] = '\0';
                    next_char();
                    token = TK_Assignment;
                    return;
                }
            }
            if (c == '&')
            {
                next_char();
                if (c == '&')
                {
                    lex[posl++] = '&';
                    lex[posl] = '\0';
                    next_char();
                    token = TK_And;
                    return;
                }
                else
                {
                    lex[posl] = '\0';
                    next_char();
                    token = TK_Bitwise_And;
                    return;
                }
            }
            if (c == '|')
            {
                next_char();
                if (c == '|')
                {
                    lex[posl++] = '|';
                    lex[posl] = '\0';
                    next_char();
                    token = TK_Or;
                    return;
                }
                else
                {
                    lex[posl] = '\0';
                    next_char();
                    token = TK_Bitwise_Or;
                    return;
                }
            }
            if (c == '<')
            {
                next_char();
                if (c == '=')
                {
                    lex[posl++] = '=';
                    lex[posl] = '\0';
                    next_char();
                    token = TK_Less_Equal;
                    return;
                }
                else if (c == '<')
                {
                    lex[posl++] = '<';
                    lex[posl] = '\0';
                    next_char();
                    token = TK_Shift_Left;
                    return;
                }
                else
                {
                    lex[posl] = '\0';
                    next_char();
                    token = TK_Less;
                    return;
                }
            }
            if (c == '>')
            {
                next_char();
                if (c == '=')
                {
                    lex[posl++] = '=';
                    lex[posl] = '\0';
                    next_char();
                    token = TK_Greater_Equal;
                    return;
                }
                else if (c == '>')
                {
                    lex[posl++] = '>';
                    lex[posl] = '\0';
                    next_char();
                    token = TK_Shift_Right;
                    return;
                }
                else
                {
                    lex[posl] = '\0';
                    next_char();
                    token = TK_Greater;
                    return;
                }
            }
            if (c == '!')
            {
                next_char();
                if (c == '=')
                {
                    lex[posl++] = '=';
                    lex[posl] = '\0';
                    next_char();
                    token = TK_Not_Equal;
                    return;
                }
                else
                {
                    lex[posl] = '\0';
                    next_char();
                    token = TK_Not;
                    return;
                }
            }
            if (c == '+')
            {
                next_char();
                if (c == '+')
                {
                    lex[posl++] = '+';
                    lex[posl] = '\0';
                    next_char();
                    token = TK_Increment;
                    return;
                }
                else if (c == '=')
                {
                    lex[posl++] = '=';
                    lex[posl] = '\0';
                    next_char();
                    token = TK_Inc_Assignment;
                    return;
                }
                else
                {
                    lex[posl] = '\0';
                    token = TK_Sum;
                    return;
                }
            }
            if (c == '^')
            {
                lex[posl] = '\0';
                next_char();
                token = TK_Bitwise_Exclusive_Or;
                return;
            }
            if (c == '~')
            {
                lex[posl] = '\0';
                next_char();
                token = TK_Ones_Complement;
                return;
            }
            if (c == '*')
            {
                lex[posl] = '\0';
                next_char();
                token = TK_Product;
                return;
            }
            if (c == '.')
            {
                lex[posl] = '\0';
                next_char();
                token = TK_Struct_Atribute;
                return;
            }
            if (c == '[')
            {
                lex[posl] = '\0';
                next_char();
                token = TK_Open_Square_Bracket;
                return;
            }
            if (c == ']')
            {
                lex[posl] = '\0';
                next_char();
                token = TK_Close_Square_Bracket;
                return;
            }
            if (c == '(')
            {
                lex[posl] = '\0';
                next_char();
                token = TK_Open_Round_Bracket;
                return;
            }
            if (c == ')')
            {
                lex[posl] = '\0';
                next_char();
                token = TK_Close_Round_Bracket;
                return;
            }
            if (c == '{')
            {
                lex[posl] = '\0';
                next_char();
                token = TK_Open_Curly_Bracket;
                return;
            }
            if (c == '}')
            {
                lex[posl] = '\0';
                next_char();
                token = TK_Close_Curly_Bracket;
                return;
            }
            if (c == ',')
            {
                lex[posl] = '\0';
                next_char();
                token = TK_Comma;
                return;
            }
            if (c == ';')
            {
                lex[posl] = '\0';
                next_char();
                token = TK_Semicolon;
                return;
            }
            if (c == ':')
            {
                lex[posl] = '\0';
                next_char();
                token = TK_Colon;
                return;
            }
            if (c == '%')
            {
                lex[posl] = '\0';
                next_char();
                token = TK_Modulus;
                return;
            }
            if (c == '/')
            {
                lex[posl] = '\0';
                next_char();
                token = TK_Division;
                return;
            }
            if (c == '-')
            {
                next_char();
                if (c == '-')
                {
                    lex[posl++] = '-';
                    lex[posl] = '\0';
                    next_char();
                    token = TK_Decrement;
                    return;
                }
                else if (c == '=')
                {
                    lex[posl++] = '=';
                    lex[posl] = '\0';
                    next_char();
                    token = TK_Dec_Assignment;
                    return;
                }
                else if (c == '>')
                {
                    lex[posl++] = '>';
                    lex[posl] = '\0';
                    next_char();
                    token = TK_Struct_Pointer;
                    return;
                }
                else
                {
                    lex[posl] = '\0';
                    token = TK_Subtraction;
                    return;
                }
            }
            if (c == -1)
            {
                lex[posl] = '\0';
                next_char();
                token = TK_EOF;
                return;
            }
            if (c == ' ' || c == '\n' || c == '\t' || c == '\r')
            {
                next_char();
                posl--;
                break;
            }
            if (c == '\0')
            {
                token = -1;
                return;
            }
            printf("Lexical Parser Error: Character %c found in (%d)", c, c);
            while (c != '\n')
                next_char();
            break;
        case 1:
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9')
            {
                next_char();
                break;
            }
            lex[--posl] = '\0';
            token = reserved_keyword(lex);
            return;
        case 2:
            if (c >= '0' && c <= '9')
            {
                lex[pos++] = c;
                next_char();
                break;
            }
            else
            {
                state = 0;
                lex[pos] = '\0';
                token = TK_Int_Const;
                return;
            }
        }
    }
}

int main()
{
    file = fopen("program.c", "rb");
    if (!file)
    {
        printf("Error while opening file.\n");
        return 0;
    }
    next_char(); // Gets the first character of file
    get_token(); // Read the first token
    while (token != TK_EOF)
    {
        printf("%d %s\n", token, lex);
        get_token();
    }
}
