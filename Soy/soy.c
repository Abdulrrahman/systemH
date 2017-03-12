#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fields.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <person.h>

#define falloc(ty, sz) (ty *) malloc (sz * sizeof(ty))//creat anything
#define txtcopy(s) ((char *) strcpy(falloc(char, strlen(s)+1), s))
//to connect 2 charts to eachother created by me :D Im genius
#define conch(str1,str2) ((char *) strcat(strcpy(falloc(char,1 + strlen(str1)+ strlen(str2)),str1), str2))

typedef struct String{
    char *text;
  }*string;

int main(argc, argv)
int argc;
char **argv;
{
  char *directory = conch("./",argv[1]);
  char * getinpute = falloc(char,25);

  char * mode="w+" ;                    //mode to write and read for .txt files
  struct stat st = {0};                 //to check the address of folder we made

  PE person;                            //person to get the inputs with it

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
  
  if (stat(conch(directory,"/main.txt"), &st) != -1) {  //is the file exists ?
    printf("error the file already exists\n");
  }
  else
  {
    FILE* fp= fopen(conch(directory,"/main.txt"), mode);//if not creat one with the filename diroctory
    if (fp == NULL)//if the file didn`t open
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(fp, "file-id: %s\nFamily-Name: %s", conch(directory,"/"),argv[1]);//write the filename as file id to the .txt file
  }

  if (stat(conch(directory,"/father.txt"), &st) != -1) {  //is the father file exists ?
      printf("error the file already exists\n");
    }
    else
    {
      FILE* fpf= fopen(conch(directory,"/father.txt"), mode);//if not creat one with the filename diroctory
      if (fpf == NULL)//if the file didn`t open
      {
        printf("Error opening file!\n");
        exit(1);
      }
      printf("plz inter the name of the Husband : ");
      scanf("%s",getinpute);
      person = new_pinputstruct(getinpute,"M");
      fprintf(fpf, "Father: %s\nSex: %s", person->name,person->gender);
    }

  if (stat(conch(directory,"/mother.txt"), &st) != -1) {  //is the mother file exists ?
      printf("error the file already exists\n");
  }
  else
  {
      FILE* fpm= fopen(conch(directory,"/mother.txt"), mode);//if not creat one with the filename diroctory
      if (fpm == NULL)//if the file didn`t open
      {
        printf("Error opening file!\n");
        exit(1);
      }
      printf("plz inter the name of the Wife : ");
      scanf("%s",getinpute);
      person = new_pinputstruct(getinpute,"F");
      fprintf(fpm, "Mother: %s\nSex: %s", person->name,person->gender);
  }

  if (stat(conch(directory,"/children.txt"), &st) != -1) {  //is the children file exists ?
      printf("error the file already exists\n");
  }
  else
  {
      int more = 1;
      do
      {
        int Wronggender = 1;
        char *name;
        char *gnder;
        FILE* fpc= fopen(conch(directory,"/children.txt"), "a");//if not creat one with the filename diroctory
        if (fpc == NULL)//if the file didn`t open
        {
          printf("Error opening file!\n");
          exit(1);
        }
        printf("plz inter the name of the child : ");
        scanf("%s",getinpute);
        name = txtcopy(getinpute);
        printf("plz inter the gender of the child (M/m or F/f) : ");
        scanf("%s",getinpute);
        while(1)
        {
          if(strcmp(getinpute ,"M") == 0 || strcmp(getinpute ,"m") == 0 || strcmp(getinpute ,"F") == 0|| strcmp(getinpute ,"f") == 0 )
          {
            break;
          }
          else
          {
            printf("Eror Incorrect \nplz reEnter the gender of the child (M/m or F/f) : ");
            scanf("%s",getinpute);
          }
          
        }
        gnder = txtcopy(getinpute);
        person = new_pinputstruct(name,gnder);
        fprintf(fpc, "Child: %s\nSex: %s\n", person->name,person->gender);
        printf("To add more Enter (1) otherwise Enter (0) : ");
        scanf("%d",&more);
      }
      while(more);
      
  }
  
  
  system("clear");
  exit(0);
  return 0;
}