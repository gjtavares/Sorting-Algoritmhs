#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED
#endif // FUNCOES_H_INCLUDED

// Lê o arquivo e armazena a quantidade de elementos presentes do vetor.

int QntDeElementos(char *Entrada)
{
    int NumElementos;

    FILE *arq;

    arq = fopen(Entrada, "r");

    if(arq == NULL)
        printf("Erro, Arquivo nao encontrado");
    else
    {
        fscanf(arq, "%d", &NumElementos);
    }

    fclose(arq);

    return NumElementos;
}

// lê o arquivo de entrada e armazena em um vetor os elementos contidos no arquivo de entrada a serm ordenados.

void CriaVetor(int *Vetor, char *Entrada, int NumerosDeElementosDoVetor)
{
    int a, c=0;
    char crc;
    char *results;
    char ConteudoLido[1000];

    FILE *arq1, *arq2;
    arq1 = fopen(Entrada, "r");
    arq2 = fopen("Format.txt", "w");

    if(arq1 == NULL)
        printf("Erro, arquivo nao encontrado");
    else
    {
        fscanf(arq1, "%d", &a);

        while(!feof(arq1))
        {
            crc = fgetc(arq1);

            if(crc == ' ')
            {
                fprintf(arq2, "\n");
            }
            else
            {
                fprintf(arq2, "%c", crc);
            }
            fprintf(arq2, '\0');
        }
    }

    fclose(arq1);
    fclose(arq2);

    arq2 = fopen("Format.txt", "r");

    while(!feof(arq2))
    {
        results = fgets(ConteudoLido, sizeof(ConteudoLido), arq2);

        if(results && c<NumerosDeElementosDoVetor)
        {
            fscanf(arq2, "%d", &Vetor[c]);
            c++;
        }
    }

    fclose(arq2);
}

void bubllesort(int *Vetor, int inicio, int fim)
{
    int i, j;
    int Auxiliar;

    for(i=0; i<fim-inicio; i++)
    {
        for(j=inicio+1; j<=fim-i; j++)
        {
            if(Vetor[j] < Vetor[j-1])
            {
                Auxiliar = Vetor[j];
                Vetor[j] = Vetor[j-1];
                Vetor[j-1] = Auxiliar;
            }
        }
    }
}

void selectionsort(int *Vetor, int inicio, int fim)
{
    int Minimo, i, j;
    int Auxiliar;

    for(i=inicio; i<fim; i++)
    {
        Minimo = i;

        for(j=i+1; j<=fim; j++)
        {
            if(Vetor[j] < Vetor[Minimo])
            {
                Minimo = j;
            }

            Auxiliar = Vetor[Minimo];
            Vetor[Minimo] = Vetor[i];
            Vetor[i] = Auxiliar;
        }
    }
}

void insertionsort(int *Vetor, int inicio, int fim)
{
    int i, j, Auxiliar;

    for(i=inicio+1; i<=fim; i++)
    {
        Auxiliar = Vetor[i];
        j = i-1;

        while(j>=inicio && Auxiliar<Vetor[j])
        {
            Vetor[j+1] = Vetor[j];
            j= j-1;
        }

        Vetor[j+1] = Auxiliar;
    }
}

void heapsort(int *Vetor, int inicio, int fim)
{
    fim=fim+1;

    int i = ((fim-inicio+1) / 2)+inicio;
    int pai, filho, t;

    for (;;)
    {
        if (i > 0)
        {
            i--;
            t = Vetor[i];
        }
        else
        {
            fim--;
            if (fim == 0) return;
            t = Vetor[fim];
            Vetor[fim] = Vetor[0];
        }

        pai = i;
        filho = i * 2 + 1;
        while (filho < fim)
        {
            if ((filho + 1 < fim)  &&  (Vetor[filho + 1] > Vetor[filho]))
                filho++;
            if (Vetor[filho] > t)
            {
                Vetor[pai] = Vetor[filho];
                pai = filho;
                filho = pai * 2 + 1;
            }
            else
            {
                break;
            }
        }
        Vetor[pai] = t;
    }
}

void mergesort(int *V, int inicio, int fim, int k, char *algo2)
{
    int meio, i;

    if(inicio < fim)
    {
        if((fim-inicio+1)<k)
        {
            if(strcmp(algo2,"bubllesort")== 0)
            {
                bubllesort(V, inicio, fim);
            }
            if(strcmp(algo2,"selectionsort")== 0)
            {
                selectionsort(V, inicio, fim);
            }
            if(strcmp(algo2,"insertionsort")== 0)
            {
                insertionsort(V, inicio, fim);
            }
            if(strcmp(algo2,"heapsort")== 0)
            {
                heapsort(V, inicio, fim);
            }
            if(strcmp(algo2,"mergesort")== 0)
            {
                mergesort(V, inicio, fim, 1, algo2);
            }
            if(strcmp(algo2,"quicksortpivotinicial")== 0)
            {
                quicksortpivotinicial(V, inicio, fim, 1, algo2);
            }
            if(strcmp(algo2,"quicksortmedianade3")== 0)
            {
                quicksortmedianade3(V, inicio, fim+1, 1, algo2);
            }
        }
        else
        {
            meio = floor((inicio+fim)/2);
            mergesort(V, inicio, meio, k, algo2);
            mergesort(V, meio+1, fim, k, algo2);
            merge(V, inicio, meio, fim);
        }
    }

}

