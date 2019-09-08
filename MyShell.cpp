#include "Functionalities.h"

using namespace std;

Env_var *map_var=new Env_var();


string get_env(string x)
{
    x=trim(x);
    if(map_var->env_list.find(x)!=map_var->env_list.end())
    {
        return map_var->env_list[x];
    }
    return "";
}

int main()
{
    
    // int k=2;
    // // Uncomment from here
    init_shell();
    // cerr<<"Hi";
    init_history();
    // cerr<<"Hi";
    // trie();
    
    while(1)
    {
        cout<<map_var->env_list["$USER"]<<"@"<<map_var->env_list["$HOSTNAME"]<<map_var->env_list["$PS1"]<<" ";
        char *argv[2048];
        
        int status = read_input(argv);
        
        if(status==-1)
        continue;

        if(strcmp(argv[0],"exit")==0)
        {
            write_history();
            disableRawMode();
            exit(0);
        }
        
        if(strcmp(argv[0],"cd")==0)
        {
            // cout<<"hello"<<endl;
            call_cd(argv);
            continue;
        }
        if(strcmp(argv[0],"history")==0)
        {
            read_history();
            continue;
        }

        
        // if(argv[1]!=NULL)
        // {
        //     string env_if(argv[1]);
        //     if(map_var->env_list.find(env_if)!=NULL)
        //     {
        //         string env_if=get_env(env_if);
        //         // argv[1]=(char *)malloc(env_if.length()+1)*sizeof(char))
        //         strcpy(argv[1],env_if.c_str());
                
        //         // argv[1]=get_env(env_if).c_str();
        //     }
            
        // }
        // fflush(stdin);
        int pid=fork();
        
        
        //cout<<pid<<endl;
        
        // cout<<k<<endl;
        if(pid==0)
        {
            
            
            if(status==0)
            {
                // string cmd(argv[0]);
                // bool flag = check_shell_builtin(cmd);
                
                // if(flag)
                // {
                //     cout<<"shell built in\n";
                // }
                // else
                
               
                    run_pipe_cmds(argv);
                    // execvp(argv[0],(char * const*)argv);
                
            }
            
            else if(status==2)//Only >
            {
                // cout<<"Single Redirection\n";
                string file=file_redirection(argv);
                char file_copy[file.length()+1];

                strcpy(file_copy,file.c_str());

                int fd1=open(file_copy,O_CREAT|O_WRONLY|O_TRUNC,0644);
                
                dup2(fd1,1);
                run_pipe_cmds(argv);
                close(fd1);
                
            }
            
            else if(status==4)// Only >>
            {
                // cout<<"Double Redirection\n";
                string file=file_redirection(argv);
                char file_copy[file.length()+1];

                strcpy(file_copy,file.c_str());

                int fd1=open(file_copy,O_CREAT|O_WRONLY|O_APPEND,0644);

                
                dup2(fd1,1);
                run_pipe_cmds(argv);
                close(fd1);
                
                // cout<<file<<endl;
            }
            
            
            
            exit(0);
            
        }
        else
        {
            wait(NULL);
        }
        // cout<<endl;
    }
   
    disableRawMode();
}