%option yylineno
%{
#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <linux/types.h>
#include "fonctions.h"
Program *p;
int yyerror(char *s);
%}

LETTRE 	[A-Za-z]
CHIFFRE 	[0-9]
DIRECTION	("<"|">")
BLANC     (" ")
BATON ("!")


ETAT 	({LETTRE}|{CHIFFRE})+
SYMBOLE  ({LETTRE}|{CHIFFRE}|{BLANC}|{BATON})
OPERATION ({LETTRE}|{CHIFFRE}|{BLANC}|{BATON}|{DIRECTION})
INSTRUCTION	({ETAT}","{SYMBOLE}":"{OPERATION}","{ETAT})
%%
{INSTRUCTION} {
program_tranche(yytext,p);
}
.        printf("\n something else :%s", yytext);
%%
int yyerror(char *s) {
    printf("yyerror : %s\n",s);
    return 0;
}
int main(int argc ,char** argv) {
    if (argc<2) {
      perror("usage :turing programme.tur [STR*]");
     exit (EXIT_SUCCESS);
    }
    p=program_init();
    yyin = fopen(argv[1], "r" );
    yylex() ;
    program_print(p);
    Dlist *bonde;
    printf("\nInitialisation de la bonde:\n");
    bonde=dlist_new();
    if (argc>2) dlist_init(bonde,&argv[2],argc-2);
    dlist_print(bonde);
    turing(bonde,p);




   }
int yywrap(){return(1);}
