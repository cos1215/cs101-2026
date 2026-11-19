#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_SETS 5
#define NUMS 7
#define MAX_NUM 69

static int cmp(const void *a, const void *b)
{
    return *(const int *)a - *(const int *)b;
}

int main(void)
{
    int n = 0;
    int lotto[MAX_SETS][NUMS];
    
    srand((unsigned)time(NULL));
    
    printf("歡迎來到長庚樂透彩購買機台\n");
    do
    {
        printf("請問您要購買幾組樂透彩票:");
        if(scanf("%d" , &n) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            n = 0;
        }
    }
    while (n < 1 || n > MAX_SETS);
    
    for (int i = 0; i < n; i++)
    {
        int used[MAX_NUM + 1] = {0};
        for (int j = 0; j < NUMS; j++)
        {
            int r;
            do
            {
                r = rand() % MAX_NUM + 1;
            }
            while(used[r]);
            used[r] = 1;
            lotto[i][j] = r;
        }
        
        qsort(lotto[i], NUMS - 1, sizeof(int), cmp);
    }
    
    FILE *fp = fopen("lotto.txt", "w");
    if(fp == NULL)
    {
        printf("無法開啟 lotto.txt\n");
        return 1;
    }
    
    time_t now = time(NULL);
    char *t = ctime(&now);
    t[strcspn(t, "\n")] = '\0';
    
    fprintf(fp, "========= lotto649 =========\n");
    fprintf(fp, "= %s =\n", t);
    for(int i = 0; i < MAX_SETS; i++)
    {
        fprintf(fp, "[%d]:" , i + 1);
        for(int j = 0; j < NUMS; j++)
        {
            if(i < n)
                fprintf(fp, " %02d", lotto[i][j]);
            else
                fprintf(fp, " --");
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "========= casie@CGU =========\n");
    fclose(fp);
    
    printf("已為您購買的%d組的樂透組合輸出至lotto.txt\n", n);
    return 0;
}
