#ifndef MM_H
#define MM_H
///////////////////////////////////////////////////////////////////////////////
/// User Configuration                                                      ///
///////////////////////////////////////////////////////////////////////////////

#define SET_LOG 0

/* ------------------------------------------------------------------------- */
/* Memory Configuration                                                      */
/* ------------------------------------------------------------------------- */

// MAXSIZE is the maximum number of arguments/source files that can be 
// registered in the build command.
// SRC is memory to store source file names
// ARG is memory to store arguments
// CMD is memory to store main command arguments

#define MM_SRC_MAXSIZE 8
#define MM_ARG_MAXSIZE 16

#define MM_CMD_MAXSIZE \
((MM_SRC_MAXSIZE + MM_ARG_MAXSIZE) + 16)

///////////////////////////////////////////////////////////////////////////////
/// Declarations                                                            ///
///////////////////////////////////////////////////////////////////////////////

/* ------------------------------------------------------------------------- */
/* User Header Declarations                                                  */
/* ------------------------------------------------------------------------- */

void mm_rebuild(int argc, char* argv[]);

struct build;
void mm_build_init(struct build* const b);
void mm_build_add_arg(struct build* const b, char* const arg);
void mm_build_add_src(struct build* const b, char* const src);
void mm_build_set_compiler(struct build* const b, char* const compiler);
void mm_build_set_binary(struct build* const b, char* const binary);
void mm_build_compile(struct build* b);

/* ------------------------------------------------------------------------- */
/* System Specific Includes                                                  */
/* ------------------------------------------------------------------------- */

#ifdef _WIN32
#else
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#endif

/* ------------------------------------------------------------------------- */
/* Internal Declarations                                                     */
/* ------------------------------------------------------------------------- */

unsigned long int mm_strlen(const char* const str);
signed char mm_cmcmp(const char* const c_fname, const char* const m_fname);

///////////////////////////////////////////////////////////////////////////////
/// Utility Functions                                                       ///
///////////////////////////////////////////////////////////////////////////////

/* ------------------------------------------------------------------------- */
/* Miscellaneous                                                             */
/* ------------------------------------------------------------------------- */

#define SIZEOF_ARR(x) (sizeof((x)) / sizeof(*(x)))

/* ------------------------------------------------------------------------- */
/* Input/Output                                                              */
/* ------------------------------------------------------------------------- */

#define L_DEBUG     "[DEBUG]"
#define L_ERROR     "[ERROR]"
#define L_WARNING   "[WARNING]"
#define L_INFO      "[INFO]"

void mm_log(const char* const tag, const char* const restrict msg) {
#ifdef _WIN32
#else
  write(STDOUT_FILENO, tag, mm_strlen(tag));
  write(STDOUT_FILENO, ": ", 2);
  write(STDOUT_FILENO, msg, mm_strlen(msg));
  write(STDOUT_FILENO, "\n", 1);
#endif
}

void mm_cmd_print(char* cmd[], const int size) {
#ifdef _WIN32
#else
  for (int i = 0; i < size; i++) {
    write(STDOUT_FILENO, cmd[i], mm_strlen(cmd[i]));
    write(STDOUT_FILENO, " ", 1);
  }
  write(STDOUT_FILENO, "\n", 1);
#endif
}

#if SET_LOG
#define MM_LOG(L_TAG, MSG) do { mm_log(L_TAG, MSG); } while(0);
#else
#define MM_LOG(L_TAG, MSG)
#endif

/* ------------------------------------------------------------------------- */
/* Program Exit Functionality                                                */
/* ------------------------------------------------------------------------- */

#ifdef _WIN32
#define MM_EXIT(x)
#else
#define MM_EXIT(x) _exit(x)
#endif

///////////////////////////////////////////////////////////////////////////////
/// Implementations                                                         ///
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// STRUCT BUILD                                                            ///
///////////////////////////////////////////////////////////////////////////////

/* ------------------------------------------------------------------------- */
/* Struct Build Declaration                                                  */
/* ------------------------------------------------------------------------- */

struct build { 

  char* bin; 
  char* cmd;
  
  unsigned long int srcc;
  char* srcv[MM_SRC_MAXSIZE];

  unsigned long int argc;
  char* argv[MM_ARG_MAXSIZE];

};

/* ------------------------------------------------------------------------- */
/* Struct Build Method Implementation                                        */
/* ------------------------------------------------------------------------- */

#ifdef _WIN32 
#define MM_DEFAULT_COMPILER "cl"
#else
#define MM_DEFAULT_COMPILER "cc"
#endif

#define MM_DEFAULT_BINARY "a.out"

void mm_build_init(struct build* const b) {

  (*b).bin = MM_DEFAULT_BINARY;
  (*b).cmd = MM_DEFAULT_COMPILER;
  
  (*b).srcc = 0;
  (*b).argc = 0;
  
  for (int i = 0; i < MM_SRC_MAXSIZE; i++) {
    (*b).srcv[i] = 0;
  }

  for (int i = 0; i < MM_ARG_MAXSIZE; i++) {
    (*b).argv[i] = 0;
  }

}


// Note: the string must not go out of scope before build end.
void mm_build_add_arg(struct build* const b, char* const arg) {

  if ((*b).argc >= SIZEOF_ARR((*b).argv)) {
    MM_LOG(L_ERROR, "argv array overflow detected.");
    MM_EXIT(1);
  }

  (*b).argv[(*b).argc++] = arg;
  MM_LOG(L_INFO, "Updated arg list");

}

