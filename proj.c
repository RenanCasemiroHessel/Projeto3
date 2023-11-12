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

//A funcao apenas printa as opcoes disponiveis
void printMenu(){
    printf("1 - Criar Tarefa\n");
    printf("2 - Deletar Tarefa\n");
    printf("3 - Listar Tarefas\n");
    printf("4 - Alterar Tarefas\n");
    printf("5 - Filtrar Tarefas por Prioridade\n");
    printf("6 - Filtrar Tarefas por Estado\n");
    printf("7 - Filtrar Tarefas por Categoria\n");
    printf("8 - Filtrar Tarefas por Prioridade e Categoria\n");
    printf("9 - Exportar Tarefas por Prioridade\n");
    printf("10 - Exportar Tarefas por Categoria\n");
    printf("11 - Exportar Tarefas por Prioridade e Categoria\n");
    printf("12 - Sair\n");
    printf("Digite a opcao que voce quer executar: ");
};

//Essa funcao altera alguma tarefa ja existente
int alterarTarefa(ListaDeTarefas *lt) {
    int opcao;
    printf("Qual tarefa deseja alterar?");
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > lt->qtd) {
        printf("Numero invalido.\n");
        return 1;
    }

    printf("Escolha o campo que deseja alterar:\n");
    printf("1 - Tarefa\n");
    printf("2 - Descricao\n");
    printf("3 - Prioridade\n");
    printf("4 - Estado\n");
    printf("5 - Categoria\n");
    printf("Digite a opcao que voce quer alterar: ");

    int campo;
    scanf("%d", &campo);

    // Considerando que as entradas são válidas, solicite a nova informação
    switch (campo) {
        case 1:
            printf("Nova tarefa: ");
            scanf("%s", lt->tarefas[opcao - 1].tarefa);
            break;
        case 2:
            printf("Nova descricao: ");
            scanf("%s", lt->tarefas[opcao - 1].descricao);
            break;
        case 3:
            printf("Nova prioridade: ");
            scanf("%d", &lt->tarefas[opcao - 1].prioridade);
            break;
        case 4:
            printf("Novo estado: "); 
            scanf(" %s", lt->tarefas[opcao - 1].estado);
            break;
        case 5:
            printf("Nova categoria: ");
            scanf("%s", lt->tarefas[opcao - 1].categoria);
            break;
        default:
            printf("Opcao invalida.\n");
            return 1;
    }

    printf("Tarefa %d alterada com sucesso!\n", opcao);
    return 0;
}

//essa funcao filtra as tarefas pelo numero de prioridade digitado pelo usuario
int filtrarPorPrioridade(ListaDeTarefas lt) {
    int prioridadeFiltrada;
    printf("Digite a prioridade para filtrar: ");
    scanf("%d", &prioridadeFiltrada);

    printf("Tarefas com prioridade %d:\n", prioridadeFiltrada);

    int encontrouTarefas = 0;  // indicador para verificar se há tarefas com a prioridade filtrada

    for (int i = 0; i < lt.qtd; i++) {
        if (lt.tarefas[i].prioridade == prioridadeFiltrada) {
            printf("Tarefa %d:\n", i + 1);
            printf("Nome: %s\n", lt.tarefas[i].tarefa);
            printf("Descricao: %s\n", lt.tarefas[i].descricao);
            printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
            printf("Estado: %s\n", lt.tarefas[i].estado);
            printf("Categoria: %s\n", lt.tarefas[i].categoria);
            printf("\n");

            encontrouTarefas = 1;
        }
    }
    // Caso nao ache nenhuma tarefa com o nivel de prioridade digitado
    if (!encontrouTarefas) {
        printf("Nenhuma tarefa encontrada com prioridade %d.\n", prioridadeFiltrada);
    }

    return 0;
}
//Essa funcao compara strings e retorna um valor inteiro,  0 se forem iguais, - se a primeira string for menor e + se for maior que a segunda
int comparar_strings(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
        str1++;
        str2++;
    }
    return (*str1) - (*str2);
}

