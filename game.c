#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

int first_value1 = -1;///
int first_value2 = -1;
void push1_value(int, int stack_undo_value[]);///
void push2_value(int, int stack_redo_value[]);
int isEmpty1_value();///
int isEmpty2_value();
int pop1_value(int stack_undo_value[]);///
int pop2_value(int stack_redo_value[]);

// stack undo bottom element //UNDO AS 1 , REDO AS 2
int first1 = -1;
int first2 = -1;

int row, column;

void push1(int *, int *stack_undo[]); // adds the address of new element of ##our array to the ##undo array
void push2(int *, int *stack_redo[]); // adds the address of the popped element of the ##undo array to the ##redo array

int isEmpty1(); // checks if ##undo stack is empty or not
int isEmpty2(); // checks if ##redo stack is empty or not

int *pop1(int *stack_undo[]); // pops the top element of the ##undo stack (in order to push it to ##redo stack)
int *pop2(int *stack_redo[]); // pops the top element of the ##redo stack (in order to push it to ##undo stack)

// THERE IS NO isFull function in both stacks , as the game is limited by elements = rows * columns


int horizontal_check(int height, int width, int arr[height][width], int xo, int, int, int);
int vertical_check(int height, int width, int arr[height][width], int xo, int, int, int);
int diagonal_check_45(int height, int width, int arr[height][width], int xo, int, int, int);
int diagonal_check_135(int height, int width, int arr[height][width], int xo, int, int, int);

void check_score(int height, int width, int arr[height][width], int xo);

void play_display_with_computer(int row, int column, int arr[row * 2 + 1][column * 4 + 1]);

void display_time(clock_t start, clock_t end);
void save1(int k,int turn ,int column,int height , int width , int arr[height][width],int maxcolsize[column+1]);
void init_array(int height, int width, int arr[height][width]);               /// RECENTLY ADDED
void printboard(int height, int width, int arr[height][width]);               /// RECENTLY ADDED
void play_display(int row, int column, int arr[row*2+1][column*4+1], int* stack_undo[], int* stack_redo[], int stack_undo_value[], int stack_redo_value[]); ///edited
void greet_players(int mode);
int choices_mode();
int prompt_mode();
void play(int width, int height);
int choices();
void delete_box();
void draw_box_main();
void gotoxy(int x, int y);
void display_board(int width, int height); // DELETED
int main_menu();

