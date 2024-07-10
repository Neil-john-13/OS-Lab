
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int used[10];
bool found(int a[],int n,int x)
{
    for(int i=0;i<n;i++)
    {
        if(a[i]==x)
        {
            return true;
        }
    }
    return false;
}

void display(int a[],int n,int count)
{
    if(count<n)
    {
        for(int i=0;i<count;i++)
        {
            printf("%d ",a[i]);
        }
    }
    else{
        for(int i=0;i<n;i++)
        {
            printf("%d ",a[i]);
        }
    }
   
}

int findLRU(int frames[], int used[], int nframes) {
    int i, min = used[0], minIndex = 0;
    for (i = 1; i < nframes; i++) {
        if (used[i] < min) {
            min = used[i];
            minIndex = i;
        }
    }
    return minIndex;
}



void FIFO(int ref[],int n_frames,int n)
{
    int count=0,index=0;
    int frame[8];
    printf("\n ref_string\t\tframe\t\t\tstatus");
    printf("\n---------------------------------------------------------------------------");
    for (int i = 0; i < n_frames; i++) {
        frame[i]=-1;
    }
    for(int i=0;i<n;i++)
    {
        if(found(frame,n_frames,ref[i]))
        {
            printf("\n\t%d\t\t",ref[i]);
            display(frame,n_frames,count);
            printf("\t\t\thit");
        }
        else
        {
            frame[index]=ref[i];
            index=(index+1)%n_frames;
            count++;
            printf("\n\t%d\t\t",ref[i]);
            display(frame,n_frames,count);
            printf("\t\t\tmiss");
        }
    }
    printf("\nthe number of page fault : %d",count);
}


void LRU(int ref[],int n_frames,int n)
{
    int count=0,index=0;
    int frame[8],used[10];
    for (int i = 0; i < n_frames; i++) {
        used[i] = 0;
        frame[i]=-1;
    }
    printf("\nLRU Page Replacement Algorithm:\n");
    printf("\n ref_string\t\tframe\t\t\t\tstatus");
    printf("\n---------------------------------------------------------------------------");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < n_frames; j++) {
            if (frame[j] == ref[i]) {
                found = 1;
                used[j] = i + 1;
                break;
            }
        }
        if (found==0) {
            int lruIndex = findLRU(frame, used, n_frames);
            frame[lruIndex] = ref[i];
            used[lruIndex] = i + 1; 
            count++;
            printf("\n\t%d\t\t",ref[i]);
            display(frame,n_frames,count);
            printf("\t\t\tmiss");
        }
        else{
            printf("\n\t%d\t\t",ref[i]);
            display(frame,n_frames,count);
            printf("\t\t\thit");
        }
    }
    printf("\nthe number of page fault : %d",count);
}

int findReplacement(int ref[], int n, int frame[], int n_frames, int i) {
    int replaceIndex = -1;

    int max_future_index = -1;
    for (int j = 0; j < n_frames; j++) {
        bool found_future = false;
        for (int k = i + 1; k < n; k++) {
            if (ref[k] == frame[j]) {
                found_future = true;
                if (k > max_future_index) {
                    max_future_index = k;
                    replaceIndex = j;
                }
                break;
            }
        }
        if (!found_future) {
            replaceIndex = j;
            break;
        }
    }

    return replaceIndex;  
}

void OPR(int ref[],int n_frames,int n)
{
    int count=0,index=0;
    int frame[8];
    for (int i = 0; i < n_frames; i++) {
        frame[i]=-1;
    }
    printf("\n ref_string\t\tframe\t\t\t\tstatus");
    printf("\n---------------------------------------------------------------------------");  
    for (int i = 0; i < n; i++) {
        if (found(frame, n_frames, ref[i])) 
        {
            printf("\n\t%d\t\t", ref[i]);
            display(frame, n_frames, count);
            printf("\t\t\thit");
        } 
        else 
        {
            int replace_index = -1;
            if (count < n_frames)
            {
                replace_index = count;
            } 
            else 
            {
                replace_index=findReplacement(ref, n,frame,n_frames,i);
            }
            frame[replace_index] = ref[i];
            count++;
            printf("\n\t%d\t\t", ref[i]);
            display(frame, n_frames, count);
            printf("\t\t\tmiss");
        }
    }
    printf("\nthe number of page fault : %d",count);
}


void main()
{
    int n,n_frames,choice;
    int ref[100];
    printf("enter the number of  elements in reference  string  : ");
    scanf("%d",&n);
    printf(" enter the  elements in reference  string: ");
    for(int i =0;i<n;i++)
    {
        scanf("%d",&ref[i]);
    }
    printf("enter the number of  frames : ");
    scanf("%d",&n_frames);
    while(true)
    {
        printf("\n1. FIFO\n2. LRU\n3. OPR \n4. exit\nEnter your choice : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                FIFO(ref,n_frames,n);
                break;
            case 2:
                LRU(ref,n_frames,n);
                break;
            case 3:
                OPR(ref,n_frames,n);
                break;
            case 4:
                exit(0);
            default :
                printf("\n invalid choice !");
        }
    }

}