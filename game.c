#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <stdbool.h>
#include <limits.h>
void printboard(int height, int width, int arr[height][width]);
void play_display(int height, int width);
int choices();
void delete_box();
void draw_box();
void gotoxy(int x,int y);
void display_board(int width,int height);
int main_menu();

//////////main program
int main()
{
    int width, height, choice;

    choice = main_menu();


    if (choice == 1) //////New game
    {
        gotoxy(0, 0);
        printf("please enter the size of your connect four game:");//Prompting width and height
        scanf("%d %d", &height, &width);// i change this

         /* this will be changed to read from file XML after initializing it but
        for now let's cover every thing*/
        /*validation on size not exceeding integer borders or negative*/

        while(width <= 0 || width > INT_MAX || height <= 0 || height > INT_MAX)
        {
            printf("select an appropriate size: ");
            scanf("%d %d", &height, &width);// i change this
        }

        //algorithm of printing
        //display_board(width, height);
        //new algorithm of printing
        play_display(height,width);
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

    draw_box(); // to draw the menu

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

void draw_box(){
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

//will not be used again just leave it if we need it temporary
/*
void display_board(int width,int height){

    /*display board function: display the game board for the user*/
    /*function parameters: 1- Width of the board (number of columns),
                           2- Height of the board (number of rows)*/
/*
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
*/
// function to play and display board after each turn it take two arguments :height and width
void play_display(int height, int width)
{
    int col1,col2; // will stand for columns of two players
    long long int k=width*height; //number of moves
    int moves[height][width];  //array to store moves
    int maxcolsize[width];   // array to check maxsize //all its elements will take value of height and will be decreased if column chosen


   int i,j;
   for(i=0;i<height;i++)
   {
       for(j=0;j<width;j++)
       {
           moves[i][j]=0; //set all moves to default zero
       }

   }
   for(i=0;i<width;i++)
   {
       maxcolsize[i]=height;  // set all values of it to value of height as mentioned
   }

   int turn=1;
     printboard(height,width,moves); //print standrd board

   while(k>0)
   {

       if(turn%2==1) // odd turns player 1
       {
            printf("\n player1,please choose column from 0 to %d:",width-1);
       scanf("%d",&col1);
           while(maxcolsize[col1]<0||col1>width-1||col1<0)// validation on column index
            {
                 printf("this column is no longer valid\n");
                 printf("please choose another one: ");
                 scanf("%d",&col1);
            }

           moves[maxcolsize[col1]][col1]=1; // if player 1 choose a column the row index of it will start from height and will be decreased till zero
             printboard(height,width,moves); // print board after paying
           maxcolsize[col1]--;
           turn++; // increase turns
       }
       else
       {
            printf("\n player2, choose column from 0 to %d:",width-1);
            scanf("%d",&col2);
            while(maxcolsize[col2]<0||col2>width-1||col2<0)
            {
                 printf("this column is no longer valid\n");
                 printf("please choose another one: ");
                 scanf("%d",&col2);
            }
           moves[maxcolsize[col2]][col2]=-1;

             printboard(height,width,moves);

            maxcolsize[col2]--;
           turn++;
           /* system("cls"); */
       }
       k--; //decrease k till zero which will indicate that board is complete
   }





}


void printboard(int height, int width, int arr[height][width]) //this fn will be called in the fn of playing game to display board after each turn
                                                    //it takes height and width and array of moves and display according to value
{

    int i,j;
    for(i=0;i<height;i++)
    {
        printf("\n************************\n");
        for(j=0;j<width;j++)
        {
            if(arr[i][j]==0)
            {
                printf("| |");
            }
            else if(arr[i][j]==1)
            {
                printf("|X|");
            }

           else if(arr[i][j]==-1)
           {
                printf("|O|");
           }
        }
    }

}

// my play fn takes inputs but the display some times don't change
// it is better to test game by yourself to understand it more
