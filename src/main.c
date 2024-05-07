#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include <install.h>
#include <configure.h>

int main(int argc, char * argv[]) {

  int flag_ninstall = 0;
  int flag_nconfigure = 0;

  struct option long_options[] = {
    {"no-install", no_argument, &flag_ninstall, 1},
    {"no-configure", no_argument, &flag_nconfigure, 1},
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
  
  if (!flag_ninstall) {
    printf("running installation\n");
    install();
  }

  if (!flag_nconfigure) {
    printf("running configuration\n");
    configure();
  }

  return 0;

}
