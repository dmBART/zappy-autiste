/*
** graph_commands_cases.c for zappy in /u/all/ekra_a/cu/rendu/c/zappy-autiste/src_server
** 
** Made by alexandra ekra
** Login   <ekra_a@epitech.net>
** 
** Started on  Sun Jun 20 16:06:00 2010 alexandra ekra
** Last update Mon Jun 21 00:51:09 2010 alexandra ekra
*/

#include "../includes/server.h"

void	mct(t_desc *serv, t_play *players, t_env *e, char **cmd)
{
  if (cmd[1])
    write(players[e->i].cs, "sbp\n", 4);
  else
    send_cases_content(serv, players, e);
}

void	bct(t_desc *serv, t_play *players, t_env *e, char **cmd)
{
  int	x;
  int	y;

  if (!cmd[1] || !cmd[2] || cmd[3] || check_is_num(cmd[1]) == -1 
      || check_is_num(cmd[2]) == -1)
    write(players[e->i].cs, "sbp\n", 4);
  else
    {
      x = my_getnbr(cmd[1]);
      y = my_getnbr(cmd[2]);
      write(players[e->i].cs, "bct ", 4);
      my_putnbr_fd(players[e->i].cs, x);
      write(players[e->i].cs, " ", 1);
      my_putnbr_fd(players[e->i].cs, y);
      write(players[e->i].cs, " ", 1);
      if (aff_ressources(serv, e, x, y) == 0)
	aff_empty_cases(players[e->i].cs);
      write(players[e->i].cs, "\n", 1);
    }
}
