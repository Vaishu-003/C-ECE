MACRO1.C
#include<stdio.h>
#include<conio.h>
#include<string.h>
void main()
{
int i,j=0,sno=1,mdno=1;
char word[20];
FILE *fip,*fmnt,*fmdt,*fir;
clrscr();
fip=fopen("input.dat","r");		//open input  file
fmnt=fopen("mnt.dat","w");		//open mnt table
fmdt=fopen("mdt.dat","w");		//open mdt table
fir=fopen("ir.dat","w");		//Open Intermediate representation file 
while(!feof(fip))				//till the end if input code
{
	fscanf(fip,"%s",word);
	while(strcmp(word,"MACRO")&&(strcmp(word,"END")))
	{						//check for start of macro or end
		fprintf(fir," %s",word);   //if word is not macro and end
		fgets(word,20,fip);		//paste it in IR file
		if(!strcmp(word,"END\n"))
		{
			j=1;
			break;			//end, close all
		}
	}
	if(j!=1)
	{
		fgets(word,20,fip);         		//name of macro
		fprintf(fmnt," %d%s", sno,word);
		sno++;
		fprintf(fmdt," %d%s",mdno,word);
		mdno++;
		fgets(word,20,fip);			//paste it in mnt & mdt
	}
	while(strcmp(word,"MEND\n")&&(strcmp(word,"END\n")))
	{							//paste until end of macro
		fprintf(fmdt," %d %s",mdno,word);
   		mdno++;
		if(!strcmp(word,"END"))
			break;
		fgets(word,20,fip);
	}
	if(j!=1)
	{
		fprintf(fmdt," %d %s",mdno,word);	//paste MEND
		mdno++;
	}
}
fclose(fir);
fclose(fip);
fclose(fmdt);
fclose(fmnt);						//close all files
printf("\n CODE IS WRITTEN IN MNT.DAT,MDT.DAT & IR.DAT FILES");
getch();
}