//////////main program
int main()
{
    clock_t start, end;

    start = clock(); // defining start time

    int width, height, row, column, choice, mode;

    choice = main_menu();

    if (choice == 1) //////New game
    {

        mode = prompt_mode();
        if (mode == 1) // vs computer
        {
            gotoxy(0, 0);
            greet_players(1);
            ShowConsoleCursor(true);                                                                  // to get the white dash in the console back
            printf("Enter the height and the width of your connect 4 board (separated by a space):"); // Prompting width and height
            scanf("%d %d", &row, &column);                                                            // i change this

            /* this will be changed to read from file XML after initializing it but
           for now let's cover every thing*/
            /*validation on size not exceeding integer borders or negative*/

            while (column <= 0 || column > INT_MAX || row <= 0 || row > INT_MAX)
            {
                printf("select an appropriate size: ");
                scanf("%d %d", &row, &column); // i change this
            }

            width = column * 4 + 1;
            height = row * 2 + 1;

            int arr[height][width];

            init_array(height, width, arr);

            sleep(1);
            system("cls");

            // algorithm of printing
            // display_board(width, height);
            // new algorithm of printing

            srand(time(NULL));
            play_display_with_computer(row, column, arr);

            /* this will be changed to read from file XML after initializing it but
           for now let's cover every thing*/
            /*validation on size not exceeding integer borders or negative*/

            // algorithm of printing

            // display_board(width, height); //DELETED
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (mode == 2) // 2 players
        {
            gotoxy(0, 0);
            greet_players(2);
            ShowConsoleCursor(true); // to get the white dash in the console back

            printf("please enter the height and the width of your connect 4 board (separated by a space):"); // Prompting width and height
            scanf("%d %d", &row, &column);                                                                   // i change this

            /* this will be changed to read from file XML after initializing it but
           for now let's cover every thing*/
            /*validation on size not exceeding integer borders or negative*/


            while (row <= 0 || row > INT_MAX || column <= 0 || column > INT_MAX)
            {
                printf("select an appropriate size: ");
                scanf("%d %d", &row, &column); // i change this
            }

            int *stack_undo[row * column * 3];
            int *stack_redo[row * column * 3];

            int stack_undo_value[row * column * 3]; ///new
            int stack_redo_value[row * column * 3];

            width = column * 4 + 1;
            height = row * 2 + 1;

            int arr[height][width];

            init_array(height, width, arr);

            sleep(1);
            system("cls");

            // algorithm of printing
            // display_board(width, height);
            // new algorithm of printing
            play_display(row, column, arr, stack_undo, stack_redo, stack_undo_value, stack_redo_value);

            end = clock();            // defining end time
            display_time(start, end); // display the time

            /* this will be changed to read from file XML after initializing it but
           for now let's cover every thing*/
            /*validation on size not exceeding integer borders or negative*/

            // algorithm of printing

            // display_board(width, height); //DELETED
        }
        else // to main menu
        {
            main();
        }
    }
    else if (choice == 2) // Load game
    {

    }
    else if (choice == 3) // Top scores
    {
    }
    else // Exit
    {
        return 0;
    }
    return 0;
}

void gotoxy(int x, int y)
{
    /*
    function responsible for moving freely in the console
    */
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main_menu()
{
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

int choices()
{
    int position = 1, choose;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    ShowConsoleCursor(false); // to hide white dash in console

    gotoxy(40, 10);
    printf("  Welcome to connect 4 game!  ");

    do
    {
        SetConsoleTextAttribute(console, 15); // initial form of the menu
        gotoxy(40, 11);
        printf(" 1] New game                  ");

        gotoxy(40, 12);
        printf(" 2] Load game                 ");

        gotoxy(40, 13);
        printf(" 3] Top scores                ");

        gotoxy(40, 14);
        printf(" 4] Quit                      \n");

        switch (position)
        {

        case 1:
            SetConsoleTextAttribute(console, 240); // for highlighting the choice
            gotoxy(40, 11);
            printf(" 1] New game                  ");
            break;

        case 2:
            SetConsoleTextAttribute(console, 240);
            gotoxy(40, 12);
            printf(" 2] Load game                 ");
            break;

        case 3:
            SetConsoleTextAttribute(console, 240);
            gotoxy(40, 13);
            printf(" 3] Top scores                ");
            break;

        case 4:
            SetConsoleTextAttribute(console, 240);
            gotoxy(40, 14);
            printf(" 4] Quit                      \n");
            break;

        case 0:
            position += 4;
            SetConsoleTextAttribute(console, 240);
            gotoxy(40, 14);
            printf(" 4] Quit                      \n");
            break;

        case 5:
            position -= 4;
            SetConsoleTextAttribute(console, 240);
            gotoxy(40, 11);
            printf(" 1] New game.                 ");
            break;
        }

        choose = getch();

        switch (choose)
        {
        case -32:
            choose = getch();
            break;

        case 80:
            position++;
            break;

        case 72:
            position--;
            break;
        }

    } while (choose != 13 && choose != 27);

    if (choose == 27)
    {
        position = 4;
    }

    SetConsoleTextAttribute(console, 15); // get the console back to its default mode

    return position;
}

void ShowConsoleCursor(bool showFlag)
{
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

void draw_box_main()
{
    /*
    responsible for creating the border of the main menu window
    hint: check extended ASCII (DOS) code for the values: 201, 205, 187, 186, 200, 188 --> in (ASCII_Extended.png) attached with this file
    */
    gotoxy(39, 9);
    printf("%c", 201);

    for (int i = 0; i < 30; i++)
    {
        printf("%c", 205);
    }

    printf("%c", 187);

    for (int i = 0; i < 5; i++)
    {
        gotoxy(39, 10 + i);

        printf("%c", 186);

        for (int j = 0; j < 30; j++)
        {
            printf(" ");
        }

        printf("%c\n", 186);
    }

    gotoxy(39, 15);
    printf("%c", 200);

    for (int i = 0; i < 30; i++)
    {
        printf("%c", 205);
    }

    printf("%c", 188);
}

void delete_box()
{
    /*
    responsible for clearing the screen after the main menu is done
    */
    system("cls");
}

int prompt_mode()
{
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

int choices_mode()
{
    int position = 1, choose;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    ShowConsoleCursor(false); // to hide white dash in console

    do
    {
        SetConsoleTextAttribute(console, 15); // initial form of the menu
        gotoxy(40, 11);
        printf(" 1] Single player             ");

        gotoxy(40, 12);
        printf(" 2] Multiplayer               ");

        gotoxy(40, 13);
        printf(" 3] Main menu                 ");

        switch (position)
        {

        case 1:
            SetConsoleTextAttribute(console, 240); // for highlighting the choice
            gotoxy(40, 11);
            printf(" 1] Single player             ");
            break;

        case 2:
            SetConsoleTextAttribute(console, 240);
            gotoxy(40, 12);
            printf(" 2] Multiplayer               ");
            break;

        case 3:
            SetConsoleTextAttribute(console, 240);
            gotoxy(40, 13);
            printf(" 3] Main menu                 ");
            break;

        case 0:
            position += 3;
            SetConsoleTextAttribute(console, 240);
            gotoxy(40, 13);
            printf(" 3] Main menu                 ");
            break;

        case 4:
            position -= 3;
            SetConsoleTextAttribute(console, 240);
            gotoxy(40, 11);
            printf(" 1] Single player             ");
            break;
        }

        choose = getch();

        switch (choose)
        {
        case -32:
            choose = getch();
            break;

        case 80:
            position++;
            break;

        case 72:
            position--;
            break;
        }

    } while (choose != 13 && choose != 27);

    if (choose == 27)
    {
        position = 3;
    }

    SetConsoleTextAttribute(console, 15); // get the console back to its default mode

    return position;
}

void greet_players(int mode)
{
    /*
    to say hello to the players
    its parameter -mode- has only two values: 1- to greet the player in single player mode
                                              2- to greet the two players in multiplayer mode
     */
    printf("Hello user1, ");
    if (mode == 1)
    {
        printf("\n");
    }
    else
    {
        printf("user2\n");
    }
    printf("let's start our game\n");
}

void init_array(int height, int width, int arr[height][width])
{
    /*
    initializing the array responsible for displaying, save & load, undo & redo, score check ...etc.
    arguments : take the REAL width and height of the array (including borders)
    */

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
                arr[i][j] = 201;

            else if (i == height - 1 && j == width - 1)
                arr[i][j] = 188;

            else if (i % 2 == 0 && j % 4 == 0 && i > 0 && i < height - 1 && j > 0 && j < width - 1)
                arr[i][j] = 206;

            else if (i == 0 && j == width - 1)
                arr[i][j] = 187;

            else if (i == height - 1 && j == 0)
                arr[i][j] = 200;

            else if (i % 2 == 0 && j == 0)
                arr[i][j] = 204;

            else if (i % 2 == 0 && j == width - 1)
                arr[i][j] = 185;

            else if (i == 0 && j % 4 == 0)
                arr[i][j] = 203;

            else if (i == height - 1 && j % 4 == 0)
                arr[i][j] = 202;

            else if (i % 2 == 0 && j % 4 != 0)
                arr[i][j] = 205;

            else if (i % 2 == 1 && j % 4 == 0)
                arr[i][j] = 186;

            else
                arr[i][j] = 32; // space in ascii code
        }
    }
}

// function to play and display board after each turn it take two arguments :height and width
void play_display(int row, int column, int arr[row * 2 + 1][column * 4 + 1],int* stack_undo[], int* stack_redo[], int stack_undo_value[], int stack_redo_value[])
{
    char ans;
    clock_t start = clock();
    int col1, col2, i, j, height = 2 * row + 1, width = 4 * column + 1; // col 1, 2: will stand for columns of two players , while i, j are iterators
    long long int k = row * column;                                     // number of moves
    int maxcolsize[column + 1];                                         // array to check maxsize //all its elements will take value of height and will be decreased if column chosen

    for (i = 1; i < column + 1; i++)
    {
        maxcolsize[i] = row; // set all values of it to value of height as mentioned
    }

    int turn = 1;

    printboard(height, width, arr); // print standard board

    while (k > 0)
    {

        if (turn % 2 == 1 || turn % 2 == -1) // odd turns player 1
        {
            char str1[1] = {0};
            int ch1, n1 = 0;

            printf("\nplayer1,please choose column from 1 to %d (u for undo, r for redo, s for save):\n", column);

            fflush(stdin);


            while ((ch1 = getchar()) != 10 && n1 < 1)
            {
                if (ch1 != 32 && ch1 != 44)
                {
                    if (isdigit(ch1))
                    {
                        str1[n1] = ch1;
                        n1++;

                    }
                    else if (isalpha(ch1))
                    {
                        str1[n1] = ch1;
                        n1++;
                    }
                }
            }
            col1 = str1[0];

            if(isalpha(col1) && (col1 == 83 || col1 == 115)) ///to save the game
            {
                save1( k, turn , column, height , width ,arr[height][width], maxcolsize[column+1]);
                turn --;
            }
            else if(isdigit(col1) && (col1 - 48 > column || col1 - 48 < 1 || maxcolsize[col1 - 48] < 1)) ///validate user input
            {
                printf("This column is no longer valid\n");
                turn--;
            }
            else if(isalpha(col1) && first2 == -1 && (col1 == 82 || col1 == 114)) ///if user exceeds number of possible redos
            {
                printf("You can not redo once more\n");
                turn--;
            }
            else if(isalpha(col1) && first1 == -1 && (col1 == 85 || col1 == 117)) ///if user exceeds number of possible undos
            {
                printf("You can not undo once more\n");
                turn--;
            }
            else if(isdigit(col1) && (col1 - 48 >= 1) && (col1 - 48 <= column)) ///playing normally
            {
                if(first2 != -1)
                {
                    first2 = -1;
                    first_value2 = -1;
                }
                arr[maxcolsize[col1 - 48] * 2 -1][(col1 - 48)* 4 - 1] = 1; // if player 1 choose a column the row index of it will start from height and will be decreased till zero
                push1(&arr[maxcolsize[col1 - 48] * 2 -1][(col1 - 48) * 4 - 1], stack_undo);
                push1_value(arr[maxcolsize[col1 - 48] * 2 -1][(col1 - 48) * 4 - 1], stack_undo_value);

                arr[maxcolsize[col1 - 48] * 2 -1][(col1 - 48)* 4 - 2] = 1;
                push1(&arr[maxcolsize[col1 - 48] * 2 -1][(col1 - 48) * 4 - 2], stack_undo);
                push1_value(arr[maxcolsize[col1 - 48] * 2 -1][(col1 - 48) * 4 - 2], stack_undo_value);

                arr[maxcolsize[col1 - 48] * 2 -1][(col1 - 48)* 4 - 3] = 1;
                push1(&arr[maxcolsize[col1 - 48] * 2 -1][(col1 - 48) * 4 - 3], stack_undo);
                push1_value(arr[maxcolsize[col1 - 48] * 2 -1][(col1 - 48) * 4 - 3], stack_undo_value);


                maxcolsize[col1 - 48]--;

                k--;
            }
            else if(isalpha(col1) && (col1 == 85 || col1 == 117)) ///undo
            {

                push2(pop1(stack_undo), stack_redo);
                push2_value(pop1_value(stack_undo_value), stack_redo_value);

                push2(pop1(stack_undo), stack_redo);
                push2_value(pop1_value(stack_undo_value), stack_redo_value);

                push2(pop1(stack_undo), stack_redo);
                push2_value(pop1_value(stack_undo_value), stack_redo_value);

                for(int i = 1; i < height; i += 2)
                {
                    for(int j = 1;(j < width); j++)
                    {
                        if((int)&arr[i][j] == (int)stack_redo[0] || (int)&arr[i][j] == (int)stack_redo[2] || (int)&arr[i][j] == (int)stack_redo[1])
                        {
                            arr[i][j] = 32;

                            if(j % 4 == 1)
                            {
                                 maxcolsize[(int)(j/4.0 + 0.75)]++;
                            }
                        }
                    }
                }
                k++;


            }
            else if(isalpha(col1) && (col1 == 82 || col1 == 114)) ///redo
            {

                push1(pop2(stack_redo), stack_undo);
                push1_value(pop2_value(stack_redo_value), stack_undo_value);

                push1(pop2(stack_redo), stack_undo);
                push1_value(pop2_value(stack_redo_value), stack_undo_value);

                push1(pop2(stack_redo), stack_undo);
                push1_value(pop2_value(stack_redo_value), stack_undo_value);

                for(int i = 1; i < height; i += 2)
                {
                    for(int j = 1;(j < width); j++)
                    {
                        if((int)&arr[i][j] == (int)stack_undo[0])
                        {
                            arr[i][j] = stack_undo_value[0];

                            if(j % 4 == 1)
                            {
                                maxcolsize[(int)(j/4.0 + 0.75)]--;
                            }
                        }
                        else if((int)&arr[i][j] == (int)stack_undo[1])
                        {
                            arr[i][j] = stack_undo_value[1];

                            if(j % 4 == 1)
                            {
                                maxcolsize[(int)(j/4.0 + 0.75)]--;
                            }
                        }
                        else if((int)&arr[i][j] == (int)stack_undo[2])
                        {
                            arr[i][j] = stack_undo_value[2];

                            if(j % 4 == 1)
                            {
                                maxcolsize[(int)(j/4.0 + 0.75)]--;
                            }
                        }
                    }
                }
                k--;
            }
            else
            {
                printf("\n Enter a valid input.\n");
                turn --;
            }

            printboard(height, width, arr);

            check_score(height, width, arr, 1);

            clock_t end = clock();    // defining end time

            display_time(start, end); // display the time

            turn++;
        }
        else //////////////////////////////////////////PLAYER 2 TURN
        {
            char str1[1] = {0};
            int ch1, n1 = 0;

            printf("\nplayer2, choose column from 1 to %d (u for undo, r for redo, s for save):\n", column);

            fflush(stdin);

            while ((ch1 = getchar()) != 10 && n1 < 1)
            {

                if (ch1 != 32)
                {
                    if (isdigit(ch1))
                    {
                        str1[n1] = ch1;
                        n1++;
                    }
                    else if (isalpha(ch1))
                    {
                        str1[n1] = ch1;
                        n1++;
                    }
                }

            }
            col2 = str1[0];

            if(isalpha(col2) && (col2 == 83 || col2 == 115)) ///to save the game
            {
                save1( k, turn , column, height , width ,arr[height][width], maxcolsize[column+1]);
                turn --;
            }
            else if(isdigit(col2) && (col2 - 48 > column || col2 - 48 < 1 || maxcolsize[col2 - 48] < 1)) ///validate player 2 choice
            {
                printf("This column is no longer valid\n");
                turn--;
            }
            else if(isalpha(col2) && first2 == -1 && (col2 == 82 || col2 == 114)) /// if user exceeds number of possible redos
            {
                printf("You can not redo once more.\n");
                turn--;
            }
            else if(isalpha(col2) && first1 == -1 && (col2 == 85 || col2 == 117)) ///if user exceeds number of possible undos
            {
                printf("You can not undo once more.\n");
                turn--;
            }
            else if(isdigit(col2) && col2 - 48 >= 1 && col2 - 48 <= column) ///playing normally
            {
                if(first2 != -1)
                {
                    first2 = -1;
                    first_value2 = -1;
                }

                arr[maxcolsize[col2 - 48] * 2 -1][(col2 - 48)* 4 - 1] = -1; // if player 1 choose a column the row index of it will start from height and will be decreased till zero
                push1(&arr[maxcolsize[col2 - 48] * 2 -1][(col2 - 48) * 4 - 1], stack_undo);
                push1_value(arr[maxcolsize[col2 - 48] * 2 -1][(col2 - 48) * 4 - 1], stack_undo_value);

                arr[maxcolsize[col2 - 48] * 2 -1][(col2 - 48)* 4 - 2] = -1;
                push1(&arr[maxcolsize[col2 - 48] * 2 -1][(col2 - 48) * 4 - 2], stack_undo);
                push1_value(arr[maxcolsize[col2 - 48] * 2 -1][(col2 - 48) * 4 - 2], stack_undo_value);

                arr[maxcolsize[col2 - 48] * 2 -1][(col2 - 48)* 4 - 3] = -1;
                push1(&arr[maxcolsize[col2 - 48] * 2 -1][(col2 - 48) * 4 - 3], stack_undo);
                push1_value(arr[maxcolsize[col2 - 48] * 2 -1][(col2 - 48) * 4 - 3], stack_undo_value);

                maxcolsize[col2 - 48]--;

                k--;

            }
            else if(isalpha(col2) && (col2 == 85 || col2 == 117)) ///undo
            {


                push2(pop1(stack_undo), stack_redo);
                push2_value(pop1_value(stack_undo_value), stack_redo_value);

                push2(pop1(stack_undo), stack_redo);
                push2_value(pop1_value(stack_undo_value), stack_redo_value);

                push2(pop1(stack_undo), stack_redo);
                push2_value(pop1_value(stack_undo_value), stack_redo_value);

                for(int i = 1; i < height; i += 2)
                {
                    for(int j = 1;(j < width); j++)
                    {

                        if((int)&arr[i][j] == (int)stack_redo[0] || (int)&arr[i][j] == (int)stack_redo[2] || (int)&arr[i][j] == (int)stack_redo[1])
                        {
                            arr[i][j] = 32;
                            if(j % 4 == 1)
                            {
                                maxcolsize[(int)(j/4.0 + 0.75)]++;
                            }
                        }
                    }
                }
                k++;

            }

            else if(isalpha(col2) && (col2 == 82 || col2 == 114)) ///redo
            {
                push1(pop2(stack_redo), stack_undo);
                push1_value(pop2_value(stack_redo_value), stack_undo_value);

                push1(pop2(stack_redo), stack_undo);
                push1_value(pop2_value(stack_redo_value), stack_undo_value);

                push1(pop2(stack_redo), stack_undo);
                push1_value(pop2_value(stack_redo_value), stack_undo_value);


                for(int i = 1; i < height; i += 2)
                {
                    for(int j = 1;(j < width); j++)
                    {
                        if((int)&arr[i][j] == (int)stack_undo[0])
                        {
                            arr[i][j] = stack_undo_value[0]; ///need some edit !!!

                            if(j % 4 == 1)
                            {
                                maxcolsize[(int)(j/4.0 + 0.75)]--;
                            }
                        }
                        else if((int)&arr[i][j] == (int)stack_undo[1])
                        {
                            arr[i][j] = stack_undo_value[1];

                            if(j % 4 == 1)
                            {
                                maxcolsize[(int)(j/4.0 + 0.75)]--;
                            }
                        }
                        else if((int)&arr[i][j] == (int)stack_undo[2])
                        {
                            arr[i][j] = stack_undo_value[2];

                            if(j % 4 == 1)
                            {
                                maxcolsize[(int)(j/4.0 + 0.75)]--;
                            }
                        }
                    }
                }
                k--;
            }
            else
            {
                printf("\n Enter a valid input\n");
                turn --;
            }

            printboard(height, width, arr);

            check_score(height, width, arr, -1);

            clock_t end = clock();    // defining end time

            display_time(start, end); // display the time

            turn++;
        }
    }
}

void printboard(int height, int width, int arr[height][width]) // this fn will be called in the fn of playing game to display board after each turn
                                                               // it takes height and width and array of moves and display according to value
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            SetConsoleTextAttribute(console, 15);
            if (arr[i][j] == 1)
            {
                SetConsoleTextAttribute(console, 144); //blue
                printf(" ");
            }
            else if (arr[i][j] == -1)
            {
                SetConsoleTextAttribute(console, 64); //red
                printf(" ");
            }
            else
                printf("%c", arr[i][j]);
        }
        printf("\n");
    }
}

