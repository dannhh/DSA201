#include <iostream>
#include <math.h>
using namespace std;

void ascendingSort(int a[], int n) {
    /*
     * STUDENT ANSWER
     * TODO: sort array in ascending order. 
     */
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            if(a[i] > a[j]) swap(a[i], a[j]);
        }
    }
}

void descendingSort(int a[], int n) {
    /*
     * STUDENT ANSWER
     * TODO: sort array in descending order. 
     */
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            if(a[i] < a[j]) swap(a[i], a[j]);
        }
    }
}

void mySort(int a[], int n, void (*sort)(int[], int)) {
	/*
     * STUDENT ANSWER
     * TODO: sort array based on sort algorithm of function sort. 
     */
    if(sort == descendingSort) descendingSort(a, n);
    else if(sort == ascendingSort) ascendingSort(a, n);
}
int main() {
    //<TEST>
   int n = 10;
int a[10] = { 4, 6, 1, 3, 4, 7, 8, 9, 10, 0 };
void (*sortAlgorithm)(int[], int) = ascendingSort;
    mySort(a, n, sortAlgorithm);
    for (int i = 0; i < n; ++i) {
	printf("%d ", a[i]);
    }
	
    return 0;
}