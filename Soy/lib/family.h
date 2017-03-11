#ifndef _FAMILY_ 
#define _FAMILY_

#include <stdio.h>
#include "person.h"

typedef struct finputstruct {
  PE father;               /* father */
  PE mother;                /* mother */
  int childrenNo;
  PE *childerns;
} *Fa;

extern Fa new_finputstruct(char*,char*,int);
extern void jettison_finputstruct(/* Fa */);

#endif