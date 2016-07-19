#include <iostream>
#include <sstream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>

#define  IZQUIERDA 75
#define  DERECHA   77

using namespace std;

/*void pintarAvion(int x );
void pintarInstruccion(void);*/


char avion_l1[]={' ',' ',' ','"',' ',' ',' ',0};
char avion_l2[]={' ','|','*','*','*','|',' ',0};
char avion_l3[]={' ','*',' ','*',' ','*',' ',0};

char Explosion_l1[]={' ',' ','*','*',' ',' ',' ',0};
char Explosion_l2[]={' ','*','*','*','*',' ',' ',0};
char Explosion_l3[]={' ',' ','*','*',' ',' ',' ',0};

char Explosion_r1[]={'*',' ','*','*',' ','*',' ',0};
char Explosion_r2[]={' ','*','*','*','*',' ',' ',0};
char Explosion_r3[]={'*',' ','*','*',' ','*',' ',0};

char Borrar_Avion[]={' ',' ',' ',' ',' ',' ',' ',0};

//VARIABLES GLOBALES
int NumVidas = 3;
int Corazon  = 3;
int ix = 40, iy = 19;

//ASTEROIDES
int y  = 8, x = 12;
int yy = 12, xx = 17;
int x1 = 58, y1 = 6;
int x2 = 70, y2 = 9;

int  i,v;

//VARIABLES PARA RUTINA CAMBIAR DE NIVEL
int  Repeticion = 0, Nivel = 0;
bool Condicion = false;

void gotoxy(int x, int y) //FUNCION QUE POSICIONA
{
    HANDLE hCon;
    COORD  dwPos;

    dwPos.X = x;
    dwPos.Y = y;

    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);

}//funcion gotxy

void Vidas(int vi)
{
    gotoxy(2,1); printf("Vidas %d",vi);
}//vidas

void Barra_Salud(int n)
{
    gotoxy(72,1); printf(" ");
    gotoxy(73,1); printf(" ");
    gotoxy(74,1); printf(" ");

    for(int v = 0; v < n; v++)
    {
        gotoxy(72+v,1); printf("%c",3);
    }//for
}//barra salud

void Explotar()
{
    gotoxy(ix,iy);   puts(Explosion_l1);
    gotoxy(ix,iy+1); puts(Explosion_l2);
    gotoxy(ix,iy+2); puts(Explosion_l3);

    Sleep(380);

    gotoxy(ix,iy);   puts(Explosion_r1);
    gotoxy(ix,iy+1); puts(Explosion_r2);
    gotoxy(ix,iy+2); puts(Explosion_r3);

    Sleep(380);

    gotoxy(ix,iy);   puts(avion_l1);
    gotoxy(ix,iy+1); puts(avion_l2);
    gotoxy(ix,iy+2); puts(avion_l3);

}//explosicion

void Jugar(void)
{
    //RUTINA DE LOS ASTEROIDES
    gotoxy(x,y);   printf("%c",4);
    gotoxy(xx,yy); printf("%c",4);
    gotoxy(x1,y1); printf("%c",4);
    gotoxy(x2,y2); printf("%c",4);

    Sleep(70);

    gotoxy(x,y);   printf(" ");
    gotoxy(xx,yy); printf(" ");
    gotoxy(x1,y1); printf(" ");
    gotoxy(x2,y2); printf(" ");

    if(y > 20)
    {
        y = 4;
        x = (rand() % 70)+6;

        if(y == 4)
        {
            Condicion = false;
        }
    }//if
    if(yy > 20)
    {
        yy = 4;
        xx = (rand() % 70)+6;
    }//if
    if(y1 > 20)
    {
        y1 = 4;
        x1 = (rand() % 70)+6;
    }//if
    if(y2 > 20)
    {
        y2 = 4;
        x2 = (rand() % 70)+6;
    }//if

    //RUTINA PARA MOVER AVION
    if(kbhit())
    {
        unsigned char Tecla = getch();

        switch(Tecla)
        {
        case IZQUIERDA:
            if(ix > 4)
            {
                gotoxy(ix,iy);   puts(Borrar_Avion);
                gotoxy(ix,iy+1); puts(Borrar_Avion);
                gotoxy(ix,iy+2); puts(Borrar_Avion);

                ix-=2;

                gotoxy(ix,iy);   puts(avion_l1);
                gotoxy(ix,iy+1); puts(avion_l2);
                gotoxy(ix,iy+2); puts(avion_l3);
            }//if
            break;

        case DERECHA:
            if(ix < 70)
            {
                gotoxy(ix,iy);   puts(Borrar_Avion);
                gotoxy(ix,iy+1); puts(Borrar_Avion);
                gotoxy(ix,iy+2); puts(Borrar_Avion);

                ix+=2;

                gotoxy(ix,iy);   puts(avion_l1);
                gotoxy(ix,iy+1); puts(avion_l2);
                gotoxy(ix,iy+2); puts(avion_l3);
            }//if
            break;
        }//swicth
    }//if

    //RUTINA PARA GOLPES DE ASTEROIDES
    if((x > ix && x < ix+6 && y == iy-1) || (xx > ix && xx < ix+6 && yy == iy-1)||
       (x1 > ix && x1 < ix+6 && y1 == iy-1) || (x2 > ix && x2 < ix+6 && y2 == iy-1))
    {
        Corazon--;
        Barra_Salud(Corazon);
        printf("\a");
    }//if

    gotoxy(ix,iy);   puts(avion_l1);
    gotoxy(ix,iy+1); puts(avion_l2);
    gotoxy(ix,iy+2); puts(avion_l3);

    if(Corazon == 0)
    {
        NumVidas--;
        Vidas(NumVidas);
        Explotar();
        Corazon = 3;
        Barra_Salud(Corazon);
    }//if

    //RUTINA PARA CAMBIAR DE NIVEL
    if(!Condicion)
    {
        Repeticion++;
        Condicion = true;
    }//if
    if(Repeticion == 10)
    {
        Nivel++;
        gotoxy(35,1); printf("NIVEL %d",Nivel);

        gotoxy(ix,iy);   puts(Borrar_Avion);
        gotoxy(ix,iy+1); puts(Borrar_Avion);
        gotoxy(ix,iy+2); puts(Borrar_Avion);

        iy-=2;

        gotoxy(ix,iy);   puts(avion_l1);
        gotoxy(ix,iy+1); puts(avion_l2);
        gotoxy(ix,iy+2); puts(avion_l3);

        Repeticion = 0;
    }//if

    y++; yy++; y1++; y2++;



}//jugar

int main()
{
    system("Color 3");
    Vidas(NumVidas);
    Barra_Salud(Corazon);
    gotoxy(35,1); printf("NIVEL %d",Nivel);

    gotoxy(ix,iy);   puts(avion_l1);
    gotoxy(ix,iy+1); puts(avion_l2);
    gotoxy(ix,iy+2); puts(avion_l3);

    while(NumVidas > 0 && Nivel <= 6)
    Jugar();

    gotoxy(20,15); printf("GAME OVER");
    getch();
    system("pause>null");
    return 0;
}//main
