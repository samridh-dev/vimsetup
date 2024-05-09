#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include <install.h>
#include <configure.h>

int main(int argc, char * argv[]) {

  int flag_install = 0;
  int flag_config = 0;
  int flag_full = 0;

  struct option long_options[] = {
    {"full",     no_argument,  &flag_full,     1},
    {"install",  no_argument,  &flag_install,  1},
    {"config",   no_argument,  &flag_config,   1},
    {0,          0,            0,              0}  // End of options marker
  };
  int opt;
  while ((opt = getopt_long(argc, argv, "", 
                long_options, NULL)) != -1) {
    
    switch (opt) {
      case '?':
        printf("Unknown option provided: '%s'\n", optarg);
        break;
      default: 
        break;
    }

  }

  if (flag_install) {
    install();
  }

  if (flag_config) {
    configure();
  }
  
  if (flag_full) {
    install();
    configure();
  }

  return 0;
}
