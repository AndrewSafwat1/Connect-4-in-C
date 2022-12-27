#include <stdio.h>
#include <stdlib.h>
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

int main()
{
    int flag = 1;
    scanf("%d %d", &row, &column);
    int *stack_undo[row * column];
    int *stack_redo[row * column];
    int arr[row][column];

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            arr[i][j] = 1;
            push1(&arr[i][j], stack_undo); // push every input in columns in the stack_undo
        }
    }

    // if user puts undo "u" or "U"
    push2(pop1(stack_undo), stack_redo); // remove top element from undo and inputs it as top elemnt in redo array
    push2(pop1(stack_undo), stack_redo); // remove top element from undo and inputs it as top elemnt in redo array

    // if user puts redo "r" or "R"
    push1(pop2(stack_redo), stack_undo); // remove top element from redo and inputs it as top element in undo array //TRY COMMENTING THIS LINE TO SEE THE DIFFERENCE

    // normal display of board but with condition
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            flag = 1;
            for (int k = 0; k <= first1; k++)
            {
                if (&arr[i][j] == stack_undo[k]) // checks if the element is present in undo stack in order to display it
                {
                    flag = 0;
                    printf("%d ", arr[i][j]);
                    break;
                }
            }
            if (flag)
            {
                printf("%d ", 0);
            }
        }
        printf("\n");
    }

    return 0;
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

        int *value = stack_undo[0];

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

        int *value = stack_redo[0];

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
