#include <rm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

/* ------------------------------------------------------------------------- */
/* void vs_rm()                                                              */
/* ------------------------------------------------------------------------- */

void vs_rm(const char* const fname) {

        if (fname == NULL) {
                fprintf(stderr, "Error: Null file name provided.\n");
                return;
        }

        if (remove(fname) == 0) {
                printf("Successfully deleted file: %s\n", fname);
        } else {
                fprintf(stderr, "Warning: Could not delete file: %s: ", fname);
                perror("");
        }

}

/* ------------------------------------------------------------------------- */
/* void vs_rmd()                                                             */
/* ------------------------------------------------------------------------- */

void vs_rmd(const char* const dname) {

        if (dname == NULL) {
                fprintf(stderr, "Error: Null directory name provided.\n");
                return;
        }

        if (rmdir(dname) == 0) {
                printf("Successfully deleted directory: %s\n", dname);
        } else {
                perror("Error deleting directory");
        }

}

/* ------------------------------------------------------------------------- */
/* void vs_rmr()                                                             */
/* ------------------------------------------------------------------------- */

#define VS_RMR_BUFSIZE 1024
void vs_rmr(const char* const name) {

        DIR* dir;
        struct dirent *entry;
        struct stat statbuf;
        char path[VS_RMR_BUFSIZE];
 
        if (stat(name, &statbuf) == -1) {
                 perror("Error getting status of source");
                 return;
        }
 
        if (S_ISDIR(statbuf.st_mode)) {

                dir = opendir(name);
                if (dir == NULL) {
                         perror("Error opening directory");
                         return;
                }
                
                while ((entry = readdir(dir)) != NULL) {

                        if (strcmp(entry->d_name, ".")  == 0 || 
                            strcmp(entry->d_name, "..") == 0) {
                                 continue;
                        }
                
                        sprintf(path, "%s/%s", 
                                name, entry->d_name);

                        vs_rmr(path);

                }
                
                closedir(dir);
                
                vs_rmd(name);

        } else {
                vs_rm(name);
        }

}

/* ------------------------------------------------------------------------- */
/* End                                                                       */
/* ------------------------------------------------------------------------- */
