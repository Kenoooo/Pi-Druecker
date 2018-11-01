#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"
#include "mqtt.h"
//#include "stopwatch.h"

#define CLIENTID	"Kontroll-PC"
#define QOS		1
#define TIMEOUT		10000L

MQTTClient client;

volatile MQTTClient_deliveryToken deliveredtoken;

void delivered(void *context, MQTTClient_deliveryToken dt)
{
	printf("Message with token value %d delivery confirmed\n", dt);
	deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
	int i;
	char* payloadptr;

	printf("Message arrived\n");
	printf("	topic: %s\n", topicName);
	printf("	message: ");

	payloadptr = message->payload;
	for(i=0; i<message->payloadlen; i++)
	{
		putchar(*payloadptr++);
	}
	putchar('\n');
	MQTTClient_freeMessage(&message);
	MQTTClient_free(topicName);
	return 1;
}

void connlost(void *context, char *cause)
{

	//char* currentTime;
	//currentTime = (char *) malloc(20 * sizeof(char));
	//getTime(&currentTime);
	printf("\nConnection lost\n");
	printf("	cause: %s\n", cause);
	//printf("at Time: %s\n", currentTime);

	connectToBroker();
}

int instantiateClient(char* address){
	int rc;
	rc = MQTTClient_create(&client, address, CLIENTID,
			MQTTCLIENT_PERSISTENCE_NONE, NULL);
	MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);
	return rc;
}

void connectToBroker(void){
	int rc;
	MQTTClient_connectOptions conn_opts =
			MQTTClient_connectOptions_initializer;
	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 0;
	do{
	rc = MQTTClient_connect(client, &conn_opts);
	} while(rc != MQTTCLIENT_SUCCESS);
}

void sendMessage(char* topic, char* payload){
	MQTTClient_message pubmsg = MQTTClient_message_initializer;
	MQTTClient_deliveryToken token;

	pubmsg.payload = payload;
	pubmsg.payloadlen = strlen(payload);
	pubmsg.qos = QOS;
	pubmsg.retained = 0;
	deliveredtoken = 0;
	MQTTClient_publishMessage(client, topic, &pubmsg, &token);
	printf("Current token: %d\n", token);
	while(deliveredtoken != token);
	printf("Delivered %s\n", payload);
	/*if(deliveredtoken = token){
		printf("Delivered %s\n", payload);
		return 0;
	} else{
		printf("ERROR on delivery %s\n", payload);
		return -1;
	}*/
}

void disconnectFromBroker(void){
	MQTTClient_disconnect(client, TIMEOUT);
	MQTTClient_destroy(&client);
}
