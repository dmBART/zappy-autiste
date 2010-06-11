/*
** client_management.c for serveur in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Fri May 28 00:49:11 2010 aime-bijou iniongo
** Last update Fri Jun 11 03:22:13 2010 aime-bijou iniongo
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

void		close_client(t_play *player, t_env *e)
{
  player[e->i].type = FD_FREE;
  write(player[e->i].cs, "ko\n", 3);
  close(player[e->i].cs);
  if (player[e->i].team != NULL)
    free(player[e->i].team);
  player[e->i].team = NULL;
  printf("client %d disconnected\n", player[e->i].cs);
  FD_CLR(player[e->i].cs, &e->readfs);
}

void		manage_buff(t_play *player, char *buffer, int len)
{
  int		l;
  int		i;
  int		x;

  l = 0;
  i = player->end  % 100;
  while (l < len)
    {
      if (buffer[l] == 13 || buffer[l] == '\n')
	buffer[l] = '\0';
      l++;
    }
  if (player->action[i] == NULL)
    player->action[i] = xmalloc(sizeof(player->action[i]) * len);
  else
    {
      free(player->action[i]);
      player->action[i] = xmalloc(sizeof(player->action[i]) * len);
    }
  x = 0;
  while (buffer[x] != '\0')
    {
      player->action[i][x] = buffer[x];
      x++;
    }
/*   strcpy(player->action[i], buffer); */
  player->end++;
}

void		show_all_timer(t_timev *timer)
{
  while (timer)
    {
      my_putstr("action = ");
      my_putstr(timer->action);
      my_putstr("\n");
      timer = timer->next;
    }
  my_putstr("####################\n#################\n############\n\n");
}

void		client_write(t_desc *serv, t_play *players, t_env *e, t_timev t, int n)
{
  int		x;

  x = players[e->i].end - 1;
  if (players[e->i].team == NULL && n > 1)
    {
      choose_a_team(serv, players, players[e->i].action[0], e);
      players[e->i].begin = players[e->i].end;
    }
  else
    add_elem(&serv->tv, players[e->i].action[x], players[e->i].cs, serv->t);
}

void		manage_client(t_desc *serv, t_play *players, t_env *e, t_timev t)
{
  int		n;
  int		x;
  char		buff[4091];

  e->i = -1;
  while (e->i++ < MAX_FD)
    {
      if (players[e->i].type == FD_CLIENT && FD_ISSET(players[e->i].cs, &e->readfs))
	{
	  memset(buff, 0, 4090);
	  n = xread(players[e->i].cs, buff, 4090);
	  if (n == 0)
	    close_client(players, e);
	  else
	    {
	      manage_buff(&players[e->i], buff, n);
	      client_write(serv, players, e, t, n);
	    }
	}
      gettimeofday(&e->tv, &e->ts);
      if (e->tv.tv_sec >= t.t_old.tv_sec &&  e->tv.tv_usec > t.t_old.tv_usec
	  && serv->tv != NULL && t.d == 1)
	{
	  if (players[e->i].type == FD_CLIENT)
	    {
	      t.d = 0;
	      /* 	  write(t.cs, "Ok\n", 3);
			  printf("time of execution = %ld\n", t.t);*/
	      del_elem_to_queu(&serv->tv, t);
	    }
	}
      else
	update_time_struct(serv->tv, e);
    }
}

void			add_players(int s, t_env *e, t_play *players)
{
  int			x;
  unsigned int		len;
  struct sockaddr_in	client;

  x = 0;
  len = sizeof(client);
  if ((e->cs = accept(s, (struct sockaddr*)&client, &len)) != -1)
    while (x < MAX_FD)
      {
	if (players[x].type == FD_FREE)
	  {
	    players[x].cs = e->cs;
	    printf("new connection %d\n", players[x].cs);
	    players[x].ip = inet_ntoa(client.sin_addr);
	    players[x].life = 1260;
	    write(e->cs, "BIENVENUE\n", 10);
	    players[x].type = FD_CLIENT;
	    players[x].end = 0;
	    players[x].begin = 0;
	    players[x].lvl = 1;
	    break;
	  }
	x++;
      }
}
