/*
** annexe.c for buffer ... in /u/all/iniong_a/cu/rendu/c/tmp
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Mon Jun 14 17:33:41 2010 aime-bijou iniongo
** Last update Fri Jun 18 10:21:57 2010 aime-bijou iniongo
*/

#include <stdio.h>
#include <string.h>
#include "../includes/server.h"

void		free_tab(char **tab)
{
  int		x;

  x = -1;
  while (x++ < 100)
    if (tab[x] != NULL)
      {
	free(tab[x]);
	tab[x] = NULL;
      }
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
  if (player->action[i] != NULL)
    {
      free(player->action[i]);
      player->action[i] = NULL;
    }
  if (buffer[0] == '\0')
    {
      player->action[i] = xmalloc(sizeof(char *) * my_strlen("empty"));
      strcpy(player->action[i], "empty");
    }
  else
    {
      player->action[i] = xmalloc(sizeof(char *) * my_strlen(buffer));
      strcpy(player->action[i], buffer);
      printf("client %d send : ' %s'\n", player->cs, player->action[i]);
    }
  player->end++;
}
