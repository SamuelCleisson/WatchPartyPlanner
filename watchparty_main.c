#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 50

// Armazena informações dos usuários do sistema
typedef struct
{
    int idUsuario;
    char nome[100];
    char nickname[50];
    char status[20];
} Usuario;

// Representa a sala do WatchParty
typedef struct
{
    int idSala;
    char nomeSala[100];
    int idCriador;
    int participantes[20];
    int numParticipantes;
    char status[20];
} Sala;

// Representa uma mensagem enviada no chat
typedef struct
{
    int idSala;
    char autor[50];
    char mensagem[200];
} Mensagem;

// Catalogo de filmes e series
typedef struct
{
    int idConteudo;
    char titulo[100];
    char plataforma[50];
    char genero[50];
} Conteudo;

// Armazena informações sobre uma sessão de exibição
typedef struct
{
    int idSessao;
    char data[15];
    char horario[10];
    int idSala;
    int idConteudo;
    char status[20];
} SessaoDeExibicao;

// No da lista encadeada de notificações
typedef struct NoNotificacao
{
    char mensagem[200];
    struct NoNotificacao *prox;
} NoNotificacao;

NoNotificacao *listaNotificacoes = NULL;

Usuario listaUsuarios[MAX_ITENS];
int numUsuarios = 0;

Sala listaSalas[MAX_ITENS];
int numSalas = 0;

Mensagem listaMensagens[100];
int numMensagens = 0;

Conteudo listaConteudos[MAX_ITENS];
int numConteudos = 0;

SessaoDeExibicao listaSessoes[MAX_ITENS];
int numSessoes = 0;

int idUsuarioLogado = -1;

void carregarDadosIniciais(); // Carrega os dados pré-criados

void telaLogin();   // Tela de login mostrando os usuarios
void menuUsuario(); // Menu de opções

void verSalas();
void criarSala(); // Cria uma nova sala
void entrarNaSala(int idSala);
void encerrarSala(); // Encerra a sala criada

void enviarMensagem(int idSala); // envia mensagem no chat da sala
void mostrarChat(int idSala);    // mostra o chat

void verCatalogo(); // Mostra todos os conteudos cadastrados

void removerMinhaConta();                   // Remove o usuario do sistema e das salas que participa
void verNotificacoes();                     // Mostra todas as notificações
void adicionarNotificacao(const char *msg); // Adiciona uma nova notificação

void limparBuffer();                  // faz a limpa dos caracteres restantes do teclado
void removerQuebraLinha(char *texto); // remove o quebra linha
void pressionarEnter();               // Pausa a execução

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void removerQuebraLinha(char *texto)
{
    texto[strcspn(texto, "\n")] = '\0';
}

void pressionarEnter()
{
    printf("\nPressione Enter para continuar...");
    getchar();
}

