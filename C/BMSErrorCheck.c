#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

int check_file(char *file_name);
/*
int column1(char *line, int *error_cnt);
int label_length(char *line, int *error_cnt);
int column89(char *line, int *error_cnt);
int illegal_op_code(char *line, int *error_cnt);
int operand(char *line, int *error_cnt);
*/

/*
 * Auther: Alexander Vansteel
 * Assignment: C Homework 2
 * Due Date: 2016 October 10
 */
 int main(int argc, char *argv[]){
    char file_name[100];

    memset(file_name,0,sizeof(file_name));
    printf("Enter the name of the file to scan: ");
    //fgets(file_name,sizeof(file_name),stdin);
	scanf("%s", file_name);

	printf("Requested file name: %s\n", file_name);
    check_file(file_name);
    return 0;
 }

 int check_file(char *file_name){
    FILE *fp;
	char line[500];

    if((fp = fopen(file_name, "r")) == NULL){
        perror("File name error");
        return 1;
    }
    
	printf("Opening requested file: %s\n", file_name);
	while(fgets(line,100,fp) != NULL){
		printf("%s",line);
	}

    return 0;
 }
