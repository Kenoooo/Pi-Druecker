#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backup.h"
#include "stopwatch.h"

char* backupname;

void backupInit(void){
	FILE* f;

	char* date = (char *) malloc(10 * sizeof(char));
	getDate(&date);

	strcat(date, ".txt");
	backupname = date;

	f = fopen(backupname, "a+");

	fprintf(f, "date and daytime, timestamp\n");

	fclose(f);
}

void writeBackup(char* backup){
	FILE* f;

	f = fopen(backupname, "a+");

	char* daytime = (char *) malloc(32 * sizeof(char));
	getDaytime(&daytime);

	fprintf(f, "%s, %s\n", daytime, backup);

	fclose(f);

}
