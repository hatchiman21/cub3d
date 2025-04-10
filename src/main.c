/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:32:26 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/10 14:58:12 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int main(int argc, char *argv[])
{
    t_cub3d data;
    
    if (argc != 2 || !argv[1][0])
    {
        ft_dprintf(2, "Error\n./cub3d file_name.cup\n");
        return (1);
    }
    check_file_name(argv[1]);
    check_empty_read(argv[1]);
    data.file.all_file = read_map(argv[1]);
    parse_map(&data);
    return (0);
}
