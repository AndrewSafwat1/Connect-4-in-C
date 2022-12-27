#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
void init_array(int height, int width, int arr[height][width]);
void play_display(int row, int column, int arr[row*2+1][column*2+1]);
void printboard(int height, int width, int arr[height][width]);

int main()
{

    int width, height, row, column;

    printf("enter height and width (separated by a space): ");
    scanf("%d %d", &row, &column);

    width = column * 2 + 1;
    height = row * 2 + 1;



    ///////////////////////////////////////////////in function
    int arr[height][width];

    init_array(height, width, arr);

    play_display(row, column, arr);


}
///////////////////////////


void init_array(int height, int width, int arr[height][width])
{
        for(int i = 0; i < height ;i++)
    {
        for(int j =0; j < width; j++)
        {
            if(i == 0 && j == 0)
                arr[i][j] = 201;

            else if(i == height -1 && j == width -1)
                arr[i][j] = 188;

            else if(i % 2 == 0 && j % 2 == 0 && i > 0 && i < height -1 && j > 0 && j < width -1)
                arr[i][j] = 206;

            else if(i == 0 && j == width -1)
                arr[i][j] = 187;

            else if(i == height -1 && j == 0)
                arr[i][j] = 200;

            else if(i % 2 == 0 && j == 0)
                arr[i][j] = 204;

            else if(i % 2 == 0 && j == width -1)
                arr[i][j] = 185;

            else if(i == 0 && j % 2 == 0)
                arr[i][j] = 203;

            else if(i == height -1 && j % 2 == 0)
                arr[i][j] = 202;

            else if(i % 2 == 0 && j % 2 == 1)
                arr[i][j] = 205;

            else if(i % 2 == 1 && j % 2 == 0)
                arr[i][j] = 186;

            else
                arr[i][j] = 32; //space in ascii code
        }
    }


}

//will SHIFT ONE DUE TO BASE 0
///////////////////////////////////////////////////////////////////////////////////////////////////



void play_display(int row, int column, int arr[row*2+1][column*2+1])
{
//    clock_t start=clock();
    int col1, col2, i, j, height = 2 * row + 1, width = 2 * column + 1; //col 1, 2: will stand for columns of two players , while i, j are iterators
    long long int k = row * column; //number of moves
//    int moves[row][column];  //array to store moves
    int maxcolsize[column + 1];   // array to check maxsize //all its elements will take value of height and will be decreased if column chosen


    for(i = 1; i < column + 1; i++)
    {
        maxcolsize[i] = row ;  // set all values of it to value of height as mentioned
    }

    int turn=1;

    printboard(height, width, arr); //print standard board



    while(k > 0)
    {

        if(turn % 2 == 1) // odd turns player 1
        {


            printf("\nplayer1,please choose column from 1 to %d:", column);
            scanf("%d",&col1);
            while(maxcolsize[col1] < 1 || col1 > column || col1 < 1)// validation on column index
            {
                 printf("this column is no longer valid\n");
                 printf("please choose another one: ");
                 scanf("%d", &col1);
            }
            arr[maxcolsize[col1] * 2 -1][col1 * 2 - 1] = 49; // if player 1 choose a column the row index of it will start from height and will be decreased till zero

            printboard(height, width, arr); // print board after playing

//          check_score(height, width, moves, 1);

//          clock_t end = clock(); // defining end time
//          display_time(start,end);  // display the time

            maxcolsize[col1]--;


            turn++; // increase turns


       }
       else
       {

            printf("\nplayer2, choose column from 1 to %d:", column);
            scanf("%d", &col2);

            while(maxcolsize[col2] < 1 || col2 > column || col2 < 1)
            {
                 printf("this column is no longer valid\n");
                 printf("please choose another one: ");
                 scanf("%d", &col2);
            }

            arr[maxcolsize[col2] * 2 -1][col2 * 2 - 1] = 50;


            printboard(height, width, arr);

//          check_score(height, width, moves, -1);
//          clock_t end = clock(); // defining end time
//          display_time(start,end);  // display the time


            maxcolsize[col2]--;

            turn++;

       }


       k--; //decrease k till zero which will indicate that board is complete
   }
}


void printboard(int height, int width, int arr[height][width]) //this fn will be called in the fn of playing game to display board after each turn
                                                    //it takes height and width and array of moves and display according to value
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i = 0; i < height; i++)
    {

        for(int j = 0 ; j < width ; j++)
        {
            SetConsoleTextAttribute(console, 15);
            if(arr[i][j] == 49)
            {
                SetConsoleTextAttribute(console, 144);
                printf(" ");
            }
            else if(arr[i][j] == 50)
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

