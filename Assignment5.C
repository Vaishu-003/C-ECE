SCHEDULI.C
/* JOB/PROCESS SCHEDULING ALGORITHM*/
struct						//struct representing process
{
	int p,b,q,a,turn,wait;			//p-priority, b-bust, a-arrival
}proc[40],temp;					//turn-turn time, wait time
int n,i,j,k;
void interchange (int i)			//function to interchange process
{
	temp=proc[i];
	proc[i]=proc[i+1];
	proc[i+1]=temp;
}
void input()
{
	clrscr();
	printf("JOB SCHEDULING ALGORITHMS\n");
	printf("\nEnter No. of processes");
	scanf("%d",&n);
	for (i=0;i<n;i++)
	{
		printf("\nEnter following parameter for P%d",i+1);
		printf("\n Burst time  =");
		scanf("%d",&proc[i].b);
		printf("\n Priority    =");
		scanf("%d",&proc[i].p);
		printf("\n Arrival time=");
		scanf("%d",&proc[i].a);
		proc[i].q=i+1;
	}
}
void output()
{
	int sum;
	float ta=0,wa=0;
	sum=proc[0].a;
	for(i=0;i<n;i++)
	{		//loop to calculate total turnaround and waiting time
		proc[i].wait=sum-proc[i].a;
		sum+=proc[i].b;
		proc[i].turn=sum-proc[i].a;
		ta+=proc[i].turn;
		wa+=proc[i].wait;
	}
	ta=ta/n;
	wa=wa/n;
	printf("\nProcess\tBusttime\tPriority\tArrival time\tTurnaround\tWaiting");
	for (j=0;j<=n;j++)
		for(i=0;i<n;i++)
			if(proc[i].q==j)
				printf("\np%d\t%8d%18d%13d%17d%13d",j,proc[i].b,proc[i].p,proc[i].a,proc[i].turn,proc[i].wait);
				printf("\nAverage turn around time is %f",ta);
				printf("\nAverage waiting time is %f",wa);
				getch();
}
void ps()
{				//function for priority scheduling
	for(i=0;i<n-1;i++)
		for(j=0;j<n-1;j++)
			{
			if(proc[j].p>proc[j+1].p)
				interchange(j);		//simple bubble sort logic
			if(proc[j].p==proc[j+1].p)
				if(proc[j].b>proc[j+1].b)
					interchange(j);
			}
	printf("\n RESULT WITH PRIORITY SCHEDULING\n");
	output();
}
void fcfs()
{					//function for FIFO scheduling
	for(i=0;i<n;i++)
		for(j=0;j<n-1;j++)
		   {
			if(proc[j].a>proc[j+1].a)
				interchange(j); 		//simple bubble sort logic
			if(proc[j].a==proc[j+1].a)
				if(proc[j].p<proc[j+1].p)
					interchange(j);
			}
	printf("\n RESULT WITH FCFS SCHEDULING\n");
	output();
}
void sjf()
{					//function for shortest Job first
	for(i=0;i<n;i++)
		for(j=0;j<n-1;j++)
		   {
			if(proc[j].b>proc[j+1].b)
				interchange(j); 		//simple bubble sort logic
			if(proc[j].b==proc[j+1].b)
				if(proc[j].p<proc[j+1].p)
					interchange(j);
			}
	printf("\n RESULT WITH SJF SCHEDULING\n");
	output();
}
void rr()
{					//function for round robin scheduling
int temp1[40],total=0;
float ta=0,wa=0;
printf("RESULT WITH ROUND ROBIN SCHEDULING\nQuantum time= unity\narrival time ignored\nsequence is");
for(i=0;i<n;i++)
	{
	temp1[i]=proc[i].b;		//reserve/copy value of proc.b
	total+=proc[i].b;    		//total time
	}
for(j=0;j<total;j++) 			//total iterations
{
	for(i=0;i<n;i++)			// repetition of iteration
	if(temp1[i]!=0)			//check if process completed its task
	{
	 printf("|%d|",i);		//slot allotted to process
		for(k=0;k<n;k++)		//loop increment wait & turnaround time
			if(temp1[k]!=0)
			{
				proc[k].turn++;
				proc[k].wait++;
			}
	 temp1[i]--;			//slot utilized by process
	 proc[i].wait--;
	}
}
	printf("\nProcess\tBusttime\tPriority\tArrival time\tTurnaround\tWaiting");
	for (j=0;j<=n;j++)
		for(i=0;i<n;i++)
			if(proc[i].q==j)
			{  		//loop to print output and calculate ta & wa
	printf("\np%d\t%8d%18d%13d%17d%13d" ,j,proc[i].b,proc[i].p,proc[i].a,proc[i].turn,proc[i].wait);
			   ta+=proc[i].turn;
				wa+=proc[i].wait;
				proc[i].turn=0;
			   proc[i].wait=0;
				}
				printf("\nAverage turn arroundtime is %f",ta/n);
				printf("\nAverage waiting time is %f",wa/n);
				getch();
}
void main()
{
	input();
	ps();
	fcfs();
	sjf();
	rr();
}
