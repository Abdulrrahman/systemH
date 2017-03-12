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

void createmainfile(char *PATH,char *FamilyName)
{
  struct stat st = {0};
  char * mode="w+" ;
  FILE *fp;

  if (stat(conch(PATH,"/main.txt"), &st) != -1) {  //is the file exists ?
    printf("error the file already exists\n");
  }
  else
  {
    fp= fopen(conch(PATH,"/main.txt"), mode);//if not creat one with the filename diroctory
    if (fp == NULL)//if the file didn`t open
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(fp, "file-id: %s\nFamily-Name: %s", conch(PATH,"/"),FamilyName);//write the filename as file id to the .txt file
    fclose(fp);
  }
}

void createfatherfile(char *PATH)
{
  char * getinpute = falloc(char,25);
  struct stat st = {0};
  char * mode="w+" ;
  FILE *fp;
  PE person;                            //person to get the inputs with it

  if (stat(conch(PATH,"/father.txt"), &st) != -1) {  //is the father file exists ?
      printf("error the file already exists\n");
    }
    else
    {
      fp= fopen(conch(PATH,"/father.txt"), mode);//if not creat one with the filename diroctory
      if (fp == NULL)//if the file didn`t open
      {
        printf("Error opening file!\n");
        exit(1);
      }
      printf("plz inter the name of the Husband : ");
      scanf("%s",getinpute);
      person = new_pinputstruct(getinpute,"M");
      fprintf(fp, "Father: %s\nSex: %s", person->name,person->gender);
      fclose(fp);
    }
}

void createmotherfile(char *PATH)
{
  char * getinpute = falloc(char,25);
  struct stat st = {0};
  char * mode="w+" ;
  FILE *fp;
  PE person;                            //person to get the inputs with it
  if (stat(conch(PATH,"/mother.txt"), &st) != -1) {  //is the mother file exists ?
      printf("error the file already exists\n");
  }
  else
  {
      fp= fopen(conch(PATH,"/mother.txt"), mode);//if not creat one with the filename diroctory
      if (fp == NULL)//if the file didn`t open
      {
        printf("Error opening file!\n");
        exit(1);
      }
      printf("plz inter the name of the Wife : ");
      scanf("%s",getinpute);
      person = new_pinputstruct(getinpute,"F");
      fprintf(fp, "Mother: %s\nSex: %s", person->name,person->gender);
  }

}

void createchildrenfile(char *PATH)
{
  int i;
  IS is;
  char * getinpute = falloc(char,25);
  struct stat st = {0};
  char * mode="w+" ;
  FILE *fp;
  PE person;                            //person to get the inputs with it
  if (stat(conch(PATH,"/children.txt"), &st) != -1) {  //is the children file exists ?
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
        fp= fopen(conch(PATH,"/children.txt"), "a");//if not creat one with the filename diroctory
        if (fp == NULL)//if the file didn`t open
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
        fprintf(fp, "Child: %s\nSex: %s\n", person->name,person->gender);
        printf("To add more Enter (1) otherwise Enter (0) : ");
        scanf("%d",&more);
        if(more == 0)
        {
          fclose(fp);
        }
      }
      while(more);
  }
  is = new_inputstruct(conch(PATH,"/children.txt"));
  if (is == NULL) {
    perror(conch(PATH,"/children.txt"));
    exit(1);
  }
  while(get_line(is) >= 0) {
    for (int i = 0; i < is->NF; i++) {
      if (strcmp(is->fields[0] ,"Child:") == 0 && stat(conch(PATH,is->fields[1]), &st) == -1) {       //if the folder is not exists creat else do not
        mkdir(conch(conch(PATH,"/"),is->fields[1]), 0755);
      }
    }
  }
  jettison_inputstruct(is);
}

typedef struct String{
    char *text;
  }*string;

int main(argc, argv)
int argc;
char **argv;
{
  char *directory = conch("./",argv[1]);
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
  
  createmainfile(directory,argv[1]);
  createfatherfile(directory);
  createmotherfile(directory);
  createchildrenfile(directory);

  
  exit(0);
  return 0;
}