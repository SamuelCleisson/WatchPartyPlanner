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
    char status[20];
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
void entrarNaSala();

void gerenciarConteudos();
void cadastrarConteudo();
void listarConteudos();

void gerenciarSessoes();
void criarSessao();
void listarSessoes();

void gerenciarChat();
void enviarMensagem();
void listarMensagens();

void participarSessao();

void limparBuffer();
void pressionarEnterParaContinuar();
void removerQuebraLinha(char *texto);

void removerQuebraLinha(char *texto) {
    texto[strcspn(texto, "\n")] = '\0';
}

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
                participarSessao();
                break;
            case 6:
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
    printf("| [5] Participar de Sessao          |\n");
    printf("| [6] Chat                          |\n");
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
        printf("1 - Criar Sala\n");
        printf("2 - Listar Salas\n");
        printf("3 - Entrar na Sala\n");
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
            case 3:
                entrarNaSala();
                break;
        }
    } while(opcao != 0);
}

void entrarNaSala(){
    int idSala;
    int idUsuario;

    if(numSalas == 0){
        printf("Nenhuma sala cadastrada!\n");
        return;
    }

    if(numUsuarios == 0){
        printf("Nenhum usuario cadastrado!\n");
        return;
    }

    printf("ID da Sala: ");
    scanf("%d", &idSala);

    printf("ID do Usuario: ");
    scanf("%d", &idUsuario);

    limparBuffer();

    if(idSala < 1 || idSala > numSalas){
        printf("Sala nao encontrada!\n");
        return;
    }

    if(idUsuario < 1 || idUsuario > numUsuarios){
        printf("Usuario nao encontrado!\n");
        return;
    }

    Sala *s = &listaSalas[idSala - 1];

    if(s->numParticipantes >= 20){
        printf("Sala cheia!\n");
        return;
    }

    s->participantes[s->numParticipantes] = idUsuario;
    s->numParticipantes++;

    printf(
        "%s entrou na sala %s!\n",
        listaUsuarios[idUsuario - 1].nickname,
        s->nomeSala
    );
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

    if (numUsuarios >= MAX_ITENS) {
    printf("Limite de usuarios atingido!\n");
    return;
}

    Usuario *u = &listaUsuarios[numUsuarios];

    u->idUsuario = numUsuarios + 1;

    printf("Nome: ");
    fgets(u->nome, sizeof(u->nome), stdin);
    removerQuebraLinha(u->nome);

    printf("Nickname: ");
    fgets(u->nickname, sizeof(u->nickname), stdin);
    removerQuebraLinha(u->nickname);

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

    if (numSalas >= MAX_ITENS) {
        printf("Limite de salas atingido!\n");
        return;
    }

    if (numUsuarios == 0) {
        printf("Cadastre um usuario antes de criar uma sala!\n");
        return;
    }

    Sala *s = &listaSalas[numSalas];

    s->idSala = numSalas + 1;

    printf("Nome da Sala: ");
    fgets(s->nomeSala, sizeof(s->nomeSala), stdin);
    removerQuebraLinha(s->nomeSala);

    printf("ID do Criador: ");
    scanf("%d", &s->idCriador);
    limparBuffer();

    if (s->idCriador < 1 || s->idCriador > numUsuarios) {
        printf("Usuario nao encontrado!\n");
        return;
    }

    s->numParticipantes = 0;

    strcpy(s->status, "Ativa");

    numSalas++;

    printf("Sala criada com sucesso!\n");
}

void cadastrarConteudo() {

    if (numConteudos >= MAX_ITENS) {
        printf("Limite de conteudos atingido!\n");
        return;
    }

    Conteudo *c = &listaConteudos[numConteudos];

    c->idConteudo = numConteudos + 1;

    printf("Titulo: ");
    fgets(c->titulo, sizeof(c->titulo), stdin);
    removerQuebraLinha(c->titulo);

    printf("Plataforma: ");
    fgets(c->plataforma, sizeof(c->plataforma), stdin);
    removerQuebraLinha(c->plataforma);

    printf("Genero: ");
    fgets(c->genero, sizeof(c->genero), stdin);
    removerQuebraLinha(c->genero);

    numConteudos++;

    printf("Conteudo cadastrado!\n");
}

void criarSessao() {

    if (numSessoes >= MAX_ITENS) {
        printf("Limite de sessoes atingido!\n");
        return;
    }

    if (numSalas == 0) {
        printf("Cadastre uma sala primeiro!\n");
        return;
    }

    if (numConteudos == 0) {
        printf("Cadastre um conteudo primeiro!\n");
        return;
    }

    SessaoDeExibicao *s = &listaSessoes[numSessoes];

    s->idSessao = numSessoes + 1;

    printf("Data: ");
    fgets(s->data, sizeof(s->data), stdin);
    removerQuebraLinha(s->data);

    printf("Horario: ");
    fgets(s->horario, sizeof(s->horario), stdin);
    removerQuebraLinha(s->horario);

    printf("ID Sala: ");
    scanf("%d", &s->idSala);

    printf("ID Conteudo: ");
    scanf("%d", &s->idConteudo);

    limparBuffer();

    if (s->idSala < 1 || s->idSala > numSalas) {
        printf("Sala nao encontrada!\n");
        return;
    }

    if (s->idConteudo < 1 || s->idConteudo > numConteudos) {
        printf("Conteudo nao encontrado!\n");
        return;
    }

    numSessoes++;

    printf("Sessao criada!\n");
}

