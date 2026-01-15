#include "../include/ft_ls.h"

//0000 0000

void recReadDir(t_list_ls **head, DIR *openDir, char *path) {
    t_list_ls *temp = *head;
    readDirectoryStream(temp, openDir);
    if (temp->ErrorNum == -1) return ;
    else if (temp->ErrorNum != 0 && temp->ErrorNum != -1) {
        exit_process(temp->ErrorNum);
    }
    else {
        temp->name = ft_strdup(temp->readDirPtr.d_name);
        char *jointemp = ft_strjoin(temp->name, "/");
        if (temp->path != NULL) ft_freenull(&temp->path);
        temp->path = ft_strjoin(path, jointemp);
        ft_freenull(&jointemp);
        ls_list_pushBack(head, init_ls_list());
        t_list_ls *temp_next = temp->next;
        temp_next->openDir = temp->openDir;
        temp_next->path = ft_strdup(temp->path);
        recReadDir(&temp_next, openDir, path);
    }
}

void ft_ls(t_list_ls **head, t_option op, int path_cnt) {
    t_list_ls *temp = *head;
    blkcnt_t total = 0;
    char *path = NULL;

    temp->openDir = openDirectoryStream(temp->path);
    // if (temp->openDir == NULL) exit_process(temp->ErrorNum);
    if (temp->openDir == NULL) return;

    if (ft_strrstr(temp->path, "/", 1) == 0) {
        path = ft_strjoin(temp->path, "/");
    }
    else {
        path = ft_strdup(temp->path);
    }
    recReadDir(head, temp->openDir, path);
    closeDirectoryStream(temp->openDir);
    do_Option(head, op, &total);
    // print_s_list_ls(*head);//
    ft_freenull(&path);
    char arr[10000];
    ft_memset(arr, 0, sizeof(arr));
    ft_strlcpy(arr, (*head)->path, sizeof(arr));
    char *slash_ptr = ft_strrchr(arr, '/');
    *slash_ptr = '\0';
    slash_ptr = ft_strrchr(arr, '/');
    *slash_ptr = '\0';
	if (total != 0) total /= 2;
    if (path_cnt > 1 || HASOPT(op, OPT_R)) {
        ft_printf("%s:\n", arr);
        if (HASOPT(op, OPT_l)) {
            print_ls(OPT_l, head, total);
        }
        else {
            print_ls(0, head, total);
        }
        ft_printf("\n", arr);
    }
    else {
        if (HASOPT(op, OPT_l)) {
            print_ls(OPT_l, head, total);
        }
        else {
            print_ls(0, head, total);
        }
    }
	//recursive
	t_list_ls *temp2 = *head;
	if (HASOPT(op, OPT_R)) {
		while (temp2) {
			if (ft_strlen(temp2->name) == 1 && temp2->name[0] == '.') {
				temp2 = temp2->next;
				continue;
			}
			if (ft_strlen(temp2->name) == 2 && ft_strncmp(temp2->name, "..", 2) == 0) {
				temp2 = temp2->next;
				continue;
			}
			if (temp2->long_format->authority[0] == 'd') {
				ls_list_pushChild(&temp2, init_ls_list());
				temp2->child->path = ft_strdup(temp2->path);
				ft_ls(&temp2->child, op, path_cnt);
			}
			temp2 = temp2->next;
		}
	}
}

int main(int argc, char *argv[]) {
    //notyet check argc role
    t_option option = 0;
    t_parsing *parsing_head = init_parsing_list();
    t_parsing *temp;
    int path_cnt = 0;

    if (argc > 1) {
        path_cnt = parsing_argument(&parsing_head, argv, &option);
    }
    if (path_cnt == 0) {
        parsing_head->str = ft_strdup(".");
    }
    temp = parsing_head;
    // print_s_list_parsing(temp);
    while (temp) {
        temp->head = init_ls_list();
        temp->head->path = ft_strdup(temp->str);
        ft_ls(&temp->head, option, path_cnt);
        free_all_ls_list(&temp->head);
        temp = temp->next;
    }
    // print_s_list_ls(head);
    free_all_parsing_list(&parsing_head);
    return 0;
}