// Adiciona uma mensagem à lista de notificações
void adicionarNotificacao(const char *msg)
{
    NoNotificacao *novo = (NoNotificacao *)malloc(sizeof(NoNotificacao));
    if (!novo)
        return;

    strncpy(novo->mensagem, msg, 199);
    novo->prox = NULL;

    if (listaNotificacoes == NULL)
    {
        listaNotificacoes = novo;
    }
    else
    {
        NoNotificacao *aux = listaNotificacoes;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
}

// Exibe todas as notificações
void verNotificacoes()
{
    if (listaNotificacoes == NULL)
    {
        printf("\nNenhuma notificacao ainda.\n");
        pressionarEnter();
        return;
    }

    printf("\n=== NOTIFICACOES ===\n");
    NoNotificacao *aux = listaNotificacoes;
    int i = 1;
    while (aux != NULL)
    {
        printf("[%d] %s\n", i++, aux->mensagem);
        aux = aux->prox;
    }
    printf("====================\n");
    pressionarEnter();
}

// Função principal do programa
int main()
{
    carregarDadosIniciais();
    telaLogin();
    return 0;
}

// Tela de login
void telaLogin()
{
    int opcao;

    printf("\n+-----------------------------------+\n");
    printf("|      WATCH PARTY PLANNER          |\n");
    printf("+-----------------------------------+\n");
    printf("| Quem esta assistindo hoje?        |\n");
    printf("+-----------------------------------+\n");

    for (int i = 0; i < numUsuarios; i++)
    {
        printf("| [%d] %-32s|\n", i + 1, listaUsuarios[i].nickname);
    }

    printf("+-----------------------------------+\n");
    printf("Escolha: ");

    if (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > numUsuarios)
    {
        limparBuffer();
        printf("Opcao invalida!\n");
        telaLogin();
        return;
    }
    limparBuffer();

    idUsuarioLogado = listaUsuarios[opcao - 1].idUsuario;
    strcpy(listaUsuarios[opcao - 1].status, "Online");

    char notif[200];
    snprintf(notif, sizeof(notif), "%s entrou no sistema.",
             listaUsuarios[opcao - 1].nickname);
    adicionarNotificacao(notif);

    printf("\nOla, %s! Bem-vindo(a)!\n", listaUsuarios[opcao - 1].nickname);
    pressionarEnter();

    menuUsuario();
}

// Menu principal das funcionalidades
void menuUsuario()
{
    int opcao;
    char *nick = listaUsuarios[idUsuarioLogado - 1].nickname;

    do
    {
        printf("\n+-----------------------------------+\n");
        printf("| WATCH PARTY — %s\n", nick);
        printf("+-----------------------------------+\n");
        printf("| [1] Ver salas disponiveis         |\n");
        printf("| [2] Criar uma sala                |\n");
        printf("| [3] Encerrar minha sala           |\n");
        printf("| [4] Ver catalogo de conteudos     |\n");
        printf("| [5] Ver notificacoes              |\n");
        printf("| [6] Remover minha conta           |\n");
        printf("| [0] Sair                          |\n");
        printf("+-----------------------------------+\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1)
        {
            opcao = -1;
        }
        limparBuffer();

        switch (opcao)
        {
        case 1:
            verSalas();
            break;
        case 2:
            criarSala();
            break;
        case 3:
            encerrarSala();
            break;
        case 4:
            verCatalogo();
            break;
        case 5:
            verNotificacoes();
            break;
        case 6:
            removerMinhaConta();
            return;
        case 0:
            strcpy(listaUsuarios[idUsuarioLogado - 1].status, "Offline");
            printf("\nAte a proxima, %s!\n", nick);
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (opcao != 0);
}

// Exibe as salas que estão ativas
void verSalas()
{
    if (numSalas == 0)
    {
        printf("\nNenhuma sala disponivel. Que tal criar uma?\n");
        pressionarEnter();
        return;
    }

    int opcao;
    do
    {
        printf("\n=== SALAS DISPONIVEIS ===\n");
        int temAtiva = 0;
        for (int i = 0; i < numSalas; i++)
        {
            if (strcmp(listaSalas[i].status, "Encerrada") == 0)
                continue;
            temAtiva = 1;
            printf("[%d] %s — %d participante(s) — Criador: %s\n",
                   listaSalas[i].idSala,
                   listaSalas[i].nomeSala,
                   listaSalas[i].numParticipantes,
                   listaUsuarios[listaSalas[i].idCriador - 1].nickname);
        }
        if (!temAtiva)
        {
            printf("Nenhuma sala ativa no momento.\n");
            pressionarEnter();
            return;
        }
        printf("[0] Voltar\n");
        printf("Entrar em qual sala? ");

        if (scanf("%d", &opcao) != 1)
        {
            opcao = -1;
        }
        limparBuffer();

        if (opcao == 0)
            return;

        int encontrou = 0;
        for (int i = 0; i < numSalas; i++)
        {
            if (listaSalas[i].idSala == opcao &&
                strcmp(listaSalas[i].status, "Ativa") == 0)
            {
                encontrou = 1;
                entrarNaSala(opcao);
                break;
            }
        }
        if (!encontrou && opcao != 0)
            printf("Sala nao encontrada ou encerrada!\n");

    } while (opcao != 0);
}

// Entra numa sala
void entrarNaSala(int idSala)
{
    Sala *s = NULL;
    for (int i = 0; i < numSalas; i++)
    {
        if (listaSalas[i].idSala == idSala)
        {
            s = &listaSalas[i];
            break;
        }
    }
    if (!s)
        return;

    int jaEsta = 0;
    for (int i = 0; i < s->numParticipantes; i++)
    {
        if (s->participantes[i] == idUsuarioLogado)
        {
            jaEsta = 1;
            break;
        }
    }
    if (!jaEsta && s->numParticipantes < 20)
    {
        s->participantes[s->numParticipantes++] = idUsuarioLogado;
    }

    char notif[200];
    snprintf(notif, sizeof(notif), "%s entrou na sala '%s'.",
             listaUsuarios[idUsuarioLogado - 1].nickname, s->nomeSala);
    adicionarNotificacao(notif);

    printf("\n================================\n");
    printf(" SALA: %s\n", s->nomeSala);
    printf(" Participantes: %d\n", s->numParticipantes);

    for (int i = 0; i < numSessoes; i++)
    {
        if (listaSessoes[i].idSala == idSala &&
            strcmp(listaSessoes[i].status, "Em Exibicao") == 0)
        {
            int cid = listaSessoes[i].idConteudo;
            printf(" Assistindo: %s (%s)\n",
                   listaConteudos[cid - 1].titulo,
                   listaConteudos[cid - 1].plataforma);
            break;
        }
    }
    int opcao;

    do
    {

        printf("\n================================\n");
        printf("SALA: %s\n", s->nomeSala);

        mostrarChat(idSala);

        printf("\n[1] Enviar mensagem\n");
        printf("[0] Sair da sala\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {

        case 1:
            enviarMensagem(idSala);
            break;
        }

    } while (opcao != 0);
}

// Cria uma nova sala
void criarSala()
{
    if (numSalas >= MAX_ITENS)
    {
        printf("Limite de salas atingido!\n");
        return;
    }

    Sala *s = &listaSalas[numSalas];
    s->idSala = numSalas + 1;
    s->idCriador = idUsuarioLogado;
    s->participantes[0] = idUsuarioLogado;
    s->numParticipantes = 1;
    strcpy(s->status, "Ativa");

    printf("Nome da sala: ");
    fgets(s->nomeSala, sizeof(s->nomeSala), stdin);
    removerQuebraLinha(s->nomeSala);

    printf("\n=== ESCOLHA O CONTEUDO ===\n");
    verCatalogo();
    printf("ID do conteudo (0 para nenhum): ");
    int idConteudo;
    scanf("%d", &idConteudo);
    limparBuffer();

    if (idConteudo >= 1 && idConteudo <= numConteudos && numSessoes < MAX_ITENS)
    {
        SessaoDeExibicao *sess = &listaSessoes[numSessoes];
        sess->idSessao = numSessoes + 1;
        sess->idSala = s->idSala;
        sess->idConteudo = idConteudo;
        strcpy(sess->data, "hoje");
        strcpy(sess->horario, "agora");
        strcpy(sess->status, "Em Exibicao");
        numSessoes++;

        printf("Sala criada com '%s'!\n", listaConteudos[idConteudo - 1].titulo);
    }
    else
    {
        printf("Sala criada sem conteudo!\n");
    }

    numSalas++;

    char notif[200];
    snprintf(notif, sizeof(notif), "%s criou a sala '%s'.",
             listaUsuarios[idUsuarioLogado - 1].nickname, s->nomeSala);
    adicionarNotificacao(notif);

    pressionarEnter();
}

// Fecha uma sala criada pelo usuario
void encerrarSala()
{
    int encontrou = 0;
    for (int i = 0; i < numSalas; i++)
    {
        if (listaSalas[i].idCriador == idUsuarioLogado &&
            strcmp(listaSalas[i].status, "Ativa") == 0)
        {
            encontrou = 1;
            strcpy(listaSalas[i].status, "Encerrada");

            char notif[200];
            snprintf(notif, sizeof(notif), "Sala '%s' foi encerrada por %s.",
                     listaSalas[i].nomeSala,
                     listaUsuarios[idUsuarioLogado - 1].nickname);
            adicionarNotificacao(notif);

            printf("Sala '%s' encerrada!\n", listaSalas[i].nomeSala);
        }
    }
    if (!encontrou)
        printf("Voce nao tem nenhuma sala ativa para encerrar.\n");
    pressionarEnter();
}

// Adiciona uma nova mensagem ao chat da sala
void enviarMensagem(int idSala)
{

    listaMensagens[numMensagens].idSala = idSala;

    strcpy(listaMensagens[numMensagens].autor,
           listaUsuarios[idUsuarioLogado - 1].nickname);

    printf("Mensagem: ");
    fgets(listaMensagens[numMensagens].mensagem, 200, stdin);

    removerQuebraLinha(listaMensagens[numMensagens].mensagem);

    numMensagens++;
}

// Exibe todas as mensagens da sala
void mostrarChat(int idSala)
{

    printf("\n========== CHAT ==========\n");

    for (int i = 0; i < numMensagens; i++)
    {

        if (listaMensagens[i].idSala == idSala)
        {

            printf("%s: %s\n",
                   listaMensagens[i].autor,
                   listaMensagens[i].mensagem);
        }
    }

    printf("==========================\n");
}

// Exibe o catalogo de filmes e series
void verCatalogo()
{
    printf("\n=== CATALOGO ===\n");
    for (int i = 0; i < numConteudos; i++)
    {
        printf("[%d] %s — %s — %s\n",
               listaConteudos[i].idConteudo,
               listaConteudos[i].titulo,
               listaConteudos[i].plataforma,
               listaConteudos[i].genero);
    }
    printf("================\n");
}

// Remove a conta do usuario
void removerMinhaConta()
{
    char confirm[10];
    printf("Tem certeza que quer remover sua conta? (sim/nao): ");
    fgets(confirm, sizeof(confirm), stdin);
    removerQuebraLinha(confirm);

    if (strcmp(confirm, "sim") != 0)
    {
        printf("Cancelado.\n");
        menuUsuario();
        return;
    }

    for (int s = 0; s < numSalas; s++)
    {
        if (listaSalas[s].idCriador == idUsuarioLogado)
            strcpy(listaSalas[s].status, "Encerrada");
        for (int p = 0; p < listaSalas[s].numParticipantes; p++)
        {
            if (listaSalas[s].participantes[p] == idUsuarioLogado)
            {
                for (int k = p; k < listaSalas[s].numParticipantes - 1; k++)
                    listaSalas[s].participantes[k] = listaSalas[s].participantes[k + 1];
                listaSalas[s].numParticipantes--;
                break;
            }
        }
    }

    int idx = idUsuarioLogado - 1;
    char nick[50];
    strcpy(nick, listaUsuarios[idx].nickname);

    char notif[200];
    snprintf(notif, sizeof(notif), "Conta de '%s' foi removida.", nick);
    adicionarNotificacao(notif);

    for (int i = idx; i < numUsuarios - 1; i++)
    {
        listaUsuarios[i] = listaUsuarios[i + 1];
        listaUsuarios[i].idUsuario = i + 1;
    }
    numUsuarios--;

    printf("Conta de '%s' removida. Ate mais!\n", nick);

    if (numUsuarios == 0)
    {
        printf("Nenhum usuario restante. Encerrando.\n");
        return;
    }
    telaLogin();
}

// Inicializa tudo previamente
void carregarDadosIniciais()
{
    listaUsuarios[0] = (Usuario){1, "Samuel Cleisson", "Sam", "Offline"};
    listaUsuarios[1] = (Usuario){2, "Leticia Karen", "lelete", "Offline"};
    listaUsuarios[2] = (Usuario){3, "Ana Carolina", "Ana", "Offline"};
    numUsuarios = 3;

    listaConteudos[0] = (Conteudo){1, "Stranger Things", "Netflix", "Ficcao"};
    listaConteudos[1] = (Conteudo){2, "The Boys", "Prime Video", "Acao"};
    listaConteudos[2] = (Conteudo){3, "Loki", "Disney+", "Aventura"};
    listaConteudos[3] = (Conteudo){4, "Breaking Bad", "Netflix", "Drama"};
    listaConteudos[4] = (Conteudo){5, "The Last of Us", "Max", "Drama"};
    listaConteudos[5] = (Conteudo){6, "Dark", "Netflix", "Ficcao"};
    listaConteudos[6] = (Conteudo){7, "Arcane", "Netflix", "Animacao"};
    listaConteudos[7] = (Conteudo){8, "Round 6", "Netflix", "Suspense"};
    listaConteudos[8] = (Conteudo){9, "La Casa de Papel", "Netflix", "Acao"};
    listaConteudos[9] = (Conteudo){10, "The Witcher", "Netflix", "Fantasia"};
    listaConteudos[10] = (Conteudo){11, "Invincible", "Prime Video", "Animacao"};
    listaConteudos[11] = (Conteudo){12, "Fallout", "Prime Video", "Ficcao"};
    listaConteudos[12] = (Conteudo){13, "Reacher", "Prime Video", "Acao"};
    listaConteudos[13] = (Conteudo){14, "Gen V", "Prime Video", "Acao"};
    listaConteudos[14] = (Conteudo){15, "Jack Ryan", "Prime Video", "Suspense"};
    listaConteudos[15] = (Conteudo){16, "WandaVision", "Disney+", "Ficcao"};
    listaConteudos[16] = (Conteudo){17, "Demolidor", "Disney+", "Acao"};
    listaConteudos[17] = (Conteudo){18, "Hawkeye", "Disney+", "Acao"};
    listaConteudos[18] = (Conteudo){19, "Percy Jackson", "Disney+", "Fantasia"};
    listaConteudos[19] = (Conteudo){20, "X-Men '97", "Disney+", "Animacao"};
    listaConteudos[20] = (Conteudo){21, "House of the Dragon", "Max", "Fantasia"};
    listaConteudos[21] = (Conteudo){22, "Game of Thrones", "Max", "Fantasia"};
    listaConteudos[22] = (Conteudo){23, "Chernobyl", "Max", "Drama"};
    listaConteudos[23] = (Conteudo){24, "Rick and Morty", "Max", "Animacao"};
    listaConteudos[24] = (Conteudo){25, "The Penguin", "Max", "Crime"};
    numConteudos = 25;

    listaSalas[0].idSala = 1;
    strcpy(listaSalas[0].nomeSala, "Maratona Series");
    listaSalas[0].idCriador = 1;
    listaSalas[0].participantes[0] = 1;
    listaSalas[0].participantes[1] = 2;
    listaSalas[0].numParticipantes = 2;
    strcpy(listaSalas[0].status, "Ativa");
    numSalas = 1;

    listaSessoes[0] = (SessaoDeExibicao){1, "hoje", "agora", 1, 1, "Em Exibicao"};
    numSessoes = 1;
}
