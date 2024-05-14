BANKER_3_processes.C
//global variables.
int Pcurr[3][3]; 				//max of 3 processes, 3 resources
int Pmax[3][3];
int avl[]={6,4,7};
int avltemp[]={6,4,7};
int maxres[]={6,4,7};
int running[3]; 		//Which processes are running (this appears to be used as a boolean)
int i,j, safe=0,count=0;
main()
{
int ch;
for(i=0;i<3;i++)
	running[i]=1;	 //set all the processes to "running" = true (1)
initresources();
while(1) 			//loop forever
{
	clrscr();		 //calls a command prompt command, this looks like unix clearscreen to manage the output.
	count=0; //extremely excessive logic to determing that you have a process running.
		//should be if(!(running[0]+running[1]+running[2])) to replace 8 lines here
for(i=0;i<3;i++)
{
	if(running[i])
	count++;
}
if(count==0)
{
	printf("\n\n\n\n\nCongratulations! We have completed execution of all processes successfully without any deadlock!");
	getch();
	break;
}
	//end ex	cessive logic section, begin menu section.
	//The following is just a menu for the user to see what is going one at each iteration.
else
{
	printf("\nDeadlock Prevention using Banker's Algorithm:\n");
	viewresources();
	printf("\n1. Request resource(s) for a process\n");
	printf("\n2. View Allocated Resources\n");
	printf("\n3. Exit\n");
	printf("\nEnter your choice:\n");
	scanf("%d",&ch);
	if(ch==1)
	{
		requestresource();
		getch();
	}
	else
		 if(ch==2)
		{	
		viewresources();
		getch();
		}
		else	 if(ch==3)
				break;
			else
				printf("\nInvalid Choice, please try again!\n");
	}
}
getch();
}
	//initialization routine, this defines the current "problem" to be tested.
	//I do not really understand what values go where.
initresources()
{
		//for each process, get curr. requirement and max. requirement->check if max.req...
		Pmax[0][0]=3; Pcurr[0][0]=1; avl[0]=3;
		Pmax[0][1]=3; Pcurr[0][1]=2; avl[1]=1;
		Pmax[0][2]=2; Pcurr[0][2]=2; avl[2]=1;
Pmax[1][0]=1; Pcurr[1][0]=1;
Pmax[1][1]=2; Pcurr[1][1]=0;
Pmax[1][2]=3; Pcurr[1][2]=3;
Pmax[2][0]=1; Pcurr[2][0]=1;
Pmax[2][1]=1; Pcurr[2][1]=1;
Pmax[2][2]=5; Pcurr[2][2]=1;
}
	// this routine mimics an OS resource request which basiclly checks if a resource is busy,
	//if not gives it to your process, and then marks it busy. If it is busy to begin with some
	//strategy is used to deny the request. Here, he deadlocks if the request cannot be done --
	//I think that means that the processes cannot complete because of lack of resources, no matter
	//what you do (Besides runnign them one at a time).
requestresource()
{
//check if it is allocated, will it go to deadlock
int proc, res[3];
printf("\nFor which Process, you need resources?(1-3):\n");
scanf("%d",&proc);
proc--;
if(running[proc])
{
printf("\nCurrently this process needs the foll. resources:\n");
printf("R1\tR2\tR3\n");
for(i=0;i<3;i++)
printf("%d\t",Pmax[proc][i]-Pcurr[proc][i]);
for(i=0;i<3;i++)
{
loop_3:
printf("\nEnter no. of Resource %d to Allocate to Process %d:\n",i+1,proc+1);
scanf("%d",&res[i]);
if((res[i]>(Pmax[proc][i]-Pcurr[proc][i]))||(res[i]>avl[i]))
{
printf("\nInvalid Value!, try again!");
goto loop_3;
}
}
getch();
if(allocate(proc,res))
{
printf("\nResources successfully allocated.\n");
if(checkcompletion(proc))
printf("\nProcess %d has completed its execution and its resources have been released.\n",proc+1);
}
else
printf("\nResouces cannot be allocated as it may lead to Deadlock!\n");
}
else
{
printf("\nInvalid Process no.\n");
getch();
}}
///allocate a resource to a process, used in the above routine. T
//his is just management code to mark the appropriate stuff when an allocation is allowed.
int allocate(int proc, int res[3])
{
for(i=0;i<3;i++)
{
Pcurr[proc][i]+=res[i];
avl[i]-=res[i];
}
if(!checksafe())
{
for(i=0;i<3;i++)
{
Pcurr[proc][i]-=res[i];
avl[i]+=res[i];
}
return 0;
}
return 1;
}
int checkcompletion(int proc)
{
if((Pcurr[proc][0]==Pmax[proc][0])&&(Pcurr[proc][1]==Pmax[proc][1])&&(Pcurr[proc][2]==Pmax[proc][2]))
{
for(i=0;i<3;i++)
{
avl[i]+=Pmax[proc][i];
}
running[proc]=0;
return 1;
}
return 0;
}
//print the state of the resources for the user to study.
viewresources()
{
printf("\n----Current Snapshot of the system----\n");
printf("\nMax. resources in the system:\n");
printf("R1\tR2\tR3\n");
for(i=0;i<3;i++)
printf("%d\t",maxres[i]);
printf("\nCurrent resources available in the system:\n");
printf("R1\tR2\tR3\n");
for(i=0;i<3;i++)
printf("%d\t",avl[i]);
printf("\n\nMax. resources required for Completion of each process:\n");
printf("\tR1\tR2\tR3\n");
for(i=0;i<3;i++)
{
if(running[i])
{
printf("P%d\t",i+1);
for(j=0;j<3;j++)
printf("%d\t",Pmax[i][j]);
printf("\n");
}}
printf("\n\nCurr. resources allocated for each process:\n");
printf("\tR1\tR2\tR3\n");
for(i=0;i<3;i++)
{
if(running[i])
{
printf("P%d\t",i+1);
for(j=0;j<3;j++)
printf("%d\t",Pcurr[i][j]);
printf("\n");
}
}}
// this is what you want: the bankers algorithm portion of the code! It uses the algorithm to generate a true or false (safe or unsafe) value
//which is used to see if a resource can be allocated to a given process.
int checksafe()
{
//Check if atleast one process can get all resources it needs --> Banker's algorithm
safe=0;
for(i=0;i<3;i++)
{
avltemp[i]=avl[i];
}
for(i=0;i<3;i++)
{
if(running[i])
{
if((Pmax[i][0]-Pcurr[i][0]<=avltemp[0])&&(Pmax[i][1]-Pcurr[i][1]<=avltemp[1])&&(Pmax[i][2]-Pcurr[i][2]<=avltemp[2]))
{
for(j=0;j<3;j++)
avltemp[j]+=Pcurr[i][j];
safe=1;
}
}}
return safe;
}