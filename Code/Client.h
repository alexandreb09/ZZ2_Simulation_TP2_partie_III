#pragma once

const int infini = 9999;
const int taille_max_gamme = 2;

class Client {
	int id;
	int date_entree_syst;
	int date_sortie_syst;
	int gamme[taille_max_gamme];
	int nb_machines_vues;

	static int compteur;

	public:
		Client();
		Client(int des);
		Client(int des, int dss);

		int getId();

		int getDate_entree_syst();
		void setDate_entree_syst(int new_des);

		int getDate_sortie_syst();
		void setDate_sortie_syst(int n_dss);

		int getNb_machines_vues();
		void setNb_machines_vues(int nbmv);

		int getMachine(int indice);
		void setMachine(int machine);

		friend bool operator==(const Client & cl1, const Client & cl2);
		Client& operator=(const Client &cl1);
};

bool operator==(const Client & cl1, const Client & cl2);