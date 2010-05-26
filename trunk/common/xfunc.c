/*
** xfunc_1.c for my_irc in /u/all/milbau_a/cu/rendu/c/my_irc/src_client
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Wed Apr 28 23:26:09 2010 alexis milbault
** Last update Mon May 24 14:02:49 2010 alexis milbault
*/

#include "../includes/server.h"

void	*xmalloc(size_t size)
{
  void	*ptr;

  if ((ptr = malloc(size)) == 0)
    {
      write (2, "Can't malloc.\n", 14);
      exit(EXIT_FAILURE);
    }
  return (ptr);
}

ssize_t	xread(int d, void *buf, size_t nbytes)
{
  if (read(d, buf, nbytes) == -1)
    {
      write (2, "Can't read file.\n", 17);
      exit(EXIT_FAILURE);
    }
  return (0);
}
