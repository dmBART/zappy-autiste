/*
** graph_commands.c for zappy in /u/all/ekra_a/cu/rendu/c/zappy-autiste/src_server
** 
** Made by alexandra ekra
** Login   <ekra_a@epitech.net>
** 
** Started on  Sun Jun 20 00:19:51 2010 alexandra ekra
** Last update Sun Jun 20 16:49:02 2010 alexandra ekra
*/

#include "../includes/server.h"



void	sst(t_desc *serv, t_play *players, t_env *e, char **cmd)
{
  if (!cmd[1] || cmd[2] || check_is_num(cmd[1]) == -1)
    write(players[e->i].cs, "sbp\n", 4);
  else
    {
      serv->t = my_getnbr(cmd[1]);
      send_time_unit(serv, players, e);
    }
}

void	sgt(t_desc *serv, t_play *players, t_env *e, char **cmd)
{
  if (cmd[1])
    write(players[e->i].cs, "sbp\n", 4);
  else
    send_time_unit(serv, players, e);
}

void	msz(t_desc *serv, t_play *players, t_env *e, char **cmd)
{
  if (cmd[1])
    write(players[e->i].cs, "sbp\n", 4);
  else
    send_map_size(serv, players, e);
}

t_graph		gl_command[] =
  {
    {"msz", msz},
    {"bct", bct},
    {"mct", mct},
    {"tna", tna},
    {"ppo", ppo},
    {"plv", plv},
    {"pin", pin},
    {"sgt", sgt},
    {"sst", sst},
    {0, 0}
  };

void	graph_command(t_desc *serv, t_play *players, t_env *e)
{
  char	**cmd;
  int	i;

  cmd = my_str_to_wordtab(players[e->i].action[players[e->i].end - 1]);
  i = 0;
  while (gl_command[i].com)
    {
      if (!my_strcmp(cmd[0], gl_command[i].com))
	{
	  gl_command[i].f(serv, players, e, cmd);
	  break;
	}
      i++;
    }
  if (!gl_command[i].com || !my_strcmp(cmd[0], "GRAPHIC"))
    write(players[e->i].cs, "suc\n", 4);
  /*  free_tab(cmd);*/
}

void	read_graph(t_desc *serv, t_play *players, t_env *e)
{
  int	n;
  char	buff[10];

  if (FD_ISSET(players[e->i].cs, &e->readfs))
    {
      n = xread(players[e->i].cs, buff, 10);
      if (n)
	{
	  manage_buff(&players[e->i], buff, n);
	  if (FD_ISSET(players[e->i].cs, &e->wrtefs))
	    graph_command(serv, players, e);
	}
      memset(buff, 0, 10);
    }
}
