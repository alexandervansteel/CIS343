#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

int check_file(char *file_name);
int column1(char line[], FILE *cfp);
int label(char line[], FILE *cfp);
int column89(char line[], FILE *cfp);
int end_called(char *line, int end_call, FILE *cfp);
int illegal_op_code(char *line, FILE *cfp);
int operand(char *line, FILE *cfp);

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

/*
 * Author: Alexander Vansteel
 * Purpose: Opens file
 * Inputs: FILE*, char[]*
 * Outputs: void
 * Error Handling: opening requested file, creating correction file
 */
int check_file(char *file_name){
  FILE *fp;
  char line[100];

  if((fp = fopen(file_name, "r")) == NULL){
    perror("File name error");
    return 1;
  }

  printf("Opening requested file: %s\n", file_name);

  /* Creates new file to store the corrections in. */
  char c_file[5000] = "BMSOut.txt";
  printf("Error Correction File: %s\n",c_file);
  FILE *cfp;
  if((cfp = fopen(c_file, "w")) == NULL){
    perror("Error creating correction file.");
    return 1;
  }

  int error_cnt = 0;
  int end_call = 0;
  while(fgets(line,100,fp) != NULL){
    if(end_call == 1){
      int i;
      for(i=0;i<71;i++){
        if(isspace(line[i]) == 0){
          fprintf(cfp, "%s### Invalid character after END.", line);
          error_cnt++;
        }
      }
    }

    int first_error = column1(line, cfp);

    if((first_error == 0) && (end_call == 0)){
      first_error = label(line, cfp);
      error_cnt = error_cnt + first_error;
    }
    if((first_error == 0) && (end_call == 0)){
      first_error = column89(line, cfp);
      error_cnt = error_cnt + first_error;
    }
    if((first_error == 0) && (end_call == 0)){
      first_error = end_called(line, end_call, cfp);
      error_cnt = error_cnt + first_error;
    }
    if((first_error == 0) && (end_call == 0)){
      first_error = illegal_op_code(line, cfp);
      error_cnt = error_cnt + first_error;
    }
    if((first_error == 0) && (end_call == 0)){
      first_error = operand(line, cfp);
      error_cnt = error_cnt + first_error;
    }
    if((first_error == 0) && (end_call == 0)){
      fprintf(cfp, "%s", line);
    }
  }
  printf("File check complete.\nErrors found: %d\n", error_cnt);
  return 0;
}

/*
 * Author: Alexander Vansteel
 * Purpose: Check the first column of each line for valid character
 * Inputs: char*, FILE*
 * Outputs: int
 * Error Handling: invalid character in first coloumn
 */
int column1(char *line, FILE *cfp){
  if( (isalpha(line[0]) == 0) | (line[0] != ' ') | (line[0] != '*') ){
    return 0;
  } else {
    fprintf(cfp,"%s### The first column contains an error.\n",line);
    return 1;
  }
}

/*
 * Author: Alexander Vansteel
 * Purpose: If the line starts with a label, verify the length and upper case
 * Inputs: char*, FILE*
 * Outputs: int
 * Error Handling: label is all upper, invalid space inside label, label length
 */
int label(char *line, FILE *cfp){
  if (isalpha(line[0]) != 0){
    int i;
    // Checks that all characters in Lable are upper case.
    for(i=0;i<7;i++){
      if(line[i] != ' '){
        if(isupper(line[i])==0){
          fprintf(cfp, "%s### Label Error: All characters must be upper case and cannot be digits.\n",line);
          return 1;
        }
      } else { // Checks for a space in the lable
        for(i+1;i<7;i++){
          if(line[i] != ' '){
            fprintf(cfp,"%s### Label Error: There is an invalid space in the Label.\n",line);
            return 1;
          }
        }
      }
    }

    // Checks that the Label is not longer than 7 characters.
    if(line[7] != ' '){
      fprintf(cfp,"%s### Label error: Label exceeds maximum length of 7 characters.\n",line);
      return 1;
    }
  }
  // Checks for unexpected characters in label area if no lable is present.
  if(line[0] == ' '){
    int i;
    for(i=0;i<7;i++){
      if(line[i] != ' '){
        fprintf(cfp,"%s### Invalid character in Label text. Expected no characters.\n",line);
        return 1;
      }
    }
  }
  return 0;
}

/*
 * Author: Alexander Vansteel
 * Purpose: Checks columns 8 and 9 to ensure they are always spaces
 * Inputs: char*, FILE*
 * Outputs: int
 * Error Handling: invalid character in column 8 or 9
 */
int column89(char *line, FILE *cfp){
  if(line[0] != '*'){
    if((line[7] != ' ') | (line[8] != ' ')){
      fprintf(cfp,"%s### Invalid character in column 8 or 9. Must be a space.\n");
      return 1;
    }
  }
  return 0;
}

/*
 * Author: Alexander Vansteel
 * Purpose: Checks if END has been called
 * Inputs: char*, int, FILE*
 * Outputs: int
 * Error Handling: if END has been called
 */
int end_called(char *line, int end_call, FILE *cfp){
  if((line[0] != '*') && (isalpha(line[0]) != 0)){
    if((line[9] == 'E') && (line[10] == 'N') && (line[11] == 'D')){
      end_call = 1;
    }
  }
  return 0;
}

/*
 * Author: Alexander Vansteel
 * Purpose: Check for valid Op-code
 * Inputs: char*, FILE*
 * Outputs: int
 * Error Handling: an invalid Op-code
 *                 any character after Op-code
 */
int illegal_op_code(char *line, FILE *cfp){
  if(line[0] != '*'){
    if(line[9] == ' '){
      return 0;
    }
    if(line[9] != 'E'){
      // op char 1
      if(line[9] != 'D'){
        fprintf(cfp, "%s### Invalid Op-code character 1.\n", line);
        return 1;
      }
      // op char 2
      if(line[10] != 'F'){
        fprintf(cfp, "%s### Invalid Op-code character 2.\n", line);
        return 1;
      }
      // op char 3
      if(line[11] != 'H'){
        fprintf(cfp, "%s### Invalid Op-code character 3.\n", line);
        return 1;
      }
      // op char 4
      if(line[12] != 'M'){
        fprintf(cfp, "%s### Invalid Op-code character 4.\n", line);
        return 1;
      }
      // op char 5
      if((line[13] != 'D') && (line[13] != 'S')){
        fprintf(cfp, "%s### Invalid Op-code character 5.\n", line);
        return 1;
      }
      // op char 6
      if((line[14] != 'I') && (line[14] != 'F') && (line[14] != 'D')){
        fprintf(cfp, "%s### Invalid Op-code character 6.\n", line);
        return 1;
      }
      // space after Op-code
      if(line[15] != ' '){
        fprintf(cfp, "%s### Expected a space after Op-code.\n", line);
        return 1;
      }
    }
  }
  return 0;
}

/*
 * Author: Alexander Vansteel
 * Purpose: Checks that the Operand begins in correct column.
 * Inputs: char*, FILE*
 * Outputs: int
 * Error Handling: non-space character in column earlier than 16
 */
int operand(char *line, FILE *cfp){
  if((line[0] == ' ') && (line[9] != 'D') && (line[9] != 'E')){
    int i;
    /* Verifies that there is no Op-code.*/
    for(i=9;i<15;i++){
      if(line[i] != ' '){
        fprintf(cfp, "%s### Character found in Op-code column %d when none were expected.\n", line, i+1);
        return 1;
      }
    }
  }
  return 0;
}
