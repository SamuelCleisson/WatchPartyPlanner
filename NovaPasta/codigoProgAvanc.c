#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 50

typedef struct {
  int idJogador;
  char nomeCompleto[100];
  char apelido[50];
  char email[100];
  char telefone[20];
  char generoPreferido[50];
  char contribuicaoLanche[100];
  int totalPresencas;
  float taxaVitorias;
  char notasObservacao[200];
} Jogador;

typedef struct {
  int idJogo;
  char titulo[100];
  int idDono;
  char genero[50];
  char plataforma[50];
  int minJogadores;
  int maxJogadores;
  int tempoMedioMinutos;
  float avaliacaoGrupo;
  int anoLancamento;
} Jogo;

typedef struct {
  int idSessao;
  char nomeEvento[100];
  char data[15];
  char horarioInicio[6];
  int idLocal;
  int idAnfitriao;
  int idJogoPrincipal;
  int confirmados[20];
  int numConfirmados;
  char status[50];
} SessaoDeJogo;

typedef struct {
  int idPartida;
  int idSessaoAssociada;
  int idJogo;
  int participantes[20];
  int numParticipantes;
  int idVencedor;
  char pontuacaoFinal[200];
  int duracaoMinutos;
} Partida;

typedef struct {
  int idAvaliacao;
  int idJogoAvaliado;
  int idJogadorAvaliador;
  float nota;
  char dataAvaliacao[15];
  char comentario[500];
  int recomendaria;
  int ehAnonima;
} Avaliacao;

typedef struct {
  int idExpansao;
  int idJogoBase;
  char tituloExpansao[100];
  int idDono;
  int anoLancamento;
  char oQueAdiciona[200];
  int integraComOutrasExpansoes;
  int requerJogoBase;
} Expansao;

typedef struct {
  int idCardapioItem;
  int idSessaoAssociada;
  int idJogadorResponsavel;
  char nomeItem[100];
  char quantidade[50];
  char categoria[50];
  char notasAdicionais[200];
  char status[50];
} CardapioItem;

typedef struct {
  int idCampanha;
  char nomeCampanha[100];
  int idJogoPrincipal;
  char descricao[300];
  int sessoesDaCampanha[15];
  int numSessoes;
  char status[50];
  int idMestreDaCampanha;
} Campanha;

typedef struct {
  int idVotacao;
  int idSessaoAssociada;
  char pergunta[200];
  char opcoesTexto[5][100];
  int numOpcoes;
  int votosPorOpcao[5];
  int votantes[20];
  int numVotantes;
  char status[50];
  char dataEncerramento[15];
} Votacao;

typedef struct {
  int idLocal;
  char nomeLocal[100];
  char enderecoCompleto[200];
  int idAnfitriaoPadrao;
  char notas[300];
  int capacidadeMaxima;
  char regrasDaCasa[200];
  char telefoneContato[20];
} Local;

Jogador listaJogadores[MAX_ITENS];
int numJogadores = 0;

Jogo listaJogos[MAX_ITENS];
int numJogos = 0;

SessaoDeJogo listaSessoes[MAX_ITENS];
int numSessoes = 0;

Partida listaPartidas[MAX_ITENS];
int numPartidas = 0;

Avaliacao listaAvaliacoes[MAX_ITENS];
int numAvaliacoes = 0;

Expansao listaExpansoes[MAX_ITENS];
int numExpansoes = 0;

CardapioItem listaCardapio[MAX_ITENS * 5];
int numCardapioItens = 0;

Campanha listaCampanhas[MAX_ITENS];
int numCampanhas = 0;

Votacao listaVotacoes[MAX_ITENS];
int numVotacoes = 0;

Local listaLocais[MAX_ITENS];
int numLocais = 0;

void exibirMenuPrincipal();
void gerenciarJogadores();
void cadastrarJogador();
void listarJogadoresDetalhado();
void gerenciarCatalogo();
void cadastrarJogoBase();
void cadastrarExpansao();
void listarCatalogoDetalhado();
void gerenciarSessoes();
void agendarNovaSessao();
void listarSessoesDetalhado();
void gerenciarCampanhas();
void criarNovaCampanha();
void listarCampanhasDetalhado();
void adicionarSessaoACampanha();
void gerenciarLocais();
void cadastrarNovoLocal();
void listarLocaisDetalhado();
void registrarPartida();
void avaliarJogo();
void gerenciarVotacoes();
void criarNovaVotacao();
void listarVotacoesAbertas();
void votarEmEnquete();
void verResultadosVotacao();
void gerenciarCardapio();
void adicionarItemAoCardapio();
void verCardapioDaSessao();
int lerInteiro(const char *prompt);
float lerFloat(const char *prompt);
void limparBuffer();
void pressionarEnterParaContinuar();
void removerNovaLinha(char *str);
const char *buscarApelidoJogadorPorId(int jogadorId);
const char *buscarTituloJogoPorId(int jogoId);
const char *buscarNomeLocalPorId(int localId);
void listarJogadoresSimples();
void listarJogosSimples();
void listarExpansoesSimples();
void listarSessoesSimples();
void listarCampanhasSimples();
void listarLocaisSimples();

int main() {
  int opcao;
  printf("Bem-vindo ao Game Night Planner!\n");
  do {
    exibirMenuPrincipal();
    if (scanf("%d", &opcao) != 1) {
      opcao = -1;
    }
    limparBuffer();

    switch (opcao) {
    case 1:
      gerenciarJogadores();
      break;
    case 2:
      gerenciarCatalogo();
      break;
    case 3:
      gerenciarLocais();
      break;
    case 4:
      gerenciarSessoes();
      break;
    case 5:
      gerenciarCampanhas();
      break;
    case 6:
      registrarPartida();
      break;
    case 7:
      avaliarJogo();
      break;
    case 8:
      gerenciarVotacoes();
      break;
    case 9:
      gerenciarCardapio();
      break;
    case 10:
      printf("\nSaindo do sistema... Ate mais!\n");
      break;
    default:
      printf("\nOpcao invalida! Pressione Enter para tentar novamente.\n");
      pressionarEnterParaContinuar();
      break;
    }
  } while (opcao != 10);
  return 0;
}

void exibirMenuPrincipal() {
  printf("\n+----------------------------------------+\n");
  printf("|        GAME NIGHT PLANNER v1.0         |\n");
  printf("+----------------------------------------+\n");
  printf("| [ 1 ] Gerenciar Jogadores              |\n");
  printf("| [ 2 ] Gerenciar Catalogo de Jogos      |\n");
  printf("| [ 3 ] Gerenciar Locais                 |\n");
  printf("| [ 4 ] Gerenciar Sessoes                |\n");
  printf("| [ 5 ] Gerenciar Campanhas              |\n");
  printf("| [ 6 ] Registrar Partida Realizada      |\n");
  printf("| [ 7 ] Avaliar um Jogo                  |\n");
  printf("| [ 8 ] Gerenciar Votacoes               |\n");
  printf("| [ 9 ] Gerenciar Cardapio de uma Sessao |\n");
  printf("| [ 10 ] Sair do Programa                |\n");
  printf("+----------------------------------------+\n");
  printf("Escolha uma opcao: ");
}

void gerenciarJogadores() {
  int subOpcao;
  do {
    printf("\n--- Gerenciar Jogadores ---\n");
    printf("[1] Cadastrar Novo Jogador\n");
    printf("[2] Listar Jogadores (Detalhado)\n");
    printf("[3] Voltar ao Menu Principal\n");
    printf("Escolha uma opcao: ");
    if (scanf("%d", &subOpcao) != 1) {
      subOpcao = -1;
    }
    limparBuffer();
    switch (subOpcao) {
    case 1:
      cadastrarJogador();
      break;
    case 2:
      listarJogadoresDetalhado();
      break;
    case 3:
      printf("\nRetornando ao menu principal...\n");
      break;
    default:
      printf("\nOpcao invalida!\n");
      break;
    }
    if (subOpcao != 3)
      pressionarEnterParaContinuar();
  } while (subOpcao != 3);
}

