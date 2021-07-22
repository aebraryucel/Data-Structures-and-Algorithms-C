#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define CAPACITY 999
  

struct AdjListNode //adj listelerindeki düðüm
{ 
    int id; 
    struct AdjListNode* next; 
}; 
  

struct AdjList //adj listesi 
{ 
    struct AdjListNode *head;
    int id; //hangi id ye ait listenin tutulduðu
    
}; 
  

struct Graph 
{ 
    int currentsize; //graftaki adj listesi sayýsý
    struct AdjList* array; //adj listelerini tutan array
}; 


struct read{  //her satýr ile okunan verileri tuttuðumuz veri yapýsý
	char follower[10];
	char followed[10];
	
};
  
struct AdjListNode* newAdjListNode(int id) {  //adj listesi düðümü oluþturan fonksiyon
    struct AdjListNode* newNode =  (struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
    newNode->id = id; 
    newNode->next = NULL; 
    return newNode; 
} 



  
struct Graph* createGraph(int maxsize) { //graf oluþturan fonksiyon
    struct Graph* g = (struct Graph*) malloc(sizeof(struct Graph)); 
    g->currentsize = 0; 
  

    g->array = (struct AdjList*)malloc(maxsize*sizeof(struct AdjList)); 
  
 
    for (int i=0;i<maxsize;i++) 
        g->array[i].head = NULL;

  
    return g; 
} 
  

void printGraph(struct Graph* g) {  //grafý yazdýran fonksiyon
 
    for (int i=1;i<g->currentsize;i++) 
    { 
        struct AdjListNode* current = g->array[i].head; 
        printf("\n %d id li kullanicinin takip listesi : \n head ",g->array[i].id ); 
        while (current) 
        { 
            printf("-> %d", current->id); 
            current = current->next; 
        } 
        printf("\n"); 
    } 
} 


int search(int id,struct Graph* g){//verilen id ye ait adjacency listesinin grafta olup olmadýðýný kontrol eden yardýmcý fonksiyon
	
   int i=0;
   
   while(g->array[i].id!=0){
   	    if(g->array[i].id==id){
   	    	return 1;
		}
		i++;
   }
     
   return 0;
	
}



void addFollowerList(struct Graph* g,int followerId){ //grafa adj listesi ekleyen yardýmcý fonksiyon
	
    int i=0;
	
	while(g->array[i].id!=0){		
		i++;
	}	
	g->array[i].id=followerId;
	g->currentsize++;
	
		
}



void addFollowedNode(struct Graph* g,int followerId,int followedId){ //verilen adjacency listesine(follower) node(followed) ekleyen yardýmcý fonksiyon
	
	struct AdjListNode* node=newAdjListNode(followedId);

	
	int i=0;
	
	while(g->array[i].id!=followerId){		
		i++;
	}
	
	node->next=g->array[i].head;
	g->array[i].head=node;

	
	
}




void addEdge(struct Graph* g,int followerId,int followedId){  //verilen id lere göre grafa adjacency list(follower) ve adjacecency list node(followed) ekleyen fonksiyon
	
	
	

	if(search(followerId,g)){ //eðer aranan adj listesi grafta varsa followed listeye eklenir        
		addFollowedNode(g,followerId,followedId);//followed ý listeye ekle        	
						
	}
	else{  //eðer liste yoksa liste grafa eklenir ardýndan followed listeye eklenir.
        addFollowerList(g,followerId); //listeyi ekle
		addFollowedNode(g,followerId,followedId);//followed ý listeye ekle        		    
	}
	
	
	if(!search(followedId,g)){ //followed adj listesi yoksa eklenir.
		addFollowerList(g,followedId);//listeyi ekle
	}
	
	
	
	
	
	
}



struct Graph* readcsv(struct Graph* g){  //csv dosyasýný okuyarak graf yapýsýný oluþturan fonksiyon,csv dosyasýndaki satýrlar "struct read" veri yapýsýna okunur.Okunan deðerler integer'a çevrilir elde edilen deðerler id olarak kullanýlýr
	                                     //Bu id deðerleri için "addEdge" fonksiyonuyla grafta tutulan adjacency listesi olup olmadýðý kontrol edilir eðer yoksa eklenir varsa gerekli baðlantýlar yapýlýr.
    int followerId;
    int followedId;
    
    struct read* read=(struct read*)malloc(sizeof(struct read));  

	
	FILE* file=fopen("SNAgraph.csv","r");
	if(file==NULL){
		printf("Can't open file!\n");
		return g;
	}

	char buff[1024];
	int row_count=0;
	int field_count=0;
	
	int i=0;
	
	while(fgets(buff,10240,file)){

		field_count=0;
		row_count++;

		char* field=strtok(buff,",");
		while(field){
			if(field_count==0){
				strcpy(read->follower,field);
			}
			if(field_count==1){
				strcpy(read->followed,field);
			}
			
			field=strtok(NULL,",");
			field_count++;			
		}
		i++;
		
		followerId=atoi(read->follower);
        followedId=atoi(read->followed);
						
		addEdge(g,followerId,followedId);
	}

