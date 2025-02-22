#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// max number of bytes to be copied each time
#define COUNT 1024

int main(int argc , char* argv[])
{
// buffer to store the read content from source
char buf[COUNT];

// open source file
int src_fd =  open(argv[1], O_RDONLY );

if(src_fd < 0)
{
   write(1 , "unable to open Source file" , strlen("unable to open Source file" ));
   exit(-1);
}

//open or create destination file
int dest_fd =  open(argv[2], O_WRONLY| O_CREAT , 0644);

if(dest_fd < 0)
{
   write(1 , "unable to open destination file\n" ,strlen("unable to open destination file\n"));
   exit(-2);
}

int num_read = 0 ;
while((num_read = read(src_fd, buf, COUNT)) > 0 )
{
 if( (write(dest_fd, buf, num_read) != num_read) )
 {
    write(1 ,"error while writing\n" , strlen("error while writing\n"));
    exit(-3);
 }
}

close(src_fd);
close(dest_fd);

}