void cadastrarJogador() {
  if (numJogadores >= MAX_ITENS) {
    printf(
        "\nNao e possivel cadastrar mais jogadores. Limite maximo atingido.\n");
    return;
  }
  printf("\n>> Cadastrando Novo Jogador...\n");
  Jogador novoJogador;
  novoJogador.idJogador = numJogadores + 1;
  printf("Nome Completo: ");
  fgets(novoJogador.nomeCompleto, 100, stdin);
  removerNovaLinha(novoJogador.nomeCompleto);
  printf("Apelido: ");
  fgets(novoJogador.apelido, 50, stdin);
  removerNovaLinha(novoJogador.apelido);
  printf("Email: ");
  fgets(novoJogador.email, 100, stdin);
  removerNovaLinha(novoJogador.email);
  printf("Telefone: ");
  fgets(novoJogador.telefone, 20, stdin);
  removerNovaLinha(novoJogador.telefone);
  printf("Genero de Jogo Preferido: ");
  fgets(novoJogador.generoPreferido, 50, stdin);
  removerNovaLinha(novoJogador.generoPreferido);
  printf("Contribuicao de Lanche Comum: ");
  fgets(novoJogador.contribuicaoLanche, 100, stdin);
  removerNovaLinha(novoJogador.contribuicaoLanche);
  printf("Notas/Observacoes: ");
  fgets(novoJogador.notasObservacao, 200, stdin);
  removerNovaLinha(novoJogador.notasObservacao);
  novoJogador.totalPresencas = 0;
  novoJogador.taxaVitorias = 0.0f;
  listaJogadores[numJogadores] = novoJogador;
  numJogadores++;
  printf("\nJogador '%s' cadastrado com sucesso com o ID %d!\n",
         novoJogador.apelido, novoJogador.idJogador);
}

void listarJogadoresDetalhado() {
  printf("\n--- Lista Detalhada de Jogadores ---\n");
  if (numJogadores == 0) {
    printf("Nenhum jogador cadastrado no sistema.\n");
    return;
  }
  for (int i = 0; i < numJogadores; i++) {
    Jogador jogador = listaJogadores[i];
    printf("----------------------------------\n");
    printf("ID:                  %d\n", jogador.idJogador);
    printf("Nome Completo:       %s\n", jogador.nomeCompleto);
    printf("Apelido:             %s\n", jogador.apelido);
    printf("Email:               %s\n", jogador.email);
    printf("Telefone:            %s\n", jogador.telefone);
    printf("Genero Preferido:    %s\n", jogador.generoPreferido);
    printf("Contribuicao Comum:  %s\n", jogador.contribuicaoLanche);
    printf("Observacoes:         %s\n", jogador.notasObservacao);
    printf("Total de Presencas:  %d\n", jogador.totalPresencas);
    printf("Taxa de Vitorias:    %.2f%%\n", jogador.taxaVitorias);
  }
  printf("----------------------------------\n");
}

void gerenciarCatalogo() {
  int subOpcao;
  do {
    printf("\n--- Gerenciar Catalogo de Jogos ---\n");
    printf("[1] Cadastrar Novo Jogo Base\n");
    printf("[2] Adicionar Expansao a um Jogo\n");
    printf("[3] Listar Catalogo (Detalhado)\n");
    printf("[4] Voltar ao Menu Principal\n");
    printf("Escolha uma opcao: ");
    if (scanf("%d", &subOpcao) != 1) {
      subOpcao = -1;
    }
    limparBuffer();
    switch (subOpcao) {
    case 1:
      cadastrarJogoBase();
      break;
    case 2:
      cadastrarExpansao();
      break;
    case 3:
      listarCatalogoDetalhado();
      break;
    case 4:
      printf("\nRetornando ao menu principal...\n");
      break;
    default:
      printf("\nOpcao invalida!\n");
      break;
    }
    if (subOpcao != 4)
      pressionarEnterParaContinuar();
  } while (subOpcao != 4);
}

void cadastrarJogoBase() {
  if (numJogos >= MAX_ITENS) {
    printf("\nNao e possivel cadastrar mais jogos. Limite maximo atingido.\n");
    return;
  }
  if (numJogadores == 0) {
    printf("\nErro: E necessario cadastrar ao menos um jogador para ser o dono do jogo.\n");
    return;
  }

  printf("\n>> Cadastrando Novo Jogo Base...\n");
  Jogo novoJogo;
  novoJogo.idJogo = numJogos + 1;

  printf("Titulo do Jogo: ");
  fgets(novoJogo.titulo, 100, stdin);
  removerNovaLinha(novoJogo.titulo);

  printf("Genero: ");
  fgets(novoJogo.genero, 50, stdin);
  removerNovaLinha(novoJogo.genero);

  printf("Plataforma (PC, PS5, Tabuleiro, etc.): ");
  fgets(novoJogo.plataforma, 50, stdin);
  removerNovaLinha(novoJogo.plataforma);

  do {
    novoJogo.minJogadores = lerInteiro("Numero minimo de jogadores: ");
    if (novoJogo.minJogadores <= 0) {
        printf("Erro: O numero minimo deve ser pelo menos 1.\n");
    }
  } while (novoJogo.minJogadores <= 0);

  do {
    novoJogo.maxJogadores = lerInteiro("Numero maximo de jogadores: ");
    if (novoJogo.maxJogadores < novoJogo.minJogadores) {
        printf("Erro: O numero maximo (%d) nao pode ser menor que o minimo (%d).\n", 
               novoJogo.maxJogadores, novoJogo.minJogadores);
    }
  } while (novoJogo.maxJogadores < novoJogo.minJogadores);

  do {
    novoJogo.tempoMedioMinutos = lerInteiro("Tempo medio de partida (minutos): ");
    if (novoJogo.tempoMedioMinutos <= 0) {
        printf("Erro: O tempo medio deve ser maior que 0.\n");
    }
  } while (novoJogo.tempoMedioMinutos <= 0);

  novoJogo.anoLancamento = lerInteiro("Ano de lancamento: ");

  listarJogadoresSimples();

  int donoValido = 0;
  do {
    novoJogo.idDono = lerInteiro("Digite o ID do Dono do Jogo: ");

    if (strcmp(buscarApelidoJogadorPorId(novoJogo.idDono), "Nao encontrado") != 0) {
        donoValido = 1;
    } else {
        printf("Erro: Jogador com ID %d nao encontrado. Tente novamente.\n", novoJogo.idDono);
    }
  } while (!donoValido);

  novoJogo.avaliacaoGrupo = 0.0f;
  listaJogos[numJogos] = novoJogo;
  numJogos++;
  printf("\nJogo '%s' cadastrado com sucesso com o ID %d!\n", novoJogo.titulo,
         novoJogo.idJogo);
}

