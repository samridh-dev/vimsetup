#include <cp.h>

#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

/* ------------------------------------------------------------------------- */
/* Local Functions                                                           */
/* ------------------------------------------------------------------------- */

static int check_dst(const char* const dst) {
  
        struct stat statbuf;
 
        if (stat(dst, &statbuf) == 0) {
                if (!S_ISDIR(statbuf.st_mode)) {
                        perror("Destination exists but not a directory");
                        return 0;
                }
        } else {
                if (mkdir(dst, 0755) != 0) {
                        perror("Error creating destination directory");
                        return 0;
                }
        }
 
        return 1;

}

/* ------------------------------------------------------------------------- */
/* void vs_cp()                                                              */
/* ------------------------------------------------------------------------- */

void vs_cp(const char* const src, const char* const dst) {

        FILE* fp_src;
        FILE* fp_dst;
        char buf[VS_CP_BUFSIZE];
        size_t nbytes;
 
        fp_src = fopen(src, "r");
        if (fp_src == NULL) {
                 perror("Error opening source file");
                 return;
        }
 
        fp_dst = fopen(dst, "w");
        if (fp_dst == NULL) {
                 perror("Error opening destination file");
                 fclose(fp_src);
                 return;
        }
 
        while ((nbytes = fread(buf, 1, sizeof(buf), fp_src)) > 0) {
                 fwrite(buf, 1, nbytes, fp_dst);
        }

        printf("Successfully copied file: %s to: %s\n", src, dst);

        fclose(fp_src);
        fclose(fp_dst);

}

/* ------------------------------------------------------------------------- */
/* void vs_cpd()                                                             */
/* ------------------------------------------------------------------------- */

#ifdef _WIN32

void vs_cpd(const char* const src, const char* const dst) {

}

#else

void vs_cpd(const char* const src, const char* const dst) {

        DIR* dir;
        struct dirent* entry;
        struct stat statbuf;
        char src_path[VS_CP_BUFSIZE];
        char dst_path[VS_CP_BUFSIZE];

        dir = opendir(src);
        if (dir == NULL) {
                perror("Error opening source directory");
                return;
        }

        if (!check_dst(dst)) {
                closedir(dir);
                return;
        }

        while ((entry = readdir(dir)) != NULL) {

                if (strcmp(entry->d_name, ".")  == 0 ||
                    strcmp(entry->d_name, "..") == 0) {
                        continue;
                }

                sprintf(src_path, "%s/%s", src, entry->d_name);
                sprintf(dst_path, "%s/%s", dst, entry->d_name);

                if (stat(src_path, &statbuf) == -1) {
                        perror("Error getting status of source file");
                        continue;
                }

                if (S_ISDIR(statbuf.st_mode)) {
                        vs_cpd(src_path, dst_path);
                } else {
                        vs_cp(src_path, dst_path);
                }

        }

        closedir(dir);

}

#endif

/* ------------------------------------------------------------------------- */
/* void vs_cpr()                                                             */
/* ------------------------------------------------------------------------- */

void vs_cpr(const char* const src, const char* const dst) {
        struct stat statbuf;

        if (stat(src, &statbuf) == -1) {
                perror("Error getting status of source");
                return;
        }

        if (S_ISDIR(statbuf.st_mode)) {

                if (check_dst(dst)) {
                        vs_cpd(src, dst);
                }

        } else {

                vs_cp(src, dst);

        }

}

/* ------------------------------------------------------------------------- */
/* End                                                                       */
/* ------------------------------------------------------------------------- */
