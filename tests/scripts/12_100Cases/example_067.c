#include <stdio.h>

main()
{
    int number[10];
    input(number);
    max_min(number);
    output(number);
}
input(number) int number[10];
{
    int i;
    for (i = 0; i < 9; i++)
        scanf("%d,", &number[i]);
    scanf("%d", &number[9]);
}
max_min(array) int array[10];
{
    int *max, *min, k, l;
    int *p, *arr_end;
    arr_end = array + 10;
    max = min = array;
    for (p = array + 1; p < arr_end; p++)
        if (*p > *max)
            max = p;
        else if (*p < *min)
            min = p;
    k = *max;
    l = *min;
    *p = array[0];
    array[0] = l;
    l = *p;
    *p = array[9];
    array[9] = k;
    k = *p;
    return;
}
output(array) int array[10];
{
    int *p;
    for (p = array; p < array + 9; p++)
        printf("%d,", *p);
    printf("%d\n", array[9]);
}
每天都要有进步
C 语言程序实例 100 个<3>
【程序 68 】 题目：有 n 个整数，使其前面各数顺序向后移 m 个位置，最后 m 个数变成最前面的 m 个数 1.程序分析： 2.程序源代码： main()
{
    int number[20], n, m, i;
    printf("the total numbers is:");
    scanf("%d", &n);
    printf("back m:");
    scanf("%d", &m);
    for (i = 0; i < n - 1; i++)
        scanf("%d,", &number[i]);
    scanf("%d", &number[n - 1]);
    move(number, n, m);
    for (i = 0; i < n - 1; i++)
        printf("%d,", number[i]);
    printf("%d", number[n - 1]);
}
move(array, n, m) int n, m, array[20];
{
    int *p, array_end;
    array_end = *(array + n - 1);
    for (p = array + n - 1; p > array; p--)
        *p = *(p - 1);
    *array = array_end;
    m--;
    if (m > 0)
        move(array, n, m);
}

【程序 69 】 题目：有 n 个人围成一圈，顺序排号。从第一个人开始报数（从 1 到 3 报数），凡报到 3 的人退出圈子，
    问最后留下的是原来第几号的那位。 1. 程序分析： 2.程序源代码：
#define nmax 50
    main()
{
    int i, k, m, n, num[nmax], *p;
    printf("please input the total of numbers:");
    scanf("%d", &n);
    p = num;
    for (i = 0; i < n; i++)
        *(p + i) = i + 1;
    i = 0;
    k = 0;
    m = 0;
    while (m < n - 1)
    {
        if (*(p + i) != 0)
            k++;
        if (k == 3)
        {
            *(p + i) = 0;
            k = 0;
            m++;
        }
        i++;
        if (i == n)
            i = 0;
    }
    while (*p == 0)
        p++;
    printf("%d is left\n", *p);
}

【程序 70 】 题目：写一个函数，求一个字符串的长度，在 main 函数中输入字符串，并输出其长度。 1.程序分析： 2.程序源代码： main()
{
    int len;
    char *str[20];
    printf("please input a string:\n");
    scanf("%s", str);
    len = length(str);
    printf("the string has %d characters.", len);
}
length(p) char *p;
{
    int n;
    n = 0;
    while (*p != '\0')
    {
        n++;
        p++;
    }
    return n;
}
【程序 71 】 题目：编写 input() 和 output() 函数输入，输出 5 个学生的数据记录。
    1.程序分析： 2.程序源代码：
#define N 5
    struct student
{
    char num[6];
    char name[8];
    int score[4];
} stu[N];
input(stu) struct student stu[];
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        printf("\n please input %d of %d\n", i + 1, N);
        printf("num: ");
        scanf("%s", stu[i].num);
        printf("name: ");
        scanf("%s", stu[i].name);
        for (j = 0; j < 3; j++)
        {
            printf("score %d.", j + 1);
            scanf("%d", &stu[i].score[j]);
        }
        printf("\n");
    }
}
print(stu) struct student stu[];
{
    int i, j;
    printf("\nNo. Name Sco1 Sco2 Sco3\n");
    for (i = 0; i < N; i++)
    {
        printf("%-6s%-10s", stu[i].num, stu[i].name);
        for (j = 0; j < 3; j++)
            printf("%-8d", stu[i].score[j]);
        printf("\n");
    }
}
main()
{
    input();
    print();
}

