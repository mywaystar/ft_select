/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:24:29 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/21 19:18:48 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <libft.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>

# define UNUSED(x) (void)(x)
# define TOP ((buf[0] == 27 && buf[1] == 91 && buf[2] == 65))
# define BOTTOM ((buf[0] == 27 && buf[1] == 91 && buf[2] == 66))
# define RIGHT ((buf[0] == 27 && buf[1] == 91 && buf[2] == 67))
# define LEFT ((buf[0] == 27 && buf[1] == 91 && buf[2] == 68))
# define SPACE ((buf[0] == 32 && buf[1] == 0 && buf[2] == 0))
# define BACK_SPACE ((buf[0] == 127 && buf[1] == 0 && buf[2] == 0))
# define DELETE ((buf[0] == 27 && buf[1] == 91 && buf[2] == 51))
# define ENTER ((buf[0] == 10 && buf[1] == 0 && buf[2] == 0))
# define EXIT ((buf[0] == 27 && buf[1] == 0 && buf[2] == 0))
# define COLS (ft_lstcount(s->list) / s->win.ws_row)

typedef struct termios	t_termios;
typedef struct winsize	t_winsize;

typedef struct	s_selector
{
	char		*str;
	int			is_selected;
	int			y;
}				t_selector;

typedef struct	s_select
{
	t_list		*list;
	t_termios	term;
	t_winsize	win;
	size_t		max_len;
	int			cursor_index;
	int			cursor_x;
	int			cursor_y;
	int			cols;
	int			tty;
	char		*term_name;
}				t_select;

t_select		*ft_select_recover(void);
int				tputs_putchar(int c);
void			ft_init_max_len(t_select *select);
void			ft_select_init_select(t_select *select, int ac, char **av);
int				ft_select_init_termcaps(t_select *select);
int				ft_select_init_window(t_select *select);
void			ft_select_print_selected(t_select *select, t_list *list);
void			ft_select_print(t_select *select, t_list *list);
void			ft_select_event(int i);
void			ft_select_free_selector(void *content, size_t size);
void			ft_select_free_env(void);
int				ft_select_keyboard(t_select *select);
int				ft_select_reset(t_select *select);
void			ft_select_errors_usage(void);
void			ft_select_events_exit(int i);
void			ft_select_events_go_background(int i);
void			ft_select_events_go_foreground(int i);
void			ft_select_events_resize(int i);
int				ft_select_get_max_words_by_page(void);
int				ft_select_get_pages(void);
int				ft_selected_get_page_offset(void);

#endif
