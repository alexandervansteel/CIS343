#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

/*
 * Auther: Alexander Vansteel
 * Assignment: C Homework 2
 * Due Date: 2016 October 3
 */
int main(int argc, char *argv[]){
  char file_name[100], line[100];
  FILE *fp;
  int *error_cnt;
  
  memset(file_name, 0, sizeof(file_name));
  memset(line, 0, sizeof(line));

  printf("Enter the name of the file to scan: ");
  fgets(file_name,sizeof(file_name),stdin);

  printf("File name: \n");
  open_file(&fp, &file_name);

  while(fgets(line, sizeof(line),fp)){
    int first_error = column1(&line, &error_cnt);
    if(first_error == 0){
      first_error = lable_length(&line, &error_cnt);
    }
    if(first_error == 0){
      first_error = column89(&line, &error_cnt);
    }
    if(first_error == 0){
      first_error = illegal_op_code(&line, &error_cnt);
    }
    if(first_error == 0){
      first_error = operand(&line, &error_cnt);
    }
    if(first_error == 0){
      printf("%s\nNo errors detected in line.\n");
    }
  }
  fclose(fp);

  printf("End of Processing - %d errors encountered.\n", error_cnt);
  return 0;
}

/*
 * Author: Alexander Vansteel
 * Purpose: Opens file
 * Inputs: FILE*, char[]*
 * Outputs: void
 * Error Handling: open()
 */
void open_file(FILE *fp, char *file_name){
  fp = fopen(file_name, "r");
  if(fp == NULL){
    perror("open error");
  } else {
    printf("Opening file: %s\n", file_name);
  }
}

/*
 * Author: Alexander Vansteel
 * Purpose: Checks first column to verify it is a letter, space, or *
 * Inputs: char[]*, int*
 * Outputs: int
 * Error Handling: checks for character, space or *
 */
int column1(char (*line)[500], int *error_cnt){
  if(!(isalpha(line[0]) | (strcmp(line[0]," ") == 0) |
      (strcmp(line[0],"*") == 0))){
    printf("%s\nThe first column contains an error.\n");
    error_cnt++;
    return 1;
  } else {
    return 0;
  }
}

/*
 * Author: Alexander Vansteel
 * Purpose: Checks Lable to ensure all character are upper case and the lenght
 *          is less than 7 characters.
 * Inputs: char[]*, int*
 * Outputs: int
 * Error Handling: all upper case, length less than 8
 */
 int lable_length(char (*line)[500], int *error_cnt){
  if(isalpha(line[0])){
    int i;
    /* Checks that all characters in Lable are upper case. */
    for(i=0;i<7;i++){
      if(isspace(line[i]) == 0){
        if(isupper(line[i]) == 0){
          printf("%s\nLable Error: All characters must be upper case.\n",line);
          error_cnt++;
          return 1;
        }
      } else {
        for(i;i<7;i++){
          if(isspace(line[i]) == 0){
            printf("#s\nLable Error: There is a space in the Lable.\n", line);
            error_cnt++;
            return 1;
          }
        }
      }
    }

    /* Checks that Lable is not longer than 7 characters. */
    if(isspace(line[7]) == 0){
      printf("%s\nLable Error: Lable exceeds maximum length of 7 characters.\n", line);
      error_cnt++;
      return 1;
    }
  } else {
    return 0;
  }
 }

/*
 * Author: Alexander Vansteel
 * Purpose: Checks column 8 and 9 verify they are spaces.
 * Inputs: char[]*, int*
 * Outputs: int
 * Error Handling: column 8 or 9 is not a space
 */
int column89(char (*line), int *error_cnt){
  if((strcmp(line[7]," ") != 0) | (strcmp(line[8], " ") != 0)){
    printf("%s\nInvalid character in column 8 or 9.\n", line);
    error_cnt++;
    return 1;
  } else {
    return 0;
  }
}

/*
* Author: Alexander Vansteel
* Purpose: Checks for valid Op-code.
* Inputs: char[]*, int*
* Outputs: int
* Error Handling: any non-space character in the first 10 columns
*                 an invalid Op-code
*                 any character after Op-code
*/
int illegal_op_code(char (*line)[500], int *error_cnt){
  int i;

  if(isspace(line[0])){
    /* Verifies the first 10 coloumns are empty if the line is an Op-code. */
    for(i=0;i<10;i++){
      if(isspace(line[i]) == 0){
        printf("%s\nThere is an illegal character in the first 10 coloumns of the Op-code.\n",line);
        error_cnt++;
        return 1;
      }
    }
  }

  /*
  * Verifies the Op-code is correct if the start of the Op-code column has a
  * character in it.
  */
  if(isspace(line[9]) == 0){
    for(i=9;i<sizeof(line);i++){
      // op char 1
      if((i=9) && (strcmp(line[i],"D") != 0)){
        printf("%s\nInvalid Op-code: Check first character.\n", line);
        error_cnt++;
        return 1;
      }
      // op char 2
      if((i=10) && (strcmp(line[i],"F") != 0)){
        printf("%s\nInvalid Op-code: Check second character.\n", line);
        error_cnt++;
        return 1;
      }
      //op char 3
      if((i=11) && ((strcmp(line[i],"H") != 0) | (strcmp(line[i],"M") != 0))){
        printf("%s\nInvalid Op-code: Check third character.\n",line);
        error_cnt++;
        return 1;
      }
      // op char 4
      if((i=12) && (strcmp(line[i],"M") != 0)){
        printf("%s\nInvalid Op-code: Check fourth character.\n", line);
        error_cnt++;
        return 1;
      }
      // op char 5
      if((i=13) && ((strcmp(line[i],"D") != 0) | (strcmp(line[i],"S") != 0))){
        printf("%s\nInvalid Op-code: Check fifth character.\n", line);
        error_cnt++;
        return 1;
      }
      // op char 6
      if((i=14) && ((strcmp(line[i],"F") != 0) |
                    (strcmp(line[i],"D") != 0) | (strcmp(line[i],"I") != 0))){
        printf("%s\nInvalid Op-code: Check sixth character.\n", line);
        error_cnt++;
        return 1;
      }
      if((i = 15) && (isspace(line[i]) == 0)){
        printf("%s\nInvalid character after Op-code.", line);
        error_cnt++;
        return 1;
      }
    }
  }

  /* Verifies that there is no Op-code.*/
  for(i=9;i<15;i++){
    if(isspace(line[i]) == 0){
      printf("%s\nCharacter found in Op-code column when none were expected.\n", line);
      error_cnt++;
      return 1;
    } else {
      return 0;
    }
  }
}

/*
* Author: Alexander Vansteel
* Purpose: Checks that the Operand is in the correct column if no Op-code.
* Inputs: char[]*, int*
* Outputs: int
* Error Handling: non-space character in column earlier than 16
*/
int operand(char (*line)[100], int *error_cnt){
  if(isspace(line[0]) != 0){
    int i;
    for(i=0;i<sizeof(line);i++){
      if((i<16) && (isspace(line[i]) == 0)){
        printf("%s\nInvalid Operand: ", line);
        printf("Character in column %d is invalid.", i+1);
        error_cnt++;
        return 1;
      }
    }
  }
  return 0;
}
