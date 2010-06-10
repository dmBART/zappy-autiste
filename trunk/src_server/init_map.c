/*
** init_map.c for zappy in /u/all/milbau_a/cu/zappy/src_server
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Wed Jun  2 15:56:44 2010 alexis milbault
** Last update Thu Jun 10 18:40:32 2010 alexis milbault
*/

#include <time.h>
#include "../includes/server.h"

/*
** (nb_ressource_de_base_par_joueur * nb_joueurs) * (taille_map / 100)
** quota[0] = food
** quota[1] = lin
** quota[2] = der
** quota[3] = sib
** quota[4] = man
** quota[5] = phi
** quota[6] = thy
*/
int	*get_quota(t_desc *serv, int *quota)
{
  if ((serv->x * serv->y) >= 100)
    {
      quota[0] = (5 * (serv->nb_sock * 2)) * ((serv->x * serv->y) / 100);
      quota[1] = (2 * (serv->nb_sock * 2)) * ((serv->x * serv->y) / 100);
      quota[2] = (2 * (serv->nb_sock * 2)) * ((serv->x * serv->y) / 100);
      quota[3] = (3 * (serv->nb_sock * 2)) * ((serv->x * serv->y) / 100);
      quota[4] = (3 * (serv->nb_sock * 2)) * ((serv->x * serv->y) / 100);
      quota[5] = (2 * (serv->nb_sock * 2)) * ((serv->x * serv->y) / 100);
      quota[6] = (1 * (serv->nb_sock * 2)) * ((serv->x * serv->y) / 100);
    }
  else
    {
      quota[0] = (5 * (serv->nb_sock * 2));
      quota[1] = (2 * (serv->nb_sock * 2));
      quota[2] = (2 * (serv->nb_sock * 2));
      quota[3] = (3 * (serv->nb_sock * 2));
      quota[4] = (3 * (serv->nb_sock * 2));
      quota[5] = (2 * (serv->nb_sock * 2));
      quota[6] = (1 * (serv->nb_sock * 2));
    }
  return (quota);
}

/*
** Un quota de ressources doit etre trouver en fonction
** du nombre de joueurs ainsi que la taille de la map.
** On remplit la map aleatoirement selon ce quota
** (x, y en rand).
*/
void	init_map(t_desc *serv)
{
  int	quota[7];
  int	i;
  int	x;
  int	y;

  i = 0;
  serv->map = 0;
  srand(time(0));
  get_quota(serv, quota);
  while (i < 7)
    {
      if (quota[i] > 0)
	{
	  x = rand() % serv->x;
	  y = rand() % serv->y;
	  if (update_exist_case(serv->map, x, y, i) < 0)
	    fill_map(&serv->map, x, y, i);
	}
      if (quota[i]-- <= 0)
	i++;
    }
}
