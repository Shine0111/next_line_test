#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#define BUFFER_SIZE 2

char	*read_from_file(int fd)
{
	int		bytes_read;
	char		*cup_buffer;
	static int	count = 1;

	printf("malloc#[%d]---", count++);
	cup_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!cup_buffer)
		return (NULL);
	cup_buffer[BUFFER_SIZE] = 0;
	bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(cup_buffer);
		return (NULL);
	}
	return (cup_buffer);
}

char	*get_next_line(int fd)
{
	char	*buffer;

	buffer = read_from_file(fd);
	return (buffer);
}

int	main(void)
{
	int	fd;
	char	*next_line;
	int	count;

	count = 0;
	fd = open("example.txt", O_RDONLY);
	//checks is open() fails
	if (fd == -1)
	{
		printf("Error opening file!");
		return (1);
	}
	while (1)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break ;
		count++;
		printf("[%d]:%s\n", count, next_line);
		free(next_line);
		next_line = NULL;
	}

	close(fd);
	return (0);
}
