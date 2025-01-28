#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define WIDTH 40
#define HEIGHT 20
#define PACMAN 'C'
#define WALL '#'
#define FOOD '*'
#define EMPTY ' '
#define DEMON 'X'

int res = 0;
int score = 0;
int pacmanx,pacmany;
char board[HEIGHT][WIDTH];
int food =0;
int curr =0;
void initialize() {
    for (int i =0; i<HEIGHT; i++) {
        for (int j=0; j<WIDTH; j++) {
            if (i == 0 || j == WIDTH-1 || j==0 || i==HEIGHT-1){
                board[i][j] = WALL;
            }
            else
                board[i][j] = EMPTY;
            }
        }
        int count = 50;
        while (count !=0) {
            int i = (rand()% (HEIGHT+1));
            int j = (rand()% (WIDTH+1));
            if (board[i][j] != WALL && board[i][j] != PACMAN) {
                board[i][j] = WALL;
                count--;
            }
        }
        int val=5;
        while (val--) {
            int row = (rand()% (HEIGHT+1));
            for (int j = 3; j<WIDTH-3; j++) {
                if (board[row][j] !=WALL && board[row][j] != PACMAN) {
                    board[row][j] = WALL;
                }
            }
        }
        count =10;
        while (count != 0) {
            int i= (rand()% (HEIGHT+1));
            int j = (rand()% (WIDTH+1));

            if (board[i][j]!= WALL && board[i][j]!= PACMAN) {
                board[i][j] = DEMON;
                count--;
            }
        }
        pacmanx = WIDTH/2;
        pacmany = HEIGHT/2;
        board[pacmanx][pacmany] = PACMAN;

        for (int i =0; i< HEIGHT; i++) {
            for(int j = 0; j<WIDTH; j++) {
                if (i % 2 ==0 && j % 2==0 && board[i][j] != WALL && board[i][j] != PACMAN && board[i][j] != DEMON) {
                    board[i][j] = FOOD;
                    food++;
                }
            }
        }
    }

void draw() {
    system("cls");
    for (int i =0; i <HEIGHT; i++) {
        for (int j=0; j<WIDTH; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    printf("Skor : %d\n",score);
}

void move(int movex,int movey) {
    int x = pacmanx + movex;
    int y = pacmany + movey;

    if (board[y][x] != WALL) {
        if (board[y][x] == FOOD) {
            score++;
            food--;
            curr++;
            if (food==0) {
                res =2;
                return;
            }
        }
        else if (board[y][x] == DEMON) {
            res =1;
        }
        board[pacmany][pacmanx] = EMPTY;
        pacmanx=x;
        pacmany = y;
        board[pacmany][pacmanx]   = PACMAN;
    }
}

int main() {
    initialize();
    char ch;
    food -=35;
    int totalfood = food;

    printf("W,A,S,D tuslarini kullanarak yonlendirme yapiniz\nCikis icin q\n");
    printf("Devam etmek icin Y tusuna basin:");
    ch = getch();
    if (ch != 'Y' && ch != 'y') {
        printf("Oyundan cikiliyor!");
        return 1;
    }
    while (1)
    {
        draw();
        printf("Total yiyecek sayisi : %d\n",totalfood);
        printf("Total yenen yiyecek : %d\n",curr);
        if (res ==  1) {
            system("cls");
            printf("Oyun bitti!\nOldurulen seytan sayisi : %d\n",score);
            return 1;
        }
        if (res ==  2) {
            system("cls");
            printf("Kazandin!\nSkorun : %d\n",score);
            return 1;
        }
        ch = getch();
        switch (ch) {
            case 'w':
                move(0,-1);
            break;
            case 's':
                move(0,1);
            break;
            case 'a':
                move(-1,0);
            break;
            case 'd':
                move(1,0);
            break;
            case 'q':
                printf("Oyun bitti!\nSkorun :  %d\n",score);
            return 0;
        }
    }
    return 0;
}