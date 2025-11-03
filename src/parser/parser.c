/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:56:21 by kzarins           #+#    #+#             */
/*   Updated: 2025/11/03 20:56:23 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "parser.h"
#include <fcntl.h>
#include <stdio.h>

#define CAMERA 0
#define AMBIENT 1

static int	extract_objects(const char *line, t_app *app, int *ret)
{
	if (ft_strncmp(line, "sp", 2) == 0)
		*ret = extract_sphere(line, app);
	else if (ft_strncmp(line, "pl", 2) == 0)
		*ret = extract_plane(line, app);
	else if (ft_strncmp(line, "cy", 2) == 0)
		*ret = extract_cylinder(line, app);
	else if (ft_strncmp(line, "tr", 2) == 0)
		*ret = extract_triangle(line, app);
	else if (ft_strncmp(line, "co", 2) == 0)
		*ret = extract_cone(line, app);
	else
		return (1);
	return (*ret);
}

static int	extract_line_data(const char *line, t_app *app,
		int *has_cam_and_amb)
{
	int	ret;

	ret = 0;
	if (*line == 'A')
	{
		ret = extract_ambient_light(line, app);
		has_cam_and_amb[AMBIENT] = 1;
	}
	else if (*line == 'C')
	{
		ret = extract_camera(line, app);
		has_cam_and_amb[CAMERA] = 1;
	}
	else if (*line == 'L')
		ret = extract_light(line, app);
	else if (extract_objects(line, app, &ret) < 1)
		return (ret);
	else if (*line == '\n' || *line == '#')
		ret = 0;
	else
		return (-1);
	return (ret);
}

void	hide_newline(char *line)
{
	if (!line)
		return ;
	while(*line && *line != '\n')
		line++;
	if (*line && *line == '\n')
		*line = 0;
}

int	extract_all_lines(int fd, int camera_and_ambient[], t_app *app)
{
	char	*line;
	int		ret;

	line = get_next_line(fd);
	hide_newline(line);
	ret = 0;
	while (line)
	{
		ret = extract_line_data(line, app, camera_and_ambient);
		if (ret == -1)
		{
			printf("Invalid line: %s\n", line);
			while (line)
			{
				line = get_next_line(fd);
				free(line);
			}
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
		hide_newline(line);
	}
	return (0);
}

int	pars(const char *path, t_app *app)
{
	int	fd;
	int	camera_and_ambient[2];

	camera_and_ambient[CAMERA] = 0;
	camera_and_ambient[AMBIENT] = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (printf("Could no open the file!"), -1);
	if (extract_all_lines(fd, camera_and_ambient, app) == -1)
		return (-1);
	if (camera_and_ambient[CAMERA] != 1 || camera_and_ambient[AMBIENT] != 1)
		return (printf("Camera and/or ambient light missing!\n"), -1);
	return (0);
}
