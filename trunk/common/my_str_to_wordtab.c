/*
** my_str_to_wordtab.c for my_ftp in /u/all/milbau_a/cu/rendu/c/my_ftp/common
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Sun Apr 18 21:37:28 2010 alexis milbault
** Last update Wed Apr 28 23:32:22 2010 alexis milbault
*/

#include <stdlib.h>
#include "../includes/server.h"

int	my_countword(char *str)
{
  int	i;
  int	m;

  i = 0;
  m = 2;
  while (str[i] != '\0' && str[i] != '\n')
    {
      if (str[i] == ' ')
	m = m + 1;
      i = i + 1;
    }
  return (m);
}
int	my_countchar(char *str)
{
  int	c;
  
  c = 0;
  while (str[c] != ' ' && str[c] != '\0' && str[c] != '\n')
    c = c + 1; 
  c = c + 1;
  return (c);
}

char	**my_str_to_wordtab(char *str)
{
  char	**tab;
  int	i;
  int	b;
  int	a;
  
  b = 0;
  i = 0;
  a = 0;
  if (str[i] == ' ')
    while (str[i] == ' ')
      i++;
  tab = xmalloc(sizeof(*tab) * (my_countword(str)));
  while (str[i] != '\n' && str[i] != '\0')
    {
      if (str[i] == ' ' || str[i] == '\n')
	{
	  while (str[i] == ' ')
	    i++;
	  a = a + 1;
	  b = 0;
	}
      tab[a] = xmalloc(sizeof(**tab) * (my_countchar(str + i)));
      while ((str[i] != ' ')  && (str[i] != '\n') && (str[i] != '\0'))
	tab[a][b++] = str[i++];
      tab[a][b] = '\0';
    }
  tab[a + 1] = 0;
  return (tab);
}