// Função para filtrar tarefas por estado
int filtrarPorEstado(ListaDeTarefas lt) {
    char estadoFiltrado[100];
    printf("Digite o estado para filtrar: ");
    scanf("%s", estadoFiltrado);

    printf("Tarefas com estado %s:\n", estadoFiltrado);

    int encontrouTarefas = 0;  // indicador para verificar se há tarefas com o estado filtrado

    for (int i = 0; i < lt.qtd; i++) {
        // Comparação manual de strings
        int j;
        for (j = 0; estadoFiltrado[j] != '\0' && lt.tarefas[i].estado[j] != '\0'; j++) {
            if (estadoFiltrado[j] != lt.tarefas[i].estado[j]) {
                break;  // laco para identificar, se houver diferença, interrompa a comparação
            }
        }

        // Verifique se a comparação foi bem-sucedida
        if (estadoFiltrado[j] == '\0' && lt.tarefas[i].estado[j] == '\0') {
            // As strings são iguais
            printf("Tarefa %d:\n", i + 1);
            printf("Nome: %s\n", lt.tarefas[i].tarefa);
            printf("Descricao: %s\n", lt.tarefas[i].descricao);
            printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
            printf("Estado: %s\n", lt.tarefas[i].estado);
            printf("Categoria: %s\n", lt.tarefas[i].categoria);
            printf("\n");

            encontrouTarefas = 1;
        }
    }

    if (!encontrouTarefas) {
        printf("Nenhuma tarefa encontrada com estado %s.\n", estadoFiltrado);
    }

    return 0;
}

int compararPrioridade(const Tarefas *a, const Tarefas *b) {
    return b->prioridade - a->prioridade;
}

// Função para filtrar tarefas por categoria e ordenar por prioridade de maior para menor
int filtrarPorCategoria(ListaDeTarefas lt) {
    char categoriaFiltrada[100];
    printf("Digite a categoria para filtrar: ");
    scanf("%s", categoriaFiltrada);

    printf("Tarefas com categoria %s (ordenadas por prioridade de maior para menor):\n", categoriaFiltrada);

    // Filtrar tarefas por categoria
    Tarefas tarefasFiltradas[100];
    int qtdFiltradas = 0;

    for (int i = 0; i < lt.qtd; i++) {
        if (comparar_strings(lt.tarefas[i].categoria, categoriaFiltrada) == 0) {
            tarefasFiltradas[qtdFiltradas] = lt.tarefas[i];
            qtdFiltradas++;
        }
    }

    // Ordenar tarefas filtradas por prioridade de maior para menor
    for (int i = 0; i < qtdFiltradas - 1; i++) {
        for (int j = 0; j < qtdFiltradas - i - 1; j++) {
            if (compararPrioridade(&tarefasFiltradas[j], &tarefasFiltradas[j + 1]) < 0) {
                // Trocar as tarefas de lugar se a prioridade for menor
                Tarefas temp = tarefasFiltradas[j];
                tarefasFiltradas[j] = tarefasFiltradas[j + 1];
                tarefasFiltradas[j + 1] = temp;
            }
        }
    }

    // loop para exibir as tarefas filtradas por categoria
    for (int i = 0; i < qtdFiltradas; i++) {
        printf("Tarefa %d:\n", i + 1);
        printf("Nome: %s\n", tarefasFiltradas[i].tarefa);
        printf("Descricao: %s\n", tarefasFiltradas[i].descricao);
        printf("Prioridade: %d\n", tarefasFiltradas[i].prioridade);
        printf("Estado: %s\n", tarefasFiltradas[i].estado);
        printf("Categoria: %s\n", tarefasFiltradas[i].categoria);
        printf("\n");
    }
    // caso nao encontre nenhuma tarefa com essa categoria
    if (qtdFiltradas == 0) {
        printf("Nenhuma tarefa encontrada com categoria %s.\n", categoriaFiltrada);
    }

    return 0;
}


