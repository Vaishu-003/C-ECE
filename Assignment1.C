/* program for lexical analyser*/
#include<stdio.h>
#include<conio.h>
#include<string.h>
int main(void)
{
int i=0,j=0,x=0,t=0,ss=0,ss_print[15],kw_print=0,ss_flag=0,kw_flag=0,wrdfnd=0,key_print[10],idn_pri[10];
char ch,kw[10],mac1[15][15],spl_symb[]={'#','+','-','*','/','>','<','(',')','=',',',';','{','}'};
char keywrds[10][10]={"include","void","main","stdio.h","conio.h","getch","int","char","float"};
FILE *in;
clrscr();
in=fopen("test.c","r");
for(i=0;i<15;i++)
	{
		ss_print[i]=0;
		key_print[i]=0;
		idn_pri[i]=0;
		mac1[i][0]=0;
	}
do
	{
		ss_flag=0;
		wrdfnd=0;
		ch=fgetc(in);

		for (i=0;i<14;i++)
			if(ch==spl_symb[i])
			{
			 ss++;
			 ss_print[i]++;
			 ss_flag=1;
			}
		if(ss_flag==0 && ch!=' ')
		{
			if((ch>='a' && ch<='z') || (ch>='A' && ch>='Z' ) || ch=='.')
			{
			  kw[j]=ch;
			  kw_flag=1;
			  j++;
			}
			}
			else if (kw_flag==1 || ch==' ')
			{
				kw[j]='\0';
				wrdfnd=1;
			}
			if(wrdfnd==1)
			{
				kw_print=0;
				for(i=0;i<10;i++)
				{
					if (strcmp(kw,keywrds[i])==0)
					{
						key_print[i]++;
						kw_print=1;
						j=0;
					}
				}
				if(kw_print!=1)
				{
					if(ch!=' ')
					{
					for(i=0;i<=x;i++)
					if(!strcmp(kw,mac1[i]))
					{
						idn_pri[i]++;
						t=1;
						break;
					}
					if(t!=1)
					{
					strcpy(mac1[x],kw);
					t=0;
					x++;
					}
				}
				}
				j=0;
			}
	} while(ch!=EOF);

	printf("\nSymbol Table\n");
	for(i=0;i<14;i++)
			printf("%d \t %c \t %d \n",i,spl_symb[i],ss_print[i]);
	printf("no of special symbol %d\nUniform Symbol Table\n",ss);
	getch();
	for(i=0;i<14;i++)
		if(ss_print[i]!=0)
			printf("%d \t %c \t \n",i+1,spl_symb[i]);
	getch();
	printf("\nKeyword Table\n");
	for(i=0;i<6;i++)
		if(key_print[i]!=0)
			printf("%d \t %d \t %s \n",i+1,key_print[i],keywrds[i]);
	printf("\nData Types table\n");
	for(i=6;i<9;i++)
		if(key_print[i]!=0)
			printf("%d \t %d \t %s \n",i-5,key_print[i],keywrds[i]);
	printf("\nIdentifier Table\n");
	for(i=0;i<10;i++)
		if(idn_pri[i]!=0)
			printf("%d \t%s \t%d\n",i+1,mac1[i],idn_pri[i]);
	getch();
	fclose(in);
	return 1;
}