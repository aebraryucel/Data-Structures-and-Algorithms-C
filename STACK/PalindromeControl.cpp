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



int palindrom(){
	
	char string[30];
	
	printf("kontrol metnini girin:\n");
	scanf("%s",string);
	
	int i=0; //i --> size          j-->palindrom için kelimenin ortasýnýn indisi     makam  sekkes farikkiraf
	int j;//kelimenin yarýsýnýn indisini tuttuðumuz deðiþken
	int k=0; //harfleri push pop yaparken kullandýðýmýz sayaç
    char temp;
    temp=string[i];
	while(temp!='\0'){  //kelimenin harf sayýsýný hesaplýyoruz.i deðiþkenine atýyoruz.
		temp=string[i];
		i++;
	}
	i--; //döngüde 1 defa fazladan arttýrdýðýmýz i yi azaltýyoruz.
	
    if(i%2==0){   //eðer kelimenin harf sayýsý çift ise
    	j=i/2;
    	while(k!=j){
    		push(string[k]);
    		k++;
		}
    	
    	while(k!=i){
    		if(string[k]!=pop()){
    			return -1;
			}
    		k++;
    		
		}
		return 1;
	}
	
	
    else if(i%2==1){ //eðer harf sayýsý tek ise
    	j=i/2;
    	
    	while(k!=j){
    		push(string[k]);
    		k++;
		}
		
    	k++; //kelimeyi ortadan bölen harfi atlamak için k 'yý arttýrýyoruz.
    	
    	while(k!=i){
    		if(string[k]!=pop()){
    			return -1;
			}
    		k++;
		}
    	return 1;
    	
	}
	
	
}




int main(){
	
	int r=palindrom();
	
	if(r==1){
		printf("kelime palindrom!\n");
	}
	else{
		printf("kelime palindrom degil!\n");
	}
	
	
	
	
}



