#include<bits/stdc++.h>
#include<unistd.h>


#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <fcntl.h>
using namespace std;

int read_input(char *argv[]);
void conv_string_cmd_char(string input,char *argv[]);

void run_pipe_cmds(char *argv[]);
// bool check_shell_builtin(string cmd);