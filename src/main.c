#include "../include/ft_ls.h"

void recReadDir(t_list_ls **head, DIR *openDir) {
    t_list_ls *temp = *head;
    readDirectoryStream(temp, openDir);
    if (temp->ErrorNum == -1) return ;
    else if (temp->ErrorNum != 0 && temp->ErrorNum != -1) {
        exit_process(temp->ErrorNum);
    }
    else {
        temp->name = ft_strdup(temp->readDirPtr.d_name);
        char *jointemp = ft_strjoin(temp->path, "/");
        if (temp->path != NULL) ft_freenull(&temp->path);
        temp->path = ft_strjoin(jointemp, temp->name);
        ft_freenull(&jointemp);
        ls_list_pushBack(head, init_ls_list());
        t_list_ls *temp_next = temp->next;
        temp_next->openDir = temp->openDir;
        temp_next->path = ft_strdup(temp->path);
        recReadDir(&temp_next, openDir);
    }
}

void ft_ls(t_list_ls **head) {
    t_list_ls *temp = *head;
    temp->openDir = openDirectoryStream(temp->path);
    if (temp->openDir == NULL) exit_process(temp->ErrorNum);

    recReadDir(head, temp->openDir);
    closeDirectoryStream(temp->openDir);
}

int main(int argc, char *argv[]) {
    //notyet check argc role
    argc += 1;
    t_list_ls *head = init_ls_list();
    head->path = ft_strdup(argv[1]);
    ft_ls(&head);
    print_ls(1, &head);
    free_all_ls_list(&head);
    return 0;
}