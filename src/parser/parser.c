#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "parser.h"
#include "get_next_line.h"

static int	extract_line_data(const char *line)
{
	int ret;

	ret = 0;
//	TODO: remove the debug line under
//	printf("The line is: %s\n", line);
	if (*line == 'A')
		ret = extract_ambient_light(line);	
	else if (*line == 'C')
		ret = extract_camera(line);
	else if (*line == 'L')
		ret = extract_light(line);
	else if (ft_strncmp(line, "sp", 2) == 0)
		ret = extract_sphere(line);
	else if (ft_strncmp(line, "pl", 2) == 0)
		ret = extract_plane(line);
	else if (ft_strncmp(line, "cy", 2) == 0)
		ret = extract_cylinder(line);
	else if (*line == '\n')
		ret = 0;
	else
		return (-1);
	return (ret);
}

void	hide_newline(char *line)
{
	if (!line)
		return ;
	while(*line != '\n')
		line++;
	if (*line == '\n')
		*line = 0;
}

int pars(const char *path)
{
	int	fd;
	char	*line;
	int	ret;

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
		ret = extract_line_data(line);
		if (ret == -1)
		{
			while(line) 
			{
				line = get_next_line(fd);
				free(line);
			}
			printf("Invalid file content!\n");
			return (-1);
		}
		line = get_next_line(fd);
		hide_newline(line);
	}
	return (0);
}
