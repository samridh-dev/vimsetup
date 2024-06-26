#include <vs.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------------- */
/* Command Line Functions                                                    */
/* ------------------------------------------------------------------------- */

static void vs_print_version(int argc, char* argv[]) {
      (void) argc;

      printf("Usage: %s [OPTIONS]\n", argv[0]);

}

static void vs_print_help(int argc, char* argv[]) {
      (void) argc;

      printf("Usage: %s [OPTIONS]\n", argv[0]);
      printf("Options:\n");
      printf("  -h, --help           Display this help message and exit\n");
      printf("  -v, --version        Display version and exit\n");
      printf("      --full           Install and configure Vim\n");
      printf("      --install        Only install Vim\n");
      printf("      --config         Add personal configuration to Vim\n");

}

static void vs_parseopts(int argc, char* argv[],
                         int* f_full, int* f_config, int* f_install) {
        
        int i;

        *f_full = 0;
        *f_config = 0;
        *f_install = 0;

        if (argc == 1) {
          vs_print_version(argc, argv);
          exit(0);
        }
        
        i = 1;
        while (i < argc) {
                
                if (strcmp(argv[i], "-h") == 0 || 
                    strcmp(argv[i], "--help") == 0) {
                        vs_print_help(argc, argv);
                        exit(0);
                } 

                if (strcmp(argv[i], "-v") == 0 || 
                    strcmp(argv[i], "--version") == 0) {
                        vs_print_version(argc, argv);
                        exit(0);
                } 

                if (strcmp(argv[i], "--full") == 0) {
                        *f_full = 1;
                } else if (strcmp(argv[i], "--config") == 0) {
                        *f_config = 1;
                } else if (strcmp(argv[i], "--install") == 0) {
                        *f_install = 1;
                } else {
                        fprintf(stderr, "Unknown option: %s\n", argv[i]);
                }

                i++;

        }

        if ((*f_full + *f_config + *f_install) > 1)  {
                fprintf(stderr, 
                        "Error: Only one flag can be set. " 
                        "Refer to %s --help for more specifications.\n",
                        argv[0]);
                exit(-1);
        }

}

/* ------------------------------------------------------------------------- */
/* Main                                                                      */
/* ------------------------------------------------------------------------- */

int main(int argc, char* argv[]) {
        
        int f_full;
        int f_config;
        int f_install;

        vs_parseopts(argc, argv, &f_full, &f_config, &f_install); 

        if (f_full) {
                vs_install();
                vs_configure();
        } else if (f_config) {
                vs_configure();
        } else if (f_install) {
                vs_install();
        }

        return 0;

}    

/* ------------------------------------------------------------------------- */
/* End                                                                       */
/* ------------------------------------------------------------------------- */
