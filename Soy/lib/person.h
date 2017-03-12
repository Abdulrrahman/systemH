#ifndef _PERSON_ 
#define _PERSON_

#include <stdio.h>

typedef struct pinputstruct {
  char *name;               /* persone name */
  char *gender;                 /* persone gender */
} *PE;

extern PE new_pinputstruct(/* persone name and gender */);
extern void jettison_pinputstruct(/* IS */);

#endif