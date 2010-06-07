/*
** xfunc_1.c for my_irc in /u/all/milbau_a/cu/rendu/c/my_irc/src_client
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Wed Apr 28 23:26:09 2010 alexis milbault
** Last update Sun Jun  6 23:48:56 2010 aime-bijou iniongo
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <stdio.h>
#include "../includes/server.h"

void	*xmalloc(size_t size)
{
  void	*ptr;

  if ((ptr = malloc(size)) == 0)
    {
      perror("malloc");
/*       write (2, "Can't malloc.\n", 14); */
      exit(EXIT_FAILURE);
    }
  return (ptr);
}

ssize_t	xread(int d, void *buf, size_t nbytes)
{
  int	n;

  if ((n = read(d, buf, nbytes)) == -1)
    {
      write (2, "Can't read file.\n", 17);
      exit(EXIT_FAILURE);
    }
  return (n);
}

int	xsocket(int domain, int type, int protocol)
{
  int	fd;

  fd = socket(domain, type, protocol);
  if (fd == -1)
    {
      perror("socket : ");
      exit(EXIT_FAILURE);
    }
  return (fd);
}

void	xbind(int s, struct sockaddr_in addr)
{
  if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    {
      perror("bind : ");
      exit(EXIT_FAILURE);
    }
}

int	xlisten(int s, int backlog)
{
  int	i;

  i = listen(s, backlog);
  if (i == -1)
    {
      perror("listen : ");
      exit(EXIT_FAILURE);
    }
  return (0);
}

int	xselect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
		struct timeval *timeout)
{
  int	r;

  if ((r = select(nfds, readfds, writefds, exceptfds, timeout)) == -1)
    {
      perror("select");
      exit(EXIT_FAILURE);
    }
  return (r);
}
