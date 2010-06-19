/*
** client_management.c for serveur in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Fri May 28 00:49:11 2010 aime-bijou iniongo
** Last update Sat Jun 19 15:26:02 2010 aime-bijou iniongo
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include "../includes/server.h"

void		my_putchar(char c)
{
  write(1, &c, 1);
}

void		ghost_mode(t_play *player, t_env *e)
{
  close(player[e->i].cs);
  player[e->i].type = FD_GHOST;
  FD_CLR(player[e->i].cs, &e->readfs);
  FD_CLR(player[e->i].cs, &e->wrtefs);
}

void		close_client(t_play *player, t_env *e)
{
  player[e->i].type = FD_FREE;
  write(player[e->i].cs, "ko\n", 3);
  close(player[e->i].cs);
  if (player[e->i].team != NULL)
    {
      return_place_on_team(&player[e->i], e->team);
      free(player[e->i].team);
    }
  player[e->i].team = NULL;
  printf("client %d disconnected\n", player[e->i].cs);
  FD_CLR(player[e->i].cs, &e->readfs);
  FD_CLR(player[e->i].cs, &e->wrtefs);
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
	  nbr = place_in_the_team(e->team, serv->players[e->i].action[0]);
	  my_putnbr_fd(serv->players[e->i].cs, nbr);
	  my_putchar_fd(serv->players[e->i].cs, '\n');
	  my_putnbr_fd(serv->players[e->i].cs, serv->x);
	  my_putchar_fd(serv->players[e->i].cs,' ');
	  my_putnbr_fd(serv->players[e->i].cs, serv->y);
	  my_putchar_fd(serv->players[e->i].cs,'\n');
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

void	temp_life(t_play *player, t_env *e, t_desc *serv, t_timev t)
{
  double time1;
  double time2;

  gettimeofday(&e->tv, NULL);
  time1 = (double)e->tv.tv_sec + (double)e->tv.tv_usec / 1000000;
  time2 = (double)t.t_old.tv_sec + (double)t.t_old.tv_usec / 1000000;
  if (serv->tv != NULL && t.d == 1)
    if (my_strcmp(t.action, "vie") == 0 && time1 >= time2)
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
	    player->type = FD_FREE;
	    if (player[e->i].team != NULL)
	      {
		return_place_on_team(&player[e->i], e->team);
		free(player[e->i].team);
		player[e->i].team = NULL;
	      }
	    printf("deleting client %d\n", player[e->i].cs);
	  }
      }
}

void	treat_command(t_desc *serv, t_env *e, t_play *player, t_timev t)
{
  double time1;
  double time2;

  gettimeofday(&e->tv, NULL);
  if (serv->tv != NULL && t.d == 1)
    {
      time1 = (double)e->tv.tv_sec + (double)e->tv.tv_usec / 1000000;
      time2 = (double)t.t_old.tv_sec + (double)t.t_old.tv_usec / 1000000;
      if (time1 >= time2)
	if (player->type == FD_CLIENT)
	  {
 	    t.d = 0;
	    if (my_strcmp(t.action, "vie") == 0)
	      {
		manage_life(player, e, serv, t);
	      }
 	    else
	      {
		my_putstr("executing commande \" ");
		my_putstr(t.action);
		my_putstr(" \" from player : ");
		my_putnbr_fd(1, t.cs);
		my_putstr("\n");
		manage_commande(serv, player, e, t.action);
		del_elem_to_queu(&serv->tv, t);
	      }
	  }
    }
}

void	manage_client(t_desc *serv, t_env *e, t_timev t)
{
  int	n;
  int	x;
  char	buff[4091];

  e->i = -1;
  while (e->i++ < MAX_FD)
    {
      if (serv->players[e->i].type == FD_CLIENT &&
	  FD_ISSET(serv->players[e->i].cs, &e->readfs))
	{
	  n = xread(serv->players[e->i].cs, buff, 4090);
	  if (n == 0)
	    {
	      if (serv->players[e->i].inv[0] > 0)
		{
		  ghost_mode(serv->players, e);
		  printf("client in ghost mode\n");
		}
	      else
		{
		  close_client(serv->players, e);
		  printf("deleting client %d\n", serv->players[e->i].cs);
		}
	    }
	  else
	    {
	      manage_buff(&serv->players[e->i], buff, n);
	      if (!my_strcmp(serv->players[e->i].action[serv->players[e->i].end - 1], "GRAPHIC"))
		{
		  serv->players[e->i].type = FD_GRAPHIC;
		  graphic_write(serv, serv->players, e);
		}
	      else
		client_write(serv, e, n);
	    }
	  memset(buff, 0, 4091);
	}
      if (serv->players[e->i].type == FD_CLIENT)
	{
	  if (serv->players[e->i].cs == t.cs && FD_ISSET(t.cs, &e->wrtefs))
	    treat_command(serv, e, &serv->players[e->i], t);
	}
      else if (serv->players[e->i].type == FD_GHOST)
 	temp_life(&serv->players[e->i],  e, serv, t);
    }
}

void			add_players(t_desc *serv, t_env *e)
{
  int			x;
  int			i;
  unsigned int		len;
  struct sockaddr_in	client;

  x = 0;
  i = 0;
  len = sizeof(client);
  if ((e->cs = accept(serv->s, (struct sockaddr*)&client, &len)) != -1)
    while (x < MAX_FD)
      {
	if (serv->players[x].type == FD_FREE)
	  {
	    init_client(&serv->players[x], e->cs, inet_ntoa(client.sin_addr), serv);
	    break;
	  }
	x++;
      }
}
