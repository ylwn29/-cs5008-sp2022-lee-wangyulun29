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
      return 1;
    }
    if (n==2){
      return 7;
    }
    if (d[n]!=0){
      return d[n];
    }
    int i=3,sum=0;
    while(i<=n){
      sum += 2*(dp(n-i));
      i++;
      //printf("sum:%d n:%d i:%d\n",sum, n, i);
    }
    d[n] = 3*dp(n-2) + 2*dp(n-1) + sum;
    return d[n];
}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}
