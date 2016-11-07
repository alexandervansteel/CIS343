#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int FillTable(int a[], int* max){
  int i, input;
  char c;
  for(i=0;i<=*max;i++){
    printf("Enter an integer or' Q' or 'q' to quit: ");
    if(scanf("%d", &input) == 1){
      a[i]= input;
    }
    else{
      (scanf("%c",&c) == 1);
      if((c=='Q') || (c=='q')){
        *max = i - 1;
        break;
      } else{
        printf("Invalid input. Please try again.\n");
        i--;
      }
    }
  }
  printf("Table complete.\n");
}

void PrintReverseTable(int a[], int max){
  for(max;max>=0;max--){
    printf("%d\n",a[max]);
  }
}

int main(int argc, char *argv[]){
  int max;

  printf("Enter the maximum number of elements: ");
  scanf("%d", &max);
  max--;

  int table[max];
  memset(table, 0, sizeof(table));
  FillTable(table,&max);
  PrintReverseTable(table,max);

  return 0;
}
