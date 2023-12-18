/*

TP1
FEITO POR NICOLAS HENRIQUE DIAS XAVIER;

*/

#include <stdio.h>
#include <stdlib.h>

int preencher_tabuleiro(int jogador[10][10]){
    // A função recebe como parâmetro o tabuleiro vazio e o preenche (0-Água, 1-Navio).
    int num_barcos;
    scanf("%d", &num_barcos);
    int barcos[num_barcos][4];
    char sentido;

    // Recebendo as entradas de cada barco e armazenando no vetor barcos:
    for (int i=0; i<num_barcos; i++){
        scanf("%d %c %d %d", &barcos[i][0], &sentido, &barcos[i][2], &barcos[i][3]);
        barcos[i][1] = (sentido=='h') ? 1 : 2;
    }
    
    // Preenchendo todo o tabuleiro com 0:
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            jogador[i][j] = 0;
        }
    }
    
    // Posicionando os barcos:
    int x0, y0, x, y;
    for(int i=0; i<num_barcos; i++){
        x0 = barcos[i][2];
        y0 = barcos[i][3];
        for(int t=0; t<barcos[i][0]; t++){
            if(barcos[i][1]==2){
                x = x0+t;
                if(x>9){x -= 10;}
                y=y0;
            }
            else{
                x=x0;
                y = y0+t;
                if(y>9){y -= 10;}
            }
            jogador[x][y]=1;
        }
    }

    return 0;
}

int print_tabuleiro(int jogador[10][10]){
    // A função recebe como parâmetro o tabuleiro preenchido e o imprime com a formatação adequada.
    printf("  |" );
    for (int j=0; j<10; j++) {
        printf(" %d", j);
    }
    printf("\n" );
    printf("--+" );
    for (int j=0; j<10-3; j++) {
        printf ("---" );
    }
    printf("\n");
    
    for (int i=0; i<10; i++) {
        printf ("%d |", i );
        for (int j=0; j<10; j++) {
            printf(" %d", jogador[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

int ataque_normal(int pos[2], int atacado[10][10]){
    // A função recebe como parâmetro as coordenadas do ataque e o tabuleiro atacado e execulta a ofensiva.
    int acerto = 0;
    if(atacado[pos[0]][pos[1]]==1){
        atacado[pos[0]][pos[1]] = 0;
        acerto = 1;
    }
    // Retorna se houve um acerto
    return acerto;
}

int ataque_especial(int pos[2], int atacado[10][10]){
    // A função recebe como parâmetros a coordenada vertical ou horizontal de ataque e o tabuleiro atacado e execulta a ofensiva.
    for(int i=0; i<10; i++){
        if(pos[0]==1){atacado[pos[1]][i] = 0;}
        else{atacado[i][pos[1]] = 0;}
    }
    return 0;
}

int resultado(int jogador_1[10][10], int jogador_2[10][10]){
    // A função recebe como parâmetros os tabuleiros e verifica se há um ganhador ao final da batalha.
    int contagem_1=0, contagem_2=0, ganhador=0;
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            contagem_1 += (jogador_1[i][j]==1) ? 1 : 0;
            contagem_2 += (jogador_2[i][j]==1) ? 1 : 0;
        }
    }
    if(contagem_1>0 && contagem_2==0){ganhador=1;}
    if(contagem_2>0 && contagem_1==0){ganhador=2;}

    return ganhador;
}

int main() {
    // Iniciando e preenchendo cada um dos tabuleiros 
    int jogador_1[10][10], jogador_2[10][10], num_ataques;
    
    preencher_tabuleiro(jogador_1);

    preencher_tabuleiro(jogador_2);

    // Guardando os dados de ataque no vetor batalha
    scanf("%d", &num_ataques);
    char sentido, tipo_atk;
    int atk, coord[2], combo_1=0, combo_2=0, batalha[num_ataques][3];

    for(int i=0; i<num_ataques; i++){
        scanf(" %c", &tipo_atk);
        batalha[i][0] = (tipo_atk=='n') ? 1 : 2;
        if(batalha[i][0] == 1){
            scanf(" %d %d", &batalha[i][1], &batalha[i][2]);
        }
        else{
            scanf(" %c %d", &sentido, &batalha[i][2]);
            batalha[i][1] = (sentido == 'h') ? 1 : 2;
        }
    }

    // Realizando as rodadas de ataques alternados
    for(int i=0; i<num_ataques; i++){
        coord[0] = batalha[i][1];
        coord[1] = batalha[i][2];
        if(batalha[i][0] == 1){
            if(i%2==0){
                // Ataque normal dos Algoritmistas
                atk = ataque_normal(coord, jogador_2);
                combo_1 = (atk==1) ? combo_1+1 : 0;
            }
            else{
                // Ataque normal dos Estruturistas
                atk = ataque_normal(coord, jogador_1);
                combo_2 = (atk==1) ? combo_2+1 : 0;
            }
        }
        else {
            if(i%2==0){
                // Ataque especial dos Algoritmistas
                if(combo_1 >= 2){ataque_especial(coord, jogador_2);}
                combo_1=0;
            }
            else if(i%2==1){
                // Ataque especial dos Estruturistas
                if(combo_2 >= 2){ataque_especial(coord, jogador_1);}
                combo_2=0;
            }
        }
    }

    // Printando o estado final de cada jogador
    print_tabuleiro(jogador_1);
    print_tabuleiro(jogador_2);

    // Printando o resultado (0-Empate, 1-Algoritmistas, 2-Estruturistas)
    printf("%d", resultado(jogador_1, jogador_2));

    return 0;
}