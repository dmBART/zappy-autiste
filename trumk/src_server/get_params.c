/*
** default_mode.c for zappy in /u/all/milbau_a/cu/rendu/c/zappy
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Mon May 24 22:30:45 2010 alexis milbault
** Last update Tue May 25 16:17:32 2010 alexis milbault
*/

#include <stdio.h>
#include "../includes/options.h"

int	check_is_opt(char *str)
{
  int	i;

  i = 0;
  while (opt_tab[i].ref_opt != NULL)
    {
      if (my_strcmp(opt_tab[i].ref_opt, str) == 0)
	return (0);
      i++;
    }
  return (-1);
}

static void	get_default_mode(t_desc *serv)
{
  if (!serv->port)
    serv->port = DEFAULT_PORT;
  if (!serv->x)
    serv->x = DEFAULT_SIZE;
  if (!serv->y)
    serv->y = DEFAULT_SIZE;
  if (!serv->nb_sock)
    serv->nb_sock = DEFAULT_PLAYER;
  if (!serv->t)
    serv->t = DEFAULT_TIME;
  if (!serv->team)
    {
      serv->team = xmalloc(sizeof(**serv->team) * (2 + 1));
      serv->team[0] = DEFAULT_TEAM1;
      serv->team[1] = DEFAULT_TEAM2;
      serv->team[2] = 0;
    }
}

static void	validate_default_mode(t_desc *serv)
{
  char	buf[2];
  int	flag;

  flag = 0;
  printf("Informations missing. Default Mode completed them :\n");
  print_desc(serv);
  while (flag == 0)
    {
      flag = 1;
      my_putstr("Do you want continue with this configuration ? y/n : ");
      xread(0, &buf, 2);
      if (buf[0] == 'n')
	{
	  free(serv->team);
	  exit(EXIT_FAILURE);
	}
      if (buf[0] != 'y')
	flag = 0;
    }
}

void	get_param(t_desc *serv, char **argv, int argc)
{
  int	i;
  int	j;

  i = 1;
  while (i < argc)
    {
      j = -1;
      while (opt_tab[++j].ref_opt != NULL)
	if (my_strcmp(opt_tab[j].ref_opt, argv[i]) == 0)
	  {
	    i = opt_tab[j].f(serv, argv, argc, i);
	    break;
	  }
      if (opt_tab[j].ref_opt == NULL)
	printf("'%s' isn't an argument.\n", argv[i++]);
    }
  if (!serv->port || !serv->x || !serv->y ||
      !serv->nb_sock || !serv->t || !serv->team)
    {
      get_default_mode(serv);
      validate_default_mode(serv);
    }
}
