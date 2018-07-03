#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];
int i, j, pivot;

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/
void quick_sort(int A[ ], int n){
    int i ,j ,pivot ;
    if(n<=1)return;
    pivot = A[0];
    for(i = j = 1; i < n; i++){
        if(A[i] < pivot){
            int z = A[j];
            A[j] = A[i];
            A[i] = z;
            j++;
        }
    }
    int x=A[0];
    A[0]=A[j-1];
    A[j-1]=x;
    quick_sort(A,j-1);
    quick_sort(A+j,n-j);
    
}

int quick_select(int A[], int n, int k){
	if(n>5){
  	for(i=0;i<n/5;i++){
  		quick_sort(A+5*i,5);
  		int z = A[i+1];
      A[i+1] = A[3+5*i];
      A[3+5*i] = z;}
      if(n%5==1){
      A[n/5+1]=A[n-1];     
      }else if(n%5==2){
     A[n/5+1]=(A[n-2]+A[n-1])/2;
     }else if(n%5==3){
     	A[n/5+1]=A[n-2];
     }else if (n%5==4){
     	A[n/5+1]=(A[n-3]+A[n-2])/2;}
     if((n-1)/5+1%2==0){
     	pivot=(A[((n-1)/5+1)/2]+A[((n-1)/5+1)/2-1])/2;
     }else{pivot=A[((n-1)/5+1)/2];}
	}else{
	if(n%2==0){
		pivot=(A[n/2]+A[n/2-1])/2;
	}else{pivot=A[n/2];}}
  	
  for(i = j = 0; i < n; i++){
    if(A[i] <= pivot){
      int z = A[j];
      A[j] = A[i];
      A[i] = z;
      j++;
    }
  }

  if(j == k+1) return pivot;
  else if(j < k+1) return quick_select(A+j, n-j, k-j);
  else return quick_select(A, j-1, k);
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
//    printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
