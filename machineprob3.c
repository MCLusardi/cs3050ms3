#include<stdio.h>
#include<stdlib.h>

//functions
void BuildMaxHeap(int* A, int heapsize); //written
void MaxHeapify(int* A, int i, int heapsize); //written
int HeapExtractMax(int* A, int *heapsize); //written
void HeapChangeKey(int* A, int i, int key); //written
void MaxHeapInsert(int* A, int key, int *heapsize); //written, but question?
void Heapsort(int* A, int *heapsize);
int Parent(int i); //written
int Left(int i); //written
int Right(int i); //written
int HeapMax(int* A);
void Delete(int* A, int i);
void freeHeap(int* A);

int main(void){
    char filename[30];
    int heapsize = 0;

    printf("Enter the filename and hit enter!\n");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("File cannot be accessed\n");
    }
    
    fscanf(fp, "%d\n", &heapsize);
    int *A = malloc((1001) *sizeof(int)); //malloc extra space to account for indexing from 1

    for(int i = 1; i <= heapsize; i++){
        fscanf(fp, "%d\n", &A[i]);
    }

    for(int i = 1; i <=heapsize; i++){
        printf("%d\n", A[i]);
    }

    BuildMaxHeap(A, heapsize);
    printf("finished building heap\n");
    for(int i = 1; i <=heapsize; i++){
        printf("%d\n", A[i]);
    }

    char command;
    int parameter1;
    int parameter2;
    while(!feof(fp)){
        fscanf(fp, "%c", &command);
        if (command == 'E') {
            printf("Command was E\n");
            fscanf(fp, "\n");
            HeapExtractMax(A, &heapsize);
            for(int i = 1; i <=heapsize; i++){
                printf("%d\n", A[i]);
            }
        }
        else if (command == 'I') {
            printf("Command was I\n");
            fscanf(fp, "%d\n", &parameter1);
            MaxHeapInsert(A, parameter1, &heapsize);
            for(int i = 1; i <=heapsize; i++){
                printf("%d\n", A[i]);
            }
        }
        else if (command == 'C') {
            printf("Command was C\n");
            fscanf(fp, "%d %d\n", &parameter1, &parameter2);
            printf("Parameters are %d and %d\n", parameter1, parameter2);
        }
        else if (command == 'D'){
            printf("Command was D\n");
            fscanf(fp, "%d\n", &parameter1);
            printf("Parameter is %d\n", parameter1);
        }
    }
    
}

int Parent(int i){
    return(i/2);
}

int Left(int i){
    return(2*i);
}

int Right(int i){
    return((2*i)+1);
}

void MaxHeapify(int* A, int i, int heapsize){
    int left = Left(i);
    int right = Right(i);
    int largest = 0;

    if(left <= heapsize && A[left]>A[i]){
        largest = left;
    }else{
        largest = i;
    }
    if(right <= heapsize && A[right]>A[largest]){
        largest = right;
    }
    if(largest != i){
        int temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        MaxHeapify(A, largest, heapsize);
    }
}

void BuildMaxHeap(int* A, int heapsize){
    for(int i = (heapsize/2) ; i >= 1 ; i = i/2){
        MaxHeapify(A, i, heapsize);
    }
}

int HeapExtractMax(int* A, int *heapsize){
    if(*(heapsize) < 1){
        printf("error : heap underflow\n");
    }
    int max = A[1];
    A[1] = A[*(heapsize)];
    (*(heapsize))--;
    //heapsize[0] = *(heapsize)-1; 
    MaxHeapify(A, 1, *(heapsize));
    return max;
}

void HeapChangeKey(int* A, int i, int key){
    if(key > A[i]){
        A[i] = key;
        while( i > 1 && A[Parent(i)] < A[i]){
            int temp = A[i];
            A[i] = A[Parent(i)];
            A[Parent(i)] = temp;
            i = Parent(i);
        }
    }else if(key < A[i]){
        A[i] = key;
        while( i > 1 && A[Parent(i)] > A[i]){
            int temp = A[i];
            A[i] = A[Parent(i)];
            A[Parent(i)] = temp;
            i = Parent(i);
        }
    }
}

void MaxHeapInsert(int* A, int key, int *heapsize){
    (*(heapsize))++;
    A[*(heapsize)] = -1;
    HeapChangeKey(A, *heapsize, key);
}