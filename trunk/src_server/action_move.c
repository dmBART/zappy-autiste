/*
** move.c for zappy in /u/all/milbau_a/cu/zappy/src_server
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Tue Jun  1 11:24:02 2010 alexis milbault
** Last update Tue Jun  1 12:05:22 2010 alexis milbault
*/

#include "../includes/server.h"

static void	move_on_x(t_desc *serv, t_play *player)
{
  if (play->dir == RIGHT)
    {
      if ((play->x + 1) == (serv->x - 1))
	play->x = 0;
      else
	play->x++;
    }
  else
    {
      if (play->x == 0)
	play->x = serv->x - 1;
      else
	play->x--;
    }
}

static void	move_on_y(t_desc *serv, t_play *player)
{
  if (play->dir == UP)
    {
      if (play->y == 0)
	play->y = serv->y - 1;
      else
	play->y--;
    }
  else
    {
      if ((play->y + 1) == (serv->y - 1))
	play->y = 0;
      else
	play->y++;
    }
}

void	move_forward(t_desc *serv, t_play *player)
{
  if ((play->dir == RIGHT) || (play->dir == LEFT))
    move_on_x(serv, player);
  else
    move_on_y(serv, player);
}

void	turn_right(t_desc *serv, t_play *player)
{
  if (serv->map)
    {
      if (play->dir == RIGHT)
	play->dir == DOWN;
      else if (play->dir == LEFT)
	play->dir == UP;
      else if (play->dir == UP)
	play->dir == LEFT;
      else
	play->dir = RIGHT;
    }
}

void	turn_left(t_desc *serv, t_play *player)
{
  if (serv->map)
    {
      if (play->dir == RIGHT)
	play->dir == UP;
      else if (play->dir == LEFT)
	play->dir == DOWN;
      else if (play->dir == UP)
	play->dir == RIGHT;
      else
	play->dir = LEFT;
    }
}
