/* This code was written by Devynne Miller and Maria Lusardi */
#include<stdio.h>
#include<stdlib.h>

//functions
/* This function takes two parameters.
A: an integer array
heapsize: an integer representing the number of elements in A
Starting with the parent node with the largest index, it calls MaxHeapify on each parent node
until it is guaranteed that no child node is larger than its parent  */
void BuildMaxHeap(int* A, int heapsize); //written
/*This function restores the MaxHeap property of an array
A: an integer array
i: the index of the head of the sub-heap to be restored
heapsize: the total number of elements in the heap
This function will check the child nodes of the given index to ensure the children are not greater than it.
If they are, the largest child becomes the parent and heapify is re-called on the node it had previously resided.
This continues until either the children are no longer larger than the given parent or the end of the heap is reached.*/
void MaxHeapify(int* A, int i, int heapsize); //written
/*This function extracts the largest element from the heap.
A: an integer array
heapsize: a pointer to the number of nodes in the array
This function will remove the first element in a heap, since by the max-heap property it is guaranteed to be the largest.
Then it will replace that node with the value in the last place on the array, decrease the count of heapsize, and call max-heapify
starting with the first node to restore the max-heap property of the array.*/
int HeapExtractMax(int* A, int *heapsize); //written
/*This function changes the value, or key, at the provided index and restores the heap.
A: an integer array
i: index to be changed
key: value to be added
size: number of elements in array
The value of A at index i is changed to the key. Then it is checked if the inserted key is greater than or less than the value 
previously there. If it is greater than, the parent nodes are checked. If the parent nodes are smaller than the current node, then they
are swaped and the parent's parent node is checked. This is repeated until the first node in the array is reached.
If the inserted key is less than the value previously there, MaxHeapify is called.*/
void HeapChangeKey(int* A, int i, int key, int size); //written
/*This key inserts a value into a heap and restores the max-heap property.
A: an integer array
key: value to be inserted
heapsize: a pointer to the number of nodes in A
First, this function increases the value pointed to by heapsize by one. The last place on the array is set to an impossibly small
number. HeapChangeKey is called to replace the last spot on the array with the key to be inserted. Since it is larger than the 
current value, it will check all of the parent nodes and swap if need be until the first node is reached or the parents are no longer
smaller than the child node. This indicates the max-heap property has been restored. */
void MaxHeapInsert(int* A, int key, int *heapsize); //written, but question?
/*This funciton returns the index of the parent node for the provided index
i: index of a node*/
int Parent(int i); //written
/*This funciton returns the index of the left child node for the provided index
i: index of a node*/
int Left(int i); //written
/*This funciton returns the index of the right child node for the provided index
i: index of a node*/
int Right(int i); //written
/*This function removes the value in the node at the provided index and restores the max-heap property
A: an integer array
i: index where value is to be removed
size: a pointer to the number of elements in the array
First, this function creates a variable key, which is the last value in the array. Then it decreases the size of the array and calls
HeapChangeKey to replace the value to be removed with the key.*/
void Delete(int* A, int i, int* size);

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

    /*for(int i = 1; i <=heapsize; i++){
        printf("%d\n", A[i]);
    }*/

    BuildMaxHeap(A, heapsize);
    //printf("finished building heap\n");
    /*for(int i = 1; i <=heapsize; i++){
        printf("%d\n", A[i]);
    }*/

    char command;
    int parameter1;
    int parameter2;
    while(!feof(fp)){
        fscanf(fp, "%c", &command);
        if (command == 'E') {
            //printf("Command was E\n");
            fscanf(fp, "\n");
            HeapExtractMax(A, &heapsize);
            /*for(int i = 1; i <=heapsize; i++){
                printf("%d\n", A[i]);
            }*/
        }
        else if (command == 'I') {
            //printf("Command was I\n");
            fscanf(fp, "%d\n", &parameter1);
            MaxHeapInsert(A, parameter1, &heapsize);
            /*for(int i = 1; i <=heapsize; i++){
                printf("%d\n", A[i]);
            }*/
        }
        else if (command == 'C') {
            //printf("Command was C\n");
            fscanf(fp, "%d %d\n", &parameter1, &parameter2);
            HeapChangeKey(A, parameter1, parameter2, heapsize);
            /*for(int i = 1; i <=heapsize; i++){
                printf("%d\n", A[i]);
            }*/
        }
        else if (command == 'D'){
            //printf("Command was D\n");
            fscanf(fp, "%d\n", &parameter1);
            Delete(A, parameter1, &heapsize);
            /*for(int i = 1; i <=heapsize; i++){
                printf("%d\n", A[i]);
            }*/
        }
    }
    for(int i = 1; i <=heapsize; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
    free(A);
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
    MaxHeapify(A, 1, *(heapsize));
    return max;
}

void HeapChangeKey(int* A, int i, int key, int size){
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
        MaxHeapify(A, i, size);
        /*while( i > 1 && A[Parent(i)] > A[i]){
            int temp = A[i];
            A[i] = A[Parent(i)];
            A[Parent(i)] = temp;
            i = Parent(i);
        }*/
    }
}

void MaxHeapInsert(int* A, int key, int *heapsize){
    (*(heapsize))++;
    A[*(heapsize)] = -1;
    HeapChangeKey(A, *heapsize, key, *heapsize);
}

void Delete(int* A, int i, int* size) {
    int key = A[*size];
    (*(size))--;
    HeapChangeKey(A, i, key, *size);
}