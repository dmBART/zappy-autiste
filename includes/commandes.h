/*
** commandes.h for zappy in /u/all/milbau_a/cu/zappy
** 
** Made by alexis milbault
** Login   <milbau_a@epitech.net>
** 
** Started on  Thu Jun  3 16:27:34 2010 alexis milbault
** Last update Sat Jun 12 21:25:34 2010 aime-bijou iniongo
*/
#ifndef _COMMANDES_H_
#define _COMMANDES_H_

#include "../includes/server.h"

typedef struct	s_cmd
{
  char		*cmd;
  void		(*f)(t_desc *, t_play *, char **);
}		t_cmd;

t_cmd	cmd_tab[]= {
  {"avance", move_forward},
  {"droite", turn_right},
  {"gauche", turn_left},
  {"voir", see},
  {"inventaire", inventory},
  {"prend", take_object},
  {"pose", drop_object},
  /*  {"expulse", },
  {"broadcast", },
  {"fork", },
  {"connect_nbr", },*/
  {NULL, NULL},
};


#endif /*_COMMANDES_H_*/