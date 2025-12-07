#include<stdio.h>
#include<math.h>
int sost;
void getinfo();
void ltpaddr();

struct segtab{
    int sno;
    int baddr;
    int limit;
}st[10];


void getinfo(){
    int i;
    printf("enter the size of segamnetaion table:\n");
    scanf("%d",&sost);
    for(i=1;i<=sost;i++){
        printf("enter the information about segmentation: %d",i);
        st[i].sno=i;
        printf("\n\nenter the base address:");
        scanf("%d",&st[i].baddr);
        printf("\n\tenter the limit:");
        scanf("%d",&st[i].limit);
    }
}
void ltpaddr(){
    int i,sn,offset,paddr;
    printf("\n\n\t\t\t SEGEMNT TABLE\n\n");
    printf("\n\tSEG.NO\tBASE ADDRESS\tLIMIT \n\n");
    for(i=1;i<=sost;i++){
        printf("\n%d \t%d \t\t%d",st[i].sno,st[i].baddr,st[i].limit);
    }
    printf("\n\n enter th logical address:");
    printf("\n\nenter segment number:");
    scanf("%d",&sn);
    printf("\n\n enter offset value:");
    scanf("%d",&offset);
    if(offset<=st[sn].limit){
        paddr = st[sn].baddr + offset;
        printf("\n\n physical address is : %d",paddr);}
        else{
            printf("\n\n invalid reference");
        }
}
int main() {
    int choice;
    getinfo();
    while(1) {
        printf("\n\n 1. Compute physical adress for a given logical address");
        printf("\n\n 2. Exit");
        printf("\n\n Enter your choice:");
        scanf("%d",&choice);
        switch(choice) {
            case 1: ltpaddr(); break;
            case 2: return 0;
        }
    }
}