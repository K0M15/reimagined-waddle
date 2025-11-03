#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "parser.h"
#include "get_next_line.h"

static int	extract_line_data(const char *line, t_app *app, int *has_cam_and_amb)
{
	int ret;

	ret = 0;
	if (*line == 'A')
	{
		ret = extract_ambient_light(line, app);
		has_cam_and_amb[1] = 1;
	}
	else if (*line == 'C')
	{
		ret = extract_camera(line, app);
		has_cam_and_amb[0] = 1;
	}
	else if (*line == 'L')
		ret = extract_light(line, app);
	else if (ft_strncmp(line, "sp", 2) == 0)
		ret = extract_sphere(line, app);
	else if (ft_strncmp(line, "pl", 2) == 0)
		ret = extract_plane(line, app);
	else if (ft_strncmp(line, "cy", 2) == 0)
		ret = extract_cylinder(line, app);
	else if (ft_strncmp(line, "tr", 2) == 0)
		ret = extract_triangle(line, app);
	else if (ft_strncmp(line, "co", 2) == 0)
		ret = extract_cone(line, app);
	else if (*line == '\n')
		ret = 0;
	else if (*line == '#')
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

int pars(const char *path, t_app *app)
{
	int	fd;
	char	*line;
	int	ret;
	int camera_and_ambient[2];

	camera_and_ambient[0] = 0;
	camera_and_ambient[1] = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Could no open the file!");
		return (-1);
	}
	line = get_next_line(fd);
	hide_newline(line);
	ret = 0;
	while(line)
	{
		ret = extract_line_data(line, app, camera_and_ambient);
		if (ret == -1)
		{
			printf("Invalid line: %s\n", line);
			while(line) 
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
	if (camera_and_ambient[0] != 1 || camera_and_ambient[1] != 1)
	{
		printf("Camera and/or ambient light missing!\n");
		return (-1);
	}
	return (0);
}
