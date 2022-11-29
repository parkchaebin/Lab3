/* q3.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void ls(const char *name) {
	DIR *dir;
	struct dirent *pde;
	char temp[20][100];
	char *dir_path[20];
	int i = 0;
	int k = 0;

	for(int m = 0; m < 20; m++)
		dir_path[m] = NULL;
	for(int n = 0; n < 20; n++) {
		for(int b = 0; b < 100; b++) 
			temp[n][b] = NULL;
	}

	if(!(dir = opendir(name)))
		return;
	printf("%s:\n", name);

	while((pde = readdir(dir)) != NULL) {
		if(pde -> d_type == DT_DIR) {
			char path[1024];
			if(strcmp(pde -> d_name, ".") == 0 || strcmp(pde -> d_name, "..") == 0)
				continue;
			snprintf(path, sizeof(path), "%s/%s", name, pde -> d_name);

			for(int c = 0; c < strlen(path); c++) {
				temp[i][c] = path[c];
			}
			dir_path[i] = temp[i];
			i++;
			printf("%s%5s", dir_path[i-1], "");
		} 
		else {
			printf("%s%5s", pde -> d_name, "");
		}
	}

	printf("\n\n");
	while(dir_path[k] != NULL) {
		if(dir_path[k] == NULL) 
			break;
		ls(dir_path[k]);
		k++;
	}
	closedir(dir);
}

int main(void) {
	ls(".");
	return 0;
}
