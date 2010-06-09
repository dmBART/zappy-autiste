/*
** option.h for zappy in /u/all/milbau_a/cu/rendu/c/my_irc/src_server
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Sat May 22 03:24:54 2010 alexis milbault
** Last update Mon May 24 21:59:48 2010 alexis milbault
*/

#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include "../includes/server.h"

typedef struct	s_opt
{
  char	*ref_opt;
  int	(*f)(t_desc *, char **, int, int);
}		t_opt;

t_opt	opt_tab[]= {
  {"-p", get_arg_port},
  {"-x", get_arg_width},
  {"-y", get_arg_hight},
  {"-n", get_arg_teams_name},
  {"-c", get_arg_nb_player},
  {"-t", get_arg_time},
  {NULL, NULL},
};


#endif /*_OPTIONS_H_*/
