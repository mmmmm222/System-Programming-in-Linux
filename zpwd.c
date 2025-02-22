#include <unistd.h>
#include <stdio.h>
#define SIZE 100
#include <stdlib.h>
int main(int argc , char* argv[])
{

	char buf[SIZE];
	char * Path_Name = getcwd(buf, SIZE);

	if(Path_Name == NULL)
	{
	   printf("Error in buffer Length\n");
	   exit(-1);
	}
	printf("%s\n",buf); 


}