void cadastrarExpansao() {
  if (numExpansoes >= MAX_ITENS) {
    printf("\nNao e possivel cadastrar mais expansoes. Limite maximo atingido.\n");
    return;
  }
  if (numJogos == 0) {
    printf("\nErro: E necessario cadastrar um jogo base antes de adicionar uma expansao.\n");
    return;
  }

  printf("\n>> Cadastrando Novo Expansao...\n");
  Expansao novaExpansao;
  novaExpansao.idExpansao = numExpansoes + 1;

  int jogoValido = 0;
  do {
    listarJogosSimples();
    novaExpansao.idJogoBase = lerInteiro("Digite o ID do Jogo Base para esta expansao: ");

    if (strcmp(buscarTituloJogoPorId(novaExpansao.idJogoBase), "Jogo base nao encontrado") != 0) {
        jogoValido = 1;
    } else {
        printf("Erro: Jogo com ID %d nao encontrado. Tente novamente.\n", novaExpansao.idJogoBase);
    }
  } while (!jogoValido);

  printf("Titulo da Expansao: ");
  fgets(novaExpansao.tituloExpansao, 100, stdin);
  removerNovaLinha(novaExpansao.tituloExpansao);

  printf("O que a expansao adiciona (resumo): ");
  fgets(novaExpansao.oQueAdiciona, 200, stdin);
  removerNovaLinha(novaExpansao.oQueAdiciona);

  int donoValido = 0;
  do {
    listarJogadoresSimples();
    novaExpansao.idDono = lerInteiro("Digite o ID do Dono da Expansao: ");
    if (strcmp(buscarApelidoJogadorPorId(novaExpansao.idDono), "Nao encontrado") != 0) {
        donoValido = 1;
    } else {
        printf("Erro: Jogador com ID %d nao encontrado.\n", novaExpansao.idDono);
    }
  } while (!donoValido);

  novaExpansao.anoLancamento = lerInteiro("Ano de lancamento da expansao: ");

  do {
    novaExpansao.requerJogoBase = lerInteiro("Requer o jogo base para jogar? (1=Sim, 0=Nao): ");
    if (novaExpansao.requerJogoBase < 0 || novaExpansao.requerJogoBase > 1) {
        printf("Erro: Opcao invalida. Digite 1 para Sim ou 0 para Nao.\n");
    }
  } while (novaExpansao.requerJogoBase < 0 || novaExpansao.requerJogoBase > 1);

  do {
    novaExpansao.integraComOutrasExpansoes = lerInteiro("Integra com outras expansoes? (1=Sim, 0=Nao): ");
    if (novaExpansao.integraComOutrasExpansoes < 0 || novaExpansao.integraComOutrasExpansoes > 1) {
        printf("Erro: Opcao invalida. Digite 1 para Sim ou 0 para Nao.\n");
    }
  } while (novaExpansao.integraComOutrasExpansoes < 0 || novaExpansao.integraComOutrasExpansoes > 1);

  listaExpansoes[numExpansoes] = novaExpansao;
  numExpansoes++;
  printf("\nExpansao '%s' cadastrada com sucesso!\n", novaExpansao.tituloExpansao);
}

void listarCatalogoDetalhado() {
  printf("\n--- Catalogo Detalhado de Jogos e Expansoes ---\n");
  printf("\n--- JOGOS BASE ---\n");
  if (numJogos == 0) {
    printf("Nenhum jogo base cadastrado.\n");
  } else {
    for (int i = 0; i < numJogos; i++) {
      Jogo jogo = listaJogos[i];
      printf("----------------------------------\n");
      printf("ID do Jogo:          %d\n", jogo.idJogo);
      printf("Titulo:              %s\n", jogo.titulo);
      printf("Dono:                ID %d (%s)\n", jogo.idDono,
             buscarApelidoJogadorPorId(jogo.idDono));
      printf("Genero:              %s\n", jogo.genero);
      printf("Plataforma:          %s\n", jogo.plataforma);
      printf("Jogadores:           %d a %d\n", jogo.minJogadores,
             jogo.maxJogadores);
      printf("Tempo Medio:         %d min\n", jogo.tempoMedioMinutos);
      printf("Ano:                 %d\n", jogo.anoLancamento);
      printf("Avaliacao do Grupo:  %.1f / 10.0\n", jogo.avaliacaoGrupo);
    }
  }
  printf("\n--- EXPANSOES ---\n");
  if (numExpansoes == 0) {
    printf("Nenhuma expansao cadastrada.\n");
  } else {
    for (int i = 0; i < numExpansoes; i++) {
      Expansao exp = listaExpansoes[i];
      printf("----------------------------------\n");
      printf("ID da Expansao:      %d\n", exp.idExpansao);
      printf("Titulo:              %s\n", exp.tituloExpansao);
      printf("Expansao para:       ID %d (%s)\n", exp.idJogoBase,
             buscarTituloJogoPorId(exp.idJogoBase));
      printf("Dono:                ID %d (%s)\n", exp.idDono,
             buscarApelidoJogadorPorId(exp.idDono));
      printf("Adiciona:            %s\n", exp.oQueAdiciona);
    }
  }
  printf("----------------------------------\n");
}

void gerenciarSessoes() {
  int subOpcao;
  do {
    printf("\n--- Gerenciar Sessoes de Jogo ---\n");
    printf("[1] Agendar Nova Sessao\n");
    printf("[2] Listar Sessoes Agendadas (Detalhado)\n");
    printf("[3] Voltar ao Menu Principal\n");
    printf("Escolha uma opcao: ");
    if (scanf("%d", &subOpcao) != 1) {
      subOpcao = -1;
    }
    limparBuffer();
    switch (subOpcao) {
    case 1:
      agendarNovaSessao();
      break;
    case 2:
      listarSessoesDetalhado();
      break;
    case 3:
      printf("\nRetornando ao menu principal...\n");
      break;
    default:
      printf("\nOpcao invalida!\n");
      break;
    }
    if (subOpcao != 3)
      pressionarEnterParaContinuar();
  } while (subOpcao != 3);
}

void agendarNovaSessao() {
  if (numSessoes >= MAX_ITENS) {
    printf("\nNao e possivel agendar mais sessoes. Limite maximo atingido.\n");
    return;
  }
  if (numJogadores == 0 || numJogos == 0 || numLocais == 0) {
    printf("\nErro: E necessario ter ao menos um Jogador, Jogo e Local cadastrado para agendar uma sessao.\n");
    return;
  }

  printf("\n>> Agendando Nova Sessao de Jogo...\n");
  SessaoDeJogo novaSessao;
  novaSessao.idSessao = numSessoes + 1;

  printf("Nome do Evento: ");
  fgets(novaSessao.nomeEvento, 100, stdin);
  removerNovaLinha(novaSessao.nomeEvento);

  printf("Data (DD/MM/AAAA): ");
  fgets(novaSessao.data, 15, stdin);
  removerNovaLinha(novaSessao.data);

  printf("Horario de Inicio (HH:MM): ");
  fgets(novaSessao.horarioInicio, 6, stdin);
  removerNovaLinha(novaSessao.horarioInicio);

  int localValido = 0;
  do {
    listarLocaisSimples();
    novaSessao.idLocal = lerInteiro("Digite o ID do Local do evento: ");

    if (strcmp(buscarNomeLocalPorId(novaSessao.idLocal), "Local nao encontrado") != 0) {
        localValido = 1;
    } else {
        printf("Erro: Local com ID %d nao encontrado. Tente novamente.\n", novaSessao.idLocal);
    }
  } while (!localValido);

  int anfitriaoValido = 0;
  do {
    listarJogadoresSimples();
    novaSessao.idAnfitriao = lerInteiro("Digite o ID do Anfitriao: ");

    if (strcmp(buscarApelidoJogadorPorId(novaSessao.idAnfitriao), "Nao encontrado") != 0) {
        anfitriaoValido = 1;
    } else {
        printf("Erro: Jogador com ID %d nao encontrado. Tente novamente.\n", novaSessao.idAnfitriao);
    }
  } while (!anfitriaoValido);

  int jogoValido = 0;
  do {
    listarJogosSimples();
    novaSessao.idJogoPrincipal = lerInteiro("Digite o ID do Jogo Principal: ");

    if (strcmp(buscarTituloJogoPorId(novaSessao.idJogoPrincipal), "Jogo base nao encontrado") != 0) {
        jogoValido = 1;
    } else {
        printf("Erro: Jogo com ID %d nao encontrado. Tente novamente.\n", novaSessao.idJogoPrincipal);
    }
  } while (!jogoValido);

  strcpy(novaSessao.status, "Planejada");
  novaSessao.numConfirmados = 0;
  listaSessoes[numSessoes] = novaSessao;
  numSessoes++;
  printf("\nSessao '%s' agendada com sucesso com o ID %d!\n",
         novaSessao.nomeEvento, novaSessao.idSessao);
}

