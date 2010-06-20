/*
** annexe.c for buffer ... in /u/all/iniong_a/cu/rendu/c/tmp
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Mon Jun 14 17:33:41 2010 aime-bijou iniongo
** Last update Sun Jun 20 14:58:44 2010 aime-bijou iniongo
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

char		*get_buf(char *buffer, int len, t_play *player)
{
  void		*save;
  char		*tmp;
  int		n;
  int		l;

  if (buffer[0] == '\n' || buffer[0] == 13)
    return (NULL);
  tmp = xmalloc(sizeof(char *) * len);
  strcpy(tmp, buffer);
  n = len;
  while (buffer[len - 1] != '\n')
    {
      bzero(buffer, len);
      save = tmp;
      if ((len = xrecv(player->cs, buffer, 4091, 0)) > 0)
	{
	  n += len - 1;
	  free(tmp);
	  tmp = xmalloc(sizeof(char *) * n);
	  tmp = save;
	  strcat(tmp, buffer);
	}
       else
 	break;
    }
  l = 0;
  while (l < n)
    {
      if (tmp[l] == 13 || tmp[l] == '\n')
	tmp[l] = '\0';
      l++;
    }
  return (tmp);
}

void		manage_buff(t_play *player, char *buffer, int len)
{
  int		i;
  int		x;
  char		a;
  char		*tmp;

  tmp = get_buf(buffer, len, player);
  i = player->end  % 100;
  if (player->action[i] != NULL)
    {
      free(player->action[i]);
      player->action[i] = NULL;
    }
  if (tmp == NULL)
    {
      if (player->action[i] == NULL)
	player->action[i] = xmalloc(sizeof(char *) * my_strlen("empty"));
      strcpy(player->action[i], "empty");
    }
  else
    {
      player->action[i] = xmalloc(sizeof(char *) * my_strlen(tmp));
      strcpy(player->action[i], tmp);
    }
  printf("client %d send : ' %s'\n", player->cs, player->action[i]);
  if (tmp != NULL)
    free(tmp);
  player->end++;
}
