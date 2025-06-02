#include <stdio.h>
#include <stdlib.h>

void imprimeVetor(int vetor[], int tamanho)
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

void bubbleSort(int vetor[], int tamanho)
{
    for (int i = 0; i < tamanho - 1; i++) // pega cada elemento de um vetor
    {
        for (int j = 0; j < tamanho - i - 1; j++) // e vai comparando com o proximo
        {
            if (vetor[j] > vetor[j + 1]) // se o proximo elemento for maior
            {
                int temp = vetor[j + 1];
                vetor[j + 1] = vetor[j];
                vetor[j] = temp; // os valores invertem
            } // o laço repete ate percorrer todos os elementos e comparar todos os elementos
        }
        printf("\n");
    }
}

void insertionSort(int vetor[], int tamanho)
{
    for (int i = 1; i < tamanho; i++) // i comeca em 1 pois se quer o segundo elemento, pois a posicao 0 eh considerada ordenada
    {
        int chave = vetor[i]; // comeca no segundo elemento, mas ira avancar a cada laco
        int j = i - 1;        // indice do elemento anterior a chave

        while (j >= 0 && chave < vetor[j]) // se o indice do elemento anterior a chave for >= 0, e a chave for menor que o elemento anterior (parte ordenada), significa que esta desordenado
        {
            vetor[j + 1] = vetor[j]; // troca o valor de vetor[i](atual ou chave) pelo valor do elemento anterior
            j--;                     // serve para quebrar o loop, quando j for -1 ou quando o elemento desordenado estiver ordenado
        }

        vetor[j + 1] = chave; // garante que a chave sempre seja inserida no lugar correto
    }
}

void selectionSort(int vetor[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        int indiceMenor = i;
        for (int j = i + 1; j < tamanho; j++)
        {
            if (vetor[j] < vetor[indiceMenor])
            {
                indiceMenor = j;
            }
        }

        if (indiceMenor != i)
        {
            int temp = vetor[indiceMenor];
            vetor[indiceMenor] = vetor[i];
            vetor[i] = temp;
        }
    }
}

void quickSort(int vetor[], int tamanho)
{
    if (tamanho < 2) // Se o tamanho do vetor for menor que 2, não há nada a ordenar
        return;

    int pivo = vetor[tamanho / 2]; // Escolhe o pivô como o elemento do meio
    int i, j;
    i = 0;
    j = tamanho - 1;

    while (i <= j)
    {
        while (vetor[i] < pivo) // Encontra o primeiro elemento maior ou igual ao pivô
            i++;
        while (vetor[j] > pivo) // Encontra o primeiro elemento menor ou igual ao pivô
            j--;

        if (i <= j)
        {
            // Troca os elementos encontrados
            int temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
            i++;
            j--;
        }
    }

    // Chama recursivamente para as duas metades
    quickSort(vetor, j + 1);
    quickSort(vetor + i, tamanho - i);
}

void mergeSort(int vetor[], int tamanho)
{
    if (tamanho < 2) // Se o tamanho do vetor for menor que 2, não há nada a ordenar
        return;

    int meio = tamanho / 2;
    int *esquerda = (int *)malloc(meio * sizeof(int));
    int *direita = (int *)malloc((tamanho - meio) * sizeof(int));

    // Copia os elementos para os sub-vetores
    for (int i = 0; i < meio; i++)
        esquerda[i] = vetor[i];
    for (int i = meio; i < tamanho; i++)
        direita[i - meio] = vetor[i];

    // Ordena recursivamente os sub-vetores
    mergeSort(esquerda, meio);
    mergeSort(direita, tamanho - meio);

    // Mescla os sub-vetores de volta no vetor original
    int i = 0, j = 0, k = 0;
    while (i < meio && j < tamanho - meio)
    {
        if (esquerda[i] <= direita[j])
            vetor[k++] = esquerda[i++];
        else
            vetor[k++] = direita[j++];
    }

    // Copia os elementos restantes, se houver
    while (i < meio)
        vetor[k++] = esquerda[i++];
    while (j < tamanho - meio)
        vetor[k++] = direita[j++];

    free(esquerda);
    free(direita);
}

