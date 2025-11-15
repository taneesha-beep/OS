#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

void desc_sorting(int a[], int n) {
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if (a[j] >= a[i]){
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
	
	printf("sorted array:\n");
	for (int i=0;i<n;i++){
		printf("%d\n",a[i]);
	}
}

void asc_sorting(int a[], int n) {
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if (a[j] <= a[i]){
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
	
	printf("sorted array:\n");
	for (int i=0;i<n;i++){
		printf("%d\n",a[i]);
	}
}

int main(){
	int n;
	printf("enter n: ");
	scanf("%d",&n);
	int a[n];
	
	printf("enter numbers: \n");
	
	for (int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	
	if (fork()==0) {
		asc_sorting(a,n);
	}
	
	else {
		desc_sorting(a,n);
	}
	
	return 0;
}