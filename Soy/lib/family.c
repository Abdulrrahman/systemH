#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "family.h"

#define talloc(ty, sz) (ty *) malloc (sz * sizeof(ty))

static Fa make_finputstruct(char *father,char *mother,int childrenNo)
{
                            /* "M" for Male */
                         /* "F" for Female */
    Fa fa;
    char *gender;

    fa = talloc(struct finputstruct, 1);

    fa->father = new_pinputstruct(father,"M");
    fa->mother = new_pinputstruct(mother,"F");
    fa->childrenNo = childrenNo;
    fa->childerns = talloc(PE, childrenNo);

    return fa;
}

Fa new_finputstruct(char *father,char *mother,int childrenNo)   /*  Calls malloc */
{
  return make_finputstruct(father, mother,childrenNo);
}

void jettison_finputstruct(Fa fa)
{
  free(fa);
  return;
}