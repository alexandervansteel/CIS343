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
    char no_errors[] = "No errors detected in this line.\n";

    int first_error = column1(line, &error_cnt, cfp);
    /*
    if(first_error == 0){
      first_error = label_length(line, &error_cnt, cfp);
      if(error_cnt == 0){
        fprintf(cfp, "%s\n", no_errors);
      }
    }
    if(first_error == 0){
      first_error = column89(line, &error_cnt, cfp);
      if(error_cnt == 0){
        fprintf(cfp, "%s\n", no_errors);
      }
    }
    if(first_error == 0){
      first_error = illegal_op_code(line, &error_cnt, cfp);
      if(error_cnt == 0){
        fprintf(cfp, "%s\n", no_errors);
      }
    }
    if(first_error == 0){
      first_error = operand(line, &error_cnt, cfp);
      if(error_cnt == 0){
        fprintf(cfp, "%s\n", no_errors);
      }
    }
    if(first_error == 0){
      fprintf(cfp, "%s", line);
      fprintf(cfp, "%s\n", no_errors);
    }
    */
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
int column1(char *line, int *error_cnt, FILE *cfp){
  if( (isalpha(line[0]) == 0) | (line[0] != " ") | (line[0] != "*") ){
    fprintf(cfp, "%s", line);
    return 1;
  } else {
    fprintf(cfp,"%sThe first column contains an error.\n",line);
    error_cnt++;
    return 0;
  }
}

/*
 * Author: Alexander Vansteel
 * Purpose:
 * Inputs: char[], int*, FILE*
 * Outputs: int
 * Error Handling:
 */
int label_length(char line[], int *error_cnt, FILE *cfp){
  //fprintf(cfp, "%s", line);

  return 0;
}

/*
 * Author: Alexander Vansteel
 * Purpose:
 * Inputs: char[], int*, FILE*
 * Outputs: int
 * Error Handling:
 */
int column89(char line[], int *error_cnt, FILE *cfp){
  //fprintf(cfp, "%s", line);

  return 0;
}

/*
 * Author: Alexander Vansteel
 * Purpose:
 * Inputs: char[], int*, FILE*
 * Outputs: int
 * Error Handling:
 */
int illegal_op_code(char line[], int *error_cnt, FILE *cfp){
  //fprintf(cfp, "%s", line);

  return 0;
}

/*
 * Author: Alexander Vansteel
 * Purpose:
 * Inputs: char[], int*, FILE*
 * Outputs: int
 * Error Handling:
 */
int operand(char line[], int *error_cnt, FILE *cfp){
  //fprintf(cfp, "%s", line);

  return 0;
}
