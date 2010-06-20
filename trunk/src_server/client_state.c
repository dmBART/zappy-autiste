/*
** client_state.c for client_state in /u/all/iniong_a/cu/rendu/c/trunk/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Sat Jun 19 18:11:37 2010 aime-bijou iniongo
** Last update Sun Jun 20 12:49:25 2010 aime-bijou iniongo
*/

#include "../includes/server.h"

void		welcome_client(t_desc *serv, t_env *e, char *team_name)
{
  int		nbr;

  nbr = place_in_the_team(e->team, team_name);
  my_putnbr_fd(serv->players[e->i].cs, nbr);
  my_putchar_fd(serv->players[e->i].cs, '\n');
  my_putnbr_fd(serv->players[e->i].cs, serv->x);
  my_putchar_fd(serv->players[e->i].cs,' ');
  my_putnbr_fd(serv->players[e->i].cs, serv->y);
  my_putchar_fd(serv->players[e->i].cs,'\n');
}

void		client_write(t_desc *serv, t_env *e, int n)
{
  int		x;
  int		nbr;

  serv->players[e->i].begin = serv->players[e->i].end;
  e->t = serv->t;
  e->state = serv->players[e->i].state;
  x = (serv->players[e->i].end  % 100) - 1;
  e->end = serv->players[e->i].end;
  if (serv->players[e->i].team == NULL && n > 1)
    {
      if (choose_a_team(serv, serv->players, serv->players[e->i].action[0], e) == 0)
	{
	  welcome_client(serv, e, serv->players[e->i].action[0]);
	  add_elem(&serv->tv, "vie", serv->players[e->i].cs, e);
	  serv->players[e->i].state = 1;
	}
    }
  else
    {
      add_elem(&serv->tv, serv->players[e->i].action[x], serv->players[e->i].cs, e);
    }
}

void	manage_life(t_play *player, t_env *e, t_desc *serv, t_timev t)
{
  if (player->inv[0] > 0)
    {
      player->inv[0]--;
      e->end = 1;
      e->state  = 0;
      del_elem_to_queu(&serv->tv, t);
      add_elem(&serv->tv, "vie", player->cs, e);
    }
  else
    {
      del_elem_to_queu(&serv->tv, t);
      write(player->cs, "mort\n", 5);
      close_client(player, e);
    }
}
