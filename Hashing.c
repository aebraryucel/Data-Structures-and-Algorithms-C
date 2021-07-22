#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct HashNode{
	char word[20];
};


const int c1=2;
const int c2=1;
const int m=16673; // 0.6 doluluk oraný ve 10000 eleman için m(hash tablo boyutu) deðeri 16666'dan büyük en küçük asal sayý olmalýdýr. Bu da 16673'tür.

char alphabet[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'}; 



int calculateIndex(int key,int i){ //stringten elde edilen key deðeri için index hesabý yapan fonksiyon, i ve key parametreleri alýr ve elde edilen index deðerini döndürür.
	int index;// hesaplanýlan index deðerini tutan deðiþken.
		
	index=key+c1*i+c2*i*i;
	
	index=(index+i*i)%m;
	    	
	
	return index;
	
}


struct HashNode* createHashTable(struct HashNode* hashtable){ // smallDictionary.txt yi okuyup hash tablosu oluþturan fonksiyon.  main fonksiyonda initialize edilen hashtablosunu parametre olarak alýr oluþturulan hash tablosunu döndürür.

	int i;//hash fonksiyonunda index hesaplanýrken kullanýlan deðiþken
	int j;//döngü deðiþkeni
	char buf[100];// dosyadan okunan kelimeleri tutan buffer
	int index;	//keyden elde edilen indexi tutan deðiþken
	FILE* fp; 
	int key;//stringten elde edilen keyi tutan deðiþken
	
	if ((fp = fopen("SmallDictionary.txt", "r")) == NULL) {
        printf("Error! File cannot be opened.");
        exit(1);
    }	

    while (fgets(buf,1000, fp)!=NULL){  	
        i=0;
    
	    buf[strcspn(buf, "\n")] = 0;	//Okunan kelimenin sonundan \n karakterini siler.
    
        for(j=0;j < strlen(buf); j++){  //okunan kelimelerin büyük harfe çevrilmesi
    	    buf[j]=toupper(buf[j]);	
	    }   	
    		
        for(j=key=0;j < strlen(buf); j++){ //kelimelerdeki karakterlerden key deðeri elde edilmesi
        	key += ('a'- buf[j])*26*j;	
	    }	
    
    	
Loop1:	
		index=calculateIndex(key,i); // kelimeden elde edilen key deðeri calculateIndex fonksiyonuna i deðeriyle birlikte gönderilerek index hesaplanýr.
		
	    
		if(!strcmp(hashtable[index].word,"-")){ //eðer hash tablosunda boþ bir yere rastlamýþsak kelime eklenir.
		    strcpy(hashtable[index].word,buf); 
	    }
	    else{ //eðer boþ bir yere gelmemiþsek i arttýrýlarak tekrar index hesabý yapýlmasý için Loop1 etiketine gidilir.
		    i++;
		    goto Loop1;

	    }
	    		
	}
	
   return hashtable;

}



void recommendWord(struct HashNode* hashtable,char word[]){ // Parametre olarak hash tablosu ve aranan kelimeyi alarak ,hash tablosunda aranan kelimeye benzer kelimeleri (varsa) ekrana yazdýran fonksiyon.
	int i; //döngü deðiþkeni
	int j;//döngü deðiþkeni
	int result; // searchWord fonksiyonundan gelen sonucu tutan deðiþken
	char temp;// geçici karakter tutan deðiþken
	
	for(i=0;i < strlen(word); i++){ //deðiþkenin her harfinin sýrayla deðiþtirilmesi için döngü
		temp=word[i];//deðiþtirilecek harfin sonradan yerine konulmasý için geçici deðiþkende tutulmasý 
		
		for(j=0;j < 26;j++){ //deðiþtirilen harfin alfabedeki her harfle sýrasýyla deðiþtirilmesi için döngü

			word[i]=alphabet[j];// kelimenin i. harfinin alfabedeki j. harfle deðiþtirilmesi
			result=searchWord(hashtable,word); //deðiþtirilen kelimenin hash tablosunda aranmasý
			if(result!=-1){ 
				printf("Onerilen Kelime -> %s \n",hashtable[result].word);
			}
			
		}
	      
    	word[i]=temp;// i. harfin alfabedeki harflerle deðiþtirildikten sonra yerine konulmasý   örneðin  ABLE kelimesinde BBLE,CBLE,DBLE arandýktan sonra ACLE,ADLE,AFLE gibi kelimenin 2. harfinin deðiþtirilip aranmasý için kelimenin tekrar ABLE yapýlmasý.	
	}  	
	
	
}




int searchWord(struct HashNode* hashtable,char word[]){  // Hash tablosunu ve aranan kelimeyi parametre olarak alan, kelimeyi bulursa hash tablosundaki indexini,bulamaz ise -1 döndüren fonksiyon.
	

	int key=0; //kelimeden elde edilen key deðeri için tutulan deðiþken
	int index;//key ve i deðeriyle hesaplanan index deðeri için tutulan deðiþken
	int i=0;  // hash fonksiyonlarýnda kullanýlan i deðiþkeni
	int j; //döngü deðiþkeni
	
	
	for(j=0;j < strlen(word); j++){  //okunan kelimelerin büyük harfe çevrilmesi
    	word[j]=toupper(word[j]);	
	}   	
    		
    for(j=key=0;j < strlen(word); j++){ //kelimelerdeki karakterlerden key deðeri elde edilmesi
    	key += ('a'- word[j])*26*j;	
	}
	


Loop2:	
	index=calculateIndex(key,i); // kelimeden elde edilen key deðeri calculateIndex fonksiyonuna i deðeriyle birlikte gönderilerek index hesaplanýr.
	
	if(i>m-1 || !strcmp(hashtable[index].word,"-")){ //   Hash tablosunda boþ bir yer bulursak veya i deðeri tablo boyutunu geçerse kelimemiz hash tablosunda yok demektir. -1 deðeri döndürülür.
		//printf("step number : %d \n",i+1);
		return -1;
	}
	
	if(!strcmp(hashtable[index].word,word)){ //  Hash tablosunda aranan kelimenin bulunmasý ve index deðerinin döndürülmesi.
		//printf("step number : %d \n",i+1);
		return index;
	}
	else{ //  eðer tabloda boþ bir yere rastlamamýþsak ve aradýðýmýz kelimeyi de bulamamýþsak i deðeri arttýrýlýp indexin tekrar hesaplanmasý için Loop2 etiketine gidilir.
		i++;
		goto Loop2;
		
	}
	
	
	
}



int stepcount;//ikili arama yapýnca adým sayýsýný tutan deðiþken

int binarySearch(struct HashNode* linearDictionary, int l, int r, char word[],int stepcnt)  // sözlük yapýsný sýralý bir þekilde tutan linearDictionary dizisini,dizinin sol ve sað indisini,aranan kelimeyi ve fonksiyon her çaðrýldýðýndaki adým sayýsýný parametre olarak ikili arama yapan fonksiyon. 
{
	int mid;
	
    if (r >= l) {
        mid = l + (r - l) / 2;
        

        if (!strcmp(linearDictionary[mid].word,word)){
        	stepcount=stepcnt;
            return mid;
		}

        
        if (strcmp(linearDictionary[mid].word,word)>0){
        	stepcnt++;
            return binarySearch(linearDictionary, l, mid - 1, word,stepcnt);        	
		}

        stepcnt++;
        return binarySearch(linearDictionary, mid + 1, r, word,stepcnt);
    }
  
    return -1;
}







int main(){
	
	int i;
	char word[30];
	int result;
	
	struct HashNode* hashtable=(struct HashNode*)malloc(m*sizeof(struct HashNode)); 
	

	
	for(i=0;i<16673;i++){ //hashtablosundaki boþ alanlarýn '-' olarak initialize edilmesi.
		hashtable[i].word[0]='-';
	}
	
	hashtable=createHashTable(hashtable);	
	
	
	printf("**********HARF YAZIM KONTROLU PROGRAMI*****************\n");
	
	printf("Aramak istediginiz kelimeyi giriniz: \n");
	scanf("%s",word);
	
	result=searchWord(hashtable,word);
	if(result==-1){
		printf("Aradiginiz kelime bulunamadi. Sozlukte olan olasi oneriler listeleniyor...\n");
		recommendWord(hashtable,word);
	}
	
	if(result!=-1){
	    printf("Kelime dogru yazilmistir. \n");
    }
	free(hashtable);
	
	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   // IKILI ARAMA ILE ALAKALI KISIM - HASH TABLOSU ILE ILGILI ISLEM YAPARKEN BU KISMI YORUMA ALINIZ

/*
    int j;   
	struct HashNode* linearDictionary=(struct HashNode*)malloc(10000*sizeof(struct HashNode));
	FILE* fp;
	int index=0;
	char buf[100];
	char word2[20];
	
	
	if ((fp = fopen("SmallDictionary.txt", "r")) == NULL) {
        printf("Error! File cannot be opened.");
        exit(1);
    }
    
	while (fgets(buf,1000, fp)!=NULL){  	
        
    
	    buf[strcspn(buf, "\n")] = 0;	//Okunan kelimenin sonundan \n karakterini siler.
    
        for(j=0;j < strlen(buf); j++){  //okunan kelimelerin büyük harfe çevrilmesi
    	    buf[j]=toupper(buf[j]);	
	    } 
		
	
    	strcpy(linearDictionary[index].word,buf);
		index++;	
	}
	
	while(1){
	
	printf("Binary Search ile aranacak kelimeyi giriniz: \n");
	scanf("%s",&word2);
	
	for(j=0;j < strlen(word2); j++){  //okunan kelimelerin büyük harfe çevrilmesi
    	    word2[j]=toupper(word2[j]);	
    }
	
	

	
	binarySearch(linearDictionary,0,10000,word2,0);
	printf("Aranan kelime icin adim sayisi : %d \n",stepcount);

}
	
   free(linearDictionary);
	*/
}