void listarSessoesDetalhado() {
  printf("\n--- Lista Detalhada de Sessoes Agendadas ---\n");
  if (numSessoes == 0) {
    printf("Nenhuma sessao agendada no momento.\n");
    return;
  }
  for (int i = 0; i < numSessoes; i++) {
    SessaoDeJogo sessao = listaSessoes[i];
    printf("----------------------------------\n");
    printf("ID da Sessao:        %d\n", sessao.idSessao);
    printf("Evento:              %s\n", sessao.nomeEvento);
    printf("Data e Hora:         %s as %s\n", sessao.data,
           sessao.horarioInicio);
    printf("Status:              %s\n", sessao.status);
    printf("Local:               ID %d (%s)\n", sessao.idLocal,
           buscarNomeLocalPorId(sessao.idLocal));
    printf("Anfitriao:           ID %d (%s)\n", sessao.idAnfitriao,
           buscarApelidoJogadorPorId(sessao.idAnfitriao));
    printf("Jogo Principal:      ID %d (%s)\n", sessao.idJogoPrincipal,
           buscarTituloJogoPorId(sessao.idJogoPrincipal));
    printf("Jogadores Confirmados: %d\n", sessao.numConfirmados);
  }
  printf("----------------------------------\n");
}

void gerenciarCampanhas() {
  int subOpcao;
  do {
    printf("\n--- Gerenciar Campanhas ---\n");
    printf("[1] Criar Nova Campanha\n");
    printf("[2] Listar Campanhas (Detalhado)\n");
    printf("[3] Adicionar Sessao a uma Campanha\n");
    printf("[4] Voltar ao Menu Principal\n");
    printf("Escolha uma opcao: ");
    if (scanf("%d", &subOpcao) != 1) {
      subOpcao = -1;
    }
    limparBuffer();
    switch (subOpcao) {
    case 1:
      criarNovaCampanha();
      break;
    case 2:
      listarCampanhasDetalhado();
      break;
    case 3:
      adicionarSessaoACampanha();
      break;
    case 4:
      printf("\nRetornando ao menu principal...\n");
      break;
    default:
      printf("\nOpcao invalida!\n");
      break;
    }
    if (subOpcao != 4)
      pressionarEnterParaContinuar();
  } while (subOpcao != 4);
}

void criarNovaCampanha() {
  if (numCampanhas >= MAX_ITENS) {
    printf("\nNao e possivel criar mais campanhas. Limite maximo atingido.\n");
    return;
  }
  if (numJogadores == 0 || numJogos == 0) {
    printf("\nErro: E necessario ter ao menos um Jogador (para ser o mestre) e um Jogo cadastrado.\n");
    return;
  }

  printf("\n>> Criando Nova Campanha...\n");
  Campanha novaCampanha;
  novaCampanha.idCampanha = numCampanhas + 1;

  printf("Nome da Campanha: ");
  fgets(novaCampanha.nomeCampanha, 100, stdin);
  removerNovaLinha(novaCampanha.nomeCampanha);

  printf("Breve descricao da Campanha: ");
  fgets(novaCampanha.descricao, 300, stdin);
  removerNovaLinha(novaCampanha.descricao);

  int jogoValido = 0;
  do {
    listarJogosSimples();
    novaCampanha.idJogoPrincipal = lerInteiro("Digite o ID do Jogo Principal da Campanha: ");

    if (strcmp(buscarTituloJogoPorId(novaCampanha.idJogoPrincipal), "Jogo base nao encontrado") != 0) {
        jogoValido = 1;
    } else {
        printf("Erro: Jogo com ID %d nao encontrado. Tente novamente.\n", novaCampanha.idJogoPrincipal);
    }
  } while (!jogoValido);

  int mestreValido = 0;
  do {
    listarJogadoresSimples();
    novaCampanha.idMestreDaCampanha = lerInteiro("Digite o ID do Jogador que sera o Mestre/Organizador: ");

    if (strcmp(buscarApelidoJogadorPorId(novaCampanha.idMestreDaCampanha), "Nao encontrado") != 0) {
        mestreValido = 1;
    } else {
        printf("Erro: Jogador com ID %d nao encontrado. Tente novamente.\n", novaCampanha.idMestreDaCampanha);
    }
  } while (!mestreValido);

  strcpy(novaCampanha.status, "Em Andamento");
  novaCampanha.numSessoes = 0;
  listaCampanhas[numCampanhas] = novaCampanha;
  numCampanhas++;
  printf("\nCampanha '%s' criada com sucesso com o ID %d!\n",
         novaCampanha.nomeCampanha, novaCampanha.idCampanha);
}

void listarCampanhasDetalhado() {
  printf("\n--- Lista Detalhada de Campanhas ---\n");
  if (numCampanhas == 0) {
    printf("Nenhuma campanha criada no momento.\n");
    return;
  }
  for (int i = 0; i < numCampanhas; i++) {
    Campanha campanha = listaCampanhas[i];
    printf("----------------------------------\n");
    printf("ID da Campanha:      %d\n", campanha.idCampanha);
    printf("Nome:                %s\n", campanha.nomeCampanha);
    printf("Descricao:           %s\n", campanha.descricao);
    printf("Status:              %s\n", campanha.status);
    printf("Jogo Principal:      ID %d (%s)\n", campanha.idJogoPrincipal,
           buscarTituloJogoPorId(campanha.idJogoPrincipal));
    printf("Mestre/Organizador:  ID %d (%s)\n", campanha.idMestreDaCampanha,
           buscarApelidoJogadorPorId(campanha.idMestreDaCampanha));
    printf("Sessoes Registradas: %d\n", campanha.numSessoes);
    if (campanha.numSessoes > 0) {
      printf("IDs das Sessoes:     ");
      for (int j = 0; j < campanha.numSessoes; j++) {
        printf("%d ", campanha.sessoesDaCampanha[j]);
      }
      printf("\n");
    }
  }
  printf("----------------------------------\n");
}

void adicionarSessaoACampanha() {
  if (numCampanhas == 0 || numSessoes == 0) {
    printf("\nErro: E necessario ter ao menos uma campanha e uma sessao para fazer a vinculacao.\n");
    return;
  }

  printf("\n>> Vinculando Sessao a uma Campanha...\n");
  int idCampanha, idSessao;
  int indiceCampanha = -1;

  do {
    listarCampanhasSimples();
    idCampanha = lerInteiro("Digite o ID da Campanha: ");

    indiceCampanha = -1;
    for (int i = 0; i < numCampanhas; i++) {
      if (listaCampanhas[i].idCampanha == idCampanha) {
        indiceCampanha = i;
        break;
      }
    }

    if (indiceCampanha == -1) {
        printf("Erro: Campanha com ID %d nao encontrada. Tente novamente.\n", idCampanha);
    }
  } while (indiceCampanha == -1);

  int sessaoEncontrada = 0;
  do {
    listarSessoesSimples();
    idSessao = lerInteiro("Digite o ID da Sessao a ser adicionada: ");

    sessaoEncontrada = 0;
    for (int i = 0; i < numSessoes; i++) {
        if (listaSessoes[i].idSessao == idSessao) {
            sessaoEncontrada = 1;
            break;
        }
    }

    if (!sessaoEncontrada) {
        printf("Erro: Sessao com ID %d nao encontrada. Tente novamente.\n", idSessao);
    }
  } while (!sessaoEncontrada);

  if (listaCampanhas[indiceCampanha].numSessoes < 15) {
    listaCampanhas[indiceCampanha]
        .sessoesDaCampanha[listaCampanhas[indiceCampanha].numSessoes] = idSessao;
    listaCampanhas[indiceCampanha].numSessoes++;
    printf("\nSessao %d adicionada a campanha '%s' com sucesso!\n", idSessao,
           listaCampanhas[indiceCampanha].nomeCampanha);
  } else {
    printf("\nErro: Esta campanha ja atingiu o numero maximo de sessoes (15).\n");
  }
}

