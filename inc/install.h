#ifndef NS_INSTALL_H
#define NS_INSTALL_H

static const char* const clone_directory = "https://github.com/vim/vim.git";
static const char* const configure_flags = 
  "--disable-gui --disable-X11"
  "--disable-xattr --disable-xfontset --disable-xim --disable-xsmp_interact"
  "--disable--arabic --disable--xpm --disable-vim9script"
;

void install(void);

#endif
