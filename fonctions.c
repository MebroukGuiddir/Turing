#include "fonctions.h"
extern int stepFlag,instructionFlag;

/**
* initialiser un programme (allouer l'espace mémoire nécessaire)
*@return {Program *} un pointeur de type Program
**/
Program * program_init(){
  Program *p=(Program*)malloc(sizeof(Program));
  p->instructions=NULL;
  p->length=0;
  return p;
}
/**
* ajouter une instruction au programme
*@return {void}
**/
void program_add(Instruction inst, Program *program) {
  program->length++;
  Instruction *temp = (Instruction*)realloc(program->instructions, (program->length * sizeof(Instruction)));

    if (temp == NULL)
    {
        printf("Cannot allocate more memory.\n");

    }
    else
    {
        program->instructions = temp;
        program->instructions[program->length-1]=inst;

    }
}

/**
* trancher la chaine de caractères text en une instruction
*@param {char *} text la chaine de caractères à trancher
*@return {Instruction} instruction
**/
Instruction tranche(char *text) {

	Instruction inst;
	sscanf(text,"%[^,],%c:%c,%s",inst.p,&inst.s, &inst.o, inst.q);
  return inst;

}
/**
* vérifier si une instruction exist dans la liste des instructions (program)
*@param {Program *} program liste des instructions
*@param {Instruction} l'instruction recherchée
*@return {int} 0 si non trouvé , 1 exsit ,2 exist avec le même couple condition (p,s) et non pas le couple (o,q)
**/
int program_instruction_exist(Program *program,Instruction inst){
  int exist=0;
  for (int i = 0; i < program->length; i++) {
   //search instruction
  if(strcmp(inst.p,program->instructions[i].p)==0 && inst.s==program->instructions[i].s)
  { exist++;
  if(strcmp(inst.q,program->instructions[i].q)!=0 || inst.o!=program->instructions[i].o)
  {
    exist++;
  }

   return exist;
  }

}
return 0;
}

/**
* afficher un programme
*@param {Program *} le programme à afficher
*@return {void}
**/
void program_print(Program *program){
  printf("Programme :\n\n");
  for (size_t i = 0; i < program->length; i++) {
    instruction_print(program->instructions[i]);
    printf("\n");
  }
}

/**
*afficher une instruction
*@param {Instruction} instruction
*@return {void}
**/
void instruction_print(Instruction inst){
  printf("\033[1;33m\033[40m %s \033[0m",inst.p) ;
  printf("\033[1;34m\033[40m,\033[0m");
  printf("\033[1;33m\033[40m %c \033[0m",inst.s) ;
  printf("\033[1;34m\033[40m:\033[0m" );
  printf("\033[1;33m\033[40m %c \033[0m",inst.o) ;
  printf("\033[1;34m\033[40m,\033[0m" );
  printf("\033[1;33m\033[40m %s \033[0m",inst.q) ;
  printf("\n");
}

/**
* initialiser la bande (allouer l'espace mémoire nécessaire )
*@return {Dlist *}
**/
Dlist *dlist_new(void)
{
    Dlist *p_new = malloc(sizeof *p_new);
    if (p_new != NULL)
    {
        p_new->length = 0;
        p_new->p_head = NULL;
        p_new->p_first = NULL;
        p_new->p_last = NULL;
    }
    return p_new;
}

/**
* ajouter au debut de la bande
*@param { Dlist * } bande
*@param { char } value caractère à insérer
*@return { void }
**/
void dlist_insert_begin(Dlist * bande,char value){
  struct node *p_new = malloc(sizeof *p_new);
  if (p_new != NULL && bande != NULL )
  {
     if(bande->length != 0)
      { //empty list
        p_new->p_next = bande->p_first;
        p_new->index = (bande->p_first->index) -1;
        bande->p_first->p_prev=p_new;
      }
     else {
       p_new->index = 0;
       p_new->p_next=NULL;
       bande->p_last=p_new;
       bande->p_head=p_new;
     }
       p_new->content=value;
       p_new->p_prev = NULL;
       bande->p_first=p_new;
       bande->length++;
  }


}

/**
* ajouter à la fin de la bande
*@param { Dlist * } bande
*@param { char } value caractère à insérer
*@return { void }
**/
void dlist_insert_end(Dlist * bande,char value){
  struct  node *p_new = malloc(sizeof *p_new);
  if (p_new != NULL && bande != NULL )
  {
     if(bande->length != 0)
      { //empty list
        p_new->p_prev = bande->p_last;
        p_new->index = (bande->p_last->index) +1;
        bande->p_last->p_next=p_new;
      }
     else {
       p_new->index = 0;
       p_new->p_prev=NULL;
       bande->p_first=p_new;
       bande->p_head=p_new;
     }
       p_new->content=value;
       p_new->p_next = NULL;
       bande->p_last=p_new;
       bande->length++;
  }
}

/**
* afficher la bande
*@param { Dlist * } bande
*@return { void }
**/
void dlist_print(Dlist *bande){
  if (bande != NULL)
   {
       struct node *p_temp = bande->p_first;
         printf("\n\n\033[1;33m\033[49m ... \033[0m   ");

       while (p_temp != NULL)
       {
         if(p_temp==bande->p_head)
           printf("\033[1;33m\033[44m %c \033[0m",p_temp->content);
         else
            printf("\033[1;33m\033[40m %c \033[0m",p_temp->content);

             printf("   ");
             fflush(stdout);
             p_temp = p_temp->p_next;
       }
    printf("\033[1;33m\033[49m ... \033[0m\n\n\n");
   }

}
/**
* initialiser la bande
*@param { Dlist * } bande
*@param { char **  } init_bande - un tableau de chaines de caractères
*@param { int } size - la taille du tableau
*@return {void}
**/
void dlist_init(Dlist * bande,char ** init_bande,int size){
  if(init_bande != NULL)
  for (size_t i = 0; i < size; i++) {
    int j=0;
    //skip opt argument
    if(init_bande[i][0]!='-')
    {while (init_bande[i][j]!='\0') {
      //insérer dans la bande
      dlist_insert_end(bande,init_bande[i][j]);
      j++;
    }
    //ajouter un blanc
    if(i<size-1)dlist_insert_end(bande,' ');
   }
  }
}

/**
* executer un programme
*@param { Dlist * } bande
*@param {Program *} program - le programme à executer
*@return {void}
**/
void turing(Dlist * bande,Program *program){
  int execute=1,iteration=0,i;
  char *currentStat=program->instructions[0].p;
  printf("Exécution:\n\n\n");
  while (execute) {
    i=0;
    execute=0;
    for (i = 0; i < program->length; i++) {
     //search instruction
    if(strcmp(currentStat,program->instructions[i].p)==0 && bande->p_head->content==program->instructions[i].s)
    { //effectuer l'operation o
      switch (program->instructions[i].o) {
        //move left
        case '>':{
          if(bande->p_head->p_next==NULL)
          dlist_insert_end(bande,' ');
          bande->p_head=bande->p_head->p_next;break;
        }
        //move right
        case '<':{
          if(bande->p_head->p_prev==NULL)
          dlist_insert_begin(bande,' ');
          bande->p_head=bande->p_head->p_prev;break;
        }
        //write
        default :bande->p_head->content=program->instructions[i].o;
      }
      //changer d'etat
      currentStat=program->instructions[i].q;
      execute=1;
      printf("itération : %d\n\n",iteration );
      //print executed instruction
      if(instructionFlag)  instruction_print(program->instructions[i]);
      dlist_print(bande);
      iteration++;
      //execute step by step
      if(stepFlag)getchar();
    }

    }

  }
}
