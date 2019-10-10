#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    ID_TOKEN , PROGRAM_TOKEN,
    NUM_TOKEN,
    CONST_TOKEN, VAR_TOKEN,
    BEGIN_TOKEN, END_TOKEN,
    IF_TOKEN, THEN_TOKEN ,
    WHILE_TOKEN, DO_TOKEN ,
    READ_TOKEN, WRITE_TOKEN,
    PV_TOKEN, PT_TOKEN ,
    PLUS_TOKEN, MOINS_TOKEN ,
    MULT_TOKEN, DIV_TOKEN ,
    VIR_TOKEN, AFF_TOKEN ,
    INF_TOKEN, INFEG_TOKEN ,
    SUP_TOKEN, SUPEG_TOKEN ,
    DIFF_TOKEN, PO_TOKEN ,
    PF_TOKEN,EGAL_TOKEN ,
    EOF_TOKEN, ERREUR_TOKEN
} CODES_LEX ;

void getUniteLexical(CODES_LEX code){

    switch(code){
        case ID_TOKEN : printf("ID_TOKEN \n"); break ;
        case PROGRAM_TOKEN : printf("PROGRAM_TOKEN \n"); break ;
        case NUM_TOKEN : printf("NUM_TOKEN\n"); break ;
        case CONST_TOKEN : printf("CONST_TOKEN \n"); break ;
        case VAR_TOKEN : printf("VAR_TOKEN \n"); break ;
        case BEGIN_TOKEN : printf("BEGIN_TOKEN \n"); break ;
        case END_TOKEN : printf("END_TOKEN \n"); break ;
        case PV_TOKEN : printf("PV_TOKEN \n"); break ;
        case PT_TOKEN : printf("PT_TOKEN \n"); break ;
        case VIR_TOKEN : printf("VIR_TOKEN \n"); break ;
        case PO_TOKEN : printf("PO_TOKEN \n"); break ;
        case PF_TOKEN : printf("PF_TOKEN \n"); break ;
        case EGAL_TOKEN : printf("EGAL_TOKEN \n"); break ;
        case AFF_TOKEN : printf("AFF_TOKEN \n"); break ;
        case ERREUR_TOKEN : printf("ERREUR_TOKEN \n"); break ;
        default : break;

    }

}

typedef struct {
    char lexeme[100];
    CODES_LEX uniteLexicale;
}mot;


mot motRes[5] = {
        { "program", PROGRAM_TOKEN },
        { "const", CONST_TOKEN },
        { "var", VAR_TOKEN },
        { "Begin", BEGIN_TOKEN },
        { "end", END_TOKEN }
};

int nbMotRes = 5;
char lexeme[100] ;
int lonLex ;
FILE *fptr;

int estBlanc(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

int estLettre(char c) {
    return 'A' <= c && c <= 'Z' || 'a' <= c && c <= 'z';
}

int estChiffre(char c) {
    return '0' <= c && c <= '9';
}
void delireCar(char c) {
    ungetc(c, fptr);
}

char lireCar(void) {
    char c = fgetc(fptr) ;

    return c;
}

CODES_LEX uniteSuivante(void) {
    char c;
    c = lireCar();
    while (estBlanc(c))
        c = lireCar();
    if (feof(fptr)) {
        return EOF_TOKEN ;
    }
    if (c == ':') {
        c = lireCar();
        if (c == '=')
            return AFF_TOKEN;
        else {
            delireCar(c);
            return ERREUR_TOKEN;
        }
    }
    else if (estChiffre(c)){
        c = lireCar();
        while ( estChiffre(c)) {
            c = lireCar();
        }
        delireCar(c);
        return NUM_TOKEN ;
    }
    else if (c == '=')
        return EGAL_TOKEN;
    else if (c == ';')
        return PV_TOKEN;
    else if (c == ',')
        return VIR_TOKEN;
    else if (c == '.')
        return PT_TOKEN;
    else if (c == '(')
        return PO_TOKEN;
    else if (c == ')')
        return PF_TOKEN;
    else{
        if (estLettre(c)) {
            lonLex = 0;
            lexeme[lonLex] = c;
            lonLex++;
            c = lireCar();
            while (estLettre(c) || estChiffre(c)) {
                lexeme[lonLex++] = c;
                c = lireCar();
            }
            delireCar(c);
            lexeme[lonLex] = '\0';
            int i;
            for (i = 0; i < nbMotRes; i++)
            {

                if (strcmp(lexeme, motRes[i].lexeme) == 0){

                    return motRes[i].uniteLexicale;
                }


            }
            return ID_TOKEN;
        }
        else {

            return ERREUR_TOKEN;
        }
    }}


int main(int argc, char *argv[]) {

    if ((fptr = fopen("dic", "r")) == NULL)
    {
        printf("Error! Ouveture fichier");
        exit(1);
    }

    do
    {
        CODES_LEX  cl = uniteSuivante() ;
        getUniteLexical(cl);
        if (feof(fptr)) {
            printf("EOF_TOKEN \n");
            break;
        }
    }  while(1);

    fclose(fptr);

    system("pause") ;
    return 0;
}
