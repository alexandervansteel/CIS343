#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

<<<<<<< HEAD
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
=======
int FillTable(int a[], int max){
  int i;
  for(i=0;i<=max;i++){
    a[i] = i;
>>>>>>> 6f856e5a78a3858f74184fbd0e65d2a5f8b826e0
  }
  printf("Table complete.\n");
}

void PrintReverseTable(int a[], int max){
  for(max;max>=0;max--){
    printf("%d\n",a[max]);
  }
}

<<<<<<< HEAD
int main(int argc, char *argv[]){
  int max;

  printf("Enter the maximum number of elements: ");
  scanf("%d", &max);
  max--;

  int table[max];
  memset(table, 0, sizeof(table));
  FillTable(table,&max);
  
  PrintReverseTable(table,max);
=======
int main(int argc, char const *argv[]) {
  int table[100];
  FillTable(table,10);
  PrintReverseTable(table,10);
>>>>>>> 6f856e5a78a3858f74184fbd0e65d2a5f8b826e0
  return 0;
}
