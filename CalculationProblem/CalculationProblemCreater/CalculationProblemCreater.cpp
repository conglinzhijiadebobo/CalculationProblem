// CalculationProblemCreater.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

int RB = 0, LB = 0;					//左右括号数量，只作用本文件

int main(int argc, char *argv[])
{
	//srand((unsigned)time(NULL));
	int t = 0;
	int r = 50;
	int Count = 500;		//题目数量
	char *calproblem;
	char p[10];				//$位数随着最大题数变化
	FILE *fp;
	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "-r"))
		{
			r = atoi(argv[i + 1]);
		}
		if (!strcmp(argv[i], "-n"))
		{
			Count = atoi(argv[i + 1]);
		}
	}


	if ((fp = fopen("Question.txt", "wb")) == NULL)
	{
		printf("cannot open file\n");
		return 0;
	}
	for (; t < Count; t++) {
		int num = Creater(r);
		calproblem = CalProblem(num);
		_itoa(t+1, p, 10);
		strcat(p, ".\t");
		printf("%d. biaodashi: %s\n", t+1,calproblem);
		printf("  Varnum: %d\n", num);
		if (fwrite(p, strlen(p), 1, fp) != 1)
			printf("write error\n");
		if (fwrite(calproblem, strlen(calproblem), 1, fp) != 1)
			printf("write error\n");
		if (fputs("=", fp) != 1)
			 printf("writennnnnnnnn error\n");
		if (fputs("\r\n",fp) != 1)
			printf("writennnnnnnnn error\n");
		memset(calproblem, 0, sizeof(calproblem));
		//free(calproblem);
	}
	fclose(fp);
	//free(calproblem);
	
	getchar();
	return 0;
}

