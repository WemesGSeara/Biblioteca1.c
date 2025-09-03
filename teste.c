#include <stdio.h>
#include <stdlib.h> // A biblioteca onde vive o calloc!

int main() {
    int *notas_da_turma;
    int quantidade_de_alunos;

    printf("Digite a quantidade de alunos na turma: ");
    scanf("%d", &quantidade_de_alunos);

    // --- A MÁGICA DO CALLOC ACONTECE AQUI ---
    // Pedindo ao "engenheiro" um terreno para 'quantidade_de_alunos' casas do tipo 'int'.
    notas_da_turma = (int*) calloc(quantidade_de_alunos, sizeof(int));

    // --- VERIFICAÇÃO DE SEGURANÇA ---
    // Checando se o engenheiro conseguiu o terreno.
    if (notas_da_turma == NULL) {
        printf("Erro! Falha ao alocar memória. Memória insuficiente.\n");
        return 1; // Encerra o programa indicando um erro.
    }

    printf("\nMemória alocada com sucesso! Vamos inserir as notas.\n");

    // Usando a memória alocada como se fosse um array normal
    for (int i = 0; i < quantidade_de_alunos; i++) {
        printf("Digite a nota do aluno %d: ", i + 1);
        scanf("%d", &notas_da_turma[i]);
    }

    printf("\n--- Notas da Turma ---\n");
    for (int i = 0; i < quantidade_de_alunos; i++) {
        printf("Aluno %d: Nota %d\n", i + 1, notas_da_turma[i]);
    }


    // --- A PARTE MAIS IMPORTANTE: A LIMPEZA ---
    // Depois de usar o terreno, você DEVE devolvê-lo ao sistema.
    free(notas_da_turma);
    printf("\nMemória liberada com sucesso!\n");


    return 0;
}