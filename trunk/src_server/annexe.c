/*
** annexe.c for buffer ... in /u/all/iniong_a/cu/rendu/c/tmp
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Mon Jun 14 17:33:41 2010 aime-bijou iniongo
** Last update Mon Jun 14 18:16:55 2010 aime-bijou iniongo
*/

#include <string.h>
#include "../includes/server.h"

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
  strcpy(player->action[i], buffer);
  player->end++;
}
