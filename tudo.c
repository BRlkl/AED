#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Data {
    int value;
    char line[100];
};

void insertion_sort(struct Data *vetor, int tamanho) {
    int i, j;
    int comparacao = 0, trocas = 0;
    struct Data aux;
    clock_t inicio = clock();
    for (i = 1; i < tamanho; i++) {
        aux = vetor[i];
        j = i-1;
        comparacao++;
        while (j >= 0 && vetor[j].value > aux.value) {
            vetor[j + 1] = vetor[j];
            j--;
            comparacao++;  
            trocas++;
        }
        vetor[j + 1] = aux;
    }
    clock_t fim = clock();
    double tempo = (fim - inicio) / (double)CLOCKS_PER_SEC;
    printf("\nTempo de execucao: %f segundos", tempo);
    printf("\nNumero de comparacoes: %d", comparacao);
    printf("\nNumero de trocas: %d", trocas);
}

void selection_sort(struct Data *vetor, int tamanho) {
    int i, j, min;
    int comparacao = 0, trocas = 0;
    struct Data aux;
    clock_t inicio = clock();
    for (i = 0; i < tamanho-1; i++) {
        min = i;
        for (j = i+1; j < tamanho; j++) {
            comparacao++;
            if (vetor[j].value < vetor[min].value) {
                min = j;
            }
        }
        if (i != min) {
            aux = vetor[i];
            vetor[i] = vetor[min];
            vetor[min] = aux;
            trocas++;
        }
    }
    clock_t fim = clock();
    double tempo = (fim - inicio) / (double)CLOCKS_PER_SEC;
    printf("\nTempo de execucao: %f segundos", tempo);
    printf("\nNumero de comparacoes: %d", comparacao);
    printf("\nNumero de trocas: %d", trocas);
}

void shell_sort(struct Data *vetor, int tamanho) {
    int i, j;
    int comparacao = 0, trocas = 0;
    int gap = 1;
    struct Data aux;
    clock_t inicio = clock();
    while (gap < tamanho) {
        gap = 3*gap+1;
    }
    while (gap > 1) {
        gap /= 3;
        for (i = gap; i < tamanho; i++) {
            aux = vetor[i];
            for (j = i; j >= gap; j -= gap) {
                comparacao++;
                if (vetor[j - gap].value > aux.value) {
                    vetor[j] = vetor[j - gap];
                    trocas++;
                } 
                else {
                    break;
                }
            }
            vetor[j] = aux;
        }
    }
    clock_t fim = clock();
    double tempo = (fim - inicio) / (double)CLOCKS_PER_SEC;
    printf("\nTempo de execucao: %f segundos", tempo);
    printf("\nNumero de comparacoes: %d", comparacao);
    printf("\nNumero de trocas: %d", trocas);
}

void quick_sort(struct Data *vetor, int esquerda, int direita, int *comparacao, int *trocas) {
    int i, j;
    struct Data pivot, aux;
    i = esquerda;
    j = direita;
    pivot = vetor[(esquerda + direita) / 2];
    while (i <= j) {
        while (vetor[i].value < pivot.value) {
            i++;
            (*comparacao)++;
        }
        while (vetor[j].value > pivot.value) {
            j--;
            (*comparacao)++;
        }
        if (i <= j) {
            (*comparacao)++;
            if (vetor[i].value != vetor[j].value) {
                (*trocas)++;
                aux = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = aux;
            }
            i++;
            j--;
        }
    }
    if (esquerda < j) {
        quick_sort(vetor, esquerda, j, comparacao, trocas);
    }
    if (i < direita) {
        quick_sort(vetor, i, direita, comparacao, trocas);
    }
}

void mergesort(struct Data *vetor, int inicio, int fim, int *comparacoes, int *trocas) {
    int meio;
    if (inicio < fim) {
        meio = (inicio + fim) / 2;
        mergesort(vetor, inicio, meio, comparacoes, trocas);
        mergesort(vetor, meio + 1, fim, comparacoes, trocas);
        int i, j, k;
        int n1 = meio - inicio + 1;
        int n2 = fim - meio;
        struct Data esquerda[n1], direita[n2];
        for (i = 0; i < n1; i++)
            esquerda[i] = vetor[inicio + i];
        for (j = 0; j < n2; j++)
            direita[j] = vetor[meio + 1 + j];
        i = 0;
        j = 0;
        k = inicio;
        while (i < n1 && j < n2) {
            (*comparacoes)++;
            if (esquerda[i].value <= direita[j].value) {
                vetor[k] = esquerda[i];
                i++;
            } else {
                vetor[k] = direita[j];
                j++;
                (*trocas)++;
            }
            k++;
        }
        while (i < n1) {
            vetor[k] = esquerda[i];
            i++;
            k++;
        }
        while (j < n2) {
            vetor[k] = direita[j];
            j++;
            k++;
        }
    }
}

int busca_sequencial(struct Data *vetor, int tamanho, int chave) {
    int i, comparacoes = 0;
    for (i = 0; i < tamanho; i++) {
        comparacoes++;
        if (vetor[i].value == chave) {
            printf("\nNumero de comparacoes: %d\n", comparacoes);
            return i;
        }
    }
    printf("\nNumero de comparacoes: %d\n", comparacoes);
    return -1;
}

