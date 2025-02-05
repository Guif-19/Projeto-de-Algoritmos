#include "base.h"
#include "crescente.h"
#include "decrescente.h"
#include "random.h"

int main() {
    int op, tam_op;
    char tipo;
    
    while (1) {
        hud();  // Exibe o menu de algoritmos
        if (scanf("%d", &op) != 1) {
            printf("Erro: Entrada inválida. Tente novamente.\n");
            while (getchar() != '\n'); // Limpa o buffer
            continue;
        }

        if (op == 9) { 
            printf("Saindo...\n");
            break;
        } else if (op >= 1 && op <= 8) { 
            menu();
            if (scanf("%d", &tam_op) != 1 || tam_op < 1 || tam_op > 6) {
                printf("Erro: Opção de tamanho inválida. Tente novamente.\n");
                while (getchar() != '\n'); // Limpa o buffer
                continue;
            }

            menu_cdr();
            if (scanf(" %c", &tipo) != 1 || (tipo != 'c' && tipo != 'd' && tipo != 'r')) {
                printf("Erro: Tipo inválido. Escolha 'c', 'd' ou 'r'.\n");
                while (getchar() != '\n'); // Limpa o buffer
                continue;
            }

            int tamanhos[] = {10, 100, 1000, 10000, 100000, 1000000};
            int n = tamanhos[tam_op - 1];
            int *vetor = NULL;

            // Gera a sequência de números
            if (tipo == 'c') {
                vetor = gerar_crescente(n, op);
            } else if (tipo == 'd') {
                vetor = gerar_decrescente(n, op);
            } else {
                vetor = gerar_random(n, op);
            }

            if (!vetor) {
                printf("Erro ao gerar a sequência de números.\n");
                continue;
            }

            // Marca o tempo de início
            clock_t start_t = clock();

            // Chama o algoritmo de ordenação
            switch (op) {
                case 1: insertion_sort(vetor, n); break;
                case 2: bubble_sort(vetor, n); break;
                case 3: shell_sort(vetor, n); break;
                case 4: selection_sort(vetor, n); break;
                case 5: merge_sort(vetor, n); break;
                case 6: quick_sort(vetor, 0, n - 1); break;
                case 7: menu_heap_sort(vetor, n); break;
                case 8: heap_sort(vetor, n); break;  
                default: printf("Erro: Algoritmo inválido.\n"); break;
            }

            // Marca o tempo de término
            clock_t end_t = clock();

            // Define nomes específicos de arquivos para cada algoritmo
            char arquivo_tempo[150], arquivo_saida[150];
            const char *nome_algoritmo = (  op == 1 ? "insertion sort" :
                                            op == 2 ? "bubble sort" :
                                            op == 3 ? "shell sort" :
                                            op == 4 ? "selection sort" :
                                            op == 5 ? "merge sort" :
                                            op == 6 ? "quick sort" :
                                            "heap sort");

            snprintf(arquivo_tempo, sizeof(arquivo_tempo), "%s/arquivos de tempo/%s/tempo_execucao.txt", 
                     nome_algoritmo, tipo == 'c' ? "crescente" : tipo == 'd' ? "decrescente" : "random");
            snprintf(arquivo_saida, sizeof(arquivo_saida), "%s/arquivos de saída/%s/saida_ordenada.txt", 
                     nome_algoritmo, tipo == 'c' ? "crescente" : tipo == 'd' ? "decrescente" : "random");

            // Salva o tempo de execução em um arquivo
            salvar_tempo(start_t, end_t, arquivo_tempo);

            // Salva a sequência ordenada em um arquivo de saída
            salvar_saida(arquivo_saida, vetor, n);

            // Exibe o tempo de execução
            printf("Tempo de execução para %s com %d elementos em ordem %s: %.5lf segundos\n",
                   nome_algoritmo, n, 
                   (tipo == 'c' ? "crescente" : tipo == 'd' ? "decrescente" : "random"),
                   (double)(end_t - start_t) / CLOCKS_PER_SEC);

            // Libera a memória do vetor
            free(vetor);

        } else {
            printf("Erro: Opção inválida. Escolha um número entre 1 e 8.\n");
        }
    }

    return 0;
}
