/*
 * manipulation.c
 *
 *  Created on: 9 Dec 2012
 *      Author: tim
 */
#include <stdlib.h>
#include "data.h"
#include "functions.h"
#include <stdio.h>
void checkin(Event *event, int node_ident, Entrant *entrant, int h, int m){
	int time = h*60 + m;
	Node *at = findNode(event, node_ident);
	entrant->time = time;
	listadd(at, &entrant->visited);
}



