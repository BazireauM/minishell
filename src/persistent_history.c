/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   persistent_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametzen <ametzen@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:50:57 by ametzen           #+#    #+#             */
/*   Updated: 2023/08/15 10:27:27 by ametzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	restore_history(const char *save_file_path)
{
	char	*line_buffer;
	int		fd;

	fd = open(save_file_path, O_RDONLY);
	if (fd < 0)
		return ;
	line_buffer = get_next_line(fd);
	while (line_buffer)
	{
		add_history(line_buffer);
		free(line_buffer);
		line_buffer = get_next_line(fd);
	}
	close(fd);
}

static int	try_open(const char *path, int max_tries)
{
	int	fd;
	int	attempts;

	attempts = 0;
	while (attempts < max_tries)
	{
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		if (fd > 0)
			break ;
		attempts++;
	}
	return (fd);
}

// REVIEW can write() do partial writes?
void	save_command(const char *command, const char *save_file_path)
{
	int	fd;

	if (command == NULL)
		return ;
	if (ft_strlen(command) <= 0)
		return ;
	add_history(command);
	fd = try_open(save_file_path, 100);
	if (fd < 0)
		return ;
	write(fd, command, ft_strlen(command));
	write(fd, "\n", 1);
	close(fd);
}
