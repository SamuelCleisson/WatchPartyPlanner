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

typedef struct NoMensagem {
    ItemChat mensagem;
    struct NoMensagem *prox;
} NoMensagem;

NoMensagem *inicioChat = NULL;

Usuario listaUsuarios[MAX_ITENS];
int numUsuarios = 0;

Sala listaSalas[MAX_ITENS];
int numSalas = 0;

Conteudo listaConteudos[MAX_ITENS];
int numConteudos = 0;

SessaoDeExibicao listaSessoes[MAX_ITENS];
int numSessoes = 0;


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
void iniciarSessao();

void gerenciarChat();
void enviarMensagem();
void listarMensagens();

void participarSessao();

void carregarDadosIniciais();

void limparBuffer();
void pressionarEnterParaContinuar();
void removerQuebraLinha(char *texto);

void removerQuebraLinha(char *texto) {
    texto[strcspn(texto, "\n")] = '\0';
}

int main(){
    int opcao;
    printf("Bem-vindo ao Watch Party Planner!\n");
    carregarDadosIniciais();
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
        printf("1 - Criar Sessao\n");
        printf("2 - Listar Sessoes\n");
        printf("3 - Iniciar Sessao\n");
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
            case 3:
                iniciarSessao();
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
        printf("Nome: %s\n", listaUsuarios[i].nome);
        printf("Nick: %s\n", listaUsuarios[i].nickname);
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

    s->participantes[0] = s->idCriador;
    s->numParticipantes = 1;

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

    strcpy(s->status, "Agendada");
    numSessoes++;

    printf("Sessao criada!\n");
}

void enviarMensagem() {

    if (numUsuarios == 0 || numSalas == 0) {
        printf("Necessario ter usuarios e salas cadastrados!\n");
        return;
    }

    NoMensagem *novo = (NoMensagem*) malloc(sizeof(NoMensagem));

    if(novo == NULL){
        printf("Erro de memoria!\n");
        return;
    }

    static int contadorMensagens = 1;

    novo->mensagem.idMensagem = contadorMensagens++;

    printf("ID Usuario: ");
    scanf("%d", &novo->mensagem.idUsuario);

    printf("ID Sala: ");
    scanf("%d", &novo->mensagem.idSala);

    limparBuffer();

    if (novo->mensagem.idUsuario < 1 ||
        novo->mensagem.idUsuario > numUsuarios) {

        printf("Usuario nao encontrado!\n");
        free(novo);
        return;
    }

    if (novo->mensagem.idSala < 1 ||
        novo->mensagem.idSala > numSalas) {

        printf("Sala nao encontrada!\n");
        free(novo);
        return;
    }

    printf("Mensagem: ");
    fgets(novo->mensagem.mensagem,
          sizeof(novo->mensagem.mensagem),
          stdin);

    removerQuebraLinha(novo->mensagem.mensagem);

    strcpy(novo->mensagem.horario, "20:00");

    novo->prox = NULL;

    if(inicioChat == NULL){
        inicioChat = novo;
    }
    else{

        NoMensagem *aux = inicioChat;

        while(aux->prox != NULL){
            aux = aux->prox;
        }

        aux->prox = novo;
    }

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

        printf("Nenhuma sessao cadastrada!\n");
        return;
    }

    for(int i = 0; i < numSessoes; i++){

        printf("\n===== SESSAO =====\n");

        printf("ID: %d\n",
               listaSessoes[i].idSessao);

        printf("Data: %s\n",
               listaSessoes[i].data);

        printf("Horario: %s\n",
               listaSessoes[i].horario);

        printf("Sala: %s\n",
               listaSalas[
               listaSessoes[i].idSala - 1
               ].nomeSala);

        printf("Conteudo: %s\n",
               listaConteudos[
               listaSessoes[i].idConteudo - 1
               ].titulo);

        printf("Status: %s\n",
               listaSessoes[i].status);
    }
}

void iniciarSessao(){

    int idSessao;

    if(numSessoes == 0){
        printf("Nenhuma sessao cadastrada!\n");
        return;
    }

    printf("ID da Sessao: ");
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

    printf("Sessao iniciada com sucesso!\n");
}

