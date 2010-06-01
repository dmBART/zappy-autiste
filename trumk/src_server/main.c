/*
** main.c for zappy in /u/all/milbau_a/cu/rendu/c/my_irc/src_server
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Sat May 22 02:33:22 2010 alexis milbault
** Last update Fri May 28 20:07:50 2010 aime-bijou iniongo
*/

#include <stdio.h>
#include "../includes/server.h"

void	print_desc(t_desc *serv)
{
  int	i;

  i = 0;
  printf("-port: %d\n-width:%d\n-hight:%d\n-nb_player:%d\n-time:%d\n-team:",
	 serv->port, serv->x, serv->y, serv->nb_sock, serv->t);
  while (serv->team[i])
    printf("'%s' ", serv->team[i++]);
  printf("\n\n");
}

static void	tzero_serv(t_desc *serv)
{
  serv->port = 0;
  serv->x = 0;
  serv->y = 0;
  serv->nb_sock = 0;
  serv->t = 0;
  serv->team = NULL;
}

int		main(int argc, char **argv)
{
  t_desc	serv;
  int		i;

  i = 0;
  tzero_serv(&serv);
  get_param(&serv, argv, argc);
  print_desc(&serv);
  start_server(&serv);
  return (0);
}