void display_time(clock_t start, clock_t end) // fn to display time in game ///its calling position in code may be changed
                                              // but for now leave it
                                              // to use fn properly define start in beginning of code and define end at end of any process then call fn
{
    double duration = ((double)end - start) / CLOCKS_PER_SEC; // duration as a double endtime-start time
    int dur;
    dur = duration; // assigning it to integer to make the operation
    typedef struct
    { // defining time struct
        int hours;
        int minutes;
        int seconds;
    } time;

    time t; // t of variable time
    int c1; // helping variable in calculation

    /////calculation of time:

    t.hours = dur / 3600;
    c1 = dur % 3600;
    t.minutes = c1 / 60;
    t.seconds = c1 % 60;

    //// printing time:

    printf("\ntime taken in game:\n");

    if (t.hours > 0)
    {
        printf("hours : %d", t.hours);
        printf("\t");
    }
    if (t.minutes > 0)
    {
        printf("minutes : %d", t.minutes);
        printf("\t");
    }
    printf("seconds : %d", t.seconds);
}

void play_display_with_computer(int row, int column, int arr[row * 2 + 1][column * 4 + 1])
{
    int col1, col2, i, j, height = 2 * row + 1, width = 4 * column + 1; // col 1, 2: will stand for columns of two players , while i, j are iterators
    long long int k = row * column;                                     // number of moves
    int maxcolsize[column + 1];                                         // array to check maxsize //all its elements will take value of height and will be decreased if column chosen

    for (i = 1; i < column + 1; i++)
    {
        maxcolsize[i] = row; // set all values of it to value of height as mentioned
    }

    int turn = 1;
    printboard(height, width, arr); // print standard board

    while (k > 0)
    {

        if (turn % 2 == 1) // odd turns player 1
        {
            printf("\n YOUR TURN,please choose column from 1 to %d:", column);
            scanf("%d", &col1);
            while (maxcolsize[col1] < 1 || col1 > column || col1 < 1) // validation on column index
            {
                printf("this column is no longer valid\n");
                printf("please choose another one: ");
                scanf("%d", &col1);
            }

            arr[maxcolsize[col1] * 2 - 1][col1 * 4 - 3] = 1; // if player 1 choose a column the row index of it will start from height and will be decreased till zero
            arr[maxcolsize[col1] * 2 - 1][col1 * 4 - 2] = 1;
            arr[maxcolsize[col1] * 2 - 1][col1 * 4 - 1] = 1;

            printboard(height, width, arr); // print board after playing

            check_score(height, width, arr, 1);

            maxcolsize[col1]--;
            turn++; // increase turns
        }
        else
        {
            ShowConsoleCursor(false);
            printf("\n COMPUTER'S TURN\n");

            sleep(1);

            col2 = rand() % (column + 1);
            while (maxcolsize[col2] < 1 || col2 > column || col2 < 1)
            {
                col2 = rand() % (column + 1);
            }
            arr[maxcolsize[col2] * 2 - 1][col2 * 4 - 1] = -1; // red or blue is represented by three spaces
            arr[maxcolsize[col2] * 2 - 1][col2 * 4 - 2] = -1;
            arr[maxcolsize[col2] * 2 - 1][col2 * 4 - 3] = -1;

            printboard(height, width, arr);

            check_score(height, width, arr, -1);

            maxcolsize[col2]--;
            turn++;
            ShowConsoleCursor(true);
        }
        k--; // decrease k till zero which will indicate that board is complete
    }
}

