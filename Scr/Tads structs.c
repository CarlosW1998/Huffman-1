//Guarda a frequencia de repetição, caracter e nós para os filhos
typedef struct _tree Tree;
//Guarda um no para a arvore, e para o proximo queue
typedef struct _queue  queue;
//Guarda o inicio da fila de prioridade
typedef struct _deck deck;

struct _tree
{
    int repear;
    unsigned char chracter;
    Tree *left;
    Tree *right;
};
struct _queue
{
    Tree *node;
    queue *next;
};
struct _deck
{
    queue *head;
};

