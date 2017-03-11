#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fields.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define falloc(ty, sz) (ty *) malloc (sz * sizeof(ty))

typedef struct String{
    char *text;
  }*string;

int main(argc, argv)
int argc;
char **argv;
{
  if (argc != 2) {
    fprintf(stderr, "usage: ./soy familyname\n");
    exit(1);
  }
  string a = falloc(struct String, 2);
  a[0].text = "mother";
  a[1].text = "w";
  
  struct stat st = {0};

  if (stat(argv[1], &st) == -1) {
    mkdir(argv[1], 0755);
  }
  const char * filename = "./adam/sample.txt";
  const char * mode="w+" ;
  if (stat(filename, &st) != -1) {
    printf("error the file already exists\n");
  }
  FILE* fp= fopen(filename, mode);

  exit(0);
  return 0;
}