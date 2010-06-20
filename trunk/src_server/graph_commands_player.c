/*
** graph_commands_player.c for zappy in /u/all/ekra_a/cu/rendu/c/zappy-autiste/src_server
** 
** Made by alexandra ekra
** Login   <ekra_a@epitech.net>
** 
** Started on  Sun Jun 20 15:57:58 2010 alexandra ekra
** Last update Sun Jun 20 16:05:09 2010 alexandra ekra
*/

#include "../includes/server.h"

void	tna(t_desc *serv, t_play *players, t_env *e, char **cmd)
{
  if (cmd[1])
    write(players[e->i].cs, "sbp\n", 4);
  else
    send_teams_names(serv, players, e);
}

void	pin(t_desc *serv, t_play *players, t_env *e, char **cmd)
{
  int	n;

  if (!cmd[1] || cmd[2] || check_is_num(&cmd[1][1]) == -1)
    write(players[e->i].cs, "sbp\n", 4);
  else
    {
      n = my_getnbr(&cmd[1][1]);
      send_player_inv(serv, e, n);
    }
}

void	plv(t_desc *serv, t_play *players, t_env *e, char **cmd)
{
  int	n;

  if (!cmd[1] || cmd[2] || check_is_num(&cmd[1][1]) == -1)
    write(players[e->i].cs, "sbp\n", 4);
  else
    {
      n = my_getnbr(&cmd[1][1]);
      send_player_level(serv, e, n);
    }
}

void	ppo(t_desc *serv, t_play *players, t_env *e, char **cmd)
{
  int	n;

  if (!cmd[1] || cmd[2] || check_is_num(&cmd[1][1]) == -1)
    write(players[e->i].cs, "sbp\n", 4);
  else
    {
      n = my_getnbr(&cmd[1][1]);
      send_player_position(serv, e, n);
    }
}