    fclose(file);		
	
	return g;
	
	
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int searchIndex(int id,struct Graph* g){ //Verilen id ye ait adj listesinin liste dizisindeki indeksini döndüren fonksiyon
	
   int i=0; 
   while(g->array[i].id!=0){
   	    if(g->array[i].id==id){
   	    	return i;
		}
		i++;
   }
     
    return -1;
	
}




int followedcounter(int id,struct Graph* g){  //verilen adj. listesindeki düðüm sayýsýný bulan fonksiyon,baðlantý sayýsý hesabýnda kullanýlýr.
	
  int count=0;
  int index=searchIndex(id,g);
  
  struct AdjListNode* current=g->array[index].head;
  
  while(current){
  	current=current->next;
  	count++;
  }
  
  return count;	
	
	
}


int followercounter(int id,struct Graph* g){ //verilen id nin diðer id lere ait adj listelerinde kaç baðlantýsý olduðunu bulan fonksiyon,baðlantý sayýsý hesabýnda kullanýlýr.
	int count=0;
    int index=searchIndex(id,g);
    struct AdjListNode* current;

    for(int i=0;i<g->currentsize;i++){
    	current=g->array[i].head;
    	while(current){
    		if(current->id==id){
    			count++;
			}
			current=current->next;
		}
    	
    	
	}
	
	return count;
	
}












int findMin(int linkList[10]){ //en fazla baðlantýya sahip 10 kullanýcýyý bulurken kullandýðýmýz verilen dizinin en küçük elemanýnýn indeksini bulan fonksiyon
	int min=linkList[0];
	int index=0;
	
	for(int i=1;i<10;i++){
		if(linkList[i]<=min){
			min=linkList[i];
			index=i;
		}
	}
	
	return index;
	
}


int idList[10]={0,0,0,0,0,0,0,0,0,0}; //en fazla baðlantýya sahip 10 kullanýcýnýn id lerinin tutan dizi.
int linkList[10]={0,0,0,0,0,0,0,0,0,0}; //en fazla baðlantýya sahip 10 kullanýcýnýn baðlantý sayýsýný tutan dizi , id ve list dizisi ortak indeksle kullanýlacak yani idList[0]'daki id'nin baðlantý listesi linkList[0]'da tutulacak


void TopTenLink(struct Graph* g){ //En fazla baðlantýya sahip 10 kullanýcýnýn id lerini ve baðlantý sayýsýný idList ve linkList dizilerinde tutan fonksiyon
                                  //Her bir id için takip ettiklerinin sayýsý,kaç kiþi tarafýndan takip edildiði sayýsý toplanarak baðlantý sayýsý bulunur.
                                  //Ve her id için baðlantý sayýsý hesaplanýrken en fazla 10 baðlantý sayýsýný tutan dizi güncellenir.
	
	int count;
	int index;
	int currentid;
		
	for(int i=1;i<g->currentsize;i++){
	 		
	count=followedcounter(g->array[i].id,g);
	count+=followercounter(g->array[i].id,g);
	index=findMin(linkList);
	
	if(count>linkList[index]){
		idList[index]=g->array[i].id;
		linkList[index]=count;
	}
		
	}
	
		
}


void insertionSort(int arr[], int n)  //medyan deðerini bulmak için kullanýlacak yardýmcý fonksiyon
{  
    int i, key, j;  
    for (i=1;i<n;i++) 
    {  
        key=arr[i];  
        j=i-1;  
  
        while(j>=0 && arr[j]>key) 
        {  
            arr[j+1]=arr[j];  
            j=j-1;  
        }  
        arr[j+1]=key;  
    }  
}  






void AvgAndMedian(struct Graph* g){ //ortalama ve medyan deðerlerini hesaplayan fonksiyon
                                    //Tüm baðlantý sayýlarý hesaplanýr ve kullanýcý sayýsýna bölünürek ortalama hesaplanýr,ardýndan baðlantý sayýlarýný tutan dizi sýralanarak medyan hesabý yapýlýr.
	
    float avg;
    int median;	
	
	
	int currentsize=g->currentsize;
	
	int linkcounts[currentsize];

	
	for(int i=1;i<currentsize;i++){ //her bir adj listesindeki baðlantý sayýlarýnýn sýrasýyla linkcounts dizisine yerleþtirilmesi
		
	    linkcounts[i]=followedcounter(g->array[i].id,g);
	    linkcounts[i]+=followercounter(g->array[i].id,g);


	}
		
    
    float sum=0;
    
    for(int j=1;j<g->currentsize;j++){	//ortalama deðerin hesaplanmasý
    sum=linkcounts[j]+sum;	
	}

	avg=sum/currentsize;
	printf("Average : %f \n",avg);    
	
	
	insertionSort(linkcounts,currentsize);	
	int medianIndex=currentsize/2;	
	median=linkcounts[medianIndex]; //medyan hesabý
	printf("Median : %d ",median);
	
	
}
 
 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//BFS için queue implementasyonu


int queue[CAPACITY];
unsigned int size  = 0;
unsigned int rear  = CAPACITY - 1;  
unsigned int front = 0;



int isFull()
{
    return (size == CAPACITY);
}


int isEmpty()
{
    return (size == 0);
}




int enqueue(int data)
{

    if (isFull()) 
    {
        return 0;
    }
    rear = (rear + 1) % CAPACITY;
    size++;
    queue[rear] = data;

    return 1;
}


int dequeue()
{
    int data = INT_MIN;

    if (isEmpty())
    {
        return INT_MIN;
    }

    data = queue[front];

    front = (front + 1) % CAPACITY;

    size--;

    return data;
}





struct AdjListNode* searchID(int id,struct Graph* g){ //Grafta verilen id ye ait bir adj listesinin head pointer'ýný döndürürür.  BFS'de kullanýlmak üzere yardýmcý fonksiyon.
	
