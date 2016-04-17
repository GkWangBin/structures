/*************************************************************************
	> File Name: merge_sort.c
	> Author: WangBin
	> Mail: gkwangbin@126.com 
	> Created Time: 2016年04月09日 星期六 18时08分22秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

#define NUM_COUNT 900000

/*使用临时数组将两个序列其合并，并copy到原数组中*/
void merge(int arr[], int tmp_arr[], int left_pos, int right_pos, int right_end)
{
	int i , left_end, num_count, tmp_pos;

	left_end = right_pos - 1;
	num_count = right_end - left_pos + 1;
	tmp_pos = left_pos;

	/*将两个要合并的序列，较小者先放入临时数组中*/
	while(left_pos <= left_end && right_pos <= right_end)
	{
		if(arr[left_pos] <= arr[right_pos])
		{
			tmp_arr[tmp_pos++] = arr[left_pos++];
		}
		else
		{
			tmp_arr[tmp_pos++] = arr[right_pos++];
		}
	}

	while(left_pos <= left_end)
	{
		tmp_arr[tmp_pos++] = arr[left_pos++];
	}
	while(right_pos <= right_end)
	{
		tmp_arr[tmp_pos++] = arr[right_pos++];
	}

	/*把临时数组中的数据copy回原数组*/
	for(i = 0; i < num_count; i++, right_end--)
	{
		arr[right_end] = tmp_arr[right_end];
	}
}

/*递归函数*/
void msort(int arr[], int tmp_arr[], int left, int right)
{
	int center;
	if(left < right)
	{
		center = (left + right) / 2;
		msort(arr, tmp_arr, left, center);
		msort(arr, tmp_arr, center + 1, right);
		merge(arr, tmp_arr, left, center + 1, right);
	}
}

/*驱动函数*/
void merge_sort(int arr[], int count)
{
	int *tmp_arr;

	tmp_arr = (int *)malloc(count * sizeof(int));
	if(tmp_arr != NULL)
	{
		msort(arr, tmp_arr, 0, count-1);
		free(tmp_arr);
	}
	else
	{
		printf("error:alloc tempt array failed\n");
		return;
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
	merge_sort(arr,count);
	gettimeofday(&end, NULL);

	used_time = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("The merge sort time: %d us\n",used_time);

	for(i = 0; i < count; i++)
	{
		fprintf(out_file, "%d ", arr[i]);
	}

	fclose(in_file);
	fclose(out_file);
	return 0;
}
