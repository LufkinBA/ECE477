#include<stdio.h>

int fibo(int num)
{
    if(num==1||num==2)
        return 1;
    else
        return (fibo(num-1)+fibo(num-2));  // recursive call
}

int main()
{
    int i,n;
    printf("Enter the required term: ");
    scanf("%d",&n);
    printf("First %d fibonacci numbers are\n",n);
    for (i=1; i<=n; i++)
        printf("%d\n",fibo(i));
    return 0;
}
