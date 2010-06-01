/*
** client_management.c for serveur in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Fri May 28 00:49:11 2010 aime-bijou iniongo
** Last update Tue Jun  1 00:47:18 2010 aime-bijou iniongo
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include "../includes/server.h"

void		close_client(t_play *player, t_env *e)
{
  player[e->i].type = FD_FREE;
  write(player[e->i].cs, "ko\n", 3);
  close(player[e->i].cs);
  if (player[e->i].team != NULL)
    free(player[e->i].team);
  player[e->i].team = NULL;
}

void		manage_client(t_desc *serv, t_play *players, t_env *e)
{
  int		n;
  int		len;
  char		buff[4091];

  e->i = 0;
  while (e->i < MAX_FD)
    {
      if (players[e->i].type == FD_CLIENT && FD_ISSET(players[e->i].cs, &e->readfs))
	{
	  memset(buff, 0, 4090);
	  n = xread(players[e->i].cs, buff, 4090);
	  if (n == 0)
	    {
	      printf("client %d disconnected\n", players[e->i].cs);
	      close_client(players, e);
	      FD_CLR(players[e->i].cs, &e->readfs);
	    }
	  else
	    {
	      len = n - 2;
	      if (buff[len] == 13)
		buff[len] = '\0';
	      buff[n - 1] = '\0';
	      if (players[e->i].team == NULL)
		choose_a_team(serv, players, buff, e);
	      else
		add_elem(&players[e->i].t, buff);
	    }
	}
      e->i++;
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
	    players[x].t = NULL;
	    break;
	  }
	x++;
      }
}
