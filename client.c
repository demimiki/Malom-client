#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

#define INIT_STEPS 9

typedef struct{
	int state;
	int lepesek[4];
}POZ;

POZ jatekter[24];

void drawTable(){
	printf("%d-----%d-----%d\n",jatekter[0].state,jatekter[1].state,jatekter[2].state);
	printf("|     |     |\n");
	printf("| %d---%d---%d |\n",jatekter[8].state,jatekter[9].state,jatekter[10].state);
	printf("| |   |   | |\n");
	printf("| | %d-%d-%d | |\n",jatekter[16].state,jatekter[17].state,jatekter[18].state);
	printf("| | |   | | |\n");
	printf("%d-%d-%d   %d-%d-%d\n",jatekter[7].state,jatekter[15].state,jatekter[23].state,jatekter[19].state,jatekter[11].state,jatekter[3].state);
	printf("| | |   | | |\n");
	printf("| | %d-%d-%d | |\n",jatekter[22].state,jatekter[21].state,jatekter[20].state);
	printf("| |   |   | |\n");
	printf("| %d---%d---%d |\n",jatekter[14].state,jatekter[13].state,jatekter[12].state);
	printf("|     |     |\n");
	printf("%d-----%d-----%d\n",jatekter[6].state,jatekter[5].state,jatekter[4].state);
}

void init(){
	for(int i=0;i<24;i++){
		jatekter[i].state=0;
		for(int j=0;j<4;j++)
			jatekter[i].lepesek[j]=-1;
	}
	
	jatekter[0].lepesek[0]=1;
	jatekter[0].lepesek[1]=7;
	jatekter[1].lepesek[0]=0;
	jatekter[1].lepesek[1]=2;
	jatekter[1].lepesek[2]=9;
	jatekter[2].lepesek[0]=1;
	jatekter[2].lepesek[1]=3;
	jatekter[3].lepesek[0]=2;
	jatekter[3].lepesek[1]=4;
	jatekter[3].lepesek[2]=11;
	jatekter[4].lepesek[0]=3;
	jatekter[4].lepesek[1]=5;
	jatekter[5].lepesek[0]=4;
	jatekter[5].lepesek[1]=6;
	jatekter[5].lepesek[2]=13;
	jatekter[6].lepesek[0]=5;
	jatekter[6].lepesek[1]=7;
	jatekter[7].lepesek[0]=0;
	jatekter[7].lepesek[1]=6;
	jatekter[7].lepesek[2]=15;
	
	jatekter[8].lepesek[0]=9;
	jatekter[8].lepesek[1]=15;
	jatekter[9].lepesek[0]=8;
	jatekter[9].lepesek[1]=10;
	jatekter[9].lepesek[2]=1;
	jatekter[9].lepesek[3]=17;
	jatekter[10].lepesek[0]=9;
	jatekter[10].lepesek[1]=11;
	jatekter[11].lepesek[0]=10;
	jatekter[11].lepesek[1]=12;
	jatekter[11].lepesek[2]=3;
	jatekter[11].lepesek[3]=19;
	jatekter[12].lepesek[0]=11;
	jatekter[12].lepesek[1]=13;
	jatekter[13].lepesek[0]=12;
	jatekter[13].lepesek[1]=14;
	jatekter[13].lepesek[2]=5;
	jatekter[13].lepesek[3]=21;
	jatekter[14].lepesek[0]=13;
	jatekter[14].lepesek[1]=15;
	jatekter[15].lepesek[0]=8;
	jatekter[15].lepesek[1]=14;
	jatekter[15].lepesek[2]=7;
	jatekter[15].lepesek[3]=23;
	
	jatekter[16].lepesek[0]=17;
	jatekter[16].lepesek[1]=23;
	jatekter[17].lepesek[0]=16;
	jatekter[17].lepesek[1]=18;
	jatekter[17].lepesek[2]=9;
	jatekter[18].lepesek[0]=17;
	jatekter[18].lepesek[1]=19;
	jatekter[19].lepesek[0]=18;
	jatekter[19].lepesek[1]=20;
	jatekter[19].lepesek[2]=11;
	jatekter[20].lepesek[0]=19;
	jatekter[20].lepesek[1]=21;
	jatekter[21].lepesek[0]=20;
	jatekter[21].lepesek[1]=22;
	jatekter[21].lepesek[2]=13;
	jatekter[22].lepesek[0]=21;
	jatekter[22].lepesek[1]=23;
	jatekter[23].lepesek[0]=16;
	jatekter[23].lepesek[1]=22;
	jatekter[23].lepesek[2]=15;
}

