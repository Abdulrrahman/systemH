#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "family.h"

#define talloc(ty, sz) (ty *) malloc (sz * sizeof(ty))

static Fa make_finputstruct(char *familyname,char *father,char *mother,PE me,int childrenNo)
{
                            /* "M" for Male */
                         /* "F" for Female */
    Fa fa;
    char *gender;

    fa = talloc(struct finputstruct, 1);
    fa->familyname = familyname;
    fa->father = new_pinputstruct(father,"M");
    fa->mother = new_pinputstruct(mother,"F");
    fa->me = new_pinputstruct(me->name,me->gender);
    fa->childrenNo = childrenNo;

    return fa;
}

Fa new_finputstruct(char *familyname,char *father,char *mother,PE me,int childrenNo)   /*  Calls malloc */
{
  return make_finputstruct(familyname,father, mother,me,childrenNo);
}

void jettison_finputstruct(Fa fa)
{
  free(fa);
  return;
}