/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:12:06 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/11 17:56:29 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void ft_free_split(char **arr)
{
    int i = 0;
    if (!arr)
        return;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

static char *normalize_config_line(const char *line)
{
    char *key, *value, *joined, *final;
    char *tmp_key, *tmp_value;
    int i = 0;

    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    int start = i;
    while (line[i] && line[i] != ' ' && line[i] != '\t')
        i++;
    key = ft_substr(line, start, i - start);
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    value = ft_strdup(line + i);
    if (!key || !value)
    {
        free(key);
        free(value);
        return (NULL);
    }
    tmp_key = key;
    tmp_value = value;
    key = ft_strtrim(tmp_key, " \t");
    value = ft_strtrim(tmp_value, " \t");
    free(tmp_key);
    free(tmp_value);
    if (!key || !value)
    {
        free(key);
        free(value);
        return (NULL);
    }
    joined = ft_strjoin(key, " ");
    free(key);
    if (!joined)
    {
        free(value);
        return (NULL);
    }
    final = ft_strjoin_gnl(joined, value);
    free(value);
    return (final);
}

int check_string(char *check)
{
    if ((ft_strncmp(check, "NO", 2) == 0
    || ft_strncmp(check, "SO", 2) == 0
    || ft_strncmp(check, "WE", 2) == 0
    || ft_strncmp(check, "EA", 2) == 0
    || ft_strncmp(check, "F", 1) == 0
    || ft_strncmp(check, "C", 1) == 0)
    || (ft_strncmp(check, "1", 1) != 0
        && ft_strncmp(check, "0", 1) != 0))
        return (1);
    return (0);
}

static void trim_config_lines(char **lines)
{
    int i;
    char *check;
    char *normalized;

    i = -1;
    while (lines[++i])
    {
        check = ft_strtrim(lines[i], " \t\n");
        if (!check)
            exit(ft_dprintf(2, "Error\ntrim failed\n"));
        if (check_string(check))
        {
            free(check);
            normalized = normalize_config_line(lines[i]);
            if (!normalized)
            {
                ft_dprintf(2, "Error\nnormalize failed\n");
                exit(1);
            }
            free(lines[i]);
            lines[i] = normalized;
        }
        else
            free(check);
    }
}

char	*ft_strndup(const char *s, int n)
{
	char	*dup;
	char	*d;
	int		len;

	len = 0;
	while (s[len] && len < n)
		len++;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	d = dup;
	while (len > 0)
	{
		*d = *s;
		d++;
		s++;
		len--;
	}
	*d = '\0';
	return (dup);
}

int ft_newline(char *str, int *i)
{
    while (str[*i] && str[*i] != '\n')
        (*i)++;
    return (*i);
}

void exit_allocation(char **split, t_cub3d *data)
{
    ft_free_split(split);
    free(data->file.all_file);
    ft_dprintf(2, "Error\nAllocation failed\n");
    exit(1);
}

void creat_2darray_2(int i, int count, char **split, t_cub3d *data)
{
    i = 0;
    count = 0;
    while (data->file.all_file[i])
    {
        int start = i;
        while (data->file.all_file[i] && data->file.all_file[i] != '\n')
            i++;
        if (i > start)
        {
            split[count] = ft_strndup(data->file.all_file + start, i - start);
            if (!split[count])
                exit_allocation(split, data);
        }
        else
        {
            split[count] = ft_strdup("\n");
            if (!split[count])
                exit_allocation(split, data);
        }
        count++;
        i++;
    }
    split[count] = NULL;
}

char **create_2darray(t_cub3d *data)
{
    int i;
    int count;
    char **split;

    i = 0;
    count = 0;
    while (data->file.all_file[i])
    {
        count++;
        while (data->file.all_file[i] && data->file.all_file[i] != '\n')
            i++;
        i++;
    }
    split = malloc(sizeof(char *) * (count + 1));
    if (!split)
    {
        free(data->file.all_file);
        ft_dprintf(2, "Error\nAllocation failed\n");
        exit(1);
    }
    creat_2darray_2(i, count, split, data);
    return split;
}

void uncomplete_map(t_cub3d *data, int flag)
{
    if (data->file.split_all_file)
        ft_free_split(data->file.split_all_file);
    if (data->bearings.ea)
        free(data->bearings.ea);
    if (data->bearings.no)
        free(data->bearings.no);
    if (data->bearings.so)
        free(data->bearings.so);
    if (data->bearings.we)
        free(data->bearings.we);
    if (data->file.complete_file)
        free(data->file.complete_file);
    if (data->floor_color)
        free(data->floor_color);
    if (data->ceiling_color)
        free(data->ceiling_color);
    if (flag == 1)
        printf("Error\nWrong map\n");
    else if (flag == 0)
        printf("Error\nMemory allocation faild\n");
    exit(1);
}

void init_data(t_cub3d *data)
{
    data->file.complete_file = NULL;
    data->floor_color = NULL;
    data->ceiling_color = NULL;
    data->bearings.ea = NULL;
    data->bearings.no = NULL;
    data->bearings.so = NULL;
    data->bearings.we = NULL;
    data->counter.count_ea = 0;
    data->counter.count_no = 0;
    data->counter.count_so = 0;
    data->counter.count_we = 0;
    data->counter.count_floor_color = 0;
    data->counter.count_ceiling_color = 0;
}

void check_comma(t_cub3d *data)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (data->floor_color[i])
    {
        if (data->floor_color[i] == ',')
            count++;
        i++;
    }
    if (count != 2)
        uncomplete_map(data, 1);
    count = 0;
    i = 0;
    while (data->ceiling_color[i])
    {
        if (data->ceiling_color[i] == ',')
            count++;
        i++;
    }
    if (count != 2)
        uncomplete_map(data, 1);
}