【程序 72 】 题目：创建一个链表。 1.程序分析： 2.程序源代码：
    /*creat a list*/ ＃ i nclude "stdlib.h"
＃ i nclude "stdio.h" struct list
{
    int data;
    struct list *next;
};
typedef struct list node;
typedef node *link;
void main()
{
    link ptr, head;
    int num, i;
    ptr = (link)malloc(sizeof(node));
    ptr = head;
    printf("please input 5 numbers==>\n");
    for (i = 0; i <= 4; i++)
    {
        scanf("%d", &num);
        ptr->data = num;
        ptr->next = (link)malloc(sizeof(node));
        if (i == 4)
            ptr->next = NULL;
        else
            ptr = ptr->next;
    }
    ptr = head;
    while (ptr != NULL)
    {
        printf("The value is ==>%d\n", ptr->data);
        ptr = ptr->next;
    }
}

【程序 73 】 题目：反向输出一个链表。 1.程序分析： 2.程序源代码：
    /*reverse output a list*/ ＃ i nclude "stdlib.h"
＃ i nclude "stdio.h" struct list
{
    int data;
    struct list *next;
};
typedef struct list node;
typedef node *link;
void main()
{
    link ptr, head, tail;
    int num, i;
    tail = (link)malloc(sizeof(node));
    tail->next = NULL;
    ptr = tail;
    printf("\nplease input 5 data==>\n");
    for (i = 0; i <= 4; i++)
    {
        scanf("%d", &num);
        ptr->data = num;
        head = (link)malloc(sizeof(node));
        head->next = ptr;
        ptr = head;
    }
    ptr = ptr->next;
    while (ptr != NULL)
    {
        printf("The value is ==>%d\n", ptr->data);
        ptr = ptr->next;
    }
}

【程序 74 】 题目：连接两个链表。 1.程序分析： 2.程序源代码：
＃ i nclude "stdlib.h"
＃ i nclude "stdio.h" struct list
{
    int data;
    struct list *next;
};
typedef struct list node;
typedef node *link;
link delete_node(link pointer, link tmp)
{
    if (tmp == NULL) /*delete first node*/
        return pointer->next;
    else
    {
        if (tmp->next->next == NULL) /*delete last node*/
            tmp->next = NULL;
        else /*delete the other node*/
            tmp->next = tmp->next->next;
        return pointer;
    }
}
void selection_sort(link pointer, int num)
{
    link tmp, btmp;
    int i, min;
    for (i = 0; i < num; i++)
    {
        tmp = pointer;
        min = tmp->data;
        btmp = NULL;
        while (tmp->next)
        {
            if (min > tmp->next->data)
            {
                min = tmp->next->data;
                btmp = tmp;
            }
            tmp = tmp->next;
        }
        printf("\40: %d\n", min);
        pointer = delete_node(pointer, btmp);
    }
}
link create_list(int array[], int num)
{
    link tmp1, tmp2, pointer;
    int i;
    pointer = (link)malloc(sizeof(node));
    pointer->data = array[0];
    tmp1 = pointer;
    for (i = 1; i < num; i++)
    {
        tmp2 = (link)malloc(sizeof(node));
        tmp2->next = NULL;
        tmp2->data = array[i];
        tmp1->next = tmp2;
        tmp1 = tmp1->next;
    }
    return pointer;
}
link concatenate(link pointer1, link pointer2)
{
    link tmp;
    tmp = pointer1;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = pointer2;
    return pointer1;
}
void main(void)
{
    int arr1[] = {3, 12, 8, 9, 11};
    link ptr;
    ptr = create_list(arr1, 5);
    selection_sort(ptr, 5);
}
【程序 75 】 题目：放松一下，算一道简单的题目。 1.程序分析： 2.程序源代码： main()
{
    int i, n;
    for (i = 1; i < 5; i++)
    {
        n = 0;
        if (i != 1)
            n = n + 1;
        if (i == 3)
            n = n + 1;
        if (i == 4)
            n = n + 1;
        if (i != 4)
            n = n + 1;
        if (n == 3)
            printf("zhu hao shi de shi:%c", 64 + i);
    }
}

