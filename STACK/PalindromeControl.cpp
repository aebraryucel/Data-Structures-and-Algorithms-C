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
	
	int i=0; //i --> size          j-->palindrom i�in kelimenin ortas�n�n indisi     makam  sekkes farikkiraf
	int j;//kelimenin yar�s�n�n indisini tuttu�umuz de�i�ken
	int k=0; //harfleri push pop yaparken kulland���m�z saya�
    char temp;
    temp=string[i];
	while(temp!='\0'){  //kelimenin harf say�s�n� hesapl�yoruz.i de�i�kenine at�yoruz.
		temp=string[i];
		i++;
	}
	i--; //d�ng�de 1 defa fazladan artt�rd���m�z i yi azalt�yoruz.
	
    if(i%2==0){   //e�er kelimenin harf say�s� �ift ise
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
	
	
    else if(i%2==1){ //e�er harf say�s� tek ise
    	j=i/2;
    	
    	while(k!=j){
    		push(string[k]);
    		k++;
		}
		
    	k++; //kelimeyi ortadan b�len harfi atlamak i�in k 'y� artt�r�yoruz.
    	
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