// Função para filtrar tarefas por prioridade e categoria
int filtrarPorPrioridadeECategoria(ListaDeTarefas lt) {
    char categoriaFiltrada[100];
    printf("Digite a categoria para filtrar: ");
    scanf("%s", categoriaFiltrada);

    int prioridadeFiltrada;
    printf("Digite a prioridade para filtrar: ");
    scanf("%d", &prioridadeFiltrada);

    printf("Tarefas com categoria %s e prioridade %d:\n", categoriaFiltrada, prioridadeFiltrada);

    int encontrouTarefas = 0;  // indicador para verificar se há tarefas que atendem aos filtros
    //loop para listar as tarefas com a prioridade e categoria escolhida
    for (int i = 0; i < lt.qtd; i++) {
        if (comparar_strings(lt.tarefas[i].categoria, categoriaFiltrada) == 0 && lt.tarefas[i].prioridade == prioridadeFiltrada) {
            printf("Tarefa %d:\n", i + 1);
            printf("Nome: %s\n", lt.tarefas[i].tarefa);
            printf("Descricao: %s\n", lt.tarefas[i].descricao);
            printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
            printf("Estado: %s\n", lt.tarefas[i].estado);
            printf("Categoria: %s\n", lt.tarefas[i].categoria);
            printf("\n");

            encontrouTarefas = 1;
        }
    }

    if (!encontrouTarefas) {
        printf("Nenhuma tarefa encontrada com categoria %s e prioridade %d.\n", categoriaFiltrada, prioridadeFiltrada);
    }

    return 0;
}
//funcao que exporta as tarefas para um arquivo .txt por prioridade
int exportarPorPrioridade(ListaDeTarefas lt) {
    int prioridadeEscolhida;
    printf("Digite a prioridade das tarefas a serem exportadas: ");
    scanf("%d", &prioridadeEscolhida);
    // funcao que cria o arquivi .txt
    FILE *arquivo = fopen("ExportadasPrioridade.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de exportação.\n");
        return 1;
    }
    //Loop para exportar as tarefas com a prioridade escolhida 
    for (int i = 0; i < lt.qtd; i++) {
        if (lt.tarefas[i].prioridade == prioridadeEscolhida) {
            fprintf(arquivo, "Tarefa: ");
            fprintf(arquivo, "%s (", lt.tarefas[i].tarefa);
            fprintf(arquivo, "Prioridade: %d, ", lt.tarefas[i].prioridade);
            fprintf(arquivo, "Categoria: %s, ", lt.tarefas[i].categoria);
            fprintf(arquivo, "Estado: %s, ", lt.tarefas[i].estado);
            fprintf(arquivo, "Descricao: %s)\n", lt.tarefas[i].descricao);
        }
    }

    fclose(arquivo);

    printf("Tarefas com prioridade %d exportadas para o arquivo 'tarefasExportadas.txt' com sucesso.\n", prioridadeEscolhida);

    return 0;
}