【程序 76 】 题目：编写一个函数，输入 n 为偶数时，调用函数求 1 / 2 + 1 / 4 + ... + 1 / n, 当输入 n 为奇数时，调用函数 1 / 1 + 1 / 3 + ... + 1 / n(利用指针函数) 1.程序分析： 2.程序源代码： main()
＃ i nclude "stdio.h" main()
{
    float peven(), podd(), dcall();
    float sum;
    int n;
    while (1)
    {
        scanf("%d", &n);
        if (n > 1)
            break;
    }
    if (n % 2 == 0)
    {
        printf("Even=");
        sum = dcall(peven, n);
    }
    else
    {
        printf("Odd=");
        sum = dcall(podd, n);
    }
    printf("%f", sum);
}
float peven(int n)
{
    float s;
    int i;
    s = 1;
    for (i = 2; i <= n; i += 2)
        s += 1 / (float)i;
    return (s);
}
float podd(n)
int n;
{
    float s;
    int i;
    s = 0;
    for (i = 1; i <= n; i += 2)
        s += 1 / (float)i;
    return (s);
}
float dcall(fp, n) float (*fp)();
int n;
{
    float s;
    s = (*fp)(n);
    return (s);
}

【程序 77 】 题目：填空练习（指向指针的指针） 1.程序分析： 2.程序源代码： main()
{
    char *s[] = {"man", "woman", "girl", "boy", "sister"};
    char **q;
    int k;
    for (k = 0; k < 5; k++)
    {
        ; /*这里填写什么语句 */
        printf("%s\n", *q);
    }
}

【程序 78 】 题目：找到年龄最大的人，并输出。请找出程序中有什么问题。 1.程序分析： 2.程序源代码：
#define N 4
＃ i nclude "stdio.h" static struct man
{
    char name[20];
    int age;
} person[N] = {"li", 18, "wang", 19, "zhang", 20, "sun", 22};
main()
{
    struct man *q, *p;
    int i, m = 0;
    p = person;
    for (i = 0; i < N; i++)
    {
        if (m < p->age)
            q = p++;
        m = q->age;
    }
    printf("%s,%d", (*q).name, (*q).age);
}

【程序 79 】 题目：字符串排序。 1.程序分析： 2.程序源代码： main()
{
    char *str1[20], *str2[20], *str3[20];
    char swap();
    printf("please input three strings\n");
    scanf("%s", str1);
    scanf("%s", str2);
    scanf("%s", str3);
    if (strcmp(str1, str2) > 0)
        swap(str1, str2);
    if (strcmp(str1, str3) > 0)
        swap(str1, str3);
    if (strcmp(str2, str3) > 0)
        swap(str2, str3);
    printf("after being sorted\n");
    printf("%s\n%s\n%s\n", str1, str2, str3);
}
char swap(p1, p2)
char *p1, *p2;
{
    char *p[20];
    strcpy(p, p1);
    strcpy(p1, p2);
    strcpy(p2, p);
}
每天都要 C 语言程序实例 100 个<4>
【程序 80 】 题目：海滩上有一堆桃子，五只猴子来分。第一只猴子把这堆桃子凭据分为五份，多了一个，这只猴子把
    多的一个扔入海中，拿走了一份。第二只猴子把剩下的桃子又平均分成五份，又多了一个，它同样把多的
        一个扔入海中，拿走了一份，第三、第四、第五只猴子都是这样做的，问海滩上原来最少有多少个桃子？ 1.程序分析： 2.程序源代码： main()
{
    int i, m, j, k, count;
    for (i = 4; i < 10000; i += 4)
    {
        count = 0;
        m = i;
        for (k = 0; k < 5; k++)
        {
            j = i / 4 * 5 + 1;
            i = j;
            if (j % 4 == 0)
                count++;
            else
                break;
        }
        i = m;
        if (count == 4)
        {
            printf("%d\n", count);
            break;
        }
    }
}
【程序 81 】 题目： 809 *? ? = 800 * ? ? +9 * ? ? +1 其中 ? ? 代表的两位数, 8 * ? ? 的结果为两位数， 9 * ? ? 的结果为 3 位数。求 ? ? 代表的两位数，及 809 * ? ? 后的结果。 1.程序分析： 2.程序源代码： output(long b, long i)
{
    printf("\n%ld/%ld=809*%ld+%ld", b, i, i, b % i);
}
main()
{
    long int a, b, i;
    a = 809;
    for (i = 10; i < 100; i++)
    {
        b = i * a + 1;
        if (b >= 1000 && b <= 10000 && 8 * i < 100 && 9 * i >= 100)
            output(b, i);
    }
}

