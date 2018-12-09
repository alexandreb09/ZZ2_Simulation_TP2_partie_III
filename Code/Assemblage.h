#pragma once

#include "Client.h"

class Assembleur {
	int Etat;
	int date_prochain_event;
	int duree_traitement;
	Client pair_clients_presents[2];

public:
	Assembleur();
	Assembleur(int Etat, int date_prochain_event, int dt);

	const int getEtat();
	void setEtat(int n_Etat);

	const int getDPE();
	void setDPE(int new_des);

	const int getDuree_traitement();
	void setDuree_traitement(int dt);

	const Client getClient_present_1();
	const Client getClient_present_2();
	void setClient_present(Client n_cl1, Client n_cl2);
};