   int i=0; 
   while(g->array[i].id!=0){
   	    if(g->array[i].id==id){
   	    	return g->array[i].head;
		}
		i++;
   }
     
    return NULL;
		
}


int followerIDs[2000];//followerlarýn ID lerini tutan dizi
int visitedIDs[2000];//ID lerin ziyaret edilip edilmediðini tutan dizi



void createFollowerArray(struct Graph* g){ //adj listelerini tutan dizide her indeksin hangi ID için  tutan diziyi oluþturan fonksiyon.
	
	
    for(int i=1;i<g->currentsize;i++){
		followerIDs[i]=g->array[i].id;  

	}

	
}


int findIndexOfId(int id,struct Graph* g){  //IDleri tutan dizide aranan ID'nin indeksini döndüren fonksiyon.
	
	for(int i=0;i<g->currentsize;i++){
		
		if(id==followerIDs[i]){
			return i;
		}
	}
	
	return -1;
	
}





int* findMinPath(struct Graph* g,int startID){ //BFS ile verilen id yi baþlangýç düðümü alarak diðer düðümlere olan minimum uzaklýklarý hesaplayýp dizi olarak döndüren fonksiyon
	
	struct AdjListNode* current=NULL;
	int qval;
	int i;
	
	struct path* prev;


	int currentfollowerIndex;
	int index;
	
	int* pathlengths=(int*)malloc((g->currentsize)*sizeof(int));
	
	for(int j=0;j<g->currentsize;j++){
		pathlengths[j]=999;
		visitedIDs[i]=0;
	}


	enqueue(startID);
	index=findIndexOfId(startID,g);
	visitedIDs[index]=1;//baþlangýç düðümünün visited yapýlmasý
	pathlengths[index]=0;

	
	while(!isEmpty()){
		
	    qval=dequeue();//ilk elemanýn sýradan alýnmasý 

	    
	    current=searchID(qval,g);//elde edilen ID nin adj listesine eriþme
        i=searchIndex(qval,g);
	    
		currentfollowerIndex=findIndexOfId(g->array[i].id,g);//bulunduðumuz listenin followerIDs dizisindeki indeksi
		
		
	    while(current){
	    	
	    	index=findIndexOfId(current->id,g);			
				    	
            if(!visitedIDs[index]){
            
	    	pathlengths[index]=pathlengths[currentfollowerIndex]+1;	
	        visitedIDs[index]=1;
	    	enqueue(current->id);
	    	
	    	
		   }
							
	    	current=current->next;
		}
	    		
	}
	return pathlengths;
	
}



void printOnePath(int id,struct Graph* g){  //id si verilen düðümün ulaþýlabilir tüm diðer düðümlere olan uzaklýðýný gösteren fonksiyon

    
	
	int* pathArray=findMinPath(g,id);
	for(int i=1;i<g->currentsize;i++){
		if(pathArray[i]!=999 && pathArray[i]!=0){
			printf("id:%d 's path length to id:%d  is %d",id,g->array[i].id,pathArray[i]);
			printf("\n");
		}

	}
	
	

}




void allPaths(struct Graph* g){ //tüm düðümlerin diðer düðümlere olan minimum uzaklýklarýný hesaplayýp yazdýran fonksiyon


	int id;
		
	for(int i=1;i<g->currentsize;i++){
		id=g->array[i].id;	
		printOnePath(id,g);					
	}	
		

	
}

 


int main() 
{ 

    setbuf(stdout, NULL);
    
    struct Graph* g= createGraph(2000);
	g=readcsv(g);
	



    TopTenLink(g);  
    for(int i=0;i<10;i++){
    	
    	printf("id-> %d   Linkcount->%d \n",idList[i],linkList[i]);
    	
	}

	
	AvgAndMedian(g);

//	printGraph(g);
	




		
//	createFollowerArray(g);	
	
//	printOnePath(8135,g);
// 	allPaths(g);

	
	

	/*
	
	for(int i=0;i<g->currentsize;i++){
		
		if(pathLengths[514][i]!=999 && pathLengths[514][i]!=0){
			printf("%d\n",pathLengths[514][i]);		
		}

		
	}
*/
	
    //printPathLengths(g,pathLengths);

	
    return 0; 

} 





