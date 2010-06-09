/*
** object_action.c for zappy in /u/all/milbau_a/cu/zappy/src_server
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Tue Jun  1 12:05:51 2010 alexis milbault
** Last update Wed Jun  2 15:06:55 2010 alexis milbault
*/

#include "../includes/server.h"

void	see_on_right(t_desc *serv, t_play *player)
{
  int	x;
  int	y;
  int	count;
  int	count2;
  int	dep;
  int	check;

  x = player->x;
  dep = player->y;
  count = -1;
  check = 1;
  while (++count <= player->lvl)
    {
      y = dep;
      count2 = -1;
      while (++count2 < check)
	{
	  /*recuperation du contenu de la case*/
	  y = (y + 1) % serv->y;
	}
      x = (x + 1) % serv->x;
      check += 2;
      if (dep-- < 0)
	dep = serv->y;
    }
}

void	see_on_left(t_desc *serv, t_play *player)
{
  int	x;
  int	y;
  int	count;
  int	count2;
  int	dep;
  int	check;

  x = player->x;
  dep = player->y;
  count = -1;
  check = 1;
  while (++count <= player->lvl)
    {
      y = dep;
      count2 = -1;
      while (++count2 < check)
	{
	  /*recuperation du contenu de la case*/
	  if (y-- < 0)
	    y = serv->y;
	}
      if (x-- < 0)
	x = serv->x
      check += 2;
      dep = (dep + 1) % serv->y;
    }
}

void	see_on_up(t_desc *serv, t_play *player)
{
  int	x;
  int	y;
  int	count;
  int	count2;
  int	dep;
  int	check;

  y = player->y;
  dep = player->x;
  count = -1;
  check = 1;
  while (++count <= player->lvl)
    {
      x = dep;
      count2 = -1;
      while (++count2 < check)
	{
	  /*recuperation du contenu de la case*/
	  x = (x + 1) % serv->x;
	}
      if (y-- < 0)
	y = serv->y
      check += 2;
      if (dep-- < 0)
	dep = serv->x;
    }
}

void	see_on_down(t_desc *serv, t_play *player)
{
  int	x;
  int	y;
  int	count;
  int	count2;
  int	dep;
  int	check;

  y = player->y;
  dep = player->x;
  count = -1;
  check = 1;
  while (++count <= player->lvl)
    {
      x = dep;
      count2 = -1;
      while (++count2 < check)
	{
	  /*recuperation du contenu de la case*/
	  if (x-- < 0)
	    x = serv->x;
	}
      y = (y + 1) % serv->y;
      check += 2;
      dep = (dep + 1) % serv->x;
    }
}

void	see(t_desc *serv, t_play *player)
{
  if (player->dir == RIGHT)
    see_on_right(serv, player);
  if (player->dir == LEFT)
    see_on_left(serv, player);
  if (player->dir == UP)
    see_on_up(serv, player);
  if (player->dir == DOWN)
    see_on_down(serv, player);
}
