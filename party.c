#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 50

typedef struct {
    int idUsuario;
    char nome[100];
    char nickname[50];
    char status[20];
} Usuario;

typedef struct {
    int idSala;
    char nomeSala[100];
    int idCriador;
    int participantes[20];
    int numParticipantes;
    char status[20];
} Sala;

typedef struct {
    int idConteudo;
    char titulo[100];
    char plataforma[50];
    char genero[50];
} Conteudo;

typedef struct {
    int idSessao;
    char data[15];
    char horario[10];
    int idSala;
    int idConteudo;
} SessaoDeExibicao;

typedef struct {
    int idMensagem;
    int idUsuario;
    int idSala;
    char mensagem[300];
    char horario[10];
} ItemChat;

Usuario listaUsuarios[MAX_ITENS];
int numUsuarios = 0;

Sala listaSalas[MAX_ITENS];
int numSalas = 0;

Conteudo listaConteudos[MAX_ITENS];
int numConteudos = 0;

SessaoDeExibicao listaSessoes[MAX_ITENS];
int numSessoes = 0;

ItemChat listaMensagens[MAX_ITENS];
int numMensagens = 0;


void exibirMenuPrincipal();

void gerenciarUsuarios();
void cadastrarUsuario();
void listarUsuarios();

void gerenciarSalas();
void criarSala();
void listarSalas();

void gerenciarConteudos();
void cadastrarConteudo();
void listarConteudos();

void gerenciarSessoes();
void criarSessao();
void listarSessoes();

void gerenciarChat();
void enviarMensagem();
void listarMensagens();

void limparBuffer();
void pressionarEnterParaContinuar();

int main(){
    int opcao;
    printf("Bem-vindo ao Watch Party Planner!\n");
    do {
        exibirMenuPrincipal();
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                gerenciarUsuarios();
                break;
            case 2:
                gerenciarSalas();
                break;
            case 3:
                gerenciarConteudos();
                break;
            case 4:
                gerenciarSessoes();
                break;
            case 5:
                gerenciarChat();
                break;
            case 9:
                printf("\nSaindo do sistema... Ate mais!\n");
                break;
            default:
                printf("\nOpcao invalida! Pressione Enter para tentar novamente.\n");
                pressionarEnterParaContinuar();
                break;
        }
    } while (opcao != 9);
    return 0;
}


void exibirMenuPrincipal() {
    printf("\n+-----------------------------------+\n");
    printf("|      WATCH PARTY PLANNER          |\n");
    printf("+-----------------------------------+\n");
    printf("| [1] Gerenciar Usuarios            |\n");
    printf("| [2] Gerenciar Salas               |\n");
    printf("| [3] Gerenciar Conteudos           |\n");
    printf("| [4] Gerenciar Sessoes             |\n");
    printf("| [5] Chat                          |\n");
    printf("| [9] Sair                          |\n");
    printf("+-----------------------------------+\n");
}

void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pressionarEnterParaContinuar(){
    printf("Pressione Enter para continuar...");
    getchar();
}

void gerenciarUsuarios() {
    int opcao;

    do {
        printf("\n=== USUARIOS ===\n");
        printf("1 - Cadastrar Usuario\n");
        printf("2 - Listar Usuarios\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1:
                cadastrarUsuario();
                break;

            case 2:
                listarUsuarios();
                break;
        }

    } while(opcao != 0);
}

void gerenciarSalas() {
    int opcao;

    do {
        printf("\n=== SALAS ===\n");
        printf("1 - Criar Sala\n");
        printf("2 - Listar Salas\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1:
                criarSala();
                break;

            case 2:
                listarSalas();
                break;
        }

    } while(opcao != 0);
}

void gerenciarConteudos() {
    int opcao;

    do {
        printf("\n=== CONTEUDOS ===\n");
        printf("1 - Cadastrar Conteudo\n");
        printf("2 - Listar Conteudos\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1:
                cadastrarConteudo();
                break;

            case 2:
                listarConteudos();
                break;
        }

    } while(opcao != 0);
}

void gerenciarSessoes() {
    int opcao;

    do {
        printf("\n=== SESSOES ===\n");
        printf("1 - Criar Sessao\n");
        printf("2 - Listar Sessoes\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1:
                criarSessao();
                break;

            case 2:
                listarSessoes();
                break;
        }

    } while(opcao != 0);
}

void gerenciarChat() {
    int opcao;

    do {
        printf("\n=== CHAT ===\n");
        printf("1 - Enviar Mensagem\n");
        printf("2 - Ver Mensagens\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1:
                enviarMensagem();
                break;

            case 2:
                listarMensagens();
                break;
        }

    } while(opcao != 0);
}

void cadastrarUsuario() {

    if(numUsuarios >= MAX_ITENS) return;

    Usuario *u = &listaUsuarios[numUsuarios];

    u->idUsuario = numUsuarios + 1;

    printf("Nome: ");
    fgets(u->nome, 100, stdin);

    printf("Nickname: ");
    fgets(u->nickname, 50, stdin);

    strcpy(u->status, "Online");

    numUsuarios++;

    printf("Usuario cadastrado!\n");
}

void listarUsuarios() {

    for(int i = 0; i < numUsuarios; i++) {

        printf("\nID: %d\n", listaUsuarios[i].idUsuario);
        printf("Nome: %s", listaUsuarios[i].nome);
        printf("Nick: %s", listaUsuarios[i].nickname);
        printf("Status: %s\n", listaUsuarios[i].status);
    }
}

void criarSala() {

    if(numSalas >= MAX_ITENS) return;

    Sala *s = &listaSalas[numSalas];

    s->idSala = numSalas + 1;

    printf("Nome da Sala: ");
    fgets(s->nomeSala, 100, stdin);

    printf("ID do Criador: ");
    scanf("%d", &s->idCriador);
    limparBuffer();

    s->numParticipantes = 0;

    strcpy(s->status, "Ativa");

    numSalas++;

    printf("Sala criada!\n");
}

void cadastrarConteudo() {

    if(numConteudos >= MAX_ITENS) return;

    Conteudo *c = &listaConteudos[numConteudos];

    c->idConteudo = numConteudos + 1;

    printf("Titulo: ");
    fgets(c->titulo, 100, stdin);

    printf("Plataforma: ");
    fgets(c->plataforma, 50, stdin);

    printf("Genero: ");
    fgets(c->genero, 50, stdin);

    numConteudos++;

    printf("Conteudo cadastrado!\n");
}

void criarSessao() {

    if(numSessoes >= MAX_ITENS) return;

    SessaoDeExibicao *s = &listaSessoes[numSessoes];

    s->idSessao = numSessoes + 1;

    printf("Data: ");
    fgets(s->data, 15, stdin);

    printf("Horario: ");
    fgets(s->horario, 10, stdin);

    printf("ID Sala: ");
    scanf("%d", &s->idSala);

    printf("ID Conteudo: ");
    scanf("%d", &s->idConteudo);

    limparBuffer();

    numSessoes++;

    printf("Sessao criada!\n");
}

void enviarMensagem() {

    if(numMensagens >= MAX_ITENS) return;

    ItemChat *m = &listaMensagens[numMensagens];

    m->idMensagem = numMensagens + 1;

    printf("ID Usuario: ");
    scanf("%d", &m->idUsuario);

    printf("ID Sala: ");
    scanf("%d", &m->idSala);

    limparBuffer();

    printf("Mensagem: ");
    fgets(m->mensagem, 300, stdin);

    strcpy(m->horario, "20:00");

    numMensagens++;

    printf("Mensagem enviada!\n");
}