void gerenciarLocais() {
  int subOpcao;
  do {
    printf("\n--- Gerenciar Locais de Encontro ---\n");
    printf("[1] Cadastrar Novo Local\n");
    printf("[2] Listar Locais Cadastrados (Detalhado)\n");
    printf("[3] Voltar ao Menu Principal\n");
    printf("Escolha uma opcao: ");
    if (scanf("%d", &subOpcao) != 1) {
      subOpcao = -1;
    }
    limparBuffer();
    switch (subOpcao) {
    case 1:
      cadastrarNovoLocal();
      break;
    case 2:
      listarLocaisDetalhado();
      break;
    case 3:
      printf("\nRetornando ao menu principal...\n");
      break;
    default:
      printf("\nOpcao invalida!\n");
      break;
    }
    if (subOpcao != 3)
      pressionarEnterParaContinuar();
  } while (subOpcao != 3);
}

void cadastrarNovoLocal() {
  if (numLocais >= MAX_ITENS) {
    printf("\nNao e possivel cadastrar mais locais. Limite maximo atingido.\n");
    return;
  }
  printf("\n>> Cadastrando Novo Local...\n");
  Local novoLocal;
  novoLocal.idLocal = numLocais + 1;

  printf("Nome do Local: ");
  fgets(novoLocal.nomeLocal, 100, stdin);
  removerNovaLinha(novoLocal.nomeLocal);

  printf("Endereco Completo: ");
  fgets(novoLocal.enderecoCompleto, 200, stdin);
  removerNovaLinha(novoLocal.enderecoCompleto);

  do {
    novoLocal.capacidadeMaxima = lerInteiro("Capacidade Maxima de Pessoas: ");
    if (novoLocal.capacidadeMaxima <= 0) {
        printf("Erro: A capacidade maxima deve ser de pelo menos 1 pessoa.\n");
    }
  } while (novoLocal.capacidadeMaxima <= 0);

  printf("Telefone de Contato (opcional): ");
  fgets(novoLocal.telefoneContato, 20, stdin);
  removerNovaLinha(novoLocal.telefoneContato);

  printf("Regras da Casa: ");
  fgets(novoLocal.regrasDaCasa, 200, stdin);
  removerNovaLinha(novoLocal.regrasDaCasa);

  printf("Notas Adicionais: ");
  fgets(novoLocal.notas, 300, stdin);
  removerNovaLinha(novoLocal.notas);

  int anfitriaoValido = 0;
  do {
    listarJogadoresSimples();
    novoLocal.idAnfitriaoPadrao = lerInteiro("Digite o ID do Anfitriao Padrao (ou 0 se nao houver): ");

    if (novoLocal.idAnfitriaoPadrao == 0) {
        anfitriaoValido = 1;
    } else {
        if (strcmp(buscarApelidoJogadorPorId(novoLocal.idAnfitriaoPadrao), "Nao encontrado") != 0) {
            anfitriaoValido = 1;
        } else {
            printf("Erro: Jogador com ID %d nao encontrado. Digite um ID valido ou 0.\n", novoLocal.idAnfitriaoPadrao);
        }
    }
  } while (!anfitriaoValido);

  listaLocais[numLocais] = novoLocal;
  numLocais++;
  printf("\nLocal '%s' cadastrado com sucesso com o ID %d!\n",
         novoLocal.nomeLocal, novoLocal.idLocal);
}

void listarLocaisDetalhado() {
  printf("\n--- Lista Detalhada de Locais Cadastrados ---\n");
  if (numLocais == 0) {
    printf("Nenhum local cadastrado no sistema.\n");
    return;
  }
  for (int i = 0; i < numLocais; i++) {
    Local local = listaLocais[i];
    printf("----------------------------------\n");
    printf("ID do Local:         %d\n", local.idLocal);
    printf("Nome:                %s\n", local.nomeLocal);
    printf("Endereco:            %s\n", local.enderecoCompleto);
    printf("Capacidade Maxima:   %d pessoas\n", local.capacidadeMaxima);
    if (local.idAnfitriaoPadrao > 0) {
      printf("Anfitriao Padrao:    ID %d (%s)\n", local.idAnfitriaoPadrao,
             buscarApelidoJogadorPorId(local.idAnfitriaoPadrao));
    } else {
      printf("Anfitriao Padrao:    Nenhum\n");
    }
    printf("Telefone de Contato: %s\n", local.telefoneContato);
    printf("Regras da Casa:      %s\n", local.regrasDaCasa);
    printf("Notas:               %s\n", local.notas);
  }
  printf("----------------------------------\n");
}

void registrarPartida() {
  if (numPartidas >= MAX_ITENS) {
    printf("\nNao e possivel registrar mais partidas. Limite maximo atingido.\n");
    pressionarEnterParaContinuar();
    return;
  }
  if (numSessoes == 0 || numJogos == 0 || numJogadores == 0) {
    printf("\nErro: E necessario ter ao menos uma Sessao, Jogo e Jogador cadastrado para registrar uma partida.\n");
    pressionarEnterParaContinuar();
    return;
  }

  printf("\n>> Registrando Partida Realizada...\n");
  Partida novaPartida;
  novaPartida.idPartida = numPartidas + 1;

  int sessaoEncontrada = 0;
  do {
    listarSessoesSimples();
    novaPartida.idSessaoAssociada = lerInteiro("Digite o ID da Sessao onde a partida ocorreu: ");

    sessaoEncontrada = 0;
    for (int i = 0; i < numSessoes; i++) {
        if (listaSessoes[i].idSessao == novaPartida.idSessaoAssociada) {
            sessaoEncontrada = 1;
            break;
        }
    }
    if (!sessaoEncontrada) {
        printf("Erro: Sessao com ID %d nao encontrada. Tente novamente.\n", novaPartida.idSessaoAssociada);
    }
  } while (!sessaoEncontrada);

  int jogoValido = 0;
  do {
    listarJogosSimples();
    novaPartida.idJogo = lerInteiro("Digite o ID do Jogo que foi jogado: ");

    if (strcmp(buscarTituloJogoPorId(novaPartida.idJogo), "Jogo base nao encontrado") != 0) {
        jogoValido = 1;
    } else {
        printf("Erro: Jogo com ID %d nao encontrado.\n", novaPartida.idJogo);
    }
  } while (!jogoValido);

  do {
    novaPartida.duracaoMinutos = lerInteiro("Duracao da partida (em minutos): ");
    if (novaPartida.duracaoMinutos <= 0) {
        printf("Erro: A duracao deve ser maior que 0 minutos.\n");
    }
  } while (novaPartida.duracaoMinutos <= 0);

  printf("Resultado/Pontuacao Final (texto livre): ");
  fgets(novaPartida.pontuacaoFinal, 200, stdin);
  removerNovaLinha(novaPartida.pontuacaoFinal);

  printf("\n-- Adicionar Participantes --\n");
  novaPartida.numParticipantes = 0;
  int idParticipante;

  do {
    if (novaPartida.numParticipantes >= 20) {
      printf("Numero maximo de participantes (20) atingido.\n");
      break;
    }

    listarJogadoresSimples();
    idParticipante = lerInteiro("Digite o ID de um jogador participante (ou 0 para parar): ");

    if (idParticipante > 0) {
        if (strcmp(buscarApelidoJogadorPorId(idParticipante), "Nao encontrado") == 0) {
            printf("Erro: Jogador com ID %d nao existe.\n", idParticipante);
            continue;
        }

        int jaAdicionado = 0;
        for (int k = 0; k < novaPartida.numParticipantes; k++) {
            if (novaPartida.participantes[k] == idParticipante) {
                jaAdicionado = 1;
                break;
            }
        }

        if (jaAdicionado) {
            printf("Erro: Este jogador ja foi adicionado a partida.\n");
        } else {
            novaPartida.participantes[novaPartida.numParticipantes] = idParticipante;
            novaPartida.numParticipantes++;
            printf("Jogador adicionado!\n");
        }
    }
  } while (idParticipante != 0);

  if (novaPartida.numParticipantes > 0) {
    printf("\n-- Selecionar Vencedor --\n");
    printf("Participantes desta partida:\n");
    for (int i = 0; i < novaPartida.numParticipantes; i++) {
      printf("ID: %d (%s)\n", novaPartida.participantes[i],
             buscarApelidoJogadorPorId(novaPartida.participantes[i]));
    }

    int vencedorValido = 0;
    do {
        novaPartida.idVencedor = lerInteiro("Digite o ID do Vencedor (ou 0 para empate/jogo cooperativo): ");

        if (novaPartida.idVencedor == 0) {
            vencedorValido = 1;
        } else {
            for (int i = 0; i < novaPartida.numParticipantes; i++) {
                if (novaPartida.participantes[i] == novaPartida.idVencedor) {
                    vencedorValido = 1;
                    break;
                }
            }
            if (!vencedorValido) {
                printf("Erro: O ID %d nao corresponde a nenhum participante desta partida.\n", novaPartida.idVencedor);
            }
        }
    } while (!vencedorValido);

  } else {
    novaPartida.idVencedor = 0;
  }

  listaPartidas[numPartidas] = novaPartida;
  numPartidas++;
  printf("\nPartida registrada com sucesso com o ID %d!\n", novaPartida.idPartida);
  pressionarEnterParaContinuar();
}

