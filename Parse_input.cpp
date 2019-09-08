#include "Functionalities.h"

using namespace std;

deque<string> prev_cmd;
unordered_map<string,string> aliases;



void init_history()
{
    //Init_bash_history
    string line;
    ifstream myfile (".my_history");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            prev_cmd.push_back(line);
        }
        myfile.close();
    }

}


void write_history()
{
    ofstream myfile (".my_history");
    if (myfile.is_open())
    {
        while(!prev_cmd.empty())
        {
            string s=prev_cmd.front()+"\n";
            prev_cmd.pop_front();
            myfile << s;
        }
        // myfile << "This is a line.\n";
        // myfile << "This is another line.\n";
        myfile.close();
    }
    
}

int is_file(const char* path) 
{
    struct stat buf;
    stat(path, &buf);
    if(S_ISREG(buf.st_mode))
	return 1;

	return 0;
}
void trie()
{
    struct dirent *de; 
     
    DIR *dr = opendir("/bin"); 
  
    if (dr == NULL)   
    { 
        printf("Could not open current directory" ); 
        return ; 
    } 
  
    
    while ((de = readdir(dr)) != NULL) 
        {    
            cout<<de->d_name<<endl;
            if(is_file(de->d_name))
            {
                cout<<de->d_name;
            }
        } 
    
    closedir(dr);     
}

void read_history()
{
    for(int i=0;i<prev_cmd.size();i++)
    {
        cout<<i+1<<"\t"<<prev_cmd[i]<<endl;
    }
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
        // else if(iscntrl(c))
        // {
            
            
        //     cout<<(int)c<<endl;
        //     input="";
        //     break;
        // }
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
        string x=get_env("$HISTSIZE");
        stringstream k(x);
        int hist;
        k>>hist;
        if(prev_cmd.size()>hist)
        {
            prev_cmd.pop_front();
        }
    }
    else
    {
        status=-1;
        return status;
    }
    // cmd_count++;
    
    stringstream alias_input(input);
    string wor_1;
    alias_input>>wor_1;
    if(wor_1.compare("alias")==0)
    {
        // int flag=0;
        // while(alias_input>>wor_1)
        // {
        //     string s="";
        //     for(int i=0;i<wor_1.length();i++)
        //     {
        //         if(wor_1[i]!='=')
        //         {
        //             s=s+wor_1[i];
        //         }
        //         if(wor_1.compare("\'"))
        //         {
        //             flag=1;
        //         }
        //     }
        // }
        string cmd="";
        string alias_name="";
        int flag=0;
        for(int i=5;i<input.length();i++)
        {
            if(input[i]==' '&&flag!=2)
            continue;
            else if(input[i]=='\''||input[i]=='=')
            {
                // cout<<input[i]<<endl;
                flag++;
            }
            else if(flag==0)
            {
                alias_name+=input[i];
            }
            
            else if(flag==2)
            {
                cmd+=input[i];
            }
        }
        cout<<alias_name<<" = "<<cmd<<endl;
        aliases[alias_name]=cmd;
        status=-1;
        return status;
    }
    
    
    // if(aliases.find(input)!=aliases.end())
    // {
    //     input=aliases[input];
    // }
    
    
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
        if(word[0]=='$')
        {
            word=get_env(word);
        }
        if((word[0]=='~'&&word[1]=='/')||(word[0]=='~'&&word.length()==1))
        {
            string home_path=get_env("$HOME");
            word.erase (word.begin());
            word=home_path+word;
        }
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


bool if_alias(string s)
{
    return aliases.find(s)!=aliases.end();
}
string set_alias(string s)
{
    return aliases[s];
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