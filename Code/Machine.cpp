#include "Machine.h"


Machine::Machine() :Etat(0), date_prochain_event(infini) {
}

Machine::Machine(int Etat, int dpe, int dt) : Etat(Etat), date_prochain_event(dpe), duree_traitement(dt) {
}

const int Machine::getEtat() {
	return Etat;
}
void Machine::setEtat(int n_Etat) {
	Etat = n_Etat;
}

const int Machine::getDPE() {
	return date_prochain_event;
}
void Machine::setDPE(int new_des) {
	date_prochain_event = new_des;
}

const int Machine::getDuree_traitement() {
	return duree_traitement;
}
void Machine::setDuree_traitement(int dt) {
	duree_traitement = dt;
}

const Client Machine::getClient_present() {
	return client_present;
}
void Machine::setClient_present(Client n_cl) {
	client_present = n_cl;
}