#include <stdio.h>
#include <stdlib.h>




struct node{
	int val;
	struct node* next;
	
};


void init(struct node* head)
{
    head = NULL;
}

 
 
struct node* push(struct node* top,int value){
 
 	
 	struct node* newN=(struct node*)malloc(sizeof(struct node));
 	if(newN==NULL){
 		printf("node icin yer ayrilamadi.");
 		exit(0);
 		
	 }
 	newN->val=value;
 	newN->next=top;
 	top=newN;
 	return top;
 }




int findSize(struct node* top){
	int count=0;
	
	if(top==NULL){
		return count;
	}
	
	struct node* current=top;
	
	while(current!=NULL){
		count++;
		current=current->next;
		
	}
	
	return count;
	
	
}




int search(struct node* top,int value){
	
	struct node* current=top;
	
	while(current!=NULL){
		
		if(current->val==value){
			return 1;
		}
		current=current->next;
		
	}
	
	return 0;
	
	
}



int isEqual(struct node* top1,struct node* top2){
	
	if(findSize(top1)==0 && findSize(top2)==0){   // ilk durum, ikisininde bos olmasý
		return 1;
	}
	
	if(findSize(top1)!=findSize(top2)){ //ikinci durum,farklý sayýda elemana sahipler.
		return 0;
	}
	
	
	                            //üçüncü durum, 0 dan farklý ayný sayýda elemana sahipler.
	struct node* current1=top1;
	struct node* current2=top2;
	
	
	
	while(current1!=NULL){
		
	if(search(top2,current1->val)==0){
		
		return 0;
	}
	
	current1=current1->next;	
		
	}

	return 1;
	
	
}


void printStack(struct node* top){
	
 struct node* current=top;
 
 while(current!=NULL){
 	
 	printf("%d ",current->val);
 	current=current->next;
 	
 }	
	


	
}





int main(){
	
	struct node* top1=NULL;
    struct node* top2=NULL;
	
	init(top1);
	init(top2);
	
	top1=push(top1,23);
	top1=push(top1,35);
	top1=push(top1,99);
	top1=push(top1,2);
	
	
	
	top2=push(top2,23);
	top2=push(top2,2);
	top2=push(top2,35);
	top2=push(top2,99);
	
	printStack(top1);
	printf("\n");
	printStack(top2);
	printf("\n");
	
	
	
	
	int a =isEqual(top1,top2);
	
	if(a==1){
		
		printf("stackler esit");
	}
	
	else{
		
		printf("stackler esit degil");
	}
	
	
	
	
	
	
	
	
	
}
