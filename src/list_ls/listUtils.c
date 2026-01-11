#include "../../include/ls_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void free_ls_list(t_list_ls **list) {
    if (list && *list) {
        free(*list);
        *list = NULL;
    }
}

t_list_ls *init_ls_list() {
    t_list_ls *return_value = malloc(sizeof(t_list_ls));
    if (return_value == NULL) return NULL;
    ft_memset(return_value, 0, sizeof(t_list_ls));
    return_value->name = NULL;
    return_value->next = NULL;
    return_value->child = NULL;
    return return_value;
}

unsigned int cnt_ls_list(t_list_ls **head) {
    unsigned int cnt = 0;
    t_list_ls *temp = *head;
    while (temp) {
        cnt++;
        temp = temp->next;
    }
    return cnt;
}

void ls_list_pushChild(t_list_ls **head, t_list_ls *child) {
    t_list_ls *temp = *head;
    temp->child = child;
}

void free_all_ls_list(t_list_ls **head){
    t_list_ls *temp = *head;

    while (temp) {
        if (temp->child != NULL) free_all_ls_list(&temp->child);
        if (temp->name != NULL) ft_freenull(&temp->name);
        temp = temp->next;
        free_ls_list(head);
        *head = temp;
    }
}

void ls_list_pushBack(t_list_ls **head, t_list_ls *next) {
    t_list_ls *temp = *head;
    while (temp) {
        if (temp->next == NULL) {
            temp->next = next;
            break;
        }
        temp = temp->next;
    }
}