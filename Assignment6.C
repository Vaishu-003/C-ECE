BANKER.C
int Pmax[3],avl,avltemp,maxres,running[3],i,j,safe=0, Pcurr[3]; 
					//max of 3 processes, 1 resources
main()
{
for(i=0;i<3;i++)
	running[i]=1;	 //set all the processes to running=1
clrscr();
input();
while(1) 			//loop forever untill all processes completed
{	clrscr();
	if(!(running[0]+running[1]+running[2]))
	{			//check for completion of all precesses
		printf("\n\n\n\n\nCongratulations! Execution of all processes completed successfully without any deadlock!");
		getch();
		break;
	}
	Else				//else check for deadlock
	{	printf("\nDeadlock Prevention using Banker's Algorithm:\n");
		viewresources();
		requestresource();
		getch();
	}
}
}
void input()
{			//accept parameters of resource and process from user
	printf("Enter maximum resources");
	scanf("%d",&maxres);
	for(i=0;i<3;i++)
	{
		 printf("\nEnter maximum resource required for P%d\n",i+1);
		 scanf("%d",&Pmax[i]);
	 	printf("\nEnter resources currently engaged by P%d\n",i+1);
		 scanf("%d",&Pcurr[i]);
	}
	avl=maxres-(Pcurr[0]+Pcurr[1]+Pcurr[2]);
}
	/* this routine mimics an OS resource request which basically checks if a resource is busy, if not gives it to your process, and then marks it busy. If it is busy to begin with some. strategy is used to deny the request based on Bankers algorithm/formula. if the request cannot be done due to deadlock possibility. if  the processes cannot complete because of lack of resources, then running them one at a time.*/

void requestresource()
{
//check if it is allocated, will it go to deadlock
	int proc,req;
	printf("\nFor which Process, you need resources?(1-3):\n");
	scanf("%d",&proc);
	proc--;
	if(running[proc])
	{		//check for running processes only
printf("\nCurrently P%d needs %d resource:",proc+1,Pmax[proc]-Pcurr[proc]);
		loop_3:
  printf("\nEnter no. of Resources to Allocate to Process %d:\n",proc+1);
		scanf("%d",&req);
		if((req>(Pmax[proc]-Pcurr[proc]))||(req>avl))
		{	//resources should be less than available and required. 
			printf("\nInvalid Value!, try again!");
			goto loop_3;
		}
		Pcurr[proc]+=req;		//alloted
		avl-=req;
		if(checksafe())		//check if allocation is safe or not
		{
			printf("\nResources successfully allocated.\n");
			if(checkcompletion(proc))  //wait till completion
       printf("\nProcess %d has completed its execution and its resources have been released.\n",proc+1);
		}
		else
		{			// if not safe withdrew allotted resources 
			Pcurr[proc]-=req;
			avl+=req;
  printf("\nResouces cannot be allocated as it may lead to Deadlock!\n");
		}
	}
	else
	{	printf("\nInvalid Process no.\n");
		getch();
	}
}
int checkcompletion(int proc)
{	// if all requested resources are available, complete execution
	if(Pcurr[proc]==Pmax[proc])
	{
		avl+=Pmax[proc];
		running[proc]=0;
		return 1;
	}
	return 0;
}
viewresources()
{		//function to print the state of the resources for the user.
	printf("Max. resources in the system: %d\n",maxres);
	printf("\nCurrent resources available in the system:%d\n",avl);
	printf("\n\nMax. Resources required for Completion Process\n",);
	for(i=0;i<3;i++)
		if(running[i])
			printf("P%d\t%d\n",i+1,Pmax[i]);
	printf("\n\n Currently allocated resource for process\n");
	for(i=0;i<3;i++)
		if(running[i])
			printf("P%d\t%d\n",i+1,Pcurr[i]);
}
/* Bankers’ algorithm! true or false (safe or unsafe) values used to present if a resource can be allocated to a given process.*/
int checksafe()
{
//Check if atleast one process can get all resources it needs --> Banker's algorithm
	safe=0;
	avltemp=avl;
	for(i=0;i<3;i++)
		if(running[i])
			if(Pmax[i]-Pcurr[i]<=avltemp)
			{
				avltemp+=Pcurr[i];
				safe=1;
			}
	return safe;
}