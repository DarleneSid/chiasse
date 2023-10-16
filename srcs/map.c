/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 00:21:29 by dsydelny          #+#    #+#             */
/*   Updated: 2023/10/16 01:59:40 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	height_of_map(int fd)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = get_next_line(fd);
	if (!tmp)
		return (-1);
	while (tmp)
	{
		i++;
		free(tmp);
		tmp = get_next_line(fd);
		// if (!tmp)
		// 	return (printf("or this\n"), -1);
	}
	return (i);
}
//why if i protect its error?

void	free_dstr(char **dstr)
{
	int	i;

	if (!dstr)
		return ;
	i = 0;
	while (dstr[i])
		free(dstr[i++]);
	free(dstr);
}

int	invalid_start(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '\n')
		return (1);
	while (s[i] && s[i] == '\n')
	{
		if (s[i] != ' ' || s[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	is_floor(t_data *data, char *s)
{
	int		i;
	int		j;
	char	**ithinkdifferent;
	int number = 0;
	int count = 0;
	i = 2;
	j = 0;
	if (s[0] != 'F')
		return (-1);
	if (s[1] != ' ')
		return (-1);
	// 1 space or ???
	ithinkdifferent = ft_split(&s[i], ',');
	if (!ithinkdifferent)
		return (-1);
	while (ithinkdifferent[count])
	{
		number = ft_atoi(ithinkdifferent[count]);
		if (count == 0 && number >= 0 && number <= 255)
			data->f_r = number;
		if (count == 1 && number >= 0 && number <= 255)
			data->f_g = number;
		if (count == 2 && number >= 0 && number <= 255)
			data->f_b = number;
		count++;
	}
	free_dstr(ithinkdifferent);
	return (1);
}

int	is_ceiling(t_data *data, char *s)
{
	int		i;
	int		j;
	char	**ithinkdifferent;
	int number = 0;
	int count = 0;
	i = 2;
	j = 0;
	if (s[0] != 'C')
		return (-1);
	if (s[1] != ' ')
		return (-1);
	// 1 space or ???
	ithinkdifferent = ft_split(&s[i], ',');
	if (!ithinkdifferent)
		return (-1);
	while (ithinkdifferent[count])
	{
		number = ft_atoi(ithinkdifferent[count]);
		if (count == 0 && number >= 0 && number <= 255)
			data->c_r = number;
		if (count == 1 && number >= 0 && number <= 255)
			data->c_g = number;
		if (count == 2 && number >= 0 && number <= 255)
			data->c_b = number;
		count++;
	}
	free_dstr(ithinkdifferent);
	return (1);
}


int	check_valid_chars(t_data *data, char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] == '\n')
	{
		if (s[i] == '1' || s[i] == '0' || s[i] == ' ')
			i++;
		else if (s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
		{
			data->pos--;
			i++;
		}
		else
			return (0);
	}
	if (!s)
		return (0);
	return (1);
}

int	check_valid_char(char s)
{
	if (s == '1' || s == '0' || s == ' ' || s == 'N' || s == 'S' || s == 'E' || s == 'W')
		return (1);
	return (0);
}


int	init_map(t_data *data, int fd)
{
	int			row;
	char		*tmp;
	char		**map;

	row = 0;
	int i = 0;
	map = ft_calloc(sizeof(char *), (data->height + 1));
	if (!map)
		return (1);
	tmp = get_next_line(fd);
	if (!tmp)
		return (1);
	while (tmp && i < data->height)
	{
		map[row] = ft_calloc(sizeof(char), ft_strlen(tmp) + 1);
		map[row] = ft_strdup(tmp);
		row++;
		free(tmp);
		tmp = get_next_line(fd);
	}
	data->map = map;
	if (!data->map)
		return (free_dstr(data->map), free(map), close(fd), exit(0), 1);
	return (0);
}


char **check_map(t_data *data, int cur_row)
{
	int			row;
	char		**map;

	row = 0;
	int i = 1;
	data->h_map = data->height - cur_row;
	printf("i cum???\n");
	map = ft_calloc(sizeof(char *), (data->h_map + 1));
	if (!map)
		return (NULL);
	if (invalid_start(data->map[cur_row]) == 0)
	{
		map[row] = ft_calloc(sizeof(char), ft_strlen(data->map[cur_row]) + 1);
		map[row] = ft_strdup(data->map[cur_row]);
		row++;
		cur_row++;
		while((i < data->h_map) && check_valid_chars(data, data->map[cur_row]))
		{
			if (check_valid_chars(data, data->map[cur_row]) && data->pos >= 0)
			{
				map[row] = ft_calloc(sizeof(char), ft_strlen(data->map[cur_row]) + 1);
				map[row] = ft_strdup(data->map[cur_row]);
				row++;
				cur_row++;
				i++;
			}
			else if (check_valid_chars(data, data->map[cur_row]) && data->pos < 0)
			{
				free_dstr(map);
				return (NULL);
			}
			else
				return (printf("not valid map\n"), NULL);
		}
	}
	else
		return (ft_printf("NOT VALID MAP\n"), NULL);
	return (map);
}




int	all_stuff_map(t_data *data)
{
	int			row;

	row = 0;
	data->pos = 1;
	data->all_inside = 6;
	printf("pochemu suka?\n");
	while (data->map[row])
	{	
		while (data->map[row] && invalid_start(data->map[row]) == 1)
		{
			//if is_path
			// 	// : NO SO WE EA
			// check_all_path??
			if (is_floor(data, data->map[row]) != -1)
			{
				data->all_inside--;
				row++;
			}
			if (is_ceiling(data, data->map[row]) != -1)
			{
				data->all_inside--;
				row++;
			}
			if (data->map[row][0] == '\n')
				row++;
			if (is_floor(data, data->map[row]) == -1 && is_ceiling(data, data->map[row]) == -1 && data->map[row][0] != '\n' &&  invalid_start(data->map[row]))
				return (ft_printf("NOT VALID MAP wtf: %s\n", data->map[row]), -1);
		}
		printf("why no cum?\n");
		if (invalid_start(data->map[row]) == 0)
		{
			data->work_map = check_map(data, row);
			if (!data->work_map)
				return (free_dstr(data->work_map), exit(0), -1);
		}
		else
			return (-1);
	}
	free_dstr(data->map);
	return (0);
}

int	parsing(t_data *data, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		(ft_printf("Not valid fd!\n"), exit(0));
	data->height = height_of_map(fd);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		(ft_printf("Not valid fd!\n"), exit(0));
	init_map(data, fd);
	close(fd);
	all_stuff_map(data);
	printf("h %d\n", data->height);
	printf("h map %d\n", data->h_map);
	int k = 0;
	while (k < data->height)
	{
		printf("%s", data->map[k]);
		k++;
	}
	printf("MY MAP:\n\n\n");
	k = 0;
	while (k < data->h_map)
	{
		printf("%s", data->work_map[k]);
		k++;
	}
	return (0);
}

