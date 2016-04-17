/*************************************************************************
	> File Name: produce_random.c
	> Author: WangBin
	> Mail: gkwangbin@126.com 
	> Created Time: 2016年04月09日 星期六 16时14分37秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define COUNT 1000000

int main(void)
{
	int i;
	
	FILE *fp;

	srand((unsigned)time(NULL));

	if((fp=fopen("rand_num.txt","w+")) == NULL)
	{
		printf("Can't open file\n");
		exit(1);
	}
	
	for(i = 0; i < COUNT; i++)
	{
		fprintf(fp,"%d ",rand()%2000000);
	}
	
	fclose(fp);
	return 0;
}
