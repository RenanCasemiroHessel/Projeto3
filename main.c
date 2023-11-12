#include "proj.h"
#include <stdio.h>

int main() {
  int cod;
  ListaDeTarefas lt;

  cod = carregarLista(&lt, "arquivo");

  if (cod == 1) {
    lt.qtd = 0;
  }

  int opcao;
  do {
    printMenu();
    scanf("%d", &opcao);

    if (opcao == 1) {
      criarTarefa(&lt);
    } else if (opcao == 2) {
      deletarTarefa(&lt);
    } else if (opcao == 3) {
      listarTarefa(lt);
    } else if (opcao == 4) {
      alterarTarefa(&lt);
    } else if (opcao == 5) {
      filtrarPorPrioridade(lt);
    } else if (opcao == 6) {
      filtrarPorEstado(lt);
    } else if (opcao == 7) {
      filtrarPorCategoria(lt);
    } else if (opcao == 8) {
      filtrarPorPrioridadeECategoria(lt);
    } else if (opcao == 9) {
      exportarPorPrioridade(lt);
    } else if (opcao == 10) {
      exportarPorCategoria(lt);
    } else if (opcao == 11) {
      exportarPorPrioridadeECategoria(lt);
    }
  } while (opcao != 12);

  cod = salvarLista(lt, "arquivo");

  if (cod != 0) {
    printf("Erro ao salvar lista\n");
  }
}