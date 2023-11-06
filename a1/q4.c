#include <stdio.h>
#include<stdlib.h>
#include<pthread.h>

typedef struct Node
{
    int val;
    struct Node* next;
} Node;
typedef struct ListRecord{
    struct Node *head;
    struct Node *tail;
    int size;
} ListRecord;
typedef ListRecord * List;

List createList();
void makeEmptyList(List);
void insertEndOfList(int, List);
void selectionSort(List);
void swap(Node*, Node*);
void *readSort(void*);
void *readCheck(void *);
void display(List);
void display2(int*, int);

List createList()
{
    List l;
    l=(struct ListRecord *) malloc(sizeof(struct ListRecord)); //Create List
    if(l==NULL){
        printf("Out of memory!\n");
        exit(1);
    }
    return l;
}

void makeEmptyList(List l)
{
    l->head=(struct Node*)malloc(sizeof(struct Node)); //Make an empty List
    if(l->head==NULL){
        printf("Out of memory!\n");
        exit(1);
    }
    l->head->next=NULL;
    l->tail=l->head;
    l->size=0;
}

void insertEndOfList(int x, List l) {     //it performs the insert operation
    Node* insert = (Node*)malloc(sizeof(Node));
    insert->val = x;
    insert->next = NULL;
    l->tail->next = insert;
    l->tail = insert;
    l->size++;
}

void selectionSort(List l) {         //apply selection sort algorithm
    Node* i, *j;
    int min;
    for (i = l->head->next; i->next != NULL; i = i->next) {
        min = i->val;
        for (j = i->next; j != NULL; j = j->next) {
            if (j->val < min) {
                min = j->val;
                swap(i, j);
            }
        }
    }
}

void swap(Node* a, Node* b) {          //this function performs the swap operation
    int temp = a->val;
    a->val = b->val;
    b->val = temp;
}

void *readSort(void *ptr) {
    List l = createList();
    makeEmptyList(l);

    FILE* file = fopen("basakFile.txt", "r");
    if (file == NULL) {
        printf("Could not open file %s\n", "basakFile.txt");
        return NULL;
    }

    int num;
    while (fscanf(file, "%d", &num) != EOF) {
        insertEndOfList(num, l);
    }
    fclose(file);

    selectionSort(l);

    printf("Thread 1 is Sorting:");
    display(l);
}

void display(List l)          //it takes the list and display it
{
    Node *p;
    p=l->head->next;
    while(p!=NULL)
    {
        printf("--> %d\t",p->val);
        sleep(1);
        p=p->next;
    }
    printf("\n");
}

void *readCheck(void *ptr){
    int a=0;
    int *myArray = NULL;

    FILE* file = fopen("basakFile.txt", "r");
    if (file == NULL) {
        printf("Could not open file %s\n", "basakFile.txt");
        return NULL;
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

    printf("Thread 2 calculating the Factorial:");
    display2(myArray, a);
    free(myArray);
}

void display2(int arr[], int size) { //display them
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        sleep(2);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

int main(void)
{
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, readSort, NULL);
    pthread_join(thread1, NULL);
    pthread_create(&thread2, NULL, readCheck, NULL);

    pthread_join(thread2, NULL);
    printf("\nFinished!\n");
    return 0;
}
