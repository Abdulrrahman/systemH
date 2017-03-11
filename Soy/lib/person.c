#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "person.h"

#define talloc(ty, sz) (ty *) malloc (sz * sizeof(ty))

static PE make_pinputstruct(char *personename, char *key)
{
                            /* "M" for Male */
                         /* "F" for Female */
    PE is;
    char *gender;

    if (strcmp(key, "M") == 0 || strcmp(key, "m") == 0) {
        gender = "Male";
    } else if (strcmp(key, "F") == 0 || strcmp(key, "f") == 0) {
        gender = "Female";
    } else {
        return NULL;
    }

    is = talloc(struct pinputstruct, 1);

    is->name = personename;
    is->gender = gender;

    return is;
}

PE new_pinputstruct(char *personename,char *gender)   /*  Calls malloc */
{
  return make_pinputstruct(personename, gender);
}

void jettison_pinputstruct(PE is)
{
  free(is);
  return;
}