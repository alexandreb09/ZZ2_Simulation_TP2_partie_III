#include "Client.h"

int Client::compteur = 0;

Client::Client() :id(compteur), date_entree_syst(0), date_sortie_syst(-1), nb_machines_vues(0) {
}

Client::Client(int des) : id(compteur++), date_entree_syst(des), date_sortie_syst(-1), nb_machines_vues(0) {}

Client::Client(int des, int dss) : id(compteur++), date_entree_syst(des), date_sortie_syst(dss), nb_machines_vues(0) {}

Client& Client::operator=(const Client &cl1){
	if (this != &cl1) {
		id = cl1.id;
		date_entree_syst = cl1.date_entree_syst;
		date_sortie_syst = cl1.date_sortie_syst;
		nb_machines_vues = cl1.nb_machines_vues;
	}
	return *this;
}

int Client::getId() {
	return id;
}

int Client::getDate_entree_syst() {
	return date_entree_syst;
};
void Client::setDate_entree_syst(int new_des) {
	date_entree_syst = new_des;
}

int Client::getDate_sortie_syst() {
	return date_sortie_syst;
}
void Client::setDate_sortie_syst(int n_dss) {
	date_sortie_syst = n_dss;
};

int Client::getNb_machines_vues() {
	return nb_machines_vues;
}
void Client::setNb_machines_vues(int nbmv) {
	nb_machines_vues = nbmv;
}

int Client::getMachine(int indice) {
	return gamme[indice];
}
void Client::setMachine(int machine) {
	gamme[nb_machines_vues] = machine;
	nb_machines_vues++;
}



bool operator==(const Client & cl1, const Client & cl2) {
	return cl1.id == cl2.id;
}