void merge(int *V, int inicio, int meio, int fim)
{
    int *temp, p1, p2, tamanho, i, j, k;
    int fim1=0, fim2=0;

    tamanho = fim-inicio+1;
    p1=inicio;
    p2=meio+1;
    temp = (int*) malloc(tamanho*sizeof(int));

    if(temp != NULL)
    {
        for(i=0; i<tamanho; i++)
        {
            if(!fim1 && !fim2)
            {
                if(V[p1] < V[p2])
                {
                    temp[i] = V[p1++];
                }
                else
                {
                    temp[i] = V[p2++];
                }
                if(p1>meio) fim1=1;
                if(p2>fim) fim2=1;
            }
            else
            {
                if(!fim1)
                {
                    temp[i] = V[p1++];
                }
                else
                {
                    temp[i] = V[p2++];
                }
            }
        }
        for(j=0, k=inicio; j<tamanho; j++, k++)
        {
            V[k] = temp[j];
        }
    }
    free(temp);
}

void quicksortpivotinicial(int *V, int inicio, int fim,int k, char *algo2)
{
    int pivo;
    if(fim > inicio)
    {
        if((fim-inicio+1)<k)
        {
            if(strcmp(algo2,"bubllesort")== 0)
            {
                bubllesort(V, inicio, fim);
            }
            if(strcmp(algo2,"selectionsort")== 0)
            {
                selectionsort(V, inicio, fim);
            }
            if(strcmp(algo2,"insertionsort")== 0)
            {
                insertionsort(V, inicio, fim);
            }
            if(strcmp(algo2,"heapsort")== 0)
            {
                heapsort(V, inicio, fim);
            }
            if(strcmp(algo2,"mergesort")== 0)
            {
                mergesort(V, inicio, fim, 1, algo2);
            }
            if(strcmp(algo2,"quicksortpivotinicial")== 0)
            {
                quicksortpivotinicial(V, inicio, fim, 1, algo2);
            }
            if(strcmp(algo2,"quicksortmedianade3")== 0)
            {
                quicksortmedianade3(V, inicio, fim+1, 1, algo2);
            }
        }
        else
        {
            pivo = particiona(V, inicio, fim);
            quicksortpivotinicial(V, inicio, pivo-1, k, algo2);
            quicksortpivotinicial(V, pivo+1, fim, k, algo2);
        }
    }
}

int particiona(int *V, int inicio, int fim)
{
    int esq, dir, pivo, aux;
    esq = inicio;
    dir = fim;
    pivo = V[inicio];

    while(esq < dir)
    {
        while(V[esq] <= pivo)
            esq++;
        while(V[dir] > pivo)
            dir--;
        if(esq < dir)
        {
            aux = V[esq];
            V[esq] = V[dir];
            V[dir] = aux;
        }
    }

    V[inicio] = V[dir];
    V[dir] = pivo;
    return dir;
}

void swap(int *x, int *y)
{
    int temp;

    temp=*x;
    *x=*y;
    *y=temp;
}

void quicksortmedianade3(int *V, int inicio, int fim, int k, char *algo2)
{
    int pivo;

    if(fim-inicio<2) return;

    if((fim-inicio)<k)
    {
        if(strcmp(algo2,"bubllesort")== 0)
        {
            bubllesort(V, inicio, fim-1);
        }
        if(strcmp(algo2,"selectionsort")== 0)
        {
            selectionsort(V, inicio, fim-1);
        }
        if(strcmp(algo2,"insertionsort")== 0)
        {
            insertionsort(V, inicio, fim-1);
        }
        if(strcmp(algo2,"heapsort")== 0)
        {
            heapsort(V, inicio, fim-1);
        }
        if(strcmp(algo2,"mergesort")== 0)
        {
            mergesort(V, inicio, fim-1, 1, algo2);
        }
        if(strcmp(algo2,"quicksortpivotinicial")== 0)
        {
            quicksortpivotinicial(V, inicio, fim-1, 1,algo2);
        }
        if(strcmp(algo2,"quicksortmedianade3")== 0)
        {
            quicksortmedianade3(V, inicio, fim, 1, algo2);
        }
    }
    else
    {
        pivo=Medianade3Partition(V, inicio, fim);
        quicksortmedianade3(V, inicio, pivo, k, algo2);
        quicksortmedianade3(V, pivo, fim, k, algo2);
    }
}

int Medianade3Partition(int *V, int inicio, int fim)
{
    int x=V[inicio], y=V[(fim-inicio)/2+inicio], z=V[fim-1];
    int i=inicio-1, j=fim;

    if(y>x && y<z || y>z && y<x) x=y;
    else if(z>x && z<y || z>y && z<x) x=z;

    while(1)
    {
        do
        {
            j--;
        }
        while(V[j]>x);
        do
        {
            i++;
        }
        while(V[i]<x);
        if(i<j) swap(&V[i], &V[j]);
        else return j+1;
    }
}

//Medição do tempo

float getTime()
{
#ifdef _WIN32
    clock_t start = clock();
    return (float)start / CLOCKS_PER_SEC;
#else
    struct tms tempo;
    clock_t tempotic;
    float cpt = sysconf(_SC_CLK_TCK);
    times(&tempo);
    tempotic = tempo.tms_utime ;
    return ( (float) (tempotic/cpt) );
#endif
}
