#ifndef VS_EXEC_H
#define VS_EXEC_H

#if _WIN32
bool vs_exec(char* const* argv) {
  
        return true;
}
#else
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
bool vs_exec(char* const*  argv) {

        int status;
        pid_t pid = fork();
        if (pid == -1) {

                perror("fork failed");
                return false;

        } else if (pid == 0) {

                execvp(argv[0], argv);
                perror("execvp");
                _exit(EXIT_FAILURE);

        } else {

                if (waitpid(pid, &status, 0) == -1) {

                        perror("waitpid");
                        return false;
                }

        }

        if (!WIFEXITED(status) || !(WEXITSTATUS(status) == 0)) {
                return false;
        }

        return true;

}
#endif

#endif
