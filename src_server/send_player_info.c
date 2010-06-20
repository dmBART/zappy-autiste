/*
** send_player_info.c for zappy in /u/all/ekra_a/cu/rendu/c/zappy-autiste/src_server
** 
** Made by alexandra ekra
** Login   <ekra_a@epitech.net>
** 
** Started on  Sun Jun 20 15:48:42 2010 alexandra ekra
** Last update Sun Jun 20 15:51:26 2010 alexandra ekra
*/

#include "../includes/server.h"

void	aff_inv(int cs, int *inv)
{
  int	i;

  i = 0;
  while (i < 7)
    {
      my_putnbr_fd(cs, inv[i]);
      if (i < 7)
	write(cs, " ", 1);
      i++;
    }
}

void	send_player_inv(t_desc *serv, t_env *e, int n)
{
  int	i;

  i = 0;
  while (i < MAX_FD)
    {
      if (serv->players[i].cs == n)
	{
	  write(serv->players[e->i].cs, "pin #", 5);
	  my_putnbr_fd(serv->players[e->i].cs, n);
	  write(serv->players[e->i].cs, " ", 1);
	  my_putnbr_fd(serv->players[e->i].cs, serv->players[i].x);
	  write(serv->players[e->i].cs, " ", 1);
	  my_putnbr_fd(serv->players[e->i].cs, serv->players[i].y);
	  write(serv->players[e->i].cs, " ", 1);
	  aff_inv(serv->players[e->i].cs, serv->players[i].inv);
	  write(serv->players[e->i].cs, "\n", 1);
	}
      i++;
    }
}

void	send_player_level(t_desc *serv, t_env *e, int n)
{
  int	i;

  i = 0;
  while (i < MAX_FD)
    {
      if (serv->players[i].cs == n)
	{
	  write(serv->players[e->i].cs, "plv #", 5);
	  my_putnbr_fd(serv->players[e->i].cs, n);
	  write(serv->players[e->i].cs, " ", 1);
	  my_putnbr_fd(serv->players[e->i].cs, serv->players[i].lvl);
	  write(serv->players[e->i].cs, "\n", 1);
	}
      i++;
    }
}

void	send_player_position(t_desc *serv, t_env *e, int n)
{
  int	i;

  i = 0;
  while (i < MAX_FD)
    {
      if (serv->players[i].cs == n)
	{
	  write(serv->players[e->i].cs, "ppo #", 5);
	  my_putnbr_fd(serv->players[e->i].cs, n);
	  write(serv->players[e->i].cs, " ", 1);
	  my_putnbr_fd(serv->players[e->i].cs, serv->players[i].x);
	  write(serv->players[e->i].cs, " ", 1);
	  my_putnbr_fd(serv->players[e->i].cs, serv->players[i].y);
	  write(serv->players[e->i].cs, " ", 1);
	  my_putnbr_fd(serv->players[e->i].cs, serv->players[i].dir);
	  write(serv->players[e->i].cs, "\n", 1);
	}
      i++;
    }
}
