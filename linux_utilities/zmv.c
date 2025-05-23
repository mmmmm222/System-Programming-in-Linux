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
   // array of string to carry the concatinated path
   char* conc[1];

   conc[0] = strcat(argv[2] , argv[1]);

   dest_fd =  open(conc[0], O_WRONLY| O_CREAT , 0644);
   printf("new path is %s \n", conc[0]);
   if(dest_fd < 0)
   {
     write(1 , "unable to open destination file\n" ,strlen("unable to open destination file\n"));
     exit(-2);
   }
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

//delete source file
int rm_state = unlink(argv[1]);
if(rm_state != 0)
{
  write(1 ,"error while deleting source file\\n" , strlen("error while deleting source file\n"));
}

close(src_fd);
close(dest_fd);

}
