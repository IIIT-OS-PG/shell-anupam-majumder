#include "Functionalities.h"

using namespace std;

int main()
{
    // int k=2;
    while(1)
    {
        cout<<"$ ";
        char *argv[2048];
        
        int status = read_input(argv);

        if(strcmp(argv[0],"exit")==0)
        exit(0);
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
                if(argv[0]=="cd")
                {
                    // call_cd(argv);
                }
                else
                execvp(argv[0],(char * const*)argv);
            }
            else if(status==1)//Only Pipe
            {
                // cout<<"PIPE\n";
                run_pipe_cmds(argv);
            }
            else if(status==2)//Only >
            {
                cout<<"Single Redirection\n";
            }
            else if(status==3)// > and pipe
            {
                cout<<"Pipe then Single Redirection\n";
            }
            else if(status==4)// Only >>
            {
                cout<<"Double Redirection\n";
            }
            else if(status==5)// >> and pipe
            {
                cout<<"Pipe then Double Redirection\n";
            }
            
            
            exit(0);
            
        }
        else
        {
            wait(NULL);
        }
        // cout<<endl;
    }

}