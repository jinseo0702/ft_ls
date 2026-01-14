#ifndef DIRSTREAM_H
#define DIRSTREAM_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "./utils.h"

typedef struct s_list_ls t_list_ls;

typedef struct s_max_len {
	unsigned int hard_max;
	unsigned int own_max;
	unsigned int grp_max;
	unsigned int size_max;
	unsigned int date_max;
} t_max_len;

DIR *openDirectoryStream(const char *path);
void readDirectoryStream(t_list_ls *readdirPtr, DIR *openDir);
int closeDirectoryStream(DIR *dirp);

//longFormat.c
void make_long_format(t_list_ls **head, blkcnt_t *total);
void check_long_form_str_size(t_list_ls **head, t_max_len max);
void make_sate_data_to_string(t_list_ls **head);
char *decoding_authority(mode_t st_mode);
char *decoding_hardlink(nlink_t st_nlink);
char *decoding_userID(uid_t st_uid);
char *decoding_group(gid_t st_gid);
char *decoding_size(off_t st_size);
char *decoding_time(struct timespec *st_mtim);
char *decoding_name(const char *path, const char *name);

#endif