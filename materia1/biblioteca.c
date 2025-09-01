#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--- Constantes Globais ---
#define MAX_LIVROS 50  // Definindo o número máximo de livros
#define TAM_STRING 100  // Tamanho máximo para as strings (nome, autor, editora)

//--- Definição da Estrutura (Struct) para Livro ---
struct Livro {
    char nome[TAM_STRING];    // Nome do livro
    char autor[TAM_STRING];   // Autor do livro
    char editora[TAM_STRING]; // Editora do livro
    int edicao;               // Edição do livro
};

// Função para limpar o buffer da entrada (necessária após usar scanf)
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa os caracteres até o final da linha
}

//-- Função principal (main) ---
int main() {
    struct Livro biblioteca[MAX_LIVROS];  // Array de livros
    int totalLivros = 0;  // Contador para o número de livros cadastrados
    int opcao;  // Variável para armazenar a opção do menu

    //--- Laço principal do Menu ---
    do {
        // Exibe o menu de opções
        printf("==============================\n");
        printf("    BIBLIOTECA - PARTE 1\n");
        printf("1 - Cadastrar novo Livro\n");
        printf("2 - Listar todos os livros \n");
        printf("0 - Sair\n");
        printf("--------------------------------\n");

        // Lê a opção do usuário
        scanf("%d", &opcao);
        limparBufferEntrada(); // Limpa o \n deixado pelo scanf.

        //--- Processamento da Opção ---
        switch (opcao) {
            case 1: // CADASTRO DE LIVRO
                printf("--- Cadastro de novo livro ---\n");
                
                // Verifica se ainda há espaço para cadastrar novos livros
                if (totalLivros < MAX_LIVROS) {
                    // Solicita as informações do livro
                    printf("Digite o nome do livro: ");
                    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);

                    printf("Digite o autor: ");
                    fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);

                    printf("Digite a editora: ");
                    fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);

                    // Remove o '\n' inserido pelo fgets
                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';
                    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0';

                    // Solicita a edição do livro
                    printf("Digite a edição: ");
                    scanf("%d", &biblioteca[totalLivros].edicao);
                    limparBufferEntrada(); // Limpar o buffer após ler a edição

                    totalLivros++;  // Incrementa o contador de livros cadastrados

                    printf("\nLivro cadastrado com sucesso!\n");
                } else {
                    // Caso a biblioteca esteja cheia
                    printf("Biblioteca cheia! Não é possível cadastrar mais livros.\n");
                }
                
                // Pausa para o usuário ler antes de continuar
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 2: // LISTAGEM DE LIVROS
                printf("--- Lista de livros cadastrados ---\n");

                // Verifica se há livros cadastrados
                if (totalLivros == 0) {
                    printf("Nenhum livro cadastrado ainda.\n");
                } else {
                    // Exibe todos os livros cadastrados
                    for (int i = 0; i < totalLivros; i++) {
                        printf("---------------------------\n");
                        printf("LIVRO %d\n", i + 1);
                        printf("Nome: %s\n", biblioteca[i].nome);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        printf("Editora: %s\n", biblioteca[i].editora);
                        printf("Edição: %d\n", biblioteca[i].edicao);
                    }
                    printf("--------------------------\n");
                }

                // Pausa para o usuário ler antes de continuar
                printf("\nPressione Enter para continuar....");
                getchar();
                break;

            case 0: // SAIR
                printf("Saindo do sistema...\n");
                break;

            default: // Opção inválida
                printf("\nOpção inválida! Tente novamente.\n");
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
        }

    } while (opcao != 0);  // Continua até o usuário escolher sair

    return 0;  // Retorna 0 para indicar que o programa foi executado com sucesso
}
