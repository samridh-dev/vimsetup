#include <configure.h>

#include <stdlib.h>
#include <stdio.h>
void configure(void) {

  printf("Configuring vim.\n");

  char cmd[65535];
  
  snprintf(cmd, sizeof(cmd), 
  "mkdir -p ~/.vim/ && rm -rf ~/.vim/* && cp -r dat/vim/* ~/.vim/"
  );
  system(cmd);

  return;
}

