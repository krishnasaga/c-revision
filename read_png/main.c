#include <stdio.h>

int main(void){
    FILE *fp;
    fp = fopen("./image.png","rb");
    if(fp == NULL){
      perror("Problem opening file");
      return 1;
    }

    return 0;
}
