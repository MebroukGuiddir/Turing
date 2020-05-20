%option yylineno
%option nounput
%option noinput
%{
#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <linux/types.h>
#include "fonctions.h"
Program *p;
Dlist *bande;
Instruction inst;
int programFlag=0,stepFlag=0,instructionFlag=0,exist;
int yyerror(char *s);
%}
/* lexical analysis */
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
inst=tranche(yytext);
printf("->Inst :  %s\n",yytext);
exist=program_instruction_exist(p,inst);
if(exist==2){
   yyerror("Le programme ne peut contenir plus d'une règle avec le même couple condition (p,s) !");
}
if(exist==1) {
  printf("\033[1;33m\033[1m yywarning : \033[0m line %d - La règle %s existe déja!\n",yylineno,yytext);
}

program_add(inst, p);
}
.       {;}
%%
int yyerror(char *s) {
    printf("\033[1;31m\033[1m yyerror : \033[0m line %d - %s\n",yylineno,s);
    exit (EXIT_FAILURE);
}

int main(int argc ,char** argv) {
 int c;
    if (argc<2) {
   fprintf (stderr, "Usage: %s file.tur [Tape Init]* [-p -s -i]\n-p : view program\n-s : execute the program step by step\n-i : see the instruction executed\n", argv[0]);
    exit (EXIT_FAILURE);
    }
    //**********Initialisation programme*************//
    p=program_init();
    yyin = fopen(argv[1], "r" );

    //parse
    printf("\nProgram parsing :\n");
    yylex() ;






    //********Initialisation de la bande**********//

    bande=dlist_new();
    if (argc>2) dlist_init(bande,&argv[2],argc-2);
   //set flags
    while ((c = getopt (argc, argv, "psi")) != -1)
   switch (c)
    {
    case 'p'://view program
      programFlag = 1;
      break;
    case 's'://execute the program step by step
      stepFlag = 1;
      break;
    case 'i'://see the instruction executed
      instructionFlag = 1;
      break;
    default:               /* '?' */
               fprintf (stderr, "Usage: %s file.tur [Tape Init]* [-p -s -i]\n-p : view program\n-s : execute the program step by step\n-i : see the instruction executed\n", argv[0]);

               exit (EXIT_FAILURE);
    }


    //afficher les instructions
    if(programFlag)  program_print(p);

    // afficher la bonde
    printf("\nInitialisation de la bande:\n");
    dlist_print(bande);

    //*************** execution ****************//
    turing(bande,p);




   }

int yywrap(){return(1);}
