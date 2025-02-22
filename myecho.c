#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(int argc , char* argv[])
{
  int COUNT = 1;
  while(argv[COUNT] != NULL)
  {
    write(1 , argv[COUNT] , strlen(argv[COUNT]));
    if(argv[COUNT+1] != NULL)
    {
	write(1 , " " , 1 );    
    } 
    COUNT++;
  }
  write(1 , "\n" , 1 );

}
