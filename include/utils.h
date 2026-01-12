#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <errno.h>
#include "../libft/libft.h"
#include "../printf/libftprintf.h"

typedef struct s_list_ls t_list_ls;

#define ERROR_LIST \
    X(ERR_MALLOC, "Mallioc Error") \
    X(ERR_OPENDIR, "Opendir Error") \
    X(ERR_READDIR, "Readdir Error") \
    X(ERR_CLOSEDIR, "Closedir Error")



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

void print_error(t_errr error);
void exit_process(unsigned long ErrorNum);
void print_ls(int flag, t_list_ls **head);

#endif