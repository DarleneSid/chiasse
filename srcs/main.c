/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 00:19:45 by dsydelny          #+#    #+#             */
/*   Updated: 2023/10/13 00:27:36 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	ft_memset(& data, 0, sizeof(t_data));
	if (ac != 2)
		return (ft_printf("Wrong amount of arguments!\n"), 1);
	if (ft_strncmp(&av[1][ft_strlen(av[1]) - 4], ".cub\0", 5))
		return (ft_printf("It has to end with .cub!\n"), 1);
	parsing(&data, av[1]);
	return (0);
}
