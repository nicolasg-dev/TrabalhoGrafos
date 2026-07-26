#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "grafo.h"

Grafo* grafo = NULL;

void encerra()
{
    printf("=== Encerrando o programa ===\n");
    //liberar memória usada ao decorrer do programa, talvez
    if (grafo != NULL) freeGrafo(grafo);
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
    printf("--- EXTRAS ---\n");
    printf("10. Detecção de Ciclos (DFS)\n");
    printf("11. Componentes Fortemente Conexos (Kosaraju/Tarjan)\n");
    printf("12. Caminho Crítico (maior distância)\n");

}

void Menu()
{
    printMenu();

    int num = 0;

    scanf("%d", &num);
    getchar();

    switch (num)
    {
    case 1: // Carregar grafo de arquivo
        char nome[100];
        int dir = 0;

        printf("=== Carregar grafo de arquivo ===\n");
        printf("\nDigite o nome do arquivo: ");
        fgets(nome, 100, stdin);
        nome[strcspn(nome, "\n")] = '\0';

        printf("\nO grafo é direcionado (1) ou ñ direcionado (0)?\n");
        scanf("%d", &dir);
        switch(dir)
        {
            case 0:
            grafo = lerArquivo(nome, 0);
            break;

            case 1:
            grafo = lerArquivo(nome, 1);
            break;

            default:
            printf("Entrada inválida!\n");
            Menu();
            break;
        }
        //chama função desejada
        Menu();
        break;

    case 2: // Mostrar grafo
        printf("=== Mostrar grafo (lista de adjacencia) ===\n");
        if (grafo == NULL)
        {
            printf("\nVocê ainda não carregou nenhum arquivo.\n");
            getchar();
        } else
        {
            mostrarGrafo(grafo);
            getchar();
        }

        Menu();
        break;

    case 3: // Busca em profundidade
        if (grafo == NULL)
        {
            printf("\nVocê ainda não carregou nenhum arquivo.\n");
            getchar();
        } else
        {
            printf("=== Busca em Profundidade (DFS) ===\n");
            char tipo[100];
            int ini;
            printf("\nDigite qual DFS você deseja (iterativa) / (recursiva)\n");
            fgets(tipo, 100, stdin);
            tipo[strcspn(tipo, "\n")] = '\0';

            printf("\nVamos começar por qual vértice ?\n");
            scanf("%d", &ini);
            DFS(grafo, tipo, ini);

            getchar();
        }
        Menu();
        break;

    case 4: // Busca em largura
        if (grafo == NULL)
        {
            printf("\nVocê ainda não carregou nenhum arquivo.\n");
            getchar();
        } else
        {
            printf("=== Busca em Largura (BFS) ===\n");
            int distancia[grafo->V];
            int visitado[grafo->V];
            int ini;

            printf("\nVamos começar por qual vértice ?\n");
            scanf("%d", &ini);
            BFS(grafo, ini, visitado, distancia);
            getchar();
        }
        Menu();
        break;

    case 5: // Ordenação topológica
        printf("=== Ordenacao Topologica ===\n");
        //chama função desejada
        Menu();
        break;

    case 6: // Árvore geradora mínima

        if (grafo == NULL)
        {
            printf("\nVocê ainda não carregou nenhum arquivo.\n");
            getchar();
        } else
        {
            printf("=== Arvore Geradora Minima (Prim) ===\n");
            int ini;
            int pais[grafo->V];

            printf("\nVamos começar por qual vértice ?\n");
            scanf("%d", &ini);
            prim(grafo, ini, pais);
            getchar();
        }
        Menu();
        break;

    case 7: // Menor caminho
        if (grafo == NULL)
        {
            printf("\nVocê ainda não carregou nenhum arquivo.\n");
            getchar();
        } else
        {
            int origem, destino;
            printf("=== Menor Caminho (Dijkstra) ===\n");
            printf("\nDigite a origem do algoritmo (vértice de origem)\n");

            scanf("%d", &origem);

            printf("\nDigite o destino do algoritmo (vértice de destino)\n");

            scanf("%d", &destino);
            dijkstra(grafo, origem, destino);
            getchar();
        }

        Menu();
        break;

    case 8: // Estatísticas do grafo
        printf("=== Estatisticas do grafo ===\n");
        //chama função desejada
        Menu();
        break;

    case 9: // Sair
        encerra();
        return;

    case 10: // Detecção de ciclos
        printf("=== Deteccao de Ciclos (DFS) ===\n");
        //chama função desejada
        Menu();
        break;

    case 11: // Componentes fortemente conexos
        printf("=== Componentes Fortemente Conexos (Kosaraju/Tarjan) ===\n");
        //chama função desejada
        Menu();
        break;

    case 12: // Caminho crítico (só com grafos direcionados)
        if (grafo == NULL)
        {
            printf("\nVocê ainda não carregou nenhum arquivo.\n");
            getchar();
        } else
        {
            printf("=== Caminho Critico (maior distancia) ===\n");

            int *duracoes = (int*) malloc(grafo->V * sizeof(int));

            printf("--- Digite a duracao de cada tarefa ---\n");
            for (int i = 0; i < grafo->V; i++) {
                printf("Duracao da Tarefa V%d: ", i);
                scanf("%d", &duracoes[i]);
            }

            caminhoCritico(grafo, duracoes);

            free(duracoes);
            getchar();
        }
        Menu();
        break;

    default:
        printf("Opcao invalida.\n");
        Menu();
        break;
    }
}


int main (void)
{
    Menu();

    return 0;
}
