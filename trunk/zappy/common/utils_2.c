/*
** utils_2.c for utils in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Thu May 27 20:03:17 2010 aime-bijou iniongo
** Last update Thu May 27 20:05:39 2010 aime-bijou iniongo
*/

#include <stdio.h>

int	count_tab(char **tab)
{
  int	nb;

  nb = 0;
  if (tab[0] == NULL)
    {
      perror("tab is nul");
      return (0);
    }
  while (tab[nb] != NULL)
    nb++;
  return (nb);
}