// Note: the string must not go out of scope before build end.
void mm_build_add_src(struct build* const b, char* const src) {

  if ((*b).srcc >= SIZEOF_ARR((*b).srcv)) {
    MM_LOG(L_ERROR, "srcv array overflow detected.");
    MM_EXIT(1);
  }

  (*b).srcv[(*b).srcc++] = src;
  MM_LOG(L_INFO, "Updated src list");

}


void mm_build_set_compiler(struct build* const b, char* const compiler) {

  if (compiler != 0) {
    (*b).cmd = compiler; 
  }

}

void mm_build_set_binary(struct build* const b, char* const binary) {

  if (binary != 0) {
    (*b).bin = binary; 
  }

}

///////////////////////////////////////////////////////////////////////////////
/// MAIN COMPILE FUNCTION                                                   ///
///////////////////////////////////////////////////////////////////////////////

void mm_cmd_append(char** cmd, 
                   const int size,
                   const int cur,
                   char* const str) {

  if (cur > size) {
    MM_LOG(L_ERROR, "Command overflow detected.");
    MM_EXIT(1);
  }

  cmd[cur] = str;

}


// Creates entire command
// TODO : add functions to create different commands.
int mm_cmd_create(char** cmd, const int size, struct build* b) {

  int cur = 0;

  mm_cmd_append(cmd, size, cur++, (*b).cmd);
  mm_cmd_append(cmd, size, cur++, "-o");
  mm_cmd_append(cmd, size, cur++, (*b).bin);

  for (unsigned long int i = 0; i < (*b).srcc; i++) {
    cmd[cur++] = (*b).srcv[i];
  }

  for (unsigned long int i = 0; i < (*b).argc; i++) {
    cmd[cur++] = (*b).argv[i];
  }

  return cur;

}

void mm_build_compile(struct build* b) {
  
  char* cmd[MM_CMD_MAXSIZE] = {0};

  int cur = mm_cmd_create(cmd, SIZEOF_ARR(cmd), b);

  mm_cmd_print(cmd, cur);

#ifdef _WIN32
#else
  pid_t pid = fork(); 
  if (pid == -1) {
    MM_LOG(L_ERROR, "command fork failed.");  
    return;
  } 
  else if (pid == 0) {
    execvp(cmd[0], cmd);
  }
  else {
    int status;
    waitpid(-1, &status, 0);
  }
#endif

}

void mm_rebuild(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  if ((mm_cmcmp(argv[0], "mm.c") != 1) && 
      (mm_cmcmp(argv[0], "mm.h") != 1)) {  
    return;

  }

  MM_LOG(L_INFO, "Rebuilding build program.");

  struct build b;
  mm_build_init(&b);
  mm_build_set_compiler(&b, 0);
  mm_build_set_binary(&b, argv[0]);
  mm_build_add_src(&b, "mm.c");
  mm_build_compile(&b);

#ifdef _WIN32
#else
  pid_t pid = fork();
  if (pid == -1) {
    MM_LOG(L_ERROR, "self rebuild fork failed.");  
    return;
  } else if (pid == 0) {
    execlp(argv[0], argv[0], NULL);
  } else {
    int status;
    waitpid(-1, &status, 0);
    MM_LOG(L_INFO, "Exiting old program.");
    MM_EXIT(0);
  }
#endif

}

///////////////////////////////////////////////////////////////////////////////
/// Internal Implementations                                                ///
///////////////////////////////////////////////////////////////////////////////

/*****************************************************************************
 *                                                                           *
 * @desc:  This is an implementation of strlen() in <string.h>               *
 *                                                                           *
 * @params:                                                                  *
 *    const char* const str     :     null terminated string                 *
 *                                                                           *
 * @returns:                                                                 *
 *    unsigned long int         :     length of null terminated string       *
 *                                                                           *
 *****************************************************************************/
unsigned long int mm_strlen(const char* const str) { 
  unsigned long int i = 0;
  while (str[i] != '\0') i++;
  return i;
}

/*****************************************************************************
 *                                                                           *
 * @desc:  Compares the creation time of the file named by c_fname with the  *
 *         modification time of the file named by m_fname.                   *
 *                                                                           *
 * @params:                                                                  *
 *    const char* const c_fname : Path to the file whose creation time is to *
 *                                be compared.                               *
 *    const char* const m_fname : Path to the file whose modification time   *
 *                                is to be compared.                         *
 *                                                                           *
 * @returns:                                                                 *
 *    signed char              : -1 if creation time of c_fname is greater   *
 *                                than modification time of m_fname,         *
 *                                                                           *
 *                                0 if creation time of c_fname is equal to  *
 *                                modification time of m_fname,              *
 *                                                                           *
 *                                1 if creation time of c_fname is less than *
 *                                modification time of m_fname.              *
 *                                                                           *
 *****************************************************************************/
signed char mm_cmcmp(const char* const c_fname, 
                     const char* const m_fname) {

#ifdef _WIN32
#else
  struct stat attr;
  (void)stat(m_fname, &attr);
  const int m_time = attr.st_mtime;
  (void)stat(c_fname, &attr);
  const int c_time = attr.st_ctime;
#endif

  if (c_time > m_time) return -1;
  if (c_time < m_time) return  1;
  return 0;

}

///////////////////////////////////////////////////////////////////////////////
/// End                                                                     ///
///////////////////////////////////////////////////////////////////////////////
#endif
