#include<stdio.h>
#include<stdlib.h>
void display(int arr[], int size) { //display them
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("\n");
}
void readCheck(char *filename){
    int a=0;
    int *myArray = NULL;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return;
    }

    int num;
    while (fscanf(file, "%d", &num) != EOF) {       //it reads the end of the file and calculate their factorial
        if(num<0){
            printf("Negative number cannot be used for factorial!\n");
        }
        else{
            int result = 1;
            for(int i=1; i<=num; i++){
                result = result * i;
            }
            myArray = (int*)realloc(myArray, (a+1) * sizeof(int));
            myArray[a]= result;           //calculated values added into array
            a++;
        }
    }
    fclose(file);

    printf("Factorial:");
    display(myArray, a);
    free(myArray);
}

int main()
{
    readCheck("basakFile.txt");
    return 0;
}
