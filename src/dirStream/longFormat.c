#include "../../include/dirStream.h"
#include "../../include/ls_list.h"
#include <errno.h>
#include <grp.h>
#include <linux/limits.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

/*
man 2 state
man 7 idnode
ls docs : https://www.gnu.org/software/coreutils/manual/coreutils.html#Which-files-are-listed-1
time format : https://www.gnu.org/software/coreutils/manual/coreutils.html#Formatting-file-timestamps-1
*/

void make_long_format(t_list_ls **head, blkcnt_t *total) {
    t_list_ls *temp = *head;
	struct stat statbuf;
	char arr[10000];
	char *slash_ptr = NULL;

    while (temp->name != NULL) {
		ft_memset(arr, 0, sizeof(arr));
		ft_memset(&statbuf, 0, sizeof(statbuf));
		ft_strlcpy(arr, temp->path, sizeof(arr));
		slash_ptr = ft_strrchr(arr, '/');
		*slash_ptr = '\0';
		if (lstat(arr, &statbuf) == -1){
			print_error(ERR_STATE);
			// exit_process(1);
		}
		temp->st_mode = statbuf.st_mode;
		temp->st_nlink = statbuf.st_nlink;
		temp->st_uid = statbuf.st_uid;
		temp->st_gid = statbuf.st_gid;
		temp->st_size = statbuf.st_size;
		temp->st_blocks = statbuf.st_blocks;
		temp->st_mtim = statbuf.st_mtim;
		*total += temp->st_blocks;
        temp = temp->next;
    }
	make_sate_data_to_string(head);
	t_max_len max;
	max.hard_max = max_len_str_in_longform(head, 0);
	max.own_max = max_len_str_in_longform(head, 1);
	max.grp_max = max_len_str_in_longform(head, 2);
	max.size_max = max_len_str_in_longform(head, 3);
	max.date_max = max_len_str_in_longform(head, 4);
	check_long_form_str_size(head, max);
}

void check_long_form_str_size(t_list_ls **head, t_max_len max) {
    t_list_ls *temp = *head;
	t_logformat *tl = NULL; //temp_long
	size_t len = 0;
    while (temp) {
		tl = temp->long_format;
		len = ft_strlen(tl->hardlink);
		tl->hard_width = max.hard_max - len;
		len = ft_strlen(tl->owner);
		tl->owener_width = max.own_max - len;
		len = ft_strlen(tl->group);
		tl->group_width = max.grp_max - len;
		len = ft_strlen(tl->size);
		tl->size_width = max.size_max - len;
		len = ft_strlen(tl->date);
		tl->date_width = max.date_max - len;
        temp = temp->next;
    }
}


void make_sate_data_to_string(t_list_ls **head) {
    t_list_ls *temp = *head;
	t_logformat *temp_long = NULL;
    while (temp) {
		temp->long_format = ft_calloc(sizeof(t_logformat), 1);
		if (temp->long_format == NULL) {
			print_error(ERR_MALLOC);
			exit_process(1);
		}
		temp_long = temp->long_format;
		temp_long->authority = decoding_authority(temp->st_mode);
		temp_long->hardlink = decoding_hardlink(temp->st_nlink);
		temp_long->owner = decoding_userID(temp->st_uid);
		temp_long->group = decoding_group(temp->st_gid);
		temp_long->size = decoding_size(temp->st_size);
		temp_long->date = decoding_time(&temp->st_mtim);
		if (temp_long->authority[0] == 'l') {
			temp_long->name = decoding_name(temp->path, temp->name);
		} else {
			temp_long->name = ft_strdup(temp->name);
			if (temp_long->name == NULL) {
				print_error(ERR_MALLOC);
				exit_process(1);
			}
		}
        temp = temp->next;
    }
}

char *decoding_authority(mode_t st_mode) {
	char arr[30] = {'0',};
	ft_memset(arr, '-', 10);
	int break_falg = 0;
	for (int i = 0; i < 8; i++) {
		switch (i) {
			case 0:
				if (S_ISREG(st_mode)) {
					break_falg = 1;
				}
			break;
			case 1:
				if (S_ISDIR(st_mode)) {
					break_falg = 1;
					arr[0] = 'd';
				}
			break;
			case 2:
				if (S_ISCHR(st_mode)) {
					break_falg = 1;
					arr[0] = 'c';
				}
			break;
			case 3:
				if (S_ISBLK(st_mode)) {
					break_falg = 1;
					arr[0] = 'b';
				}
			break;
			case 4:
				if (S_ISFIFO(st_mode)) {
					break_falg = 1;
					arr[0] = 'P';
				}
			break;
			case 5:
				if (S_ISLNK(st_mode)) {
					break_falg = 1;
					arr[0] = 'l';
				}
			break;
			case 6:
				if (S_ISSOCK(st_mode)) {
					break_falg = 1;
					arr[0] = 's';
				}
			break;
			default:
				if (i == 7) arr[0] = '?';
			break;

		}
		if (break_falg == 1) break;
	}
	break_falg = 0;
	char *rwx = "rwxrwxrwx";
	char *arr2 = &arr[1];
	for (int i = 0; i < 9; i++) {
		//개쩐다. 비트를 이렇게 이용할 수 있다니 이건 혁신이다.
		//이게 가능한 이유는 st_mode가 권한을 100 010 001 을 보장하기 때문이다. 즉 000 000 000 이 9 개의 비트
		//만큼 &(and) 연산으로 비교를 한다면 한번에 비교를 할 수있다.
		if (st_mode & (1 << (8 - i))) arr2[i] = rwx[i];
	}
	char *temp = ft_strdup(arr);
	if (temp == NULL) {
		print_error(ERR_MALLOC);
		exit_process(1);
	}
	return (temp);
}

