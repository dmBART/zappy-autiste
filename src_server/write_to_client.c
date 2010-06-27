/*
** write_to_client.c for zappy in /u/all/milbau_a/cu/zop
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Sun Jun 20 15:48:37 2010 alexis milbault
** Last update Sun Jun 20 16:50:55 2010 alexis milbault
*/

#include <string.h>
#include "../includes/server.h"

void	add_cto_buffer(t_desc *serv, char c)
{
  serv->buffer[serv->buf++] = c;
}

void	add_sto_buffer(t_desc *serv, char *str)
{
  int	i;

  i = 0;
  while (str[i])
    serv->buffer[serv->buf++] = str[i++];
}

void	add_nto_buffer(t_desc *serv, int nbr)
{
  int	beg;
  int	end;

  if (nbr < 0)
    {
      add_cto_buffer(serv, '-');
      add_nto_buffer(serv, -nbr);
    }
  else
    {
      beg = nbr / 10;
      end = nbr % 10;
      if (beg != 0)
	add_nto_buffer(serv, beg);
      add_cto_buffer(serv, end + '0');
    }
}

void	write_to_client(t_desc *serv, int fd)
{
  write (fd, serv->buffer, my_strlen(serv->buffer));
  memset(serv->buffer, 0, 4091);
  serv->buf = 0;
}