void check_score(int height, int width, int arr[height][width], int xo)
{
    int score = 0, count;

    for (int i = height - 2; i >= 0; i -= 2)
    {
        for (int j = width - 2; j >= 0; j -= 4)
        {
            if (arr[i][j] == xo) /// NEW!
            {
                count = horizontal_check(height, width, arr, xo, i, j, 0); // height then width (columns) then diagonals - count should be 4 !!!!!
                if (count / 4 >= 1)
                {
                    score += (count - 3);
                }

                count = vertical_check(height, width, arr, xo, i, j, 0);
                if (count / 4 >= 1)
                {
                    score += (count - 3);
                }

                count = diagonal_check_45(height, width, arr, xo, i, j, 0);
                if (count / 4 >= 1)
                {
                    score += (count - 3);
                }

                count = diagonal_check_135(height, width, arr, xo, i, j, 0);
                if (count / 4 >= 1)
                {
                    score += (count - 3);
                }
            }
        }
    }
    if (xo == 1)
    {
        printf("\nPlayer 1 score: %d\n", score);
    }
    else
    {
        printf("\nPlayer 2 score: %d\n", score);
    }
    ////////////////Wee need to display both scores at the same time
}

int horizontal_check(int height, int width, int arr[height][width], int xo, int i, int j, int counter) // parameters : 1- rows,  2 -columns , 3 - array ,
// 4-x or O value (1 or -1) ,5, 6:  i and j from nested for loop commented above
{
    int count;
    if (i < 0 || j < 0 || arr[i][j] == xo * -1 || arr[i][j] == 32 || counter == 4) // base cases
    {
        count = 0;
    }
    else
    {
        counter += 1;
        count = 1 + horizontal_check(height, width, arr, xo, i, j - 4, counter);
    }

    return count;
}

