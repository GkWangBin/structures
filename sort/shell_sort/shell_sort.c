/*************************************************************************
	> File Name: insert_sort.c
	> Author: WangBin
	> Mail: gkwangbin@126.com 
	> Created Time: 2016年04月09日 星期六 18时08分22秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

#define NUM_COUNT 900000

void shell_sort(int arr[], int count)
{
	int i, j, increment;
	int tmp;

	for(increment = count / 2; increment > 0; increment /= 2 )
	{
		/*使用插入排序的方式实现希尔排序*/
		for(i = increment; i < count; i++)
		{
			tmp = arr[i];
			for(j = i; j >= increment; j -=increment)
			{
				if(tmp < arr[j - increment])
				{
					arr[j] = arr[j - increment];
				}
				else
				{
					break;
				}
			}
			arr[j] = tmp;
		}
	}
}
int main(void)
{
	int arr[NUM_COUNT] = {0};
	int i, count;

	struct timeval start, end;
	int used_time;
	
	FILE *in_file, *out_file;

	if((in_file = fopen("rand_num.txt","r")) == NULL)
	{
		printf("error:open the input file failed!\n");
		exit(1);
	}
	if((out_file = fopen("sort_num.txt","w+")) == NULL)
	{
		printf("error:open the input file failed!\n");
		exit(1);
	}

	count = NUM_COUNT;

	for(i = 0; i < count; i++)
	{
		fscanf(in_file, "%d", &arr[i]);
	}

	gettimeofday(&start, NULL);
	shell_sort(arr,count);
	gettimeofday(&end, NULL);

	used_time = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("The shell sort time: %d us\n",used_time);

	for(i = 0; i < count; i++)
	{
		fprintf(out_file, "%d ", arr[i]);
	}

	fclose(in_file);
	fclose(out_file);
	return 0;
}
