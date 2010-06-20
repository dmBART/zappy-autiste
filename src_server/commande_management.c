/*
** commande_management.c for zappy in /u/all/milbau_a/cu/zappy
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Thu Jun  3 16:15:08 2010 alexis milbault
** Last update Sun Jun 20 20:54:01 2010 alexandra ekra
*/

#include <stdlib.h>
#include "../includes/commandes.h"

void	free_tab(char **tab)
{
  int	x;

  x = 0;
  while (tab[x] != NULL)
    {
      free(tab[x]);
      x++;
    }
  if (tab[0] != NULL)
    free(tab);
}

void	manage_commande(t_desc *serv, t_play *player, t_env *e, char *cmd)
{
  int	i;
  char	**tab;

  i = 0;
  tab = my_str_to_wordtab(cmd);
  while (cmd_tab[i].cmd)
    {
      if (my_strcmp(cmd_tab[i].cmd, tab[0]) == 0)
	{
	  cmd_tab[i].f(serv, player, e, tab);
	  break ;
	}
      i++;
    }
  my_putstr("x:");
  my_putnbr_fd(1, player->x);
  my_putstr(" -- y:");
  my_putnbr_fd(1, player->y);
  my_putstr(" -- dir:");
  my_putnbr_fd(1, player->dir);
  my_putstr("\n");
  if (cmd_tab[i].cmd == NULL)
    {
      /*return KO to client*/
      write(player->cs, "ko\n", 3);
    }
}
