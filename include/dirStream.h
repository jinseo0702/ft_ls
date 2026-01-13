#ifndef DIRSTREAM_H
#define DIRSTREAM_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include "./utils.h"

typedef struct s_list_ls t_list_ls;

DIR *openDirectoryStream(const char *path);
void readDirectoryStream(t_list_ls *readdirPtr, DIR *openDir);
int closeDirectoryStream(DIR *dirp);

//longFormat.c
void make_long_format(t_list_ls **head);

#endif