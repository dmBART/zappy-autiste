/*
** do_server.c for do server in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Wed May 26 14:14:09 2010 aime-bijou iniongo
** Last update Wed May 26 15:40:40 2010 aime-bijou iniongo
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "../includes/server.h"

int			init_serveur(t_desc *serv)
{
  int			s;
  struct sockaddr_in	ser;

  s = xsocket(PF_INET, SOCK_STREAM, 0);
  ser.sin_family = AF_INET;
  ser.sin_port = htons(serv->port);
  ser.sin_addr.s_addr = INADDR_ANY;
  xbind(s, ser);
  return (s);
}

void	start_server(t_desc *serv)
{
  t_env	e;
  int	s;

  s = init_serveur(serv);
  xlisten(s, 42);
}
