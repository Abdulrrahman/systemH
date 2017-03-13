#ifndef _FAMILY_ 
#define _FAMILY_

#include <stdio.h>
#include "person.h"

typedef struct finputstruct {
  char* familyname;
  PE father;               /* father */
  PE mother;                /* mother */
  PE me;
  int childrenNo;
  PE *childerns;
} *Fa;

extern Fa new_finputstruct(char*,char*,char*,PE,int);
extern void jettison_finputstruct(/* Fa */);

#endif