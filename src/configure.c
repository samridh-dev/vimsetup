#include <configure.h>

#include <stdlib.h>
#include <stdio.h>
void configure(void) {

  char cmd[65535];
  
  // install autocomplete
  snprintf(cmd, sizeof(cmd), 
  "rm -rf config/pack/plugins/start/supertab;"
  "git clone --depth=1 "
  "https://github.com/ervandew/supertab.git "
  "config/pack/plugins/start/supertab"
  );
  system(cmd);
  
  system(cmd);
  snprintf(cmd, sizeof(cmd), 
  "rm -rf ~/.vim/* && cp -r config/* ~/.vim/"
  );
  system(cmd);

  return;
}

