/*
** send_to_graph.c for serveur in /u/all/ekra_a/cu/rendu/c/zappy-autiste/src_server
** 
** Made by alexandra ekra
** Login   <ekra_a@epitech.net>
** 
** Started on  Thu Jun 17 02:58:36 2010 alexandra ekra
** Last update Sun Jun 20 16:57:44 2010 alexandra ekra
*/

#include "../includes/server.h"

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
  my_putstr("Informations sent to graphic client.\n");
}