int esta_ordenado(struct Data *vetor, int tamanho) {
    int i;
    for (i = 1; i < tamanho; i++) {
        if (vetor[i].value < vetor[i-1].value) {
            return 0;
        }
    }
    return 1;
}

int busca_binaria(struct Data *vetor, int tamanho, int chave) {
    if (!esta_ordenado(vetor, tamanho)) {
        return -2;
    }
    int esq = 0, dir = tamanho - 1, meio, comparacoes = 0;
    while (esq <= dir) {
        meio = (esq + dir) / 2;
        comparacoes++;
        if (vetor[meio].value == chave) {
            printf("\nNumero de comparacoes: %d\n", comparacoes);
            return meio;
        } else if (vetor[meio].value < chave) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    printf("\nNumero de comparacoes: %d\n", comparacoes);
    return -1;
}

int main() {
    char arquivo[100], arquivo_organizado[120], buffer[50], linha[100];
    struct Data *vetor = NULL;
    int tamanho = 0, coluna;
    printf("\nInforme o nome do arquivo csv: ");
    scanf("%s", arquivo);
    printf("\nInforme a coluna que mandará na organização (a partir de 1): ");
    scanf("%d", &coluna);
    coluna--;
    FILE *fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }
    int linha_atual = 0;
    while (fgets(buffer, 50, fp) != NULL) {
        if (linha_atual == 0) {
            linha_atual++;
            continue;
        }
        strcpy(linha, buffer);
        char *token = strtok(buffer, ";");
        for (int i = 0; i < coluna; i++) {
            token = strtok(NULL, ";");
        }
        tamanho++;
        vetor = (struct Data *)realloc(vetor, tamanho * sizeof(struct Data));
        vetor[tamanho - 1].value = atoi(token);
        strcpy(vetor[tamanho-1].line, linha);
        linha_atual++;
    }
    fclose(fp);
    int ordenacao, escolha, busca, id, achou;
    printf("\nEscolha a ação a ser realizada: \nOrdenação (1) \nBusca (2)\n");
    scanf("%d", &escolha);
    if (escolha == 1){
        printf("\nEscolha o algoritmo de classificação: \nInsertion (1) \nSelection (2) \nShell (3)\nQuick (4)\nMerge (5)\n");
        scanf("%d", &ordenacao);
        if (ordenacao == 1){
            insertion_sort(vetor, tamanho);
        }
        else if (ordenacao == 2){
            selection_sort(vetor, tamanho);
        }
        else if (ordenacao == 3){
            shell_sort(vetor, tamanho);
        }
        else if (ordenacao == 4){
            int comparacao = 0;
            int trocas = 0;
            clock_t inicio = clock();
            quick_sort(vetor, 0, tamanho - 1, &comparacao, &trocas);
            clock_t fim = clock();
            double tempo = (fim - inicio) / (double)CLOCKS_PER_SEC;
            printf("\nTempo de execucao: %f segundos", tempo);
            printf("\nNumero de comparacoes: %d", comparacao);
            printf("\nNumero de trocas: %d", trocas);
        }
        else if (ordenacao == 5){
            int comparacao = 0;
            int trocas = 0;
            clock_t inicio = clock();
            mergesort(vetor, 0, tamanho - 1, &comparacao, &trocas);
            clock_t fim = clock();
            double tempo = (fim - inicio) / (double)CLOCKS_PER_SEC;
            printf("\nTempo de execucao: %f segundos", tempo);
            printf("\nNumero de comparacoes: %d", comparacao);
            printf("\nNumero de trocas: %d", trocas);
        }
        else{
            printf("Valor inválido");
        }
        sprintf(arquivo_organizado, "organizado_%s", arquivo);
        FILE *fpo = fopen(arquivo_organizado, "w");
        if (fpo == NULL) {
            printf("Erro ao criar o arquivo organizado.");
            free(vetor);
            return 1;
        }
        for (int i = 0; i < tamanho; i++) {
            fprintf(fpo, "%s", vetor[i].line);
        }
        fclose(fpo);
    }
    else if (escolha == 2){
        printf("\nEscolha o algoritmo de busca: \nSequencial (1) \nBinária (2)\n");
        scanf("%d", &busca);
        printf("\nDigite o ID buscado:\n");
        scanf("%d", &id);
        if (busca == 1){
            achou = busca_sequencial(vetor, tamanho, id);
            if (achou != -1){
                printf("O id %d está na linha %d.", id, achou);
            }
            else{
                printf("O id não foi encontradou.");
            }
        }
        else if (busca == 2){
            achou = busca_binaria(vetor, tamanho, id);
            if (achou == -1){
                printf("O id não foi encontradou");
            }
            else if (achou == -2){
                printf("O vetor não estava organizado. Organize e tente novamente.");
            }
            else {
                printf("O id %d está na linha %d.", id, achou);
            }
        }
        else{
            printf("Valor inválido");
        }
    }
    free(vetor);
    return 0;
}