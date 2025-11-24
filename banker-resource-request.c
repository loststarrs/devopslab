// Banker's Algorithm  
#include <stdio.h>  
int main()  
{  
    // P0, P1, P2, P3, P4 are the Process names here  
  
    int n, r, m, i, j, k,instance[10], alc[10][10],max[10][10],need[10][10],available[10],P[10],work[10],finish[10],ans[10],ind=0,request[10];  
    printf("Enter the number of process and resource types");
    scanf("%d %d", &n, &m);
    
    printf("\n enter the max instances of each resources\n");
	for (i=0;i<m;i++) {
		available[i]=0;
		printf("%c= ",(i+97));
		scanf("%d",&instance[i]);
	}
    
    printf("enter the max resource process required %dx%d matrix", n, m);
      for (i = 0; i < n; i++) {
       for (j = 0; j < m; j++) {
        scanf("%d", & max[i][j]);
     }
   }

printf("enter allocation of resource of all process %dx%d matrix", n,m);
    for (i = 0; i < n; i++) {
      for (j = 0; j < m; j++) {
        scanf("%d", & alc[i][j]);
        available[j]+=alc[i][j];
      }
    }  
    
  //computing available vector
    for(i=0;i<m;i++)
    
     available[i]=instance[i]-available[i];
     
     
 //computing NEED matrix
     for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alc[i][j];
    }
    
 printf("Enter the number of the requesting process");
 scanf("%d", &r);
 printf("Enter the request vector for the requesting process:\n");
 for(i=0;i<m;i++)
   scanf("%d",&request[i]);
 //check request < Need
 
 for(j=0;j<m;j++)
   {
     if(request[j]>need[r][j])
       {
         printf("process has exceeded its maximum claim\n");
         return 0;
        }
    }
 //check request < available   
   for(j=0;j<m;j++)
   {
     if(request[j]>available[j])
       {         
         printf("process has to wait since resources are not available\n");
         return 0;
        }
    }  
  // update the available, allocation and need 
  for(j=0;j<m;j++)
    {
    available[j] -=request[j];
    alc[r][j] += request[j];
    need[r][j]-=request[j];
    }
    
  
 //Initialize work and finish
 for(i=0;i<m;i++)
    
     work[i]=available[i];
     
  for(i=0;i<n;i++)
    finish[i]=0;
    
    
 // checking for safe sequence
    
    int y = 0;
    for (k = 0; k < m; k++) {
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
 
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]){
                        flag = 1;
                         break;
                    }
                }
 
                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        work[y] += alc[i][y];
                    finish[i] = 1;
                }
            }
        }
    }
   
 //Printing Safe sequenc if exists
  int flag = 1;
       
  for(int i=0;i<n;i++)
    {
      if(finish[i]==0)
      {
        flag=0;
         printf("The following system is not safe");
        break;
      }
    }
     
  if(flag==1)
    {
      printf("Following is the SAFE Sequence\n");
      for (i = 0; i < n - 1; i++)
        printf(" P%d ->", ans[i]);
      printf(" P%d\n", ans[n - 1]);
    }
printf("Request by procee %d can be granted\n",r);
return 0;
}
