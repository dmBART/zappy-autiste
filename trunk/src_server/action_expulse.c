/*
** action_expulse.c for zappy in /u/all/milbau_a/cu/zappy
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Fri Jun 18 13:48:22 2010 alexis milbault
** Last update Sun Jun 20 17:30:41 2010 alexis milbault
*/

#include "../includes/server.h"

void	exp_on_right(t_desc *serv, t_play *player)
{
  if ((player->x + 1) == serv->x)
    player->x = 0;
  else
    player->x++;
  if (player->dir == RIGHT)
    add_sto_buffer(serv, "deplacement 5\n");
  if (player->dir == LEFT)
    add_sto_buffer(serv, "deplacement 1\n");
  if (player->dir == UP)
    add_sto_buffer(serv, "deplacement 3\n");
  if (player->dir == DOWN)
    add_sto_buffer(serv, "deplacement 7\n");
}

void	exp_on_left(t_desc *serv, t_play *player)
{
  if (player->x == 0)
    player->x = serv->x - 1;
  else
    player->x--;
  if (player->dir == RIGHT)
    add_sto_buffer(serv, "deplacement 1\n");
  if (player->dir == LEFT)
    add_sto_buffer(serv, "deplacement 5\n");
  if (player->dir == UP)
    add_sto_buffer(serv, "deplacement 7\n");
  if (player->dir == DOWN)
    add_sto_buffer(serv, "deplacement 3\n");
}

void	exp_on_up(t_desc *serv, t_play *player)
{
  if (player->y == 0)
    player->y = serv->y - 1;
  else
    player->y--;
  if (player->dir == RIGHT)
    add_sto_buffer(serv, "deplacement 7\n");
  if (player->dir == LEFT)
    add_sto_buffer(serv, "deplacement 3\n");
  if (player->dir == UP)
    add_sto_buffer(serv, "deplacement 5\n");
  if (player->dir == DOWN)
    add_sto_buffer(serv, "deplacement 1\n");
}

void	exp_on_down(t_desc *serv, t_play *player)
{
  if ((player->y + 1) == serv->y)
    player->y = 0;
  else
    player->y++;
  if (player->dir == RIGHT)
    add_sto_buffer(serv, "deplacement 3\n");
  if (player->dir == LEFT)
    add_sto_buffer(serv, "deplacement 7\n");
  if (player->dir == UP)
    add_sto_buffer(serv, "deplacement 1\n");
  if (player->dir == DOWN)
    add_sto_buffer(serv, "deplacement 5\n");
}

void	exp_player(t_desc *serv, t_play *cur, t_play *player)
{
  if ((cur->x == player->x) && (cur->y == player->y))
    {
      if (cur->dir == RIGHT)
	exp_on_right(serv, player);
      if (cur->dir == LEFT)
	exp_on_left(serv, player);
      if (cur->dir == UP)
	exp_on_up(serv, player);
      if (cur->dir == DOWN)
	exp_on_down(serv, player);
      write_to_client(serv, player->cs);
    }
}

void	expulse_players(t_desc *serv, t_play *cur, t_play *players)
{
  int	i;

  i = 0;
  while (i < MAX_FD)
    {
      if (players[i].type != FD_FREE && players[i].cs != cur->cs)
	exp_player(serv, cur, &players[i]);
      i++;
    }
}

void	expulse(t_desc *serv, t_play *player, t_env *e, char **cmd)
{
  if (cmd[0] && e->team)
    {
      if ((get_players_on_map(serv->players, player->x, player->y) - 1) > 0)
	{
	  expulse_players(serv, player, serv->players);
	  add_sto_buffer(serv, "ok\n");
	}
      else
	add_sto_buffer(serv, "ko\n");
      write_to_client(serv, player->cs);
    }
}
