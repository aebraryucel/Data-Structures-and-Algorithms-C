#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define CAPACITY 999
  

struct AdjListNode //adj listelerindeki d���m
{ 
    int id; 
    struct AdjListNode* next; 
}; 
  

struct AdjList //adj listesi 
{ 
    struct AdjListNode *head;
    int id; //hangi id ye ait listenin tutuldu�u
    
}; 
  

struct Graph 
{ 
    int currentsize; //graftaki adj listesi say�s�
    struct AdjList* array; //adj listelerini tutan array
}; 


struct read{  //her sat�r ile okunan verileri tuttu�umuz veri yap�s�
	char follower[10];
	char followed[10];
	
};
  
struct AdjListNode* newAdjListNode(int id) {  //adj listesi d���m� olu�turan fonksiyon
    struct AdjListNode* newNode =  (struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
    newNode->id = id; 
    newNode->next = NULL; 
    return newNode; 
} 



  
struct Graph* createGraph(int maxsize) { //graf olu�turan fonksiyon
    struct Graph* g = (struct Graph*) malloc(sizeof(struct Graph)); 
    g->currentsize = 0; 
  

    g->array = (struct AdjList*)malloc(maxsize*sizeof(struct AdjList)); 
  
 
    for (int i=0;i<maxsize;i++) 
        g->array[i].head = NULL;

  
    return g; 
} 
  

void printGraph(struct Graph* g) {  //graf� yazd�ran fonksiyon
 
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


int search(int id,struct Graph* g){//verilen id ye ait adjacency listesinin grafta olup olmad���n� kontrol eden yard�mc� fonksiyon
	
   int i=0;
   
   while(g->array[i].id!=0){
   	    if(g->array[i].id==id){
   	    	return 1;
		}
		i++;
   }
     
   return 0;
	
}



void addFollowerList(struct Graph* g,int followerId){ //grafa adj listesi ekleyen yard�mc� fonksiyon
	
    int i=0;
	
	while(g->array[i].id!=0){		
		i++;
	}	
	g->array[i].id=followerId;
	g->currentsize++;
	
		
}



void addFollowedNode(struct Graph* g,int followerId,int followedId){ //verilen adjacency listesine(follower) node(followed) ekleyen yard�mc� fonksiyon
	
	struct AdjListNode* node=newAdjListNode(followedId);

	
	int i=0;
	
	while(g->array[i].id!=followerId){		
		i++;
	}
	
	node->next=g->array[i].head;
	g->array[i].head=node;

	
	
}




void addEdge(struct Graph* g,int followerId,int followedId){  //verilen id lere g�re grafa adjacency list(follower) ve adjacecency list node(followed) ekleyen fonksiyon
	
	
	

	if(search(followerId,g)){ //e�er aranan adj listesi grafta varsa followed listeye eklenir        
		addFollowedNode(g,followerId,followedId);//followed � listeye ekle        	
						
	}
	else{  //e�er liste yoksa liste grafa eklenir ard�ndan followed listeye eklenir.
        addFollowerList(g,followerId); //listeyi ekle
		addFollowedNode(g,followerId,followedId);//followed � listeye ekle        		    
	}
	
	
	if(!search(followedId,g)){ //followed adj listesi yoksa eklenir.
		addFollowerList(g,followedId);//listeyi ekle
	}
	
	
	
	
	
	
}



struct Graph* readcsv(struct Graph* g){  //csv dosyas�n� okuyarak graf yap�s�n� olu�turan fonksiyon,csv dosyas�ndaki sat�rlar "struct read" veri yap�s�na okunur.Okunan de�erler integer'a �evrilir elde edilen de�erler id olarak kullan�l�r
	                                     //Bu id de�erleri i�in "addEdge" fonksiyonuyla grafta tutulan adjacency listesi olup olmad��� kontrol edilir e�er yoksa eklenir varsa gerekli ba�lant�lar yap�l�r.
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


int searchIndex(int id,struct Graph* g){ //Verilen id ye ait adj listesinin liste dizisindeki indeksini d�nd�ren fonksiyon
	
   int i=0; 
   while(g->array[i].id!=0){
   	    if(g->array[i].id==id){
   	    	return i;
		}
		i++;
   }
     
    return -1;
	
}




int followedcounter(int id,struct Graph* g){  //verilen adj. listesindeki d���m say�s�n� bulan fonksiyon,ba�lant� say�s� hesab�nda kullan�l�r.
	
  int count=0;
  int index=searchIndex(id,g);
  
  struct AdjListNode* current=g->array[index].head;
  
  while(current){
  	current=current->next;
  	count++;
  }
  
  return count;	
	
	
}


int followercounter(int id,struct Graph* g){ //verilen id nin di�er id lere ait adj listelerinde ka� ba�lant�s� oldu�unu bulan fonksiyon,ba�lant� say�s� hesab�nda kullan�l�r.
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












int findMin(int linkList[10]){ //en fazla ba�lant�ya sahip 10 kullan�c�y� bulurken kulland���m�z verilen dizinin en k���k eleman�n�n indeksini bulan fonksiyon
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


int idList[10]={0,0,0,0,0,0,0,0,0,0}; //en fazla ba�lant�ya sahip 10 kullan�c�n�n id lerinin tutan dizi.
int linkList[10]={0,0,0,0,0,0,0,0,0,0}; //en fazla ba�lant�ya sahip 10 kullan�c�n�n ba�lant� say�s�n� tutan dizi , id ve list dizisi ortak indeksle kullan�lacak yani idList[0]'daki id'nin ba�lant� listesi linkList[0]'da tutulacak


void TopTenLink(struct Graph* g){ //En fazla ba�lant�ya sahip 10 kullan�c�n�n id lerini ve ba�lant� say�s�n� idList ve linkList dizilerinde tutan fonksiyon
                                  //Her bir id i�in takip ettiklerinin say�s�,ka� ki�i taraf�ndan takip edildi�i say�s� toplanarak ba�lant� say�s� bulunur.
                                  //Ve her id i�in ba�lant� say�s� hesaplan�rken en fazla 10 ba�lant� say�s�n� tutan dizi g�ncellenir.
	
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


void insertionSort(int arr[], int n)  //medyan de�erini bulmak i�in kullan�lacak yard�mc� fonksiyon
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






void AvgAndMedian(struct Graph* g){ //ortalama ve medyan de�erlerini hesaplayan fonksiyon
                                    //T�m ba�lant� say�lar� hesaplan�r ve kullan�c� say�s�na b�l�n�rek ortalama hesaplan�r,ard�ndan ba�lant� say�lar�n� tutan dizi s�ralanarak medyan hesab� yap�l�r.
	
    float avg;
    int median;	
	
	
	int currentsize=g->currentsize;
	
	int linkcounts[currentsize];

	
	for(int i=1;i<currentsize;i++){ //her bir adj listesindeki ba�lant� say�lar�n�n s�ras�yla linkcounts dizisine yerle�tirilmesi
		
	    linkcounts[i]=followedcounter(g->array[i].id,g);
	    linkcounts[i]+=followercounter(g->array[i].id,g);


	}
		
    
    float sum=0;
    
    for(int j=1;j<g->currentsize;j++){	//ortalama de�erin hesaplanmas�
    sum=linkcounts[j]+sum;	
	}

	avg=sum/currentsize;
	printf("Average : %f \n",avg);    
	
	
	insertionSort(linkcounts,currentsize);	
	int medianIndex=currentsize/2;	
	median=linkcounts[medianIndex]; //medyan hesab�
	printf("Median : %d ",median);
	
	
}
 
 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//BFS i�in queue implementasyonu


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





struct AdjListNode* searchID(int id,struct Graph* g){ //Grafta verilen id ye ait bir adj listesinin head pointer'�n� d�nd�r�r�r.  BFS'de kullan�lmak �zere yard�mc� fonksiyon.
	
   int i=0; 
   while(g->array[i].id!=0){
   	    if(g->array[i].id==id){
   	    	return g->array[i].head;
		}
		i++;
   }
     
    return NULL;
		
}


int followerIDs[2000];//followerlar�n ID lerini tutan dizi
int visitedIDs[2000];//ID lerin ziyaret edilip edilmedi�ini tutan dizi



void createFollowerArray(struct Graph* g){ //adj listelerini tutan dizide her indeksin hangi ID i�in  tutan diziyi olu�turan fonksiyon.
	
	
    for(int i=1;i<g->currentsize;i++){
		followerIDs[i]=g->array[i].id;  

	}

	
}


int findIndexOfId(int id,struct Graph* g){  //IDleri tutan dizide aranan ID'nin indeksini d�nd�ren fonksiyon.
	
	for(int i=0;i<g->currentsize;i++){
		
		if(id==followerIDs[i]){
			return i;
		}
	}
	
	return -1;
	
}





int* findMinPath(struct Graph* g,int startID){ //BFS ile verilen id yi ba�lang�� d���m� alarak di�er d���mlere olan minimum uzakl�klar� hesaplay�p dizi olarak d�nd�ren fonksiyon
	
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
	visitedIDs[index]=1;//ba�lang�� d���m�n�n visited yap�lmas�
	pathlengths[index]=0;

	
	while(!isEmpty()){
		
	    qval=dequeue();//ilk eleman�n s�radan al�nmas� 

	    
	    current=searchID(qval,g);//elde edilen ID nin adj listesine eri�me
        i=searchIndex(qval,g);
	    
		currentfollowerIndex=findIndexOfId(g->array[i].id,g);//bulundu�umuz listenin followerIDs dizisindeki indeksi
		
		
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



void printOnePath(int id,struct Graph* g){  //id si verilen d���m�n ula��labilir t�m di�er d���mlere olan uzakl���n� g�steren fonksiyon

    
	
	int* pathArray=findMinPath(g,id);
	for(int i=1;i<g->currentsize;i++){
		if(pathArray[i]!=999 && pathArray[i]!=0){
			printf("id:%d 's path length to id:%d  is %d",id,g->array[i].id,pathArray[i]);
			printf("\n");
		}

	}
	
	

}




void allPaths(struct Graph* g){ //t�m d���mlerin di�er d���mlere olan minimum uzakl�klar�n� hesaplay�p yazd�ran fonksiyon


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





