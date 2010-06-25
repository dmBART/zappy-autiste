/*
** main.c for zappy in /u/all/milbau_a/cu/rendu/c/my_irc/src_server
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Sat May 22 02:33:22 2010 alexis milbault
<<<<<<< .mine
** Last update Sun Jun 20 23:38:11 2010 alexis milbault
=======
** Last update Mon Jun 21 00:19:29 2010 alexandra ekra
>>>>>>> .r65
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

void	print_map(t_map *map)
{
  t_map	*tmp;

  tmp = map;
  while (tmp)
    {
      printf("x:%d - y:%d\n", tmp->x, tmp->y);
      printf("food:%d\nlin:%d\nder:%d\nsib:%d\nmen:%d\nphi:%d\nthy:%d\n",
	     tmp->res[0], tmp->res[1], tmp->res[2], tmp->res[3],
	     tmp->res[4], tmp->res[5], tmp->res[6]);
      printf("##########\n");
      tmp = tmp->next;
    }
}

static void	tzero_serv(t_desc *serv)
{
  serv->port = 0;
  serv->x = 0;
  serv->y = 0;
  serv->nb_sock = 0;
  serv->t = 0;
  serv->team = NULL;
  serv->nj = 0;
}

int		main(int argc, char **argv)
{
  t_desc	serv;
  int		i;

  i = 0;
  tzero_serv(&serv);
  get_param(&serv, argv, argc);
  print_desc(&serv);
  init_map(&serv);
  print_map(serv.map);
  start_server(&serv);
  return (0);
}