void avaliarJogo() {
  if (numAvaliacoes >= MAX_ITENS) {
    printf("\nNao e possivel registrar mais avaliacoes. Limite maximo atingido.\n");
    pressionarEnterParaContinuar();
    return;
  }
  if (numJogos == 0 || numJogadores == 0) {
    printf("\nErro: E necessario ter ao menos um Jogo e um Jogador cadastrado para criar uma avaliacao.\n");
    pressionarEnterParaContinuar();
    return;
  }

  printf("\n>> Avaliando um Jogo do Catalogo...\n");
  Avaliacao novaAvaliacao;
  novaAvaliacao.idAvaliacao = numAvaliacoes + 1;

  int jogoValido = 0;
  do {
    listarJogosSimples();
    novaAvaliacao.idJogoAvaliado = lerInteiro("Digite o ID do Jogo que deseja avaliar: ");

    if (strcmp(buscarTituloJogoPorId(novaAvaliacao.idJogoAvaliado), "Jogo base nao encontrado") != 0) {
        jogoValido = 1;
    } else {
        printf("Erro: Jogo com ID %d nao encontrado. Tente novamente.\n", novaAvaliacao.idJogoAvaliado);
    }
  } while (!jogoValido);

  int jogadorValido = 0;
  do {
    listarJogadoresSimples();
    novaAvaliacao.idJogadorAvaliador = lerInteiro("Digite o seu ID de Jogador (para identificar o autor da avaliacao): ");

    if (strcmp(buscarApelidoJogadorPorId(novaAvaliacao.idJogadorAvaliador), "Nao encontrado") != 0) {
        jogadorValido = 1;
    } else {
        printf("Erro: Jogador com ID %d nao encontrado. Tente novamente.\n", novaAvaliacao.idJogadorAvaliador);
    }
  } while (!jogadorValido);

  printf("Data da Avaliacao (DD/MM/AAAA): ");
  fgets(novaAvaliacao.dataAvaliacao, 15, stdin);
  removerNovaLinha(novaAvaliacao.dataAvaliacao);

  do {
    novaAvaliacao.nota = lerFloat("Qual sua nota para este jogo (de 0.0 a 10.0)? ");
    if (novaAvaliacao.nota < 0.0f || novaAvaliacao.nota > 10.0f) {
        printf("Erro: A nota deve ser um valor entre 0.0 e 10.0.\n");
    }
  } while (novaAvaliacao.nota < 0.0f || novaAvaliacao.nota > 10.0f);

  do {
    novaAvaliacao.recomendaria = lerInteiro("Voce recomendaria este jogo a outros? (1=Sim, 0=Nao): ");
    if (novaAvaliacao.recomendaria < 0 || novaAvaliacao.recomendaria > 1) {
        printf("Erro: Digite 1 para Sim ou 0 para Nao.\n");
    }
  } while (novaAvaliacao.recomendaria < 0 || novaAvaliacao.recomendaria > 1);

  do {
    novaAvaliacao.ehAnonima = lerInteiro("Sua avaliacao deve ser anonima? (1=Sim, 0=Nao): ");
    if (novaAvaliacao.ehAnonima < 0 || novaAvaliacao.ehAnonima > 1) {
        printf("Erro: Digite 1 para Sim ou 0 para Nao.\n");
    }
  } while (novaAvaliacao.ehAnonima < 0 || novaAvaliacao.ehAnonima > 1);

  printf("Deixe seu comentario (resenha) sobre o jogo: ");
  fgets(novaAvaliacao.comentario, 500, stdin);
  removerNovaLinha(novaAvaliacao.comentario);

  listaAvaliacoes[numAvaliacoes] = novaAvaliacao;
  numAvaliacoes++;
  printf("\nAvaliacao para o jogo ID %d registrada com sucesso!\n",
         novaAvaliacao.idJogoAvaliado);
  pressionarEnterParaContinuar();
}

void gerenciarVotacoes() {
  int subOpcao;
  do {
    printf("\n--- Gerenciar Votacoes ---\n");
    printf("[1] Criar Nova Votacao para uma Sessao\n");
    printf("[2] Listar Votacoes Abertas\n");
    printf("[3] Votar em uma Enquete\n");
    printf("[4] Ver Resultados de uma Votacao\n");
    printf("[5] Voltar ao Menu Principal\n");
    printf("Escolha uma opcao: ");
    if (scanf("%d", &subOpcao) != 1) {
      subOpcao = -1;
    }
    limparBuffer();
    switch (subOpcao) {
    case 1:
      criarNovaVotacao();
      break;
    case 2:
      listarVotacoesAbertas();
      break;
    case 3:
      votarEmEnquete();
      break;
    case 4:
      verResultadosVotacao();
      break;
    case 5:
      printf("\nRetornando ao menu principal...\n");
      break;
    default:
      printf("\nOpcao invalida!\n");
      break;
    }
    if (subOpcao != 5)
      pressionarEnterParaContinuar();
  } while (subOpcao != 5);
}

void criarNovaVotacao() {
  if (numVotacoes >= MAX_ITENS) {
    printf("\nNao e possivel criar mais votacoes. Limite maximo atingido.\n");
    return;
  }
  if (numSessoes == 0) {
    printf("\nErro: E necessario ter ao menos uma sessao agendada para criar uma votacao.\n");
    return;
  }

  printf("\n>> Criando Nova Votacao...\n");
  Votacao novaVotacao;
  novaVotacao.idVotacao = numVotacoes + 1;

  int sessaoEncontrada = 0;
  do {
    listarSessoesSimples();
    novaVotacao.idSessaoAssociada = lerInteiro("Digite o ID da Sessao a qual esta votacao pertence: ");

    sessaoEncontrada = 0;
    for (int i = 0; i < numSessoes; i++) {
        if (listaSessoes[i].idSessao == novaVotacao.idSessaoAssociada) {
            sessaoEncontrada = 1;
            break;
        }
    }
    if (!sessaoEncontrada) {
        printf("Erro: Sessao com ID %d nao encontrada. Tente novamente.\n", novaVotacao.idSessaoAssociada);
    }
  } while (!sessaoEncontrada);

  printf("Qual a pergunta da enquete?: ");
  fgets(novaVotacao.pergunta, 200, stdin);
  removerNovaLinha(novaVotacao.pergunta);

  printf("Data de Encerramento (DD/MM/AAAA): ");
  fgets(novaVotacao.dataEncerramento, 15, stdin);
  removerNovaLinha(novaVotacao.dataEncerramento);

  do {
    novaVotacao.numOpcoes = lerInteiro("Quantas opcoes de voto (de 2 a 5)? ");
    if (novaVotacao.numOpcoes < 2 || novaVotacao.numOpcoes > 5) {
        printf("Erro: Numero de opcoes invalido. A votacao deve ter entre 2 e 5 opcoes.\n");
    }
  } while (novaVotacao.numOpcoes < 2 || novaVotacao.numOpcoes > 5);

  for (int i = 0; i < novaVotacao.numOpcoes; i++) {
    printf("Texto da opcao [%d]: ", i + 1);
    fgets(novaVotacao.opcoesTexto[i], 100, stdin);
    removerNovaLinha(novaVotacao.opcoesTexto[i]);
    novaVotacao.votosPorOpcao[i] = 0;
  }

  strcpy(novaVotacao.status, "Aberta");
  novaVotacao.numVotantes = 0;
  listaVotacoes[numVotacoes] = novaVotacao;
  numVotacoes++;
  printf("\nVotacao criada com sucesso com o ID %d!\n", novaVotacao.idVotacao);
}

