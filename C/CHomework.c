#include <stdio.h>
#include <stdlib.h>

int FillTable(int a[], int max){
  int i;
  for(i=0;i<=max;i++){
    a[i] = i;
  }
}

void PrintReverseTable(int a[], int max){
  for(max;max>=0;max--){
    printf("%d\n",a[max]);
  }
}

int main(int argc, char const *argv[]) {
  int table[100];
  FillTable(table,10);
  PrintReverseTable(table,10);
  return 0;
}