void trocar(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para transformar uma subárvore com raiz no índice 'i' em um Max-Heap.
// 'n' é o tamanho do heap.
void heapify(int vetor[], int n, int i)
{
    // Inicializa o maior como a raiz da subárvore
    int maior = i;
    int esquerda = 2 * i + 1; // Índice do filho da esquerda
    int direita = 2 * i + 2;  // Índice do filho da direita

    // Se o filho da esquerda é maior que a raiz
    if (esquerda < n && vetor[esquerda] > vetor[maior])
    {
        maior = esquerda;
    }

    // Se o filho da direita é maior que o maior até agora
    if (direita < n && vetor[direita] > vetor[maior])
    {
        maior = direita;
    }

    // Se o maior não for a raiz original
    if (maior != i)
    {
        // Troca a raiz com o maior filho
        trocar(&vetor[i], &vetor[maior]);

        // Chama recursivamente heapify para a subárvore afetada
        heapify(vetor, n, maior);
    }
}

void heapSort(int vetor[], int tamanho)
{
    // 1. Construir o Max-Heap (reorganizar o vetor)
    // Começa a partir do último nó não-folha e vai até a raiz
    for (int i = tamanho / 2 - 1; i >= 0; i--)
    {
        heapify(vetor, tamanho, i);
    }

    // 2. Extrair elementos um por um do heap
    for (int i = tamanho - 1; i > 0; i--)
    {
        // Move a raiz atual (maior elemento) para o final do vetor
        trocar(&vetor[0], &vetor[i]);

        // Chama heapify na heap reduzida para manter a propriedade de Max-Heap
        heapify(vetor, i, 0);
    }
}

void radixSort(int vetor[], int tamanho)
{
    if (tamanho <= 0)
        return;

    int max_val = vetor[0];
    for (int i = 1; i < tamanho; i++)
    {
        if (vetor[i] > max_val)
        {
            max_val = vetor[i];
        }
    }

    for (int exp = 1; max_val / exp > 0; exp *= 10)
    {
        int *output = (int *)malloc(tamanho * sizeof(int));
        int count[10] = {0};

        // Contagem dos dígitos
        for (int i = 0; i < tamanho; i++)
        {
            count[(vetor[i] / exp) % 10]++;
        }

        // Cálculo das posições
        for (int i = 1; i < 10; i++)
        {
            count[i] += count[i - 1];
        }

        // Construção do vetor de saída
        for (int i = tamanho - 1; i >= 0; i--)
        {
            output[count[(vetor[i] / exp) % 10] - 1] = vetor[i];
            count[(vetor[i] / exp) % 10]--;
        }

        // Copia o vetor de saída de volta para o vetor original
        for (int i = 0; i < tamanho; i++)
        {
            vetor[i] = output[i];
        }

        free(output);
    }
}

void bucketSort(int vetor[], int tamanho)
{
    if (tamanho <= 0)
        return;

    // 1. Encontrar o maior elemento para normalizar os índices
    int max_val = vetor[0];
    for (int i = 1; i < tamanho; i++)
    {
        if (vetor[i] > max_val)
        {
            max_val = vetor[i];
        }
    }

    // Criar os buckets
    int qtd_buckets = 10;
    int *baldes[qtd_buckets];
    int contagem_baldes[qtd_buckets];

    // Inicializar os baldes (de forma mais eficiente)
    for (int i = 0; i < qtd_buckets; i++)
    {
        // Alocação mais segura, mas ainda pode ser otimizada
        // com realocação dinâmica (realloc) ou usando listas encadeadas.
        baldes[i] = (int *)malloc(tamanho * sizeof(int));
        if (baldes[i] == NULL)
        {
            // Tratar erro de alocação
            return;
        }
        contagem_baldes[i] = 0;
    }

    // 2. Distribuir os elementos nos baldes com a fórmula correta
    for (int i = 0; i < tamanho; i++)
    {
        // Fórmula de normalização para inteiros
        int indice = (int)(((long)vetor[i] * qtd_buckets) / (max_val + 1));

        // Garante que o índice não saia do limite por problemas de arredondamento
        if (indice >= qtd_buckets)
        {
            indice = qtd_buckets - 1;
        }

        baldes[indice][contagem_baldes[indice]++] = vetor[i];
    }

    // Ordenar cada balde
    for (int i = 0; i < qtd_buckets; i++)
    {
        if (contagem_baldes[i] > 0)
        { // Só ordena se o balde não estiver vazio
            insertionSort(baldes[i], contagem_baldes[i]);
        }
    }

    // Concatenar os baldes de volta no vetor original
    int k = 0;
    for (int i = 0; i < qtd_buckets; i++)
    {
        for (int j = 0; j < contagem_baldes[i]; j++)
        {
            vetor[k++] = baldes[i][j];
        }
        free(baldes[i]); // Liberar memória
    }
}

int main()
{
    printf("----------algoritmos de ordenacao-------------\n");
    printf("quantos elementos tera o array? :");

    int qtdElementos;

    scanf("%d", &qtdElementos);
    getchar();

    int array[qtdElementos];

    for (int i = 0; i < qtdElementos; i++)
    {
        printf("qual o elemento da %dº posicao? :", i);
        scanf("%d", &array[i]);
        getchar();
    }

    printf("\nseu array original e: ");

    imprimeVetor(array, qtdElementos);

    printf("\nPressione enter para continuar...");
    getchar();

    printf("como deseja ordena-lo?\n");
    printf("[1] bubble sort\n");
    printf("[2] insertion sort\n");
    printf("[3] selection sort\n");
    printf("[4] quick sort\n");
    printf("[5] merge sort\n");
    printf("[6] heap sort\n");
    printf("[7] radix sort\n");
    printf("[8] bucket sort\n");
    printf(": ");

    int escolha;
    scanf("%d", &escolha);
    getchar();

    switch (escolha)
    {
    case 1:
        bubbleSort(array, qtdElementos);
        break;
    case 2:
        insertionSort(array, qtdElementos);
        break;
    case 3:
        selectionSort(array, qtdElementos);
        break;
    case 4:
        quickSort(array, qtdElementos);
        break;
    case 5:
        mergeSort(array, qtdElementos);
        break;
    case 6:
        heapSort(array, qtdElementos);
        break;
    case 7:
        radixSort(array, qtdElementos);
        break;
    case 8:
        bucketSort(array, qtdElementos);
        break;
    default:
        printf("ERRO, opcao invalida!\n");
        break;
    }

    printf("seu array ordenado e: ");
    imprimeVetor(array, qtdElementos);

    return 0;
}