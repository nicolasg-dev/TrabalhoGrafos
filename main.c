#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
void printMenu()
{
    printf("=== SISTEMA DE GRAFOS ===\n");
    printf("1. Carregar grafo de arquivo\n");
    printf("2. Mostrar grafo (lista de adjacência)\n");
    printf("3. Busca em Profundidade (DFS)\n");
    printf("4. Busca em Largura (BFS)\n");
    printf("5. Ordenação Topológica\n");
    printf("6. Árvore Geradora Mínima (Prim)\n");
    printf("7. Menor Caminho (Dijkstra)\n");
    printf("8. Estatísticas do grafo\n");
    printf("9. Sair\n");

}

int main (void)
{
    void printMenu();
    printMenu();

    int num = 0;

    scanf("%d", &num);

    switch (num)
    {
    case 1:
        printf("Carregar grafo de arquivo.\n");
        break;

    case 2:
        printf("Mostrar grafo (lista de adjacencia).\n");
        break;

    case 3:
        printf("Busca em Profundidade (DFS).\n");
        break;

    case 4:
        printf("Busca em Largura (BFS).\n");
        break;

    case 5:
        printf("Ordenacao Topologica.\n");
        break;

    case 6:
        printf("Arvore Geradora Minima (Prim).\n");
        break;

    case 7:
        printf("Menor Caminho (Dijkstra).\n");
        break;

    case 8:
        printf("Estatisticas do grafo.\n");
        break;

    case 9:
        printf("Encerrando o programa.\n");
        break;

    default:
        printf("Opcao invalida.\n");
        break;

    }
    main
    return 0;
}
