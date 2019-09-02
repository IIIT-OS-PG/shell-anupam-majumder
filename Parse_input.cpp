#include "Functionalities.h"

using namespace std;
void read_input(char *argv[])
{
    string input;
    getline(cin,input);
    stringstream stream(input);
    int count=0;
    string word;
            
    // int i=0;
    while(stream>>word)
    {
       //const char cstr[word.size() + 1];
        // cout<<count<<" "<<word<<endl;
        argv[count]=(char *)malloc((word.length()+1)*sizeof(char *));
        strcpy(argv[count],word.c_str());
        count++;
                // cout<<count<<endl;
                // cout<<argv[i-1]<<endl;
            //     //cerr<<word<<endl;
            //     if(i==0)
            //     args[i++]="\bin\\"+word;
            //     else
            //     args[i++]=word;
            //     //cerr<<"Here"<<endl;
    }
    argv[count+1]=(char *)0;
    
}