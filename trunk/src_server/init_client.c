/*
** init_client.c for init client in /u/all/iniong_a/cu/rendu/c/zappy
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Mon Jun 14 16:53:09 2010 aime-bijou iniongo
** Last update Mon Jun 14 18:15:09 2010 aime-bijou iniongo
*/

#include <stdio.h>
#include "../includes/server.h"

void	init_client(t_play *player, int fd, char *ip)
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
