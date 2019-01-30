#include <stdio.h>
#include <stdlib.h>

int glob1 = 0x33;
int glob2; 


int main()
{

//   char *ptr = 0x00000000; 
//   char *ptr = 0x08048000; 
//   char *ptr = 0xc0000000; 

//   *ptr = 0xaa;

   int local1 = 0x55;

   printf("address glob1 is %x\n", &glob1); 

   printf("address glob2 is %x\n", &glob2); 
   
   printf("address local1 is %x\n", &local1); 
  

    printf("address main is %x\n", &main); 
   
   while(1);

   exit(0); 

} 
