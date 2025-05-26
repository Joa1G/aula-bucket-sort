#include <stdio.h>
#include <stdlib.h>

#define QTD_BUCKETS 10

// Função auxiliar: Insertion Sort (para ordenar os baldes)
void insertionSort(float vetor[], int tamanho)
{

    for (int i = 1; i < tamanho; i++)
    {
        float chave = vetor[i];
        int j = i - 1;

        while (j >= 0 && vetor[j] > chave)
        {
            vetor[j + 1] = vetor[j];
            j--;
        }

        vetor[j + 1] = chave;
    }
}

// Função principal do Bucket Sort
void bucketSort(float vetor[], int tamanho_vetor)
{
    // Criar os buckets (baldes)
    float *baldes[QTD_BUCKETS];       // inicializa um array de ponteiros float de 10 posições
    int contagem_baldes[QTD_BUCKETS]; // cria um array de inteiros de 10 posições

    // Inicializar os baldes
    for (int i = 0; i < QTD_BUCKETS; i++)
    {                                                               // irá rodar de 0..9
        baldes[i] = (float *)malloc(tamanho_vetor * sizeof(float)); // cada ponteiro desse array de ponteiros vai alocar memória para um array do tamanho do que foi passado como
                                                                    // argumento da função.
        contagem_baldes[i] = 0;
    }

    // Distribuir os elementos nos baldes
    for (int i = 0; i < tamanho_vetor; i++)
    {
        int indice = (int)(vetor[i] * QTD_BUCKETS); // verifica qual número depois da vírgula, transformando o float em inteiro, para descobrir em qual balde ele vai.

        baldes[indice][contagem_baldes[indice]++] = vetor[i]; // insere o valor em cada balde
    }

    // Ordenar cada balde
    for (int i = 0; i < QTD_BUCKETS; i++)
    {
        insertionSort(baldes[i], contagem_baldes[i]);
    }

    // Concatenar os baldes de volta no vetor original
    int k = 0;
    for (int i = 0; i < QTD_BUCKETS; i++)
    {
        for (int j = 0; j < contagem_baldes[i]; j++)
        {
            vetor[k++] = baldes[i][j];
        }
        free(baldes[i]); // Liberar memória
    }
}

// Função para imprimir o vetor
void imprimeVetor(float vetor[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (i == 0)
        {
            printf("[ %.2f, ", vetor[i]);
        }
        else if (i == tamanho - 1)
        {
            printf("%.2f ]", vetor[i]);
        }
        else
        {
            printf("%.2f, ", vetor[i]);
        }
    }
    printf("\n");
}

// Função principal
int main()
{
    float vetor[] = {0.42, 0.32, 0.23, 0.52, 0.25, 0.47, 0.51};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    printf("Vetor original:\n");
    imprimeVetor(vetor, tamanho);

    bucketSort(vetor, tamanho);

    printf("Vetor ordenado:\n");
    imprimeVetor(vetor, tamanho);

    return 0;
}
