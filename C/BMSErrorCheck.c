#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

int open_file(char *file_name);

/*
 * Auther: Alexander Vansteel
 * Assignment: C Homework 2
 * Due Date: 2016 October 10
 */
 int main(int argc, char *argv[]){
    char file_name[100];

    memset(file_name,0,sizeof(file_name));
    printf("Enter the name of the file to scan: ");
    fgets(file_name,sizeof(file_name),stdin);

    if(open_file(file_name) != 0){
      perror("open_file error");
      return 1;
    }
    return 0;
 }

 int open_file(char *file_name){
    FILE *fp;

    if((fp = fopen(file_name, "r")) == NULL){
        perror("File name error\n");
        return 1;
    } else {
        printf("Opening requested file: %s\n", file_name);
    }
    return 0;
 }
