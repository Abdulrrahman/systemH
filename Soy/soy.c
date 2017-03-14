#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fields.h>
#include <family.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <person.h>

#define falloc(ty, sz) (ty *) malloc (sz * sizeof(ty))//creat anything
#define txtcopy(s) ((char *) strcpy(falloc(char, strlen(s)+1), s))
//to connect 2 charts to eachother created by me :D Im genius
#define conch(str1,str2) ((char *) strcat(strcpy(falloc(char,1 + strlen(str1)+ strlen(str2)),str1), str2))

void deleteEnd (char* myStr){

    char *del = &myStr[strlen(myStr)];

    while (del > myStr && *del != '/')
    {
        del--;
    }
    if (*del== '/')
    {
        *del= '\0';
    }
}

char *getfamilyname(char*directory)
{
  int i;
  IS is;
  is = new_inputstruct(conch(directory,"/main.txt"));
  if (is == NULL) {
    perror(conch(directory,"/main.txt"));
    exit(1);
  }
  while(get_line(is) >= 0) {
    for (int i = 0; i < is->NF; i++) {
      if (strcmp(is->fields[0] ,"Family-Name:") == 0 ) {       //if the folder is not exists creat else do not
        return txtcopy(is->fields[1]);
        break;
      }
    }
  }
}

int findme(char*directory)
{
  struct stat st = {0};
  if (stat(directory, &st) == -1 && S_ISDIR(st.st_mode) == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

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

void createfatherfile(char *PATH,char *getinpute)
{
  IS is;
  char * getmyparents = txtcopy(PATH);
  struct stat st = {0};
  char * mode="w" ;
  FILE *fp;
  PE person;                            //person to get the inputs with it
  fp= fopen(conch(PATH,"/father.txt"), mode);//if not creat one with the filename diroctory
  if (fp == NULL)//if the file didn`t open
  {
    printf("Error opening file!\n");
    exit(1);
  }
  person = new_pinputstruct(getinpute,"M");
  fprintf(fp, "Father: %s\nSex: %s\n", person->name,person->gender);
  fclose(fp);
  deleteEnd(getmyparents);
  char * me = txtcopy(getmyparents);
  getmyparents = conch(getmyparents,"/father.txt");
  fp= fopen(getmyparents, "r+");
  if (fp == NULL || findme(conch(me,conch("/",getinpute)))== 0)//if the file didn`t open
  {
      fp= fopen(conch(PATH,"/father.txt"), "a+");
      fprintf(fp, "MyFather: Adam\n");
      fclose(fp);
  }
  else
  {
    is = new_inputstruct(getmyparents);
    int f = 0;
    while(get_line(is) >= 0) {
      for (int i = 0; i < is->NF; i++) {
        if (strcmp(is->fields[i] ,"Father:") == 0 ) {
          
          fp= fopen(conch(PATH,"/father.txt"), "a+");
          fprintf(fp, "MyFather: %s\n",is->fields[1]);
          fclose(fp);
          f=1;
          break;
        }
      }
      if(f==1)
      {
        break;
      }
    }
  }
  deleteEnd(getmyparents);
  getmyparents = conch(getmyparents,"/mother.txt");
  fp= fopen(getmyparents, "r+");
  if (fp == NULL || findme(conch(me,conch("/",getinpute)))== 0)//if the file didn`t open
  {
      fp= fopen(conch(PATH,"/father.txt"), "a+");
      fprintf(fp, "MyMother: Eve\n");
      fclose(fp);
  }
  else
  {
    is = new_inputstruct(getmyparents);
    int f = 0;
    while(get_line(is) >= 0) {
      for (int i = 0; i < is->NF; i++) {
        if (strcmp(is->fields[i] ,"Mother:") == 0 ) {
          fp= fopen(conch(PATH,"/father.txt"), "a+");
          fprintf(fp, "MyMother: %s\n",is->fields[1]);
          fclose(fp);
          f=1;
          break;
        }
      }
      if(f==1)
      {
        break;
      }
    }
  }
}

void createmotherfile(char *PATH,char * getinpute)
{
  IS is;
  char * getmyparents = txtcopy(PATH);
  struct stat st = {0};
  char * mode="w" ;
  FILE *fp;
  PE person;                            //person to get the inputs with it
  fp= fopen(conch(PATH,"/mother.txt"), mode);//if not creat one with the filename diroctory
  if (fp == NULL)//if the file didn`t open
  {
    printf("Error opening file!\n");
    exit(1);
  }
  person = new_pinputstruct(getinpute,"F");
  fprintf(fp, "Mother: %s\nSex: %s\n", person->name,person->gender);
  fclose(fp);
  deleteEnd(getmyparents);
  char * me = txtcopy(getmyparents);
  getmyparents = conch(getmyparents,"/father.txt");
  fp= fopen(getmyparents, "r+");
  if (fp == NULL || findme(conch(me,conch("/",getinpute)))== 0)//if the file didn`t open
  {
      fp= fopen(conch(PATH,"/mother.txt"), "a+");
      fprintf(fp, "MyFather: Adam\n");
      fclose(fp);
  }
  else
  {
    is = new_inputstruct(getmyparents);
    int f = 0;
    while(get_line(is) >= 0) {
      for (int i = 0; i < is->NF; i++) {
        if (strcmp(is->fields[i] ,"Father:") == 0 ) {
          
          fp= fopen(conch(PATH,"/mother.txt"), "a+");
          fprintf(fp, "MyFather: %s\n",is->fields[1]);
          fclose(fp);
          f=1;
          break;
        }
      }
      if(f==1)
      {
        break;
      }
    }
  }
  deleteEnd(getmyparents);
  getmyparents = conch(getmyparents,"/mother.txt");
  fp= fopen(getmyparents, "r+");
  if (fp == NULL || findme(conch(me,conch("/",getinpute)))== 0)//if the file didn`t open
  {
      fp= fopen(conch(PATH,"/mother.txt"), "a+");
      fprintf(fp, "MyMother: Eve\n");
      fclose(fp);
  }
  else
  {
    is = new_inputstruct(getmyparents);
    int f = 0;
    while(get_line(is) >= 0) {
      for (int i = 0; i < is->NF; i++) {
        if (strcmp(is->fields[i] ,"Mother:") == 0 ) {
          fp= fopen(conch(PATH,"/mother.txt"), "a+");
          fprintf(fp, "MyMother: %s\n",is->fields[1]);
          fclose(fp);
          f=1;
          break;
        }
      }
      if(f==1)
      {
        break;
      }
    }
  }
}

void createchildrenfile(char *PATH)
{
  int i;
  IS is;
  char * getinpute = falloc(char,250);
  struct stat st = {0};
  char * mode="a+" ;
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
        fp= fopen(conch(PATH,"/children.txt"), "a+");//if not creat one with the filename diroctory
        if (fp == NULL)//if the file didn`t open
        {
          printf("Error opening file!\n");
          exit(1);
        }
        printf("plz inter the name of the child : ");
        scanf("%s",getinpute);
        name = txtcopy(getinpute);
        getinpute = conch("/",getinpute);
        if (stat(conch(PATH,getinpute), &st) == -1 && S_ISDIR(st.st_mode) == 0) {       //if the folder is not exists creat else do not
          mkdir(conch(conch(PATH,"/"),name), 0755);
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
        }
        else
        {
          printf("This child: %s is already exists\n",name);
        }
        
        printf("To add more Enter (1) otherwise Enter (0) : ");
        scanf("%d",&more);
        fclose(fp);
      }
      while(more);
  }
}

