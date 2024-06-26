#include <mkdir.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

/* ------------------------------------------------------------------------- */
/* void vs_mkdir()                                                           */
/* ------------------------------------------------------------------------- */

void vs_mkdir(const char* const dir) {

        if (dir == NULL) {
                fprintf(stderr, "Error: Null directory name provided.\n");
                return;
        }

        if (mkdir(dir, 0755) == 0) {
                return;
        } else if (errno == EEXIST) {
                return;
        } else {
                perror("Error creating directory");
        }

}

/* ------------------------------------------------------------------------- */
/* End                                                                       */
/* ------------------------------------------------------------------------- */
