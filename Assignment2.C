#include<stdio.h>
char mot[6][6]={"STOP","ADD","SUB","MUL","MOVER","MOVEM"}; //mnemonics 
char r[4][6]={"AREG","BREG","CREG","DREG"};			//registers
struct l	
{	char name;						//name of literal
	int add;						//address of literal
} lit[20];
struct s
{	char name[20];					// name of symbol
	int add;						//address of symbol
} sy[20];

void main()
{
	char st[10];
	int lc,n1=0,ns=0,i,j=0,k=0,litflag=0,m=0,tempb,flag=0;
	FILE *fip,*fir;
	clrscr();
	fip=fopen("input.asm","r");			//assembler input
	fir=fopen("ir.dat","w");		//Intermediate Representation
	fscanf(fip,"%s",st);			//read input
	while(!feof(fip))
	{
		up:if(!strcmp(st,"START"))	//if start copy address(lc)
		{
			fscanf(fip,"%d",&lc);
			fprintf(fir,"%s%d%s%d\n","AD",1,"C",lc);
		}
		fscanf(fip,"%s",st);		//read next
		for(i=0;i<6;i++)		//check if it present in mnemonics tabl
		{
			if(!strcmp(st,mot[i]))
			{
				fprintf(fir,"%s%d","IS",i+1);	//found in mot
				fscanf(fip,"%s",st);
				for(j=0;j<4;j++)			//now find register
					if(!strcmp(st,r[j]))
						fprintf(fir,"%d",j+1);
			   fscanf(fip,"%s",st);
			   if(!strcmp(st,"="))		//if = means literal else
			   {
					k=1;
					fscanf(fip,"%s",st);
	//check if said literal already present in literlar table
					for(j=0;j<n1;j++)
						if(!strcmp(lit[j].name,st[k]))
						{
							litflag=1;
							fprintf(fir,"%s%d","L",j);
						}
	//else add new entry in Literal table
					if(litflag==0)
					{
						lit[n1].name=st[k];
						fprintf(fir,"%s%d","L",n1);
						n1++;
					}
					break;
			   }
			   else  		//if it’s not literal it must be symbol
			   {
					for(j=0;j<ns;j++)
					{
	//check if said symbol is present if symbol table

						if(!strcmp(sy[j].name,st))
						{
						flag=1;
						fprintf(fir,"%s%d\n","S",j);
						lc++;
						goto up;
						}
					}
	//else add new entry in symbol table
					if(flag==0)
					{
						strcpy(sy[ns].name,st);
						fprintf(fir,"%s%d","S",ns);
						ns++;
						break;
					}
			   }
			}
       //if it’s not there in mot then check for symbol definition [DC/DS]
			for(m=0;m<ns;m++)
			{
				if(!strcmp(st,sy[m].name))
				{
					fscanf(fip,"%s",st);
					if(!strcmp(st,"DS"))
					{
						fscanf(fip,"%d",&tempb);
						fprintf(fir,"%s%d%d\n","DL",2,tempb);
						sy[m].add=lc;
						lc+=tempb;
						goto up;
					}
					else if(!strcmp(st,"DC"))
						{
							fscanf(fip,"%d",&tempb);
						fprintf(fir,"%s%d%d\n","DL",1,tempb);
							sy[m].add=lc;
							goto up;
						}
				}
			}
		}
//check for END of assembly statements
		if(!strcmp(st,"END"))
		{
			for(i=0;i<n1;i++)
			{
				fprintf(fir,"%s%d%s%c\n","AD",2,"C",lit[i].name);
				lit[i].add=lc;
				lc++;
			}
			break;
		}
		lc++;
		fprintf(fir,"\n");
	}
//print databases

	printf("\n DATABASE:-");
	printf("\nSYMBOL TABLE\nSYMBOL ENTRY\tSYMBOL\tADDRESS\n");
	for(i=0;i<ns;i++)
		printf("\n%d\t%s\t%d",i,sy[i].name,sy[i].add);
	printf("\nLITERAL TABLE\nLITERAL ENTRY\tLITERAL\tADDRESS\n");
	for(i=0;i<n1;i++)
		printf("\n%d\t%c\t%d",i,lit[i].name,lit[i].add);
	getch();
	fclose(fir);		//close files opened
	fclose(fip);
}