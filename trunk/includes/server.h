/*
** server.h for zappy in /u/all/milbau_a/cu/rendu/c/zappy
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Sat May 22 03:27:51 2010 alexis milbault
** Last update Wed May 26 16:56:21 2010 aime-bijou iniongo
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

# define MAX_FD	30;

typedef struct	s_desc
{
  int		x;
  int		y;
  int		t;
  int		port;
  int		nb_sock;
  char		**team;
  char		**map;
}		t_desc;

typedef struct	s_play
{
  int		x;
  int		y;
  int		lvl;
  int		dir;
  int		life;
  char		*team;
  char		**inv;
}		t_play;

typedef	struct	s_env
{
  int		port;
}		t_env;

/*
**----------> xfunc.c  <----------
*/
int	xsocket(int domain, int type, int protocol);
int	xlisten(int s, int backlog);
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

void	print_desc(t_desc *serv);

#endif /*_SERVER_H_*/
