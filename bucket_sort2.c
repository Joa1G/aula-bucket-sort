#include <stdio.h>
#include <stdlib.h> // Para malloc e free

// Define o número de baldes que serão usados.
// Você pode ajustar este valor conforme necessário.
#define NUM_BUCKETS 10

// Função auxiliar para imprimir um array
void printArray(int vetor[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (i == 0)
        {
            printf("[ %d, ", vetor[i]);
        }
        else if (i == tamanho - 1)
        {
            printf("%d ]", vetor[i]);
        }
        else
        {
            printf("%d, ", vetor[i]);
        }
    }
    printf("\n");
}

// Função para encontrar o valor máximo em um array
// Isso é necessário para distribuir os elementos nos baldes de forma adequada.
int encontrarMaximo(int arr[], int n)
{
    if (n <= 0)
    {
        return 0; // Retorna 0 se o array estiver vazio ou inválido
    }
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

// Função de Insertion Sort para ordenar os elementos dentro de cada balde.
// Insertion Sort é eficiente para listas pequenas, que é o caso esperado
// para os baldes se os dados estiverem razoavelmente distribuídos.
void insertionSort(int arr[], int n)
{
    if (n <= 0)
        return; // Não faz nada se o balde estiver vazio
    int i, chave, j;
    for (i = 1; i < n; i++)
    {
        chave = arr[i];
        j = i - 1;
        // Move os elementos de arr[0..i-1] que são maiores que a chave
        // para uma posição à frente de sua posição atual
        while (j >= 0 && arr[j] > chave)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = chave;
    }
}

// Função principal do Bucket Sort
void bucketSort(int arr[], int n)
{
    if (n <= 0)
    {
        return; // Não faz nada se o array estiver vazio
    }

    // 1. Encontrar o valor máximo no array para determinar o intervalo dos baldes.
    int max_val = encontrarMaximo(arr, n);

    // Se max_val for 0, todos os elementos são 0. O array já está "ordenado"
    // ou todos os elementos irão para o primeiro balde.
    // O divisor deve ser pelo menos 1.
    int divisor = max_val + 1;

    // 2. Criar os baldes.
    // Cada balde é um array dinâmico. Usamos um array de ponteiros para os baldes.
    // E um array para rastrear a contagem de elementos em cada balde.
    int *buckets[NUM_BUCKETS];
    int bucket_counts[NUM_BUCKETS];

    for (int i = 0; i < NUM_BUCKETS; i++)
    {
        // Aloca memória para cada balde. No pior caso, todos os elementos
        // podem cair em um único balde, então alocamos espaço para 'n' elementos.
        // Para uma implementação mais otimizada em memória, poderíamos usar listas encadeadas
        // ou realocar dinamicamente conforme necessário.
        buckets[i] = (int *)malloc(n * sizeof(int));
        if (buckets[i] == NULL)
        {
            // Tratamento de erro de alocação de memória
            fprintf(stderr, "Falha na alocação de memória para o balde %d\n", i);
            // Liberar memória já alocada antes de sair
            for (int k = 0; k < i; k++)
            {
                free(buckets[k]);
            }
            return; // Ou tratar o erro de forma mais robusta
        }
        bucket_counts[i] = 0; // Inicializa a contagem de elementos para cada balde
    }

    // 3. Distribuir os elementos do array original nos baldes.
    for (int i = 0; i < n; i++)
    {
        int elemento = arr[i];
        // Calcula o índice do balde para o elemento atual.
        // A fórmula ((double)elemento / divisor) * NUM_BUCKETS normaliza o elemento
        // para o intervalo [0, NUM_BUCKETS-1].
        // O casting para (double) garante uma divisão de ponto flutuante antes do truncamento para int.
        int bucket_index = (int)(((double)elemento / divisor) * NUM_BUCKETS);

        // Garante que o elemento máximo caia no último balde se a divisão for exata
        if (bucket_index >= NUM_BUCKETS)
        {
            bucket_index = NUM_BUCKETS - 1;
        }

        // Adiciona o elemento ao balde correspondente e incrementa a contagem.
        buckets[bucket_index][bucket_counts[bucket_index]++] = elemento;
    }

    // 4. Ordenar cada balde individualmente usando Insertion Sort.
    for (int i = 0; i < NUM_BUCKETS; i++)
    {
        if (bucket_counts[i] > 0)
        { // Só ordena se o balde não estiver vazio
            insertionSort(buckets[i], bucket_counts[i]);
        }
    }

    // 5. Juntar (concatenar) os elementos dos baldes ordenados de volta no array original.
    int index = 0;
    for (int i = 0; i < NUM_BUCKETS; i++)
    {
        for (int j = 0; j < bucket_counts[i]; j++)
        {
            arr[index++] = buckets[i][j];
        }
    }

    // 6. Liberar a memória alocada para os baldes.
    for (int i = 0; i < NUM_BUCKETS; i++)
    {
        free(buckets[i]);
    }
}

// Função main para testar o Bucket Sort
int main()
{
    int arr[] = {29, 25, 3, 49, 9, 37, 21, 43};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array original:\n");
    printArray(arr, n);

    bucketSort(arr, n);

    printf("Array ordenado:\n");
    printArray(arr, n);
    printf("\n");

    int arr2[] = {0, 5, 1, 0, 8, 2};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Array original 2:\n");
    printArray(arr2, n2);
    bucketSort(arr2, n2);
    printf("Array ordenado 2:\n");
    printArray(arr2, n2);
    printf("\n");

    int arr3[] = {100, 50, 10, 20, 80, 0, 30, 90, 60, 70, 40};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("Array original 3:\n");
    printArray(arr3, n3);
    bucketSort(arr3, n3);
    printf("Array ordenado 3:\n");
    printArray(arr3, n3);
    printf("\n");

    return 0;
}