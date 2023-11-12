
typedef struct {
  int prioridade;
  char tarefa[300];
  char descricao[100];
  char estado[100];
  char categoria[100];
} Tarefas;

typedef struct {
  Tarefas tarefas[100];
  int qtd;
} ListaDeTarefas;

int criarTarefa(ListaDeTarefas *lt);

int deletarTarefa(ListaDeTarefas *lt);

int listarTarefa(ListaDeTarefas lt);

void printMenu();

int salvarLista(ListaDeTarefas lt, char nome[]);

int carregarLista(ListaDeTarefas *lt, char nome[]);

int alterarTarefa(ListaDeTarefas *lt);

int filtrarPorPrioridade(ListaDeTarefas lt);

int filtrarPorEstado(ListaDeTarefas lt);

int filtrarPorPrioridadeECategoria(ListaDeTarefas lt);

int filtrarPorCategoria(ListaDeTarefas lt);

int exportarPorPrioridade(ListaDeTarefas lt);

int exportarPorCategoria(ListaDeTarefas lt);

int exportarPorPrioridadeECategoria(ListaDeTarefas lt);
