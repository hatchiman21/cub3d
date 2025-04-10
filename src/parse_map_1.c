/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:12:06 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/10 18:54:52 by sbibers          ###   ########.fr       */
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
            exit(printf("Error\ntrim failed\n"));
        if (check_string(check))
        {
            free(check);
            normalized = normalize_config_line(lines[i]);
            if (!normalized)
            {
                printf("Error\nnormalize failed\n");
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
    printf("Error\nAllocation failed\n");
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
        printf("Error\nAllocation failed\n");
        exit(1);
    }
    creat_2darray_2(i, count, split, data);
    return split;
}

void    init_count(t_check_count *count, int *i)
{
    *i = -1;
    count->ceiling_color = 0;
    count->floor_color = 0;
    count->ea = 0;
    count->no = 0;
    count->so = 0;
    count->we = 0;
}

int check(char *str)
{
    if (ft_strncmp(str, "F ", 2) == 0 && ft_strlen(str) > 2)
        return (1);  // Floor color
    else if (ft_strncmp(str, "C ", 2) == 0 && ft_strlen(str) > 2)
        return (2);  // Ceiling color
    else if (ft_strncmp(str, "EA ", 3) == 0 && ft_strlen(str) > 3)
        return (3);  // East texture
    else if (ft_strncmp(str, "NO ", 3) == 0 && ft_strlen(str) > 3)
        return (4);  // North texture
    else if (ft_strncmp(str, "SO ", 3) == 0 && ft_strlen(str) > 3)
        return (5);  // South texture
    else if (ft_strncmp(str, "WE ", 3) == 0 && ft_strlen(str) > 3)
        return (6);  // West texture
    return (0);
}

void    check_char_1(t_cub3d *data)
{
    int i;

    init_count(&data->count, &i);
    while (data->file.split_all_file[++i])
    {
        // printf("%s\n", data->file.split_all_file[i]);
        if (check(data->file.split_all_file[i]) == 1)
            data->count.floor_color++;
        if (check(data->file.split_all_file[i]) == 2)
            data->count.ceiling_color++;
        if (check(data->file.split_all_file[i]) == 3)
            data->count.ea++;
        if (check(data->file.split_all_file[i]) == 4)
            data->count.no++;
        if (check(data->file.split_all_file[i]) == 5)
            data->count.so++;
        if (check(data->file.split_all_file[i]) == 6)
            data->count.we++;
    }
    // printf("%d\n", data->count.we);
    if (data->count.ceiling_color != 1 || data->count.floor_color != 1 || data->count.ea != 1
        || data->count.no != 1 || data->count.so != 1 || data->count.we != 1)
    {
        ft_free_split(data->file.split_all_file);
        printf("Error\nWrong map\n");
        exit(1);
    }
}

int find_newline(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    return (i);
}

int skip_spaces(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] == ' ')
        i++;
    if (str[i] == '\n' || (str[i] == '1' || str[i] == '0'))
        return (1);
    printf("str : %s\n", str);
    // exit(1);
    // else
    return (1);
}

void stop_parsing(t_cub3d *data)
{
    ft_free_split(data->file.split_all_file);
    if (data->bearings.ea)
        free(data->bearings.ea);
    else if (data->bearings.no)
        free(data->bearings.no);
    else if (data->bearings.so)
        free(data->bearings.so);
    else if (data->bearings.we)
        free(data->bearings.we);
    printf("Error\nWrong map\n");
}

int find_size_of_map(t_cub3d *data, int i)
{
    int j;

    j = 0;
    while (data->file.split_all_file[i])
    {
        if (data->file.split_all_file[i] == NULL)
            break;
        if (skip_spaces(data->file.split_all_file[i]) == 1)
        {
            i++;
            j++;
        }
        else
        {
            stop_parsing(data);
            exit(1);
        }
    }
    if (j == 0)
        stop_parsing(data);
    return (j);
}

void find_map(t_cub3d *data, int *i)
{
    int j;

    j = 0;
    if (skip_spaces(data->file.split_all_file[*i]))
    {
        int size = find_size_of_map(data, *i);
        data->map.map_2d = (char **) malloc(sizeof(char *) * size + 1);
        while (data->file.split_all_file[*i])
        {
            data->map.map_2d[j] = ft_strndup(data->file.split_all_file[*i], find_newline(data->file.split_all_file[*i]) + 1);
            (*i)++;
            j++;
        }
    }
    else
    {
        stop_parsing(data);
    }
    data->map.map_2d[j] = NULL;
}

void check_to_copy_file(t_cub3d *data, int *i)
{
    // printf("%s", data->file.split_all_file[*i]);
    // exit(1);
    if (check(data->file.split_all_file[*i]) == 1)
        data->floor_color = ft_strndup(data->file.split_all_file[*i], find_newline(data->file.split_all_file[*i] + 1));
    else if (check(data->file.split_all_file[*i]) == 2)
        data->ceiling_color = ft_strndup(data->file.split_all_file[*i], find_newline(data->file.split_all_file[*i] + 1));
    else if (check(data->file.split_all_file[*i]) == 3)
        data->bearings.ea = ft_strndup(data->file.split_all_file[*i], find_newline(data->file.split_all_file[*i] + 1));
    else if (check(data->file.split_all_file[*i]) == 4)
        data->bearings.no = ft_strndup(data->file.split_all_file[*i], find_newline(data->file.split_all_file[*i] + 1));
    else if (check(data->file.split_all_file[*i]) == 5)
        data->bearings.so = ft_strndup(data->file.split_all_file[*i], find_newline(data->file.split_all_file[*i] + 1));
    else if (check(data->file.split_all_file[*i]) == 6)
        data->bearings.we = ft_strndup(data->file.split_all_file[*i], find_newline(data->file.split_all_file[*i] + 1));
    else
        find_map(data, i);
}

void    make_map(t_cub3d *data)
{
    int i;
    
    i = -1;
    while (data->file.split_all_file[++i])
    {
        check_to_copy_file(data, &i);
    }
    ft_free_split(data->file.split_all_file);
}

void    parse_map(t_cub3d *data)
{
    data->file.split_all_file = create_2darray(data);
    free(data->file.all_file);
    if (!data->file.split_all_file || !data->file.split_all_file[0])
    {
        printf("Error\nFailed to allocate split lines\n");
        exit(1);
    }
    trim_config_lines(data->file.split_all_file);
    check_char_1(data);
    make_map(data);
    ft_free_split(data->file.split_all_file);
}
