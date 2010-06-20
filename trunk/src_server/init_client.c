/*
** init_client.c for init client in /u/all/iniong_a/cu/rendu/c/zappy
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Mon Jun 14 16:53:09 2010 aime-bijou iniongo
** Last update Sun Jun 20 22:05:11 2010 alexandra ekra
*/

#include <stdio.h>
#include <time.h>
#include "../includes/server.h"

void	place_joueur_on_the_map(t_play *player, t_desc *serv)
{
  int	tmp;

  player->x = rand() % serv->x;
  player->y = rand() % serv->y;
  tmp = rand() % 4;
  if (tmp == 0)
    player->dir = RIGHT;
  else if (tmp == 1)
    player->dir = LEFT;
  else if (tmp == 2)
    player->dir = UP;
  else
    player->dir = DOWN;
}

void	init_client(t_play *player, int fd, char *ip, t_desc *serv)
{
  int	i;

  i = 0;
  player->cs = fd;
  player->ip = ip;
  printf("new connection %d from %s\n", player->cs, ip);
  player->life = 1260;
  write(fd, "BIENVENUE\n", 10);
  player->type = FD_CLIENT;
  player->end = 0;
  player->state = 0;
  player->begin = 0;
  player->lvl = 1;
  place_joueur_on_the_map(player, serv);
  player->inv = xmalloc(sizeof(int *) * 7);
  while (i < 7)
    {
      if (i == 0)
	player->inv[i] = 10;
      else
	player->inv[i] = 0;
      i++;
    }
}
