#include<stdio.h>

 

#define MAP_X 28

#define MAP_Y 100

 

char map[MAP_X][MAP_Y] ={

 

   { "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000111111111111110000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000011111111111111111111111111000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000011111111111000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" },

   { "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111" }

 

};

 

 

 

void draw() {

 

   int h, w;

   char temp;

 

   system("cls");

   for (h = 0; h < MAP_X; h++) {

      for (w = 0; w < MAP_Y; w++) {

         

         temp = map[h][w];

         if (temp == '0') {

            printf(" ");

         }

         else if (temp == '1') {

            printf("#");

         }

      }

      printf("\n");

   }

}

 

 

int main() {

 

 

   draw();

 

   return 0;

}