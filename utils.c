#ifndef TRUE
  #define TRUE 1
#endif
#ifndef FALSE
  #define FALSE 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

//#include <fcntl.h>

/**
 * Checks if a file exists or not.
 * uses stat(), which is slightly faster
 * @return int Returns 1 if the file exists, otherwise 0
 */
int file_exists(char *filename)
{
  struct stat buffer;
  if (stat(filename, &buffer) == 0)
    return 1;
  return 0;
}


int file_read(char* filename, char * buf, int size)
{
  FILE *ifp;

  ifp = fopen(filename, "r+");
  if (ifp == NULL) {
    fprintf(stderr, "Can't open input file\n");
    return FALSE;
  }
  int success = fscanf(ifp, "%s", buf);
  if (!success)
    return FALSE;
  fclose(ifp);
  return TRUE;
}


int file_write(char* filename, char* data) {
  FILE *fp;
  fp = fopen(filename, "w+");

  if (fp == NULL) {
    fprintf(stderr, "%s\n", "Can't open input file");
    return FALSE;
  }
  fprintf(fp, "%s", data);
  fclose(fp);
  return TRUE;
}


int read_from_stdin(char * buf) {
  int ret = scanf("%s", buf);
  return ret;
}
