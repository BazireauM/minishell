/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbazirea <mbazirea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:46:49 by mbazirea          #+#    #+#             */
/*   Updated: 2023/08/16 12:34:01 by mbazirea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_list_quote(t_list **lst, char c, int *i, char *str);
int	search_next_stop(char *str);
int search_quote(char c, char *str);
void	add_list_not_quote(t_list **lst, int *i, char *str);
t_list *lexer(char *str);

int	search_quote(char c, char *str)
{
	int i;

	i = 0;
	i++;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	add_list_quote(t_list **lst, char c, int *i, char *str)
{
	int x;
	*i += 1;
	t_list *list;
	char *s;
	s = NULL;

	if (str[*i] == str[*i + 1])
	{
		s = malloc(sizeof(char) * 3);
		s[0] = c;
		s[1] = c;
		s[2] = '\0';
		*i += 2;
		return ;
	}
	if (search_quote(c, &str[*i]) !=  -1)
	{
		x = 0;
		s = malloc(sizeof(char) * (search_quote(c, &str[*i]) + 3));
		s[x] = c;
		x++;
		while (str[*i] != c && str[*i])
		{
			s[x] = str[*i];
			*i += 1;
			x++;
		}
		*i += 1;
		s[x] = c;
		s[x + 1] = '\0';
	}
	else
	{
		*i -= 1;
		add_list_not_quote(lst, i, str);
		return ;
	}
	list = ft_lstnew(s);
	ft_lstadd_back(lst, list);
}

int	search_next_stop(char *str)
{
	int i;

	i = 0;
	while (str[i] != ' ' && str[i] && str[i] != '|' && str[i] != '>' && str[i] != '<')
	{
		if (str[i] == '\'' && search_quote('\'', &str[i]) != -1)
			return (i);
		else if (str[i] == '\"' && search_quote('\"', &str[i]) != -1)
			return (i);
		i++;
	}
	return (i);
}

void	add_list_not_quote(t_list **lst, int *i, char *str)
{
	int x;
	int y;
	t_list *list;
	char *s;

	s = malloc(sizeof(char) * search_next_stop(&str[*i]));
	x = search_next_stop(&str[*i]);
	y = 0;
	while (y < x && str[*i])
	{
		s[y] = str[*i];
		y++;
		*i += 1;
	}
	s[y] = '\0';
	list = ft_lstnew(s);
	ft_lstadd_back(lst, list);
}

void	add_list_token(char *s, int *i, t_list **lst)
{
	t_list *list;

	*i += (int)ft_strlen(s);
	list = ft_lstnew(ft_strdup(s));
	ft_lstadd_back(lst, list);
}

t_list *lexer(char *str)
{
    int 	i;
    t_list	*lst;
	//t_list *list;

    lst = NULL;
    i = 0;
	while (str[i] != '\0')
    { 
		while (str[i] == ' ')
            i++;
        if (str[i] == '\"' && str[i])
		{
			add_list_quote(&lst, '\"', &i, str);
			/*
			if (str[i + 1] && str[i + 1] == '\"')
			{
				i += 1;
				list = ft_lstnew("\"\"");
				ft_lstadd_back(&lst, list);
			}
			else
			{
				add_list_quote(&lst, '\"', &i, str);
			}*/
		}
		else if (str[i] == '\'' && str[i])
			add_list_quote(&lst, '\'', &i, str);
		else if (str[i] == '|' && str[i])
			add_list_token("|", &i, &lst);
		else if (str[i] == '>' && str[i] && !(str[i + 1] == '>' && str[i + 1]))
			add_list_token(">", &i, &lst);
		else if (str[i] == '>' && str[i + 1] == '>' && str[i + 1] && str[i])
			add_list_token(">>", &i, &lst);
		else if (str[i] == '<' && str[i] && !(str[i + 1] == '<' && str[i + 1]))
			add_list_token("<", &i, &lst);
		else if (str[i] == '<' && str[i + 1] == '<' && str[i + 1] && str[i])
			add_list_token("<<", &i, &lst);
		else if  (str[i] != ' ' && str[i])
			add_list_not_quote(&lst, &i, str);

	}
	return (lst);
}
