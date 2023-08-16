/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbazirea <mbazirea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:47:11 by mbazirea          #+#    #+#             */
/*   Updated: 2023/08/16 11:05:05 by mbazirea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list *lexer(char *str);
int i = 1;

void ctrl_c_d_back_slash(int sig)
{
	if (sig == SIGINT)
		i = 0;
	else if (sig == EOF)
		i = 0;
	else if (sig == SIGQUIT)
		i = 0;
}

int	main(void)
{
	// // Include test
	// readline(NULL);
	// rl_on_new_line();
	// rl_redisplay();
	// clear_history();
	// add_history(NULL);
	// rl_replace_line();
	t_list *lst;

	char    *s;
	char	*save_file_path;

	// Initialization
	s = malloc(sizeof(char) * 500);
	signal(SIGINT ,ctrl_c_d_back_slash);

	save_file_path = ft_strjoin(getenv("HOME"), "/.minishell_history");
	restore_history(save_file_path);

	// Main loop
	while (i)
	{
		s = readline("$> ");
		save_command(s, save_file_path);
		lst =  lexer(s);
		// parser()
		// exec()
		//printf("%s\n", s);
		printf("%s\n",lst->content);
		while (lst->next)
		{	
			lst = lst->next;
			printf("%s\n",lst->content);
		}
	}

	// Cleanup
	free(save_file_path);
	return (0);
}
