#ifndef NS_INSTALL_H
#define NS_INSTALL_H

static const char* const clone_directory = "https://github.com/vim/vim.git";
static const char* const configure_flags = 
  "--disable-gui --without-x"
;

void install(void);

#endif
