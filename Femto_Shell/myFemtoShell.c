#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>


#define BUF_COUNT 100

int
main (int argc, char **argv)
{
  char buf[BUF_COUNT];

  while (1)
    {
      printf ("Femto shell prompt > ");

      // Take the command from the user
      char *fgets_ret = fgets (buf, BUF_COUNT, stdin);
      if (fgets_ret == NULL)
	{
	  printf ("error while reading from stdin");
	}
      // remove the /n from the end of the buffer , put null
      buf[strlen (buf) - 1] = 0;
      // check if the user just entered an "enter"
      if (strlen (buf) == 0)
	{
	  continue;
	}
      // check if the user wants to end the program
      else if (strcmp (buf, "exit") == 0)

	{
	  printf ("Good Bye :)\n");
	  return 0;
	}
      else if (strncmp (buf, "echo", 4) == 0)
	{

	  for (int i = 5; i < strlen (buf); i++)
	    {
	      printf ("%c", buf[i]);
	    }
	  printf ("\n");

	}
      else
	{
	  printf ("Invalid command\n");
	}
    }
  return 0;
}
