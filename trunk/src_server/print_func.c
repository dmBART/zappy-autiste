/*
** print_func.c for print functions in /u/all/iniong_a/cu/rendu/c/tmp
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Mon Jun 14 17:37:40 2010 aime-bijou iniongo
** Last update Mon Jun 14 18:11:43 2010 aime-bijou iniongo
*/

#include <stdio.h>
#include "../includes/server.h"

void	show_all_timer(t_timev *timer)
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

void	show_player_buffer(char **buffer)
{
  int	x;

  for (x=0; buffer[x] != NULL; x++)
    printf("buffer player = %s\n", buffer[x]);
}

