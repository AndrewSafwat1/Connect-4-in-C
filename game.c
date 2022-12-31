#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <string.h>

// save and load
void save(int mode, int save_no, int *stack_undo[], int stack_undo_value[], int column, int row, int arr[row * 2 + 1][column * 4 + 1], int turn, int k, int maxcolsize[]);
int loadgame(int game_number, int *stack_redo[], int stack_redo_value[]);

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

/// global
struct config /// for xml configuration
{
    int width;
    int height;
    int highscores;
};
struct config settings;

int count_string(char word1[], char word2[]);

void xml();

struct
{ /// two structs for top scores
    int r;
    char name[70];
    int score;
    char name2[70];

} winner;

typedef struct
{
    int rr;
    char nn[70];
    int ss;

} memory;

void sortscore(FILE *p, int score); /// new for top scores
void printscores(FILE *P, int x);   /// new

int first_value1 = -1; ///
int first_value2 = -1;
void push1_value(int, int stack_undo_value[]); ///
void push2_value(int, int stack_redo_value[]);
int isEmpty1_value(); ///
int isEmpty2_value();
int pop1_value(int stack_undo_value[]); ///
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

int check_score(int height, int width, int arr[height][width], int xo);

void play_display_with_computer(int row, int column, int arr[row * 2 + 1][column * 4 + 1], int *stack_undo[], int *stack_redo[], int stack_undo_value[], int stack_redo_value[], int turn, int k, int maxcolsize[]);

