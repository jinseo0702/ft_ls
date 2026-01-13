#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <errno.h>
#include "../libft/libft.h"
#include "../printf/libftprintf.h"

// 0000 0000 = l
// 0000 0001 = R
// 0000 0010 = a
// 0000 0100 = r
// 0000 1000 = t

typedef char t_option;

#define OPT_l (1 << 0)
#define OPT_R (1 << 1)
#define OPT_a (1 << 2)
#define OPT_r (1 << 3)
#define OPT_t (1 << 4)

#define HASOPT(opt, flag) (((opt) & (flag)) != 0)
#define SETOPT(opt, flag) ((opt) |= (flag))
#define CLROPT(opt, flag) ((opt) &= ~(flag))

typedef struct s_list_ls t_list_ls;

#define ERROR_LIST \
    X(ERR_MALLOC, "Mallioc Error") \
    X(ERR_OPENDIR, "Opendir Error") \
    X(ERR_READDIR, "Readdir Error") \
    X(ERR_CLOSEDIR, "Closedir Error") \
    X(ERR_INVAILD_OPTION, "invalid option -- ") \
    X(ERR_CANNOT_ACCESS, "cannot access ") \
    X(ERR_STATE, "State Error ")



typedef enum e_error {
    #define X(id, str) id,
        ERROR_LIST
    #undef X
} t_errr;

static inline const char *get_error_msg(t_errr err) {
    switch (err) {
        #define X(id ,str) case id: return str;
            ERROR_LIST
        #undef X
        default: return "Unknown Error";
    }
}

typedef struct s_parsing {
    char *str;
    struct s_parsing *next;
    t_list_ls *head;
} t_parsing ;

void print_error(t_errr error);
void print_error_ls(t_errr error, const char *str);
void exit_process(unsigned long ErrorNum);
void print_ls(int flag, t_list_ls **head);
void print_s_list_ls(t_list_ls *temp);
void print_s_list_parsing(t_parsing *temp);

//parsing.c
void free_parsing_list(t_parsing **list);
t_parsing *init_parsing_list();
unsigned int cnt_parsing_list(t_parsing **head);
void free_all_parsing_list(t_parsing **head);
void ls_parsing_pushBack(t_parsing **head, t_parsing *next);
void check_option(const char *str, t_option *opt);
int parsing_argument(t_parsing **head, char *argv[], t_option *op);

//doOption.c
void do_Option(t_list_ls **head, t_option op);

#endif