#include <stdio.h>
#include <stdlib.h>

#define RAND_MAX 100 //define o numero maximo para a faixa de numeros aleatorios
#define COORDENADA_LINHA 1 //define a posicao da coordenada referente a linha do tabuleiro no vetor tentatia
#define COORDENADA_COLUA 0 //define a posicao da coordenada referente a coluna do tabuleiro no vetor tentatia

struct JOGO
{
    char nome_jogador_X[11];
    char nome_jogador_O[11];
    int id_jogo;
    char tabuleiro[3][3];
    char vez;
    char resultado;
};

//prototipos das funcoes
int menu(void);
void get_nome(char *nome_jogador, char simbolo_jogador);
void game(struct JOGO *partida);
void inicializa_tabuleiro(char tabuleiro[][3]);
void soteia_iniciante(struct JOGO *partida);
void exibe_tabuleiro(char tabuleiro[][3]);
void movimento(char *tentativa);
void converter_coordenada(char *tentativa);
int grava_movimento(char tabuleiro[][3], char vez, char *tentativa);
void altera_vez(struct JOGO *partida);
char checa_tabulerio(char tabuleiro[][3]);
char tabuleiro_completo(char tabuleiro[][3]);
char exibe_resultado(char tabuleiro[][3]);
int gera_id_jogo(void);

int main()
{
    struct JOGO partida;
char caractere;
    int resposta;
    do{
        resposta = menu();
            switch(resposta){

    case 1:
        get_nome(partida.nome_jogador_X, 'X');
        get_nome(partida.nome_jogador_O, 'O');
        game(&partida);
        break;


    case 2:

        exit(0);
        break;
    }
caractere = resposta+'0';
fflush(stdin);
}while(caractere!='1' && caractere!='2');

    return 0;
}

int menu()
{
    int opcao;
    printf("********* Jogo da Velha *************\n");
    printf("1.Novo Jogo\n");
    printf("2.Sair\n");
    scanf("%d", &opcao);

    return opcao;
}

void get_nome(char *nome_jogador, char simbolo_jogador)
{
    char caractere;
    int contador;

    printf("Digite o nome do jogador %c (maximo 10 caracteres)\n", simbolo_jogador);
    fflush(stdin);
    gets(nome_jogador);
}

void game(struct JOGO *partida)
{
    partida->id_jogo=gera_id_jogo();
    printf("ID jogo %d\n", partida->id_jogo);
    char tentativa[2];
    partida->resultado = ' ';
    inicializa_tabuleiro(partida->tabuleiro);
    sorteia_iniciante(partida);

    do
    {
        exibe_tabuleiro(partida->tabuleiro);
        movimento(tentativa);
        converter_coordenada(tentativa);

        if(grava_movimento(partida->tabuleiro, partida->vez, tentativa)==200)
        {
            altera_vez(partida);
            partida->resultado = exibe_resultado(partida->tabuleiro);
        }
    }
    while(partida->resultado==' ');
}

void inicializa_tabuleiro(char tabuleiro[][3])
{
    for(int linha=0 ; linha<3 ; linha++)
    {
        for(int coluna=0 ; coluna<3 ; coluna++)
            tabuleiro[linha][coluna]=' ';
    }
}

void sorteia_iniciante(struct JOGO *partida)
{
    int numero_aleatorio = rand() % RAND_MAX;
    if(numero_aleatorio % 2 == 0)
    {
        printf("firstPlayer: X(%s)\n", partida->nome_jogador_X);
        partida->vez='X';
    }
    else
    {
        printf("firstPlayer: O(%s)\n", partida->nome_jogador_O);
        partida->vez='O';
    }
}

void exibe_tabuleiro(char tabuleiro[][3])
{
    for(int linha=0 ; linha<3 ; linha++)
    {
        for(int coluna=0 ; coluna<3 ; coluna++)
        {
            printf("%c", tabuleiro[linha][coluna]);

            if(coluna==0 || coluna==1)
                printf(" |");
        }
        printf("\n");
        if(linha==0 || linha==1)
        {
            printf("--|--|--");
        }
        printf("\n");
    }
}

