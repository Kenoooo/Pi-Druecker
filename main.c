#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include "mqtt.h"
#include "stopwatch.h"
#include "backup.h"

const char* brokerIP = "192.168.213.66:1883";
const char* topic = "event/timer/start";

int main (void){
	
	instantiateClient(brokerIP);
	connectToBroker();

	backupInit();

	char* payload;
	payload = (char *) malloc(20 * sizeof(char));

	int rc;
	do{
		rc = wiringPiSetup();
	} while(rc == -1);
	pinMode(5, INPUT);

	while(1){
		if(digitalRead(5) == 1){
	       		getTime(&payload);
			sendMessage(topic, payload);
			writeBackup(payload);
		}
	}
	
	return 0;
}
