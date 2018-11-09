#include <stdio.h>
#include "backup.h"

void writeBackup(char* backup){
	FILE* f;

	f = fopen("backupFile.txt", "a+");

	fprintf(f, "%s\n", backup);

	fclose(f);
}
