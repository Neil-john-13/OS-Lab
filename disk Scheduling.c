#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
void sort(int req[],int n)
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (req[j] > req[j + 1]) {
                int temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }
        }
    }
}

void FCFS(int req[],int cylinders,int n,int current)
{
    
    int currentPos = current;
    int totalSeekTime = 0;
    
    

    for (int i = 0; i < n; i++) {
        int seekTime = abs(req[i] - currentPos);
        totalSeekTime += seekTime;
        currentPos = req[i];
    }
    
    printf("Total head movement: %d\n", totalSeekTime);
    //printf("Average Seek Time: %.2f\n", (float)totalSeekTime / n);
    
}
int findShortestSeekTime(int req[], int n, int currentPos, int visited[]) {
    int shortestSeekTime = INT_MAX;
    int shortestSeekIndex = -1;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int seekTime = abs(req[i] - currentPos);
            
            if (seekTime < shortestSeekTime) {
                shortestSeekTime = seekTime;
                shortestSeekIndex = i;
            }
        }
    }
    
    return shortestSeekIndex;
}
void SSTF(int req[],int cylinders,int n,int current)
{
    int visited[30] = {0};
    int currentPos = current;
    int totalSeekTime = 0;
    
    for (int i = 0; i < n; i++) {
        int shortestSeekIndex = findShortestSeekTime(req, n, currentPos, visited);
        
        visited[shortestSeekIndex] = 1;
        
        int seekTime = abs(req[shortestSeekIndex] - currentPos);
        totalSeekTime += seekTime;
        currentPos = req[shortestSeekIndex];
    }
    
    printf("Total Seek Time: %d\n", totalSeekTime);
    //printf("Average Seek Time: %.2f\n", (float)totalSeekTime / n);
}
void SCAN(int req[],int cylinders,int n,int current,int prev)
{
    int currentPos = current;
    int totalSeekTime = 0;
    int maxTrack=cylinders-1;
    sort(req,n);
    int currentIndex = 0;
    while (currentIndex < n && req[currentIndex] < currentPos) {
        currentIndex++;
    }

    if ((prev-current)<0) { // Scanning towards the maximum track
        for (int i = currentIndex; i < n; i++) {
            int seekTime = abs(req[i] - currentPos);
            totalSeekTime += seekTime;
            currentPos = req[i];
        }
        
        totalSeekTime += abs(maxTrack - currentPos);
        currentPos = maxTrack;
        
        for (int i = currentIndex - 1; i >= 0; i--) {
            int seekTime = abs(req[i] - currentPos);
            totalSeekTime += seekTime;
            currentPos = req[i];
        }
    }
    else { // Scanning towards the minimum track
        for (int i = currentIndex - 1; i >= 0; i--) {
            int seekTime = abs(req[i] - currentPos);
            totalSeekTime += seekTime;
            currentPos = req[i];
        }
        
        totalSeekTime += abs(currentPos);
        currentPos = 0;
        
        for (int i = currentIndex; i < n; i++) {
            int seekTime = abs(req[i] - currentPos);
            totalSeekTime += seekTime;
            currentPos = req[i];
        }
    }
    
    printf("Total Seek Time: %d\n", totalSeekTime);
    //printf("Average Seek Time: %.2f\n", (float)totalSeekTime / n);
}
void CSCAN(int req[],int cylinders,int n,int current,int prev)
{
    int currentPos = current;
    int totalSeekTime = 0;
    int maxTrack=cylinders-1;
    sort(req,n);
    int currentIndex = 0;
    while (currentIndex < n && req[currentIndex] < currentPos) {
        currentIndex++;
    }

    if ((prev-current)<0) { // Scanning towards the maximum track
        for (int i = currentIndex; i < n; i++) {
            int seekTime = abs(req[i] - currentPos);
            totalSeekTime += seekTime;
            currentPos = req[i];
        }
        
        totalSeekTime += abs(maxTrack - currentPos);
        currentPos = maxTrack;
        totalSeekTime += abs(0 - currentPos);
        currentPos=0;
        
        for (int i = 0; i <currentIndex; i++) {
            int seekTime = abs(req[i] - currentPos);
            totalSeekTime += seekTime;
            currentPos = req[i];
        }
    } 
    else { // Scanning towards the minimum track
        for (int i = currentIndex - 1; i >= 0; i--) {
            int seekTime = abs(req[i] - currentPos);
            totalSeekTime += seekTime;
            currentPos = req[i];
        }
        
        totalSeekTime += abs(currentPos);
        currentPos = 0;
        totalSeekTime += abs(maxTrack - currentPos);
        currentPos = maxTrack;
        
        for (int i = n-1; i >=currentIndex; i--) {
            int seekTime = abs(req[i] - currentPos);
            totalSeekTime += seekTime;
            currentPos = req[i];
        }
    }
    printf("Total Seek Time: %d\n", totalSeekTime);
}

void main()
{
    int n,cylinders,choice,current,prev;
    int req[30];
    printf("enter the number of  request  : ");
    scanf("%d",&n);
    
    for(int i =0;i<n;i++)
    {
        printf("enter the  request %d  ",i+1);
        scanf("%d",&req[i]);
    }
    printf("enter the number of  cylinders : ");
    scanf("%d",&cylinders);
    printf("enter the current request");
    scanf("%d",&current);
    printf("enter the previous request");
    scanf("%d",&prev);

    while(true)
    {
        printf("\n1. FCFS\n2. SSTF\n3. SCAN\n4. CSACN \n5. exit\nEnter your choice : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                FCFS(req,cylinders,n,current);
                break;
            case 2:
                SSTF(req,cylinders,n,current);
                break;
            case 3:
                SCAN(req,cylinders,n,current,prev);
                break;
            case 4:
                CSCAN(req,cylinders,n,current,prev);
                break;
            case 5:
                exit(0);
            default :
                printf("\n invalid choice !");
        }
    }

}