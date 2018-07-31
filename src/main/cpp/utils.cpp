
#include "pch.h"


#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

string getHomeDir()
{
    char* val;
    
    val = getenv("HOME");


    if(val == NULL) {
        struct passwd* pw = getpwuid(getuid());
        val = pw->pw_dir;
    }

    return val;
}