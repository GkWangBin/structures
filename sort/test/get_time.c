/*************************************************************************
	> File Name: get_time.c
	> Author: WangBin
	> Mail: gkwangbin@126.com 
	> Created Time: 2016年04月09日 星期六 16时46分19秒
 ************************************************************************/

#include<stdio.h>
#include<sys/time.h>
#include<unistd.h>

int main(void)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);
	sleep(3);
	gettimeofday(&end, NULL);

	int timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;

	printf("time: %d us\n",timeuse);
	return 0;
}
