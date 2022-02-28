/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edpaulin <edpaulin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:44:28 by edpaulin          #+#    #+#             */
/*   Updated: 2022/02/27 19:54:38 by edpaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "api.h"

static void	fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data);
static char	*get_json(void);
static void	signal_handler(int signo);
static void	att_log_file(const char *method, const char *status);

static int	g_signo = 0;
static char	*g_json = NULL;

int	main(void)
{
	struct mg_mgr	mgr;

	g_json = get_json();
	if (!g_json)
	{
		write(2, "Error: cannot import json file.\n", 32);
		return (1);
	}
	mg_mgr_init(&mgr);
	mg_http_listen(&mgr, HOST, fn, NULL);
	signal(SIGINT, &signal_handler);
	while (g_signo == 0)
		mg_mgr_poll(&mgr, 1000);
	mg_mgr_free(&mgr);
	free(g_json);
}

static void	fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	struct mg_http_message	*hm;

	if (ev == MG_EV_HTTP_MSG)
	{
		hm = (struct mg_http_message *)ev_data;
		if (mg_http_match_uri(hm, "/") && !strncmp(hm->method.ptr, "GET", 3))
		{
			mg_http_reply(c, 200, JSON_TYPE, g_json);
			att_log_file(hm->method.ptr, "200");
		}
		else
		{
			mg_http_reply(c, 404, JSON_TYPE, "{\"return\": \"Not found\"}\n");
			att_log_file(hm->method.ptr, "404");
		}
	}
}

static char	*get_json(void)
{
	int		json_fd;
	ssize_t	bytes_read;
	char	buffer[30000];

	json_fd = open("./json/planetas.json", O_RDONLY);
	if (json_fd < 0)
		return (NULL);
	bytes_read = read(json_fd, buffer, 30000);
	close(json_fd);
	if (bytes_read < 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	return (strdup(buffer));
}

static void	signal_handler(int signo)
{
	g_signo = signo;
	write(1, "\n", 1);
}

static void	att_log_file(const char *method, const char *status)
{
	int			fd;
	time_t		t;
	struct tm	tm;
	char		*http_method;
	char		*endpoint;

	t = time(NULL);
	tm = *localtime(&t);
	fd = open("./log/logs.txt", O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fd < 0)
		return ;
	http_method = strtok((char *)method, " ");
	endpoint = strtok(NULL, " ");
	while (endpoint && endpoint[0] != '/')
		endpoint = strtok(NULL, " ");
	dprintf(fd, \
			"%02d-%02d-%02d %02d:%02d:%02d %s %-7s %s %s\n", \
			tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, \
			tm.tm_hour, tm.tm_min, tm.tm_sec, \
			status, \
			http_method, \
			HOST, \
			endpoint);
	close(fd);
}
