#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unctrl.h>
#include <stdlib.h>

void loop(struct dirent *dirStruct, DIR *dir) {
    if ((dirStruct = readdir(dir)) == NULL)
        return ;
    else {
        if (dirStruct->d_name[0] != '.')
            printf("%s ", dirStruct->d_name);
        loop(dirStruct, dir);
    }
}

int main (int argc, char *argv[]) {

    DIR *dir = opendir(argv[1]);
    struct dirent *dirStruct;
    loop(dirStruct, dir);
    closedir(dir);
    printf("\n");
    return (0);
}


