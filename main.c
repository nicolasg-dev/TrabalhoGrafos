#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "grafo.h"

Grafo* grafo = NULL;
void menuExtra();
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
    printf("9. EXTRAS\n");
    printf("10. Sair\n");
}

void printExtra()
{
    printf("=== SISTEMA DE GRAFOS ===\n");
    printf("1. Detecção de Ciclos (DFS)\n");
    printf("2. Componentes Fortemente Conexos (Kosaraju/Tarjan)\n");
    printf("3. Caminho Crítico (maior distância)\n");
    printf("4. Testes dos 1000s vertices.\n");
    printf("5. Retornar para o menu principal.\n");
    printf("6. Sair\n");
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
        printf("grafo1.txt (Grafo não-direcionado simples)\n");
        printf("grafo2.txt (DAG para ordenação topológica)\n");
        printf("grafo3.txt (Grafo com ciclo)\n");
        printf("grafo4.txt (Grafo ponderado para Dijkstra)\n");
        printf("grafo5.txt (Teste Kosaraju)\n");
        printf("\nDigite o nome do arquivo: ");
        fgets(nome, 100, stdin);
        nome[strcspn(nome, "\n")] = '\0';

        printf("\nO grafo é direcionado (1) ou ñ direcionado (0)?\n");
        scanf("%d", &dir);
        switch(dir)
        {
            case 0:
            grafo = lerArquivo(nome, 0);
            grafo->direcionado = 0;
            break;

            case 1:
            grafo = lerArquivo(nome, 1);
            grafo->direcionado = 1;
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
        if (grafo == NULL)
        {
            printf("\nVocê ainda não carregou nenhum arquivo.\n");
            getchar();
        } else
        {
            ordenacaoTopologica(grafo);
            getchar();
        }
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
        if (grafo == NULL)
        {
            printf("\nVocê ainda não carregou nenhum arquivo.\n");
            getchar();
        } else
        {
            printf("=== Estatisticas do grafo ===\n");
            Estatisticas(grafo);
            getchar();
        }
        Menu();
        break;

    case 9:
        menuExtra();
        break;

    case 10: // Sair
        encerra();
        return;

    default:
        printf("Opcao invalida.\n");
        Menu();
        break;
    }
}

void menuExtra()
{
    printExtra();

    int num = 0;

    scanf("%d", &num);
    getchar();

    switch (num)
    {
    case 1: // Detecção de ciclos
        printf("=== Deteccao de Ciclos (DFS) ===\n");
        if (grafo == NULL)
        {
            printf("\nVocê ainda não carregou nenhum arquivo.\n");
            getchar();
        } else
        {
            if (temCiclo(grafo))
            {
                printf("\nO grafo possui ciclos.\n\n");
            } else
            {
                printf("\nO grafo ñ possui ciclos.\n\n");
            }
        }

        Menu();
        break;

    case 2: // Componentes fortemente conexos
        if (grafo == NULL)
        {
            printf("\nVocê ainda não carregou nenhum arquivo.\n");
            getchar();
        } else
        {
            printf("=== Componentes Fortemente Conexos (Kosaraju) ===\n\n");
            Kosaraju(grafo);
            getchar();
        }
        Menu();
        break;

    case 3: // Caminho crítico (só com grafos direcionados)
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

    case 4: // Caminho crítico (só com grafos direcionados)
        int d = 0;
        printf("\nOs grafos sao direcionados (1) ou ñ direcionados (0)?\n");
        scanf("%d", &d);
        testeMilVertices(d);
        getchar();

        Menu();
        break;

    case 5: // Menu
        Menu();
        break;

    case 6: // Sair
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
    Menu();

    return 0;
}
