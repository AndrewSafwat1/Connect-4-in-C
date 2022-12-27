#include <stdio.h>
#include <stdlib.h>

int horizontal_check(int height, int width, int arr[height][width], int xo, int, int, int);
int vertical_check(int height, int width, int arr[height][width], int xo, int, int, int);
int diagonal_check_45(int height, int width, int arr[height][width], int xo, int, int, int);
int diagonal_check_135(int height, int width, int arr[height][width], int xo, int, int, int);


int main(){

    int arr[6][6] = {0};
    int score = 0, count;
    /// only a sample board !
    for(int i = 1; i < 6; i++)
    {
        arr[i-1][1] = -1;
    }
    arr[5][0]=-1;
    for(int i =0; i< 6 ; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            printf("%d ", arr[i][j]);

        }
        printf("\n");
    }

    for(int i =5; i >= 0;i--)
    {
        for(int j = 5; j>= 0; j--)
        {

            count = horizontal_check(6, 6, arr, -1, i, j, 0); //height then width (columns) then array - count should be 4 !!!!!
            if(count / 4 >= 1)
            {
                score += (count -3);

            }

            count = vertical_check(6, 6, arr, -1, i, j, 0);
            if(count / 4 >= 1)
            {
                score += (count -3);

            }

            count = diagonal_check_45 (6, 6, arr, -1, i, j, 0);
            if(count / 4 >= 1)
            {
                score += (count -3);
            }

            count = diagonal_check_135 (6, 6, arr, -1, i, j, 0);
            if(count / 4 >= 1)
            {
                score += (count -3);
            }
        }
    }



    printf("\n%d", score); //should print 3
    return 0;
}

int horizontal_check(int height, int width, int arr[height][width], int xo, int i, int j, int counter) //parameters : 1- rows,  2 -columns , 3 - array ,
//4-x or O value (1 or -1) ,5, 6:  i and j from nested for loop commented above
{
    int count;
    if(i < 0 || j < 0 || arr[i][j] == xo * -1 || arr[i][j] == 0 || counter == 4) //base cases
    {
        count = 0;
    }
    else
    {
        counter += 1;
        count = 1 +  horizontal_check(height, width, arr, xo, i, j-1, counter);
    }

    return count;
}

int vertical_check(int height, int width, int arr[height][width], int xo, int i, int j, int counter) //parameters : 1- rows,  2 -columns , 3 - array ,
//4-x or O value (1 or -1) ,5, 6:  i and j from nested for loop commented above
{
    int count;
    if(i < 0 || j < 0 || arr[i][j] == xo * -1 || arr[i][j] == 0 || counter == 4) //base cases
    {
        count = 0;
    }
    else
    {
        counter += 1;
        count = 1 +  vertical_check(height, width, arr, xo, i-1, j, counter);
    }

    return count;
}

int diagonal_check_135(int height, int width, int arr[height][width], int xo, int i, int j, int counter) //parameters : 1- rows,  2 -columns , 3 - array ,
//4-x or O value (1 or -1) ,5, 6:  i and j from nested for loop commented above
{
    int count;
    if(i < 0 || j < 0 || arr[i][j] == xo * -1 || arr[i][j] == 0 || counter == 4) //base cases
    {
        count = 0;
    }
    else
    {
        counter += 1;
        count = 1 +  diagonal_check_135(height, width, arr, xo, i-1, j-1, counter);
    }

    return count;
}

int diagonal_check_45(int height, int width, int arr[height][width], int xo, int i, int j, int counter) //parameters : 1- rows,  2 -columns , 3 - array ,
//4-x or O value (1 or -1) ,5, 6:  i and j from nested for loop commented above
{
    int count;
    if(i < 0 || j < 0 || arr[i][j] == xo * -1 || arr[i][j] == 0 || j == width || counter == 4) //base cases
    {
        count = 0;
    }
    else
    {
        counter += 1;
        count = 1 +  diagonal_check_45(height, width, arr, xo, i-1, j+1, counter);
    }

    return count;
}









