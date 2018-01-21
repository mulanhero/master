#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void my_print (char *string)
{
  printf ("The string is %s\n", string);
}



void my_print2 (char *string)
{
  char *string2;
  int size, i;

  size = strlen (string);
  string2 = (char *) malloc (size + 1);
  for (i = 0; i < size; i++)
    string2[size - i] = string[i];
  string2[size+1] = '\0';
  printf ("The string printed backward is %s\n", string2);
}

int main ()
{
  char my_string[] = "hello there";
  my_print (my_string);
  my_print2 (my_string);
  return 0;
}

