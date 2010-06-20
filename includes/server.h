/*
** server.h for zappy in /u/all/milbau_a/cu/rendu/c/zappy
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Sat May 22 03:27:51 2010 alexis milbault
<<<<<<< .mine
** Last update Sun Jun 20 22:42:56 2010 aime-bijou iniongo
=======
** Last update Sun Jun 20 16:50:41 2010 alexandra ekra
>>>>>>> .r61
** Last update Thu Jun  3 15:04:16 2010 alexis milbault
*/


#ifndef _SERVER_H_
#define _SERVER_H_

#define DEFAULT_PORT 4242
#define DEFAULT_SIZE 20
#define DEFAULT_PLAYER 2
#define DEFAULT_TIME 100
#define DEFAULT_TEAM1 "Team 1"
#define DEFAULT_TEAM2 "Team 2"
#define MAX_FD		40
#define MAX_IN		200
#define MAX_GHOST	250
#define MAX_NB(a, b)	(a > b ? a : b)
#define MIN_NB(a, b)	(a < b ? a : b)

#include <sys/time.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

enum
{
  RIGHT,
  LEFT,
  UP,
  DOWN,
  FD_CLIENT,
  FD_FREE,
  FD_GHOST,
  FD_GRAPHIC
};

typedef struct		s_timev
{
  int			d;
  int			cs;
  char			*action;
  struct timeval	t;
  struct timeval	t_new;
  struct timeval	t_old;
  struct s_timev	*next;
}			t_timev;

typedef struct	s_map
{
  int		x;
  int		y;
  int		res[7];
  struct s_map	*next;
}		t_map;

typedef struct	s_team
{
  int		place;
  int		fork;
  char		*name;
  struct s_team	*next;
}		t_team;

typedef struct	s_play
{
  int		x;
  int		y;
  int		cs;
  int		lvl;
  int		dir;
  int		life;
  int		state;
  int		begin;
  int		end;
  int		*inv;
  int		type;
  char		*team;
  char		*ip;
  char		*action;
}		t_play;

typedef struct	s_desc
{
  int		x;
  int		y;
  int		t;
  int		s;
  int		port;
  int		nb_sock;
  char		**team;
  t_map		*map;
  t_play	players[MAX_GHOST];
  t_timev	*tv;
}		t_desc;

typedef	struct		s_env
{
  int			i;
  int			t;
  int			end;
  int			cs;
  int			graph_cs;
  int			state;
  int			fd_max;
  t_team		*team;
  fd_set		readfs;
  fd_set		wrtefs;
  struct timeval	tv;
  struct timezone	ts;
}			t_env;

typedef struct		s_graph
{
  char			*com;
  void			(*f)();
}			t_graph;

/*
**----------> xfunc.c  <----------
*/
int	xsocket(int domain, int type, int protocol);
int	xlisten(int s, int backlog);
int	xselect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
	       struct timeval *timeout);
void	xbind(int s, struct sockaddr_in addr);
void	*xmalloc(size_t size);
void	*xrealloc(void *ptr, size_t size);
ssize_t	xread(int d, void *buf, size_t nbytes);
ssize_t xrecv(int s, void *buf, size_t len, int flags);

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
int	check_team_already_exist(char **argv, char **team, int i);

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
**----------> ghost_mode.c  <----------
*/
void	ghost_mode(t_timev *eve, t_play *player, t_env *e);
void	temp_life(t_play *player, t_env *e, t_desc *serv, t_timev t);


/*
**----------> client_state.c  <----------
*/
void	welcome_client(t_desc *serv, t_env *e, char *team_name);
void	client_write(t_desc *serv, t_env *e, int n);
void	manage_life(t_play *player, t_env *e, t_desc *serv, t_timev t);


/*
**----------> utils_2.c  <----------
*/
int	count_tab(char **tab);
char	**my_str_to_wordtab(char *str);
void	my_putchar_fd(int fd, char c);
void	my_putnbr_fd(int fd, int nbr);

/*
**----------> client_management.c  <----------
*/
void	add_players(t_desc *serv, t_env *e);
void	manage_client(t_desc *serv, t_env *e, t_timev t);
void	close_client(t_timev *eve, t_play *player, t_env *e);

void	init_client(t_play *player, int fd, char *ip, t_desc *serv);