void check_files(t_cub3d *data)
{
    int fd;

    fd = open(data->bearings.ea, O_RDONLY);
    if (fd == -1)
        uncomplete_map(data, 1);
    close (fd);
    fd = open(data->bearings.no, O_RDONLY);
    if (fd == -1)
        uncomplete_map(data, 1);
    close (fd);
    fd = open(data->bearings.so, O_RDONLY);
    if (fd == -1)
        uncomplete_map(data, 1);
    close (fd);
    fd = open(data->bearings.we, O_RDONLY);
    if (fd == -1)
        uncomplete_map(data, 1);
    close (fd);
}

void check_bearings_colors(t_cub3d *data)
{
    check_comma(data);
    check_files(data);
}

void split_lines(t_cub3d *data)
{
    int i;

    i = 0;
    init_data(data);
    while (data->file.split_all_file[i])
    {
        if (ft_strncmp(data->file.split_all_file[i], "F ", 2) == 0)
        {
            data->floor_color = ft_strndup(data->file.split_all_file[i] + 2, ft_strlen(data->file.split_all_file[i]) - 2);
            data->counter.count_floor_color++;
        }
        else if (ft_strncmp(data->file.split_all_file[i], "C ", 2) == 0)
        {
            data->ceiling_color = ft_strndup(data->file.split_all_file[i] + 2, ft_strlen(data->file.split_all_file[i]) - 2);
            data->counter.count_ceiling_color++;
        }
        else if (ft_strncmp(data->file.split_all_file[i], "NO ", 3) == 0)
        {
            data->bearings.no = ft_strndup(data->file.split_all_file[i] + 3, ft_strlen(data->file.split_all_file[i]) - 3);
            data->counter.count_no++;
        }
        else if (ft_strncmp(data->file.split_all_file[i], "SO ", 3) == 0)
        {
            data->bearings.so = ft_strndup(data->file.split_all_file[i] + 3, ft_strlen(data->file.split_all_file[i]) - 3);
            data->counter.count_so++;
        }
        else if (ft_strncmp(data->file.split_all_file[i], "WE ", 3) == 0)
        {
            data->bearings.we = ft_strndup(data->file.split_all_file[i] + 3, ft_strlen(data->file.split_all_file[i]) - 3);
            data->counter.count_we++;
        }
        else if (ft_strncmp(data->file.split_all_file[i], "EA ", 3) == 0)
        {
            data->bearings.ea = ft_strndup(data->file.split_all_file[i] + 3, ft_strlen(data->file.split_all_file[i]) - 3);
            data->counter.count_ea++;
        }
        else
            data->file.complete_file = ft_strjoin_gnl(data->file.complete_file, data->file.split_all_file[i]);
        i++;
    }
    if (!data->floor_color || !data->ceiling_color || !data->bearings.ea
        || !data->bearings.no || !data->bearings.so || !data->bearings.we
        || data->counter.count_ceiling_color != 1 || data->counter.count_floor_color != 1
        || data->counter.count_ea != 1 || data->counter.count_so != 1
        || data->counter.count_we != 1 || data->counter.count_no != 1)
        uncomplete_map(data, 1);
    check_bearings_colors(data);
}

