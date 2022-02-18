//Yulun Wang
//wang.yulun@northeastern.edu
// C program to check if the integer array contains duplicate elements.
#include<stdio.h>
#include<stdbool.h>

void sort(int* arr, int size) {
    int temp;
    for (int i=0; i<size; i++) {
	for (int j=0; j<size-1; j++) {
		if (arr[i] < arr[j]) {
		    temp = arr[i];
	    	    arr[i] = arr[j];
		    arr[j] = temp;	    
		}
	}
    }
    
}

int main(){

  int arr[] = {20,7,3,2,12,10,15, 2,2,2,2,4};
  int size = sizeof(arr) / sizeof(arr[0]);

  //insert your code here
  sort(arr,12);
  printf("%d",arr[11]);

return 0;
}