void display_time(clock_t start, clock_t end);
void save1(int k, int turn, int column, int height, int width, int arr[height][width], int maxcolsize[column + 1]);
void init_array(int height, int width, int arr[height][width]);                                                                                                                                        /// RECENTLY ADDED
void printboard(int height, int width, int arr[height][width]);                                                                                                                                        /// RECENTLY ADDED
void play_display(int row, int column, int arr[row * 2 + 1][column * 4 + 1], int *stack_undo[], int *stack_redo[], int stack_undo_value[], int stack_redo_value[], int turn, int k, int maxcolsize[]); /// edited
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

    int width, height, row, column, choice, mode, top_scores;

    choice = main_menu();

    if (choice == 1) //////New game
    {

        mode = prompt_mode();
        if (mode == 1) // vs computer
        {
            gotoxy(0, 0);
            greet_players(1);
            ShowConsoleCursor(true);

            xml();

            row = settings.height;
            column = settings.width;

            int *stack_undo[row * column * 3];
            int *stack_redo[row * column * 3];

            int stack_undo_value[row * column * 3]; /// new
            int stack_redo_value[row * column * 3];

            width = column * 4 + 1;
            height = row * 2 + 1;

            int arr[height][width];

            init_array(height, width, arr);

            sleep(1);
            system("cls");

            srand(time(NULL));

            int maxcolsize[column + 1];

            for (int i = 1; i < column + 1; i++)
            {
                maxcolsize[i] = row; // set all values of it to value of height as mentioned
            }

            play_display_with_computer(row, column, arr, stack_undo, stack_redo, stack_undo_value, stack_redo_value, 1, row * column, maxcolsize);

            end = clock();            // defining end time
            display_time(start, end); // display the time
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (mode == 2) // 2 players
        {
            gotoxy(0, 0);
            greet_players(2);
            ShowConsoleCursor(true); // to get the white dash in the console back

            xml();

            row = settings.height;
            column = settings.width;

            int *stack_undo[row * column * 3];
            int *stack_redo[row * column * 3];

            int stack_undo_value[row * column * 3]; /// new
            int stack_redo_value[row * column * 3];

            width = column * 4 + 1;
            height = row * 2 + 1;

            int arr[height][width];

            init_array(height, width, arr);

            sleep(1);
            system("cls");

            int maxcolsize[column + 1];

            for (int i = 1; i < column + 1; i++)
            {
                maxcolsize[i] = row; // set all values of it to value of height as mentioned
            }

            play_display(row, column, arr, stack_undo, stack_redo, stack_undo_value, stack_redo_value, 1, row * column, maxcolsize);

            end = clock();            // defining end time
            display_time(start, end); // display the time
        }
        else // to main menu
        {
            main();
        }
    }
    else if (choice == 2) // Load game
    {

        system("cls");
        ShowConsoleCursor(true);

        printf("\nEnter game number(from 1 -> 3): ");
        int game_number = getchar();

        if (isdigit(game_number) && game_number - 48 == 1)
        {
            FILE *load_file;

            if ((load_file = fopen("game1", "rb")) == NULL)
            {
                printf("\nan error occurred while opening the file.\n");
            }
            else
            {
                fread(&column, sizeof(column), 1, load_file);
                fread(&row, sizeof(row), 1, load_file);

                int *stack_redo[row * column * 3];
                int stack_redo_value[row * column * 3];

                loadgame(1, stack_redo, stack_redo_value);
            }
        }
        else if (isdigit(game_number) && game_number - 48 == 2)
        {
            FILE *load_file;

            if ((load_file = fopen("game2", "rb")) == NULL)
            {
                printf("\nan error occurred while opening the file.\n");
            }
            else
            {
                fread(&column, sizeof(column), 1, load_file);
                fread(&row, sizeof(row), 1, load_file);

                int *stack_redo[row * column * 3];
                int stack_redo_value[row * column * 3];

                loadgame(2, stack_redo, stack_redo_value);
            }
        }
        else if (isdigit(game_number) && game_number - 48 == 3)
        {
            FILE *load_file;

            if ((load_file = fopen("game3", "rb")) == NULL)
            {
                printf("\nan error occurred while opening the file.\n");
            }
            else
            {
                fread(&column, sizeof(column), 1, load_file);
                fread(&row, sizeof(row), 1, load_file);

                int *stack_redo[row * column * 3];
                int stack_redo_value[row * column * 3];

                loadgame(3, stack_redo, stack_redo_value);
            }
        }
        else
        {
            printf("You failed to load the game.");
        }
    }
    else if (choice == 3) // Top scores
    {
        xml();

        top_scores = settings.highscores;

        FILE *m;

        printscores(m, top_scores);
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

        ShowConsoleCursor(false);
        SetConsoleTextAttribute(console, 15);

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

        ShowConsoleCursor(false);
        SetConsoleTextAttribute(console, 15);

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
void play_display(int row, int column, int arr[row * 2 + 1][column * 4 + 1], int *stack_undo[], int *stack_redo[], int stack_undo_value[], int stack_redo_value[], int turn, int k, int maxcolsize[])
{
    clock_t start = clock();
    int col1, col2, i, j, height = 2 * row + 1, width = 4 * column + 1, player1, player2; // col 1, 2: will stand for columns of two players , while i, j are iterators                                                      // number of moves



    printboard(height, width, arr); // print standard board

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    while (k > 0)
    {

        if (turn % 2 == 1 || turn % 2 == -1) // odd turns player 1
        {

            char str1[2] = {-1, -1};
            int ch1, n1 = 0, col1 = 0;

            SetConsoleTextAttribute(console, 9);
            printf("\nPlayer 1, Choose column from 1 to %d (u for undo, r for redo, s for save, x for main menu):\n", column);
            SetConsoleTextAttribute(console, 15);

            fflush(stdin);

            while ((ch1 = getchar()) != 10 && n1 < 2)
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
                        break;
                    }
                }
            }

            if ((isalpha(str1[0]) == 2 || isalpha(str1[0]) == 1) && str1[1] == -1)
            {
                col1 = str1[0];
            }
            else if (isdigit(str1[0]) && str1[1] == -1)
            {
                col1 = str1[0] - 48;
            }
            else if (isdigit(str1[0]) && isdigit(str1[1]))
            {
                for (int i = 0; isdigit(str1[i]) && i < 2; i++)
                {
                    col1 = col1 * 10 + (str1[i] - 48);
                }
            }


            if (isalpha(col1) && (col1 == 83 || col1 == 115)) /// to save the game
            {
                printf("\nChoose from 1 -> 3 the file index you want to save your game in:\n");

                fflush(stdin);
                int file_number;
                file_number = getchar();

                if (isdigit(file_number) && file_number - 48 == 1)
                {
                    save(1, 1, stack_undo, stack_undo_value, column, row, arr, turn, k, maxcolsize);
                }
                else if (isdigit(file_number) && file_number - 48 == 2)
                {
                    save(1, 2, stack_undo, stack_undo_value, column, row, arr, turn, k, maxcolsize);
                }
                else if (isdigit(file_number) && file_number - 48 == 3)
                {
                    save(1, 3, stack_undo, stack_undo_value, column, row, arr, turn, k, maxcolsize);
                }
                else
                {
                    printf("\nNot a valid file index, try again later\n");
                }
                turn--;
            }
            else if ((isalpha(str1[0]) != 2 && isalpha(str1[0]) != 1) && (col1 > column || col1 < 1 || maxcolsize[col1] < 1)) /// validate user input
            {
                printf("\nThis column is no longer valid\n");
                turn--;
            }
            else if (isalpha(col1) && first2 == -1 && (col1 == 82 || col1 == 114)) /// if user exceeds number of possible redos
            {
                printf("\nYou can not redo once more\n");
                turn--;
            }
            else if (isalpha(col1) && first1 == -1 && (col1 == 85 || col1 == 117)) /// if user exceeds number of possible undos
            {
                printf("\nYou can not undo once more\n");
                turn--;
            }
            else if ((col1 >= 1) && (col1 <= column)) /// playing normally
            {
                if (first2 != -1)
                {
                    first2 = -1;
                    first_value2 = -1;
                }
                arr[maxcolsize[col1] * 2 - 1][(col1)*4 - 1] = 1; // if player 1 choose a column the row index of it will start from height and will be decreased till zero
                push1(&arr[maxcolsize[col1] * 2 - 1][(col1)*4 - 1], stack_undo);
                push1_value(arr[maxcolsize[col1] * 2 - 1][(col1)*4 - 1], stack_undo_value);

                arr[maxcolsize[col1] * 2 - 1][(col1)*4 - 2] = 1;
                push1(&arr[maxcolsize[col1] * 2 - 1][(col1)*4 - 2], stack_undo);
                push1_value(arr[maxcolsize[col1] * 2 - 1][(col1)*4 - 2], stack_undo_value);

                arr[maxcolsize[col1] * 2 - 1][(col1)*4 - 3] = 1;
                push1(&arr[maxcolsize[col1] * 2 - 1][(col1)*4 - 3], stack_undo);
                push1_value(arr[maxcolsize[col1] * 2 - 1][(col1)*4 - 3], stack_undo_value);

                maxcolsize[col1]--;

                k--;
            }
            else if (isalpha(col1) && (col1 == 85 || col1 == 117)) /// undo
            {

                push2(pop1(stack_undo), stack_redo);
                push2_value(pop1_value(stack_undo_value), stack_redo_value);

                push2(pop1(stack_undo), stack_redo);
                push2_value(pop1_value(stack_undo_value), stack_redo_value);

                push2(pop1(stack_undo), stack_redo);
                push2_value(pop1_value(stack_undo_value), stack_redo_value);

                for (int i = 1; i < height; i += 2)
                {
                    for (int j = 1; (j < width); j++)
                    {
                        if ((int)&arr[i][j] == (int)stack_redo[0] || (int)&arr[i][j] == (int)stack_redo[2] || (int)&arr[i][j] == (int)stack_redo[1])
                        {
                            arr[i][j] = 32;

                            if (j % 4 == 1)
                            {
                                maxcolsize[(int)(j / 4.0 + 0.75)]++;
                            }
                        }
                    }
                }
                k++;
            }
            else if (isalpha(col1) && (col1 == 82 || col1 == 114)) /// redo
            {

                push1(pop2(stack_redo), stack_undo);
                push1_value(pop2_value(stack_redo_value), stack_undo_value);

                push1(pop2(stack_redo), stack_undo);
                push1_value(pop2_value(stack_redo_value), stack_undo_value);

                push1(pop2(stack_redo), stack_undo);
                push1_value(pop2_value(stack_redo_value), stack_undo_value);

                for (int i = 1; i < height; i += 2)
                {
                    for (int j = 1; (j < width); j++)
                    {
                        if ((int)&arr[i][j] == (int)stack_undo[0])
                        {
                            arr[i][j] = stack_undo_value[0];

                            if (j % 4 == 1)
                            {
                                maxcolsize[(int)(j / 4.0 + 0.75)]--;
                            }
                        }
                        else if ((int)&arr[i][j] == (int)stack_undo[1])
                        {
                            arr[i][j] = stack_undo_value[1];

                            if (j % 4 == 1)
                            {
                                maxcolsize[(int)(j / 4.0 + 0.75)]--;
                            }
                        }
                        else if ((int)&arr[i][j] == (int)stack_undo[2])
                        {
                            arr[i][j] = stack_undo_value[2];

                            if (j % 4 == 1)
                            {
                                maxcolsize[(int)(j / 4.0 + 0.75)]--;
                            }
                        }
                    }
                }
                k--;
            }
            else if (isalpha(col1) && (col1 == 88 || col1 == 120))
            {
                printf("\nDo you want to save?(y/n): \n");
                int save_check = getch();
                if (save_check == 89 || save_check == 121)
                {
                    printf("\nChoose from 1 -> 3 the file index you want to save your game in:\n");
                    fflush(stdin);
                    int file_number = getchar();

                    if (isdigit(file_number) && file_number - 48 == 1)
                    {
                        save(1, 1, stack_undo, stack_undo_value, column, row, arr, turn, k, maxcolsize);
                        system("cls");
                        ShowConsoleCursor(false);
                        main();
                    }
                    else if (isdigit(file_number) && file_number - 48 == 2)
                    {
                        save(1, 2, stack_undo, stack_undo_value, column, row, arr, turn, k, maxcolsize);
                        system("cls");
                        ShowConsoleCursor(false);
                        main();
                    }
                    else if (isdigit(file_number) && file_number - 48 == 3)
                    {
                        save(1, 3, stack_undo, stack_undo_value, column, row, arr, turn, k, maxcolsize);
                        system("cls");
                        ShowConsoleCursor(false);
                        main();
                    }
                    else
                    {
                        printf("\nNot a valid file index, try again later\n");
                        turn--;
                    }
                }
                else
                {
                    turn--;
                }
            }
            else
            {
                printf("\n Enter a valid input.\n");
                turn--;
            }

            printboard(height, width, arr);

            player1 = check_score(height, width, arr, 1);

            player2 = check_score(height, width, arr, -1);

            clock_t end = clock(); // defining end time

            display_time(start, end); // display the time

            SetConsoleTextAttribute(console, 9);
            printf("\nPlayer 1 total moves: %d \n", (int)(turn/2.0 + 0.5));
            SetConsoleTextAttribute(console, 15);

            SetConsoleTextAttribute(console, 12);
            printf("\nPlayer 2 total moves: %d \n", turn/2);
            SetConsoleTextAttribute(console, 15);

            turn++;


        }
        else //////////////////////////////////////////PLAYER 2 TURN
        {
            char str1[2] = {-1, -1};
            int ch1, n1 = 0, col2 = 0;

            SetConsoleTextAttribute(console, 12);
            printf("\nplayer 2, Choose column from 1 to %d (u for undo, r for redo, s for save, x for main menu):\n", column);
            SetConsoleTextAttribute(console, 15);

            fflush(stdin);

            while ((ch1 = getchar()) != 10 && n1 < 2)
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
                        break;
                    }
                }
            }

            if ((isalpha(str1[0]) == 2 || isalpha(str1[0]) == 1) && str1[1] == -1)
            {
                col2 = str1[0];
            }
            else if (isdigit(str1[0]) && str1[1] == -1)
            {
                col2 = str1[0] - 48;
            }
            else if (isdigit(str1[0]) && isdigit(str1[1]))
            {
                for (int i = 0; isdigit(str1[i]) && i < 2; i++)
                {
                    col2 = col2 * 10 + (str1[i] - 48);
                }
            }

            if (isalpha(col2) && (col2 == 83 || col2 == 115)) /// to save the game
            {
                printf("\nChoose from 1 -> 3 the file index you want to save your game in:\n");
                fflush(stdin);
                int file_number = getchar();

                if (isdigit(file_number) && file_number - 48 == 1)
                {
                    save(1, 1, stack_undo, stack_undo_value, column, row, arr, turn, k, maxcolsize);
                }
                else if (isdigit(file_number) && file_number - 48 == 2)
                {
                    save(1, 2, stack_undo, stack_undo_value, column, row, arr, turn, k, maxcolsize);
                }
                else if (isdigit(file_number) && file_number - 48 == 3)
                {
                    save(1, 3, stack_undo, stack_undo_value, column, row, arr, turn, k, maxcolsize);
                }
                else
                {
                    printf("\nNot a valid file index, try again later\n");
                }
                turn--;
            }
            else if ((isalpha(str1[0]) != 2 && isalpha(str1[0]) != 1) && (col2 > column || col2 < 1 || maxcolsize[col2] < 1)) /// validate player 2 choice
            {
                printf("\nThis column is no longer valid\n");
                turn--;
            }
            else if (isalpha(col2) && first2 == -1 && (col2 == 82 || col2 == 114)) /// if user exceeds number of possible redos
            {
                printf("\nYou can not redo once more.\n");
                turn--;
            }
            else if (isalpha(col2) && first1 == -1 && (col2 == 85 || col2 == 117)) /// if user exceeds number of possible undos
            {
                printf("\nYou can not undo once more.\n");
                turn--;
            }
            else if (col2 >= 1 && col2 <= column) /// playing normally
            {
                if (first2 != -1)
                {
                    first2 = -1;
                    first_value2 = -1;
                }

                arr[maxcolsize[col2] * 2 - 1][(col2)*4 - 1] = -1; // if player 1 choose a column the row index of it will start from height and will be decreased till zero
                push1(&arr[maxcolsize[col2] * 2 - 1][(col2)*4 - 1], stack_undo);
                push1_value(arr[maxcolsize[col2] * 2 - 1][(col2)*4 - 1], stack_undo_value);

                arr[maxcolsize[col2] * 2 - 1][(col2)*4 - 2] = -1;
                push1(&arr[maxcolsize[col2] * 2 - 1][(col2)*4 - 2], stack_undo);
                push1_value(arr[maxcolsize[col2] * 2 - 1][(col2)*4 - 2], stack_undo_value);

                arr[maxcolsize[col2] * 2 - 1][(col2)*4 - 3] = -1;
                push1(&arr[maxcolsize[col2] * 2 - 1][(col2)*4 - 3], stack_undo);
                push1_value(arr[maxcolsize[col2] * 2 - 1][(col2)*4 - 3], stack_undo_value);

                maxcolsize[col2]--;

                k--;
            }
            else if (isalpha(col2) && (col2 == 85 || col2 == 117)) /// undo
            {

                push2(pop1(stack_undo), stack_redo);
                push2_value(pop1_value(stack_undo_value), stack_redo_value);

                push2(pop1(stack_undo), stack_redo);
                push2_value(pop1_value(stack_undo_value), stack_redo_value);

                push2(pop1(stack_undo), stack_redo);
                push2_value(pop1_value(stack_undo_value), stack_redo_value);

                for (int i = 1; i < height; i += 2)
                {
                    for (int j = 1; (j < width); j++)
                    {

                        if ((int)&arr[i][j] == (int)stack_redo[0] || (int)&arr[i][j] == (int)stack_redo[2] || (int)&arr[i][j] == (int)stack_redo[1])
                        {
                            arr[i][j] = 32;
                            if (j % 4 == 1)
                            {
                                maxcolsize[(int)(j / 4.0 + 0.75)]++;
                            }
                        }
                    }
                }
                k++;
            }

            else if (isalpha(col2) && (col2 == 82 || col2 == 114)) /// redo
            {
                push1(pop2(stack_redo), stack_undo);
                push1_value(pop2_value(stack_redo_value), stack_undo_value);

                push1(pop2(stack_redo), stack_undo);
                push1_value(pop2_value(stack_redo_value), stack_undo_value);

                push1(pop2(stack_redo), stack_undo);
                push1_value(pop2_value(stack_redo_value), stack_undo_value);

                for (int i = 1; i < height; i += 2)
                {
                    for (int j = 1; (j < width); j++)
                    {
                        if ((int)&arr[i][j] == (int)stack_undo[0])
                        {
                            arr[i][j] = stack_undo_value[0]; /// need some edit !!!

                            if (j % 4 == 1)
                            {
                                maxcolsize[(int)(j / 4.0 + 0.75)]--;
                            }
                        }
                        else if ((int)&arr[i][j] == (int)stack_undo[1])
                        {
                            arr[i][j] = stack_undo_value[1];

                            if (j % 4 == 1)
                            {
                                maxcolsize[(int)(j / 4.0 + 0.75)]--;
                            }
                        }
                        else if ((int)&arr[i][j] == (int)stack_undo[2])
                        {
                            arr[i][j] = stack_undo_value[2];

                            if (j % 4 == 1)
                            {
                                maxcolsize[(int)(j / 4.0 + 0.75)]--;
                            }
                        }
                    }
                }
                k--;
            }
            else if (isalpha(col2) && (col2 == 88 || col2 == 120))
            {
                printf("\nDo you want to save?(y/n): \n");
                int save_check = getch();
                if (save_check == 89 || save_check == 121)
                {
                    printf("\nChoose from 1 -> 3 the file index you want to save your game in:\n");
                    fflush(stdin);
                    int file_number = getchar();

                    if (isdigit(file_number) && file_number - 48 == 1)
                    {
                        save(1, 1, stack_undo, stack_undo_value, column, row, arr, turn, k, maxcolsize);
                        system("cls");
                        ShowConsoleCursor(false);
                        main();
                    }
                    else if (isdigit(file_number) && file_number - 48 == 2)
                    {
                        save(1, 2, stack_undo, stack_undo_value, column, row, arr, turn, k, maxcolsize);
                        system("cls");
                        ShowConsoleCursor(false);
                        main();

                    }
                    else if (isdigit(file_number) && file_number - 48 == 3)
                    {
                        save(1, 3, stack_undo, stack_undo_value, column, row, arr, turn, k, maxcolsize);
                        system("cls");
                        ShowConsoleCursor(false);
                        main();
                    }
                    else
                    {
                        printf("\nNot a valid file index, try again later\n");
                        turn--;
                    }
                }
                else
                {
                    turn--;
                }
            }
            else
            {
                printf("\n Enter a valid input\n");
                turn--;
            }

            printboard(height, width, arr);
            player1 = check_score(height, width, arr, 1);
            player2 = check_score(height, width, arr, -1);

            clock_t end = clock(); // defining end time

            display_time(start, end); // display the time
            SetConsoleTextAttribute(console, 9);
            printf("\nPlayer 1 total moves: %d \n", (int)(turn/2.0 + 0.5));
            SetConsoleTextAttribute(console, 15);

            SetConsoleTextAttribute(console, 12);
            printf("\nPlayer 2 total moves: %d \n", turn/2);
            SetConsoleTextAttribute(console, 15);

            turn++;
        }
    }
    if (player1 > player2)
    {
        SetConsoleTextAttribute(console, 9);
        printf("\nPlayer 1 is the winner\n");
        SetConsoleTextAttribute(console, 15);

        FILE *fb;
        if (((fb = fopen("top scores", "a")) == NULL))
        {
            printf("\ncan't add your name\n");
        }
        winner.r = 1;

        SetConsoleTextAttribute(console, 9);
        printf("\nEnter your name:");
        SetConsoleTextAttribute(console, 15);

        gets(winner.name);
        for (size_t i = 0; i < strlen(winner.name); ++i)
        {
            // printf("%c",winner.name[i]);
            /// no integer in the name
            winner.name2[i] = toupper((unsigned char)winner.name[i]);
        }
        winner.score = player1;
        fprintf(fb, "%-2d%-70s%-2d", winner.r, winner.name2, winner.score);
        fprintf(fb, "\n");
        fclose(fb);
        sortscore(fb, player1);

        xml();

        int top_scores = settings.highscores;

        printscores(fb, top_scores);
    }
    else if (player2 > player1)
    {

        SetConsoleTextAttribute(console, 12);
        printf("\nPlayer 2 is the winner\n");
        SetConsoleTextAttribute(console, 15);

        FILE *fb;
        if (((fb = fopen("top scores", "a")) == NULL))
        {
            printf("\ncan't add your name\n");
        }
        winner.r = 1;

        SetConsoleTextAttribute(console, 12);
        printf("\nEnter your name:");
        SetConsoleTextAttribute(console, 15);

        gets(winner.name);
        for (size_t i = 0; i < strlen(winner.name); ++i)
        {
            winner.name2[i] = toupper((unsigned char)winner.name[i]);
        }
        winner.score = player2;
        fprintf(fb, "%-2d%-70s%-2d", winner.r, winner.name2, winner.score);
        fprintf(fb, "\n");
        fclose(fb);
        sortscore(fb, player2);
        xml();

        int top_scores = settings.highscores;

        printscores(fb, top_scores);
    }

    printf("\nDo you want to return to main menu? (y/n): ");

    fflush(stdin);

    int escape_char = getch();
    system("cls");
    if(isalpha(escape_char) &&(escape_char ==  89 || escape_char == 121))
    {
        main();
        ShowConsoleCursor(false);
    }

}
void sortscore(FILE *p, int score)
{

    int r[100];
    int t[100];
    int i = 0;
    int temp;
    memory filter[100];
    if (((p = fopen("top scores", "r+")) == NULL))
    {
        printf("\ncan't add your name\n");
    }

    while (fscanf(p, "%d", &winner.r) != EOF)
    {

        winner.r = i + 1;
        filter[i].rr = winner.r;
        r[i] = filter[i].rr;
        fgets(winner.name2, 70, p);
        for (int j = 0; j < 70; j++)
        {
            filter[i].nn[j] = winner.name2[j];
        }
        fscanf(p, "%d", &winner.score);
        filter[i].ss = winner.score;
        t[i] = filter[i].ss;

        i++;
    }

    int k, m;
    for (k = 0; k < i - 1; k++)
    {
        for (m = k + 1; m < i; m++)
        {
            if (filter[m].ss > filter[k].ss)
            {
                temp = filter[m].rr;
                filter[m].rr = filter[k].rr;
                filter[k].rr = temp;
            }
        }
    }

    qsort(r, i, sizeof(int), cmpfunc);
    qsort(t, i, sizeof(int), cmpfunc);
    for (int n = 0; n < i / 2; n++)
    {
        int tt;
        tt = r[n];
        r[n] = r[i - n - 1];
        r[i - n - 1] = tt;
    }
    for (int n = 0; n < i / 2; n++)
    {
        int tt;
        tt = t[n];
        t[n] = t[i - n - 1];
        t[i - n - 1] = tt;
    }

    for (int l = 0; l < i; l++)
    {
        if (t[l] == score)
        {
            printf("your rank is %d\n", r[i - l - 1]);
            break;
        }
    }
}
void printscores(FILE *p, int x) /// will print x TOP SCORES  I WILL PUT IT TEN ///ANDREW CHANGE THIS TO READ FROM CONFIGURATION
{
    char s3[70];
    int r[100];
    int t[100];
    int i = 0;
    int temp;
    memory filter[100];
    if (((p = fopen("top scores", "r+")) == NULL))
    {
        printf("\ncan't add your name\n");
    }

    while (fscanf(p, "%d", &winner.r) != EOF)
    {

        winner.r = i + 1;
        filter[i].rr = winner.r;
        r[i] = filter[i].rr;
        fgets(winner.name2, 70, p);
        for (int j = 0; j < 70; j++)
        {
            filter[i].nn[j] = winner.name2[j];
        }
        fscanf(p, "%d", &winner.score);
        filter[i].ss = winner.score;
        t[i] = filter[i].ss;

        i++;
    }

    for (int y = 0; y < i - 1; y++)
    {
        if ((strcmp(filter[i - 1].nn, filter[y].nn)) == 0)
        {
            if (filter[i - 1].ss > filter[y].ss)
            {
                int tt;
                tt = filter[i - 1].ss;
                filter[i - 1].ss = filter[y].ss;
                filter[y].ss = tt;
                filter[i - 1].ss = 0;
            }
        }
    }
    for (int y = 0; y < i; y++)
    {
        t[i] = filter[i].ss;
    }

    qsort(r, i, sizeof(int), cmpfunc);

    for (int n = 0; n < i - 1; n++)
    {
        for (int e = n + 1; e < i; e++)
        {
            if (t[n] > t[e])
            {
                int tt;
                tt = t[n];
                t[n] = t[e];
                t[e] = tt;
                strcpy(s3, filter[n].nn);
                strcpy(filter[n].nn, filter[e].nn);
                strcpy(filter[e].nn, s3);
            }
        }
    }

    for (int n = 0; n < i / 2; n++)
    {
        int tt;
        tt = r[n];
        r[n] = r[i - n - 1];
        r[i - n - 1] = tt;
    }
    for (int n = 0; n < i / 2; n++)
    {
        int tt;
        tt = t[n];
        t[n] = t[i - n - 1];
        t[i - n - 1] = tt;
        strcpy(s3, filter[n].nn);
        strcpy(filter[n].nn, filter[i - n - 1].nn);
        strcpy(filter[i - n - 1].nn, s3);
    }

    for (int g = 0; g < i; g++)
    {
        if (t[g] == 0)
        {
            break;
        }
        if (g > x - 1)
        {
            break;
        }
        printf("\n%2d%70s%2d\n", r[i - g - 1], filter[g].nn, t[g]);
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
                SetConsoleTextAttribute(console, 144); // blue
                printf(" ");
            }
            else if (arr[i][j] == -1)
            {
                SetConsoleTextAttribute(console, 64); // red
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

    printf("\ntime taken in game:\n\n");

    if (t.hours > 0)
    {
        printf("\thours : %d", t.hours);
    }
    if (t.minutes > 0)
    {
        printf("\tminutes : %d", t.minutes);
        printf("\t");
    }
    printf("\tseconds : %d\n", t.seconds);
}

void play_display_with_computer(int row, int column, int arr[row * 2 + 1][column * 4 + 1], int *stack_undo[], int *stack_redo[], int stack_undo_value[], int stack_redo_value[], int turn, int k, int maxcolsize[])
{
    int col1, col2, i, j, height = 2 * row + 1, width = 4 * column + 1, player1, player2; // col 1, 2: will stand for columns of two players , while i, j are iterators                                                      // number of moves
    clock_t start = clock();

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    printboard(height, width, arr); // print standard board

    while (k > 0)
    {

        if (turn % 2 == 1 || turn % 2 == -1) // odd turns player 1
        {
            char str1[2] = {-1, -1};
            int ch1, n1 = 0, col1 = 0;

            SetConsoleTextAttribute(console, 9);
            printf("\nPlayer1, Choose column from 1 to %d (u for undo, r for redo, s for save, x for main menu):\n", column);
            SetConsoleTextAttribute(console, 15);

            fflush(stdin);

            while ((ch1 = getchar()) != 10 && n1 < 2)
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
                        break;
                    }
                }
            }

            if ((isalpha(str1[0]) == 2 || isalpha(str1[0]) == 1) && str1[1] == -1)
            {
                col1 = str1[0];
            }
            else if (isdigit(str1[0]) && str1[1] == -1)
            {
                col1 = str1[0] - 48;
            }
            else if (isdigit(str1[0]) && isdigit(str1[1]))
            {
                for (int i = 0; isdigit(str1[i]) && i < 2; i++)
                {
                    col1 = col1 * 10 + (str1[i] - 48);
                }
            }


            if (isalpha(col1) && (col1 == 83 || col1 == 115)) /// to save the game
            {
                printf("\nChoose from 1 -> 3 the file index you want to save your game in:\n");
                fflush(stdin);
                int file_number = getchar();

                if (isdigit(file_number) && file_number - 48 == 1)
                {
                    save(0, 1, stack_undo, stack_undo_value, column, row, arr, turn, k, maxcolsize);
                }
                else if (isdigit(file_number) && file_number - 48 == 2)
                {
                    save(0, 2, stack_undo, stack_undo_value, column, row, arr, turn, k, maxcolsize);
                }
                else if (isdigit(file_number) && file_number - 48 == 3)
                {
                    save(0, 3, stack_undo, stack_undo_value, column, row, arr, turn, k, maxcolsize);
                }
                else
                {
                    printf("\nNot a valid file index, try again later\n");
                }
                turn--;
            }
            else if ((isalpha(str1[0]) != 2 && isalpha(str1[0]) != 1) && (col1 > column || col1 < 1 || maxcolsize[col1] < 1)) /// validate user input
            {
                printf("\nThis column is no longer valid\n");
                turn--;
            }
            else if (isalpha(col1) && first2 == -1 && (col1 == 82 || col1 == 114)) /// if user exceeds number of possible redos
            {
                printf("\nYou can not redo once more\n");
                turn--;
            }
            else if (isalpha(col1) && first1 == -1 && (col1 == 85 || col1 == 117)) /// if user exceeds number of possible undos
            {
                printf("\nYou can not undo once more\n");
                turn--;
            }
            else if ((col1 >= 1) && (col1 <= column)) /// playing normally
            {
                if (first2 != -1)
                {
                    first2 = -1;
                    first_value2 = -1;
                }
                arr[maxcolsize[col1] * 2 - 1][(col1)*4 - 1] = 1; // if player 1 choose a column the row index of it will start from height and will be decreased till zero
                push1(&arr[maxcolsize[col1] * 2 - 1][(col1)*4 - 1], stack_undo);
                push1_value(arr[maxcolsize[col1] * 2 - 1][(col1)*4 - 1], stack_undo_value);

                arr[maxcolsize[col1] * 2 - 1][(col1)*4 - 2] = 1;
                push1(&arr[maxcolsize[col1] * 2 - 1][(col1)*4 - 2], stack_undo);
                push1_value(arr[maxcolsize[col1] * 2 - 1][(col1)*4 - 2], stack_undo_value);

                arr[maxcolsize[col1] * 2 - 1][(col1)*4 - 3] = 1;
                push1(&arr[maxcolsize[col1] * 2 - 1][(col1)*4 - 3], stack_undo);
                push1_value(arr[maxcolsize[col1] * 2 - 1][(col1)*4 - 3], stack_undo_value);

                maxcolsize[col1]--;

                k--;
            }
            else if (isalpha(col1) && (col1 == 85 || col1 == 117)) /// undo
            {

                push2(pop1(stack_undo), stack_redo);
                push2_value(pop1_value(stack_undo_value), stack_redo_value);

                push2(pop1(stack_undo), stack_redo);
                push2_value(pop1_value(stack_undo_value), stack_redo_value);

                push2(pop1(stack_undo), stack_redo);
                push2_value(pop1_value(stack_undo_value), stack_redo_value);

                push2(pop1(stack_undo), stack_redo);
                push2_value(pop1_value(stack_undo_value), stack_redo_value);

                push2(pop1(stack_undo), stack_redo);
                push2_value(pop1_value(stack_undo_value), stack_redo_value);

                push2(pop1(stack_undo), stack_redo);
                push2_value(pop1_value(stack_undo_value), stack_redo_value);

                for (int i = 1; i < height; i += 2)
                {
                    for (int j = 1; (j < width); j++)
                    {
                        if ((int)&arr[i][j] == (int)stack_redo[0] || (int)&arr[i][j] == (int)stack_redo[1] || (int)&arr[i][j] == (int)stack_redo[2] || (int)&arr[i][j] == (int)stack_redo[3] || (int)&arr[i][j] == (int)stack_redo[4] || (int)&arr[i][j] == (int)stack_redo[5])
                        {
                            arr[i][j] = 32;

                            if (j % 4 == 1)
                            {
                                maxcolsize[(int)(j / 4.0 + 0.75)]++;
                            }
                        }
                    }
                }
                turn++;
                k += 2;
            }
            else if (isalpha(col1) && (col1 == 82 || col1 == 114)) /// redo
            {

                push1(pop2(stack_redo), stack_undo);
                push1_value(pop2_value(stack_redo_value), stack_undo_value);

                push1(pop2(stack_redo), stack_undo);
                push1_value(pop2_value(stack_redo_value), stack_undo_value);

                push1(pop2(stack_redo), stack_undo);
                push1_value(pop2_value(stack_redo_value), stack_undo_value);

                push1(pop2(stack_redo), stack_undo);
                push1_value(pop2_value(stack_redo_value), stack_undo_value);

                push1(pop2(stack_redo), stack_undo);
                push1_value(pop2_value(stack_redo_value), stack_undo_value);

                push1(pop2(stack_redo), stack_undo);
                push1_value(pop2_value(stack_redo_value), stack_undo_value);

                for (int i = 1; i < height; i += 2)
                {
                    for (int j = 1; (j < width); j++)
                    {
                        if ((int)&arr[i][j] == (int)stack_undo[0])
                        {
                            arr[i][j] = stack_undo_value[0];

                            if (j % 4 == 1)
                            {
                                maxcolsize[(int)(j / 4.0 + 0.75)]--;
                            }
                        }
                        else if ((int)&arr[i][j] == (int)stack_undo[1])
                        {
                            arr[i][j] = stack_undo_value[1];

                            if (j % 4 == 1)
                            {
                                maxcolsize[(int)(j / 4.0 + 0.75)]--;
                            }
                        }
                        else if ((int)&arr[i][j] == (int)stack_undo[2])
                        {
                            arr[i][j] = stack_undo_value[2];

                            if (j % 4 == 1)
                            {
                                maxcolsize[(int)(j / 4.0 + 0.75)]--;
                            }
                        }
                        else if ((int)&arr[i][j] == (int)stack_undo[3])
                        {
                            arr[i][j] = stack_undo_value[3];

                            if (j % 4 == 1)
                            {
                                maxcolsize[(int)(j / 4.0 + 0.75)]--;
                            }
                        }
                        else if ((int)&arr[i][j] == (int)stack_undo[4])
                        {
                            arr[i][j] = stack_undo_value[4];

                            if (j % 4 == 1)
                            {
                                maxcolsize[(int)(j / 4.0 + 0.75)]--;
                            }
                        }
                        else if ((int)&arr[i][j] == (int)stack_undo[5])
                        {
                            arr[i][j] = stack_undo_value[5];

                            if (j % 4 == 1)
                            {
                                maxcolsize[(int)(j / 4.0 + 0.75)]--;
                            }
                        }
                    }
                }
                turn++;
                k -= 2;
            }
            else if (isalpha(col1) && (col1 == 88 || col1 == 120))
            {
                printf("\nDo you want to save?(y/n): ");
                int save_check = getchar();
                if (save_check == 89 || save_check == 121)
                {
                    printf("\nChoose from 1 -> 3 the file index you want to save your game in:\n");
                    fflush(stdin);
                    int file_number = getchar();

                    if (isdigit(file_number) && file_number - 48 == 1)
                    {
                        save(0, 1, stack_undo, stack_undo_value, column, row, arr, turn, k, maxcolsize);
                        system("cls");
                        ShowConsoleCursor(false);
                        main();
                    }
                    else if (isdigit(file_number) && file_number - 48 == 2)
                    {
                        save(0, 2, stack_undo, stack_undo_value, column, row, arr, turn, k, maxcolsize);
                        system("cls");
                        ShowConsoleCursor(false);
                        main();
                    }
                    else if (isdigit(file_number) && file_number - 48 == 3)
                    {
                        save(0, 3, stack_undo, stack_undo_value, column, row, arr, turn, k, maxcolsize);
                        system("cls");
                        ShowConsoleCursor(false);
                        main();
                    }
                    else
                    {
                        printf("\nNot a valid file index, try again later\n");
                        turn--;
                    }
                }
                else
                {
                    turn--;
                }
            }
            else
            {
                printf("\n Enter a valid input.\n");
                turn--;
            }

            printboard(height, width, arr);

            player1 = check_score(height, width, arr, 1);
            player2 = check_score(height, width, arr, -1);

            clock_t end = clock(); // defining end time

            display_time(start, end); // display the time

            SetConsoleTextAttribute(console, 9);
            printf("\nPlayer 1 total moves: %d \n", (int)(turn/2.0 + 0.5));
            SetConsoleTextAttribute(console, 15);

            SetConsoleTextAttribute(console, 12);
            printf("\nPlayer 2 total moves: %d \n", turn/2);
            SetConsoleTextAttribute(console, 15);

            turn++;
        }
        else ////////////////////////////////////////////////COMPUTER'S TURN
        {
            ShowConsoleCursor(false);

            SetConsoleTextAttribute(console, 12);
            printf("\n  COMPUTER'S TURN\n");
            SetConsoleTextAttribute(console, 15);

            sleep(1);

            col2 = rand() % (column + 1);
            while (maxcolsize[col2] < 1 || col2 > column || col2 < 1)
            {
                col2 = rand() % (column + 1);
            }

            arr[maxcolsize[col2] * 2 - 1][(col2)*4 - 1] = -1; // if player 1 choose a column the row index of it will start from height and will be decreased till zero
            push1(&arr[maxcolsize[col2] * 2 - 1][(col2)*4 - 1], stack_undo);
            push1_value(arr[maxcolsize[col2] * 2 - 1][(col2)*4 - 1], stack_undo_value);

            arr[maxcolsize[col2] * 2 - 1][(col2)*4 - 2] = -1;
            push1(&arr[maxcolsize[col2] * 2 - 1][(col2)*4 - 2], stack_undo);
            push1_value(arr[maxcolsize[col2] * 2 - 1][(col2)*4 - 2], stack_undo_value);

            arr[maxcolsize[col2] * 2 - 1][(col2)*4 - 3] = -1;
            push1(&arr[maxcolsize[col2] * 2 - 1][(col2)*4 - 3], stack_undo);
            push1_value(arr[maxcolsize[col2] * 2 - 1][(col2)*4 - 3], stack_undo_value);

            printboard(height, width, arr);

            player1 = check_score(height, width, arr, 1);
            player2 = check_score(height, width, arr, -1);

            clock_t end = clock(); // defining end time

            display_time(start, end); // display the time

            SetConsoleTextAttribute(console, 9);
            printf("\nPlayer 1 total moves: %d \n", (int)(turn/2.0 + 0.5));
            SetConsoleTextAttribute(console, 15);

            SetConsoleTextAttribute(console, 12);
            printf("\nPlayer 2 total moves: %d \n", turn/2);
            SetConsoleTextAttribute(console, 15);

            maxcolsize[col2]--;

            turn++;

            ShowConsoleCursor(true);
            k--; // decrease k till zero which will indicate that board is complete
        }
    }

    if (player1 > player2)
    {
        SetConsoleTextAttribute(console, 9);
        printf("\nPlayer 1 wins\n");
        SetConsoleTextAttribute(console, 15);
    }
    else if (player2 > player1)
    {
        SetConsoleTextAttribute(console, 12);
        printf("\nComputer wins\n");
        SetConsoleTextAttribute(console, 15);
    }

    printf("\nDo you want to return to main menu? (y/n): ");

    fflush(stdin);

    int escape_char = getch();
    system("cls");
    if(isalpha(escape_char) &&(escape_char ==  89 || escape_char == 121))
    {
        main();
        ShowConsoleCursor(false);
    }
}

