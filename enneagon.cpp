#include <stdio.h>
#include <stdlib.h>

// https://www.zhihu.com/question/46235037
/**
 * N芒星N个顶点,如果能找到一个数值k(k>1),每次跳过k个顶点,如果N次之后能将所有的顶点遍历,则判断可以一笔画出.
 * */

bool EnneagonTest(unsigned int n)
{
    if (n < 4)
    {
        return false;
    }

    bool rst = false;
    bool *arr = new bool[n];
    printf("Enneagon %d:", n);
    for (unsigned int k = 2; k <= n / 2; k++)
    {
        memset(arr, 0, n * sizeof(bool));
        unsigned int t = 0;
        for (unsigned int i = 0; i < n; i++)
        {
            arr[t] = true;
            t = (t + k) % n;
        }

        bool can = true;
        for (unsigned int i = 0; i < n; i++)
        {
            if (!arr[i])
            {
                can = false;
                break;
            }
        }

        if (can)
        {
            printf("%d ", k);
            rst = true;
        }
    }

    if (!rst)
    {
        printf("Can not");
    }

    printf("\r\n");
    delete[] arr;

    return rst;
}