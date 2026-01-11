#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	FILE *filePointer = fopen("todo.txt", "a+");
	if (filePointer == NULL){
		printf("Errow opening file");
		return 1;
	};
	if (argc < 2){
		printf("Error ! Please input a valid method!\n");
		return 1;
	}
	else if (argc < 3 && !strcmp(argv[1], "add")){
		printf("Error ! Please input a valid input!\n");
		return 1;
	}
	else if (!strcmp(argv[1], "add")){
		int total_length = 0;

		for (int i = 2; i < argc; i++){
			total_length += strlen(argv[i]) + 1;
		}

		char *fullTask = malloc(total_length);
		if (fullTask == NULL){
			printf("Error allocating memory");
			return 1;
		}
		fullTask[0] = '\0';
		for (int i=2; i < argc; i++){
			strcat(fullTask, argv[i]);
			if ( i < argc - 1){
				strcat(fullTask, " ");
			}
		}
		fprintf(filePointer, "%s\n", fullTask);
		free(fullTask);
	}
	else if (!strcmp(argv[1], "list")){
		rewind(filePointer);
		char ch;
		while((ch = fgetc(filePointer)) != EOF){
			printf("%c", ch);
		}
	}
	fclose(filePointer);
	return 0;
}