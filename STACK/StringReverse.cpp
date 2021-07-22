#include <stdio.h>
#include <stdlib.h>


struct stackn{
	char data;
	struct stackn* next;
	
};



struct stackn* top=NULL;





void push(char data){
	
	struct stackn* newN=(struct stackn*)malloc(sizeof(struct stackn));
	newN->data=data;
	
	if(top==NULL){
		top=newN;
		newN->next=NULL;
		return;
	}
	
	
	newN->next=top;
	top=newN;
	return;
	
	
}

char pop(){
	
	char retc;
	
	if(top==NULL){
		return NULL;
	}
	
    retc=top->data;
	struct stackn* temp=top;
	top=top->next;
	free(temp);
	
	return retc;
	
}


void reverse(){
	char string[30];

	 
	char temp;
	int count=0;
	
	printf("cevrilecek metni girin:\n");
	scanf("%s",string);

	
	temp=string[0];
	while(temp!='\0'){
		temp=string[count];
		push(temp);
		count++;
	}
	
	pop();
	
	for(int i=0;i<count;i++){
		string[i]=pop();
	}
	
	
	printf("\nCevrilmis string: %s",string);
	
	
}



int main(){
	
	
	reverse();
	
	
	
	
	
	
}

