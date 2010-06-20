/*
** events_to_graph.c for zappy in /u/all/ekra_a/cu/rendu/c/zappy/src_server
** 
** Made by alexandra ekra
** Login   <ekra_a@epitech.net>
** 
** Started on  Sun Jun 20 22:55:03 2010 alexandra ekra
** Last update Mon Jun 21 00:50:26 2010 alexandra ekra
*/

#include "../includes/server.h"

void	send_new_pos(t_play *player, t_env *e)
{
  write(e->graph_cs, "ppo #", 5);
  my_putnbr_fd(e->graph_cs, player->n);
  write(e->graph_cs, " ", 1);
  my_putnbr_fd(e->graph_cs, player->x);
  write(e->graph_cs, " ", 1);
  my_putnbr_fd(e->graph_cs, player->y);
  write(e->graph_cs, " ", 1);
  my_putnbr_fd(e->graph_cs, player->dir);
  write(e->graph_cs, "\n", 1);
}

int	aff_case_res(t_desc *serv, t_env *e, int x, int y)
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
	      my_putnbr_fd(e->graph_cs, tmp->res[f]);
	      f++;
	      if (f < 7)
		write(e->graph_cs, " ", 1);
	    }
	  break;
	}
      tmp = tmp->next;
    }
  return (f);
}

void	send_pin_bct(t_desc *serv, t_play *player, t_env *e)
{
  write(e->graph_cs, "pin #", 5);
  my_putnbr_fd(e->graph_cs, player->n);
  write(e->graph_cs, " ", 1);
  my_putnbr_fd(e->graph_cs, player->x);
  write(e->graph_cs, " ", 1);
  my_putnbr_fd(e->graph_cs, player->y);
  write(e->graph_cs, " ", 1);
  aff_inv(e->graph_cs, player->inv);
  write(e->graph_cs, "\n", 1);
  write(e->graph_cs, "bct ", 4);
  my_putnbr_fd(e->graph_cs, player->x);
  write(e->graph_cs, " ", 1);
  my_putnbr_fd(e->graph_cs, player->y);
  write(e->graph_cs, " ", 1);
  if (aff_case_res(serv, e, player->x, player->y) == 0)
    aff_empty_cases(player->cs);
  write(e->graph_cs, "\n", 1);
}



void	graph_drop_objects(t_desc *serv, t_play *player, t_env *e, int id)
{
  write(e->graph_cs, "pdr #", 5);
  my_putnbr_fd(e->graph_cs, player->n);
  write(e->graph_cs, " ", 1);
  my_putnbr_fd(e->graph_cs, id);
  write(e->graph_cs, "\n", 1);
  send_pin_bct(serv, player, e);
}

void	graph_take_objects(t_desc *serv, t_play *player, t_env *e, int id)
{
 write(e->graph_cs, "pgt #", 5);
  my_putnbr_fd(e->graph_cs, player->n);
  write(e->graph_cs, " ", 1);
  my_putnbr_fd(e->graph_cs, id);
  write(e->graph_cs, "\n", 1);
  send_pin_bct(serv, player, e);
}
