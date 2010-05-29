/*
** server.h for zappy in /u/all/milbau_a/cu/rendu/c/zappy
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Sat May 22 03:27:51 2010 alexis milbault
** Last update Sat May 29 22:59:59 2010 aime-bijou iniongo
*/


#ifndef _SERVER_H_
#define _SERVER_H_

#define DEFAULT_PORT 4242
#define DEFAULT_SIZE 20
#define DEFAULT_PLAYER 2
#define DEFAULT_TIME 100
#define DEFAULT_TEAM1 "Team 1"
#define DEFAULT_TEAM2 "Team 2"

#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

# define MAX_FD		30
# define FD_FREE	0
# define FD_CLIENT	1
# define MAX_NB(a, b)	(a > b ? a : b)

typedef struct	s_desc
{
  int		x;
  int		y;
  int		t;
  int		s;
  int		port;
  int		nb_sock;
  char		**team;
  char		**map;
}		t_desc;

typedef struct		s_timev
{
  int			p;
  int			time;
  /*int			count;*/
  char			*action;
  struct s_timev	*next;
  struct s_timev	*prev;
}			t_timev;

typedef struct	s_play
{
  int		x;
  int		y;
  int		lvl;
  int		dir;
  int		life;
  int		cs;
  char		*team;
  char		*ip;
  char		**inv;
  char		type;
  t_timev	*t;
}		t_play;

typedef	struct	s_env
{
  int		cs;
  int		fd_max;
}		t_env;

/*
**----------> xfunc.c  <----------
*/
int	xsocket(int domain, int type, int protocol);
int	xlisten(int s, int backlog);
int	xselect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
	       struct timeval *timeout);
void	xbind(int s, struct sockaddr_in addr);
void	*xmalloc(size_t size);
ssize_t	xread(int d, void *buf, size_t nbytes);

/*
**----------> utils.c  <----------
*/
int	my_strlen(char *str);
int	my_strcmp(char *s1, char *s2);
int	my_getnbr(char *str);
void	my_putstr(char *str);

/*
**----------> check_func.c  <----------
*/
int	check_is_num(char *str);
int	check_is_printable(char *str);
int	check_team_already_exist(char **argv, char **team, int i, int j);

/*
**----------> get_param.c  <----------
*/
void	get_param(t_desc *serv, char **argv, int argc);
int	check_is_opt(char *str);


/*
**----------> get_arg.c  <----------
*/
int	get_arg_port(t_desc *serv, char **argv, int ac, int i);
int	get_arg_width(t_desc *serv, char **argv, int ac, int i);
int	get_arg_hight(t_desc *serv, char **argv, int ac, int i);
int	get_arg_teams_name(t_desc *serv, char **argv, int ac, int i);
int	get_arg_nb_player(t_desc *serv, char **argv, int ac, int i);
int	get_arg_time(t_desc *serv, char **argv, int ac, int i);

/*
**----------> do_server.c  <----------
*/
void	start_server(t_desc *serv);

/*
**----------> utils_2.c  <----------
*/
int	count_tab(char **tab);

/*
**----------> client_management.c  <----------
*/
void	add_players(int s, t_env *e, t_play *players);
void	manage_client(t_desc *serv, t_play *players, fd_set readfs);
void	close_client(t_play *player, int i);

/*
**----------> select_team.c  <----------
*/
void	choose_a_team(t_desc *serv, t_play *players, char *buff, int i);

/*
**----------> gestion_timer.c  <----------
*/
void	add_elem(t_timev **player, char *action);


void	print_desc(t_desc *serv);

#endif /*_SERVER_H_*/
