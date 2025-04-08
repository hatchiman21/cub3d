/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salam <salam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:32:26 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/08 23:58:32 by salam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void ft_free_split(char **arr)
{
    int i = 0;
    if (!arr)
        return;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

char *normalize_config_line(const char *line)
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

void trim_config_lines(char **lines)
{
    int i = 0;
    char *check;
    char *normalized;

    while (lines[i])
    {
        check = ft_strtrim(lines[i], " \t\n");
        if (!check)
            exit(ft_dprintf(2, "Error\ntrim failed\n"));
        if (ft_strncmp(check, "NO", 2) == 0
            || ft_strncmp(check, "SO", 2) == 0
            || ft_strncmp(check, "WE", 2) == 0
            || ft_strncmp(check, "EA", 2) == 0
            || ft_strncmp(check, "F", 1) == 0
            || ft_strncmp(check, "C", 1) == 0)
        {
            free(check);
            normalized = normalize_config_line(lines[i]);
            if (!normalized)
                exit(ft_dprintf(2, "Error\nnormalize failed\n"));
            free(lines[i]);
            lines[i] = normalized;
        }
        else
            free(check);
        i++;
    }
}

void parse_map(t_cub3d *data)
{
    data->split_all_file = ft_split(data->all_file, '\n');
    free(data->all_file);
    if (!data->split_all_file || !data->split_all_file[0])
    {
        ft_dprintf(2, "Error\nfaild to allocate");
        exit(1);
    }
    trim_config_lines(data->split_all_file);
    int i = 0;
    while (data->split_all_file[i])
    {
        printf("%s\n", data->split_all_file[i]);
        i++;
    }
    ft_free_split(data->split_all_file);
}

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
    data.all_file = read_map(argv[1]);
    parse_map(&data);
    return (0);
}
