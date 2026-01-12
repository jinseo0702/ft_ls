#include "../../include/utils.h"
#include "../../include/ls_list.h"

void print_error(t_errr error) { 
    ft_fprintf(2, "[%s] : %s\n",get_error_msg(error) ,strerror(errno));
}

void exit_process(unsigned long ErrorNum) {
    exit(ErrorNum);
}

void print_ls(int flag, t_list_ls **head) {
    t_list_ls *temp = *head;
    flag += 1;
    while (temp) {
        if (temp->name != NULL) ft_printf("%s ", temp->name);
        temp = temp->next;
    }
    ft_printf("\n");
}