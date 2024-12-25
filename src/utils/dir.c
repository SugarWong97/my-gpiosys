#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int find_in_dir(char *dirpath, const char *keyword, char* got_filename)
{
#if 1
    int ret = 0;
    DIR *dir = opendir(dirpath);
    if(dir == NULL) {
        printf("open %s failed ",dirpath);
        perror(":");
        return 0;
    }

    struct dirent *ent;
    while((ent = readdir(dir)) != NULL)
    {
        if(strstr(ent->d_name, keyword) != 0)
        {
            //printf("file name: %s \n",ent->d_name);
            sprintf(got_filename,"%s", ent->d_name);
            ret = 1;
            break;
        }
    }
    closedir(dir);
    return ret;
#endif
    //sprintf(got_filename,"gpiochip906");
    return 1;
}