int check_score(int height, int width, int arr[height][width], int xo)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
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
        SetConsoleTextAttribute(console, 9);
        printf("\nPlayer 1 score: %d\n", score);
        SetConsoleTextAttribute(console, 15);
    }
    else
    {
        SetConsoleTextAttribute(console, 12);
        printf("\nPlayer 2 score: %d\n", score);
        SetConsoleTextAttribute(console, 15);
    }

    return score;
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

// undo stack_value

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

void xml()
{
    static int error_path = 0;

    char path[200] = {'0'};
    if (error_path == 0) // dafault file to be named "config.xml"
        strcpy(path, "config.xml");
    else
    {
        if (error_path <= 3) // if any error till 3 trials, program gets other file path
        {
            printf("configuration file not valid, Enter a valid path: ");
            gets(path);
        }
        else // after 3 trials, program creates its own default values
        {    // default

            settings.width = 7;
            settings.height = 9;
            settings.highscores = 10;
            return;
        }
    }
    char ch, file_new[500] = {'0'};
    char conf_1[] = "<Configurations>", width_1[] = "<Width>", height_1[] = "<Height>", highscores_1[] = "<Highscores>";
    char conf_2[] = "</Configurations>", width_2[] = "</Width>", height_2[] = "</Height>", highscores_2[] = "</Highscores>";
    int i = 0, start_config, end_config, start_width, end_width, start_height, end_height, start_highscores, end_highscores, err_flag, tag_flag = 0;

    FILE *file;

    if ((file = fopen(path, "r")) == NULL)
    {
        error_path++;
        xml();
        return;
    }
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '<')
        {
            tag_flag = 0;
        }
        else if (ch == '>')
        {
            tag_flag = 1;
        }

        if (ch != ' ' && ch != '\n' && ch != '\t' && tag_flag == 1)
        { // IGNORING ANY SPACES OR TABS OR BREAKING LINE
            file_new[i] = ch;
            i++;
        }
        else if (tag_flag == 0)
        {
            file_new[i] = ch;
            i++;
        }
    }
    file_new[i] = '\0'; // insert the end of string file

    fclose(file);

    start_config = count_string(conf_1, file_new);
    end_config = count_string(conf_2, file_new);

    if (start_config == -1 || end_config == -1 || end_config < start_config)
    {
        error_path++;
        return xml();
    }

    start_width = count_string(width_1, file_new);
    end_width = count_string(width_2, file_new);

    int size_width = end_width - start_width + 1;

    if (start_width == -1 || end_width == -1 || end_width < start_width || end_width > end_config || start_width < start_config)
    {
        error_path++;
        return xml();
    }
    char width[size_width];

    ///////handle if letters are assigned between tags

    // for width

    for (int p = 0, j = start_width + 7; j < end_width; j++, p++)
    {
        err_flag = 0;
        if (isdigit(file_new[j]))
        {
            width[p] = file_new[j];
        }
        else
        {
            err_flag = 1;
            error_path++;
            break;
        }
    }

    if (err_flag)
    {
        return xml();
    }
    width[end_width] = '\0';

    start_height = count_string(height_1, file_new); /// for getting the height value
    end_height = count_string(height_2, file_new);
    int size_height = end_height - start_height + 1;

    if (start_height == -1 || end_height == -1 || end_height < start_height || end_height > end_config || start_height < start_config)
    {
        error_path++;
        return xml();
    }

    char height[size_height];

    // for height
    for (int p = 0, j = start_height + 8; j < end_height; j++, p++)
    {
        err_flag = 0;
        if (isdigit(file_new[j]))
        {
            height[p] = file_new[j];
        }
        else
        {
            err_flag = 1;
            error_path++;
            break;
        }
    }

    if (err_flag)
    {
        return xml();
    }

    height[end_height] = '\0';

    start_highscores = count_string(highscores_1, file_new);
    end_highscores = count_string(highscores_2, file_new);

    int size_highscores = end_highscores - start_highscores + 1;

    if (start_highscores == -1 || end_highscores == -1 || end_highscores < start_highscores || end_highscores > end_config || start_highscores < start_config)
    {
        error_path++;
        return xml();
    }

    char highscores[size_highscores];

    // for high scores
    for (int p = 0, j = start_highscores + 12; j < end_highscores; ++j, ++p)
    {
        err_flag = 0;
        if (isdigit(file_new[j]))
        {
            highscores[p] = file_new[j];
        }
        else
        {
            err_flag = 1;
            error_path++;
            break;
        }
    }
    if (err_flag)
    {
        return xml();
    }

    highscores[end_highscores] = '\0';

    if (atoi(height) < 4 || atoi(width) < 4 || atoi(highscores) < 1 || atoi(height) > 50 || atoi(width) > 50 || atoi(highscores) > 100) // convert string to number
    {
        error_path++;
        return xml();
    }

    settings.width = atoi(width);
    settings.height = atoi(height);
    settings.highscores = atoi(highscores);
}