void getfamilydetails(char *PATH)
{
  int i;
  IS is;
  char * getinpute = falloc(char,25);

  is = new_inputstruct(conch(PATH,"/main.txt"));
  if (is == NULL) {
    perror(conch(PATH,"/main.txt"));
    exit(1);
  }
  while(get_line(is) >= 0) {
    for (int i = 0; i < is->NF; i++) {
      if (strcmp(is->fields[0] ,"Family-Name:") == 0 ) {       //if the folder is not exists creat else do not
        printf("Family Name = %s\n",is->fields[1]);
        break;
      }
    }
  }

  is = new_inputstruct(conch(PATH,"/father.txt"));
  if (is == NULL) {
    perror(conch(PATH,"/father.txt"));
    exit(1);
  }
  while(get_line(is) >= 0) {
    for (int i = 0; i < is->NF; i++) {
      if (strcmp(is->fields[i] ,"Father:") == 0 ) {      
        printf("Husband\n\tName = %s\n\tSex = %s\n",is->fields[1],"Male");
      }
      if (strcmp(is->fields[i] ,"MyFather:") == 0 ) { 
        printf("\tMyFather: = %s\n",is->fields[1]);
      }
      if (strcmp(is->fields[i] ,"MyMother:") == 0 ) {      
        printf("\tMyMother: = %s\n",is->fields[1]);
      }
    }
  }

  is = new_inputstruct(conch(PATH,"/mother.txt"));
  if (is == NULL) {
    perror(conch(PATH,"/mother.txt"));
    exit(1);
  }
  while(get_line(is) >= 0) {
    for (int i = 0; i < is->NF; i++) {
      if (strcmp(is->fields[i] ,"Mother:") == 0 ) {       //if the folder is not exists creat else do not
        printf("Wife\n\tName = %s\n\tSex = %s\n",is->fields[1],"Female");
      }
      if (strcmp(is->fields[i] ,"MyFather:") == 0 ) { 
        printf("\tMyFather: = %s\n",is->fields[1]);
      }
      if (strcmp(is->fields[i] ,"MyMother:") == 0 ) {      
        printf("\tMyMother: = %s\n",is->fields[1]);
      }
    }
  }

  is = new_inputstruct(conch(PATH,"/children.txt"));
  if (is == NULL) {
    perror(conch(PATH,"/children.txt"));
    exit(1);
  }

  is = new_inputstruct(conch(PATH,"/children.txt"));
  int y = 0;
  while(get_line(is) >= 0) {
     for (int i = 0; i < is->NF; i++) {
      if (strcmp(is->fields[i] ,"Child:") == 0 ) {
        getinpute = txtcopy(is->fields[1]);
        printf("child:\n\tName = %s\n\t",is->fields[1]);
      }
      if (strcmp(is->fields[i] ,"Sex:") == 0 ) {       //if the folder is not exists creat else do not
        printf("Sex = %s\n",is->fields[1]);
      }
     }
  }
}


