#include <stdio.h>
#include "proj.h"


//Essa funcao limpa o buffer do teclado, apagando o lixo de memoria e evita bugs
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para criar uma nova tarefa
int criarTarefa(ListaDeTarefas *lt) {
    if (lt->qtd >= 100) {
        printf("A lista de tarefas está cheia. Nao eh possivel adicionar mais tarefas.\n");
        return 1;
    }

    printf("Tarefa: ");
    scanf("%s", lt->tarefas[lt->qtd].tarefa);
    limparBufferEntrada(); // Limpa o buffer após a leitura de string
    printf("Descricao da Tarefa: ");
    scanf("%s", lt->tarefas[lt->qtd].descricao);
    limparBufferEntrada(); // Limpa o buffer após a leitura de string
    printf("Prioridade da Tarefa: ");
    scanf("%d", &lt->tarefas[lt->qtd].prioridade);
    limparBufferEntrada(); // Limpa o buffer após a leitura de string

  
    int estadoValido = 0;
    do {
        char estadoEscolhido[100];
        printf("Estado da Tarefa (completo, em andamento ou nao iniciado): ");
        scanf(" %[^\n]s", estadoEscolhido);
        limparBufferEntrada(); // Limpa o buffer após a leitura de string

        int completo = 1, andamento = 1, naoIniciado = 1;
        int estadoLen = 0;
        while (estadoEscolhido[estadoLen] != '\0') {
            estadoLen++;
        }
        //Esse laco verifica se o estado escolhido eh valido
        for (int i = 0; i < estadoLen; i++) {
            if (estadoEscolhido[i] != "completo"[i]) {
                completo = 0;
            }
            if (estadoEscolhido[i] != "em andamento"[i]) {
                andamento = 0;
            }
            if (estadoEscolhido[i] != "nao iniciado"[i]) {
                naoIniciado = 0;
            }
        }
        //Se o estado escolhido for valido, o estado da tarefa eh atualizado
        if (completo || andamento || naoIniciado) {
            for (int i = 0; i < estadoLen; i++) {
                lt->tarefas[lt->qtd].estado[i] = estadoEscolhido[i];
            }
            estadoValido = 1;
        } else {
            printf("Opção invalida. Insira uma opcao valida (completo, em andamento ou nao iniciado).\n");
        }
    } while (!estadoValido);

    printf("Categoria da Tarefa: ");
    scanf("%s", lt->tarefas[lt->qtd].categoria);
    limparBufferEntrada(); // Limpa o buffer após a leitura de string
    printf("\n");
    lt->qtd += 1;
    return 0;
}

//Essa funcao exclui as tarefas que foram criadas anteriormente
int deletarTarefa(ListaDeTarefas *lt){
    int opcao;
    printf("Qual tarefa deseja deletar?");
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > lt->qtd) {
        printf("Numero invalido.\n");
        return 1;
    }
    //Esse laço sobrescreve a tarefa que deseja excluir pela proxima tarefa na lista
    for (int i = opcao - 1; i < lt->qtd - 1; i++) {
        lt->tarefas[i] = lt->tarefas[i + 1];
    }

    lt->qtd--;
    printf("Tarefa %d excluida com sucesso!\n", opcao);
    return 0;
};

//Essa funcao lista as tarefas presentes na struct ListaDeTarefas
int listarTarefa(ListaDeTarefas lt){
    for (int i = 0; i < lt.qtd; i++){
        printf("Tarefa %d:\n", i + 1);
        printf("Nome: %s\n", lt.tarefas[i].tarefa);
        printf("Descricao: %s\n", lt.tarefas[i].descricao);
        printf("Prioridade: %d\n" , lt.tarefas[i].prioridade);
        printf("Estado: %s\n", lt.tarefas[i].estado);
        printf("Categoria: %s\n", lt.tarefas[i].categoria);
        printf("\n");
    }
    return 0;
};