int count_string(char word1[], char word2[])
{
    int counter = -1, i = 0;
    while (word2[i] != '\0')
    {
        int j = 0;
        if (word2[i] == word1[j])
        {
            int k = i;
            while (word2[k] == word1[j] && word1[j] != '\0')
            {
                k++;
                j++;
            }
            if (word1[j] == '\0')
            {
                counter = i;
            }
        }
        i++;
    }
    return counter;
}

void save(int mode, int save_no, int *stack_undo[], int stack_undo_value[], int column, int row, int arr[row * 2 + 1][column * 4 + 1], int turn, int k, int maxcolsize[])
{
    FILE *saved_file;
    switch (save_no)
    {
    case 1:
        saved_file = fopen("game1", "wb");
        break;
    case 2:
        saved_file = fopen("game2", "wb");
        break;
    case 3:
        saved_file = fopen("game3", "wb");
        break;
    }

    fwrite(&column, sizeof(column), 1, saved_file);
    fwrite(&row, sizeof(row), 1, saved_file);

    fwrite(&mode, sizeof(mode), 1, saved_file);

    fwrite(&turn, sizeof(turn), 1, saved_file);

    fwrite(&k, sizeof(k), 1, saved_file);

    fwrite(&first_value1, sizeof(first_value1), 1, saved_file);
    fwrite(stack_undo_value, sizeof(stack_undo_value[0]), row * column * 3, saved_file);

    fwrite(&first1, sizeof(first1), 1, saved_file);
    fwrite(stack_undo, sizeof(stack_undo[0]), row * column * 3, saved_file);

    fwrite(maxcolsize, sizeof(maxcolsize[0]), column + 1, saved_file);

    fwrite(arr, sizeof(arr[0][0]), (row * 2 + 1) * (column * 4 + 1), saved_file);

    fclose(saved_file);
}

