#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"

void encerra()
{
    printf("=== Encerrando o programa ===\n");
    //liberar memória usada ao decorrer do programa, talvez
}

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

void Menu()
{
    printMenu();

    int num = 0;

    scanf("%d", &num);
    getchar();

    switch (num)
    {
    case 1:
        printf("=== Carregar grafo de arquivo ===\n");
        //chama função desejada
        Menu();
        break;

    case 2:
        printf("=== Mostrar grafo (lista de adjacencia) ===\n");
        //chama função desejada
        Menu();
        break;

    case 3:
        printf("=== Busca em Profundidade (DFS) ===\n");
        //chama função desejada
        Menu();
        break;

    case 4:
        printf("=== Busca em Largura (BFS) ===\n");
        //chama função desejada
        Menu();
        break;

    case 5:
        printf("=== Ordenacao Topologica ===\n");
        //chama função desejada
        Menu();
        break;

    case 6:
        printf("=== Arvore Geradora Minima (Prim) ===\n");
        //chama função desejada
        Menu();
        break;

    case 7:
        printf("=== Menor Caminho (Dijkstra) ===\n");
        //chama função desejada
        Menu();
        break;

    case 8:
        printf("=== Estatisticas do grafo ===\n");
        //chama função desejada
        Menu();
        break;

    case 9:
        encerra();
        return;

    default:
        printf("Opcao invalida.\n");
        Menu();
        break;
    }
}


int main (void)
{

    lerArquivo("grafo1.txt");

    return 0;
}