int vertical_check(int height, int width, int arr[height][width], int xo, int i, int j, int counter) // parameters : 1- rows,  2 -columns , 3 - array ,
// 4-x or O value (1 or -1) ,5, 6:  i and j from nested for loop commented above
{
    int count;
    if (i < 0 || j < 0 || arr[i][j] == xo * -1 || arr[i][j] == 32 || counter == 4) // base cases
    {
        count = 0;
    }
    else
    {
        counter += 1;
        count = 1 + vertical_check(height, width, arr, xo, i - 2, j, counter);
    }

    return count;
}

int diagonal_check_135(int height, int width, int arr[height][width], int xo, int i, int j, int counter) // parameters : 1- rows,  2 -columns , 3 - array ,
// 4-x or O value (1 or -1) ,5, 6:  i and j from nested for loop commented above
{
    int count;
    if (i < 0 || j < 0 || arr[i][j] == xo * -1 || arr[i][j] == 32 || counter == 4) // base cases
    {
        count = 0;
    }
    else
    {
        counter += 1;
        count = 1 + diagonal_check_135(height, width, arr, xo, i - 2, j - 4, counter);
    }

    return count;
}

int diagonal_check_45(int height, int width, int arr[height][width], int xo, int i, int j, int counter) // parameters : 1- rows,  2 -columns , 3 - array ,
// 4-x or O value (1 or -1) ,5, 6:  i and j from nested for loop commented above
{
    int count;
    if (i < 0 || j < 0 || arr[i][j] == xo * -1 || arr[i][j] == 32 || j >= width || counter == 4) // base cases
    {
        count = 0;
    }
    else
    {
        counter += 1;
        count = 1 + diagonal_check_45(height, width, arr, xo, i - 2, j + 4, counter);
    }

    return count;
}
void save1(int k,int turn ,int column,int height , int width , int arr[height][width],int maxcolsize[column+1])
{
    int i,j;
    FILE *out; ///in load out write

   out=fopen("saving data1","w");
   /*
   fwrite(&height,sizeof(height),1,out);
   fwrite(&width,sizeof(width),1,out);
   fwrite(&k,sizeof(k),1,out);
   fwrite(&turn,sizeof(turn),1,out);
   */
   fprintf(out,"%d",height);
    fprintf(out,"%d",width);
     fprintf(out,"%d",k);
      fprintf(out,"%d",turn);
/*
  for(i=0;i<height;i++)
  {
      for(j=0;j<width;j++)
      {
          fprintf(out,"%d",arr[i][j]);
      }
  }

  for(i=0;i<column+1;i++)
  {
      fprintf(out,"%d",maxcolsize[i]);
  }
*/
    fclose(out);

}
void save2(int k,int turn ,int column,int height , int width , int arr[height][width],int maxcolsize[column+1])
{
    int i,j;
    FILE *out; ///in load out write

   out=fopen("saving data2","w");
   /*
   fwrite(&height,sizeof(height),1,out);
   fwrite(&width,sizeof(width),1,out);
   fwrite(&k,sizeof(k),1,out);
   fwrite(&turn,sizeof(turn),1,out);
   */
   fprintf(out,"%d",height);
    fprintf(out,"%d",width);
     fprintf(out,"%d",k);
      fprintf(out,"%d",turn);
/*
  for(i=0;i<height;i++)
  {
      for(j=0;j<width;j++)
      {
          fprintf(out,"%d",arr[i][j]);
      }
  }

  for(i=0;i<column+1;i++)
  {
      fprintf(out,"%d",maxcolsize[i]);
  }
*/
    fclose(out);

}

