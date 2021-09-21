#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int valor;
    int visitado;
    struct lista *lista_adj;
} vertice;

typedef struct lista
{
    int qtd;
    struct registro *inicio;
} lista;

typedef struct registro
{
    int valor;
    struct registro *prox;
} registro;

void mostrar_lista(lista *l);
int incluir_ordenado_lista(lista *l, int x);
void dfs(vertice *vertices, int x);
    registro *aloca_registro();
lista *aloca_lista();

int main()
{
    vertice *vertices;
    int qtd_vertices;
    int opcao;
    int contador = 0;
    int a, b;
    int i;

    scanf("%d", &qtd_vertices);

    vertices = (vertice *)calloc(qtd_vertices + 1, sizeof(vertice));

    for (int j = 0; j <= qtd_vertices/2; j++)
    {
        a = 0;
        b = 0;

        scanf("%d", &a);

        scanf("%d", &b);

        //printf("\n passei %d", j);

        if (vertices[a].lista_adj == NULL)
            vertices[a].lista_adj = aloca_lista();
        incluir_ordenado_lista(vertices[a].lista_adj, b);

        if (vertices[b].lista_adj == NULL)
            vertices[b].lista_adj = aloca_lista();
        incluir_ordenado_lista(vertices[b].lista_adj, a);
    }

    // for (i = 1; i <= qtd_vertices; i++)
    // {
    //     printf("\n\nVertice %d ", i);
    //     mostrar_lista(vertices[i].lista_adj);
    // }


    for(i = 1; i <= qtd_vertices; i++){
        if(vertices[i].visitado == 0){
            dfs(vertices, i);
            contador++;
        }
    }
    printf("\n %d", contador);
    

    printf("\n");
    return 0;
}

lista *aloca_lista()
{
    lista *novo;
    novo = (lista *)calloc(1, sizeof(lista));
    return novo;
}

registro *aloca_registro()
{
    registro *novo;
    novo = (registro *)calloc(1, sizeof(registro));
    return novo;
}

int incluir_ordenado_lista(lista *l, int x)
{
    if (l == NULL)
        return 0;

    registro *novo, *aux = NULL, *ant = NULL;
    novo = aloca_registro();
    novo->valor = x;

    if (l->inicio == NULL)
    {
        l->inicio = novo;
    }
    else
    {
        int inserido = 0;
        aux = l->inicio;
        while (aux != NULL && !inserido)
        {

            if (aux->valor == novo->valor)
            {
                return 0;
            }

            if (aux->valor < novo->valor)
            {
                ant = aux;
                aux = aux->prox;
            }
            else
            {
                if (ant == NULL)
                    l->inicio = novo;
                else
                    ant->prox = novo;

                novo->prox = aux;
                inserido = 1;
            }
        }
        if (!inserido)
        {
            ant->prox = novo;
            inserido = 1;
        }
    }
    l->qtd++;
    return 1;
}

void mostrar_lista(lista *l)
{
    registro *aux;

    if (l == NULL)
    {
        printf("\n Lista nula");
        return;
    }

    if (l->inicio == NULL)
    {
        printf("\n Lista vazia");
        return;
    }

    aux = l->inicio;
    while (aux != NULL)
    {
        printf("\n -> %d", aux->valor);
        aux = aux->prox;
    }
}

void dfs(vertice *vertices, int x)
{
    registro *aux;
    vertices[x].visitado = 1;
    // printf(" %d", x);

    if (vertices[x].lista_adj == NULL)
        return;

    aux = vertices[x].lista_adj->inicio;

    while (aux != NULL)
    {
        if (vertices[aux->valor].visitado == 0)
        {
            dfs(vertices, aux->valor);
        }
        aux = aux->prox;
    }
}