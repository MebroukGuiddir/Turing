
//*********** structures *****************//
struct node
{
    int index;
    char content;
    struct node *p_next;
    struct node *p_prev;
};

typedef struct dlist
{
    size_t length;
    struct node *p_first;
    struct node *p_last;
    struct node *p_head;
} Dlist;
//structure to store instructions
typedef struct Instruction {
        char p[10];
        char s;
        char o;
        char q[10];
} Instruction;
// Program structure contain list of instructions
typedef struct Program {
  Instruction *instructions;
  int length;
} Program;

//***********prototypes *****************//
Program * program_init();
void program_add(Instruction inst, Program *program);
void program_tranche(char *text,Program *program);
void program_print(Program *program);
void instruction_print(Instruction inst);
Dlist *dlist_new(void);
void dlist_insert_begin(Dlist * bonde,char value);
void dlist_insert_end(Dlist * bonde,char value);
void dlist_print(Dlist *bonde);
void dlist_init(Dlist * bonde,char ** init_bonde,int size);
void turing(Dlist * bonde,Program *program);
