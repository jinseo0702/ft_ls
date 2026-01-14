#include "../../include/utils.h"
#include "../../include/ls_list.h"
#include <sys/types.h>

void print_error(t_errr error) { 
    ft_fprintf(2, "[%s] : %s\n",get_error_msg(error) ,strerror(errno));
}

void print_error_ls(t_errr error, const char *str) { 
    ft_fprintf(2, "ls : %s '%s'\n",get_error_msg(error), str);
}

void exit_process(unsigned long ErrorNum) {
    exit(ErrorNum);
}

void print_ls(int flag, t_list_ls **head, blkcnt_t total) {
    t_list_ls *temp = *head;
    t_logformat *tl; //tmep_long

    if (flag == 0){
        while (temp) {
            if (temp->name != NULL) ft_printf("%s  ", temp->name);
            temp = temp->next;
        }
        ft_printf("\n");
    }
    else {
        tl = NULL;
        ft_printf("total %d\n", total);
        while (temp) {
            if (temp->name != NULL) {
                tl = temp->long_format;
                ft_printf("%s %*%s %s%* %s%* %*%s %s %s \n", tl->authority, tl->hard_width, tl->hardlink, tl->owner, tl->owener_width, tl->group, tl->group_width, tl->size_width, tl->size, tl->date, tl->name);
            }
            temp = temp->next;
        }
    }
}

void print_s_list_ls(t_list_ls *temp) {
    while (temp) {
        if (temp->next != NULL){
            ft_printf("\ns_list_l {\n");
            ft_printf("     openDir : %p\n", temp->openDir);
            ft_printf("     Path : %s\n", temp->path);
            ft_printf("     readDirPtr : %p\n", temp->readDirPtr);
            ft_printf("     Name : %s\n", temp->name);
            ft_printf("     St_mode : %o\n", temp->st_mode);
            ft_printf("     St_nlink : %d\n", temp->st_nlink);
            ft_printf("     St_uid : %d\n", temp->st_uid);
            ft_printf("     St_gid : %d\n", temp->st_gid);
            ft_printf("     St_size : %d\n", temp->st_size);
            ft_printf("     St_blocks : %d\n", temp->st_blocks);
            ft_printf("     St_mtim : %d\n", temp->st_mtim);
            ft_printf("     ErrorNum : %d\n", temp->ErrorNum);
            ft_printf("     Next : %p\n", temp->next);
            ft_printf("     Child : %p\n", temp->child);
            ft_printf("}\n\n");
        }
        temp = temp->next;
    }
    ft_printf("\n");
}

void print_s_list_parsing(t_parsing *temp) {
    while (temp) {
        if (temp->next != NULL){
            ft_printf("\ns_parsing {\n");
            ft_printf("     str : %s\n", temp->str);
            ft_printf("     next : %p\n", temp->next);
            ft_printf("     head : %p\n", temp->head);
            ft_printf("}\n\n");
        }
        temp = temp->next;
    }
    ft_printf("\n");
}