#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

const char* PROMPT = "mybash> ";

int isWhitespace(const char c) {
  return c == ' ' || c == '\t' || c == '\n';
}

void readCommand(char* args[50], int* argsCount, int* backgroundMode) {
    printf("%s", PROMPT);
    fflush(stdout);

    *argsCount = 0;
    *backgroundMode = 0;

    char cmd[4096];
    int bytesRead = read(0, cmd, 4096);

    int i;
    for (i = 0; i < bytesRead; i++) {
       if (!isWhitespace(cmd[i])) {
         if (i == 0 || isWhitespace(cmd[i - 1])) {
           args[(*argsCount)++] = cmd + i;
         }
       }

       if (i > 0 && isWhitespace(cmd[i - 1])) {
         cmd[i - 1] = '\0';
       }
    }

    cmd[bytesRead - 1] = '\0';
    args[*argsCount] = NULL;

    if (!strcmp(args[(*argsCount) - 1], "&")) {
      *backgroundMode = 1;
      (*argsCount)--;
      args[*argsCount] = NULL;
    }
}

int executeCommand(char* args[50], int argsCount, int backgroundMode) {
  int pid = fork();

  if (pid == -1) {
    printf("Could not fork\n");
    return -1;
  }

  if (!pid) {
    // child
    int result = execvp(args[0], args);
    printf("Command %s not found\n", args[0]);
    exit(result);
  }

  else {
    // parent
    if (!backgroundMode) {
      int status;
      wait(&status);
      // if (status == 0) {
      //   printf("Command %s finished with status %d\n", args[0], status);
      // }
      return status;
    }
  }
}

int main() {
  while (1) {
    char* args[50];
    int argsCount, backgroundMode;

    readCommand(args, &argsCount, &backgroundMode);

    if (argsCount == 1 && !strcmp(args[0], "bye")) {
      printf("bye\n");
      return 0;
    }

    if (argsCount > 0) {
      executeCommand(args, argsCount, backgroundMode);
    }
  }
}
