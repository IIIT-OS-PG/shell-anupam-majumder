#include "Functionalities.h"

using namespace std;
int read_input(char *argv[])
{
    string input="";
    int status=0;
    while(1)
    {
        char c;
        c=getchar();
        if(c=='\n')
        break;
        if(c=='|')
        status=1;
        if(c=='>')
        status+=2;
        input+=c;
        // getline(cin,input);
    }
    stringstream stream(input);
    int count=0;
    string word;
    
    // int i=0;
    while(stream>>word)
    {
       //const char cstr[word.size() + 1];
        // cout<<count<<" "<<word<<endl;
        // if((word.compare(">"))==0)
        // status+=2;
        // else if((word.compare(">>"))==0)
        // status+=4;
        
        argv[count]=(char *)malloc((word.length()+1)*sizeof(char));
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
    argv[count]=(char *)0;

    return status;
    
}

void conv_string_cmd_char(string input,char *argv[])
{
    stringstream stream(input);
    int count=0;
    string word;
    
    // int i=0;
    while(stream>>word)
    {
      
        argv[count]=(char *)malloc((word.length()+1)*sizeof(char));
        strcpy(argv[count],word.c_str());
        count++;
            
    }
    argv[count]=(char *)0;

}