【程序 82 】 题目：八进制转换为十进制 1.程序分析： 2.程序源代码： main()
{
    char *p, s[6];
    int n;
    p = s;
    gets(p);
    n = 0;
    while (*(p) != '\0')
    {
        n = n * 8 + *p - '0';
        p++;
    }
    printf("%d", n);
}

【程序 83 】 题目：求 0 — 7 所能组成的奇数个数。 1.程序分析： 2.程序源代码： main()
{
    long sum = 4, s = 4;
    int j;
    for (j = 2; j <= 8; j++) /*j is place of number*/
    {
        printf("\n%ld", sum);
        if (j <= 2)
            s *= 7;
        else
            s *= 8;
        sum += s;
    }
    printf("\nsum=%ld", sum);
}

【程序 84 】 题目：一个偶数总能表示为两个素数之和。 1.程序分析： 2.程序源代码：
＃ i nclude "stdio.h"
＃ i nclude "math.h" main()
{
    int a, b, c, d;
    scanf("%d", &a);
    for (b = 3; b <= a / 2; b += 2)
    {
        for (c = 2; c <= sqrt(b); c++)
            if (b % c == 0)
                break;
        if (c > sqrt(b))
            d = a - b;
        else
            break;
        for (c = 2; c <= sqrt(d); c++)
            if (d % c == 0)
                break;
        if (c > sqrt(d))
            printf("%d=%d+%d\n", a, b, d);
    }
}

【程序 85 】 题目：判断一个素数能被几个 9 整除 1.程序分析： 2.程序源代码： main()
{
    long int m9 = 9, sum = 9;
    int zi, n1 = 1, c9 = 1;
    scanf("%d", &zi);
    while (n1 != 0)
    {
        if (!(sum % zi))
            n1 = 0;
        else
        {
            m9 = m9 * 10;
            sum = sum + m9;
            c9++;
        }
    }
    printf("%ld,can be divided by %d \"9\"", sum, c9);
}

