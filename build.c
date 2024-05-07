// includes
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

// macros
#define FILE_MAXSIZE 32
#define FILE_NAME_MAXSIZE 128
#define CMD_MAXSIZE 65535

#define SET_DEBUG 1

static const char* exec_name = "vimsetup-source";

// source files and directory
static const char* src_dir = "src/";
static const char* src_ext = ".c";

static char sfiles[(FILE_MAXSIZE + 1) * FILE_NAME_MAXSIZE + 1];
#define SFILES_SIZE ( (sizeof(sfiles) / sizeof(*sfiles)) - 1)

// compile variables
static const char* const cflags= "-Iinc/";
static const char* const cflags_deb = "-O0 -Werror -Wall -Wextra -pedantic";
static const char* const cflags_rel = "-O3";

// helper functions
int extcmp(const char* const str, 
           const char* const ext) {
  
  const int str_len = strlen(str);
  const int ext_len = strlen(ext);

  if (ext_len > str_len) return 0;
  return strcmp(str + strlen(str) - strlen(ext), ext) == 0;

}

// parse directory function
char* parse_dir(char* files, const int fsize, 
                const char* path, const char* ext) {

  int cur = 0;

  memset(files, ' ', fsize);
  files[fsize] = '\0';

  DIR* dr = opendir(path);
  if (dr == NULL) {
    printf("Could not open directory: %s\n", strerror(errno));
    return NULL;
  }

  struct dirent *de;
  while ((de = readdir(dr)) != NULL) {

    const char* const dname = (*de).d_name;
    const int dname_size = strlen(dname);

    const int has_extension = extcmp(dname, ext);
    if (!has_extension) continue;

    strncpy(&files[cur], path, strlen(path));
    cur += strlen(path);

    strncpy(&files[cur], dname, dname_size);
    cur += dname_size + 1;

  }
  files[cur] = '\0';

  return files;
}


static char cmd[CMD_MAXSIZE];

int compile_build(int argc, char* argv[]) {

  const char* const build_path = "./build.c"; // this makes build executable
                                              // to be run in the same
                                              // directory as the source.

  const char* const f_mtime = ".__build_mtime.dat";

  struct stat attr;
  if (stat(build_path, &attr) < 0) {
    perror("Failed to get build source file status");
    return 0;
  }

  time_t mtime = attr.st_mtime;
  time_t mtime_last = 0;

  FILE* fp = fopen(f_mtime, "r+");
  if (errno == ENOENT) {

    fp = fopen(f_mtime, "w+");

    fwrite(&mtime, sizeof(time_t), 1, fp);
    fseek(fp, 0L, SEEK_SET);

  }

  if (fp == NULL) {
    perror("Error opening file");
    return 0;
  }

  fread(&mtime_last, sizeof(time_t), 1, fp);
  fseek(fp, 0L, SEEK_SET);

  if (mtime != mtime_last) {

    snprintf(cmd, sizeof(cmd), 
            "cc -O3 build.c -o %s",
            argv[0]);
    system(cmd);

    fwrite(&mtime, sizeof(time_t), 1, fp);

    fclose(fp);
    return 1;
  }
  
  fclose(fp);
  return 0;
}

void compile_binary(int argc, char* argv[]) {

  (void)parse_dir(sfiles, SFILES_SIZE, src_dir, src_ext);

  const char* const cflags_extra = 
    #if SET_DEBUG
      cflags_deb;
    #else
      cflags_rel;
    #endif

  snprintf(cmd, sizeof(cmd), 
           "cc %s %s %s -o %s",
           cflags, cflags_extra, sfiles, exec_name);
  system(cmd);

}

int main(int argc, char* argv[]) {              
  
  const int compiled = compile_build(argc, argv);
  
  if (compiled) {
    pid_t pid = fork();

    if (pid == -1) {
      perror("fork failed");
      return 0;
    } else if (pid == 0) {
      execvp(argv[0], argv);
    } else {
      int status;
      waitpid(pid, &status, 0);
    }
    return 0;
  }

  compile_binary(argc, argv);

  return 0;
}
