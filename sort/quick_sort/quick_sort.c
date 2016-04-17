/*************************************************************************
	> File Name: quick_sort.c
	> Author: WangBin
	> Mail: gkwangbin@126.com 
	> Created Time: 2016年04月09日 星期六 18时08分22秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

#define NUM_COUNT 900000
#define CUT_OFF	3

/*交换数组中两元素的位置*/
void swap(int *a, int *b)
{
	int tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}

/*insert sort*/
void insert_sort(int arr[], int count)
{
	int i, pos;
	int tmp;

	for(pos = 1; pos < count; pos++)
	{
		tmp = arr[pos];
		for(i = pos; i > 0 && arr[i - 1] > tmp; i--)
		{
			arr[i] = arr[i - 1];
		}
		arr[i] = tmp;
	}
}

/*找出枢轴，头尾中间三个元素的中位数*/
int median3(int arr[], int left, int right)
{
	int center;

	center = (left + right) / 2;

	if(arr[left] > arr[center])
	{
		swap(&arr[left], &arr[center]);
	}
	if(arr[left] > arr[right])
	{
		swap(&arr[left], &arr[right]);
	}
	if(arr[center] > arr[right])
	{
		swap(&arr[center], &arr[right]);
	}

	swap(&arr[center], &arr[right - 1]);
	return arr[right -1];
}

/*快排的主例程*/
void q_sort(int arr[], int left, int right)
{
	int i, j;
	int pivot;

	if(left + CUT_OFF <= right)
	{
		pivot = median3(arr, left, right);
		i = left;
		j = right - 1;

		while (1)
		{
			while(arr[++i] < pivot){}
			while(arr[--j] > pivot){}
			if(i < j)
			{
				swap(&arr[i], &arr[j]);
			}
			else
			{
				break;
			}
		}
		swap(&arr[i], &arr[right - 1]);

		q_sort(arr, left, i - 1);
		q_sort(arr, i + 1, right);
	}
	/*如果序列小于3,则使用插入排序*/
	else
	{
		insert_sort(arr+left, right - left + 1);
	}
}

/*快排驱动函数*/
int quick_sort(int arr[], int count)
{
	q_sort(arr, 0 , count - 1);
}

/*测试函数*/
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
	quick_sort(arr,count);
	gettimeofday(&end, NULL);

	used_time = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("The quick sort time: %d us\n",used_time);

	for(i = 0; i < count; i++)
	{
		fprintf(out_file, "%d ", arr[i]);
	}

	fclose(in_file);
	fclose(out_file);
	return 0;
}
