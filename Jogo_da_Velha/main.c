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
        switch(resposta)
        {
            case 1:
                get_nome(partida.nome_jogador_X, 'X');
                get_nome(partida.nome_jogador_O, 'O');
                game(&partida);
            break;

            case 2:
                exit(0);
            break;
        }
        caractere = resposta+'0';//converte int em char para fazer o tratamento adequado caso o usuário digite letras como resposta
        fflush(stdin);//limpa o buffer para não entrar e. looping infinito
    }while(caractere!='1' && caractere!='2');//confere se o usuário digitou uma opção válida 

    return 0;
}

//apresenta as opções para o usuário e lê sua resposta 
int menu()
{
    int opcao;
    printf("********* Jogo da Velha *************\n");
    printf("1.Novo Jogo\n");
    printf("2.Sair\n");
    scanf("%d", &opcao);

    return opcao;
}

//solicita o nome do jogador é armazena na struct jogo
void get_nome(char *nome_jogador, char simbolo_jogador)
{
    char caractere;
    int contador;

    printf("Digite o nome do jogador %c (maximo 10 caracteres)\n", simbolo_jogador);
    fflush(stdin);
    gets(nome_jogador);
}

//chama os métodos necessários e na sequência adequada para realizar o jogo
void game(struct JOGO *partida)
{
    char tentativa[2];//armazena as coordenadas que o usuário escolhe para jogar
    partida->id_jogo=gera_id_jogo();
    printf("ID jogo %d\n", partida->id_jogo);
    partida->resultado = ' ';//inicializa o resultado do jogo deixando em aberto até que o jogo termine
    inicializa_tabuleiro(partida->tabuleiro);
    sorteia_iniciante(partida);

    do
    {
        exibe_tabuleiro(partida->tabuleiro);
        movimento(tentativa);
        converter_coordenada(tentativa);

        if(grava_movimento(partida->tabuleiro, partida->vez, tentativa)==200)
        {//se o método retornarr 200 o movimento foi bem sucedido
            altera_vez(partida); //como o movimento foi feito, o outro jogador deve fazer o próximo movimento 
            partida->resultado = exibe_resultado(partida->tabuleiro);//analisa o tabuleiro para obter o resultado atual
        }//se o movimento não for bem sucedido é solicitado que o mesmo jogador escolha outra posição para jogar
    }while(partida->resultado==' '); 
}

//percorre o campo tabuleiro da struct para liberar todas as posições  
void inicializa_tabuleiro(char tabuleiro[][3])
{
    for(int linha=0 ; linha<3 ; linha++)
    {
        for(int coluna=0 ; coluna<3 ; coluna++)
            tabuleiro[linha][coluna]=' ';
    }
}

//gera número aleatório para sortear iniciante
void sorteia_iniciante(struct JOGO *partida)
{
    int numero_aleatorio = rand() % RAND_MAX;
    if(numero_aleatorio % 2 == 0)//se o número for par o jogador X começa o jogo 
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

//percorre a matriz tabuleiro e imprimi na tela
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

//lê as coordenadas do tabuleiro digitadas pelo usuário e armazena no vetor tentativa 
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
//adequa a posi�ao informada pelo usuario ao indice padrao da matriz que � x e y = 0 no canto esquerdo superior
void converter_coordenada(char *tentativa)
{
    if(tentativa[COORDENADA_LINHA]=='0')
        tentativa[COORDENADA_LINHA]='2';

    else if(tentativa[COORDENADA_LINHA]=='2')
        tentativa[COORDENADA_LINHA]='0';
}

int grava_movimento(char tabuleiro[][3], char vez, char *tentativa)
{
    int indice_linha = tentativa[COORDENADA_LINHA] - '0'; // transforma char em inteiro
    int indice_coluna = tentativa[COORDENADA_COLUA] - '0';//pra usa-la como índice 
    if(tabuleiro[indice_linha][indice_coluna] == ' ')
    {
        tabuleiro[indice_linha][indice_coluna] = vez;
        return 200;//retorna 200 se a tentativa foi em uma posição livre do tabuleiro 
    }
    else
        printf("Posi�ao ocupada, escolha outra\n");
        
    return 1;//retorna 1 se a tentativa não foi validada
}

//determina quem será o próximo jogador 
void altera_vez(struct JOGO *partida)
{
    if(partida->vez=='X')
        partida->vez='O';
    else
        partida->vez='X';

    printf("player: %c\n", partida->vez);
}

//percorre o tabuleiro para conferir se há algum ganhador 
char checa_tabulerio(char tabuleiro[][3])
{
    //checa as linhas
    for(int linha=0 ; linha<3 ; linha++)
    {
        if(tabuleiro[linha][0]==tabuleiro[linha][1] && tabuleiro[linha][0]==tabuleiro[linha][2])
        //se uma todos os campos de uma linha estão preenchidos pelo mesmo caractere, há um ganhador 
            return tabuleiro[linha][0];//retorna o caractere, o qual equivale ao ganhador 
    }

    //checa as colunas 
    for(int coluna=0 ; coluna<3 ; coluna++)
    {
        if(tabuleiro[0][coluna]==tabuleiro[1][coluna] && tabuleiro[0][coluna]==tabuleiro[2][coluna])
            return tabuleiro[0][coluna];
    }

    //checa a diagonal principal 
    if(tabuleiro[0][0]==tabuleiro[1][1] && tabuleiro[1][1]==tabuleiro[2][2])
        return tabuleiro[0][0];
    
    //checa a diagonal secundária 
    if(tabuleiro[0][2]==tabuleiro[1][1] && tabuleiro[1][1]==tabuleiro[2][0])
        return tabuleiro[0][2];

    return ' ';//se não há vencedor retorna espaço como resultado 
}

//percorre o tabuleiro para analisar se todas as posições já foram preenchidas 
char tabuleiro_completo(char tabuleiro[][3])
{
    for(int linha=0 ; linha<3 ; linha++)
        for(int coluna=0 ; coluna<3 ; coluna++)
            if(tabuleiro[linha][coluna]== ' ')
                return ' ';
    return 'V';//retorna v se estiver completo
}

char exibe_resultado(char tabuleiro[][3])
{
    char resultado = checa_tabulerio(tabuleiro);//verificar se houve ganhador
    if(resultado != ' ')
    {
        printf("msg: Partida finalizada");
        printf("winner: %c", resultado);
        return resultado;
    }
    else//se não houve ganhador verifica se o tabuleiro está todo preenchido
    {
        resultado = tabuleiro_completo(tabuleiro);//se estiver todo preenchido, o jogo empatou
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
