#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef int bool;
typedef int TIPOPESO;

typedef struct adjacencia {
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice {
    ADJACENCIA *cab;
} VERTICE;

typedef struct grafo {
    int vertices;
    int arestas;
    VERTICE *adj;
} GRAFO;

GRAFO *criarGrafo(int v) {
    int i;

    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (VERTICE *)malloc(v * sizeof(VERTICE));

    for (i = 0; i < v; i++) {
        g->adj[i].cab = NULL;
    }
    return g;
}

ADJACENCIA *criaAdj(int v, int peso) {
    ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    temp->vertice = v;
    temp->peso = peso;
    temp->prox = NULL;
    return temp;
}

bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p) {
    if (!gr) return false;
    if ((vf < 0) || (vf >= gr->vertices)) return false;
    if ((vi < 0) || (vi >= gr->vertices)) return false;

    ADJACENCIA *novo = criaAdj(vf, p);
    novo->prox = gr->adj[vi].cab;
    gr->adj[vi].cab = novo;
    gr->arestas++;
    return true;
}

void imprime(GRAFO *gr) {
    printf("Vertices: %d. Arestas: %d.\n", gr->vertices, gr->arestas);

    for (int i = 0; i < gr->vertices; i++) {
        printf("v%d: ", i);
        ADJACENCIA *ad = gr->adj[i].cab;
        while (ad) {
            printf("v%d(%d) ", ad->vertice, ad->peso);
            ad = ad->prox;
        }
        printf("\n");
    }
}

int main() {
    // Grafo não direcionado e ponderado
    GRAFO *grafo1 = criarGrafo(5);
    criaAresta(grafo1, 0, 1, 2);
    criaAresta(grafo1, 1, 2, 4);
    criaAresta(grafo1, 2, 0, 12);
    criaAresta(grafo1, 2, 4, 40);
    criaAresta(grafo1, 3, 1, 3);
    criaAresta(grafo1, 4, 3, 8);

    printf("Grafo 1 (Nao direcionado e ponderado):\n");
    imprime(grafo1);

    // Grafo orientado e ponderado
    GRAFO *grafo2 = criarGrafo(6);
    criaAresta(grafo2, 0, 1, 1);
    criaAresta(grafo2, 1, 3, 3);
    criaAresta(grafo2, 3, 2, 2);
    criaAresta(grafo2, 3, 4, 4);
    criaAresta(grafo2, 2, 4, 5);
    criaAresta(grafo2, 2, 5, 6);
    criaAresta(grafo2, 4, 5, 9);
    
    printf("\nGrafo 2 (Orientado e ponderado):\n");
    imprime(grafo2);

    // Calculando o valor total do caminho de {1, 5} em grafo2
    int caminho[] = {1, 5};
    int valorTotalCaminho = 0;

    for (int i = 0; i < sizeof(caminho) / sizeof(caminho[0]) - 1; i++) {
        int v1 = caminho[i];
        int v2 = caminho[i + 1];
        ADJACENCIA *ad = grafo2->adj[v1].cab;

        while (ad) {
            if (ad->vertice == v2) {
                valorTotalCaminho += ad->peso;
                break;
            }
            ad = ad->prox;
        }
    }

    printf("\nValor total do caminho de {1, 5} em grafo2: %d\n", valorTotalCaminho);

    return 0;
}
