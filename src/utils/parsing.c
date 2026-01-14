#include "../../include/utils.h"
#include <unistd.h>


void free_parsing_list(t_parsing **list) {
    if (list && *list) {
        free(*list);
        *list = NULL;
    }
}

t_parsing *init_parsing_list() {
    t_parsing *return_value = malloc(sizeof(t_parsing));
    if (return_value == NULL) return NULL; //굳이 사용해야 할까?
    ft_memset(return_value, 0, sizeof(t_parsing));
    return return_value;
}

unsigned int cnt_parsing_list(t_parsing **head) {
    unsigned int cnt = 0;
    t_parsing *temp = *head;
    while (temp) {
        cnt++;
        temp = temp->next;
    }
    return cnt;
}

void free_all_parsing_list(t_parsing **head) {
    t_parsing *temp = *head;

    while (temp) {
        if (temp->str != NULL) ft_freenull(&temp->str);
        temp = temp->next;
        free_parsing_list(head);
        *head = temp;
    }
}

void ls_parsing_pushBack(t_parsing **head, t_parsing *next) {
    t_parsing *temp = *head;
    while (temp) {
        if (temp->next == NULL) {
            temp->next = next;
            break;
        }
        temp = temp->next;
    }
}

void check_option(const char *str, t_option *opt) {
    char arr[2] = {0,};
    for (int i = 1; str[i] != '\0'; ++i) {
        char c = str[i];
        switch (c) {
            case 'l':
                SETOPT(*opt, OPT_l);
                break;
            case 'R':
                SETOPT(*opt, OPT_R);
                break;
            case 'a':
                SETOPT(*opt, OPT_a);
                break;
            case 'r':
                SETOPT(*opt, OPT_r);
                break;
            case 't':
                SETOPT(*opt, OPT_t);
                break;
            default:
                arr[0] = c;
                print_error_ls(ERR_INVAILD_OPTION, arr);
                exit_process(ERR_INVAILD_OPTION);
                break;
        }
    }
}

int parsing_argument(t_parsing **head, char *argv[], t_option *op){
    t_parsing *temp = *head;
    t_parsing *next;
    int path_cnt = 0;

    if(argv[1][0] == '-' && ft_strlen(argv[1]) > 1) check_option(argv[1],  op);
    else {
        temp->str = ft_strdup(argv[1]);
        path_cnt++;
    };

    for (int i = 2; argv[i] != NULL; i++) {
        char c = argv[i][0];
        switch (c) {
            case '-' :
                if (ft_strlen(argv[i]) > 1) {
                    check_option(argv[i],  op);
                    break;
                }
                __attribute__((fallthrough)); //default 로 내려가는건 의도가 된 것이다. 라는 것을 컴파일러에게 알림
            default:
                if (temp->str == NULL) {
                    temp->str = ft_strdup(argv[i]);
                    path_cnt++;
                }
                else {
                    ls_parsing_pushBack(&temp, init_parsing_list());
                    next = temp->next;
                    next->str = ft_strdup(argv[i]);
                    path_cnt++;
                    temp = next;
                }
                break;
        }
    }
    return path_cnt;
}
