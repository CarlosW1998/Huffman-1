#include<stdio.h>
#include<stdlib.h>

typedef struct _tree Tree;

struct _tree{
    int repear;
    unsigned char c;
    Tree *next;
    Tree *left;
    Tree *right;
};

//FUNÇÕES AUXILIARES
Tree* creating_nodes (unsigned char c)
{
	Tree *h_tree = (Tree *)malloc(sizeof(Tree));
	h_tree->c = c;
	h_tree->left = NULL;
	h_tree->right = NULL;
	return h_tree;
}
//FUNÇÃO PRINCIPAL
Tree* re_building_huffman_tree (FILE *arquivo)
{
    int cond = 1;
    unsigned char i;

    fscanf(arquivo, "%c", &i);
    printf("%c", i);

    if(i != '*')
    {
        cond = 0;
    }
    if(i == '\\')
    {
        fscanf(arquivo, "%c", &i);
        printf("%c", i);
        cond = 0;
    }
    Tree *h_tree = creating_nodes(i);
    if(cond)
    {
        h_tree->left = re_building_huffman_tree(arquivo);
        h_tree->right = re_building_huffman_tree(arquivo);
    }

	return h_tree;
}

//----------------------------TRASFORMAR STRING EM ARVORE DE HUFFMAN--------------------------------------//
void escreve_ai_tiu(Tree *root, FILE *entrada, FILE *saida, int lixo)
{
    Tree *aux = root;
    unsigned char character, aux1;
    int i;
    fscanf(entrada, "%c", &character);
    aux1 = character;
    while(fscanf(entrada, "%c", &character) != EOF)
    {
        for(i = 7; i >= 0; i--)
        {
            if(aux->left == NULL && aux->right == NULL)
            {
                fprintf(saida,"%c",aux->c);
                aux = root;
            }
            if(aux1 & 1<<i)
                aux = aux->right;
            else
                aux = aux->left;
        }
        aux1 = character;
    }
    for(i = 7; lixo <= 8; lixo++, i--)
    {
        if(aux->left == NULL && aux->right == NULL)
        {
            fprintf(saida,"%c",aux->c);
            aux = root;
        }
        if(aux1 & 1<<i)
            aux = aux->right;
        else
            aux = aux->left;
    }
    return ;
}
void testando_a_arvore_de_boas(Tree *root)
{
    if(root == NULL)
        return ;
    printf("%c", root->c);
    testando_a_arvore_de_boas(root->left);
    testando_a_arvore_de_boas(root->right);
}

int main()
{
    char nome_entrada[100], nome_saida[100];
    unsigned char aux, *arvore;
    int lixo, tam_tree = 0, i;
    Tree *root = NULL;
    FILE *arquivo_compacto, *arquivo_sem_pacto;

    printf("O nome do arquivo:\n");
    scanf("%[^\n]s", nome_entrada);
    getchar();
    printf("O nome do arquivo de saida:\n");
    scanf("%[^\n]s", nome_saida);
    getchar();

    arquivo_compacto = fopen(nome_entrada, "rb");

    if(arquivo_compacto == NULL)
        printf("NOOO\n");
    else
        printf("BUUIIAAA\n");

    fscanf(arquivo_compacto, "%c", &aux);
    printf("|%d|", aux);
    //pega o lixo, os 3 primeiros bits
    lixo = aux>>5;

    //printf("%d\n", lixo); ignora saporraqui

    //elimina o lixo e pega o que ta na arvore no primeiro bity
    tam_tree = aux & 0b00011111;
    tam_tree = tam_tree<<8;

    fscanf(arquivo_compacto, "%c", &aux);
    printf("|%d|", aux);

    //pega o que ta no segundo bite;

    tam_tree = tam_tree | aux;

    printf("%d %d\n", tam_tree, lixo);
    arvore = (unsigned char*) malloc((sizeof(unsigned char)*tam_tree));
    //for(i = 0; i < tam_tree; i++)
    //{
        //fscanf(arquivo_compacto, "%c", &arvore[i]);
    //}
    root = re_building_huffman_tree(arquivo_compacto);
    arquivo_sem_pacto = fopen(nome_saida, "wb");
    //testando_a_arvore_de_boas(root);
    escreve_ai_tiu(root, arquivo_compacto, arquivo_sem_pacto, lixo);
    fclose(arquivo_sem_pacto);

    return 0;
}
