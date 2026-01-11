#include "../../include/ls_list.h"
#include <stdio.h>


int main(void) {

    t_list_ls *head = init_ls_list();

    printf("%u \n", cnt_ls_list(&head));
    ls_list_pushBack(&head, init_ls_list());
    ls_list_pushBack(&head, init_ls_list());
    ls_list_pushBack(&head, init_ls_list());
    ls_list_pushBack(&head, init_ls_list());
    ls_list_pushBack(&head, init_ls_list());
    ls_list_pushBack(&head, init_ls_list());
    ls_list_pushBack(&head, init_ls_list());
    printf("%u \n", cnt_ls_list(&head));
    ls_list_pushChild(&head, init_ls_list());
    t_list_ls *childHead = head->child;
    ls_list_pushBack(&childHead, init_ls_list());
    ls_list_pushBack(&childHead, init_ls_list());
    ls_list_pushBack(&childHead, init_ls_list());
    ls_list_pushBack(&childHead, init_ls_list());
    ls_list_pushBack(&childHead, init_ls_list());
    ls_list_pushBack(&childHead, init_ls_list());
    ls_list_pushBack(&childHead, init_ls_list());
    ls_list_pushBack(&childHead, init_ls_list());
    ls_list_pushBack(&childHead, init_ls_list());
    ls_list_pushBack(&childHead, init_ls_list());
    ls_list_pushBack(&childHead, init_ls_list());
    printf("%u \n", cnt_ls_list(&childHead));
    ls_list_pushChild(&childHead, init_ls_list());
    t_list_ls *childHead2 = childHead->child;
    ls_list_pushBack(&childHead2, init_ls_list());
    ls_list_pushBack(&childHead2, init_ls_list());
    ls_list_pushBack(&childHead2, init_ls_list());
    ls_list_pushBack(&childHead2, init_ls_list());
    ls_list_pushBack(&childHead2, init_ls_list());
    ls_list_pushBack(&childHead2, init_ls_list());
    ls_list_pushBack(&childHead2, init_ls_list());
    ls_list_pushBack(&childHead2, init_ls_list());
    ls_list_pushBack(&childHead2, init_ls_list());
    ls_list_pushBack(&childHead2, init_ls_list());
    ls_list_pushBack(&childHead2, init_ls_list());
    ls_list_pushBack(&childHead2, init_ls_list());
    ls_list_pushBack(&childHead2, init_ls_list());
    ls_list_pushBack(&childHead2, init_ls_list());
    printf("%u \n", cnt_ls_list(&childHead2));
    ls_list_pushChild(&childHead2->next, init_ls_list());
    t_list_ls *childHead3 = childHead2->next->child;
    ls_list_pushBack(&childHead3, init_ls_list());
    ls_list_pushBack(&childHead3, init_ls_list());
    ls_list_pushBack(&childHead3, init_ls_list());
    ls_list_pushBack(&childHead3, init_ls_list());
    ls_list_pushBack(&childHead3, init_ls_list());
    ls_list_pushBack(&childHead3, init_ls_list());
    ls_list_pushBack(&childHead3, init_ls_list());
    ls_list_pushBack(&childHead3, init_ls_list());
    ls_list_pushBack(&childHead3, init_ls_list());
    ls_list_pushBack(&childHead3, init_ls_list());
    ls_list_pushBack(&childHead3, init_ls_list());
    ls_list_pushBack(&childHead3, init_ls_list());
    printf("%u \n", cnt_ls_list(&childHead3));
    free_all_ls_list(&head);

    return 0;
}