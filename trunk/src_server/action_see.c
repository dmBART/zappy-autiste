/*
** object_action.c for zappy in /u/all/milbau_a/cu/zappy/src_server
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Tue Jun  1 12:05:51 2010 alexis milbault
** Last update Sun Jun 20 22:39:57 2010 alexandra ekra
*/

#include "../includes/server.h"

int	get_players_on_map(t_play *players, int x, int y)
{
  int	i;
  int	count;

  i = 0;
  count = 0;
  while (players[i].team != NULL)
    {
      if ((players[i].x == x) && (players[i].y == y))
	count++;
      i++;
    }
  return (count);
}

static void	aff_player_on_case(t_play *players, t_play *cur, int x, int y)
{
  int	i;
  int	flag;

  flag = 0;
  i = get_players_on_map(players, x, y) + 1;
  while (--i > 0)
    {
      if (flag == 1)
	write(cur->cs, " ", 1);
      write(cur->cs, "joueur", 6);
      flag = 1;
    }
}

static void	aff_ressources_on_case(t_map *map, t_play *cur, int x, int y)
{
  t_map	*tmp;
  int	i;
  int	j;

  tmp = map;
  i = -1;
  while (tmp)
    {
      if ((tmp->x == x) && (tmp->y == y))
	while (++i < 7)
	  {
	    j = tmp->res[i] + 1;
	    while (--j > 0)
	      {
		write(cur->cs, " ", 1);
		write(cur->cs, (char *)get_ressource_name(i), my_strlen(get_ressource_name(i)));
	      }
	  }
      tmp = tmp->next;
    }
}

static void	aff_case(t_desc *serv, t_play *cur, int x, int y, int count)
{
  if (count == 0)
    write(cur->cs, "{", 1);
  aff_player_on_case(serv->players, cur, x, y);
  aff_ressources_on_case(serv->map, cur, x, y);
}

static void	see_on_right(t_desc *serv, t_play *player)
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
	  aff_case(serv, player, x, y, count);
	  if ((count == player->lvl) && ((count2 + 1) == check))
	    write(player->cs, "}\n", 2);
	  else
	    write(player->cs, ",", 1);
	  y = (y + 1) % serv->y;
	}
      x = (x + 1) % serv->x;
      check += 2;
      if (--dep < 0)
	dep = serv->y - 1;
    }
}

static void	see_on_left(t_desc *serv, t_play *player)
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
	  aff_case(serv, player, x, y, count);
	  if ((count == player->lvl) && ((count2 + 1) == check))
	    write(player->cs, "}\n", 2);
	  else
	    write(player->cs, ",", 1);
	  if (--y < 0)
	    y = serv->y - 1;
	}
      if (--x < 0)
	x = serv->x - 1;
      check += 2;
      dep = (dep + 1) % serv->y;
    }
}

static void	see_on_up(t_desc *serv, t_play *player)
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
	  aff_case(serv, player, x, y, count);
	  if ((count == player->lvl) && ((count2 + 1) == check))
	    write(player->cs, "}\n", 2);
	  else
	    write(player->cs, ",", 1);
	  x = (x + 1) % serv->x;
	}
      if (--y < 0)
	y = serv->y - 1;
      check += 2;
      if (--dep < 0)
	dep = serv->x - 1;
    }
}

static void	see_on_down(t_desc *serv, t_play *player)
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
	  aff_case(serv, player, x, y, count);
	  if ((count == player->lvl) && ((count2 + 1) == check))
	    write(player->cs, "}\n", 2);
	  else
	    write(player->cs, ",", 1);
	  if (--x < 0)
	    x = serv->x - 1;
	}
      y = (y + 1) % serv->y;
      check += 2;
      dep = (dep + 1) % serv->x;
    }
}

void	see(t_desc *serv, t_play *player, t_env *e, char **cmd)
{
  if (cmd[0] && e->team)
  {
    if (player->dir == RIGHT)
      see_on_right(serv, player);
    if (player->dir == LEFT)
      see_on_left(serv, player);
    if (player->dir == UP)
      see_on_up(serv, player);
    if (player->dir == DOWN)
      see_on_down(serv, player);
    write(player->cs, "ok\n", 3);
  }
}