// Função para exportar tarefas por categoria para um arquivo de texto
int exportarPorCategoria(ListaDeTarefas lt) {
    char categoriaEscolhida[100];
    printf("Digite a categoria das tarefas a serem exportadas: ");
    scanf("%s", categoriaEscolhida);
    // funcao que cria o arquivo .txt
    FILE *arquivo = fopen("ExportadasCategoria.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de exportação.\n");
        return 1;
    }

    // Ordenar tarefas por prioridade (usando bubble sort)
    for (int i = 0; i < lt.qtd - 1; i++) {
        for (int j = 0; j < lt.qtd - i - 1; j++) {
            if (lt.tarefas[j].prioridade < lt.tarefas[j + 1].prioridade) {
                Tarefas temp = lt.tarefas[j];
                lt.tarefas[j] = lt.tarefas[j + 1];
                lt.tarefas[j + 1] = temp;
            }
        }
    }
    //loop para exportar as tarefas com a categoria escolhida
    for (int i = 0; i < lt.qtd; i++) {
        if (comparar_strings(lt.tarefas[i].categoria, categoriaEscolhida) == 0) {
            fprintf(arquivo, "Tarefa: ");
            fprintf(arquivo, "%s (", lt.tarefas[i].tarefa);
            fprintf(arquivo, "Prioridade: %d, ", lt.tarefas[i].prioridade);
            fprintf(arquivo, "Categoria: %s, ", lt.tarefas[i].categoria);
            fprintf(arquivo, "Estado: %s, ", lt.tarefas[i].estado);
            fprintf(arquivo, "Descricao: %s)\n", lt.tarefas[i].descricao);
        }
    }

    fclose(arquivo);

    printf("Tarefas com categoria %s exportadas para o arquivo 'ExportadasCategoria.txt' com sucesso.\n", categoriaEscolhida);

    return 0;
}


// Função para exportar tarefas por prioridade e categoria para um arquivo de texto
int exportarPorPrioridadeECategoria(ListaDeTarefas lt) {
  char categoriaEscolhida[100];
  printf("Digite a categoria das tarefas a serem exportadas: ");
  scanf("%s", categoriaEscolhida);
  //pede a prioridade que deseja filtrar antes
  int prioridadeEscolhida;
  printf("Digite a prioridade das tarefas a serem exportadas: ");
  scanf("%d", &prioridadeEscolhida);
  //funcao que cria o arquivo.txt
  FILE *arquivo = fopen("ExportadasCategoriaPrioridade.txt", "w");
  if (arquivo == NULL) {
      printf("Erro ao criar o arquivo de exportação.\n");
      return 1;
  }

  // Ordenar tarefas por prioridade 
  for (int i = 0; i < lt.qtd - 1; i++) {
      for (int j = 0; j < lt.qtd - i - 1; j++) {
          if (lt.tarefas[j].prioridade < lt.tarefas[j + 1].prioridade) {
              Tarefas temp = lt.tarefas[j];
              lt.tarefas[j] = lt.tarefas[j + 1];
              lt.tarefas[j + 1] = temp;
          }
      }
  }
  //loop para exportar as tarefas que correspondam as categorias e prioridade escolhida
  for (int i = 0; i < lt.qtd; i++) {
      if (comparar_strings(lt.tarefas[i].categoria, categoriaEscolhida) == 0 &&
          lt.tarefas[i].prioridade == prioridadeEscolhida) {
          fprintf(arquivo, "Tarefa: ");
          fprintf(arquivo, "%s (", lt.tarefas[i].tarefa);
          fprintf(arquivo, "Prioridade: %d, ", lt.tarefas[i].prioridade);
          fprintf(arquivo, "Categoria: %s, ", lt.tarefas[i].categoria);
          fprintf(arquivo, "Estado: %s, ", lt.tarefas[i].estado);
          fprintf(arquivo, "Descricao: %s)\n", lt.tarefas[i].descricao);
      }
  }

  fclose(arquivo);

  printf("Tarefas com categoria %s e prioridade %d exportadas para o arquivo 'ExportadasCategoriaPrioridade.txt' com sucesso.\n", categoriaEscolhida, prioridadeEscolhida);

  return 0;
}

//Essa funcao salva as tarefas da struct em um arquivo binario
int salvarLista(ListaDeTarefas lt, char nome[]){
    FILE *arquivo = fopen(nome, "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fwrite(&lt, sizeof(ListaDeTarefas), 1, arquivo);
    fclose(arquivo);
    return 0;

}

//A funcao carrega os itens do arquivo e passa para a struct do programa
int carregarLista(ListaDeTarefas *lt, char nome[]){
    FILE *arquivo = fopen(nome, "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fread(lt, sizeof(ListaDeTarefas), 1, arquivo);
    fclose(arquivo);
    return 0;
};