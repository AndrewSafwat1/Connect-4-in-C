#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

void choices();
void draw_box();
void gotoxy(int x,int y);
void display_board(int width,int height);
int main_menu();

int main()
{
    int width, height, choice;

    choice = main_menu();

    //Prompting width and height
    if (choice == 1)
    {
        printf("please enter the size of your connect four game:");
        scanf("%d %d", &width, &height);

         /* this will be changed to read from file XML after initializing it but
        for now let's cover every thing*/
        /*validation on size not exceeding integer borders or negative*/

        while(width <= 0 || width > 2147483647 || height <= 0 || height > 2147483647)
        {
            printf("select an appropriate size: ");
            scanf("%d %d", &width, &height);
        }

        //algorithm of printing
        display_board(width, height);
    }

    return 0;
}





void gotoxy(int x,int y)
{
    COORD coord= {0,0};
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int main_menu(){
    draw_box();
    choices();

}

void choices(){
    int position = 1;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    gotoxy(40, 10);
    printf("  Welcome to connect 4 game!");

    do{
    gotoxy(40, 11);
    printf("1] New game.                  ");

    gotoxy(40, 12);
    printf("2] Load game                  ");

    gotoxy(40, 13);
    printf("3] Top scores                 ");

    gotoxy(40, 14);
    printf("4] Quit                       \n");


    int choose = getch();

    if(choose == 38)
        position -= 1;
    else if(choose == 40)
        position += 1;


    switch(position)
    {


        case 1: SetConsoleTextAttribute(console, 240);
                gotoxy(40, 11);
                printf("1] New game.                  ");
                SetConsoleTextAttribute(console, 15);
                break;

        case 2: SetConsoleTextAttribute(console, 240);
                gotoxy(40, 12);
                printf("2] Load game                  ");
                SetConsoleTextAttribute(console, 15);
                break;

        case 3: SetConsoleTextAttribute(console, 240);
                gotoxy(40, 13);
                printf("3] Top scores                 ");
                SetConsoleTextAttribute(console, 15);
                break;

        case 4: SetConsoleTextAttribute(console, 240);
                gotoxy(40, 14);
                printf("4] Quit                       \n");
                SetConsoleTextAttribute(console, 15);
                break;

        case 0: position += 4;
                SetConsoleTextAttribute(console, 240);
                gotoxy(40, 14);
                printf("4] Quit                       \n");
                SetConsoleTextAttribute(console, 15);
                break;

        case 5: position -= 4;
                SetConsoleTextAttribute(console, 240);
                gotoxy(40, 10);
                printf("  Welcome to connect 4 game!");
                SetConsoleTextAttribute(console, 15);
                break;
     }
    }while(1);
}

void draw_box(){
    gotoxy(39, 9);
    printf("%c", 201);

    for(int i = 0; i < 30; i++)
    {
        printf("%c", 205);
    }

    printf("%c", 187);



    for(int i = 0; i < 5 ; i++)
    {
        gotoxy(39, 10+i);

        printf("%c", 186);

        for(int j = 0; j < 30; j++)
        {
            printf(" ");
        }

        printf("%c\n", 186);
    }

    gotoxy(39, 15);
    printf("%c", 200);

    for(int i = 0; i < 30; i++)
    {
        printf("%c", 205);
    }

    printf("%c", 188);

}


void display_board(int width,int height){

    /*display board function: display the game board for the user*/
    /*function parameters: 1- Width of the board (number of columns),
                           2- Height of the board (number of rows)*/

    int i,j;

    for (i=0; i < width; i++) {
        printf ("+");

        for (j=0; j < height; j++)
            printf("-+");

        printf ("\n");
        printf ("|");

        for (j=0; j < height; j++)
            printf(" |");

        printf ("\n");
    }

    printf ("+");

    for (j=0; j < height; j++)
        printf("-+");

    printf ("\n");
}
