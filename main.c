#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <pthread.h>
#include "mqtt.h"
#include "stopwatch.h"
#include "backup.h"

#define BROKERIP "192.168.213.66:1883"
#define TOPIC "event/timer/start/time"
#define TOPIC_S "event/timer/start/status"

#define DEBOUNCETIME 7500

void *status(){
	char* state = "online";
	while(1){
		sendMessage((char*)TOPIC_S, state);
		sleep(10);
	}	
}

int main (void){
	
	instantiateClient((char*)BROKERIP);
	connectToBroker();

	backupInit();
	
	pthread_t p1;
	pthread_create(&p1,NULL,status,NULL);
	
	char* payload;
	payload = (char *) malloc(20 * sizeof(char));

	int rc;
	do{
		rc = wiringPiSetup();
	} while(rc == -1);
	pinMode(5, INPUT);
	
	int warte = 0;
	int buttonPressed = 0;
	while(1){
		if(digitalRead(5) == 1){
			//printf("%d\n", buttonPressed);
			buttonPressed++;
		}else{
			buttonPressed = 0;
		}
		if(buttonPressed == DEBOUNCETIME){
			getTime(&payload);
			sendMessage((char*)TOPIC, payload);
			writeBackup(payload);
			sleep(5);
		}
	}
	disconnectFromBroker();
	free(&payload);
	
	return 0;
}