void fromMsgToTable(char* msg){
	int index=0;
	char* token = strtok(msg, ","); 
    while (token != NULL) { 
        jatekter[index].state=atoi(token); 
        token = strtok(NULL, ","); 
		index++;
    } 
}

int main(int argc, char* argv[]){
	if(argc!=2){
		printf("Ervenytelen argumentum!\n");
		return 0;
	}
	init();
	
	int networksocket;
    networksocket = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in serveraddress;
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(atoi(argv[1]));
    serveraddress.sin_addr.s_addr = INADDR_ANY;
	
	int sikeres;
	sikeres=connect(networksocket, (struct sockaddr *) &serveraddress, sizeof(serveraddress));
	if(sikeres==-1){
		fprintf(stderr,"Hiba \"connect\" soran\n");
		return 0;
	}
	char uzenet[1000];
	sikeres=recv(networksocket, &uzenet, sizeof(uzenet), 0);
	if(sikeres==-1){
		fprintf(stderr,"Hiba \"recv\" soran\n");
		return 0;
	}
	printf("%s. player\n",uzenet);
	int player=atoi(uzenet);
	if(player==1)
		printf("Varakozas a masik jatekos csatlakozasara\n");
	if(player==2)
		printf("Varakozas a masik jatekos lepesere\n");
	
	int kivalasztott,ok;
	for(int i=0;i<INIT_STEPS;i++){
		ok=0;
		sikeres=recv(networksocket, &uzenet, sizeof(uzenet), 0);//Kör
			if(sikeres==-1){
			fprintf(stderr,"Hiba \"recv\" soran\n");
			return 0;
		}
		printf("Kor: %d\n",atoi(uzenet));
		
		sikeres=recv(networksocket, &uzenet, sizeof(uzenet), 0);//Tábla
			if(sikeres==-1){
			fprintf(stderr,"Hiba \"recv\" soran\n");
			return 0;
		}
		int index=0;
		char* token = strtok(uzenet, ","); 
		while (token != NULL) { 
			jatekter[index].state=atoi(token); 
			token = strtok(NULL, ","); 
			index++;
		} 
		drawTable();
				
		printf("Kerem a mezot: ");
		scanf("%d",&kivalasztott);
		while(!ok){
			sprintf(uzenet,"%d",kivalasztott);
			sikeres=send(networksocket,uzenet,sizeof(uzenet),0);//Mező
			if(sikeres==-1){
				fprintf(stderr,"Hiba \"send\" soran\n");
				return 0;
			}
			sikeres=recv(networksocket, &uzenet, sizeof(uzenet), 0);//Válasz
			if(sikeres==-1){
				fprintf(stderr,"Hiba \"recv\" soran\n");
				return 0;
			}
			if(atoi(uzenet)==-1){
				fprintf(stderr,"Ervenytelen mezo, irja be ujra: ");	
				scanf("%d",&kivalasztott);
			}
			else{
				printf("OK\n");
				ok=1;
				sikeres=recv(networksocket, &uzenet, sizeof(uzenet), 0);//Válasz
				if(sikeres==-1){
					fprintf(stderr,"Hiba \"recv\" soran\n");
					return 0;
				}
				fromMsgToTable(uzenet); 
				drawTable();
				printf("Varakozas a masik jatekos lepesere\n");
			}
		}
	}
	
	//receive table
	
	sikeres=recv(networksocket, &uzenet, sizeof(uzenet), 0);//table
	if(sikeres==-1){
		fprintf(stderr,"Hiba \"recv\" soran\n");
		return 0;
	}
	
	printf("A mezok feltoltve, a jatek kezdodik\n\n");
	fromMsgToTable(uzenet);
	drawTable();
	
	/////////////////////////////////////////////////////////////////////////////////////////
	
	
	while(1){
		printf("Varakozas a masik jatekos lepesere.\n");
		sikeres=recv(networksocket, &uzenet, sizeof(uzenet), 0);//Tábla
		if(sikeres==-1){
			fprintf(stderr,"Hiba \"recv\" soran\n");
			return 0;
		}
		fromMsgToTable(uzenet);
		drawTable();
		
		sikeres=recv(networksocket, &uzenet, sizeof(uzenet), 0);//START,GAVE_UP,OTHER_GAVE_UP,WIN,LOSE,DRAW
		if(sikeres==-1){
			fprintf(stderr,"Hiba \"recv\" soran\n");
			return 0;
		}
		
		
		if(strcmp(uzenet,"START")==0){
			uzenet[0]='\0';
			char bemenet[20];
			printf("Kerem a lepest: ");
			scanf("%s",bemenet);
			if(strcmp(bemenet,"FELADOM")==0)
				sprintf(uzenet,"FELADOM");
			else
				sprintf(uzenet,"LEP,%s",bemenet);
			int ok=0;
			while(!ok){//jó lépésnél folytatja
				sikeres=send(networksocket,uzenet,sizeof(uzenet),0);//Művelet
				if(sikeres==-1){
					fprintf(stderr,"Hiba \"send\" soran\n");
					return 0;
				}
				uzenet[0]='\0';
				sikeres=recv(networksocket, &uzenet, sizeof(uzenet), 0);//Varakozik szerver üzenetére(NO,MALOM,OK)
				if(sikeres==-1){
					fprintf(stderr,"Hiba \"recv\" soran\n");
					return 0;
				}
				if(strcmp(uzenet,"NO")==0){
					ok=0;
					printf("Ervenytelen lepes, kerem az uj lepest: ");
					uzenet[0]='\0';					
					scanf("%s",bemenet);
					sprintf(uzenet,"LEP,%s",bemenet);
				}
				else
					ok=1;		
			}
			
			if(strcmp(uzenet,"OK")==0){//tabla kiiratasa
				sikeres=recv(networksocket, &uzenet, sizeof(uzenet), 0);//Tábla
				if(sikeres==-1){
					fprintf(stderr,"Hiba \"recv\" soran\n");
					return 0;
				}
				fromMsgToTable(uzenet);
				drawTable();
			}
			
			if(strcmp(uzenet,"MALOM")==0){//malom van
				printf("Malom van, vegyen el egy korongot az ellenfeltol: ");
				uzenet[0]='\0';
				scanf("%s",uzenet);
				ok=0;
				while(!ok){
					sikeres=send(networksocket,uzenet,sizeof(uzenet),0);//Pozíció
					if(sikeres==-1){
						fprintf(stderr,"Hiba \"send\" soran\n");
						return 0;
					}
					sikeres=recv(networksocket, &uzenet, sizeof(uzenet), 0);//Tábla
					if(sikeres==-1){
						fprintf(stderr,"Hiba \"recv\" soran\n");
						return 0;
					}
				
					if(strcmp(uzenet,"NO")==0){
						ok=0;
						printf("Nem lehet elvegezni, kerem az uj koordinatat: ");
						scanf("%s",uzenet);
					}
					else{
						ok=1;
					}
				}
				if(strcmp(uzenet,"OK")==0){//tabla kiiratasa
					sikeres=recv(networksocket, &uzenet, sizeof(uzenet), 0);//Tábla
					if(sikeres==-1){
						fprintf(stderr,"Hiba \"recv\" soran\n");
						return 0;
					}
					fromMsgToTable(uzenet);
					drawTable();
				}
			}		
		}
		
		if(strcmp(uzenet,"GAVE_UP")==0){
			printf("A jatekot feladtad.\n");
			printf("A jatek veget ert!\n");	
			return 0;
		}
		
		if(strcmp(uzenet,"OTHER_GAVE_UP")==0){
			printf("A jatekot az ellenfel feladta, nyertel.\n");
			printf("A jatek veget ert!\n");	
			return 0;
		}
		
		if(strcmp(uzenet,"LOSE")==0){
			printf("A jatekot az ellenfel nyerte, vesztettel.\n");
			printf("A jatek veget ert!\n");	
			return 0;
		}
		
		if(strcmp(uzenet,"WIN")==0){
			printf("Nyertel\n");
			printf("A jatek veget ert!\n");	
			return 0;
		}
		
		if(strcmp(uzenet,"DRAW")==0){
			printf("A jatek dontetlennel zarult\n");
			printf("A jatek veget ert!\n");	
			return 0;
		}
	}
	return 0;
}
