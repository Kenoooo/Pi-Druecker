#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

void getTime(char** returnValue){

	struct timeval tval;
	gettimeofday(&tval, NULL);

	char* str;
	str = malloc(20 * sizeof(char));
	unsigned long long millis = (unsigned long long) tval.tv_sec * 1000 + tval.tv_usec / 1000;
	sprintf(str, "%lld", millis);
	
	strcpy(*returnValue, str);

	free(str);
}
