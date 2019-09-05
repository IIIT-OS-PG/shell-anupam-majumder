#include "Functionalities.h"
using namespace std;

// bool check_shell_builtin(string cmd)
// {
//     int fd[2];
//     //execl("/bin/bash","-c","type", cmd.c_str(), (const char *)NULL);
//     char *args[]={"sh","-c","type","cd",NULL};
//     // cout<<args[0]<<args[1]<<args[2]<<args[3]<<endl;
   
//     cerr<<execvp(args[0],args);
//     //cerr<<c;
//     return true;
// }

void run_pipe_cmds(char *argv[])
{
    string s=argv[0];
    // int count=1;
    for(int i=1;argv[i]!=NULL;i++)
    {
        s=s+" "+argv[i];
    }
    // cout<<s<<endl;
    
    char cstr[s.size() + 1];
	strcpy(cstr, s.c_str());

    char *cmd=strtok(cstr,"|");
    int count=0;
    vector<string> a;

    while(cmd!=NULL)
    {
        string x(cmd);
        a.push_back(x);


        // cout<<x<<endl;
     
        cmd = strtok(NULL, "|"); 
    }


    //
    // int f=open("123.txt",O_CREAT|O_APPEND,0644);
    for(int i=0;i<a.size()-1;i++)
    {
        char *args[1024];
        // cout<<a[i]<<endl;
        conv_string_cmd_char(a[i],args);

        int fd[2];
        pipe(fd);
        
        
        int pid=fork();
        
        // // cout<<args[0]<<endl<<endl;
        if(pid==0)
        {
            // char buf[5];
            

            dup2(fd[1],1);
            close(fd[0]);
            
            execvp(args[0],args);
            
            exit(0);
        }
        
        wait(NULL);
        
        dup2(fd[0],0);
        close(fd[1]);
        // cout<<args[0]<<" "<<args[1]<<endl;
        // cout<<args[0]<<endl;
    }
    // cout<<a[a.size()-1]<<endl;
    char *args[1024];
    conv_string_cmd_char(a[a.size()-1],args);
    // cout<<args[0]<<" "<<args[1]<<endl;
    execvp(args[0],args);

}
string file_redirection(char *argv[])
{
    string s=argv[0];
    // int count=1;
    int i;
    for(i=1;argv[i]!=NULL;i++)
    {
        s=s+" "+argv[i];
    }
    string input="";
    for(i=0;i<s.length();i++)
    {
        if(s[i]=='>')
        break;
        input+=s[i];
    }
    
    conv_string_cmd_char(input,argv);
    // cout<<input<<endl;
    
    if(s[i+1]=='>')
    i++;

    while(s[++i]==' ');
    
    
    s=s.substr(i,s.length()-i);
    // s.trim();
    // cout<<s<<endl;
    return s;
    //???Left
}


void call_cd(char *argv[])
{
    if (chdir(argv[1]) != 0)  
    {
        cout<<"No such directory is present\n";
    }
    else
    {
        // char s[100];
        //<<endl;
        // cout<<argv[1]<<endl;
        chdir(argv[1]);
        // setenv("PWD",getcwd(s,100),1);
        
    }
  
}