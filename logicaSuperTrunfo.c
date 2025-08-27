#include <stdio.h>
#include <stdlib.h>

// Desafio Super Trunfo - Países
// Tema 2 - Comparação das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de comparação de cartas de cidades. 
// Siga os comentários para implementar cada parte do desafio.

// Definição das variáveis para armazenar as propriedades das cidades
// Você pode utilizar o código do primeiro desafio

// Cadastro das Cartas:
// Implemente a lógica para solicitar ao usuário que insira os dados das cidades
// utilizando a função scanf para capturar as entradas.
// utilize o código do primeiro desafio

// Exemplo:
// printf("Digite o código da cidade: ");
// scanf("%s", codigo);
// 
// (Repita para cada propriedade)

// Comparação de Cartas:
// Desenvolva a lógica de comparação entre duas cartas.
// Utilize estruturas de decisão como if, if-else para comparar atributos como população, área, PIB, etc.

// Exemplo:
// if (populacaoA > populacaoB) {
//     printf("Cidade 1 tem maior população.\n");
// } else {
//     printf("Cidade 2 tem maior população.\n");
// }

// Exibição dos Resultados:
// Após realizar as comparações, exiba os resultados para o usuário.
// Certifique-se de que o sistema mostre claramente qual carta venceu e com base em qual atributo.

// Exemplo:
// printf("A cidade vencedora é: %s\n", cidadeVencedora);



typedef struct {
    char estado[3];
    char codigo[4];
    char nomeCidade[50];

    unsigned long int totalPopulacao;
    float areaCidade;
    float pib;
    int totalTurismo;

    float densidadePopulacao;
    float pibPerCapita;
    float superPoder;
} Carta;

typedef enum {
    ATTR_POPULACAO,
    ATTR_AREA,
    ATTR_PIB,
    ATTR_TURISMO,
    ATTR_DENSIDADE,
    ATTR_PIB_PER_CAPITA,
    ATTR_SUPER_PODER
} Atributos;

const char* NAMES_ATTR[] = {
    "População",
    "Área",
    "PIB",
    "Turismo",
    "Densidade",
    "PIB per capita",
    "Super Poder"
};


static void lerCarta(Carta *carta, int cartaNum) {
    printf("====== CADASTRE A CARTA %d ======\n", cartaNum);
    printf("Estado (Digite uma letra de A a H): ");
    scanf(" %2s", carta->estado);

    printf("Digite o código (ex: 01): ");
    scanf("%3s", carta->codigo);

    printf("Digite o nome da cidade: ");
    scanf(" %[^\n]", carta->nomeCidade);

    printf("Digite a população: ");
    scanf("%lu", &carta->totalPopulacao);

    printf("Digite a área (em km²): ");
    scanf("%f", &carta->areaCidade);

    printf("Digite o PIB: ");
    scanf("%f", &carta->pib);

    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &carta->totalTurismo);
    printf("\n");
}

static void calcIndices(Carta *carta) {
    if (carta->areaCidade > 0.0f && carta->totalPopulacao > 0) {
        carta->densidadePopulacao = (float)carta->totalPopulacao / carta->areaCidade;
    } else {
        carta->densidadePopulacao = 0.0f;
    }

    if (carta->totalPopulacao > 0) {
        carta->pibPerCapita = carta->pib / (float)carta->totalPopulacao;
    } else {
        carta->pibPerCapita = 0.0f;
    }

    float inversoDensidade = (carta->densidadePopulacao > 0.0f) ? (1.0f / carta->densidadePopulacao) : 0.0f;

    carta->superPoder = (float)carta->totalPopulacao 
                     + carta->areaCidade
                     + carta->pib
                     + (float)carta->totalTurismo
                     + carta->pibPerCapita
                     + inversoDensidade;
}

static void showCarta(const Carta *carta, int idx) {
    printf("=== CARTA %d ===\n", idx);
    printf("Estado: %s\n", carta->estado);
    printf("Código: %s\n", carta->codigo);
    printf("Nome da Cidade: %s\n", carta->nomeCidade);
    printf("População: %lu\n", carta->totalPopulacao);
    printf("Área: %.2f km²\n", carta->areaCidade);
    printf("PIB: %.2f bilhões de reais\n", carta->pib);
    printf("Pontos Turísticos: %d\n", carta->totalTurismo);
    printf("Densidade Populacional: %.2f\n", carta->densidadePopulacao);
    printf("PIB per Capita: %.2f\n", carta->pibPerCapita);
    printf("Super Poder: %.2f\n", carta->superPoder);
    printf("\n");
}

