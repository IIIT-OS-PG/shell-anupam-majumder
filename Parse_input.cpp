#include "Functionalities.h"

using namespace std;

vector<string> prev_cmd;
void init_history()
{
    //Init_bash_history
}



int read_input(char *argv[])
{
    string input="";int prev_ind=prev_cmd.size()-1;
    int status=0;
    while(1)
    {
        char c;
        
        
        c=getchar();
        // cout<<(int)c;
        if(c=='\n')
        {
            cout<<c;
            break;
        }
        else if((int)c==9)
        {
            //trie();
            continue;
        }
        else if((int)c==127)
        {
            if(input.length()!=0)
            {
                cout<<"\b \b";
                input.pop_back();
            }
        }
        else if((int)c==27)
        {
            getchar();
            int input_len;
            switch(getchar())
            {
                case 'A':
                //history
                input_len=input.length();
                
                if(prev_ind>=0)    
                {
                    while(input_len--)
                    {
                        if(input_len==0)
                        {
                            cout<<"\b";
                            continue;
                        }
                        cout<<"\b \b";
                    }
                    input=prev_cmd[prev_ind];
                    prev_ind--;
                    if(prev_ind==-1)
                    prev_ind=0;
                    cout<<input;
                }
                break;
                case 'B':
                //history
                input_len=input.length();
                
                if((prev_ind+1)<prev_cmd.size())    
                {
                    
                    while(input_len--)
                    {
                        if(input_len==0)
                        {
                            cout<<"\b";
                            continue;
                        }
                        cout<<"\b \b";
                    }
                    
                    prev_ind++;
                    input=prev_cmd[prev_ind];
                    
                    if(prev_ind==prev_cmd.size())
                    {
                        prev_ind=prev_cmd.size()-1;
                    }
                    cout<<input;
                }
                break;
                
                case 'D':
                
                break;
                //cout<<"\033[D";
                
            }
        }
        else if(iscntrl(c))
        {
            
            
            cout<<(int)c<<endl;
            input="";
            break;
        }
        else if(isprint(c))
        {
            if(c=='>')
            {
                if(input.length()>0 && input[input.length()-1]=='>')
                {
                    status=4;
                }
                else
                status=2;
            }
            if((int)c!=27)
            {
                cout<<c;
                input+=c;
            }
        }
        
        // getline(cin,input);
    }
    // cout<<input<<endl;
    if(input.compare(""))
    {
        
        prev_cmd.push_back(input);
    }
    else
    {
        status=-1;
        return status;
    }
    // cmd_count++;


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