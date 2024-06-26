#include "mm.h"
#include <stdio.h> 
int main(int argc, char* argv[]) {

        mm_rebuild(argc, argv);

        struct build vimsetup;

        mm_build_init(&vimsetup);
        mm_build_set_binary(&vimsetup, "vimsetup");

        mm_build_add_src(&vimsetup, "src/cp.c");
        mm_build_add_src(&vimsetup, "src/rm.c");
        mm_build_add_src(&vimsetup, "src/mkdir.c");

        mm_build_add_src(&vimsetup, "src/vs.c");

        mm_build_add_src(&vimsetup, "src/main.c");

        mm_build_add_arg(&vimsetup, "-Iinc/");

        mm_build_add_arg(&vimsetup, "-std=c89");
        mm_build_add_arg(&vimsetup, "-Wall");
        mm_build_add_arg(&vimsetup, "-Werror");
        mm_build_add_arg(&vimsetup, "-Wpedantic");
        mm_build_add_arg(&vimsetup, "-Wextra");
        mm_build_add_arg(&vimsetup, "-Wconversion");
        mm_build_add_arg(&vimsetup, "-Wshadow");
        mm_build_add_arg(&vimsetup, "-Wpointer-arith");
        mm_build_add_arg(&vimsetup, "-Wcast-qual");
        mm_build_add_arg(&vimsetup, "-Wstrict-prototypes");
        mm_build_add_arg(&vimsetup, "-Wmissing-prototypes");
        mm_build_add_arg(&vimsetup, "-Wredundant-decls");
        mm_build_add_arg(&vimsetup, "-Wnested-externs");
        mm_build_add_arg(&vimsetup, "-Wold-style-definition");
        mm_build_add_arg(&vimsetup, "-Wmissing-declarations");
        mm_build_add_arg(&vimsetup, "-Wformat=2");
  
        mm_build_compile(&vimsetup);

        return 0;

}
