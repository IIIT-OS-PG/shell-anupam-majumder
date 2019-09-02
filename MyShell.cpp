#include "Functionalities.h"

using namespace std;

int main()
{
    // int k=2;
    while(1)
    {
        cout<<"$ ";
        char *argv[2048];
        read_input(argv);
        if(strcmp(argv[0],"exit")==0)
        exit(0);
        // fflush(stdin);
        int pid=fork();
        
        
        //cout<<pid<<endl;
        
        // cout<<k<<endl;
        if(pid==0)
        {
            
            
            
            execvp(argv[0],(char * const*)argv);
            
            
            
            exit(0);
            
        }
        else
        {
            wait(NULL);
        }
        // cout<<endl;
    }

}