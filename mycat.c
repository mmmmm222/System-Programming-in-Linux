#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define COUNT 100

int main(int argc , char* argv[])
{
	char buf[COUNT];
	int fd =  open(argv[1], O_RDONLY );
	if(fd == -1)
	{
		printf("error if file descriptor");
		exit(-2);
	}

	int num_read = 0 ;
	while((num_read = read(fd, buf, COUNT)) > 0 )
	{
		write(1 , buf, num_read);
	}
	
	//end of file
	printf("\n\n\n file ended \n");
	// close the file
	close(fd);
	exit(0);
}

