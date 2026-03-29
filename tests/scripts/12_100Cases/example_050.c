#include <stdio.h>

test.h 文件如下：
#define LAG >
#define SMA <
#define EQ
＃ i nclude "test.h" /* 一个新文件 50.c，包含 test.h*/ ＃ i nclude "stdio.h"
void main()
{ int i=10;
int j=20;
if(i LAG j)
printf("\40: %d larger than %d \n",i,j);
else if(i EQ j)
printf("\40: %d equal to %d \n",i,j);
else if(i SMA j)
printf("\40:%d smaller than %d \n",i,j);
else
printf("\40: No such value.\n");
}
