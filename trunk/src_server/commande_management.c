/*
** commande_management.c for zappy in /u/all/milbau_a/cu/zappy
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Thu Jun  3 16:15:08 2010 alexis milbault
** Last update Sat Jun 12 21:27:31 2010 aime-bijou iniongo
*/

#include "../includes/commandes.h"

void	manage_commande(t_desc *serv, t_play *player, char *cmd)
{
  int	i;
  char	**tab;

  i = 0;
  tab = my_str_to_wordtab(cmd);
  while (cmd_tab[i].cmd)
    {
      if (my_strcmp(cmd_tab[i].cmd, tab[0]) == 0)
	{
	  cmd_tab[i].f(serv, player, tab);
	  break ;
	}
      i++;
    }
  if (cmd_tab[i].cmd == NULL)
    {
      /*return KO to client*/
      write(player->cs, "ko\n", 3);
    }
}
