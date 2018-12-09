#pragma once

#include "Client.h"


class Machine {
	int Etat;
	int date_prochain_event;
	int duree_traitement;
	Client client_present;

	public:
		Machine();
		Machine(int Etat, int date_prochain_event, int dt);

		const int getEtat();
		void setEtat(int n_Etat);

		const int getDPE();
		void setDPE(int new_des);

		const int getDuree_traitement();
		void setDuree_traitement(int dt);

		const Client getClient_present();
		void setClient_present(Client n_cl);
};
