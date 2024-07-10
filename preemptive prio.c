#include<stdio.h>
struct process
{
    int id;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
    int RT;
    int prio;
};
void sort(struct process p[], int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(p[j].AT>p[j+1].AT)
            {
                struct process temp =p[j];
                p[j]=p[j+1];
                p[j+1]=temp;

            }
        }
    }
}


void display(struct process p[],int n)
{
    printf("\nProcess ID\tAT\tBT\tCT\tWT\tTAT");
    printf("\n--------------------------------------------------");
    for(int i=0;i<n;i++)
    {
        printf("\n\t%d\t%d\t%d\t%d\t%d\t%d\t",p[i].id,p[i].AT,p[i].BT,p[i].CT,p[i].WT,p[i].TAT);
    }
}

void main()
{
    int n;
    struct process p[10];
    printf("enter the number of process :");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        printf("Enter the  process id : ");
        scanf("%d",&p[i].id);
        printf("Enter the  process arrival time : ");
        scanf("%d",&p[i].AT);
        printf("Enter the  process burst time : ");
        scanf("%d",&p[i].BT);
        printf("Enter the  process priority : ");
        scanf("%d",&p[i].prio);
        p[i].RT=p[i].BT;
    }
    sort(p,n);
    int processed=0,time=0,totalTAT=0,totalWT=0;
    while(processed!=n)
    {
        int shortest=-1;
        int shortest_prio=99999999;
        for(int i=0;i<n;i++)
        {
            if(p[i].AT<=time && p[i].prio<shortest_prio && p[i].RT>0)
            {
                shortest=i;
                shortest_prio=p[i].prio;
            }
           
        }
        if(shortest==-1)
        {
            time++;
            continue;
        }
        p[shortest].RT--;
        if(p[shortest].RT==0)
        {
            p[shortest].CT=time+1;
            p[shortest].TAT=p[shortest].CT-p[shortest].AT;
            totalTAT+=p[shortest].TAT;
            p[shortest].WT=p[shortest].TAT-p[shortest].BT;
            totalWT+=p[shortest].WT;
            processed++;
        }
        time++;
    }
    display(p,n);
    printf("\n the average turn around time : %.2f",(float)(totalTAT/n));
    printf("\n the average waiting time : %.2f",(float)(totalWT/n));
}