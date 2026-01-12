#ifndef FT_LS_H
#define FT_LS_H

#include "./dirStream.h"
#include "./utils.h"
#include "./ls_list.h"
#include "../libft/libft.h"
#include "../printf/libftprintf.h"

void ft_ls(t_list_ls **head);
void recReadDir(t_list_ls **head, DIR *openDir);


#endif