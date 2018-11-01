#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include "mqtt.h"
#include "stopwatch.h"
#include "backup.h"

int main (int argc, char* argv[]){
	
	if(argc != 3){
		printf("Erwartete Parameter: Adresse, Topic\n");
	}
	else {
		/*for(int i = 0; i < argc; i++){
			printf("%s\n", argv[i]);
		}*/
		char* address = argv[1];
		char* topic = argv[2];

		instantiateClient(address);
		connectToBroker();

		char* payload;
		payload = (char *) malloc(20 * sizeof(char));
		if(wiringPiSetup() == -1){
			printf("wiringPi Setup Fehler");
			return 1;
		}else{
			pinMode(5, INPUT);
		}
		while(1){
			if(digitalRead(5) == 1){
				getchar();
	        		getTime(&payload);
				sendMessage(topic, payload);
				writeBackup(payload);
			}
		}
		//disconnectFromBroker();

		//free(payload);
	}

	return 0;

}