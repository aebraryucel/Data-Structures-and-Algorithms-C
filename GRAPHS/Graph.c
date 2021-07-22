#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define SIZE 999
  

struct AdjListNode //adj listelerindeki düðüm
{ 
    int id; 
    struct AdjListNode* next; 
    int weight;
}; 
  

struct Graph 
{ 
    int size; //graftaki adj listesi sayýsý
    struct AdjListNode** array; //adj listelerini tutan array
    int nodeCnt;
    int edgeCnt;
    int startNode;
    int finishNode;
    
}; 


struct Edge{
	int source;
	int dest;
	int weight;
};



struct Path{
	int cost;
	int path[100];
};



  
struct AdjListNode* newAdjListNode(int id) {  //adj listesi düðümü oluþturan fonksiyon
    struct AdjListNode* newNode =  (struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
    newNode->id = id; 
    newNode->next = NULL; 
    return newNode; 
} 




struct Graph* createGraph(int size) { //graf oluþturan fonksiyon
    int i;
    struct Graph* g = (struct Graph*) malloc(sizeof(struct Graph)); 
    g->size = size; 
    g->array = (struct AdjListNode**)malloc(size*sizeof(struct AdjListNode*)); 
    
    for (i = 0; i<size; i++){
    	g->array[i] = NULL;
	}

    
    return g; 
} 





void printGraph(struct Graph* g) {  //grafý yazdýran fonksiyon
    int i;
    
    printf("graf dugum sayisi: %d\n",g->nodeCnt);
    printf("graf kenar sayisi: %d\n",g->edgeCnt);
    printf("graf baslangic dugumu: %d , bitis dugumu : %d",g->startNode,g->finishNode);
    
    for (i=0;i<g->size;i++) 
    { 
        struct AdjListNode* current = g->array[i]; 
        
        if(current!=NULL){
		
        printf("\n %d numarali dugumun kenarlari : \n ",i); 
        while (current!=NULL) 
        { 
            printf("%d ->", current->id);
            current = current->next; 
        }
        printf("\n"); 
        
      }
    } 
} 





struct Graph* readData(struct Graph* g){  // veri okuma
	 int start;
	 int finish;
	 int weight; 
	 int r;   
	 struct AdjListNode* temp;   
	                

	FILE* fp=fopen("Veri5.txt","r");
	if(fp==NULL){
		printf("Dosya acilamadi!\n");
		return g;
	}
	
	r = fscanf(fp, "%d %d", &g->nodeCnt,&g->edgeCnt);
	
	r = fscanf(fp, "%d %d", &g->startNode,&g->finishNode);
	
    while (((r = fscanf(fp, "%d %d %d", &start,&finish,&weight)) != EOF)){
			temp=newAdjListNode(finish);
		
			temp->weight=weight;	
			temp->next=g->array[start];
			g->array[start]=temp;
				
			
			
    }
    	
    fclose(fp);			
	return g;
}






int checkCostArray(int array[],int size){
	
	int i;
	
	for(i=0;i<size;i++){
		if(array[i]!=99999){
			return 0;
		}
	}
	
	return 1;
	
	
}




int findMinCost(int array[],int size){
	
	int i;
	int min=9999999;
	int minIndex;
	
	for(i=0;i<size;i++){
		if(array[i]<min){
			min=array[i];
			minIndex=i;
		}
	}
		
	return minIndex;

}

struct Path shortestPath(struct Graph* g,int startNode,int finishNode){  //2 düðüm arasýndaki en kýsa yolu bulan fonksiyon

    int prev[g->nodeCnt];
    int cost[g->nodeCnt];
    int isExtended[g->nodeCnt];
    int i;
    struct AdjListNode* temp;
    struct Path shortestpath;
    int minIndex;
    int currentMinCost=99999;

    for(i=0;i<g->nodeCnt;i++){
    	cost[i]=99999;
    	prev[i]=-1;
    	isExtended[i]=-1;
	}
	
	
	temp=g->array[startNode];
	
	while(temp!=NULL){
		
		if(temp->id==finishNode){
			currentMinCost=temp->weight;
			cost[temp->id]=99999;
			prev[temp->id]=startNode;
		}
		else{
		    cost[temp->id]=temp->weight;
		    prev[temp->id]=startNode;
		    	
		}

        temp=temp->next;
	}
	
	isExtended[startNode]=1;
	prev[startNode]=startNode;
	

