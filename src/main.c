/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:58:41 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/08 19:25:58 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

static void    check_file_name(char *file_name)
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

static void check_empty_read(char *map_name)
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

static void handle_memory_allocation(char *str, int fd)
{
    if (str)
        free(str);
    close(fd);
    ft_dprintf(2, "Error\nNULL check\n");
    exit(1);
}

static void read_map(char *map_name)
{
    char    *map;
    char    *str;
    int     fd;
    
    map = NULL;
    fd = open(map_name, O_RDONLY);
    while (1)
    {
       str = get_next_line(fd);
       printf("%s", str);
       if (!str)
           break;
       map = ft_strjoin_gnl(map, str);
       if (!map)
           handle_memory_allocation(str, fd);
       free(str);
    }
    // printf("%s\n", map);
    free(map);
    close(fd);
}

int main(int argc, char *argv[])
{
    // t_cub3d data;
    
    if (argc != 2 || !argv[1][0])
    {
        ft_dprintf(2, "Error\n./cub3d file_name.cup\n");
        return (1);
    }
    check_file_name(argv[1]);
    check_empty_read(argv[1]);
    read_map(argv[1]);
    return (0);
}
