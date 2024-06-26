#include <vs.h>

#include <stdlib.h>
#include <stdio.h>

#include <mkdir.h>
#include <rm.h>
#include <cp.h>

/* ------------------------------------------------------------------------- */
/* Local Functions                                                           */
/* ------------------------------------------------------------------------- */

static const char* get_home(void) {

        const char* const HOME = getenv("HOME");
        
        if (HOME == NULL) {
                perror("$HOME environment variable not set");
        }
         
        return HOME;

}

/* ------------------------------------------------------------------------- */
/* void vs_configure                                                         */
/* ------------------------------------------------------------------------- */

#define VS_CONFIG_BUFSIZE 1024
void vs_configure(void) {

        char dst[VS_CONFIG_BUFSIZE];
        char src[VS_CONFIG_BUFSIZE];

        const char* const HOME = get_home();
        
        sprintf(dst, "%s/.vim/", HOME);
        sprintf(src, "./dat/vim/");

        /* delete directory contents */
        vs_rmr(dst);
        
        /* make new directory */
        vs_mkdir(dst);
        
        /* copy contents */
        vs_cpr(src, dst);
                
}

/* ------------------------------------------------------------------------- */
/* void vs_install()                                                         */
/* ------------------------------------------------------------------------- */

void vs_install(void) {
        return;
}

/* ------------------------------------------------------------------------- */
/* End                                                                       */
/* ------------------------------------------------------------------------- */
