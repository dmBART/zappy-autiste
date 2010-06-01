/*
** check_func.c for zappy in /u/all/milbau_a/cu/rendu/c/zappy
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Mon May 24 00:16:58 2010 alexis milbault
** Last update Mon May 24 15:19:29 2010 alexis milbault
*/

#include "../includes/server.h"

int	check_is_num(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] < '0' || str[i] > '9')
	return (-1);
      i++;
    }
  return (0);
}

int	check_team_already_exist(char **argv, char **team, int i, int j)
{
  int	a;

  a = 0;
  while (team[a])
    {
      if (my_strcmp(argv[i], team[a]) == 0)
	return (0);
      a++;
    }
  return (-1);
}

int	check_is_printable(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] < 33 || str[i] > 126)
	return (-1);
      i++;
    }
  return (0);
}
