#pragma once

const int libre = 0;
const int occupe = 1;
const int bloque = 2;
const int ENTREE_1 = 0;
const int ENTREE_2 = 1;
const int MACHINE_1 = 2;
const int MACHINE_2 = 3;
const int ASSEMBLAGE = 4;
const int SORTIE = 5;

typedef struct pair_client {
	Client liste[2];
}pair_client_t;