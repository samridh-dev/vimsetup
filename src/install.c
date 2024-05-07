#include <install.h>

#include <stdlib.h>
#include <stdio.h>
void install(void) {

  char cmd[65535];

  snprintf(cmd, sizeof(cmd), 
  "sudo rm -rf vim/"
  );
  system(cmd);

  snprintf(cmd, sizeof(cmd), 
  "sudo git clone %s && cd vim/src;"
  "./configure %s;"
  "make -j$(nproc); sudo make install"
  ,
  clone_directory,
  configure_flags
  );
  system(cmd);

  snprintf(cmd, sizeof(cmd), 
  "sudo rm -rf vim/"
  );
  system(cmd);

}