void save3(int k,int turn ,int column,int height , int width , int arr[height][width],int maxcolsize[column+1])
{
    int i,j;
    FILE *out; ///in load out write

   out=fopen("saving data3","w");
   /*
   fwrite(&height,sizeof(height),1,out);
   fwrite(&width,sizeof(width),1,out);
   fwrite(&k,sizeof(k),1,out);
   fwrite(&turn,sizeof(turn),1,out);
   */
   fprintf(out,"%d",height);
    fprintf(out,"%d",width);
     fprintf(out,"%d",k);
      fprintf(out,"%d",turn);
/*
  for(i=0;i<height;i++)
  {
      for(j=0;j<width;j++)
      {
          fprintf(out,"%d",arr[i][j]);
      }
  }

  for(i=0;i<column+1;i++)
  {
      fprintf(out,"%d",maxcolsize[i]);
  }
*/
    fclose(out);

}

// undo stack

void push1(int *ptr, int *stack_undo[])
{
    first1 += 1;
    for (int i = first1; i > 0; i--)
    {
        stack_undo[i] = stack_undo[i - 1];
    }
    stack_undo[0] = ptr;
}

int *pop1(int *stack_undo[])
{
    if (isEmpty1())
    {
        // stack under flow ////Dont do the undo
    }
    else
    {

        int value = stack_undo[0];

        for (int i = 0; i < first1; i++)
        {
            stack_undo[i] = stack_undo[i + 1];
        }
        first1--;
        return value;
    }
}

