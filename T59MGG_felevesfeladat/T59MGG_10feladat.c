#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
  
// Struktúra az üzenetsornak
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} uzenet;



int main()
{
    key_t key;
	char as[2], bs[3];
	int a, b;
    int msgid;
  
    // ftok kulcs generálás
    key = ftok("progfile", 65);
  
    // msgget az üzenetsor létrehozásához
    msgid = msgget(key, 0666 | IPC_CREAT);
    uzenet.mesg_type = 1;
  
  
  
	// Adatok megnyitása olvasásra a bemenet.txt-ből
	FILE* ptr;
 
	if ((ptr=fopen("bemenet.txt", "r")) == NULL){
       printf("Fajl megnyitasa sikertelen! A hiba oka:\n");
	   perror(0);
	   exit(1);
	}


	// Fájl tartalmának olvasása majd kiírása a memóriaszegmensbe, fájl pointer lezárása
    fgets(uzenet.mesg_text, 256, ptr);
	fclose(ptr);
	
	
	
    // msgsnd és msgrcv az üzenet küldésére és fogadására
    msgsnd(msgid, &uzenet, sizeof(uzenet), 0);
	msgrcv(msgid, &uzenet, sizeof(uzenet), 1, 0);
	
	
	// Üzenetből az első két szám karakterének kiolvasása, átalakítása
	memcpy(as, uzenet.mesg_text, 2);
	a=atoi(&as);


	// Üzenetből az utolsó két szám karakterének kiolvasása, átalakítása
	snprintf(bs, sizeof(bs), "%c%c", uzenet.mesg_text[strlen(uzenet.mesg_text)-2],uzenet.mesg_text[strlen(uzenet.mesg_text)-1]);
	b=atoi(bs);
	
	
	// A legnagyobb közös osztó kiválasztó algoritmusa
	int i, lko;


    for(i = 1; i <= a && i <= b; i++)
    {
        if(a % i == 0 && b % i == 0)
            lko = i;
    }

    printf("%d és %d legnagyobb kozos osztoja %d.\n", a, b, lko);
	
	
	
	// Az eredmeny.txt fájl megnyitása írásra
	
	if ((ptr=fopen("eredmeny.txt", "w")) == NULL){
       printf("Fajl megnyitasa sikertelen! A hiba oka:\n");
	   perror(0);
	   exit(1);
	}
	
	
	// Eredmény kiírása fájlba, file pointer lezárása
	fprintf(ptr, "%d, %d, %d", a, b, lko);
	close(ptr);
	
	
    return 0;
}