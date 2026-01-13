#include "../../include/ls_list.h"

void free_ls_list(t_list_ls **list) {
    if (list && *list) {
        free(*list);
        *list = NULL;
    }
}

t_list_ls *init_ls_list() {
    t_list_ls *return_value = malloc(sizeof(t_list_ls));
    if (return_value == NULL) return NULL; //굳이 사용해야 할까?
    ft_memset(return_value, 0, sizeof(t_list_ls));
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
        if (temp->path != NULL) ft_freenull(&temp->path);
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

void ls_list_remove(t_list_ls **head, const unsigned char c) {
    t_list_ls **pp= head;
    t_list_ls *cur;
    while (*pp) {
        cur = *pp;
        if (cur->name && (unsigned char)cur->name[0] == c) {
            *pp = cur->next;
            if (cur->name != NULL) ft_freenull(&cur->name);
            if (cur->path != NULL) ft_freenull(&cur->path);
            free_ls_list(&cur);
            continue;
        }
        pp = &((*pp)->next);
    }
}

void sort_list(t_list_ls **head, int (*cmp)()) {
    int swapped;
    t_list_ls *cur;
    t_list_ls *next;
    t_list_ls **pp;
    size_t len_cur;
    size_t len_next;
    size_t len;

    do {
        swapped = 0;
        pp = head;
        while (*pp && (*pp)->next) {
            cur = *pp;
            next = cur->next;
            len_cur = ft_strlen(cur->name);
            len_next = ft_strlen(next->name);
            len = len_cur > len_next ? len_cur : len_next;
            if (cmp(cur->name, next->name, len) > 0) {
                cur->next = next->next;
                next->next = cur;
                *pp = next;
                swapped = 1;
            }
            pp = &((*pp)->next);
        }
    }while (swapped);
}

void sort_reverse_list(t_list_ls **head, int (*cmp)()) {
    int swapped;
    t_list_ls *cur;
    t_list_ls *next;
    t_list_ls **pp;
    size_t len_cur;
    size_t len_next;
    size_t len;

    do {
        swapped = 0;
        pp = head;
        while (*pp && (*pp)->next) {
            cur = *pp;
            next = cur->next;
            len_cur = ft_strlen(cur->name);
            len_next = ft_strlen(next->name);
            len = len_cur > len_next ? len_cur : len_next;
            if (cmp(cur->name, next->name, len) < 0) {
                cur->next = next->next;
                next->next = cur;
                *pp = next;
                swapped = 1;
            }
            pp = &((*pp)->next);
        }
    }while (swapped);
}