void listarMensagens(){

    if(inicioChat == NULL){
        printf("Nenhuma mensagem enviada!\n");
        return;
    }

    NoMensagem *aux = inicioChat;

    while(aux != NULL){

        printf("\n[%s]\n",
               aux->mensagem.horario);

        printf("%s:\n",
               listaUsuarios[
               aux->mensagem.idUsuario - 1
               ].nickname);

        printf("%s\n",
               aux->mensagem.mensagem);

        aux = aux->prox;
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

    int participanteEncontrado = 0;

    for(int i = 0; i < sala->numParticipantes; i++){

        if(sala->participantes[i] == idUsuario){

            participanteEncontrado = 1;
            break;
        }
    }

    if(!participanteEncontrado){

        printf("Voce nao esta nesta sala!\n");
        printf("Entre na sala antes de participar da sessao.\n");
        return;
    }

    if(strcmp(listaSessoes[idSessao - 1].status, "Em Exibicao") != 0){
    printf("A sessao ainda nao foi iniciada!\n");
    return;

    }


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

void carregarDadosIniciais(){

    //USUARIOS
    listaUsuarios[0].idUsuario = 1;
    strcpy(listaUsuarios[0].nome, "Samuel");
    strcpy(listaUsuarios[0].nickname, "Sam");
    strcpy(listaUsuarios[0].status, "Online");

    listaUsuarios[1].idUsuario = 2;
    strcpy(listaUsuarios[1].nome, "Leticia");
    strcpy(listaUsuarios[1].nickname, "lelete");
    strcpy(listaUsuarios[1].status, "Online");

    listaUsuarios[2].idUsuario = 3;
    strcpy(listaUsuarios[2].nome, "Ana Carolina");
    strcpy(listaUsuarios[2].nickname, "Ana");
    strcpy(listaUsuarios[2].status, "Online");

    numUsuarios = 3;

    //SERIES
    listaConteudos[0].idConteudo = 1;
    strcpy(listaConteudos[0].titulo, "Stranger Things");
    strcpy(listaConteudos[0].plataforma, "Netflix");
    strcpy(listaConteudos[0].genero, "Ficcao");

    listaConteudos[1].idConteudo = 2;
    strcpy(listaConteudos[1].titulo, "The Boys");
    strcpy(listaConteudos[1].plataforma, "Prime Video");
    strcpy(listaConteudos[1].genero, "Acao");

    listaConteudos[2].idConteudo = 3;
    strcpy(listaConteudos[2].titulo, "Loki");
    strcpy(listaConteudos[2].plataforma, "Disney+");
    strcpy(listaConteudos[2].genero, "Aventura");

    numConteudos = 3;

    // SALAS
    listaSalas[0].idSala = 1;
    strcpy(listaSalas[0].nomeSala, "Maratona Series");
    listaSalas[0].idCriador = 1;

    listaSalas[0].participantes[0] = 1;
    listaSalas[0].participantes[1] = 2;

    listaSalas[0].numParticipantes = 2;

    strcpy(listaSalas[0].status, "Ativa");

    // SALA 2
    listaSalas[1].idSala = 2;
    strcpy(listaSalas[1].nomeSala, "Filmes de Acao");
    listaSalas[1].idCriador = 2;

    listaSalas[1].participantes[0] = 2;
    listaSalas[1].participantes[1] = 3;

    listaSalas[1].numParticipantes = 2;

    strcpy(listaSalas[1].status, "Ativa");

    numSalas = 2;

    // SESSÕES
    listaSessoes[0].idSessao = 1;
    strcpy(listaSessoes[0].data, "15/06/2026");
    strcpy(listaSessoes[0].horario, "20:00");

    listaSessoes[0].idSala = 1;
    listaSessoes[0].idConteudo = 1;

    strcpy(listaSessoes[0].status, "Agendada");

    // SESSAO 1
    listaSessoes[0].idSessao = 1;
    strcpy(listaSessoes[0].data, "15/06/2026");
    strcpy(listaSessoes[0].horario, "20:00");
    listaSessoes[0].idSala = 1;
    listaSessoes[0].idConteudo = 1;
    strcpy(listaSessoes[0].status, "Agendada");

    // SESSAO 2
    listaSessoes[1].idSessao = 2;
    strcpy(listaSessoes[1].data, "16/06/2026");
    strcpy(listaSessoes[1].horario, "21:00");
    listaSessoes[1].idSala = 1;
    listaSessoes[1].idConteudo = 2;
    strcpy(listaSessoes[1].status, "Agendada");

    // SESSAO 3
    listaSessoes[2].idSessao = 3;
    strcpy(listaSessoes[2].data, "17/06/2026");
    strcpy(listaSessoes[2].horario, "19:30");
    listaSessoes[2].idSala = 1;
    listaSessoes[2].idConteudo = 3;
    strcpy(listaSessoes[2].status, "Agendada");

    // SESSAO 4
    listaSessoes[3].idSessao = 4;
    strcpy(listaSessoes[3].data, "18/06/2026");
    strcpy(listaSessoes[3].horario, "22:00");
    listaSessoes[3].idSala = 2;
    listaSessoes[3].idConteudo = 2;
    strcpy(listaSessoes[3].status, "Agendada");

    numSessoes = 4;
}