void listarVotacoesAbertas() {
  printf("\n--- Votacoes Abertas ---\n");
  int encontradas = 0;
  for (int i = 0; i < numVotacoes; i++) {
    if (strcmp(listaVotacoes[i].status, "Aberta") == 0) {
      printf("----------------------------------\n");
      printf("ID da Votacao: %d | Sessao ID: %d\n", listaVotacoes[i].idVotacao,
             listaVotacoes[i].idSessaoAssociada);
      printf("Pergunta: %s\n", listaVotacoes[i].pergunta);
      encontradas++;
    }
  }
  if (encontradas == 0) {
    printf("Nenhuma votacao aberta no momento.\n");
  }
  printf("----------------------------------\n");
}

void verResultadosVotacao() {
  if (numVotacoes == 0) {
    printf("\nNenhuma votacao registrada no sistema.\n");
    return;
  }

  int idVotacao = lerInteiro("Digite o ID da votacao para ver os resultados: ");

  int indiceVotacao = -1;
  for (int i = 0; i < numVotacoes; i++) {
    if (listaVotacoes[i].idVotacao == idVotacao) {
      indiceVotacao = i;
      break;
    }
  }

  if (indiceVotacao == -1) {
    printf("\nErro: Votacao com ID %d nao encontrada.\n", idVotacao);
    return;
  }

  Votacao v = listaVotacoes[indiceVotacao];
  printf("\n--- Resultados para a Votacao ID %d ---\n", v.idVotacao);
  printf("Status: %s\n", v.status);
  printf("Pergunta: %s\n", v.pergunta);
  for (int i = 0; i < v.numOpcoes; i++) {
    printf("Opcao [%d]: %s - Votos: %d\n", i + 1, v.opcoesTexto[i],
           v.votosPorOpcao[i]);
  }
  printf("Total de Votos: %d\n", v.numVotantes);
  printf("----------------------------------\n");
}

void votarEmEnquete() {
  if (numVotacoes == 0) {
    printf("\nNenhuma votacao registrada.\n");
    return;
  }

  int idVotacao, idJogador, opcaoVoto;
  int indiceVotacao = -1;

  int votacaoValida = 0;
  do {
    listarVotacoesAbertas();
    idVotacao = lerInteiro("Digite o ID da votacao em que deseja votar: ");

    indiceVotacao = -1;
    for (int i = 0; i < numVotacoes; i++) {
      if (listaVotacoes[i].idVotacao == idVotacao) {
        indiceVotacao = i;
        break;
      }
    }

    if (indiceVotacao == -1) {
        printf("Erro: Votacao com ID %d nao encontrada. Tente novamente.\n", idVotacao);
    } else if (strcmp(listaVotacoes[indiceVotacao].status, "Aberta") != 0) {
        printf("Erro: Esta votacao ja esta encerrada/fechada. Escolha outra.\n");
        indiceVotacao = -1;
    } else {
        votacaoValida = 1;
    }
  } while (!votacaoValida);

  printf("\n--- Votando em: %s ---\n", listaVotacoes[indiceVotacao].pergunta);
  for (int i = 0; i < listaVotacoes[indiceVotacao].numOpcoes; i++) {
    printf("Digite [%d] para: %s\n", i + 1, listaVotacoes[indiceVotacao].opcoesTexto[i]);
  }

  int jogadorValido = 0;
  do {
    listarJogadoresSimples();
    idJogador = lerInteiro("Digite o seu ID de jogador para registrar o voto: ");

    if (strcmp(buscarApelidoJogadorPorId(idJogador), "Nao encontrado") == 0) {
        printf("Erro: Jogador com ID %d nao encontrado no sistema.\n", idJogador);
        continue;
    }

    int jaVotou = 0;
    for (int i = 0; i < listaVotacoes[indiceVotacao].numVotantes; i++) {
        if (listaVotacoes[indiceVotacao].votantes[i] == idJogador) {
            jaVotou = 1;
            break;
        }
    }

    if (jaVotou) {
        printf("Erro: O jogador ID %d ja votou nesta enquete. Tente outro ID.\n", idJogador);
    } else {
        jogadorValido = 1;
    }
  } while (!jogadorValido);

  char promptVoto[50];
  sprintf(promptVoto, "Escolha sua opcao (1 a %d): ", listaVotacoes[indiceVotacao].numOpcoes);

  do {
    opcaoVoto = lerInteiro(promptVoto);
    if (opcaoVoto < 1 || opcaoVoto > listaVotacoes[indiceVotacao].numOpcoes) {
        printf("Erro: Opcao invalida. Digite um numero entre 1 e %d.\n", listaVotacoes[indiceVotacao].numOpcoes);
    }
  } while (opcaoVoto < 1 || opcaoVoto > listaVotacoes[indiceVotacao].numOpcoes);

  listaVotacoes[indiceVotacao].votosPorOpcao[opcaoVoto - 1]++;
  listaVotacoes[indiceVotacao].votantes[listaVotacoes[indiceVotacao].numVotantes] = idJogador;
  listaVotacoes[indiceVotacao].numVotantes++;
  printf("\nVoto computado com sucesso!\n");
}

void gerenciarCardapio() {
  int subOpcao;
  do {
    printf("\n--- Gerenciar Cardapio das Sessoes ---\n");
    printf("[1] Adicionar Item ao Cardapio de uma Sessao\n");
    printf("[2] Ver Cardapio Completo de uma Sessao\n");
    printf("[3] Voltar ao Menu Principal\n");
    printf("Escolha uma opcao: ");
    if (scanf("%d", &subOpcao) != 1) {
      subOpcao = -1;
    }
    limparBuffer();
    switch (subOpcao) {
    case 1:
      adicionarItemAoCardapio();
      break;
    case 2:
      verCardapioDaSessao();
      break;
    case 3:
      printf("\nRetornando ao menu principal...\n");
      break;
    default:
      printf("\nOpcao invalida!\n");
      break;
    }
    if (subOpcao != 3)
      pressionarEnterParaContinuar();
  } while (subOpcao != 3);
}

