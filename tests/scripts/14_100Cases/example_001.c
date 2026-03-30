#include <stdio.h>

main()
{
int i,j,k;
printf("\n");
for(i=1;i<5;i++) /* 以下为三重循环 */
for(j=1;j<5;j++)
for (k=1;k<5;k++)
{
if (i!=k&&i!=j&&j!=k) /* 确 保 i 、 j 、 k 三 位 互 不 相 同
*/ printf("%d,%d,%d\n",i,j,k);
}
}