static void printResult(const char *attribute, int winner, const Carta *a, const Carta *b, Atributos attr) {
    const char* cartaWinner = winner ? "Carta 1" : "Carta 2";
    const char* cityWinner  = winner ? a->nomeCidade : b->nomeCidade;

    printf("Comparação de cartas (Atributo: %s):\n", attribute);

    switch (attr) {
        case ATTR_POPULACAO:
            printf("Carta 1 - %s (%s): %lu\n", a->nomeCidade, a->estado, a->totalPopulacao);
            printf("Carta 2 - %s (%s): %lu\n", b->nomeCidade, b->estado, b->totalPopulacao);
            break;

        case ATTR_AREA:
            printf("Carta 1 - %s (%s): %.2f km²\n", a->nomeCidade, a->estado, a->areaCidade);
            printf("Carta 2 - %s (%s): %.2f km²\n", b->nomeCidade, b->estado, b->areaCidade);
            break;

        case ATTR_PIB:
            printf("Carta 1 - %s (%s): %.2f bilhões de reais\n", a->nomeCidade, a->estado, a->pib);
            printf("Carta 2 - %s (%s): %.2f bilhões de reais\n", b->nomeCidade, b->estado, b->pib);
            break;

        case ATTR_TURISMO:
            printf("Carta 1 - %s (%s): %d pontos turísticos\n", a->nomeCidade, a->estado, a->totalTurismo);
            printf("Carta 2 - %s (%s): %d pontos turísticos\n", b->nomeCidade, b->estado, b->totalTurismo);
            break;

        case ATTR_DENSIDADE:
            printf("Carta 1 - %s (%s): %.2f hab/km²\n", a->nomeCidade, a->estado, a->densidadePopulacao);
            printf("Carta 2 - %s (%s): %.2f hab/km²\n", b->nomeCidade, b->estado, b->densidadePopulacao);
            break;

        case ATTR_PIB_PER_CAPITA:
            printf("Carta 1 - %s (%s): %.2f reais\n", a->nomeCidade, a->estado, a->pibPerCapita);
            printf("Carta 2 - %s (%s): %.2f reais\n", b->nomeCidade, b->estado, b->pibPerCapita);
            break;

        case ATTR_SUPER_PODER:
            printf("Carta 1 - %s (%s): %.2f\n", a->nomeCidade, a->estado, a->superPoder);
            printf("Carta 2 - %s (%s): %.2f\n", b->nomeCidade, b->estado, b->superPoder);
            break;
    }

    printf("Resultado: %s (%s) venceu!\n\n", cartaWinner, cityWinner);
}


static void compareAttr(const Carta *a, const Carta *b, Atributos attr) {
    int winner = 0;
    const char* attribute = "";
    const char* theCity = "";

    switch (attr) {
        case ATTR_POPULACAO:
            winner = ( (float)a->totalPopulacao > (float)b->totalPopulacao );
            attribute = NAMES_ATTR[ATTR_POPULACAO];
            theCity = winner ? a->nomeCidade : b->nomeCidade;
            break;
        case ATTR_AREA:
            winner = ( a->areaCidade > b->areaCidade );
            attribute = NAMES_ATTR[ATTR_AREA];
            theCity = winner ? a->nomeCidade : b->nomeCidade;
            break;
        case ATTR_PIB:
            winner = ( a->pib > b->pib );
            attribute = NAMES_ATTR[ATTR_PIB];
            theCity = winner ? a->nomeCidade : b->nomeCidade;
            break;
        case ATTR_TURISMO:
            winner = ( a->totalTurismo > b->totalTurismo );
            attribute = NAMES_ATTR[ATTR_TURISMO];
            theCity = winner ? a->nomeCidade : b->nomeCidade;
            break;
        case ATTR_DENSIDADE:
            winner = ( a->densidadePopulacao < b->densidadePopulacao );
            attribute = NAMES_ATTR[ATTR_DENSIDADE];
            theCity = winner ? a->nomeCidade : b->nomeCidade;
            break;
        case ATTR_PIB_PER_CAPITA:
            winner = ( a->pibPerCapita > b->pibPerCapita );
            attribute = NAMES_ATTR[ATTR_PIB_PER_CAPITA];
            theCity = winner ? a->nomeCidade : b->nomeCidade;
            break;
        case ATTR_SUPER_PODER:
            winner = ( a->superPoder > b->superPoder );
            attribute = NAMES_ATTR[ATTR_SUPER_PODER];
            theCity = winner ? a->nomeCidade : b->nomeCidade;
            break;
        default:
            break;
    }
    
    printResult(attribute, winner, a, b, attr);
    printf("\n");
}

int main(void) {
    Carta carta1 = {0}, carta2 = {0};

    lerCarta(&carta1, 1);
    lerCarta(&carta2, 2);

    calcIndices(&carta1);
    calcIndices(&carta2);
    
    showCarta(&carta1, 1);
    showCarta(&carta2, 2);

    compareAttr(&carta1, &carta2, ATTR_POPULACAO);
    compareAttr(&carta1, &carta2, ATTR_AREA);
    // depois faço o resto

    return 0;
}