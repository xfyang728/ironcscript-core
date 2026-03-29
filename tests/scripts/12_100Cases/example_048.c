#include <stdio.h>

#define LAG >
#define SMA <
#define EQ
＃ i nclude "stdio.h"
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
