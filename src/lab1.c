/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>

void multiply(int matrix[][5], int array[], int size1, int size2){
    for(int i = 0; i < 2; i++){
         for(int j = 0; j < 5; j++){
              matrix[i][j] = matrix[i][j] * array[j];
         }
    }
}

int main()
{
    //part3
    int array[] = {1,2,3,4,5};
    int matrix[][5] = {{1,1,1,1,1}, {1, 1, 1, 1, 1}};
    multiply(matrix, array);
    for(int i = 0; i < 2; i++){
           for(int j = 0; j < 5; j++){
               printf("[%d], ", matrix[i][j]);
           }
       }
    return 0;
}



int part2(){
    int number;
    char name[500];
    printf("Enter a number: ");
    scanf("%d", &number);
    printf("Enter a sentence: ");
    scanf("%s", name);
    for (int i = 0; i < number; i++)
        printf("%s\n",name);
    return 0;
}

int part1(){
    int number;
    char* name = "Sabina";
    printf("Enter a number: ");
    scanf("%d", &number);
    for (int i = 0; i < number; i++)
        printf("%s\n",name);
    return 0;
}
