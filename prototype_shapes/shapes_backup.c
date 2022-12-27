#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int row, column;

int main()
{

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int width, height, input;

    printf("enter height and width (separated by a space): ");
    scanf("%d %d", &row, &column);

    width = column * 4 + 1;///edited!!
    height = row * 2 + 1;

    ///////////////////////////////////////////////in function
    int arr[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0) // done
                arr[i][j] = 201;

            else if (i == height - 1 && j == width - 1) // done
                arr[i][j] = 188;

            else if (i % 2 == 0 && j % 4 == 0 && i > 0 && i < height - 1 && j > 0 && j < width - 1) /// edited!
                arr[i][j] = 206;

            else if (i == 0 && j == width - 1) // done
                arr[i][j] = 187;

            else if (i == height - 1 && j == 0) // done
                arr[i][j] = 200;

            else if (i % 2 == 0 && j == 0) // done
                arr[i][j] = 204;

            else if (i % 2 == 0 && j == width - 1) // done
                arr[i][j] = 185;

            else if (i == 0 && j % 4 == 0) /// edited!!!!!!!
                arr[i][j] = 203;

            else if (i == height - 1 && j % 4 == 0) /// edited!!!!!!!
                arr[i][j] = 202;

            else if (i % 2 == 0 && j % 4 != 0) /// edited!!
                arr[i][j] = 205;

            else if (i % 2 == 1 && j % 4 == 0) /// edited!
                arr[i][j] = 186;

            else
                arr[i][j] = 32; // space in ascii code
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }

    for (int k = 0; k < column * row; k++)
    {
        scanf("%d", &input);
        if (arr[height - 2][input * 4 - 3] == 32) ///edited column only!!
        {
            arr[input * 2 -1][input * 4 - 3] = 1;
            arr[input * 2 -1][input * 4 - 2] = 1;
            arr[input * 2 -1][input * 4 - 1] = 1;
        }

        for (int i = 0; i < height; i++)
        {

            for (int j = 0; j < width; j++)
            {
                SetConsoleTextAttribute(hConsole, 15);
                if (arr[i][j] == 1)
                {
                    SetConsoleTextAttribute(hConsole, 144); ///edited
                    printf(" ");
                }
                else if (arr[i][j] == -1)
                {
                    SetConsoleTextAttribute(hConsole, 64);
                    printf(" ");
                }
                else
                    printf("%c", arr[i][j]);
            }
            printf("\n");
        }
    }
}
