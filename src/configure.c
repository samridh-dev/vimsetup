#include <configure.h>

#include <stdlib.h>
#include <stdio.h>
void configure(void) {

  char cmd[65535];

#if 0
  // install autocomplete
  snprintf(cmd, sizeof(cmd), 
  "rm -rf config/pack/plugins/start/supertab;"
  "git clone --depth=1 "
  "https://github.com/ervandew/supertab.git "
  "config/pack/plugins/start/supertab"
  );
  system(cmd);
#endif
  
  snprintf(cmd, sizeof(cmd), 
  "mkdir -p ~/.vim/ && rm -rf ~/.vim/* && cp -r config/* ~/.vim/"
  );
  system(cmd);

  return;
}

