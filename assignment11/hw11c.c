// name: Yulun Wang
// email: wang.yulun@northeastern.edu

#include <stdio.h>

int d[20];

long long int dp(int n) {

    // Add your code here
    if (n==0){
      return 0;
    }
    if (n==1){
      return 0;
    }
    if (n==2){
      return 3;
    }
    if (d[n]!=0){
      return d[n];
    }
    int sum=0, i=n%2;
    while (i>=2){
      sum += 2*(dp(n-2*i));
      i--;
    }
    d[n] = 3*dp(n-2) + sum;
    return d[n];
}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}
