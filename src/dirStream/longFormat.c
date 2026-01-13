#include "../../include/dirStream.h"
#include "../../include/ls_list.h"
#include <sys/stat.h>

void make_long_format(t_list_ls **head) {
    t_list_ls *temp = *head;
	struct stat statbuf;
	char arr[10000];
	char *slash_ptr = NULL;
    while (temp) {
		ft_memset(arr, 0, sizeof(arr));
		ft_memset(&statbuf, 0, sizeof(statbuf));
		ft_strlcpy(arr, temp->path, sizeof(arr));
		slash_ptr = ft_strrchr(arr, '/');
		*slash_ptr = '\0';
		if (stat(arr, &statbuf) == -1){
			print_error(ERR_STATE);
			exit_process(1);
		}
		temp->st_mode = statbuf.st_mode;
		temp->st_nlink = statbuf.st_nlink;
		temp->st_uid = statbuf.st_uid;
		temp->st_gid = statbuf.st_gid;
		temp->st_blocks = statbuf.st_blocks;
		temp->st_mtim = statbuf.st_mtim;
        temp = temp->next;
    }
	print_s_list_ls(*head); //
}