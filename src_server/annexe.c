/*
** annexe.c for buffer ... in /u/all/iniong_a/cu/rendu/c/tmp
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Mon Jun 14 17:33:41 2010 aime-bijou iniongo
** Last update Mon Jun 21 00:00:12 2010 aime-bijou iniongo
*/

#include <stdio.h>
#include <string.h>
#include "../includes/server.h"

int	count_elem_timer(t_timev *eve, int fd)
{
  int	count;

  count = 0;
  while (eve)
    {
      if (eve->cs == fd)
	if (my_strcmp(eve->action, "vie") != 0)
	  count++;
      eve = eve->next;
    }
  return (count);
}

char		*get_true_buf(char *buffer, int len, t_play *player)
{
  void		*save;
  char		*tmp;
  int		n;

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
  return (tmp);
}

char		*get_buf(char *buffer, int len, t_play *player)
{
  int		l;
  int		n;
  char		*tmp;

  l = 0;
  if (buffer[0] == '\n' || buffer[0] == 13)
    return (NULL);
  tmp = get_true_buf(buffer, len, player);
  n = my_strlen(tmp);
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
  char		*tmp;

  tmp = get_buf(buffer, len, player);
  i = player->end  % 100;
  if (player->action != NULL)
    {
      free(player->action);
      player->action = NULL;
    }
  if (tmp == NULL)
    {
      if (player->action == NULL)
	player->action = xmalloc(sizeof(char *) * my_strlen("empty"));
      strcpy(player->action, "empty");
    }
  else
    {
      player->action = xmalloc(sizeof(char *) * my_strlen(tmp));
      strcpy(player->action, tmp);
    }
  printf("client %d send : ' %s'\n", player->cs, player->action);
  if (tmp != NULL)
    free(tmp);
  player->end++;
}
