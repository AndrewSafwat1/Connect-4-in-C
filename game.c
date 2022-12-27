#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

int horizontal_check(int height, int width, int arr[height][width], int xo, int, int, int);
int vertical_check(int height, int width, int arr[height][width], int xo, int, int, int);
int diagonal_check_45(int height, int width, int arr[height][width], int xo, int, int, int);
int diagonal_check_135(int height, int width, int arr[height][width], int xo, int, int, int);

void check_score(int height, int width, int arr[height][width], int xo);

void play_display_with_computer(int row, int column, int arr[row * 2 + 1][column * 2 + 1]);

void display_time(clock_t start, clock_t end);

void init_array(int height, int width, int arr[height][width]);               /// RECENTLY ADDED
void printboard(int height, int width, int arr[height][width]);               /// RECENTLY ADDED
void play_display(int row, int column, int arr[row * 2 + 1][column * 2 + 1]); /// RECENTLY ADDED
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

            width = column * 2 + 1;
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

            width = column * 2 + 1;
            height = row * 2 + 1;

            int arr[height][width];

            init_array(height, width, arr);

            sleep(1);
            system("cls");

            // algorithm of printing
            // display_board(width, height);
            // new algorithm of printing
            play_display(row, column, arr);

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
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
                arr[i][j] = 201;

            else if (i == height - 1 && j == width - 1)
                arr[i][j] = 188;

            else if (i % 2 == 0 && j % 2 == 0 && i > 0 && i < height - 1 && j > 0 && j < width - 1)
                arr[i][j] = 206;

            else if (i == 0 && j == width - 1)
                arr[i][j] = 187;

            else if (i == height - 1 && j == 0)
                arr[i][j] = 200;

            else if (i % 2 == 0 && j == 0)
                arr[i][j] = 204;

            else if (i % 2 == 0 && j == width - 1)
                arr[i][j] = 185;

            else if (i == 0 && j % 2 == 0)
                arr[i][j] = 203;

            else if (i == height - 1 && j % 2 == 0)
                arr[i][j] = 202;

            else if (i % 2 == 0 && j % 2 == 1)
                arr[i][j] = 205;

            else if (i % 2 == 1 && j % 2 == 0)
                arr[i][j] = 186;

            else
                arr[i][j] = 32; // space in ascii code
        }
    }
}

// function to play and display board after each turn it take two arguments :height and width
void play_display(int row, int column, int arr[row * 2 + 1][column * 2 + 1])
{
    clock_t start = clock();
    int col1, col2, i, j, height = 2 * row + 1, width = 2 * column + 1; // col 1, 2: will stand for columns of two players , while i, j are iterators
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

            printf("\nplayer1,please choose column from 1 to %d:", column);
            scanf("%d", &col1);
            while (maxcolsize[col1] < 1 || col1 > column || col1 < 1) // validation on column index
            {
                printf("this column is no longer valid\n");
                printf("please choose another one: ");
                scanf("%d", &col1);
            }
            arr[maxcolsize[col1] * 2 - 1][col1 * 2 - 1] = 1; // if player 1 choose a column the row index of it will start from height and will be decreased till zero

            printboard(height, width, arr); // print board after playing

            check_score(height, width, arr, 1);

            clock_t end = clock();    // defining end time
            display_time(start, end); // display the time

            maxcolsize[col1]--;

            turn++; // increase turns
        }
        else
        {

            printf("\nplayer2, choose column from 1 to %d:", column);
            scanf("%d", &col2);

            while (maxcolsize[col2] < 1 || col2 > column || col2 < 1)
            {
                printf("this column is no longer valid\n");
                printf("please choose another one: ");
                scanf("%d", &col2);
            }

            arr[maxcolsize[col2] * 2 - 1][col2 * 2 - 1] = -1;

            printboard(height, width, arr);

            check_score(height, width, arr, -1);

            clock_t end = clock();    // defining end time
            display_time(start, end); // display the time

            maxcolsize[col2]--;

            turn++;
        }

        k--; // decrease k till zero which will indicate that board is complete
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
                SetConsoleTextAttribute(console, 144);
                printf(" ");
            }
            else if (arr[i][j] == -1)
            {
                SetConsoleTextAttribute(console, 64);
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

void play_display_with_computer(int row, int column, int arr[row * 2 + 1][column * 2 + 1])
{
    int col1, col2, i, j, height = 2 * row + 1, width = 2 * column + 1; // col 1, 2: will stand for columns of two players , while i, j are iterators
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

            arr[maxcolsize[col1] * 2 - 1][col1 * 2 - 1] = 1;

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
            arr[maxcolsize[col2] * 2 - 1][col2 * 2 - 1] = -1;

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

    for (int i = height - 1; i >= 0; i--)
    {
        for (int j = width - 1; j >= 0; j--)
        {
            if (arr[i][j] == xo) /// NEW!
            {
                count = horizontal_check(height, width, arr, xo, i, j, 0); // height then width (columns) then array - count should be 4 !!!!!
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
        count = 1 + horizontal_check(height, width, arr, xo, i, j - 2, counter);
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
        count = 1 + diagonal_check_135(height, width, arr, xo, i - 2, j - 2, counter);
    }

    return count;
}

int diagonal_check_45(int height, int width, int arr[height][width], int xo, int i, int j, int counter) // parameters : 1- rows,  2 -columns , 3 - array ,
// 4-x or O value (1 or -1) ,5, 6:  i and j from nested for loop commented above
{
    int count;
    if (i < 0 || j < 0 || arr[i][j] == xo * -1 || arr[i][j] == 32 || j == width || counter == 4) // base cases
    {
        count = 0;
    }
    else
    {
        counter += 1;
        count = 1 + diagonal_check_45(height, width, arr, xo, i - 2, j + 2, counter);
    }

    return count;
}
