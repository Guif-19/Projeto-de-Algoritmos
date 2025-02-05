#ifndef CRESCENTE_H_INCLUDED
#define CRESCENTE_H_INCLUDED

#include "base.h"
#include <sys/stat.h>  // Para mkdir no Linux/macOS
#include <direct.h>    // Para _mkdir no Windows

// Função para criar diretórios (compatível com Windows e Linux/macOS)
void criar_diretorios() {
    const char *algoritmos[] = {
        "insertion sort", "bubble sort", "shell sort", 
        "selection sort", "merge sort", "quick sort", "heap sort"
    };

    const char *tipos[] = {"arquivos de entrada", "arquivos de saída", "arquivos de tempo"};
    const char *ordem = "crescente";

    for (int i = 0; i < 7; i++) {
        #ifdef _WIN32
            _mkdir(algoritmos[i]);
        #else
            mkdir(algoritmos[i], 0777);
        #endif

        for (int j = 0; j < 3; j++) {
            char path[150];
            snprintf(path, sizeof(path), "%s/%s", algoritmos[i], tipos[j]);

            #ifdef _WIN32
                _mkdir(path);
            #else
                mkdir(path, 0777);
            #endif

            snprintf(path, sizeof(path), "%s/%s/%s", algoritmos[i], tipos[j], ordem);

            #ifdef _WIN32
                _mkdir(path);
            #else
                mkdir(path, 0777);
            #endif
        }
    }
}

int* gerar_crescente(int n, int algoritmo) {
    const char *algoritmos[] = {
        "insertion sort", "bubble sort", "shell sort", 
        "selection sort", "merge sort", "quick sort", "heap sort"
    };

    // Validação do algoritmo
    if (algoritmo < 1 || algoritmo > 7) {
        printf("Erro: Algoritmo inválido! Escolha um número entre 1 e 7.\n");
        return NULL;
    }

    // Criar diretórios, se ainda não existirem
    criar_diretorios();

    // Alocação de memória para o vetor
    int *vet = (int*)malloc(n * sizeof(int));
    if (!vet) {
        printf("Erro: Falha ao alocar memória para o vetor de %d elementos.\n", n);
        return NULL;
    }

    // Geração dos caminhos para arquivos
    char arq_entrada[150], arq_saida[150], arq_tempo[150];
    snprintf(arq_entrada, sizeof(arq_entrada), "%s/arquivos de entrada/crescente/%d_crescente.txt", algoritmos[algoritmo - 1], n);
    snprintf(arq_saida, sizeof(arq_saida), "%s/arquivos de saída/crescente/%d_ordenado.txt", algoritmos[algoritmo - 1], n);
    snprintf(arq_tempo, sizeof(arq_tempo), "%s/arquivos de tempo/crescente/tempo_crescente_%d.txt", algoritmos[algoritmo - 1], n);

    // Gera os números em ordem crescente e salva no arquivo de entrada
    FILE *entrada = fopen(arq_entrada, "w");
    if (!entrada) {
        printf("Erro ao abrir o arquivo de entrada: %s\n", arq_entrada);
        free(vet);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        vet[i] = i + 1;
        fprintf(entrada, "%d\n", vet[i]);
    }
    fclose(entrada);

    // Marca o início do tempo
    clock_t inicio = clock();

    // Ordena o vetor usando o algoritmo selecionado
    switch (algoritmo) {
        case 1: insertion_sort(vet, n); break;
        case 2: bubble_sort(vet, n); break;
        case 3: shell_sort(vet, n); break;
        case 4: selection_sort(vet, n); break;
        case 5: merge_sort(vet, n); break;
        case 6: quick_sort(vet, 0, n - 1); break;
        case 7: heap_sort(vet, n); break;  
    }

    // Marca o fim do tempo
    clock_t fim = clock();

    // Salva o vetor ordenado no arquivo de saída
    FILE *saida = fopen(arq_saida, "w");
    if (!saida) {
        printf("Erro ao abrir o arquivo de saída: %s\n", arq_saida);
        free(vet);
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        fprintf(saida, "%d\n", vet[i]);
    }
    fclose(saida);

    // Salva e exibe o tempo de execução
    salvar_tempo(inicio, fim, arq_tempo);
    printf("Tempo de execução para ordenação crescente com %d elementos usando %s: %.5lf segundos\n", 
           n, algoritmos[algoritmo - 1], (double)(fim - inicio) / CLOCKS_PER_SEC);

    return vet;
}

#endif // CRESCENTE_H_INCLUDED
