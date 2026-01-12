#ifndef DIRSTREAM_H
#define DIRSTREAM_H

#include <sys/types.h>
#include <dirent.h>
#include "./utils.h"

typedef struct s_list_ls t_list_ls;

DIR *openDirectoryStream(const char *path);
void readDirectoryStream(t_list_ls *readdirPtr, DIR *openDir);
int closeDirectoryStream(DIR *dirp);

#endif