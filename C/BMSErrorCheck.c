#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

int check_file(char *file_name);
int column1(char line[], int *error_cnt, FILE *cfp);
int label_length(char line[], int *error_cnt, FILE *cfp);
int column89(char line[], int *error_cnt, FILE *cfp);
int illegal_op_code(char line[], int *error_cnt, FILE *cfp);
int operand(char line[], int *error_cnt, FILE *cfp);

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
  char c_file[5000] = "correction_";
  strcat(c_file, file_name);
  printf("Error Correction File: %s\n",c_file);
  FILE *cfp;
  if((cfp = fopen(c_file, "w")) == NULL){
    perror("Error creating correction file.");
    return 1;
  }

  while(fgets(line,100,fp) != NULL){
    int error_cnt;

    int first_error = column1(line, &error_cnt, cfp);
    
    if(first_error == 0){
      first_error = label_length(line, &error_cnt, cfp);
    }
    
    if(first_error == 0){
      first_error = column89(line, &error_cnt, cfp);
    }
    /*
    if(first_error == 0){
      first_error = illegal_op_code(line, &error_cnt, cfp);
    }
    if(first_error == 0){
      first_error = operand(line, &error_cnt, cfp);
    }
    */
    if(first_error == 0){
      fprintf(cfp, "%s", line);
    }
  }
  printf("File check complete.");
  return 0;
}

/*
 * Author: Alexander Vansteel
 * Purpose: Check the first column of each line for valid character
 * Inputs: char*, int*, FILE*
 * Outputs: int
 * Error Handling: none
 */
int column1(char *line, int *error_cnt, FILE *cfp){
  if( (isalpha(line[0]) == 0) | (line[0] != " ") | (line[0] != "*") ){
    return 0;
  } else {
    fprintf(cfp,"%sThe first column contains an error.\n",line);
    error_cnt++;
    return 1;
  }
}

/*
 * Author: Alexander Vansteel
 * Purpose: If the line starts with a label, verify the length and upper case
 * Inputs: char*, int*, FILE*
 * Outputs: int
 * Error Handling: label is all upper, invalid space inside label, label length
 */
int label_length(char *line, int *error_cnt, FILE *cfp){
  if (isalpha(line[0])){
    int i;
    // Checks that all characters in Lable are upper case.
    for(i=0;i<7;i++){
      if(isspace(line[i])==0){
        if(isupper(line[i])==0){
          fprintf(cfp, "%slabel Error: All characters must beupper case.\n",line);
          error_cnt++;
          return 1;
        }
      } else { // Checks for a space in the lable
        for(i;i<7;i++){
          if(isspace(line[i])==0){
            fprintf(cfp,"%sLabel Error: There is an invalid space in the Label.\n",line);
            error_cnt++;
            return 1;
          }
        }
      }
    }
    
    // Checks that the Label is not longer than 7 characters.
    if(isspace(line[7])==0){
      fprintf(cfp,"%sLabel error: Label exceeds maximum length of 7 characters.\n",line);
      error_cnt++;
      return 1;
    }
  }
  return 0;
}

/*
 * Author: Alexander Vansteel
 * Purpose: Checks columns 8 and 9 to ensure they are always spaces
 * Inputs: char*, int*, FILE*
 * Outputs: int
 * Error Handling: invalid character in column 8 or 9
 */
int column89(char *line, int *error_cnt, FILE *cfp){
  if( (isspace(line[7]) == 0) | (isspace(line[8]) == 0)){
    fprintf(cfp,"%sInvalid character in column 8 or 9. Must be a space.\n",line);
    error_cnt++;
    return 1;
  }
  return 0;
}

/*
 * Author: Alexander Vansteel
 * Purpose:
 * Inputs: char*, int*, FILE*
 * Outputs: int
 * Error Handling:
 */
int illegal_op_code(char *line, int *error_cnt, FILE *cfp){
  //fprintf(cfp, "%s", line);

  return 0;
}

/*
 * Author: Alexander Vansteel
 * Purpose:
 * Inputs: char*, int*, FILE*
 * Outputs: int
 * Error Handling:
 */
int operand(char *line, int *error_cnt, FILE *cfp){
  //fprintf(cfp, "%s", line);

  return 0;
}