char *decoding_hardlink(nlink_t st_nlink) {
	char *link = ft_itoa(st_nlink);
	if (link == NULL) {
		print_error(ERR_MALLOC);
		exit_process(1);
	}
	return (link);
}

char *decoding_userID(uid_t st_uid) {
	struct passwd *temp;
	errno = 0;
	temp = getpwuid(st_uid);
	if (temp == NULL && errno != 0) {
		print_error(ERR_PWUID);
		exit_process(1);
	}
	char *strDup;
	//못찾은경우
	if (temp == NULL) strDup = ft_itoa(st_uid);
	//찾은경우
	else strDup = ft_strdup(temp->pw_name);
	if (strDup == NULL) {
		print_error(ERR_MALLOC);
		exit_process(1);
	}
	return strDup;
}

char *decoding_group(gid_t st_gid) {
	struct group *temp;
	errno = 0;
	temp = getgrgid(st_gid);
	if (temp == NULL && errno != 0) {
		print_error(ERR_GRGID);
		exit_process(1);
	}
	char *strDup;
	//못찾은경우
	if (temp == NULL) strDup = ft_itoa(st_gid);
	//찾은경우
	else strDup = ft_strdup(temp->gr_name);
	if (strDup == NULL) {
		print_error(ERR_MALLOC);
		exit_process(1);
	}
	return strDup;
}

char *decoding_size(off_t st_size) {
	char *size = ft_itoa(st_size);
	if (size == NULL) {
		print_error(ERR_MALLOC);
		exit_process(1);
	}
	return (size);
}

//나중에 6개월이 지난 시간을 참조해서 바꿔줘야함.
//"Wed Jun 30 21:49:08 1993\n"
char *decoding_time(struct timespec *st_mtim) {
	time_t now = time(NULL);
	unsigned long comparison;
	char arr[1000] = {0,};

	char *time = ctime(&st_mtim->tv_sec);
	if (time == NULL) {
		print_error(ERR_CTIME);
		exit_process(1);
	}
	comparison = now - st_mtim->tv_sec;
	char **temp = ft_split(time, ' ');
	ft_strlcpy(arr, temp[1], sizeof(arr));
	if (ft_strlen(temp[2]) == 1) ft_strlcat(arr, "  ", sizeof(arr));
	else ft_strlcat(arr, " ", sizeof(arr));
	ft_strlcat(arr, temp[2], sizeof(arr));
	ft_strlcat(arr, " ", sizeof(arr));
	char *year = ft_strrchr(temp[4], '\n');
	*year = '\0';
	if (comparison > 15552000) {
		ft_strlcat(arr, " ", sizeof(arr));
		ft_strlcat(arr, temp[4], sizeof(arr));
	} else {
		temp[3][5] = '\0';
		ft_strlcat(arr, temp[3], sizeof(arr));
	}
	char *strDup = ft_strdup(arr);
	if (strDup == NULL) {
		print_error(ERR_MALLOC);
		exit_process(1);
	}
	ft_free_two(temp);
	return strDup;
}

char *decoding_name(const char *path, const char *name) {
	size_t path_size = PATH_MAX;
	char path_dup[path_size];
	char buf[path_size];
	char *temp = NULL;

	ft_memset(path_dup, 0, path_size);
	ft_strlcpy(path_dup, path, path_size);
	temp = ft_strrchr(path_dup, '/');
	*temp = '\0';
	temp = NULL;
	ft_memset(buf, 0, path_size);
	if (readlink(path_dup, buf, path_size) == -1) {
		print_error(ERR_READLINK);
		// exit_process(1);
	}
	char return_temp[path_size * 3];
	ft_memset(return_temp, 0, (path_size * 3));
	ft_strlcat(return_temp, name, sizeof(return_temp));
	ft_strlcat(return_temp, " -> ", sizeof(return_temp));
	ft_strlcat(return_temp, buf, sizeof(return_temp));
	char *return_value = ft_strdup(return_temp);
	if (return_value == NULL) {
		print_error(ERR_MALLOC);
		exit_process(1);
	}
	return return_value;
}