    while(!checkCostArray(cost,g->nodeCnt)){
    	
    	minIndex=findMinCost(cost,g->nodeCnt); 
    	
    	temp=g->array[minIndex];
    //	printf("extended : %d\n",minIndex);
    	
    	while(temp!=NULL){
    		
    		if(minIndex==finishNode){
    			currentMinCost=cost[minIndex];
    			break;
			}
    		else if(temp->id==finishNode){
    			cost[temp->id]=99999;
    			
    		//	printf("finish node: %d  prev node: %d cost: %d\n",temp->id,minIndex,cost[minIndex]+temp->weight);
    			if((cost[minIndex]+temp->weight < currentMinCost)){
    				currentMinCost=cost[minIndex]+temp->weight;
    				prev[temp->id]=minIndex;
				}
    			
			}
			else if((cost[minIndex]+temp->weight < cost[temp->id]) && (isExtended[temp->id] != 1)){
				
				cost[temp->id]=cost[minIndex]+temp->weight;
				prev[temp->id]=minIndex;
			//	printf("node :%d   new cost: %d  new prev: %d \n",temp->id,cost[temp->id],prev[temp->id]);
				
			}
    		
    		
    		temp=temp->next;
		}
    	
    	
    	isExtended[minIndex]=1;
    	cost[minIndex]=99999;
    	
    	
    	
    	
	}
	
	
	if(currentMinCost==99999){
//		printf("iki dugum arasinda yol bulunamadi. \n");
		shortestpath.cost=99999;
		return shortestpath;
	}
	else{
		int index;
		
		for(i=0;i<g->nodeCnt;i++){
			shortestpath.path[i]=-1;
		}
		
		shortestpath.cost=currentMinCost;
		
		i=(g->nodeCnt)-1;
		
		shortestpath.path[i]=finishNode;
		
		while(i!=-1){
			i--;
			shortestpath.path[i]=prev[shortestpath.path[i+1]];
			if(prev[shortestpath.path[i+1]]==startNode){
				break;
			}
				
		}

		
			
		return shortestpath;
	}
    

}






int* queue[1000];
int front = -1;
int rear = -1;


void enQueue(int* item)  
{  
     
    if(rear == 999)  
    {  
        printf("\nOVERFLOW\n");  
        return;  
    }  
    if(front == -1 && rear == -1)  
    {  
        front = 0;  
        rear = 0;  
    }  
    else   
    {  
        rear = rear+1;  
    }  
    queue[rear] = item;  
  //  printf("\nValue inserted ");  
      
}  
int* deQueue()  
{  
    int* item;   
    if (front == -1 || front > rear)  
    {  
        printf("\nUNDERFLOW\n");  
        return;  
              
    }  
    else  
    {  
        item = queue[front];  
        if(front == rear)  
        {  
            front = -1;  
            rear = -1 ;  
        }  
        else   
        {  
            front = front + 1;  
        }  
    //    printf("\nvalue deleted ");  
    }  
      
    return item;
}  



int* allocatePath(struct Graph* g){
	int i;
	int* path;
    path=(int*)malloc(g->nodeCnt*sizeof(int));
	
	for(i=0;i<g->nodeCnt;i++){
		path[i]=-1;
	}
	
	
	return path;
}





int arraySize(int* array){
	int i=0;
	
	while(array[i]!=-1){
		i++;
	}
	
	return i;
}

int* edgeList(struct Graph* g,int src){
	
	struct AdjListNode* temp;
	int* edges=(int*)malloc((g->nodeCnt-1)*sizeof(int));
	int i=0;
	int j;
	for(j=0;j<g->nodeCnt-1;j++){
		edges[j]=-1;
	}
	
	temp=g->array[src];
	
	while(temp!=NULL){
	    edges[i]=temp->id;
	
		temp=temp->next;
		i++;
	}
	
	
	return edges;
	
}


int calculateCost(struct Graph* g,int* path,int pathlength){
   	int i=pathlength-1;
   	int j;
   	int cost=0;
   	
   	struct AdjListNode* temp;
   	
	while(i!=0){
	    temp=g->array[path[i-1]];
	    
   	    while(temp!=NULL){
	        
	        if(temp->id==path[i]){
	        	cost=cost+temp->weight;
	        	break;
			}
		    temp=temp->next;  
	    }
	    
	    i--;
	}      

   	   
   	 return cost;
   	
   }



