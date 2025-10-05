#include <stdio.h>
#include <stdlib.h>

int main(){
	int n, i, sum = 0;
	int *arr;

	printf("Enter the amount of integers: ");
	scanf("%d", &n);

	arr = (int *)malloc(n * sizeof(int));
	if (arr == NULL){
		printf("Memory allocation failed!\n");
		return 1;
	}

	printf("Enter %d integers:\n", n);

	for(i = 0; i < n; i++){
		scanf("%d", &arr[i]);
	}

	for(i = 0; i < n; i++){
		sum += arr[i];
	}

	printf("The sum of your integers: %d\n", sum);

	free(arr);

	return 0;
}


