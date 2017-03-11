#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fields.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define falloc(ty, sz) (ty *) malloc (sz * sizeof(ty))//creat anything
//to connect 2 charts to eachother created by me :D Im genius
#define conch(str1,str2) ((char *) strcat(strcpy(falloc(char,1 + strlen(str1)+ strlen(str2)),str1), str2))

typedef struct String{
    char *text;
  }*string;

int main(argc, argv)
int argc;
char **argv;
{
  char * mode="w+" ;                    //mode to write and read for .txt files
  struct stat st = {0};                 //to check the address of folder we made

  if (argc != 2) {                      //error checking for input of program name and the name of family-tree
    fprintf(stderr, "usage: ./soy familyname\n");
    exit(1);
  }

  /*string a = falloc(struct String, 2);
  a[0].text = "mother";
  a[1].text = "w";*/
  
  if (stat(argv[1], &st) == -1) {       //if the folder is not exists creat else do not
    mkdir(argv[1], 0755);
  }
  else
  {
    printf("error the file already exists\n");
  }

  char * filename = conch("./",argv[1]);// look up in define explanation is there
  filename = conch(filename,"/main.txt");//after this comment we have the diroctory of the file like ./familyname/main.txt
  
  if (stat(filename, &st) != -1) {  //is the file exists ?
    printf("error the file already exists\n");
  }
  else
  {
    FILE* fp= fopen(filename, mode);//if not creat one with the filename diroctory
    if (fp == NULL)//if the file didn`t open
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(fp, "file id: %s\n", filename);//write the filename as file id to the .txt file
  }
  printf("%s\n",filename);//that wat we printed to the file
  exit(0);
  return 0;
}