	int* results[1000];	
	
void paths(struct Graph* g,int src,int dest){  //verilen 2 düðüm arasýndaki tüm yollarý bulan fonksiyon
	int k=0;
	int i,j,m,u;
	int* path;
	int* newpath;
	int* edges;
	int edgeCnt;
	int l;
	int cost;
	int cycleflag;
	path=allocatePath(g);
	path[0]=src;	

	enQueue(path);	
		
	while(front!=-1){
		i=0;
		path=deQueue();
		
		
		while(path[i]!=-1){
			i++;
		}
		
		if(path[i-1]==dest){
			u=0;
			results[k]=path;
			k++;
			printf("Bulunan Rota : ");
			while(path[u] < g->nodeCnt && path[u] > -1){
				printf("%d ",path[u]);
				u++;
			}
			cost=calculateCost(g,path,u);
			printf("\n");
			printf("Rota Maliyeti: %d \n",cost);
			
			
		}
		
			
		edges=edgeList(g,path[i-1]);	
		edgeCnt=arraySize(edges);
			
			
		for(m=0;m<edgeCnt;m++){
			cycleflag=0;
			newpath=allocatePath(g);
			
			for(j=0;j<i;j++){
				newpath[j]=path[j];
			}
			
			for(u=0;u<i;u++){
				if(newpath[u]==edges[m]){
					cycleflag=1;
					break;
				}
			}
			
			if(cycleflag!=1){
				newpath[i]=edges[m];
			} 
			else{
				continue;
			}
			
			
			if(path[i-1]!=dest){
			   enQueue(newpath);
			}				
			

				
				
	}
}
	
	
	
	
	
	
}







void connectedNodes(struct Graph* g){  // graf içindeki doðrudan baðlantýlý düðümleri yazdýran fonksiyon
	
	int i;
	int src;
	int dest;
	struct AdjListNode* temp;
	
	printf("Dogrudan bagli dugumler : \n");
	
	for(i=0;i<g->nodeCnt;i++){
		temp=g->array[i];
		src=i;
		while(temp!=NULL){
			dest=temp->id;
			temp=temp->next;
			printf("%d - %d \n",src,dest);
		}
	}

}

















int queue2[1000];
int front2 = -1;
int rear2 = -1;


void enQueue2(int item)  
{  
     
    if(rear2 == 999)  
    {  
        printf("\nOVERFLOW\n");  
        return;  
    }  
    if(front2 == -1 && rear2 == -1)  
    {  
        front2 = 0;  
        rear2 = 0;  
    }  
    else   
    {  
        rear2 = rear2+1;  
    }  
    queue2[rear2] = item;  
  //  printf("\nValue inserted ");  
      
}  
int deQueue2()  
{  
    int item;   
    if (front2 == -1 || front2 > rear2)  
    {  
        printf("\nUNDERFLOW\n");  
        return;  
              
    }  
    else  
    {  
        item = queue2[front2];  
        if(front2 == rear2)  
        {  
            front2 = -1;  
            rear2 = -1 ;  
        }  
        else   
        {  
            front2 = front2 + 1;  
        }  
    //    printf("\nvalue deleted ");  
    }  
      
    return item;
}  




struct Graph* addVertices(struct Graph* undirectedG,int src,int dest){
	
	struct AdjListNode* temp;
	int flag=0;
	
	temp=undirectedG->array[src];
	
	
	while(temp!=NULL){
		if(temp->id==dest){
			flag=1;
			break;
		}
		temp=temp->next;
	}
	
	if(flag!=1){
		temp=newAdjListNode(dest);
		temp->next=undirectedG->array[src];
		undirectedG->array[src]=temp;
	}
	
	flag=0;
	temp=undirectedG->array[dest];
	
	while(temp!=NULL){
		if(temp->id==src){
			flag=1;
			break;
		}
		temp=temp->next;
	}
	
	if(flag!=1){
		temp=newAdjListNode(src);
		temp->next=undirectedG->array[dest];
		undirectedG->array[dest]=temp;
	}
	
	return undirectedG;
	
}





struct Graph* createUndirectedGraph(struct Graph* g){
	
	int i;
	struct AdjListNode* temp;
	
	struct Graph* undirectedG= createGraph(50);
	undirectedG->nodeCnt=g->nodeCnt;
	
	for(i=0;i<g->nodeCnt;i++){
		temp=g->array[i];
		
		while(temp!=NULL){		
			undirectedG=addVertices(undirectedG,temp->id,i);
		//	printf("src : %d dest : %d \n",i,temp->id);
			temp=temp->next;
		}
				
	}
	
