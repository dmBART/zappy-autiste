/*
** send_cases_content.c for zappy in /u/all/ekra_a/cu/rendu/c/zappy-autiste/src_server
** 
** Made by alexandra ekra
** Login   <ekra_a@epitech.net>
** 
** Started on  Sun Jun 20 15:45:25 2010 alexandra ekra
** Last update Sun Jun 20 15:45:56 2010 alexandra ekra
*/

#include "../includes/server.h"

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
