#include <stdlib.h>
int main() 
{
#if defined(_WIN32)
    return system("shutdown /s /t 0");
#else 
    return system("sudo shutdown -h now");
    
#endif
}