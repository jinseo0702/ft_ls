#include "../../include/dirStream.h"
#include "../../include/ls_list.h"
#include <errno.h>
#include <unistd.h>

DIR *openDirectoryStream(const char *path) {
    DIR *openDirPtr = opendir(path);
    // if (openDirPtr == NULL) print_error(ERR_OPENDIR);
    if (openDirPtr == NULL) print_error_ls(ERR_OPENDIR, path);
    return (openDirPtr); 
}

void readDirectoryStream(t_list_ls *readdirPtr, DIR *openDir) {
    errno = 0;
    readdirPtr->ErrorNum = 0;
    dirent *temp = readdir(openDir);
    if (temp == NULL && errno != 0){
        readdirPtr->ErrorNum = errno;
        print_error(ERR_OPENDIR);
        return ;
    }
    if (temp != NULL) {
        readdirPtr->readDirPtr = *temp;
    }
    else {
        ft_memset(&readdirPtr->readDirPtr, 0, sizeof(dirent));
        readdirPtr->ErrorNum = -1;
    }
}

int closeDirectoryStream(DIR *dirp) {
    int flag = closedir(dirp);
    if (flag == -1) print_error(ERR_CLOSEDIR);
    return flag;
}