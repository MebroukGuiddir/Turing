
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "fonctions.h"


Program * program_init(){
  Program *p=(Program*)malloc(sizeof(Program));
  p->instructions=NULL;
  p->length=0;
  return p;
}
//add instruction to program list
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

void program_tranche(char *text,Program *program) {

	Instruction inst;
	sscanf(text,"%[^,],%c:%c,%s",inst.p,&inst.s, &inst.o, inst.q);
	program_add(inst, program);
}
void program_print(Program *program){
  printf("Programme :\n\n");
  for (size_t i = 0; i < program->length; i++) {
    instruction_print(program->instructions[i]);
    printf("\n");
  }
}
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
**/
void dlist_insert_begin(Dlist * bonde,char value){
  struct node *p_new = malloc(sizeof *p_new);
  if (p_new != NULL && bonde != NULL )
  {
     if(bonde->length != 0)
      { //empty list
        p_new->p_next = bonde->p_first;
        p_new->index = (bonde->p_first->index) -1;
        bonde->p_first->p_prev=p_new;
      }
     else {
       p_new->index = 0;
       p_new->p_next=NULL;
       bonde->p_last=p_new;
       bonde->p_head=p_new;
     }
       p_new->content=value;
       p_new->p_prev = NULL;
       bonde->p_first=p_new;
       bonde->length++;
  }


}
void dlist_insert_end(Dlist * bonde,char value){
  struct  node *p_new = malloc(sizeof *p_new);
  if (p_new != NULL && bonde != NULL )
  {
     if(bonde->length != 0)
      { //empty list
        p_new->p_prev = bonde->p_last;
        p_new->index = (bonde->p_last->index) +1;
        bonde->p_last->p_next=p_new;
      }
     else {
       p_new->index = 0;
       p_new->p_prev=NULL;
       bonde->p_first=p_new;
       bonde->p_head=p_new;
     }
       p_new->content=value;
       p_new->p_next = NULL;
       bonde->p_last=p_new;
       bonde->length++;
  }
}

void dlist_print(Dlist *bonde){
  if (bonde != NULL)
   {
       struct node *p_temp = bonde->p_first;
       while (p_temp != NULL)
       {  printf("\033[1;35m %d \033[0m",p_temp->index);
          printf("\033[s");
          printf("\033[2C");
         if(p_temp==bonde->p_head)
            printf("\033[1;33m\033[44m %c \033[0m",p_temp->content);
         else
            {printf("\033[1;33m\033[40m %c \033[0m",p_temp->content);}

            printf(" ");
            printf("\033[u");
           fflush(stdout);
           p_temp = p_temp->p_next;
       }
    printf("\n\n");
   }

}
void dlist_init(Dlist * bonde,char ** init_bonde,int size){
  if(init_bonde != NULL)
  for (size_t i = 0; i < size; i++) {
    int j=0;
    while (init_bonde[i][j]!='\0') {
      dlist_insert_end(bonde,init_bonde[i][j]);
      j++;
    }
    if(i<size-1)dlist_insert_end(bonde,' ');
  }
}

void turing(Dlist * bonde,Program *program){
  int execute=1,iteration=0,i;
  char *currentStat=program->instructions[0].p;
  printf("Exécution:\n");
  while (execute) {
    i=0;
    execute=0;
    for (i = 0; i < program->length; i++) {
     //search instruction
    if(strcmp(currentStat,program->instructions[i].p)==0 && bonde->p_head->content==program->instructions[i].s)
    { //effectuer l'operation o
      switch (program->instructions[i].o) {
        case '>':{
          if(bonde->p_head->p_next==NULL)
          dlist_insert_end(bonde,' ');
          bonde->p_head=bonde->p_head->p_next;break;
        }
        case '<':{
          if(bonde->p_head->p_prev==NULL)
          dlist_insert_begin(bonde,' ');
          bonde->p_head=bonde->p_head->p_prev;break;
        }
        default :bonde->p_head->content=program->instructions[i].o;
      }
      //changer d'etat
      currentStat=program->instructions[i].q;
      execute=1;
      printf("itération : %d\n",iteration );
      dlist_print(bonde);
      iteration++;
    }

    }

  }
}
