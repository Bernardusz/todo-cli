#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

void createTask (char *title[], int argc, FILE *filePointer, char *argv[]);
void readTask (FILE *filePointerReading);
void updateTask (FILE *fileTemp, char line[], char target[], FILE *filePointerReading, char *argv[]);
void deleteTask ();

int main(int argc, char *argv[]){
	FILE *filePointer = fopen("todo.txt", "a+");
	FILE *fileTemp = fopen("todo.tmp", "w");
	FILE *filePointerReading = fopen("todo.txt", "r");
	if (!filePointer || !filePointerReading || !fileTemp){
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
		createTask(fullTask, argc, filePointer, argv);
		free(fullTask);
		
	}
	else if (!strcmp(argv[1], "list")){
		rewind(filePointerReading);
		char ch;
		while((ch = fgetc(filePointerReading)) != EOF){
			printf("%c", ch);
		}
	}
	else if(!strcmp(argv[1], "edit") && argc == 4){
		char line[MAX_LENGTH];
		char target[MAX_LENGTH];
		updateTask(fileTemp, line, target, filePointerReading, argv);
	}
	else if (!strcmp(argv[1], "delete") && argc == 3){
		char line[MAX_LENGTH];
		char target[MAX_LENGTH];
		deleteTask(fileTemp, line, target, filePointerReading, argv);
	}
	else {
		printf("You didn't do anything valid!");
		return 1;
	}
	fclose(filePointer);
	fclose(filePointerReading);
	fclose(fileTemp);
	
	return 0;
};

void createTask (char *title[], int argc, FILE *filePointer, char *argv[]){
	title[0] = '\0';
	for (int i=2; i < argc; i++){
		strcat(title, argv[i]);
		if ( i < argc - 1){
			strcat(title, " ");
		}
	}
	fprintf(filePointer, "%s\n", title);
}
void readTask (FILE *filePointerReading){
	rewind(filePointerReading);
	char ch;
	while((ch = fgetc(filePointerReading)) != EOF){
		printf("%c", ch);
	}
}
void updateTask (FILE *fileTemp, char line[], char target[], FILE *filePointerReading, char *argv[]){
	snprintf(target, sizeof(target), "%s\n", argv[2]);
	rewind(filePointerReading);
	while (fgets(line, MAX_LENGTH, filePointerReading) != NULL){
		if (!strcmp(target, line)){
			fprintf(fileTemp, "%s\n", argv[3]);
		}
		else{
			fputs(line, fileTemp);
		}
	};
	remove("todo.txt");
	rename("todo.tmp", "todo.txt");
}
void deleteTask (FILE *fileTemp, char line[], char target[], FILE *filePointerReading, char *argv[]){
	snprintf(target, sizeof(target), "%s\n", argv[2]);
	rewind(filePointerReading);
	while (fgets(line, MAX_LENGTH, filePointerReading) != NULL){
		if (strcmp(target, line)){
			fputs(line, fileTemp);
		}
	};
	remove("todo.txt");
	rename("todo.tmp", "todo.txt");
}
