/*
** action_objects.c for zappy in /u/all/milbau_a/cu/zappy
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Wed Jun  2 15:06:26 2010 alexis milbault
<<<<<<< .mine
** Last update Sun Jun 20 17:01:03 2010 alexis milbault
=======
** Last update Mon Jun 21 00:03:45 2010 alexandra ekra
>>>>>>> .r65
*/

#include "../includes/server.h"

void	inventory(t_desc *serv, t_play *player, t_env *e, char **cmd)
{
  int	i;
  int	len;
  int	start;

  i = -1;
  start = 0;
  if (serv && (cmd[0] != NULL) && e->team)
    {
      while (++i < 7)
	{
	  if (i == 0)
	    add_sto_buffer(serv, "{ ");
	  len = my_strlen(get_ressource_name(i));
	  add_sto_buffer(serv, (char *)get_ressource_name(i));
	  add_cto_buffer(serv, ' ');
	  add_nto_buffer(serv, player->inv[i]);
	  if (i == 6)
	    add_sto_buffer(serv, "}\n");
	  else
	    add_sto_buffer(serv, ", ");
	  write_to_client(serv, player->cs);
	}
    }
}

void	take_object(t_desc *serv, t_play *player, t_env *e, char **cmd)
{
  int	id;

  if ((cmd[1] != NULL) && ((id = get_ressource_id(cmd[1])) >= 0) && e->team)
    {
      if (take_ressource_on_map(serv->map, player->x, player->y, id) == 0)
	{
	  player->inv[id]++;
	  add_sto_buffer(serv, "ok\n");
	  if (e->graph_cs != -1 && FD_ISSET(e->graph_cs, &e->wrtefs))
	    graph_take_objects(serv, player, e, id);
	}
      else
	add_sto_buffer(serv, "ko\n");
    }
  else
    add_sto_buffer(serv, "ko\n");
  write_to_client(serv, player->cs);
}

void	drop_object(t_desc *serv, t_play *player, t_env *e, char **cmd)
{
  int	id;

  if ((cmd[1] != NULL) && ((id = get_ressource_id(cmd[1])) >= 0) && e->team)
    {
      if (player->inv[id] > 0)
	{
	  player->inv[id]--;
	  if (update_exist_case(serv->map, player->x, player->y, id) < 0)
	    fill_map(&serv->map, player->x, player->y, id);
	  add_sto_buffer(serv, "ok\n");
	  if (e->graph_cs != -1 && FD_ISSET(e->graph_cs, &e->wrtefs))
	    graph_drop_objects(serv, player, e, id);
	}
      else
	add_sto_buffer(serv, "ko\n");
    }
  else
    add_sto_buffer(serv, "ko\n");
  write_to_client(serv, player->cs);
}