void adicionarItemAoCardapio() {
  if (numCardapioItens >= MAX_ITENS * 5) {
    printf("\nNao e possivel adicionar mais itens ao cardapio. Limite maximo atingido.\n");
    return;
  }
  if (numSessoes == 0 || numJogadores == 0) {
    printf("\nErro: E necessario ter ao menos uma Sessao e um Jogador cadastrado.\n");
    return;
  }

  printf("\n>> Adicionando Item ao Cardapio...\n");
  CardapioItem novoItem;
  novoItem.idCardapioItem = numCardapioItens + 1;

  int sessaoEncontrada = 0;
  do {
    listarSessoesSimples();
    novoItem.idSessaoAssociada = lerInteiro("Digite o ID da Sessao para adicionar o item: ");

    sessaoEncontrada = 0;
    for (int i = 0; i < numSessoes; i++) {
        if (listaSessoes[i].idSessao == novoItem.idSessaoAssociada) {
            sessaoEncontrada = 1;
            break;
        }
    }
    if (!sessaoEncontrada) {
        printf("Erro: Sessao com ID %d nao encontrada. Tente novamente.\n", novoItem.idSessaoAssociada);
    }
  } while (!sessaoEncontrada);

  int jogadorValido = 0;
  do {
    listarJogadoresSimples();
    novoItem.idJogadorResponsavel = lerInteiro("Digite o ID do Jogador responsavel por este item: ");

    if (strcmp(buscarApelidoJogadorPorId(novoItem.idJogadorResponsavel), "Nao encontrado") != 0) {
        jogadorValido = 1;
    } else {
        printf("Erro: Jogador com ID %d nao encontrado. Tente novamente.\n", novoItem.idJogadorResponsavel);
    }
  } while (!jogadorValido);

  printf("Nome do Item: ");
  fgets(novoItem.nomeItem, 100, stdin);
  removerNovaLinha(novoItem.nomeItem);

  printf("Quantidade: ");
  fgets(novoItem.quantidade, 50, stdin);
  removerNovaLinha(novoItem.quantidade);

  printf("Categoria (Salgado, Doce, Bebida, etc.): ");
  fgets(novoItem.categoria, 50, stdin);
  removerNovaLinha(novoItem.categoria);

  printf("Notas Adicionais: ");
  fgets(novoItem.notasAdicionais, 200, stdin);
  removerNovaLinha(novoItem.notasAdicionais);

  strcpy(novoItem.status, "Confirmado");
  listaCardapio[numCardapioItens] = novoItem;
  numCardapioItens++;
  printf("\nItem adicionado ao cardapio da sessao com sucesso!\n");
}

void verCardapioDaSessao() {
  if (numSessoes == 0) {
    printf("\nNenhuma sessao agendada para ver o cardapio.\n");
    return;
  }
  int idSessao;
  int sessaoEncontrada = 0;

  do {
    listarSessoesSimples();
    idSessao = lerInteiro("Digite o ID da Sessao para ver o cardapio: ");

    sessaoEncontrada = 0;
    for (int i = 0; i < numSessoes; i++) {
        if (listaSessoes[i].idSessao == idSessao) {
            sessaoEncontrada = 1;
            break;
        }
    }

    if (!sessaoEncontrada) {
        printf("Erro: Sessao com ID %d nao encontrada. Tente novamente.\n", idSessao);
    }
  } while (!sessaoEncontrada);

  printf("\n--- Cardapio da Sessao ID %d ---\n", idSessao);
  int encontrados = 0;
  for (int i = 0; i < numCardapioItens; i++) {
    if (listaCardapio[i].idSessaoAssociada == idSessao) {
      CardapioItem item = listaCardapio[i];
      printf("----------------------------------\n");
      printf("Item:         %s (%s)\n", item.nomeItem, item.quantidade);
      printf("Categoria:    %s\n", item.categoria);
      printf("Responsavel:  ID %d (%s)\n", item.idJogadorResponsavel,
             buscarApelidoJogadorPorId(item.idJogadorResponsavel));
      printf("Notas:        %s\n", item.notasAdicionais);
      encontrados++;
    }
  }
  if (encontrados == 0) {
    printf("Nenhum item de cardapio registrado para esta sessao.\n");
  }
  printf("----------------------------------\n");
}

int lerInteiro(const char *prompt) {
  int valor;
  int resultadoScan;

  do {
    printf("%s", prompt);
    resultadoScan = scanf("%d", &valor);

    if (resultadoScan != 1) {
      printf("\nEntrada invalida! Por favor, digite um numero inteiro.\n\n");
    }

    limparBuffer();

  } while (resultadoScan != 1);

  return valor;
}

float lerFloat(const char *prompt) {
  float valor;
  int resultadoScan;

  do {
    printf("%s", prompt);
    resultadoScan = scanf("%f", &valor);

    if (resultadoScan != 1) {
      printf("\nEntrada invalida! Por favor, digite um numero.\n\n");
    }

    limparBuffer();

  } while (resultadoScan != 1);

  return valor;
}

void limparBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void pressionarEnterParaContinuar() {
  printf("\nPressione Enter para continuar...");
  getchar();
}

void removerNovaLinha(char *str) {
  size_t len = strlen(str);
  if (len > 0 && str[len - 1] == '\n') {
    str[len - 1] = '\0';
  }
}

const char *buscarApelidoJogadorPorId(int jogadorId) {
  for (int i = 0; i < numJogadores; i++) {
    if (listaJogadores[i].idJogador == jogadorId) {
      return listaJogadores[i].apelido;
    }
  }
  return "Nao encontrado";
}

const char *buscarTituloJogoPorId(int jogoId) {
  for (int i = 0; i < numJogos; i++) {
    if (listaJogos[i].idJogo == jogoId) {
      return listaJogos[i].titulo;
    }
  }
  return "Jogo base nao encontrado";
}

const char *buscarNomeLocalPorId(int localId) {
  for (int i = 0; i < numLocais; i++) {
    if (listaLocais[i].idLocal == localId) {
      return listaLocais[i].nomeLocal;
    }
  }
  return "Local nao encontrado";
}

void listarJogadoresSimples() {
  printf("\n-- Jogadores Cadastrados --\n");
  if (numJogadores == 0) {
    printf("Nenhum jogador cadastrado.\n");
  } else {
    for (int i = 0; i < numJogadores; i++) {
      printf("ID: %d | Nome: %s | Apelido: %s\n", listaJogadores[i].idJogador,
             listaJogadores[i].nomeCompleto, listaJogadores[i].apelido);
    }
  }
  printf("---------------------------\n");
}

void listarJogosSimples() {
  printf("\n-- Jogos no Catalogo --\n");
  if (numJogos == 0) {
    printf("Nenhum jogo cadastrado.\n");
  } else {
    for (int i = 0; i < numJogos; i++) {
      printf("ID: %d | Titulo: %s\n", listaJogos[i].idJogo,
             listaJogos[i].titulo);
      
    }
  }
  printf("------------------------\n");
}

void listarExpansoesSimples() {
  printf("\n-- Expansoes no Catalogo --\n");
  if (numExpansoes == 0) {
    printf("Nenhuma expansao cadastrada.\n");
  } else {
    for (int i = 0; i < numExpansoes; i++) {
      printf("ID: %d | Titulo: %s (Para Jogo ID: %d)\n",
             listaExpansoes[i].idExpansao, listaExpansoes[i].tituloExpansao,
             listaExpansoes[i].idJogoBase);
    }
  }
  printf("---------------------------\n");
}

void listarSessoesSimples() {
  printf("\n-- Sessoes Agendadas --\n");
  if (numSessoes == 0) {
    printf("Nenhuma sessao agendada.\n");
  } else {
    for (int i = 0; i < numSessoes; i++) {
      printf("ID: %d | Evento: %s | Data: %s\n", listaSessoes[i].idSessao,
             listaSessoes[i].nomeEvento, listaSessoes[i].data);
    }
  }
  printf("------------------------\n");
}

void listarCampanhasSimples() {
  printf("\n-- Campanhas em Andamento --\n");
  if (numCampanhas == 0) {
    printf("Nenhuma campanha criada.\n");
  } else {
    for (int i = 0; i < numCampanhas; i++) {
      printf("ID: %d | Nome: %s\n", listaCampanhas[i].idCampanha,
             listaCampanhas[i].nomeCampanha);
    }
  }
  printf("---------------------------\n");
}

void listarLocaisSimples() {
  printf("\n-- Locais Cadastrados --\n");
  if (numLocais == 0) {
    printf("Nenhum local cadastrado.\n");
  } else {
    for (int i = 0; i < numLocais; i++) {
      printf("ID: %d | Nome: %s\n", listaLocais[i].idLocal,
             listaLocais[i].nomeLocal);
    }
  }
  printf("-------------------------\n");
}