/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void	del_selector(void *elem, size_t content)
{
	t_selector	*selector;
	selector = ((t_list *)elem)->content;
	if(selector->str)
		free(selector->str);
	free(elem);
	content = 0;
}

int		tputs_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

void	ft_select_event(int i)
{
	if (i == SIGWINCH)
		ft_select_events_resize(i);
	else if (i == SIGTSTP)
		ft_select_events_go_background(i);
	else if (i == SIGCONT)
		ft_select_events_go_foreground(i);
	else if (i == SIGINT)
		ft_select_events_exit(i);
	else if (i == SIGQUIT)
		ft_select_events_exit(i);
}

void	ft_select_print(t_list *list)
{
	t_list			*cur;
	t_selector	*selector;
	t_select		*select;
	int		y;
	int		x;

	y = 1;
	x = 0;
	select = ft_select_recover();
	tputs(tgetstr("cl", NULL), 0, tputs_putchar);
	tputs(tgetstr("ho", NULL), 0, tputs_putchar);
	cur = list;
	while (cur)
	{
		selector = cur->content;
		ft_putstr(selector->str);
		if (y == select->win.ws_row)
		{
			y = 0;
			x += select->max_len + 2;
		}
		tputs(tgoto(tgetstr("cm", NULL), x, y), 1, tputs_putchar);
		y++;
		cur = cur->next;
	}
}

int		main(int ac, char **av)
{
	t_select	*select;

	select = ft_select_recover();
	if (ac == 1)
	{
		ft_select_errors_usage();
		return (1);
	}
	signal(SIGWINCH, ft_select_event);
	signal(SIGTSTP, ft_select_event);
	signal(SIGCONT, ft_select_event);
	signal(SIGINT, ft_select_event);
	signal(SIGQUIT, ft_select_event);
	ft_select_init_select(select, ac, av);
	ft_select_init_termcaps(select);
	ft_select_init_window(select);
	//ft_lstiter(select.list, &show_str);
	while (1);
	return (0);
}