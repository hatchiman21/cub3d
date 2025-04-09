/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:12:06 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/09 18:59:30 by sbibers          ###   ########.fr       */
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
    int i = -1;
    while (data->file.split_all_file[++i])
        printf("%s\n", data->file.split_all_file[i]);
    ft_free_split(data->file.split_all_file);
}
