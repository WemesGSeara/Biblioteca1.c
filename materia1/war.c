#include <stdio.h>
#include <string.h>

//---Definição da Estrutura (Struct) para Território---
struct Territorio {
    char nome[30];  // Nome do território
    char cor[10];   // Cor do território
    int tropas;     // Quantidade de tropas
};

//--Função principal (main)--
int main() {
    // Declaração de um vetor para armazenar 5 estruturas do tipo Territorio
    struct Territorio territorios[5];
    int i; // Variável de controle para os laços

    //--Entrada de Dados: Laço para preencher 5 territórios---
    printf("---Cadastro de 5 Territórios---\n");
    for (i = 0; i < 5; ++i) {
        printf("\nTerritório #%d:\n", i + 1);

        // Entrada do nome do território
        printf("Digite o nome do território (máx 29 caracteres):\n");
        scanf(" %29[^\n]", territorios[i].nome);

        // Entrada da cor do exército
        printf("Digite a cor do exército (máx 9 caracteres):\n");
        scanf(" %9[^\n]", territorios[i].cor);

        // Entrada da quantidade de tropas
        printf("Digite a quantidade de tropas:\n");
        scanf("%d", &territorios[i].tropas);
    }

    //---Exibição de Dados: Laço para exibir os 5 territórios---
    printf("\n---Dados dos Territórios Cadastrados---\n");
    for (i = 0; i < 5; ++i) {
        printf("------------------\n");
        printf("TERRITÓRIO %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }
    printf("------------------\n");

    return 0;
}
