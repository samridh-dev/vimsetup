#include "mm.h"
int main(int argc, char* argv[]) {
  mm_rebuild(argc, argv);

  struct build vimsetup;

  mm_build_init(&vimsetup);
  mm_build_set_binary(&vimsetup, "vimsetup");

  mm_build_add_src(&vimsetup, "src/configure.c");
  mm_build_add_src(&vimsetup, "src/install.c");
  mm_build_add_src(&vimsetup, "src/main.c");

  mm_build_add_arg(&vimsetup, "-Iinc/");

  mm_build_compile(&vimsetup);

  return 0;

}

