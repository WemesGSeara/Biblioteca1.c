/**
 * @file gerenciador_biblioteca.c
 * @brief Um sistema simples de gerenciamento de biblioteca em C.
 * @details Este programa permite cadastrar livros, listar os livros cadastrados,
 * realizar empréstimos e listar os empréstimos. Utiliza alocação dinâmica
 * de memória para gerenciar os dados da biblioteca e dos empréstimos.
 * @author Wemes G. Seara
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=============================================================================
// Definições e Constantes Globais
//=============================================================================

#define MAX_LIVROS 50       // Capacidade máxima de armazenamento de livros.
#define MAX_EMPRESTIMO 100  // Número máximo de empréstimos que podem ser registrados.
#define TAM_STRING 100      // Tamanho padrão para campos de texto (strings).

//=============================================================================
// Estruturas de Dados
//=============================================================================

/**
 * @struct Livro
 * @brief Estrutura para armazenar as informações de um único livro.
 */
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel; // Flag de status: 1 para disponível, 0 para emprestado.
};

/**
 * @struct Emprestimo
 * @brief Estrutura para registrar um empréstimo.
 * @details Associa um livro (através do seu índice) a um usuário.
 */
struct Emprestimo {
    int indiceLivro;                 // Índice do livro no array 'biblioteca'.
    char nomeUsuario[TAM_STRING];    // Nome do usuário que pegou o livro.
};

//=============================================================================
// Funções Auxiliares
//=============================================================================

/**
 * @brief Limpa o buffer de entrada do teclado (stdin).
 * @details Esta função é essencial após leituras com scanf que não consomem
 * o caractere de nova linha ('\n'), evitando problemas em leituras subsequentes
 * com fgets. Ela consome todos os caracteres até encontrar um '\n' ou o fim do arquivo (EOF).
 */
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//=============================================================================
// Função Principal
//=============================================================================

