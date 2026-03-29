#include <stdio.h>

main()
{
int x,y,z,t;
scanf("%d%d%d",&x,&y,&z);
if (x>y)
{t=x;x=y;y=t;} /* 交换 x,y 的值 */
if(x>z)
{t=z;z=x;x=t;}/* 交换 x,z 的值 */
if(y>z)
{t=y;y=z;z=t;}/* 交换 z,y 的值 */
printf("small to big: %d %d %d\n",x,y,z);
}
