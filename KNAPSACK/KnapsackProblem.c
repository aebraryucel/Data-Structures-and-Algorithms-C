#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void knapsackGreedy(float capacity, int n, float weight[], float profit[])
{
	float x[20], totalprofit,y;
	int i,j;
	y=capacity;
	totalprofit=0;
	for(i=0;i < n;i++)
		x[i]=0.0;
	for(i=0;i < n;i++)
	{
		if(weight[i] > y)
			break;
		else
		{
			x[i]=1.0;
			totalprofit=totalprofit+profit[i];
			y=y-weight[i];
		}
	}
	if(i < n)	
		x[i]=y/weight[i];
	totalprofit=totalprofit+(x[i]*profit[i]);
	printf("The selected elements are:\n ");
	for(i=0;i < n;i++)
		if(x[i]==1.0)
			printf("\nProfit is %f with weight %f ", profit[i], weight[i]);
		else if(x[i] > 0.0)
			printf("\n%f part of Profit %f with weight %f", x[i], profit[i], weight[i]);
	printf("\nTotal profit for %d objects with capacity %f = %f\n\n", n, capacity,totalprofit);

}



int max(int a, int b) 
{ 
    return (a > b) ? a : b; 
} 
  
int knapSack(int W, int wt[], int val[], int n) 
{ 
    int i, w; 
    int K[n + 1][W + 1]; 
   
    for (i = 0; i <= n; i++) { 
        for (w = 0; w <= W; w++) { 
            if (i == 0 || w == 0) 
                K[i][w] = 0; 
            else if (wt[i - 1] <= w) 
                K[i][w] = max( 
                    val[i - 1] + K[i - 1][w - wt[i - 1]], 
                    K[i - 1][w]); 
            else
                K[i][w] = K[i - 1][w]; 
        } 
    } 
   
    return K[n][W]; 
} 
   




int main(){
	
	
	int itemCnt;
    float capacity;
    int capacityInt;
	char line[30];
	
	int itemIDs_[50];
    float values_[50];
    float weights_[50];
    
    int values[50];
    int weights[50];
    
    
    int m;
    for(m=0;m<50;m++){
    	itemIDs_[m]=-1;
    	values_[m]=-1.0;
    	weights_[m]=-1.0;
	}
    
    
	
	FILE * fp;

    fp = fopen ("input1.txt", "r");
   
    if(fp==NULL){
   	    printf("file error! \n");
   	    return -1;
   
       }
   
   
   
   
   int lineNo=0;
   int k=0;
   itemCnt=0;
   
   while (fgets(line, sizeof(line), fp) != NULL){
   	line[strcspn(line, "\n")] = 0;
    
    
    
    if(lineNo==0){
    	capacity=atof(line);
    	capacityInt=atoi(line);
 	
    	lineNo++;
    	continue;
	}
	
	k=0;
	
	char * token = strtok(line," ");
	
    while( token != NULL ) {
    //	printf("%s\n",token);
       if(k==0){
       	    itemIDs_[lineNo-1]=atoi(token);
       	    k++;
	   }
	   else if(k==1){
	   	    weights_[lineNo-1]=atof(token);
	   	    weights[lineNo-1]=atoi(token);
	   	    k++;
	   	
	   }
	   else if(k==2){
	   	    values_[lineNo-1]=atof(token);
	   	    values[lineNo-1]=atoi(token);
	   	    k=0;
	   }
       token = strtok(NULL, " ");
       
   }
    
    
    lineNo++;
    

}

  itemCnt=lineNo-2;
  
  



  

  knapsackGreedy(capacity,itemCnt,weights_,values_);



   printf("KnapSack Dynamic Programming Profit: %d\n", knapSack(capacityInt, weights, values, itemCnt));

	
}

	
