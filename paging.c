#include<stdio.h>

int main()
{
   int ms, ps, nop, np, rempages, i, j, x, y, pa, offset;
   int s[10], fno[10][20];
   printf("\nEnter the main memory size -- "); 
   scanf("%d",&ms);
   printf("\nEnter the page size -- "); 
   scanf("%d",&ps);
   nop = ms/ps;
   printf("\nThe no. of pages available in memory are -- %d ",nop);
   printf("\nEnter number of processes -- ");
   scanf("%d",&np);
   rempages = nop; 
   for(i=0;i<np;i++)
    {
      printf("\nEnter no. of pages required for p[%d]-- ",i);
      scanf("%d",&s[i]);
      if(s[i] >rempages)
       {
        printf("\nMemory is Full"); 
        s[i]=999; //indicating memory not allotted
        break;
       }
     rempages = rempages - s[i];
     printf("\nEnter pagetable for p[%d] --- ",i);
     printf("\n Enter Frames numbers to which pages of p[%d] are to be mapped\n",i);
   for(j=0;j<s[i];j++)
   scanf("%d",&fno[i][j]);
  }
   printf("\n\n\t\tPage table \n");
   printf("\nProcess\t\tFrames alloted\n");
   for(i=0;i<np;i++)
   {
     if(s[i]==999)
       {
        printf("Memory not allotted for process %d\n",i);
        break;
        }
     printf("%d\t\t",i);
      for(j=0;j<s[i];j++)
        printf("%d,",fno[i][j]);
     printf("\n");
    } 

   printf("\nEnter Logical Address to find Physical Address "); 
   printf("\nEnter process no. and page number and offset -- ");
   scanf("%d %d %d",&x,&y, &offset);
    if(x>np || y>=s[x] || offset>=ps)
      printf("\nInvalid Process or Page Number or offset");
   else
    { 
     pa=fno[x][y]*ps+offset;
     printf("\nThe Physical Address is -- %d\n\n",pa);
    }
return 0;
}

