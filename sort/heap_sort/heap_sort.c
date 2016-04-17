/*************************************************************************
	> File Name: heap_sort.c
	> Author: WangBin
	> Mail: gkwangbin@126.com 
	> Created Time: 2016年04月09日 星期六 18时08分22秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

/*正常的堆是从数组１开始的，数组0位置放置一个标记，方便堆操作
 * 在堆排序中，输入序列为正常的数组，所以需要对孩子的位置做特殊处理*/
#define left_child(i) (2 * (i) + 1)

#define NUM_COUNT 900000

/*下滤的操作，一次只处理一个从上层传递过来的节点，在该节点到叶节点的
 * 路径上进行下滤的操作，将较小的节点向着较大的孩子节点的路径走一步，
 * 走到父节点不小于孩子节点时候停止。
 * 功能：应用与建堆*/
void percolate_down(int arr[], int i, int count)
{
	int child, tmp;

	for(tmp = arr[i]; left_child(i) < count; i = child)
	{
		child = left_child(i);
		/*很巧妙的使用一次比较，得出较大孩子的位置*/
		if(child != count-1 && arr[child + 1] > arr[child])
		{
			child++;
		}
		if(tmp < arr[child])
		{
			/*将较大的孩子换到父亲的位置*/
			arr[i] = arr[child];
		}
		else
		{
			break;
		}
	}
	arr[i] = tmp;
}

void swap(int *a, int *b)
{
	int tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}

/*使用一个数组进行堆排序*/
void heap_sort(int arr[], int count)
{
	int i;
	int tmp;

	/*建大顶堆*/
	for(i = count / 2; i >= 0; i--)
	{
		percolate_down(arr, i, count);
	}
	
	/*将大顶堆根上元素放在数组最后，堆尺寸减一*/
	for(i = count - 1; i > 0; i--)
	{
		swap(&arr[0], &arr[i]);	
		percolate_down(arr, 0, i);
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
	heap_sort(arr,count);
	gettimeofday(&end, NULL);

	used_time = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("The heap sort time: %d us\n",used_time);

	for(i = 0; i < count; i++)
	{
		fprintf(out_file, "%d ", arr[i]);
	}

	fclose(in_file);
	fclose(out_file);
	return 0;
}
