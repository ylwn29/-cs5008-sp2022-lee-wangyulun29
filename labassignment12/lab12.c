//enter your email here: wang.yulun@northeastern.edu
//enter your name here: Yulun Wang
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
void longestCommonPrefix(char arr[][20],int m, char res[20]){
    
    
    //insert your code here
    int index=0;
    int n=strlen(arr[0]);
    int i,j;
    for (i=0;i<n;i++){
        char c=arr[0][i];
	bool flag=true;
	for (j=1;j<m;j++){
	    if (!(c==arr[j][i])){
	        flag=false;
		break;
	    }
	}
	if(flag==true){
	    res[i]=c;
	}else{
	    break;
	}	
    }
    res[i]='\0';
        
}

int main(){
    int i;
    char arr[5][20]={"aaabc","aaanv","aaamk","aaavf","aaacf"};//input
    char res[20];//output
    int m=sizeof(arr)/sizeof(arr[0]);//number of rows

    longestCommonPrefix(arr,m,res);
    printf("The LCP is: ");
    for (i=0;i<strlen(res);i++){
        printf("%c",res[i]);
    }
    printf("\n");
    
    return 0;
}

