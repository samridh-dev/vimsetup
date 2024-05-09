#include <install.h>

#include <stdlib.h>
#include <stdio.h>
void install(void) {
  char cmd[65535];

  // Remove existing Vim directory
  snprintf(cmd, sizeof(cmd), "sudo rm -rf vim/");
  system(cmd);

#if 1
  // Clone Vim repository and configure
  snprintf(cmd, sizeof(cmd), 
    "sudo git clone %s --depth 1 && cd vim/src && sudo ./configure %s", 
    clone_directory, 
    configure_flags);
  if (system(cmd) != 0) {
     printf("\033[0;31mError:\033[0m ./configure failed\n");
     return;
  }
#endif

  // Make and install Vim
  snprintf(cmd, sizeof(cmd), 
    "cd vim/src && sudo make -j$(nproc) && sudo make install"
  );
  if (system(cmd) != 0) {
    printf("\033[0;31mError:\033[0m Make or make install failed\n");
    return;
  }

  // Clean up
  snprintf(cmd, sizeof(cmd), "sudo rm -rf vim/");
  system(cmd);

  printf("\033[0;32mVim installed successfully!\033[0m\n");

}

