#define MAX_ITENS 50

typedef struct {
    int idUsuario;
    char nomeCoompleto[100];
    char nickname[50];
    char email[100];
    char senha[50];
    char plataformaPreferida[50];
    int totalWatchParties;
    float avaliacaoMedia;
    char status[20]; // Online, Offline, Ocupado
} Usuario;

typedef struct {
    int idSala;
    char nomeSala[100];
    int idCriador;
    int participantes[20];
    int numParticipantes;
    char descricao[200];
    char privacidade[20];
    char codigoAcesso[20];
    char status[20]; // Ativo, Encerrado, Cancelado
} Sala;

typedef struct {
    int idConteudo;
    char titulo[100];
    char plataforma[50];
    char genero[50];
    int anoLancamento;
    int duracaoMinutos;
    float avaliacaoMedia;
} Conteudo;

typedef struct {
    int idAvaliacao;
    int idUsuario;
    int idConteudo;
    float nota;
    char comentario[300];
    char dataAvaliacao[15];
    int recomendaria; // 0 = Não, 1 = Sim
} Avaliacao;

typedef struct {
    int idSessao;
    char nomeSessao[100];
    char data[15];
    char horarioInicio[6];
    int idSala;
    int idAnfitriao;
    int idConteudoPrincipal;
    int participantes[20];
    int numParticipantes;
    char status[50];
} SessaoDeExibicao;

typedef struct {
    int idParticipacao;
    int idUsuario;
    int idSessao;
    char funcao[20]; // Anfitriao, Participante
    char status[20]; // Confirmado, Pendente
    char horarioEntrada[10];
    int tempoAssistido;
} Participacao;

typedef struct {
    int idPlaylist;
    char nomePlaylist[100];
    int idCriador;
    int conteudos[50];
    int numConteudos;
    char descricao[200];
    char categoria[50];
} ListaDeReprducao;

typedef struct {
    int idMensagem;
    int idUsuario;
    int idSala;
    char mensagem[300];
    char dataEnvio[15];
    char horaEvenio[10];
    char tipoMensagem[20]; // Texto, Sistema
} ItemChat;

typedef struct {
    int idConvite;
    int idSala;
    int idRemetente;
    int idDestinatario;
    char status[20]; // Aceito, Pendente, Recusado
    char dataEnvio[15];
    char codigoConvite[20];
} Convite;

Usuario listaUsuarios[MAX_ITENS];
int numUsuarios = 0;

Sala listaSalas[MAX_ITENS];
int numSalas = 0;

SessaoDeExibicao listaSessoes[MAX_ITENS];
int numSessoes = 0;

Conteudo listaConteudos[MAX_ITENS];
int numConteudos = 0;

Participacao listaParticipacoes[MAX_ITENS];
int numParticipacoes = 0;

Avaliacao listaAvaliacoes[MAX_ITENS];
int numAvaliacoes = 0;

Avaliacao listaAvaliacoes[MAX_ITENS];
int numAvaliacoes = 0;

ListaDeReprducao listaPlaylists[MAX_ITENS];
int numPlaylists = 0;

ItemChat listaMensagens[MAX_ITENS];
int numMensagens = 0;

Convite listaConvites[MAX_ITENS];
int numConvites = 0;

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



void exibirMenuPrincipal(){
    printf("\n+-----------------------------------+\n");
    printf("|      WATCH PARTY PLANNER          |\n");
    printf("+-----------------------------------+\n");
    printf("| [1] Gerenciar Usuarios            |\n");
    printf("| [2] Gerenciar Salas               |\n");
    printf("| [3] Gerenciar Conteudos           |\n");
    printf("| [4] Gerenciar Sessoes             |\n");
    printf("| [5] Gerenciar Playlists           |\n");
    printf("| [6] Gerenciar Avaliacoes          |\n");
    printf("| [7] Gerenciar Convites            |\n");
    printf("| [8] Ver Notificacoes              |\n");
    printf("| [9] Sair                          |\n");
    printf("+-----------------------------------+\n");
}
