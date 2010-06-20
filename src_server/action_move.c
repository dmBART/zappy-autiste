/*
** move.c for zappy in /u/all/milbau_a/cu/zappy/src_server
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Tue Jun  1 11:24:02 2010 alexis milbault
** Last update Sun Jun 20 23:55:00 2010 alexandra ekra
*/

#include "../includes/server.h"

static void	move_on_x(t_desc *serv, t_play *player)
{
  if (player->dir == RIGHT)
    {
      if ((player->x + 1) == serv->x)
	player->x = 0;
      else
	player->x++;
    }
  else
    {
      if (player->x == 0)
	player->x = serv->x - 1;
      else
	player->x--;
    }
}

static void	move_on_y(t_desc *serv, t_play *player)
{
  if (player->dir == UP)
    {
      if (player->y == 0)
	player->y = serv->y - 1;
      else
	player->y--;
    }
  else
    {
      if ((player->y + 1) == serv->y)
	player->y = 0;
      else
	player->y++;
    }
}

void	move_forward(t_desc *serv, t_play *player, t_env *e, char **cmd)
{
  int	cs;

  if (cmd[0] && e->team)
    {
      if ((player->dir == RIGHT) || (player->dir == LEFT))
	move_on_x(serv, player);
      else
	move_on_y(serv, player);
      write(player->cs, "ok\n", 3);
      if (e->graph_cs != -1 && FD_ISSET(e->graph_cs, &e->wrtefs))
	send_new_pos(player, e);
    }
}

void	turn_right(t_desc *serv, t_play *player, t_env *e, char **cmd)
{
  if (serv->map && cmd[0] && e->team)
    {
      if (player->dir == RIGHT)
	player->dir = DOWN;
      else if (player->dir == LEFT)
	player->dir = UP;
      else if (player->dir == UP)
	player->dir = RIGHT;
      else
	player->dir = LEFT;
      write(player->cs, "ok\n", 3);
      if (e->graph_cs != -1 && FD_ISSET(e->graph_cs, &e->wrtefs))
	send_new_pos(player, e);
    }
}

void	turn_left(t_desc *serv, t_play *player, t_env *e, char **cmd)
{
  if (serv->map && cmd[0] && e->team)
    {
      if (player->dir == RIGHT)
	player->dir = UP;
      else if (player->dir == LEFT)
	player->dir = DOWN;
      else if (player->dir == UP)
	player->dir = LEFT;
      else
	player->dir = RIGHT;
      write(player->cs, "ok\n", 3);
      if (e->graph_cs != -1 && FD_ISSET(e->graph_cs, &e->wrtefs))
	send_new_pos(player, e);
    }
}