void movimento(char *tentativa)
{
    char coluna;
    char linha;




    printf("Digite a posicao da jogada:\n");
    printf("OBS: coordenadas x e y = 0 no canto inferior esquerdo.\n");
    do
    {
        printf("x(coluna):");
        fflush(stdin);
        scanf("%c", &coluna);
    }
    while(coluna!='0' && coluna!='1' && coluna!='2');  //verifica se o usuario digitou caractere valido como posicao do tabuleiro

    do
    {
        printf("y(linha):");
        fflush(stdin);
        scanf("%c", &linha);
    }
    while(linha!='0' && linha!='1' && linha!='2'); //verifica se o usuario digitou caractere valido como posicao do tabuleiro

    tentativa[COORDENADA_COLUA]=coluna;
    tentativa[COORDENADA_LINHA]=linha;
}

//como o desafio pede que o x e y = 0 no canto inferior esquerdo
//adequa a posiçao informada pelo usuario ao indice padrao da matriz que é x e y = 0 no canto esquerdo superior
void converter_coordenada(char *tentativa)
{
    if(tentativa[COORDENADA_LINHA]=='0')
        tentativa[COORDENADA_LINHA]='2';

    else if(tentativa[COORDENADA_LINHA]=='2')
        tentativa[COORDENADA_LINHA]='0';
}

int grava_movimento(char tabuleiro[][3], char vez, char *tentativa)
{
    //tentativa[COORDENADA_LINHA]
    //tentativa[COORDENADA_COLUA]

    int indice_linha = tentativa[COORDENADA_LINHA] - '0'; // transforma char em inteiro
    int indice_coluna = tentativa[COORDENADA_COLUA] - '0';
    if(tabuleiro[indice_linha][indice_coluna] == ' ')
    {
        tabuleiro[indice_linha][indice_coluna] = vez;
        //exibe_tabuleiro(tabuleiro);
        return 200;
    }
    else
        printf("Posiçao ocupada, escolha outra\n");

    return 1;
}

void altera_vez(struct JOGO *partida)
{
    if(partida->vez=='X')
        partida->vez='O';
    else
        partida->vez='X';

    printf("player: %c\n", partida->vez);
}

char checa_tabulerio(char tabuleiro[][3])
{
    for(int linha=0 ; linha<3 ; linha++)
    {
        if(tabuleiro[linha][0]==tabuleiro[linha][1] && tabuleiro[linha][0]==tabuleiro[linha][2])
            return tabuleiro[linha][0];
    }

    for(int coluna=0 ; coluna<3 ; coluna++)
    {
        if(tabuleiro[0][coluna]==tabuleiro[1][coluna] && tabuleiro[0][coluna]==tabuleiro[2][coluna])
            return tabuleiro[0][coluna];
    }

    if(tabuleiro[0][0]==tabuleiro[1][1] && tabuleiro[1][1]==tabuleiro[2][2])
        return tabuleiro[0][0];

    if(tabuleiro[0][2]==tabuleiro[1][1] && tabuleiro[1][1]==tabuleiro[2][0])
        return tabuleiro[0][2];

    return ' ';
}

char tabuleiro_completo(char tabuleiro[][3])
{
    for(int linha=0 ; linha<3 ; linha++)
        for(int coluna=0 ; coluna<3 ; coluna++)
            if(tabuleiro[linha][coluna]== ' ')
                return ' ';
    return 'V';
}

char exibe_resultado(char tabuleiro[][3])
{
    char resultado = checa_tabulerio(tabuleiro);
    if(resultado != ' ')
    {
        printf("msg: Partida finalizada");
        printf("winner: %c", resultado);
        return resultado;
    }
    else
    {
        resultado = tabuleiro_completo(tabuleiro);
        if(resultado == 'V')
        {
            printf("msg: Partida finalizada!\n");
            printf("winner: Draw\n");
            return resultado;
        }
    }

    return ' ';
}

int gera_id_jogo()
{
    int id = rand() % RAND_MAX;
    return id;
}
