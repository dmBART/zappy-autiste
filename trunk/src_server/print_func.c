/*
** print_func.c for print functions in /u/all/iniong_a/cu/rendu/c/tmp
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Mon Jun 14 17:37:40 2010 aime-bijou iniongo
** Last update Sun Jun 20 23:39:44 2010 alexis milbault
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

  x = 0;
  while (buffer[x] != NULL)
    {
      printf("buffer player = %s\n", buffer[x]);
      x++;
    }
}

