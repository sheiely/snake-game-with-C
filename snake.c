#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

char tecla;
int oneTime = 1;
int vivo = 1;


struct positions{
        int x;
        int y;
};





int tamanhoarray = 1;
int qntFrutas = 0;
int pontuation = 0;

struct positions *pose;
struct positions *fruits;


void main()
{
    CleanScreen();
    oneTime = 1;
    vivo = 1;
    tamanhoarray = 1;
    qntFrutas = 0;
    pontuation = 0;
    pose = (struct positions *) malloc(1*sizeof(struct positions));
    fruits = (struct positions *) malloc(1*sizeof(struct positions));
    pose[0].x = 20;
    pose[0].y = 10;
    CreatFruit();

	int p;
    for(p = 0; p<tamanhoarray; p++){
        pose[p].x=pose[0].x-(p*2);
        pose[p].y=pose[0].y;
    }
    CriarMapa();
    Atualizar();

}

void CreatFruit(){
    qntFrutas++;
    fruits = realloc(fruits,qntFrutas*sizeof(struct positions));
    srand(time(NULL));

    fruits[qntFrutas-1].x = (2*(rand() % 39))+2;
    fruits[qntFrutas-1].y = (rand() % 18)+1;


}

void CursorPosition(int x, int y){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}


void CriarMapa(){
    //cria as barras de colisão superiores
    printf("%c", 201);
    int i;
    for(i = 0; i<40; i++){
        printf("%c%c", 205,205);
    };
    printf("%c\n", 187);
    ////////////////////////////////////////

    for(i = 1; i<20; i++){
        CursorPosition(0, i);
        printf("%c", 186);
        CursorPosition(81, i);
        printf("%c", 186);
    }




    //cria as barras de colisão inferiores
    printf("\n%c", 200);
    
    for(i = 0; i<40; i++){
        printf("%c%c", 205, 205);
    };
    printf("%c", 188);
    ////////////////////////////////////////
}


void Atualizar(){


	int p;
    for(p=0; p<tamanhoarray; p++){
        CursorPosition(pose[p].x, pose[p].y);
        printf(" ");
    }



    Movimentar();
    VerificarMorte();

    for(p=0; p<tamanhoarray; p++){
        CursorPosition(pose[p].x, pose[p].y);
        printf("%c", 254);
    }


	int i;
    for(i = 0; i < qntFrutas; i++){
        if(pose[0].x == fruits[i].x && pose[0].y == fruits[i].y){
            pontuation++;
            tamanhoarray++;
            pose = realloc(pose,tamanhoarray*sizeof(struct positions));
            qntFrutas--;
            fruits = realloc(fruits,qntFrutas*sizeof(struct positions));


        }
        if(qntFrutas>0){
           CursorPosition(fruits[i].x, fruits[i].y);
            printf("%c", 208);
        }else{
            CreatFruit();
        }

    }


    CursorPosition(0, 25);
    printf("Pontuacao: %d", pontuation);
    Sleep(200);


    //verifica se ainda esta vivo
    if(vivo == 1){
        Atualizar();
    }else if(vivo == 0){
        CleanScreen();
        CursorPosition(0, 10);
        printf("You is dead >:(\n\n\n\n\n   Pontuation: %d \n\n\n\n\n   Can you be better? Try again pressing any key\n\n\n\n\n\n\n\n\n\n", pontuation);
        system("pause");
        main();


    }
    /////////////////////////////
}



void Movimentar(){
		int i;
        for(i = 0; kbhit(); i++){
                tecla = getch();
        }
        if(tecla == 'w'){
			
            for(i = tamanhoarray-1; i>0; i--){
                pose[i].x = pose[i-1].x;
                pose[i].y =  pose[i-1].y;
            }
            pose[0].y--;
        }else if(tecla == 's'){
            for(i = tamanhoarray-1; i>0; i--){
                pose[i].x = pose[i-1].x;
                pose[i].y =  pose[i-1].y;
            }
            pose[0].y++;
        }else if(tecla == 'd'){
            for(i = tamanhoarray-1; i>0; i--){
                pose[i].x = pose[i-1].x;
                pose[i].y =  pose[i-1].y;
            }
            pose[0].x+=2;
        }else if(tecla == 'a'){
            for(i = tamanhoarray-1; i>0; i--){
                pose[i].x = pose[i-1].x;
                pose[i].y =  pose[i-1].y;
            }
            pose[0].x-=2;
        }
}


void VerificarMorte(){
    if(pose[0].x <1 || pose[0].x >80 || pose[0].y<1 || pose[0].y>19){
        vivo = 0;
    }
    int p;
    for(p = 1; p<tamanhoarray; p++){
        if(pose[0].x == pose[p].x && pose[0].y == pose[p].y){
           vivo = 0;
        }
    }
}

void CleanScreen(){
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #endif
}