void enviarMensagem() {

    if (numMensagens >= MAX_ITENS) {
        printf("Limite de mensagens atingido!\n");
        return;
    }

    if (numUsuarios == 0 || numSalas == 0) {
        printf("Necessario ter usuarios e salas cadastrados!\n");
        return;
    }

    ItemChat *m = &listaMensagens[numMensagens];

    m->idMensagem = numMensagens + 1;

    printf("ID Usuario: ");
    scanf("%d", &m->idUsuario);

    printf("ID Sala: ");
    scanf("%d", &m->idSala);

    limparBuffer();

    if (m->idUsuario < 1 || m->idUsuario > numUsuarios) {
        printf("Usuario nao encontrado!\n");
        return;
    }

    if (m->idSala < 1 || m->idSala > numSalas) {
        printf("Sala nao encontrada!\n");
        return;
    }

    printf("Mensagem: ");
    fgets(m->mensagem, sizeof(m->mensagem), stdin);
    removerQuebraLinha(m->mensagem);

    strcpy(m->horario, "20:00");

    numMensagens++;

    printf("Mensagem enviada!\n");
}

void listarSalas(){
    if(numSalas == 0) {
        printf("Nenhuma sala cadastrada!\n");
        return;
    }
    for(int i = 0; i < numSalas; i++){
        printf("\nID: %d\n", listaSalas[i].idSala);
        printf("Nome: %s", listaSalas[i].nomeSala);
        printf("Criador: %d\n", listaSalas[i].idCriador);
        printf("Participantes: %d\n",
       listaSalas[i].numParticipantes);

        printf("Status: %s\n",
        listaSalas[i].status);
    }
}

void listarConteudos(){
    if(numConteudos == 0){
        printf("Nenhum conteudo cadastrado!\n");
        return;
    }

    for(int i = 0; i < numConteudos; i++){
        printf("\n========Conteudo========\n");
        printf("ID: %d\n", listaConteudos[i].idConteudo);
        printf("Titulo: %s\n", listaConteudos[i].titulo);
        printf("Plataforma: %s\n", listaConteudos[i].plataforma);
        printf("Genero: %s\n", listaConteudos[i].genero);
    }
}

void listarSessoes(){
    if(numSessoes == 0){
        printf("Nenhum sessão cadastrada!\n");
    }

    for(int i = 0; i < numSessoes; i++){
        printf("\n===== SESSAO =====\n");
        printf("ID: %d\n", listaSessoes[i].idSessao);
        printf("Data: %s\n", listaSessoes[i].data);
        printf("Horario: %s\n", listaSessoes[i].horario);
        printf("Sala: %d\n", listaSessoes[i].idSala);
        printf("Conteudo: %d\n", listaSessoes[i].idConteudo);
    }
}

void listarMensagens(){
    if(numMensagens == 0){
        printf("Nenhuma mensagem enviada!\n");
        return;
    }

    for(int i = 0; i < numMensagens; i++){

        printf("\n[%s]\n", listaMensagens[i].horario);

        printf("%s:\n",
            listaUsuarios[
            listaMensagens[i].idUsuario - 1
            ].nickname);

        printf("%s\n",
            listaMensagens[i].mensagem);
}

    for(int i = 0; i < numMensagens; i++){
        printf("\n===== MENSAGEM =====\n");
        printf("ID: %d\n", listaMensagens[i].idMensagem);
        printf("Usuario: %d\n", listaMensagens[i].idUsuario);
        printf("Sala: %d\n", listaMensagens[i].idSala);
        printf("Horario: %s\n", listaMensagens[i].horario);
        printf("Texto: %s\n", listaMensagens[i].mensagem);
    }
}

void participarSessao(){

    int idUsuario;
    int idSessao;
    int opcao;

    if(numSessoes == 0){
        printf("Nenhuma sessao disponivel!\n");
        return;
    }

    printf("ID Usuario: ");
    scanf("%d", &idUsuario);

    printf("ID Sessao: ");
    scanf("%d", &idSessao);

    limparBuffer();

    if(idUsuario < 1 || idUsuario > numUsuarios){
        printf("Usuario nao encontrado!\n");
        return;
    }

    if(idSessao < 1 || idSessao > numSessoes){
        printf("Sessao nao encontrada!\n");
        return;
    }

    Sala *sala = &listaSalas[listaSessoes[idSessao - 1].idSala - 1];
    Conteudo *conteudo = &listaConteudos[listaSessoes[idSessao - 1].idConteudo - 1];

    do {

        printf("\n================================\n");
        printf(" WATCH PARTY EM ANDAMENTO\n");
        printf("================================\n");

        printf("Usuario: %s\n",
               listaUsuarios[idUsuario - 1].nickname);

        printf("Sala: %s\n",
               sala->nomeSala);

        printf("Conteudo: %s\n",
               conteudo->titulo);

        printf("Plataforma: %s\n",
               conteudo->plataforma);

        printf("Participantes: %d\n",
               sala->numParticipantes);

        printf("Status: %s\n",
               listaSessoes[idSessao - 1].status);

        printf("================================\n");

        printf("1 - Ver mensagens\n");
        printf("2 - Enviar mensagem\n");
        printf("3 - Sair da sessao\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao){

            case 1:
                listarMensagens();
                break;

            case 2:
                enviarMensagem();
                break;
        }

    } while(opcao != 3);
}

void iniciarSessao(){
    int idSessao;

    printf("ID da Sessão: ");
    scanf("%d", &idSessao);

      limparBuffer();

    if(idSessao < 1 || idSessao > numSessoes){
        printf("Sessao nao encontrada!\n");
        return;
    }

    strcpy(
        listaSessoes[idSessao - 1].status,
        "Em Exibicao"
    );

    printf("Sessao iniciada!\n");
}
