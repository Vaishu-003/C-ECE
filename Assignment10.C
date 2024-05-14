DISK.C
// C++ program to demonstrate
// FCFS Disk Scheduling algorithm
#include <stdio.h>
#include <math.h>

int size = 8;
int i;
void FCFS(int arr[],int head)
{
	int seek_count = 0;
	int cur_track, distance;

	for(i=0;i<size;i++)
	{
		cur_track = arr[i];
	
		// calculate absolute distance
		distance = fabs(head - cur_track);
	
		// increase the total count
		seek_count += distance;
	
		// accessed track is now new head
		head = cur_track;
	}

	printf("Total number of seek operations: %d\n",seek_count);
	
	// Seek sequence would be the same
	// as request array sequence
	printf("Seek Sequence is\n");

	for (i = 0; i < size; i++) {
		printf("%d\n",arr[i]);
	}
}

//Driver code
int main()
{
	// request array
	int arr[8] = { 176, 79, 34, 60, 92, 11, 41, 114 };
	int head = 50;

	FCFS(arr,head);

	getch();
	return 0;
}

//This code is contributed by Pratham Kashyap