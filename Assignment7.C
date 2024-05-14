page.C
int fr[10],cy=1,frsize,stsize;p[20]; //frame, frame & string size,string
void display()
{
	int i;
	printf("\n Cycle: %d \tRequested page: %d\t",cy,p[cy-1]);
	for(i=0;i<frsize;i++)
	printf("\t%d",fr[i]);
	cy++;
}
void main()
{
	int i,j,ch=0,fs[10];
	int index=0,k,l,flag1=0,flag2=0,pf=0;
	clrscr();
	printf("\nEnter frame size(1-10):");
	scanf("%d",&frsize);
	printf("\n Enter string length(1-20):");
	scanf("%d",&stsize);
	printf("\n Enter %d elements of string:",stsize);
	for(i=0;i<stsize;i++)
	scanf("%d",&p[i]);
	printf("\nWITH FIFO algorithm");
again:for(i=0;i<frsize;i++)
		fr[i]=-1;
	for(j=0;j<stsize;j++)
	{
		flag1=0,flag2=0;
		for(i=0;i<frsize;i++)
			if(fr[i]==p[j])
			{		// if page already present in frame
				flag1=1;
				flag2=1;
				break;
			}
		if(flag1==0)
			for(i=0;i<frsize;i++)
				if(fr[i]==-1)
				{	//check for free slot in frame
					fr[i]=p[j];
					flag2=1;
					break;
				}
		if(flag2==0)	//page not present in frame and no free slot
		{    if(ch==1)
		{			//LRU algorithm logic
			for(i=0;i<frsize;i++)
				fs[i]=0;	//to record usage pattern
//check last framesize -1 usage to find LRU frame
			for(k=j-1,l=1;l<=frsize-1;l++,k--)
				for(i=0;i<frsize;i++)
					if(fr[i]==p[k])
						fs[i]=1;		
			for(i=0;i<3;i++)
				if(fs[i]==0)	//replace LRU frame
					index=i;
			fr[index]=p[j];
			}
			else
			{			//FIFO algorithm login
				fr[index]=p[j];
			index++;
			if(index==frsize)
			index=0;
			}
			pf++;		//replace oldest item in frame cyclically 
		}
		display();
		}
		printf("\n no of page faults :%d",pf);
		if(ch==0)
		{		//toggle algorithm after FIFO execution
		ch=1;
		cy=1;pf=0;	//reinitialize shared variables
		printf("\nWith LRU algorithm");
		goto again;
		}
		getch();
}