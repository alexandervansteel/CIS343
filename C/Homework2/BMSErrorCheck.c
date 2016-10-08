#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

int check_file(char *file_name);
int column1(char line[], int *error_cnt, FILE *cfp);
int label_length(char line[], int *error_cnt, FILE *cfp);
int column89(char line[], int *error_cnt, FILE *cfp);
int end_called(char *line, int *error_cnt, int *end_call, FILE *cfp);
int illegal_op_code(char line[], int *error_cnt, int *op_code, FILE *cfp);
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

  int error_cnt;
  int op_code;
  int end_call = 0;
  while(fgets(line,100,fp) != NULL){
    if(end_call == 1){
      int i;
      for(i=0;i<71;i++){
        if(isspace(line[i]) == 0){
          fprintf(cfp, "%sInvalid character after END.", line);
        }
      }
    }

    int first_error = column1(line, &error_cnt, cfp);

    if((first_error == 0) && (end_call == 0)){
      first_error = label_length(line, &error_cnt, cfp);
    }

    if((first_error == 0) && (end_call == 0)){
      first_error = column89(line, &error_cnt, cfp);
    }
    if((first_error == 0) && (end_call == 0)){
      first_error = end_called(line, &error_cnt, &end_call, cfp);
    }
    if((first_error == 0) && (end_call == 0)){
      first_error = illegal_op_code(line, &error_cnt, &op_code, cfp);
    }
    if((first_error == 0) && (end_call == 0) && (op_code == 0)){
      first_error = operand(line, &error_cnt, cfp);
    }
    if((first_error == 0) && (end_call == 0)){
      fprintf(cfp, "%s", line);
    }
  }
  printf("File check complete.\nErrors found: %d", error_cnt);
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
    fprintf(cfp,"%sInvalid character in column 8 or 9. Must be a space.\n");
    error_cnt++;
    return 1;
  }
  return 0;
}

/*
 * Author: Alexander Vansteel
 * Purpose: Checks if END has been called
 * Inputs: char*, int*, int*, FILE*
 * Outputs: int
 * Error Handling: non-space character in column earlier than 16
 *                 if END has been called
 */
 int end_called(char *line, int *error_cnt, int *end_call, FILE *cfp){
   // Verifies first 10 coloums are empty if the line does not begin with a * or label
   if(isspace(line[0]) != 0){
     int i;
     for(i=0;i<10;i++){
       if(isspace(line[i]) == 0){
         fprintf(cfp,"%sInvalid character before Operand.\n",line);
         error_cnt++;
         return 1;
       }
     }
   }

   if((line[9] == "E") && (line[10] == "N") && (line[11] == "D")){
     end_call = 1;
   }

   return 0;
 }

/*
 * Author: Alexander Vansteel
 * Purpose: Check for valid Op-code
 * Inputs: char*, int*, int*, FILE*
 * Outputs: int
 * Error Handling: any non-space character in the first 10 columns
 *                 an invalid Op-code
 *                 any character after Op-code
 */
int illegal_op_code(char *line, int *error_cnt, int *op_code, FILE *cfp){
  if(isspace(line[0]) | isalpha(line[0])){
    int i;
    for(i=9;i<70;i++){
      // op char 1
      if((i=9) && (line[i] != "D")){
        fprintf(cfp, "%sInvalid Op-code: Character 1.\n", line);
        error_cnt++;
        return 1;
      }
      // op char 2
      if((i=10) && (line[i] != "F")){
        fprintf(cfp, "%sInvalid Op-code: Character 2.\n", line);
        error_cnt++;
        return 1;
      }
      // op char 3
      if((i=11) && (line[i] != "M")){
        fprintf(cfp, "%sInvalid Op-code: Character 3.\n", line);
        error_cnt++;
        return 1;
      }
      // op char 4
      if((i=12) && (line[i] != "H")){
        fprintf(cfp, "%sInvalid Op-code: Character 4.\n", line);
        error_cnt++;
        return 1;
      }
      // op char 5
      if((i=13) && ((line[i] != "D") | (line[i] != "S"))){
        fprintf(cfp, "%sInvalid Op-code: Character 5.\n", line);
        error_cnt++;
        return 1;
      }
      // op char 6
      if((i=14) && ((line[i] != "D") | (line[i] != "F") | (line[i] != "I"))){
        fprintf(cfp, "%sInvalid Op-code: Expecting space.\n", line);
        error_cnt++;
        return 1;
      }
      // checks for space after op code
      if((i=15) && (isspace(line[i]) == 0)){
        fprintf(cfp, "%sInvalid Op-code: Space expected after 6 digit Op-code.\n", line);
        error_cnt++;
        return 1;
      }
    }
  }
  op_code = 1;
  return 0;
}

/*
 * Author: Alexander Vansteel
 * Purpose: Checks that the Operand begins in correct column.
 * Inputs: char*, int*, FILE*
 * Outputs: int
 * Error Handling: checks if op-code present
 *                 non-space character in column earlier than 16
 */
int operand(char *line, int *error_cnt, FILE *cfp){
  int i;
  /* Verifies that there is no Op-code.*/
  for(i=9;i<15;i++){
    if(isspace(line[i]) == 0){
      fprintf(cfp, "%sCharacter found in Op-code column when none were expected.\n", line);
      error_cnt++;
      return 1;
    }
  }
  if(isspace(line[0]) != 0){
    for(i=0;i<70;i++){
      if((i<16) && (isspace(line[i]) == 0)){
        fprintf(cfp,"%sInvalid operand: Character in column %d is invalid./n",line,i+1);
        error_cnt++;
        return 1;
      }
    }
  }
  return 0;
}
