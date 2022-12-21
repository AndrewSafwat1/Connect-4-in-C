#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <stdbool.h>
#include <limits.h>

void greet_players(int mode);
int choices_mode();
int prompt_mode();
void play(int width,int height);
int choices();
void delete_box();
void draw_box_main();
void gotoxy(int x,int y);
void display_board(int width,int height);
int main_menu();

//////////main program
int main()
{
    int width, height, choice, mode;

    choice = main_menu();


    if (choice == 1) //////New game
    {
        mode = prompt_mode();
        if (mode == 1) //vs computer
        {
            greet_players(1);

        }
        else if (mode == 2) // 2 players
        {
            gotoxy(0, 0);
            greet_players(2);

            printf("please enter the height and the width of your connect 4 board (separated by a space):"); //Prompting width and height
            scanf("%d %d", &width, &height);



             /* this will be changed to read from file XML after initializing it but
            for now let's cover every thing*/
            /*validation on size not exceeding integer borders or negative*/

            while(width <= 0 || width > INT_MAX || height <= 0 || height > INT_MAX)
            {
                printf("select an appropriate size: ");
                scanf("%d %d", &width, &height);
            }
            //initializing board array
            char board[height * 2 + 1][width * 2 + 2];

            //algorithm of printing

            display_board(width, height);
        }
        else // to main menu
        {
            main();
        }



    }
    else if(choice == 2) // Load game
    {

    }
    else if(choice == 3) // Top scores
    {

    }
    else //Exit
    {
        return 0;
    }


    return 0;
}



