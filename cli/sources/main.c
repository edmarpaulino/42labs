/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edpaulin <edpaulin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:58:28 by edpaulin          #+#    #+#             */
/*   Updated: 2022/02/27 19:43:09 by edpaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli.h"

static int	ft_print_log(int option, char *text);
static int	open_file(int option);
static void	error_exit(int option);
static void	print_file_lines(int fd, __u_long *n, int option, char *text);

int	main(int argc, char *argv[])
{
	if (argc == 1)
		return (ft_print_log(0, NULL));
	if (argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")))
		return (ft_print_log(1, NULL));
	if (argc == 3 && (!strcmp(argv[1], "-t") || !strcmp(argv[1], "--target")))
		return (ft_print_log(2, argv[2]));
	if (argc == 3 && (!strcmp(argv[1], "-n") || !strcmp(argv[1], "--number")))
		return (ft_print_log(3, argv[2]));
	if (argc == 2 && (!strcmp(argv[1], "-n") || !strcmp(argv[1], "--number")))
		return (ft_print_log(4, NULL));
	return (ft_print_log(5, NULL));
}

static int	ft_print_log(int option, char *text)
{
	int			fd;
	__u_long	n;

	fd = open_file(option);
	if (fd < 0)
		error_exit(option);
	n = 0;
	print_file_lines(fd, &n, option, text);
	close(fd);
	if (option == 2 && n == 0)
		printf("No matches found\n");
	else if (option == 3 || option == 4)
		printf("Total value: %ld\n", n);
	return (0);
}

static int	open_file(int option)
{
	int	fd;

	if (option == 1)
		return (open(HELP_FILE, O_RDONLY));
	if (option == 5)
		return (open(INVALID, O_RDONLY));
	return (open(LOG_FILE, O_RDONLY));
}

static void	error_exit(int option)
{
	if (option == 1)
		fprintf(stderr, "Error: failed to open \"%s\"", HELP_FILE);
	else if (option == 5)
		fprintf(stderr, "Error: failed to open \"%s\"", INVALID);
	else
		fprintf(stderr, "Error: failed to open \"%s\"", LOG_FILE);
	exit(EXIT_FAILURE);
}

static void	print_file_lines(int fd, __u_long *n, int option, char *text)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (option == 0 || option == 1 || option == 4 || option == 5)
		{
			if (option != 4)
				ft_putstr_fd(line, 1);
			(*n)++;
		}
		else if (option == 2 && strstr(line, text))
		{
			ft_putstr_fd(line, 1);
			(*n)++;
		}
		else if (option == 3 && strstr(line, text))
			(*n)++;
		free(line);
		line = get_next_line(fd);
	}
}
