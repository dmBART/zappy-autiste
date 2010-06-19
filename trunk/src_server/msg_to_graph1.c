/*
** send_to_graph.c for serveur in /u/all/ekra_a/cu/rendu/c/zappy-autiste/src_server
** 
** Made by alexandra ekra
** Login   <ekra_a@epitech.net>
** 
** Started on  Thu Jun 17 02:58:36 2010 alexandra ekra
** Last update Sat Jun 19 13:00:08 2010 alexandra ekra
*/

#include <unistd.h>
#include "../includes/server.h"

void	aff_inv(int cs, int *inv)
{
  int	i;

  i = 0;
  while (i < 7)
    {
      my_putnbr_fd(cs, inv[i]);
      if (i < 7)
	write(cs, " ", 1);
      i++;
    }
}

void	send_player_inv(t_desc *serv, t_env *e, int n)
{
  int	i;

  i = 0;
  while (i < MAX_FD)
    {
      if (serv->players[i].cs == n)
	{
	  write(serv->players[e->i].cs, "pin #", 5);
	  my_putnbr_fd(serv->players[e->i].cs, n);
	  write(serv->players[e->i].cs, " ", 1);
	  my_putnbr_fd(serv->players[e->i].cs, serv->players[i].x);
	  write(serv->players[e->i].cs, " ", 1);
	  my_putnbr_fd(serv->players[e->i].cs, serv->players[i].y);
	  write(serv->players[e->i].cs, " ", 1);
	  aff_inv(serv->players[e->i].cs, serv->players[i].inv);
	  write(serv->players[e->i].cs, "\n", 1);
	}
      i++;
    }
}

void	send_player_level(t_desc *serv, t_env *e, int n)
{
  int	i;

  i = 0;
  while (i < MAX_FD)
    {
      if (serv->players[i].cs == n)
	{
	  write(serv->players[e->i].cs, "plv #", 5);
	  my_putnbr_fd(serv->players[e->i].cs, n);
	  write(serv->players[e->i].cs, " ", 1);
	  my_putnbr_fd(serv->players[e->i].cs, serv->players[i].lvl);
	  write(serv->players[e->i].cs, "\n", 1);
	}
      i++;
    }
}

void	send_player_position(t_desc *serv, t_env *e, int n)
{
  int	i;

  i = 0;
  while (i < MAX_FD)
    {
      if (serv->players[i].cs == n)
	{
	  write(serv->players[e->i].cs, "ppo #", 5);
	  my_putnbr_fd(serv->players[e->i].cs, n);
	  write(serv->players[e->i].cs, " ", 1);
	  my_putnbr_fd(serv->players[e->i].cs, serv->players[i].x);
	  write(serv->players[e->i].cs, " ", 1);
	  my_putnbr_fd(serv->players[e->i].cs, serv->players[i].y);
	  write(serv->players[e->i].cs, " ", 1);
	  my_putnbr_fd(serv->players[e->i].cs, serv->players[i].dir);
	  write(serv->players[e->i].cs, "\n", 1);
	}
      i++;
    }
}

void	send_map_size(t_desc *serv, t_play *players, t_env *e)
{
  write(players[e->i].cs, "msz ", 4);
  my_putnbr_fd(players[e->i].cs, serv->x);
  write(players[e->i].cs, " ", 1);
  my_putnbr_fd(players[e->i].cs, serv->y);
  write(players[e->i].cs, "\n", 1);
}

void	send_time_unit(t_desc *serv, t_play *players, t_env *e)
{
  if (!gettimeofday(&e->tv, NULL))
    {
      write(players[e->i].cs, "sgt ", 4);
      my_putnbr_fd(players[e->i].cs, e->tv.tv_sec);
      write(players[e->i].cs, "\n", 1);
    }
}

int	aff_ressources(t_desc *serv, t_env *e, int x, int y)
{
  int	f;
  t_map	*tmp;

  f = 0;
  tmp = serv->map;
  while (tmp)
    {
      if (tmp->x == x && tmp->y == y)
	{
	  while (f < 7)
	    {
	      my_putnbr_fd(serv->players[e->i].cs, tmp->res[f]);
	      f++;
	      if (f < 7)
		write(serv->players[e->i].cs, " ", 1);
	    }
	  break;
	}
      tmp = tmp->next;
    }
  return (f);
}

void	aff_empty_cases(t_play *players, t_env *e)
{
  int	f;

  f = 0;
  while (f < 7)
    {
      my_putnbr_fd(players[e->i].cs, 0);
      f++;
      if (f < 7)
	write(players[e->i].cs, " ", 1);
    }
}

void	send_cases_content(t_desc *serv, t_play *players, t_env *e)
{
  int	x;
  int	y;
  int	f;

  x = 0;
  while (x < serv->x)
    {
      y = 0;
      while (y < serv->y)
	{
	  write(players[e->i].cs, "bct ", 4);
	  my_putnbr_fd(players[e->i].cs, x);
	  write(players[e->i].cs, " ", 1);
	  my_putnbr_fd(players[e->i].cs, y);
	  write(players[e->i].cs, " ", 1);
	  if ((f = aff_ressources(serv, e, x, y)) == 0)
	    aff_empty_cases(players, e);
	  write(players[e->i].cs, "\n", 1);
	  y++;
	}
      x++;
    }
}

void	send_teams_names(t_desc *serv, t_play *players, t_env *e)
{
  int	i;

  i = 0;
  while (serv->team[i])
    {
      write(players[e->i].cs, "tna ", 4);
      write(players[e->i].cs, serv->team[i], my_strlen(serv->team[i]));
      write(players[e->i].cs, "\n", 1);
      i++;
    }
}

void	graphic_write(t_desc *serv, t_play *players, t_env *e)
{
  my_putstr("Graphic client connected.\nSending informations on the map...\n");
  send_map_size(serv, players, e);
  send_time_unit(serv, players, e);
  send_cases_content(serv, players, e);
  send_teams_names(serv, players, e);
  send_player_position(serv, e, 4);
  send_player_level(serv, e, 4);
  send_player_inv(serv, e, 4);
  my_putstr("Informations sent to graphic client.\n");
}
