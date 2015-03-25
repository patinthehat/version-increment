#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>

#include "utils.h"


#define __USE_GNU



int BUF_SIZE = 128;


//set to 1 to increment major version when minor reached 100. i.e.:
//1.99.0 + 0.01.0 = 1.100.0 = 2.0.0
#define ON_MINOR_100_INCREMENT_MAJOR_FIELD 0

typedef int version_numbers_t[3];

typedef struct version_numbers_s {
  int major;
  int minor;
  int patch;
} version_numbers;

typedef version_numbers* version_numbers_ptr;

#define VERNUMIDX2(vn,idx) (idx >= 2 ? vn.patch : vn.minor)
#define VERNUMIDX(vn,idx) (idx == 0 ? vn.major : VERNUMIDX2(vn,idx))

int increaseVersion(version_numbers* versionData, int index, int amount)
{
  switch(index) {
    case 0:
      versionData->major = versionData->major + amount;
      versionData->minor = 0;
      versionData->patch = 0;
      return 1;
    case 1:
      versionData->minor = versionData->minor + amount;
      versionData->patch = 0;
      #ifdef ON_MINOR_100_INCREMENT_MAJOR_FIELD
        if (versionData->minor >= 100) {
          versionData->minor = 0;
          versionData->major = versionData->major + 1;
          return 1;
        }
      #endif
      return 1;
    case 2:
      versionData->patch = versionData->patch + amount;
      return 1;
  }
}

void echo(char * s) {
  printf("%s\n", s);
}

void usage(int argc, char** argv) {
  printf("Usage: %s [version(x.y.z)] [index-to-increment] [increment-by]\n", argv[0]);
  printf("If '-' is passed as the version number, the version will be read from stdin.\n");
  exit(EXIT_FAILURE);
}

int assign_vd_from_version_numbers(version_numbers * vd, version_numbers_t vn) {
  memcpy((version_numbers_t*)vd, vn, sizeof(int)*3);
  return(EXIT_SUCCESS);
}



int main(int argc, char ** argv)
{
  version_numbers vd;
  char filenameStr[BUF_SIZE];
  char versionBuf[BUF_SIZE];
  
  if (argc == 1) {
    usage(argc,argv);
  }

  char * versionStr = argv[1];
  //versionStr = malloc(BUF_SIZE);
  //memcpy(versionStr, argv[1], BUF_SIZE);
  int indexToIncrement;
  int incrementBy;
  int useVersionFromFile = 0;

  if (file_exists(versionStr)) {
    memcpy((char*)filenameStr, versionStr, BUF_SIZE);
    file_read(versionStr, (char *)versionBuf, 128);
    useVersionFromFile = 1;
    memmove(versionBuf, (char*)versionBuf, BUF_SIZE);
    printf("%s\n", versionBuf);    
    memmove(versionStr, versionBuf, BUF_SIZE);
  } else {
    
    if (strcmp(versionStr, "-")==0) {
      char buf[BUF_SIZE];
      int cRead = read_from_stdin((char *)buf);
      memmove(versionStr, (char*)buf, BUF_SIZE);
    }
  }
    switch(argc) {
      case 2:
        indexToIncrement   = 2;
        incrementBy        = 1;
        break;
      case 3:
        indexToIncrement   = 2;
        incrementBy        = atoi(argv[3]);
        break;
      case 4:
        indexToIncrement   = atoi(argv[2]);
        incrementBy        = atoi(argv[3]);
        break;
      default:
        //indexToIncrement = 2;
        //incrementBy = 1;
        break;
    }
    
    
    if (useVersionFromFile == 1) {
    //  memmove((char*)versionStr, (char*)useVersionFromFile, BUF_SIZE);
    }
  
/*
  if (strcmp(argv[2], "major") == 0)
    indexToIncrement = 0;
  if (strcmp(argv[2], "minor") == 0)
    indexToIncrement = 1;
  if (strcmp(argv[2], "patch") == 0)
    indexToIncrement = 2;  
  */
  const char s[2] = ".";
  char *token;
  char *str1 = versionStr;

  int versionNumbers[3] = {0, 0, 0};

  /* walk through other tokens */
  int index = 0;

  /* get the first token */
  token = strtok(str1, s);
  while( token != NULL )
  {
    versionNumbers[index] = atoi(token);
    token = strtok(NULL, s);
    index++;
  }

  
  assign_vd_from_version_numbers(&vd, versionNumbers);
  increaseVersion(&vd, indexToIncrement, incrementBy);
  
  char vbuf[BUF_SIZE];
  sprintf((char*)vbuf, "%d.%d.%d\n", (int)vd.major, (int)vd.minor, (int)vd.patch);
  printf("%s", (char*)vbuf);
  
  //file_write((char*)filenameStr, (char*)vbuf);
    if (useVersionFromFile == 1) {
      FILE *fp;
      fp = fopen(filenameStr, "w");
      printf("%s\n", filenameStr);
      fprintf(fp, "%s", (char*)vbuf);// "%d.%d.%d\n", (int)vd.major, (int)vd.minor, (int)vd.patch);
      fclose(fp);
    }
  /**/

  return(EXIT_SUCCESS);
}