void check_complete_file(t_cub3d *data)
{
    int i;

    i = 0;
    while (data->file.complete_file[i])
    {
        if (data->file.complete_file[i] != '0' && data->file.complete_file[i] != '1'
        && data->file.complete_file[i] != ' ' && data->file.complete_file[i] != '\n'
        && data->file.complete_file[i] != 'N' && data->file.complete_file[i] != 'S'
        && data->file.complete_file[i] != 'E' && data->file.complete_file[i] != 'W')
            uncomplete_map(data, 1);
        i++;
    }
    free(data->file.complete_file);
    data->file.complete_file = NULL;
}

int skip_spaces(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] == ' ')
        i++;
    if (str[i] == '1' || str[i] == '0')
        return (1);
    else
        return (0);
}


void create_map(t_cub3d *data)
{
    int i;
    int j;
    int map_lines;
    int temp;

    i = 0;
    j = 0;
    map_lines = 0;
    while (data->file.split_all_file[i])
    {
        if (skip_spaces(data->file.split_all_file[i]))
            break;
        i++;
    }
    temp = i;
    while (data->file.split_all_file[temp])
    {
        map_lines++;
        temp++;
    }
    data->map.map = malloc(sizeof(char *) * (map_lines + 1));
    if (!data->map.map)
        uncomplete_map(data, 0);
    while (data->file.split_all_file[i])
    {
        data->map.map[j] = ft_strdup(data->file.split_all_file[i]);
        if (!data->map.map[j])
        {
            ft_free_split(data->map.map);
            uncomplete_map(data, 0);
        }
        i++;
        j++;
    }
    data->map.map[j] = NULL;
    ft_free_split(data->file.split_all_file);
    data->file.split_all_file = NULL;
}

void	check_map(t_cub3d *data)
{
	int		i;
	int		j;
	int		player_count;
	char	c;

	i = 0;
	player_count = 0;
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
		{
			c = data->map.map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				player_count++;
			else if (c != '0' && c != '1' && c != ' ' && c != '\n')
			{
				ft_free_split(data->map.map);
                uncomplete_map(data, 1);
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
	{
        ft_free_split(data->map.map);
        uncomplete_map(data, 1);
	}
}

void parse_map(t_cub3d *data)
{
    data->file.split_all_file = create_2darray(data);
    free(data->file.all_file);
    if (!data->file.split_all_file || !data->file.split_all_file[0])
    {
        ft_dprintf(2, "Error\nFailed to allocate split lines\n");
        exit(1);
    }
    trim_config_lines(data->file.split_all_file);
    split_lines(data);
    check_complete_file(data);
    create_map(data);
    check_map(data);
    // for no leaks, check if all done, except flood fill and colors.
    ft_free_split(data->map.map);
    uncomplete_map(data, 1);
}