	return undirectedG;
	
}




int checkVisitedArray(int visited[],int size){ 
	
	int i;
	
	for(i=0;i<size;i++){
		if(visited[i]==-1){
			return 1;
		}
	}
		
	return 0;

}



int* components[50];
int componentCounter=0;


void bfs(struct Graph* g,int visited[]) {
	
	int currentNode;
	int adjNode;
    struct AdjListNode* temp;
    int* componentNodes;
    int i;
    int j;
    int componentNodeCnt;
    int recStartNode;
    int start;



    componentCounter=1;
    
   
   while(checkVisitedArray(visited,g->nodeCnt)){
   	i=0;
   	while(visited[i]!=-1){
   		i++;
	}
   	start=i;
   	componentNodeCnt=0;
    visited[start] = componentCounter;
    enQueue2(start);
    
    while (front2!=-1) {
    
      currentNode = deQueue2();
      //printf("Visited %d\n", currentNode);
      componentNodeCnt++;
      temp = g->array[currentNode];

      while (temp!=NULL) {
        adjNode = temp->id;

        if (visited[adjNode] == -1) {
          visited[adjNode] = componentCounter;
          enQueue2(adjNode);
         }
      temp = temp->next;
    }
  }
  

   componentCounter++;
  

 }
 
 
    printf("Baglantili bilesen sayisi : %d \n",componentCounter-1);
 
    
	    
    for(i=1;i<componentCounter;i++){
      
	  printf("Baglantili bilesen %d dugumleri : ",i);	
    
	  j=0;	
      while(j<g->nodeCnt){
	    if(visited[j]==i){
	  	  printf("%d ",j);
	    } 	 
 	  
        j++; 
      } 
    printf("\n");    	
    	
    	
	}
    

 
 
 
 
}





int connectedComponents(struct Graph* g){ // Parametre olarak verilen grafý undirected graf haline çevirip bfs yaparak baðlantýlý bileþenleri bulan fonksiyon.
	
	int visited[g->nodeCnt];
	int i;
	for(i=0;i<g->nodeCnt;i++){
		visited[i]=-1;
	}
	
	struct Graph* undirectedgraph;	
	undirectedgraph=createUndirectedGraph(g);
		
	bfs(undirectedgraph,visited);
	
	
}






void longestPath(struct Graph* g){ //Shortest path fonksiyonunu kullanarak en kýsa yollar arasýndan en uzununu bulan fonksiyon.
	
	int i,j,k;
	struct Path* paths=(struct Path*)malloc(10000*sizeof(struct Path));
	struct Path path_;
	int src;
	int dest;
	int cost=-999999;

	int longestPathIndex;
	
	k=0;
	cost=-999999;
	
	for(i=0;i<g->nodeCnt;i++){
		for(j=0;j<g->nodeCnt;j++){
			if(i==j){
				continue;
			}
			
			paths[k]=shortestPath(g,i,j);
		//	printf("src : %d  dest : %d  cost : %d \n",i,j,paths[k].cost);
			
			if(paths[k].cost!=99999 && paths[k].cost>cost){
				src=i;
				dest=j;
				cost=paths[k].cost;
			}
				
			k++;
		}
	}
	
	printf("En uzun yol: \n");
	printf("Kaynak dugum: %d  Hedef dugum: %d  Maliyet: %d  \n",src,dest,cost);
	
	
}







int main() 
{ 
    int i;
    int j;
    int* path;
    struct Graph* g= createGraph(50);
	g=readData(g);
	
	//Kullanýlacak fonksiyonu yorum satýrýndan/yorum satýrý bloðundan çýkarýp diðer fonksiyonlarý yorum satýrýna alýnýz.
	
	
   // printGraph(g);
    
   // connectedNodes(g);
    



   //connectedComponents(g);
 


    //paths(g,0,3);
 

   longestPath(g);
 
 
    /*
    struct Path path_;
    
    path_=shortestPath(g,0,15);
    
    
    if(path_.cost!=99999){
	
      printf("En kisa yol: ");
    
      for(i=0;i<g->nodeCnt;i++){
    	if(path_.path[i]!=-1){
    		printf("%d ",path_.path[i]);
		}
	  }
    
      printf("\nMaliyet : %d \n",path_.cost);
    
     }
     
     */
  
    

	
    return 0; 

} 



















