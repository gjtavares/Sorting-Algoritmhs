#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <time.h>
#else
#include <sys/times.h>
#include <sys/unistd.h>
#endif
#include "funcoes.h"

int main(int argc, int **argv)
{
    int i;
    int k = atoi(argv[3]); // Valor k fornecido na linha de comando é armazenado
    char algo1[50], algo2[50];
    char Entrada[50];

    strcpy(algo1, argv[1]);
    strcpy(algo2, argv[2]);
    strcpy(Entrada, argv[4]);

    int *NumerosDeElementosDoVetor = (int*)malloc(sizeof(int));
    if(NumerosDeElementosDoVetor == NULL)
        return printf("Espaço em memoria Insuficiente\n");

    *NumerosDeElementosDoVetor = QntDeElementos(Entrada);

    int *Vetor = (int*)malloc(*NumerosDeElementosDoVetor * sizeof(int));
    if(Vetor == NULL)
        return printf("Espaço em memoria Insuficiente\n");

    CriaVetor(Vetor, Entrada, *NumerosDeElementosDoVetor);

    // Medição do tempo

    int a;
    // O tempo eh calculado como a subtracao de dois tempos
    int C = *NumerosDeElementosDoVetor;
    float s = getTime();
    int* vec = (int*) malloc (C * sizeof(int));

    // Chama os algorotimos de ordeção

    if(strcmp(algo1,"mergesort")== 0)
    {
        mergesort(Vetor, 0, *NumerosDeElementosDoVetor-1, k, algo2);
    }
    else
    {
        if(strcmp(algo1,"quicksortpivotinicial")== 0)
        {
            quicksortpivotinicial(Vetor, 0, *NumerosDeElementosDoVetor-1, k, algo2);
        }
        else
        {
            if(strcmp(algo1,"quicksortmedianade3")== 0)
            {
                quicksortmedianade3(Vetor, 0, *NumerosDeElementosDoVetor, k, algo2);
            }
            else
            {
                printf("\nalgo1 nao identificado");
                return;
            }
        }
    }

    for (a = 0; a < C; a++)
    {
        vec[a] = a;
    }

    // Tempo gasto paraordenação é exibido

    free(vec);
    printf("\nTempo gasto em segundos para inserir %d numeros no vetor: %.5fs\n\n", C, getTime() - s);
    return 0;

    return 0;
}
