#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;


bool GameOver;
const int altura = 20;
const int largura = 30;
enum eDirecao{ PARADO = 0 , CIMA , BAIXO , DIREITA, ESQUERDA};
eDirecao dir;
int FrutaPosX, FrutaPosY;
int TamanhoRabo, RaboX[100], RaboY[100];
int x, y;

void setup(){
    GameOver = false;
    dir = PARADO;
    x = largura / 2;
    y = altura / 2;
    FrutaPosX = rand() % largura;
    FrutaPosY = rand() % altura;
}

void visual(){
    system("cls");
    for (int i = 0; i < largura+2; i++)
        cout << "#";
    cout << endl;
 
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == FrutaPosY && j == FrutaPosX)
                cout << "*";
            else
            {
                bool Rabo = false;
                for (int k = 0; k < TamanhoRabo; k++)
                {
                    if (RaboX[k] == j && RaboY[k] == i)
                    {
                        cout << "o";
                        Rabo = true;
                    }
                }
                if (!Rabo)
                    cout << " ";
            }
                 
 
            if (j == largura - 1)
                cout << "#";
        }
        cout << endl;
    }
 
    for (int i = 0; i < largura+2; i++)
        cout << "#";
    cout << endl;
}

void logica(){
    int PrevX = RaboX[0];
    int PrevY = RaboY[0];
    int Xanterior, Yanterior;
    RaboX[0] = x;
    RaboY[0] = y;

    for(int i = 1; i < TamanhoRabo; i++){
        Xanterior = RaboX[i];
        Yanterior = RaboY[i];
        RaboX[i] = PrevX;
        RaboY[i] = PrevY;
        PrevX = Xanterior;
        PrevY = Yanterior;
    }

    switch(dir){
        case ESQUERDA:
            x--;
            break;
        case DIREITA:
            x++;
            break;
        case CIMA:
            y--;
            break;
        case BAIXO:
            y++;
            break;
        default:
            break;
    }

    if(x >= largura) x = 0;
    else if(x < 0) x = largura - 1;
    if(y >= altura) y = 0;
    else if(y < 0) y = altura - 1;

    for(int i = 0; i < TamanhoRabo ;i++){
        if(RaboX[i] == x && RaboY[i] == y){
            GameOver = true;
        }
    }

    if(x == FrutaPosX && y == FrutaPosY){
        FrutaPosX = rand() % largura;
        FrutaPosY = rand() % altura;
        TamanhoRabo++;
    }
}

void input(){
    if(_kbhit()){
        switch(_getch()){
            case 'a':
                dir = ESQUERDA;
                break;
            case 's':
                dir = BAIXO;
                break;
            case 'd':
                dir = DIREITA;
                break;
            case 'w':
                dir = CIMA;
                break;
            case 'x':
                GameOver = true;
                break;
        }
    }   


}


int main(){

    setup();

    while(!GameOver){
        visual();
        input();
        logica();
        Sleep(10);
    }


    return 0;
}
