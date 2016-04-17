/*************************************************************************
	> File Name: bubble_sort.c
	> Author: WangBin
	> Mail: gkwangbin@126.com 
	> Created Time: 2016年04月10日 星期日 13时25分54秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

#define NUM_COUNT 100000
#define true 1
#define false 0

void bubble_sort(int arr[], int count)
{
	int i, j, tmp;
	int swap;

	for(i = count-1; i > 0; i--)
	{
		swap = false;
		/*将大数向右冒泡，每次确定一个元素的位置*/
		for(j = 0; j <= i - 1; j++)
		{
			if(arr[j] > arr[j + 1])
			{
				tmp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = tmp;
				swap = true;			
			}
		}
		
		/*序列已经有序的话直接退出*/
		if(!swap)
		{
			break;
		}
	}
}

void pro_bubble_sort(int arr[], int count)
{
	int i, j, max, pos;

	for(i = count - 1; i > 0; i--)
	{
		max = arr[i];
		pos = i;

		for(j = 0; j < i; j++)
		{
			if(max < arr[j])
			{
				max = arr[j];
				pos = j;
			}
		}
		arr[pos] = arr[i];
		arr[i] = max;

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
	pro_bubble_sort(arr,count);
	gettimeofday(&end, NULL);

	used_time = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("The pro bubble sort time: %d us\n",used_time);

	for(i = 0; i < count; i++)
	{
		fprintf(out_file, "%d ", arr[i]);
	}

	fclose(in_file);
	fclose(out_file);
	return 0;
}