int loadgame(int game_number, int *stack_redo[], int stack_redo_value[])
{
    FILE *load_file;
    switch (game_number)
    {
    case 1:
        load_file = fopen("game1", "rb");
        break;
    case 2:
        load_file = fopen("game2", "rb");
        break;
    case 3:
        load_file = fopen("game3", "rb");
        break;
    }

    if (load_file == NULL)
    {
        printf("\nan error occurred while opening the file.\n");
        return;
    }

    int column, row, turn, mode, k;

    fread(&column, sizeof(column), 1, load_file);
    fread(&row, sizeof(row), 1, load_file);

    fread(&mode, sizeof(mode), 1, load_file);

    int arr[row * 2 + 1][column * 4 + 1], stack_undo_value[row * column * 3], *stack_undo[row * column * 3], maxcolsize[column + 1];

    fread(&turn, sizeof(turn), 1, load_file);

    fread(&k, sizeof(k), 1, load_file);

    fread(&first_value1, sizeof(first_value1), 1, load_file); // edited globally
    fread(stack_undo_value, sizeof(stack_undo_value[0]), row * column * 3, load_file);

    fread(&first1, sizeof(first1), 1, load_file); // edited globally
    fread(stack_undo, sizeof(stack_undo[0]), row * column * 3, load_file);

    fread(maxcolsize, sizeof(maxcolsize[0]), column + 1, load_file);

    fread(arr, sizeof(arr[0][0]), (row * 2 + 1) * (column * 4 + 1), load_file);

    fclose(load_file);

    if (mode == 0)
    {
        play_display_with_computer(row, column, arr, stack_undo, stack_redo, stack_undo_value, stack_redo_value, turn, k, maxcolsize);
    }
    else if (mode == 1)
    {
        play_display(row, column, arr, stack_undo, stack_redo, stack_undo_value, stack_redo_value, turn, k, maxcolsize);
    }
}
