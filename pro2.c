#include <stdio.h>
#include <math.h>
#include <float.h>

#define NUMERO_CIDADE 10

// Coordenadas das 10 cidades
double cidade_x[NUMERO_CIDADE] = {0, 2, 5, 1, 6, 7, 3, 8, 4, 9};
double cidade_y[NUMERO_CIDADE] = {0, 3, 4, 1, 2, 5, 8, 9, 7, 6};

double distancia(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)); // Calcula a distância entre dois pontos
}

void calcular_distancias(double distancias[NUMERO_CIDADE][NUMERO_CIDADE])
{
    // Calcula a matriz de distancia entre todas as cidades
    for (int i = 0; i < NUMERO_CIDADE; i++)
    {
        for (int j = 0; j < NUMERO_CIDADE; j++)
        {
            distancias[i][j] = distancia(cidade_x[i], cidade_y[i], cidade_x[j], cidade_y[j]);
        }
    }
}

void trocar(int *m, int *v) {
    int temp = *m;
    *m = *v;
    *v = temp;
}

void permutacao(int *cidades, int inicio, int fim, double distancias[NUMERO_CIDADE][NUMERO_CIDADE], double *melhor_distancia, int *melhor_rota) {
    if (inicio == fim) {
        double distancia_atual = 0;
        int rota_atual[NUMERO_CIDADE + 1];

        rota_atual[0] = 0;
        distancia_atual += distancias[0][cidades[0]];

        for (int i = 0; i < fim; i++) {
            rota_atual[i + 1] = cidades[i];
            if (i < fim - 1) {
                distancia_atual += distancias[cidades[i]][cidades[i + 1]];
            }
        }
        distancia_atual += distancias[cidades[fim - 1]][0];
        rota_atual[NUMERO_CIDADE] = 0;

        // Imprime a rota testada em uma única linha
        printf("Rota testada: ");
        for (int i = 0; i <= NUMERO_CIDADE; i++) {
            printf("%d", rota_atual[i]);
            if (i < NUMERO_CIDADE) {
                printf(" -> ");
            }
        }
        printf(" | Distancia: %.2f\n", distancia_atual);

        if (distancia_atual < *melhor_distancia) {
            *melhor_distancia = distancia_atual;
            for (int i = 0; i <= NUMERO_CIDADE; i++) {
                melhor_rota[i] = rota_atual[i];
            }
        }
    } else {
        for (int i = inicio; i < fim; i++) {
            trocar(&cidades[inicio], &cidades[i]);
            permutacao(cidades, inicio + 1, fim, distancias, melhor_distancia, melhor_rota);
            trocar(&cidades[inicio], &cidades[i]);
        }
    }
}


int main()
{
    double distancias[NUMERO_CIDADE][NUMERO_CIDADE];
    calcular_distancias(distancias);

    for(int i = 0; i < NUMERO_CIDADE; i++) {
        printf("Cidade %d: [%g, %g]\n", i, cidade_x[i], cidade_y[i]);
    }

    printf("\nCalculo das rotas possiveis (aguarde, sao 362.880 rotas):\n\n");

    int cidades[NUMERO_CIDADE - 1];
    for (int i = 0; i < NUMERO_CIDADE - 1; i++) {
        cidades[i] = i + 1;
    }

    double melhor_distancia = DBL_MAX; 
    int melhor_rota[NUMERO_CIDADE + 1];

    permutacao(cidades, 0, NUMERO_CIDADE - 1, distancias, &melhor_distancia, melhor_rota);

    printf("TODAS AS ROTAS FORAM CALCULADAS.\n");
    printf("Melhor rota encontrada: ");
    for (int i = 0; i <= NUMERO_CIDADE; i++) {
        printf("%d", melhor_rota[i]);
        if (i < NUMERO_CIDADE) {
            printf(" -> ");
        }
    }
    printf("\nDistancia total: %.2f\n", melhor_distancia);

    printf("O algoritmo de greedy, pois otimiza o codigo, porem nao consegue ter a mesma presicao para escolher a melhor rota.");
    return 0;
}