int main() {
    // Ponteiros para alocação dinâmica dos dados.
    struct Livro *biblioteca;
    struct Emprestimo *emprestimos;
    
    // Alocação de memória para o array de livros.
    // calloc é usado para inicializar todos os campos com zero, o que é uma prática segura.
    biblioteca = (struct Livro *) calloc(MAX_LIVROS, sizeof(struct Livro));

    // Alocação de memória para o array de empréstimos.
    emprestimos = (struct Emprestimo *) malloc(MAX_EMPRESTIMO * sizeof(struct Emprestimo));

    // Verificação de falha na alocação de memória.
    // É uma boa prática de programação defensiva encerrar o programa se a memória não puder ser alocada.
    if (biblioteca == NULL || emprestimos == NULL){
        printf("Erro: Falha fatal ao alocar memoria.\n");
        return 1; // Retorna 1 para indicar um erro.
    }

    // Variáveis de controle do sistema.
    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;

    // Laço principal do programa, que exibe o menu e processa as opções.
    // O laço continua até que o usuário escolha a opção 0 para sair.
    do {
        printf("==============================\n");
        printf("    BIBLIOTECA - PARTE 2\n");
        printf("1 - Cadastrar novo Livro\n");
        printf("2 - Listar todos os livros\n");
        printf("3 - Realizar emprestimo\n");
        printf("4 - Listar emprestimos\n");
        printf("0 - Sair\n");
        printf("--------------------------------\n");

        scanf("%d", &opcao);
        limparBufferEntrada(); // Limpeza do buffer após ler a opção numérica.

        switch (opcao) {
            case 1: { // Bloco de Cadastro de Livro
                printf("--- Cadastro de novo livro ---\n");
                
                if (totalLivros < MAX_LIVROS) {
                    // Solicita as informações do livro ao usuário.
                    printf("Digite o nome do livro: ");
                    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);

                    printf("Digite o autor: ");
                    fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);

                    printf("Digite a editora: ");
                    fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);

                    // Remove o caractere de nova linha ('\n') inserido pelo fgets.
                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';
                    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0';

                    printf("Digite a edição: ");
                    scanf("%d", &biblioteca[totalLivros].edicao);
                    limparBufferEntrada();
                    
                    // Garante que o livro recém-criado seja marcado como disponível para empréstimo.
                    biblioteca[totalLivros].disponivel = 1;

                    totalLivros++; // Incrementa o contador de livros na biblioteca.
                    printf("\nLivro cadastrado com sucesso!\n");
                } else {
                    printf("Biblioteca cheia! Não é possível cadastrar mais livros.\n");
                }
                
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            }

            case 2: { // Bloco de Listagem de Livros
                printf("--- Lista de livros cadastrados ---\n");

                if (totalLivros == 0) {
                    printf("Nenhum livro cadastrado ainda.\n");
                } else {
                    // Itera sobre o array de livros e exibe as informações de cada um.
                    for (int i = 0; i < totalLivros; i++) {
                        printf("---------------------------\n");
                        printf("LIVRO %d\n", i + 1);
                        printf("Nome: %s\n", biblioteca[i].nome);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        printf("Editora: %s\n", biblioteca[i].editora);
                        printf("Edição: %d\n", biblioteca[i].edicao);
                        
                        // O operador ternário escolhe a string a ser exibida com base no status.
                        printf("Status: %s\n", biblioteca[i].disponivel ? "Disponivel" : "Emprestado");
                    }
                    printf("--------------------------\n");
                }

                printf("\nPressione Enter para continuar....");
                getchar();
                break;
            }

            case 3: { // Bloco de Realização de Empréstimo
                printf("--- Realizar emprestimo ---\n");

                if (totalEmprestimos >= MAX_EMPRESTIMO) {
                    printf("Limite de emprestimos atingido!\n");
                } else {
                    printf("Livros disponiveis:\n");
                    int disponiveis = 0;
                    
                    // Mostra ao usuário apenas os livros que estão disponíveis.
                    for (int i = 0; i < totalLivros; i++) {
                        if (biblioteca[i].disponivel) {
                            printf("%d - %s\n", i + 1, biblioteca[i].nome);
                            disponiveis++;
                        }
                    }

                    if (disponiveis == 0) {
                        printf("Nenhum livro disponivel para emprestimo.\n");
                    } else {
                        printf("\nDigite o numero do livro que deseja emprestar: ");
                        int numLivro;
                        scanf("%d", &numLivro);
                        limparBufferEntrada();

                        // Converte a escolha do usuário (base 1) para o índice do array (base 0).
                        int indice = numLivro - 1;

                        // Valida a entrada do usuário: o índice deve ser válido e o livro deve estar disponível.
                        if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel) {
                            printf("Digite o nome do usuario que esta pegando o livro: ");
                            fgets(emprestimos[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                            emprestimos[totalEmprestimos].nomeUsuario[strcspn(emprestimos[totalEmprestimos].nomeUsuario, "\n")] = '\0';

                            // Registra o empréstimo.
                            emprestimos[totalEmprestimos].indiceLivro = indice;
                            
                            // Atualiza o status do livro para indisponível.
                            biblioteca[indice].disponivel = 0;

                            totalEmprestimos++;
                            printf("\nEmprestimo realizado com sucesso!\n");
                        } else {
                            printf("\nNumero de livro invalido ou livro indisponivel.\n");
                        }
                    }
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            }

            case 4: { // Bloco de Listagem de Empréstimos
                printf("--- Lista de Emprestimos ---\n");
                if (totalEmprestimos == 0) {
                    printf("Nenhum emprestimo realizado ainda.\n");
                } else {
                    // Itera sobre o array de empréstimos.
                    for (int i = 0; i < totalEmprestimos; i++) {
                        // Usa o índice armazenado no empréstimo para buscar os dados do livro.
                        int indiceLivro = emprestimos[i].indiceLivro;
                        printf("---------------------------\n");
                        printf("Emprestimo %d\n", i + 1);
                        printf("Livro: %s\n", biblioteca[indiceLivro].nome);
                        printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
                    }
                     printf("--------------------------\n");
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            }

            case 0: // Sair
                printf("Saindo do sistema...\n");
                break;

            default: // Opção Inválida
                printf("\nOpção inválida! Tente novamente.\n");
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
        }

    } while (opcao != 0);

    // Libera a memória alocada para evitar memory leaks ao final do programa.
    free(biblioteca);
    free(emprestimos);
    
    // Finaliza o programa com sucesso.
    return 0;
}