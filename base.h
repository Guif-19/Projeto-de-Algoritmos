#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <direct.h>  

// Funções do Menu
void hud() {
    printf("--------- ALGORITMOS ---------\n");
    printf("1 - Insertion Sort\n");
    printf("2 - Bubble Sort\n");
    printf("3 - Shell Sort\n");
    printf("4 - Selection Sort\n");
    printf("5 - Merge Sort\n");
    printf("6 - Quick Sort\n");
    printf("7 - Heap Sort\n");
    printf("8 - Menu do Heap Sort\n");
    printf("9 - Sair\n");
    printf("Escolha uma opção: ");
}

void menu() {
    printf("Escolha a quantidade de números:\n");
    printf("1 -> 10\n2 -> 100\n3 -> 1.000\n4 -> 10.000\n5 -> 100.000\n6 -> 1.000.000\n");
}

void menu_cdr() {
    printf("Escolha o tipo de entrada:\n");
    printf("'c' - Crescente\n'd' - Decrescente\n'r' - Randômica\n");
}

// Função Insertion Sort
void insertion_sort(int vet[], int size) {
    for (int j = 1; j < size; j++) {
        int chave = vet[j];
        int i = j - 1;

        while (i >= 0 && vet[i] > chave) {
            vet[i + 1] = vet[i];
            i--;
        }
        vet[i + 1] = chave;
    }
}

// Função Bubble Sort
void bubble_sort(int vet[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (vet[j] > vet[j + 1]) {
                int temp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = temp;
            }
        }
    }
}

// Função Shell Sort
void shell_sort(int *vet, int size) {
    int h = 1;
    while (h < size) h = 3 * h + 1;

    while (h > 0) {
        for (int i = h; i < size; i++) {
            int value = vet[i];
            int j = i;
            while (j > h - 1 && value < vet[j - h]) {
                vet[j] = vet[j - h];
                j -= h;
            }
            vet[j] = value;
        }
        h /= 3;
    }
}

// Função Selection Sort
void selection_sort(int num[], int tam) { 
    for (int i = 0; i < (tam - 1); i++) {
        int min = i;
        for (int j = (i + 1); j < tam; j++) {
            if (num[j] < num[min]) {
                min = j;
            }
        }
        if (i != min) {
            int aux = num[i];
            num[i] = num[min];
            num[min] = aux;
        }
    }
}


// Função Merge Sort
void merge(int vet[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = vet[left + i];
    for (int j = 0; j < n2; j++) R[j] = vet[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) vet[k++] = L[i++];
        else vet[k++] = R[j++];
    }

    while (i < n1) vet[k++] = L[i++];
    while (j < n2) vet[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort_rec(int vet[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_rec(vet, left, mid);
        merge_sort_rec(vet, mid + 1, right);
        merge(vet, left, mid, right);}
}

void merge_sort(int vet[], int size) {
    merge_sort_rec(vet, 0, size - 1);
    }



// Função Quick Sort com particionamento pela mediana
int particiona_mediana(int vet[], int p, int r) {
    int mediana = (p + r) / 2;
    int valores[] = {vet[p], vet[mediana], vet[r]};
    int pivoMediana;

    // Determina o índice do pivô com base na mediana
    if ((valores[0] <= valores[1] && valores[1] <= valores[2]) || (valores[2] <= valores[1] && valores[1] <= valores[0]))
        pivoMediana = mediana;
    else if ((valores[1] <= valores[0] && valores[0] <= valores[2]) || (valores[2] <= valores[0] && valores[0] <= valores[1]))
        pivoMediana = p;
    else
        pivoMediana = r;

    // Troca o pivô com o último elemento
    int troca = vet[pivoMediana];
    vet[pivoMediana] = vet[r];
    vet[r] = troca;

    int pivoReal = vet[r];
    int i = p - 1;

    for (int j = p; j <= r - 1; j++) {
        if (vet[j] <= pivoReal) {
            i++;
            troca = vet[i];
            vet[i] = vet[j];
            vet[j] = troca;
        }
    }

    troca = vet[r];
    vet[r] = vet[i + 1];
    vet[i + 1] = troca;

    return i + 1;
}

void quick_sort(int vet[], int p, int r) {
    if (p < r) {
        int posPivo = particiona_mediana(vet, p, r);
        quick_sort(vet, p, posPivo - 1);
        quick_sort(vet, posPivo + 1, r);
    }
}

// Função para trocar dois elementos
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função MIN_HEAPIFY
void min_heapify(int *vet, int i, int n) {
    int menor = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < n && vet[esquerda] < vet[menor]) {
        menor = esquerda;
    }
    if (direita < n && vet[direita] < vet[menor]) {
        menor = direita;
    }

    if (menor != i) {
        swap(&vet[i], &vet[menor]);
        min_heapify(vet, menor, n);
    }
}

// Função BUILD_MIN_HEAP
void build_min_heap(int *vet, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        min_heapify(vet, i, n);
    }
}

// Função HEAP_MINIMUM
int heap_minimum(int *vet) {
    return vet[0]; // O menor elemento está na raiz
}

