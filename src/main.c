#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include <install.h>
#include <configure.h>

int main(int argc, char * argv[]) {

  int flag_install_only = 0;
  int flag_config_only = 0;

  struct option long_options[] = {
    {"install-only", no_argument, &flag_config_only, 1},
    {"config-only", no_argument, &flag_config_only, 1},
    {0, 0, 0, 0}  // End of options marker
  };

  int opt;
  while ((opt = getopt_long(argc, argv, "", 
                long_options, NULL)) != -1) {
    
    switch (opt) {
      default: 
        break; 
    }

  }

  // Begin installation
  if (flag_install_only) {
    install();
    return 0;
  }

  if (flag_config_only) {
    configure();
    return 0;
  }

  install();
  configure();

  return 0;

}
