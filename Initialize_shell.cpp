#include "Functionalities.h"

struct termios orig_termios;
void disableRawMode() 
{
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void init_shell()
{
    
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw=orig_termios;
    
    raw.c_lflag &= ~(ECHO | ICANON);
    
    
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}