/*
**----------> select_team.c  <----------
*/
int	place_in_the_team(t_team *team, char *team_name);
int	choose_a_team(t_desc *serv, t_play *players, char *buff, t_env *e);
int	take_a_team(t_play *player, char *team, t_env *e, t_team *myteam);
void	add_elem_in_team(t_desc *serv, t_team **team, int i);
void	return_place_on_team(t_play *player, t_team *team);

/*
**----------> gestion_timer.c  <----------
*/
void	manage_time_in_select(t_timev t, struct timeval *tv);
void	update_time_struct(t_timev *time, t_env *e);
t_timev	manage_time(t_desc *serv);

/*
**----------> elem_timer_timer.c  <----------
*/
void	del_elem_player(t_timev **eve, int fd, int size);
void	del_elem_to_queu(t_timev **time, t_timev t);
void	add_elem(t_timev **player, char *action, int id, t_env *e);

/*
**----------> Gestion map  <----------
*/
char	*get_ressource_name(int id);
void	init_map(t_desc *serv);
void	fill_map(t_map **map, int x, int y, int i);
int	get_ressource_id(char *res);
int	update_exist_case(t_map *map, int x, int y, int id);
int	take_ressource_on_map(t_map *map, int x, int y, int id);
int	get_players_on_map(t_play *players, int x, int y);

/*
**----------> Action Function  <----------
*/
void	see(t_desc *serv, t_play *player, t_env *e, char **cmd);
void	move_forward(t_desc *serv, t_play *player, t_env *e, char **cmd);
void	turn_right(t_desc *serv, t_play *player, t_env *e, char **cmd);
void	turn_left(t_desc *serv, t_play *player, t_env *e, char **cmd);
void	inventory(t_desc *serv, t_play *player, t_env *e, char **cmd);
void	take_object(t_desc *serv, t_play *player, t_env *e, char **cmd);
void	check_life(t_desc *serv, t_play *player, t_env *e, char **cmd);
void	drop_object(t_desc *serv, t_play *player, t_env *e, char **cmd);
void	manage_commande(t_desc *serv, t_play *player, t_env *e, char *cmd);
void	connect_nbr(t_desc *serv, t_play *player, t_env *e, char **cmd);
void	lvl_up(t_desc *serv, t_play *player, t_env *e, char **cmd);

/*
**----------> annexe.c  <----------
*/
void	manage_buff(t_play *player, char *buffer, int len);
int	count_elem_timer(t_timev *eve, int fd);

/*
**----------> print_func.c  <----------
*/
void	show_all_timer(t_timev *timer);
void	show_player_buffer(char **buffer);



void	print_desc(t_desc *serv);

/*
**----------> msg_to_graph1.c  <----------
*/
void	graphic_write(t_desc *serv, t_play *players, t_env *e);
void	send_teams_names(t_desc *serv, t_play *players, t_env *e);
void	send_time_unit(t_desc *serv, t_play *players, t_env *e);
void	send_map_size(t_desc *serv, t_play *players, t_env *e);

/*
**----------> send_cases_content.c  <----------
*/
void	send_cases_content(t_desc *serv, t_play *players, t_env *e);
void	aff_empty_cases(t_play *players, t_env *e);
int	aff_ressources(t_desc *serv, t_env *e, int x, int y);

/*
**----------> send_player_info.c  <----------
*/
void	send_player_position(t_desc *serv, t_env *e, int n);
void	send_player_level(t_desc *serv, t_env *e, int n);
void	send_player_inv(t_desc *serv, t_env *e, int n);

/*
**----------> graph_commands.c  <----------
*/
void	read_graph(t_desc *serv, t_play *players, t_env *e);
void	graph_command(t_desc *serv, t_play *players, t_env *e);
void	msz(t_desc *serv, t_play *players, t_env *e, char **cmd);
void	sgt(t_desc *serv, t_play *players, t_env *e, char **cmd);
void	sst(t_desc *serv, t_play *players, t_env *e, char **cmd);

/*
**----------> graph_commands_player.c  <----------
*/
void	ppo(t_desc *serv, t_play *players, t_env *e, char **cmd);
void	plv(t_desc *serv, t_play *players, t_env *e, char **cmd);
void	pin(t_desc *serv, t_play *players, t_env *e, char **cmd);
void	tna(t_desc *serv, t_play *players, t_env *e, char **cmd);

/*
**----------> graph_commands_cases.c  <----------
*/
void	bct(t_desc *serv, t_play *players, t_env *e, char **cmd);
void	mct(t_desc *serv, t_play *players, t_env *e, char **cmd);

#endif /*_SERVER_H_*/
