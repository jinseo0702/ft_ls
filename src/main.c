#include "../include/ft_ls.h"

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

void ft_ls(t_list_ls **head) {
    t_list_ls *temp = *head;
    char *path = NULL;

    temp->openDir = openDirectoryStream(temp->path);
    if (temp->openDir == NULL) exit_process(temp->ErrorNum);

    if (ft_strrstr(temp->path, "/", 1) == 0) {
        path = ft_strjoin(temp->path, "/");
    }
    else {
        path = ft_strdup(temp->path);
    }
    recReadDir(head, temp->openDir, path);
    closeDirectoryStream(temp->openDir);
    ft_freenull(&path);
    sort_list(head, ft_strncmp);
}

int main(int argc, char *argv[]) {
    //notyet check argc role
    argc += 1;
    t_list_ls *head = init_ls_list();
    head->path = ft_strdup(argv[1]);
    ft_ls(&head);
    print_ls(1, &head);
    // print_s_list_ls(head);
    free_all_ls_list(&head);
    return 0;
}