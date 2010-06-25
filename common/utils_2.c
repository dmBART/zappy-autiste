/*
** utils_2.c for utils in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Thu May 27 20:03:17 2010 aime-bijou iniongo
** Last update Sun Jun 20 16:41:45 2010 alexis milbault
*/

#include <stdio.h>
#include <unistd.h>

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

void	my_putchar_fd(int fd, char c)
{
  write(fd, &c, 1);
}

void	my_putnbr_fd(int fd, int nbr)
{
  int	beg;
  int	end;

  if (nbr < 0)
    {
      my_putchar_fd(fd, '-');
      my_putnbr_fd(fd, -nbr);
    }
  else
    {
      beg = nbr / 10;
      end = nbr % 10;
      if (beg != 0)
	my_putnbr_fd(fd, beg);
      my_putchar_fd(fd, end + '0');
    }

}