int isEmpty1()
{
    if (first1 == -1)
    {
        return 1;
    }
    return 0;
}

// redo stack

void push2(int *ptr, int *stack_redo[])
{
    first2 += 1;
    for (int i = first2; i > 0; i--)
    {
        stack_redo[i] = stack_redo[i - 1];
    }
    stack_redo[0] = ptr;
}

int *pop2(int *stack_redo[])
{
    if (isEmpty2())
    {
        // stack under flow ////Dont do the Redo
    }
    else
    {

        int value = stack_redo[0];

        for (int i = 0; i < first2; i++)
        {
            stack_redo[i] = stack_redo[i + 1];
        }
        first2--;
        return value;
    }
}

int isEmpty2()
{
    if (first2 == -1)
    {
        return 1;
    }
    return 0;
}


//undo stack_value



void push1_value(int x, int stack_undo[])
{
    first_value1 += 1;
    for (int i = first_value1; i > 0; i--)
    {
        stack_undo[i] = stack_undo[i - 1];
    }
    stack_undo[0] = x;
}

int pop1_value(int stack_undo[])
{
    if (isEmpty1_value())
    {
        // stack under flow ////Dont do the undo
    }
    else
    {

        int value = stack_undo[0];

        for (int i = 0; i < first_value1; i++)
        {
            stack_undo[i] = stack_undo[i + 1];
        }
        first_value1--;
        return value;
    }
}

int isEmpty1_value()
{
    if (first_value1 == -1)
    {
        return 1;
    }
    return 0;
}

// redo stack

void push2_value(int x, int stack_redo[])
{
    first_value2 += 1;
    for (int i = first_value2; i > 0; i--)
    {
        stack_redo[i] = stack_redo[i - 1];
    }

    stack_redo[0] = x;
}

int pop2_value(int stack_redo[])
{
    if (isEmpty2_value())
    {
        // stack under flow ////Dont do the Redo
    }
    else
    {

        int value = stack_redo[0];

        for (int i = 0; i < first2; i++)
        {
            stack_redo[i] = stack_redo[i + 1];
        }
        first_value2--;
        return value;
    }
}

int isEmpty2_value()
{
    if (first_value2 == -1)
    {
        return 1;
    }
    return 0;
}