void enterfather(char *directory)
{
  char *getinput = falloc(char,250);
  struct stat st = {0};                //to check the address of folder we made
  if (stat(conch(directory,"/father.txt"), &st) != -1) {  //is the father file exists ?
      printf("error the file already exists\n");
    }
  else
  {
      printf("plz inter the name of the Husband : ");
      scanf("%s",getinput);
      createfatherfile(directory,getinput);
  }
}

void entermother(char *directory)
{
  char *getinput = falloc(char,250);
  struct stat st = {0};                //to check the address of folder we made
  if (stat(conch(directory,"/mother.txt"), &st) != -1) {  //is the father file exists ?
      printf("error the file already exists\n");
    }
  else
  {
      printf("plz inter the name of the Wife : ");
      scanf("%s",getinput);
      createmotherfile(directory,getinput);
  }
}

int main(argc, argv)
int argc;
char **argv;
{
  char *getinput = falloc(char,250);
      
  if (argc != 2) {//error checking for input of program name and the name of family-tree
    fprintf(stderr, "usage: ./soy FamilyName\n");
    exit(1);
  }

  char *directory = conch("./",argv[1]);
  struct stat st = {0};                //to check the address of folder we made

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
  enterfather(directory);
  entermother(directory);
  createchildrenfile(directory);
  getfamilydetails(directory);

  int getout;
  IS is;
  PE pe;
  do
  {
    getout = 0;

    char *sbdirectory;
    printf("please enter persone name to enter his family details : ");
    scanf("%s",getinput);
    sbdirectory = conch(directory,conch("/",getinput));
    if (stat(sbdirectory, &st) == 0)
    {
      int found = 0;
      is = new_inputstruct(conch(directory,"/children.txt"));
      while(get_line(is) >= 0) {
        for (int i = 0; i < is->NF; i++) {
          if(found == 1)
          {
            if(strcmp(is->fields[1],"Male")== 0)
            {
              pe = new_pinputstruct(txtcopy(getinput),"m");
            }
            else
            {
              pe = new_pinputstruct(txtcopy(getinput),"f");
            }
            found = 2;
            break;
          }
          if (strcmp(is->fields[1] ,getinput) == 0 ) {
            found = 1;
            break;
          }
        }
        if(found == 2)
        {
          break;
        }
      }

      if(strcmp(pe->gender,"Male")==0)
      {
        createmainfile(sbdirectory,getfamilyname(directory));
        createfatherfile(sbdirectory,pe->name);
        entermother(sbdirectory);
        createchildrenfile(sbdirectory);
      }
      else if(strcmp(pe->gender,"Female")==0)
      {
        if (stat(conch(sbdirectory,"/main.txt"), &st) != -1)
        {
          printf("error the file already exists\n");
        }
        else{
          printf("Please enter the family name : ");
          scanf("%s",getinput);
          createmainfile(sbdirectory,getinput);
        }
        enterfather(sbdirectory);
        createmotherfile(sbdirectory,pe->name);
        createchildrenfile(sbdirectory);
      }
    }
    else
    {
      printf("Sorry this person is not exists please reEnter a correct name !!\n");
    }
  }
  while(1);
  exit(0);
  return 0;
}