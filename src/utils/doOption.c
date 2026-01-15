#include "../../include/utils.h"
#include "../../include/ls_list.h"
#include <sys/types.h>

void do_Option(t_list_ls **head, t_option op, blkcnt_t *total) {
    for (int i = 0; i < 4; i++) {
        switch (i) {
            case 0 :
                if (!HASOPT(op, OPT_a)) ls_list_remove(head, '.');
                break;
            case 1 :
                if(!HASOPT(op, OPT_t)) {
                    if (!HASOPT(op, OPT_r)) {
                        sort_list(head, ft_strncmp);
                    } else {
                        sort_reverse_list(head, ft_strncmp);
                    }
                }
                break;
            case 2 :
				if (HASOPT(op, OPT_l) || HASOPT(op, OPT_R) || HASOPT(op, OPT_t)) {
					make_long_format(head, total);
				}
                break;
            case 3 :
                if (HASOPT(op, OPT_t)) {
                    if (HASOPT(op, OPT_r)) {
                        time_sort_reverse_list(head);
                    } else {
                        time_sort_list(head);
                    }
                }
                break;
        }
    }
}