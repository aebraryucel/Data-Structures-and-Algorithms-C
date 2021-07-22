#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct HashNode{
	char word[20];
};


const int c1=2;
const int c2=1;
const int m=16673; // 0.6 doluluk oran� ve 10000 eleman i�in m(hash tablo boyutu) de�eri 16666'dan b�y�k en k���k asal say� olmal�d�r. Bu da 16673't�r.

char alphabet[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'}; 



int calculateIndex(int key,int i){ //stringten elde edilen key de�eri i�in index hesab� yapan fonksiyon, i ve key parametreleri al�r ve elde edilen index de�erini d�nd�r�r.
	int index;// hesaplan�lan index de�erini tutan de�i�ken.
		
	index=key+c1*i+c2*i*i;
	
	index=(index+i*i)%m;
	    	
	
	return index;
	
}


struct HashNode* createHashTable(struct HashNode* hashtable){ // smallDictionary.txt yi okuyup hash tablosu olu�turan fonksiyon.  main fonksiyonda initialize edilen hashtablosunu parametre olarak al�r olu�turulan hash tablosunu d�nd�r�r.

	int i;//hash fonksiyonunda index hesaplan�rken kullan�lan de�i�ken
	int j;//d�ng� de�i�keni
	char buf[100];// dosyadan okunan kelimeleri tutan buffer
	int index;	//keyden elde edilen indexi tutan de�i�ken
	FILE* fp; 
	int key;//stringten elde edilen keyi tutan de�i�ken
	
	if ((fp = fopen("SmallDictionary.txt", "r")) == NULL) {
        printf("Error! File cannot be opened.");
        exit(1);
    }	

    while (fgets(buf,1000, fp)!=NULL){  	
        i=0;
    
	    buf[strcspn(buf, "\n")] = 0;	//Okunan kelimenin sonundan \n karakterini siler.
    
        for(j=0;j < strlen(buf); j++){  //okunan kelimelerin b�y�k harfe �evrilmesi
    	    buf[j]=toupper(buf[j]);	
	    }   	
    		
        for(j=key=0;j < strlen(buf); j++){ //kelimelerdeki karakterlerden key de�eri elde edilmesi
        	key += ('a'- buf[j])*26*j;	
	    }	
    
    	
Loop1:	
		index=calculateIndex(key,i); // kelimeden elde edilen key de�eri calculateIndex fonksiyonuna i de�eriyle birlikte g�nderilerek index hesaplan�r.
		
	    
		if(!strcmp(hashtable[index].word,"-")){ //e�er hash tablosunda bo� bir yere rastlam��sak kelime eklenir.
		    strcpy(hashtable[index].word,buf); 
	    }
	    else{ //e�er bo� bir yere gelmemi�sek i artt�r�larak tekrar index hesab� yap�lmas� i�in Loop1 etiketine gidilir.
		    i++;
		    goto Loop1;

	    }
	    		
	}
	
   return hashtable;

}



void recommendWord(struct HashNode* hashtable,char word[]){ // Parametre olarak hash tablosu ve aranan kelimeyi alarak ,hash tablosunda aranan kelimeye benzer kelimeleri (varsa) ekrana yazd�ran fonksiyon.
	int i; //d�ng� de�i�keni
	int j;//d�ng� de�i�keni
	int result; // searchWord fonksiyonundan gelen sonucu tutan de�i�ken
	char temp;// ge�ici karakter tutan de�i�ken
	
	for(i=0;i < strlen(word); i++){ //de�i�kenin her harfinin s�rayla de�i�tirilmesi i�in d�ng�
		temp=word[i];//de�i�tirilecek harfin sonradan yerine konulmas� i�in ge�ici de�i�kende tutulmas� 
		
		for(j=0;j < 26;j++){ //de�i�tirilen harfin alfabedeki her harfle s�ras�yla de�i�tirilmesi i�in d�ng�

			word[i]=alphabet[j];// kelimenin i. harfinin alfabedeki j. harfle de�i�tirilmesi
			result=searchWord(hashtable,word); //de�i�tirilen kelimenin hash tablosunda aranmas�
			if(result!=-1){ 
				printf("Onerilen Kelime -> %s \n",hashtable[result].word);
			}
			
		}
	      
    	word[i]=temp;// i. harfin alfabedeki harflerle de�i�tirildikten sonra yerine konulmas�   �rne�in  ABLE kelimesinde BBLE,CBLE,DBLE arand�ktan sonra ACLE,ADLE,AFLE gibi kelimenin 2. harfinin de�i�tirilip aranmas� i�in kelimenin tekrar ABLE yap�lmas�.	
	}  	
	
	
}




int searchWord(struct HashNode* hashtable,char word[]){  // Hash tablosunu ve aranan kelimeyi parametre olarak alan, kelimeyi bulursa hash tablosundaki indexini,bulamaz ise -1 d�nd�ren fonksiyon.
	

	int key=0; //kelimeden elde edilen key de�eri i�in tutulan de�i�ken
	int index;//key ve i de�eriyle hesaplanan index de�eri i�in tutulan de�i�ken
	int i=0;  // hash fonksiyonlar�nda kullan�lan i de�i�keni
	int j; //d�ng� de�i�keni
	
	
	for(j=0;j < strlen(word); j++){  //okunan kelimelerin b�y�k harfe �evrilmesi
    	word[j]=toupper(word[j]);	
	}   	
    		
    for(j=key=0;j < strlen(word); j++){ //kelimelerdeki karakterlerden key de�eri elde edilmesi
    	key += ('a'- word[j])*26*j;	
	}
	


Loop2:	
	index=calculateIndex(key,i); // kelimeden elde edilen key de�eri calculateIndex fonksiyonuna i de�eriyle birlikte g�nderilerek index hesaplan�r.
	
	if(i>m-1 || !strcmp(hashtable[index].word,"-")){ //   Hash tablosunda bo� bir yer bulursak veya i de�eri tablo boyutunu ge�erse kelimemiz hash tablosunda yok demektir. -1 de�eri d�nd�r�l�r.
		//printf("step number : %d \n",i+1);
		return -1;
	}
	
	if(!strcmp(hashtable[index].word,word)){ //  Hash tablosunda aranan kelimenin bulunmas� ve index de�erinin d�nd�r�lmesi.
		//printf("step number : %d \n",i+1);
		return index;
	}
	else{ //  e�er tabloda bo� bir yere rastlamam��sak ve arad���m�z kelimeyi de bulamam��sak i de�eri artt�r�l�p indexin tekrar hesaplanmas� i�in Loop2 etiketine gidilir.
		i++;
		goto Loop2;
		
	}
	
	
	
}



int stepcount;//ikili arama yap�nca ad�m say�s�n� tutan de�i�ken

int binarySearch(struct HashNode* linearDictionary, int l, int r, char word[],int stepcnt)  // s�zl�k yap�sn� s�ral� bir �ekilde tutan linearDictionary dizisini,dizinin sol ve sa� indisini,aranan kelimeyi ve fonksiyon her �a�r�ld���ndaki ad�m say�s�n� parametre olarak ikili arama yapan fonksiyon. 
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
	

	
	for(i=0;i<16673;i++){ //hashtablosundaki bo� alanlar�n '-' olarak initialize edilmesi.
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
    
        for(j=0;j < strlen(buf); j++){  //okunan kelimelerin b�y�k harfe �evrilmesi
    	    buf[j]=toupper(buf[j]);	
	    } 
		
	
    	strcpy(linearDictionary[index].word,buf);
		index++;	
	}
	
	while(1){
	
	printf("Binary Search ile aranacak kelimeyi giriniz: \n");
	scanf("%s",&word2);
	
	for(j=0;j < strlen(word2); j++){  //okunan kelimelerin b�y�k harfe �evrilmesi
    	    word2[j]=toupper(word2[j]);	
    }
	
	

	
	binarySearch(linearDictionary,0,10000,word2,0);
	printf("Aranan kelime icin adim sayisi : %d \n",stepcount);

}
	
   free(linearDictionary);
	*/
}

