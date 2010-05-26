/*
** utils.c for zappy in /u/all/milbau_a/cu/rendu/c/zappy
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Mon May 24 00:50:37 2010 alexis milbault
** Last update Mon May 24 15:45:03 2010 alexis milbault
*/

#include <unistd.h>

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    i++;
  return (i);
}

void	my_putstr(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    write(1, &str[i++], 1);
}


int	my_strcmp(char *s1, char *s2)
{
  int	i;

  i = 0;
  if (my_strlen(s1) != my_strlen(s2))
    return (-1);
  while (s1[i] && s2[i])
    {
      if (s1[i] != s2[i])
	return (-1);
      i++;
    }
  return (0);
}

int	my_getnbr(char *str)
{
  int	result;
  int	fact_mult;
  int	i;

  fact_mult = 1;
  result = 0;
  i = my_strlen(str) - 1;
  while (i >= 0)
    {
      result += (fact_mult * (str[i] - '0'));
      fact_mult *= 10;
      i--;
    }
  return (result);
}
