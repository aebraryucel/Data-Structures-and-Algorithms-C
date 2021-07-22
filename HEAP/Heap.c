#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Point{
	int x;
	int y;
};



double distance(int x,int y){ //Euclide distance'ýn (0,0) noktasýna göre hesaplanmasý
	
	return sqrt((x*x)+(y*y));
	
}




int size = 0;//heap'in anlýk boyutunu tutan deðiþken

void swap(struct Point* a, struct Point* b) {
  struct Point temp = *b;
  *b = *a;
  *a = temp;
}


void heapify(struct Point* heap, int i) {
  if (size == 1) {
    printf("Heapte tek eleman var!\n");
    return;
  } 
   else {
    
    int minIndex =i;
    int left = 2*i+1;
    int right = 2*i+2;
    
    if (left < size && distance(heap[left].x,heap[left].y) < distance(heap[minIndex].x,heap[minIndex].y)){
    	minIndex = left;
	}
      
    if (right < size && distance(heap[right].x,heap[right].y) < distance(heap[minIndex].x,heap[minIndex].y)){
    	minIndex = right;
	}
     

    if (minIndex != i) {
      swap(&heap[i], &heap[minIndex]);
      heapify(heap, minIndex);
    }
  }
}


void insert(struct Point* heap, struct Point newPoint) {
	int i;
  if (size==0) {
    heap[0]=newPoint;
    size+=1;
  } 
  else {
    heap[size] = newPoint;
    size += 1;
    for (i=size/2-1;i>=0;i--) {
      heapify(heap, i);
    }
  }
}


struct Point deleteRoot(struct Point* heap) {
  struct Point point; 	
  int i;
  point=heap[0];
  
  swap(&heap[0],&heap[size-1]);
  size -= 1;
  for (i=size/2-1; i>=0;i--) {
    heapify(heap,i);
  }
  
  return point;
}


void printHeap(struct Point* heap) {
	int i;
    for (i=0;i<size;i++){
  	printf("%d - %d \n", heap[i].x,heap[i].y);
    }
    
    printf("\n");
}






int main(){
	
	int pointCount;
	int x;
	int y;
	struct Point point;
	
	FILE* fp=fopen("Quiz4-Veri1.txt","r");
	if(fp==NULL){
		printf("Dosya acilamadi!\n");
		return -1;
	}
	
	fscanf(fp, "%d", &pointCount);
	
	struct Point* heap=(struct Point*)malloc(pointCount*sizeof(struct Point));
	
    while (((fscanf(fp, "%d;%d", &x,&y)) != EOF)){
    	
    	struct Point* point=(struct Point*)malloc(sizeof(struct Point));
    	point->x=x;
    	point->y=y;
    	insert(heap,*point);

    }
    	
    fclose(fp);	
	
	printf("Heap Baslangic Durumu: \n");
	printHeap(heap);
	printf("\n");
	
	while(size!=1){
		point=deleteRoot(heap);
		printf("Nokta Silindi %d - %d \n\n",point.x,point.y);
		printf("Heap Yeni Hali:\n");
	    printHeap(heap);
		
	}
	

	
	
	
}