void gotoxy(int x,int y){
    /*
    function responsible for moving freely in the console
    */
    COORD coord= {0,0};
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main_menu(){
    /*
    main menu window with four choices to choose from the function.

    returns 1, 2, 3 or 4 according to user keyboard input "Enter" or "ESC" buttons

    choice 1 "only accessed by Enter" is responsible for creating new game

    choice 2 "only accessed by Enter" is responsible for loading the previous game

    choice 3 "only accessed by Enter" is responsible for showing top scores

    choice 4 "accessed by both Enter and ESC" is responsible for closing the program

    */
    int choice;

    draw_box_main(); // to draw the menu

    choice = choices();

    delete_box(); // clear the console

    return choice;
}

int choices(){
    int position = 1, choose;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    ShowConsoleCursor(false); //to hide white dash in console

    gotoxy(40, 10);
    printf("  Welcome to connect 4 game!  ");

    do{
        SetConsoleTextAttribute(console, 15); // initial form of the menu
        gotoxy(40, 11);
        printf(" 1] New game.                 ");

        gotoxy(40, 12);
        printf(" 2] Load game                 ");

        gotoxy(40, 13);
        printf(" 3] Top scores                ");

        gotoxy(40, 14);
        printf(" 4] Quit                      \n");


        switch(position)
        {


            case 1: SetConsoleTextAttribute(console, 240); // for highlighting the choice
                    gotoxy(40, 11);
                    printf(" 1] New game.                 ");
                    break;

            case 2: SetConsoleTextAttribute(console, 240);
                    gotoxy(40, 12);
                    printf(" 2] Load game                 ");
                    break;

            case 3: SetConsoleTextAttribute(console, 240);
                    gotoxy(40, 13);
                    printf(" 3] Top scores                ");
                    break;

            case 4: SetConsoleTextAttribute(console, 240);
                    gotoxy(40, 14);
                    printf(" 4] Quit                      \n");
                    break;

            case 0: position += 4;
                    SetConsoleTextAttribute(console, 240);
                    gotoxy(40, 14);
                    printf(" 4] Quit                      \n");
                    break;

            case 5: position -= 4;
                    SetConsoleTextAttribute(console, 240);
                    gotoxy(40, 11);
                    printf(" 1] New game.                 ");
                    break;
        }

        choose = getch();

        switch(choose)
        {
            case -32:choose = getch();
                     break;

            case 80: position ++;
                     break;

            case 72: position --;
                     break;
        }

    }while(choose != 13 && choose != 27);

    if(choose == 27)
    {
        position = 4;
    }

    SetConsoleTextAttribute(console, 15); // get the console back to its default mode

    ShowConsoleCursor(true); // to get the white dash in the console back

    return position;

}

void ShowConsoleCursor(bool showFlag){
    /*
    responsible for hiding the white dash in the console while the user is in the main menu.
    parameters: true  -> to show the white dash
                false -> to hide the white dash
    */
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void draw_box_main(){
    /*
    responsible for creating the border of the main menu window
    hint: check extended ASCII (DOS) code for the values: 201, 205, 187, 186, 200, 188 --> in (ASCII_Extended.png) attached with this file


    */
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

void delete_box(){
    /*
    responsible for clearing the screen after the main menu is done
    */
    system("cls");
}

int prompt_mode(){
    /*
    similar to main menu but it differs only on return value which has range of 1 - 3
    choice 1: to play vs computer
    choice 2: to play vs player
    choice 3: to return to main menu
    */
    int choice;

    draw_box_main(); // to draw the menu

    choice = choices_mode(); // to get the choice

    delete_box(); // clear the console

    return choice;
}

int choices_mode(){
    int position = 1, choose;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    ShowConsoleCursor(false); //to hide white dash in console

    do{
        SetConsoleTextAttribute(console, 15); // initial form of the menu
        gotoxy(40, 11);
        printf(" 1] Single player             ");

        gotoxy(40, 12);
        printf(" 2] Multiplayer               ");

        gotoxy(40, 13);
        printf(" 3] Main menu                 ");

        switch(position)
        {


            case 1: SetConsoleTextAttribute(console, 240); // for highlighting the choice
                    gotoxy(40, 11);
                    printf(" 1] Single player             ");
                    break;

            case 2: SetConsoleTextAttribute(console, 240);
                    gotoxy(40, 12);
                    printf(" 2] Multiplayer               ");
                    break;

            case 3: SetConsoleTextAttribute(console, 240);
                    gotoxy(40, 13);
                    printf(" 3] Main menu                 ");
                    break;


            case 0: position += 3;
                    SetConsoleTextAttribute(console, 240);
                    gotoxy(40, 13);
                    printf(" 3] Main menu               \n");
                    break;

            case 4: position -= 3;
                    SetConsoleTextAttribute(console, 240);
                    gotoxy(40, 11);
                    printf(" 1] Single player             ");
                    break;
        }

        choose = getch();

        switch(choose)
        {
            case -32:choose = getch();
                     break;

            case 80: position ++;
                     break;

            case 72: position --;
                     break;
        }

    }while(choose != 13 && choose != 27);

    if(choose == 27)
    {
        position = 3;
    }

    SetConsoleTextAttribute(console, 15); // get the console back to its default mode

    ShowConsoleCursor(true); // to get the white dash in the console back

    return position;
}

void greet_players(int mode){
    /*
    to say hello to the players
    its parameter -mode- has only two values: 1- to greet the player in single player mode
                                              2- to greet the two players in multiplayer mode
     */
    printf("Hello user1, ");
    if(mode == 1)
    {
        printf("\n");
    }
    else
    {
        printf("user2\n");
    }
    printf("let's start our game\n");
}


void display_board(int width,int height){

    /*
    display board function: display the game board for the user
    function parameters: 1- Width of the board (number of columns),
                           2- Height of the board (number of rows)
    */
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
       /* algorithm of playing game(2 players mode)*///ANDREW PUT THIS IN THE CHOICE OF CHOOSING 2 PLAYERS MODE

   play(width,height);

}

void play(int width,int height)
{
    int turn,col;
    for(turn=1;turn<=width*height;turn++)
    {
        if(turn%2==1)
        {

            printf("\r your turn player 1 , choose a column from 1 to %d to put your x \b \n",width);
            scanf("%d",&col);
        }
        else
        {
            fflush(stdout);
            printf("\r your turn player 2 , choose a column from 1 to %d to put your o \b \n ",width);
            scanf("%d",&col);

        }

    }

}
