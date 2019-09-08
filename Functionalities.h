#include<bits/stdc++.h>
#include<unistd.h>
#include<termios.h>
#include<dirent.h>

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
#include <fstream>
using namespace std;


string get_env(string x);


void init_shell();
void disableRawMode();
// void init_history();

void init_history();
void write_history();
int is_file(const char* path);
void trie();
bool if_alias(string x);
string set_alias(string x);
void read_history();

// void handle_sigint(int sig);
int read_input(char *argv[]);
void conv_string_cmd_char(string input,char *argv[]);

void run_pipe_cmds(char *argv[]);
string file_redirection(char *argv[]);
void call_cd(char *argv[]);
string trim(const string& str);

// bool check_shell_builtin(string cmd);


// public: 
class Env_var
{
    public:
    unordered_map<string,string> env_list;
    
    Env_var()
    {
        //.myrc initialization
        string line;
        ifstream myfile (".myrc");
        if (myfile.is_open())
        {
            while ( getline (myfile,line) )
            {
                stringstream ss(line);
                string word;
                int flag=0;
                while(ss>>word)
                {
                    
                    word="$"+word;
                    string val;
                    ss>>val;
                    ss>>val;
                    env_list[word]=val;
                    // cout<<word<<" "<<val<<endl;
                    
                }
                // prev_cmd.push_back(line);
            }
        myfile.close();
        }
        /*
        string env_var[5] = {"PATH","HOME","PS1","HOSTNAME","USER"};
        FILE *fp=fopen(".myrc","w");
        if(fp!=NULL)
        {
            for(int i=0; i<5; i++)
	        {
                
                string s="$"+env_var[i];
                string val="";
                if(getenv(env_var[i].c_str())!=NULL)
                val=getenv(env_var[i].c_str());

                s=env_var[i]+" = "+val+"\n";
                fputs (s.c_str(),fp);
    
                // cout<<s<<" "<<val<<endl;
                env_list[s] = val;
            }
            fclose (fp);
        }*/
    }
};
