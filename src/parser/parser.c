#include <fcntl.h>
#include <stdio.h>

static int	extract_line_data(const char *line)
{
	if (*line == 'A')
		extract_ambient_light(line);	
	else if (*line == 'C')
		extract_camera(line);
	else if (*line == 'L')
		extract_light(line);
	else if (ft_strncmp(line, 'sp', 2) == 0)
		extract_sphere(line);
	else if (ft_strncmp(line, 'pl', 2) == 0)
		extract_plane(line);
	else if (ft_strncmp(line, 'cy', 2) == 0)
		extract_cylinder(line);
	else
		return (-1);
	return (0);
}

int pars(const char *path)
{
	int	fd;
	char	*line;
	int	ret;

	fd = open(path, O_RDONLY);
	if (!fd)
	{
		printf("Could no open the file!");
		return (-1)
	}
	line = get_next_line(fd);
	while(line)
	{
		ret = extract_line_data(line)
		if (ret == -1)
		{
//TODO: maybe the while loop formating should change
			while(line);
			printf("Invalid file content!\n");
			return (-1);
		}
		line = get_next_line(fd);
	}
	return (0);
}
