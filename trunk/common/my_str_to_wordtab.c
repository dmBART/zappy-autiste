/*
** my_str_to_wordtab_modif.c for minishell2 in /u/all/milbau_a/cu/rendu/c/minishell2
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Wed Feb 25 14:09:29 2009 alexis milbault
** Last update Mon Jun 21 00:13:28 2010 alexis milbault
*/

#include "../includes/server.h"

int	count_word(char *str)
{
  int	i;
  int	n;

  i = 0;
  n = 1;
  while (str[i] != '\0' && str[i] != '\n')
    {
      if (str[i] == ' ' && str[i + 1] != '\0')
	n++;
      i++;
    }
  return (n);
}

int	countchar(char *str)
{
  int	c;

  c = 0;
  while ((str[c] != ' ') && (str[c] != '\0') && (str[c] != '\n'))
    c++;
  c += 1;
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
  tab = xmalloc(sizeof(*tab) * ((count_word(str) + 1)));
  while (str[i] != '\n' && str[i] != '\0')
    {
      if (str[i] == ' ' || str[i] == '\n')
	{
	  while (str[i] == ' ')
	    i++;
	  a = a + 1;
	  b = 0;
	}
      tab[a] = xmalloc(sizeof(**tab) * ((countchar(str + i) + 1)));
      while ((str[i] != ' ')  && (str[i] != '\n') && (str[i] != '\0'))
	tab[a][b++] = str[i++];
      tab[a][b] = '\0';
    }
  tab[a + 1] = 0;
  return (tab);
}