【程序 86 】 题目：两个字符串连接程序 1.程序分析： 2.程序源代码：
＃ i nclude "stdio.h" main()
{
    char a[] = "acegikm";
    char b[] = "bdfhjlnpq";
    char c[80], *p;
    int i = 0, j = 0, k = 0;
    while (a[i] != '\0' && b[j] != '\0')
    {if (a[i] {
            c[k] = a[i];
            i++;}
else
c[k]=b[j++];
k++;
    }
    c[k] = '\0';
    if (a[i] == '\0')
        p = b + j;
    else
        p = a + i;
    strcat(c, p);
    puts(c);
}

【程序 87 】 题目：回答结果（结构体变量传递） 1.程序分析： 2.程序源代码：
＃ i nclude "stdio.h" struct student
{
    int x;
    char c;
} a;
main()
{
    a.x = 3;
    a.c = 'a';
    f(a);
    printf("%d,%c", a.x, a.c);
}
f(struct student b)
{
    b.x = 20;
    b.c = 'y';
}

【程序 88 】 题目：读取 7 个数（ 1 — 50 ）的整数值，每读取一个值，程序打印出该值个数的＊。 1.程序分析： 2.程序源代码： main()
{
    int i, a, n = 1;
    while (n <= 7)
    {
        do
        {
            scanf("%d", &a);
        } while (a < 1 || a > 50);
        for (i = 1; i <= a; i++)
            printf("*");
        printf("\n");
        n++;
    }
    getch();
}

【程序 89 】 题目：某个公司采用公用电话传递数据，数据是四位的整数，在传递过程中是加密的，加密规则如下：每
    位数字都加上 5,
    然后用和除以 10 的余数代替该数字，再将第一位和第四位交换，第二位和第三位交换。 1.程序分析： 2.程序源代码： main()
{
    int a, i, aa[4], t;
    scanf("%d", &a);
    aa[0] = a % 10;
    aa[1] = a % 100 / 10;
    aa[2] = a % 1000 / 100;
    aa[3] = a / 1000;
    for (i = 0; i <= 3; i++)
    {
        aa[i] += 5;
        aa[i] %= 10;
    }
    for (i = 0; i <= 3 / 2; i++)
    {
        t = aa[i];
        aa[i] = aa[3 - i];
        aa[3 - i] = t;
    }
    for (i = 3; i >= 0; i--)
        printf("%d", aa[i]);
}

【程序 90 】 题目：专升本一题，读结果。 1.程序分析： 2.程序源代码：
＃ i nclude "stdio.h"
#define M 5
    main()
{
    int a[M] = {1, 2, 3, 4, 5};
    int i, j, t;
    i = 0;
    j = M - 1;
while(i {
        t = *(a + i);
        *(a + i) = *(a + j);
        *(a + j) = t;
        i++;
        j--;
}
for(i=0;i printf("%d",*(a+i));
}
【程序 91 】 题目：时间函数举例 1 1.程序分析： 2.程序源代码：
＃ i nclude "stdio.h"
＃ i nclude "time.h" void main()
{
    time_t lt;       /*define a longint time varible*/
    lt = time(NULL); /*system time and date*/
    printf(ctime(<));
    /*english format output*/ printf(asctime(localtime(<))); /*tranfer to tm*/
    printf(asctime(gmtime(<)));                              /*tranfer
to Greenwich time*/
}

【程序 92 】 题目：时间函数举例 2 1.程序分析： 2.程序源代码：
    /*calculate time*/ ＃ i nclude "time.h"
＃ i nclude "stdio.h" main()
{
    time_t start, end;
    int i;
    start = time(NULL);
    for (i = 0; i < 3000; i++)
    {
        printf("\1\1\1\1\1\1\1\1\1\1\n");
    }
    end = time(NULL);
    printf("\1: The different is %6.3f\n", difftime(end, start));
}

【程序 93 】 题目：时间函数举例 3 1.程序分析： 2.程序源代码：
    /*calculate time*/ ＃ i nclude "time.h"
＃ i nclude "stdio.h" main()
{
    clock_t start, end;
    int i;
    double var;
    start = clock();
    for (i = 0; i < 10000; i++)
    {
        printf("\1\1\1\1\1\1\1\1\1\1\n");
    }
    end = clock();
    printf("\1: The different is %6.3f\n", (double)(end - start));
}

【程序 94 】 题目：时间函数举例 4, 一个猜数游戏，判断一个人反应快慢。 1.程序分析： 2.程序源代码：
＃ i nclude "time.h"
＃ i nclude "stdlib.h"
＃ i nclude "stdio.h" main()
{
    char c;
    clock_t start, end;
    time_t a, b;
    double var;
    int i, guess;
    srand(time(NULL));
    printf("do you want to play it.('y' or 'n') \n");
loop:
    while ((c = getchar()) == 'y')
    {
        i = rand() % 100;
        printf("\nplease input number you guess:\n");
        start = clock();
        a = time(NULL);
        scanf("%d", &guess);
        while (guess != i)
        {
            if (guess > i)
            {
                printf("please input a little smaller.\n");
                scanf("%d", &guess);
            }
            else
            {
                printf("please input a little bigger.\n");
                scanf("%d", &guess);
            }
        }
        end = clock();
        b = time(NULL);
        printf("\1: It took you %6.3f seconds\n", var = (double)(end - start) / 18.2);
        printf("\1: it took you %6.3f seconds\n\n", difftime(b, a));
        if (var < 15)
            printf("\1\1 You are very clever! \1\1\n\n");
        else if (var < 25)
            printf("\1\1 you are normal! \1\1\n\n");
        else
            printf("\1\1 you are stupid! \1\1\n\n");
        printf("\1\1 Congradulations \1\1\n\n");
        printf("The number you guess is %d", i);
    }
    printf("\ndo you want to try it again?(\"yy\".or.\"n\")\n");
    if ((c = getch()) == 'y')
        goto loop;
}

【程序 95 】 题目：家庭财务管理小程序 1.程序分析： 2.程序源代码：
    /*money management system*/ ＃ i nclude "stdio.h"
＃ i nclude "dos.h" main()
{
    FILE *fp;
    struct date d;
    float sum, chm = 0.0;
    int len, i, j = 0;
    int c;
    char ch[4] = "", ch1[16] = "", chtime[12] = "", chshop[16], chmoney[8];
pp:
    clrscr();
    sum = 0.0;
    gotoxy(1, 1);
    printf("|---------------------------------------------------------------------------|");
    gotoxy(1, 2);
    printf("| money management system(C1.0) 2000.03 |");
    gotoxy(1, 3);
    printf("|---------------------------------------------------------------------------|");
    gotoxy(1, 4);
    printf("| -- money records -- | -- today cost list -- |");
    gotoxy(1, 5);
    printf("| ------------------------ |-------------------------------------|");
    gotoxy(1, 6);
    printf("| date: -------------- | |");
    gotoxy(1, 7);
    printf("| | | | |");
    gotoxy(1, 8);
    printf("| -------------- | |");
    gotoxy(1, 9);
    printf("| thgs: ------------------ | |");
    gotoxy(1, 10);
    printf("| | | | |");
    gotoxy(1, 11);
    printf("| ------------------ | |");
    gotoxy(1, 12);
    printf("| cost: ---------- | |");
    gotoxy(1, 13);
    printf("| | | | |");
    gotoxy(1, 14);
    printf("| ---------- | |");
    gotoxy(1, 15);
    printf("| | |");
    gotoxy(1, 16);
    printf("| | |");
    gotoxy(1, 17);
    printf("| | |");
    gotoxy(1, 18);
    printf("| | |");
    gotoxy(1, 19);
    printf("| | |");
    gotoxy(1, 20);
    printf("| | |");
    gotoxy(1, 21);
    printf("| | |");
    gotoxy(1, 22);
    printf("| | |");
    gotoxy(1, 23);
    printf("|---------------------------------------------------------------------------|");
    i = 0;
    getdate(&d);
    sprintf(chtime, "%4d.%02d.%02d", d.da_year, d.da_mon, d.da_day);
    for (;;)
    {
        gotoxy(3, 24);
        printf(" Tab __browse cost list Esc __quit");
        gotoxy(13, 10);
        printf(" ");
        gotoxy(13, 13);
        printf(" ");
        gotoxy(13, 7);
        printf("%s", chtime);
        j = 18;
        ch[0] = getch();
        if (ch[0] == 27)
            break;
        strcpy(chshop, "");
        strcpy(chmoney, "");
        if (ch[0] == 9)
        {
        mm:
            i = 0;
            fp = fopen("home.dat", "r+");
            gotoxy(3, 24);
            printf(" ");
            gotoxy(6, 4);
            printf(" list records ");
            gotoxy(1, 5);
            printf("|-------------------------------------|");
            gotoxy(41, 4);
            printf(" ");
            gotoxy(41, 5);
            printf(" |");
            while (fscanf(fp, "%10s%14s%f\n", chtime, chshop, &chm) != EOF)
            {
                if (i == 36)
                {
                    getch();
                    i = 0;
                }
                if ((i % 36) < 17)
                {
                    gotoxy(4, 6 + i);
                    printf(" ");
                    gotoxy(4, 6 + i);
                }
                else if ((i % 36) > 16)
                {
                    gotoxy(41, 4 + i - 17);
                    printf(" ");
                    gotoxy(42, 4 + i - 17);
                }
                i++;
                sum = sum + chm;
                printf("%10s %-14s %6.1f\n", chtime, chshop, chm);
            }
            gotoxy(1, 23);
            printf("|---------------------------------------------------------------------------|");
            gotoxy(1, 24);
            printf("| |");
            gotoxy(1, 25);
            printf("|---------------------------------------------------------------------------|");
            gotoxy(10, 24);
            printf("total is %8.1f$", sum);
            fclose(fp);
            gotoxy(49, 24);
            printf("press any key to.....");
            getch();
            goto pp;
        }
        else
        {
            while (ch[0] != '\r')
            {
                if (j < 10)
                {
                    strncat(chtime, ch, 1);
                    j++;
                }
                if (ch[0] == 8)
                {
                    len = strlen(chtime) - 1;
                    if (j > 15)
                    {
                        len = len + 1;
                        j = 11;
                    }
                    strcpy(ch1, "");
                    j = j - 2;
                    strncat(ch1, chtime, len);
                    strcpy(chtime, "");
                    strncat(chtime, ch1, len - 1);
                    gotoxy(13, 7);
                    printf(" ");
                }
                gotoxy(13, 7);
                printf("%s", chtime);
                ch[0] = getch();
                if (ch[0] == 9)
                    goto mm;
                if (ch[0] == 27)
                    exit(1);
            }
            gotoxy(3, 24);
            printf(" ");
            gotoxy(13, 10);
            j = 0;
            ch[0] = getch();
            while (ch[0] != '\r')
            {
                if (j < 14)
                {
                    strncat(chshop, ch, 1);
                    j++;
                }
                if (ch[0] == 8)
                {
                    len = strlen(chshop) - 1;
                    strcpy(ch1, "");
                    j = j - 2;
                    strncat(ch1, chshop, len);
                    strcpy(chshop, "");
                    strncat(chshop, ch1, len - 1);
                    gotoxy(13, 10);
                    printf(" ");
                }
                gotoxy(13, 10);
                printf("%s", chshop);
                ch[0] = getch();
            }
            gotoxy(13, 13);
            j = 0;
            ch[0] = getch();
            while (ch[0] != '\r')
            {
                if (j < 6)
                {
                    strncat(chmoney, ch, 1);
                    j++;
                }
                if (ch[0] == 8)
                {
                    len = strlen(chmoney) - 1;
                    strcpy(ch1, "");
                    j = j - 2;
                    strncat(ch1, chmoney, len);
                    strcpy(chmoney, "");
                    strncat(chmoney, ch1, len - 1);
                    gotoxy(13, 13);
                    printf(" ");
                }
                gotoxy(13, 13);
                printf("%s", chmoney);
                ch[0] = getch();
            }
            if ((strlen(chshop) == 0) || (strlen(chmoney) == 0))
                continue;
            if ((fp = fopen("home.dat", "a+")) != NULL)
                ;
            fprintf(fp, "%10s%14s%6s", chtime, chshop, chmoney);
            fputc('\n', fp);
            fclose(fp);
            i++;
            gotoxy(41, 5 + i);
            printf("%10s %-14s %-6s", chtime, chshop, chmoney);
        }
    }
}

【程序 96 】 题目：计算字符串中子串出现的次数 1.程序分析： 2.程序源代码：
＃ i nclude "string.h"
＃ i nclude "stdio.h" main()
{
    char str1[20], str2[20], *p1, *p2;
    int sum = 0;
    printf("please input two strings\n");
    scanf("%s%s", str1, str2);
    p1 = str1;
    p2 = str2;
    while (*p1 != '\0')
    {