// Função HEAP_EXTRACT_MIN
int heap_extract_min(int *vet, int *n) {
    if (*n <= 0) {
        printf("Heap vazio!\n");
        return -1;
    }

    int min = vet[0]; // Salva o menor elemento
    vet[0] = vet[*n - 1]; // Move o último elemento para a raiz
    (*n)--; // Reduz o tamanho do heap
    min_heapify(vet, 0, *n); // Restaura a propriedade do heap

    return min;
}

// Função HEAP_INCREASE_KEY
void heap_increase_key(int *vet, int i, int chave) {
    if (chave < vet[i]) {
        printf("Erro: Nova chave é menor que a atual!\n");
        return;
    }

    vet[i] = chave; // Atualiza a chave
    while (i > 0 && vet[(i - 1) / 2] > vet[i]) { // Restaura a propriedade do heap
        swap(&vet[i], &vet[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Função MAX_HEAP_INSERT
void max_heap_insert(int *vet, int *n, int chave) {
    (*n)++; // Aumenta o tamanho do heap
    vet[*n - 1] = chave; // Insere a chave no final
    heap_increase_key(vet, *n - 1, chave); // Restaura a propriedade do heap
}

// Função para gerar vetor randômico
void gerar_vetor_aleatorio(int *vet, int tamanho) {
    srand(time(NULL));
    for (int i = 0; i < tamanho; i++) {
        vet[i] = rand() % 1000 + 1;
    }
}

// Função para gerar vetor crescente
void gerar_vetor_crescente(int *vet, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vet[i] = i + 1;
    }
}

// Função para gerar vetor decrescente
void gerar_vetor_decrescente(int *vet, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vet[i] = tamanho - i;
    }
}

// Função para imprimir o vetor
void imprimir_vetor(int *vet, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

// Função HEAPSORT
void heap_sort(int *vet, int n) {
    build_min_heap(vet, n); // Constrói o heap mínimo

    for (int i = n - 1; i > 0; i--) {
        swap(&vet[0], &vet[i]); // Move a raiz (menor elemento) para o final
        min_heapify(vet, 0, i); // Restaura a propriedade do heap
    }
}

// Menu principal
void menu_heap_sort() {
    int opcao;
    int n;
    int *vet;

    while (1) {
        printf("\n--- MENU HEAP SORT ---\n");
        printf("1 - HEAP_MINIMUM\n");
        printf("2 - HEAP_EXTRACT_MIN\n");
        printf("3 - HEAP_INCREASE_KEY\n");
        printf("4 - MAX_HEAP_INSERT\n");
        printf("5 - SAIR\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 5) {
            printf("Saindo do menu Heap Sort...\n");
            break;
        }

        printf("Digite o tamanho do vetor: ");
        scanf("%d", &n);
        vet = (int *)malloc(n * sizeof(int));
        if (!vet) {
            printf("Erro ao alocar memória.\n");
            continue;
        }

        printf("Digite os elementos do vetor:\n");
        for (int i = 0; i < n; i++) {
            scanf("%d", &vet[i]);
        }

        build_min_heap(vet, n);
        printf("Heap mínimo criado:\n");
        imprimir_vetor(vet, n);

        switch (opcao) {
            case 1: {
                printf("Menor elemento (raiz do heap): %d\n", heap_minimum(vet));
                break;
            }
            case 2: {
                int min = heap_extract_min(vet, &n);
                printf("Menor elemento extraído: %d\n", min);
                printf("Heap após extração:\n");
                imprimir_vetor(vet, n);
                break;
            }
            case 3: {
                int pos;
                printf("Digite a posição para aumentar a chave: ");
                scanf("%d", &pos);
                heap_increase_key(vet, pos, 1000);
                printf("Heap após aumento da chave:\n");
                imprimir_vetor(vet, n);
                break;
            }
            case 4: {
                max_heap_insert(vet, &n, 1000);
                printf("Heap após inserção do elemento 1000:\n");
                imprimir_vetor(vet, n);
                break;
            }
            default:
                printf("Opção inválida!\n");
        }

        free(vet);
    }
}
// Função para calcular e salvar o tempo de execução em arquivo
void salvar_tempo(clock_t inicio, clock_t fim, const char *nome_arquivo) {
    double tempo_exec = (double)(fim - inicio) / CLOCKS_PER_SEC;
    FILE *arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de tempo: %s\n", nome_arquivo);
        return;
    }

    fprintf(arquivo, "Tempo de execução: %.5lf segundos\n", tempo_exec);
    printf("Tempo de execução salvo em: %s\n", nome_arquivo);
    fclose(arquivo);
}

// Função para salvar a sequência ordenada em um arquivo
void salvar_saida(const char *nome_arquivo, int *vetor, int tamanho) {
    FILE *arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de saída: %s\n", nome_arquivo);
        return;
    }

    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d\n", vetor[i]);
    }
    printf("Arquivo de saída salvo em: %s\n", nome_arquivo);
    fclose(arquivo);
}

#endif // BASE_H_INCLUDED
