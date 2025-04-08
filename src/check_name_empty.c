/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name_empty.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:32:03 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/08 22:48:30 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    check_file_name(char *file_name)
{
    int     i;
    int     j;
    char    *name;

    if (ft_strlen(file_name) <= 3)
    {
        ft_dprintf(2, "Error\nfile_name must final with .cub\n");
        exit(1);
    }
    i = 0;
    j = 3;
    name = ".cub";
    while (file_name[i])
        i++;
    i--;
    while (j >= 0)
    {
        if (name[j--] != file_name[i--])
        {
            ft_dprintf(2, "Error\nfile_name must final with .cub\n");
            exit(1);
        }
    }
}

void check_empty_read(char *map_name)
{
    int     fd;
    char    buff[1];
    int     byte_read;

    fd = open(map_name, O_RDONLY);
    if (fd == -1)
    {
        ft_dprintf(2, "Error\ncan not read the file\n");
        exit(1);
    }
    byte_read = read(fd, buff, 1);
    close(fd);
    if (byte_read == 0)
    {
        ft_dprintf(2, "Error\nempty file\n");
        exit(1);
    }
}
