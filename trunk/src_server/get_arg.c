/*
** get_arg.c for zappy in /u/all/milbau_a/cu/rendu/c/zappy
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Sat May 22 03:37:29 2010 alexis milbault
** Last update Mon May 24 22:15:35 2010 alexis milbault
*/

#include <stdio.h>
#include "../includes/server.h"

void	my_error_arg(char *str)
{
  fprintf(stderr, "%s\n\n", str);
  fprintf(stderr, "Usage : ./server\n\t-p [port]\n\t-x [map_width]");
  fprintf(stderr, "\n\t-y [map_hight]\n\t-n [name_team1 name_team2...]");
  fprintf(stderr, "\n\t-c [nb_player_per_team]\n\t-t [time_unit]\n");
  exit(EXIT_FAILURE);
}

int	get_arg_port(t_desc *serv, char **argv, int ac, int i)
{
  int	port;

  if ((i + 1 == ac) || (check_is_opt(argv[i + 1]) == 0))
    my_error_arg("Too few argument for the parameter -p.");
  if (serv->port != 0)
    my_error_arg("Multiple definition of the parameter -p.");
  if (check_is_num(argv[i + 1]) == 0)
    {
      port = my_getnbr(argv[i + 1]);
      if ((port > 1023) && (port <= 65535))
	serv->port = my_getnbr(argv[i + 1]);
      else
	my_error_arg("Argument for parameter -p must between 1023 and 65535");
    }
  else
    my_error_arg("Argument for parameter -p must be numeric.");
  return (i + 2);
}

int	get_arg_width(t_desc *serv, char **argv, int ac, int i)
{
  int	width;

  if ((i + 1 == ac) || (check_is_opt(argv[i + 1]) == 0))
    my_error_arg("Too few argument for the parameter -x.");
  if (serv->x != 0)
    my_error_arg("Multiple definition of the parameter -x.");
  if (check_is_num(argv[i + 1]) == 0)
    {
      if ((width = my_getnbr(argv[i + 1])) > 0)
	serv->x = width;
      else
	my_error_arg("Argument for parameter -x must be superior to 0.");
    }
  else
    my_error_arg("Argument for parameter -x must be numeric.");
  return (i + 2);
}

int	get_arg_hight(t_desc *serv, char **argv, int ac, int i)
{
  int	hight;

  if ((i + 1 == ac) || (check_is_opt(argv[i + 1]) == 0))
    my_error_arg("Too few argument for the parameter -y.");
  if (serv->y != 0)
    my_error_arg("Multiple definition of the parameter -y.");
  if (check_is_num(argv[i + 1]) == 0)
    {
      if ((hight = my_getnbr(argv[i + 1])) > 0)
	serv->y = hight;
      else
	my_error_arg("Argument for parameter -y must be superior to 0.");
    }
  else
    my_error_arg("Argument for parameter -y must be numeric.");
  return (i + 2);
}

void	fill_team_name(t_desc *serv, char **argv, int i, int j)
{
  int	a;

  a = 0;
  serv->team = xmalloc(sizeof(**serv->team) * (j - i + 1));
  while (a < j - i)
    serv->team[a++] = 0;
  a = 0;
  while (i < j)
    {
      if (check_team_already_exist(argv, serv->team, i, j) < 0)
	serv->team[a++] = argv[i++];
      else
	{
	  free(serv->team);
	  my_error_arg("Name of team must be different.");
	}
    }
  serv->team[a] = 0;
}

int	get_arg_teams_name(t_desc *serv, char **argv, int ac, int i)
{
  int	j;

  j = i + 1;
  if ((i + 1 == ac) || (check_is_opt(argv[i + 1]) == 0))
    my_error_arg("Too few argument for the parameter -n.");
  if (serv->team)
    my_error_arg("Multiple definition of the parameter -n.");
  while ((j < ac) && (check_is_opt(argv[j]) < 0))
    {
      if (check_is_printable(argv[j]) == 0)
	j++;
      else
	my_error_arg("Argument for parameter -n must be printable characters.");
    }
  if ((j - (i + 1)) > 1)
    fill_team_name(serv, argv, i + 1, j);
  else
    my_error_arg("Too few argument for parameter -n.");
  return (j);
}

int	get_arg_nb_player(t_desc *serv, char **argv, int ac, int i)
{
  int	nb;

  if ((i + 1 == ac) || (check_is_opt(argv[i + 1]) == 0))
    my_error_arg("Too few argument for the parameter -c.");
  if (serv->nb_sock != 0)
    my_error_arg("Multiple definition of the parameter -c.");
  if (check_is_num(argv[i + 1]) == 0)
    {
      if ((nb = my_getnbr(argv[i + 1])) > 0)
	serv->nb_sock = nb;
      else
	my_error_arg("Argument for parameter -c must be superior to 0.");
    }
  else
    my_error_arg("Argument for parameter -c must be numeric.");
  return (i + 2);
}

int	get_arg_time(t_desc *serv, char **argv, int ac, int i)
{
  int	nb;

  if ((i + 1 == ac) || (check_is_opt(argv[i + 1]) == 0))
    my_error_arg("Too few argument for the parameter -t.");
  if (serv->t != 0)
    my_error_arg("Multiple definition of the parameter -t.");
  if (check_is_num(argv[i + 1]) == 0)
    {
      if ((nb = my_getnbr(argv[i + 1])) > 0)
	serv->t = nb;
      else
	my_error_arg("Argument for parameter -t must be superior to 0.");
    }
  else
    my_error_arg("Argument for parameter -t must be numeric.");
  return (i + 2);
}
