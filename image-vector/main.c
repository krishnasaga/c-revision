#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t** create_empty_image_vector(unsigned int width,unsigned int height){
    uint32_t** image_vector;
    image_vector = (uint32_t **) malloc(8*100);
    printf("%ld\n", sizeof(image_vector)*100*100);

    for(int i = 0;i<100;++i){
      image_vector[i] = (uint32_t *) malloc(8*100);
    }

    for(int i = 0;i<100;++i){
        for(int j = 0;j<100;++j){
            image_vector[i][j] = 0;
        }
    }
   return  image_vector;
}

void distroy_image_vector(uint32_t** image_vector){
    free(image_vector);
}

void draw_stright_line(uint32_t** image_vector,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2){
    for(int i = 0;i<100;++i){
        for(int j = 0;j<100;++j){
            if((y2 - y1)*i - (x2 - x1)*j + (x2*y1 - x1*y2) == 0){
                image_vector[i][j] = 1;
            }
        }
    }
}

int main(void){
    uint32_t** image_vector = create_empty_image_vector(100,100);
    draw_stright_line(image_vector,10,10,20,20);
    for(int i = 0;i<100;++i){
        for(int j = 0;j<100;++j){
            printf("%d",image_vector[i][j]);
        }
         printf("\n");
    }


    distroy_image_vector(image_vector);
}
