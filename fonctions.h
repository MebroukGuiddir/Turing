#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
//*********** structures *****************//
//structure to store each node of the tape
struct node
{
    int index; //node index
    char content; //node content
    struct node *p_next;//next node
    struct node *p_prev;// previous node
};
//structure of the tape
typedef struct dlist
{
    size_t length; // tape size
    struct node *p_first;// points the first element of the tape
    struct node *p_last; // points the last element of the tape
    struct node *p_head; // points the head of the band
} Dlist;
//structure to store instructions
typedef struct Instruction {
        char p[10]; // state in
        char s; // symbole
        char o; //operation
        char q[10]; // state out
} Instruction;
// Program structure contain the list of instructions
typedef struct Program {

  Instruction *instructions; //instructions list
  int length;//program size
} Program;

//***********prototypes *****************//
/**
* initialiser un programme (allouer l'espace mémoire nécessaire)
*@return {Program *} un pointeur de type Program
**/
Program * program_init();
/**
* ajouter une instruction au programme
*@return {void}
**/
void program_add(Instruction inst, Program *program);
/**
* trancher la chaine de caractères text en une instruction
*@param {char *} text la chaine de caractères à trancher
*@return {Instruction} instruction
**/
Instruction tranche(char *text);
/**
* afficher le programme
*@param {Program *} le programme à afficher
*@return {void}
**/
void program_print(Program *program);
/**
* vérifier si une instruction exist dans la liste des instructions (program)
*@param {Program *} program liste des instructions
*@param {Instruction} l'instruction recherchée
*@return {int} 0 si non trouvé , 1 exsit ,2 exist avec le même couple condition (p,s) et non pas le couple (o,q)
**/
int program_instruction_exist(Program *program,Instruction inst);
/**
*afficher une instruction
*@param {Instruction} instruction
*@return {void}
**/
void instruction_print(Instruction inst);
/**
* initialiser la bande (allouer l'espace mémoire nécessaire )
*@return {Dlist *}
**/
Dlist *dlist_new(void);
/**
* ajouter au debut de la bande
*@param { Dlist * } bande
*@param { char } value caractère à insérer
*@return { void }
**/
void dlist_insert_begin(Dlist * bande,char value);
/**
* ajouter à la fin de la bande
*@param { Dlist * } bande
*@param { char } value caractère à insérer
*@return { void }
**/
void dlist_insert_end(Dlist * bande,char value);
/**
* afficher la bande
*@param { Dlist * } bande
*@return { void }
**/
void dlist_print(Dlist *bande);
/**
* initialiser la bande
*@param { Dlist * } bande
*@param { char **  } init_bande - un tableau de chaines de caractères
*@param { int } size - la taille du tableau
*@return {void}
**/
void dlist_init(Dlist * bande,char ** init_bande,int size);
/**
* executer un programme
*@param { Dlist * } bande
*@param {Program *} program - le programme à executer
*@return {void}
**/
void turing(Dlist * bande,Program *program);
