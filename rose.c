/*************************************************************************
	> File Name: rose.c
	> Author: zty
	> Mail: 1295303752@qq.com
	> Created Time: Tue 01 May 2018 11:45:59 AM CST
 ************************************************************************/

#include<stdio.h>
int rose(int n)
{
    int i, j, k,m;
    i = n % 10;
    j = n / 10 % 10;
    k = n / 100%10;
    m = n / 1000;
    if ((i*i*i*i + j*j*j*j + k*k*k*k+m*m*m*m) == n)
        return 1;
    else
        return 0;
}
int main()
{
    int i;
    for (i = 1000; i < 10000; i++)
    {
        if (rose(i) == 1)
            printf("%d ", i);
    }
    return 0;
}
