#include <stdio.h>
#include "backup.h"

void writeBackup(char* backup){
	printf("%s\n", backup);
	FILE* f;
	int i = 5;

	printf("file open\n");
	f = fopen("backupFile.txt", "a+");

	printf("file print\n");
	fprintf(f, "%s\n", backup);

	printf("file close\n");
	fclose(f);
}
