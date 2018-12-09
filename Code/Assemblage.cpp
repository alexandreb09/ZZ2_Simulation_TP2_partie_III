#include "Assemblage.h"


Assembleur::Assembleur() :Etat(0), date_prochain_event(infini) {
}

Assembleur::Assembleur(int Etat, int dpe, int dt) : Etat(Etat), date_prochain_event(dpe), duree_traitement(dt) {
}

const int Assembleur::getEtat() {
	return Etat;
}
void Assembleur::setEtat(int n_Etat) {
	Etat = n_Etat;
}

const int Assembleur::getDPE() {
	return date_prochain_event;
}
void Assembleur::setDPE(int new_des) {
	date_prochain_event = new_des;
}

const int Assembleur::getDuree_traitement() {
	return duree_traitement;
}
void Assembleur::setDuree_traitement(int dt) {
	duree_traitement = dt;
}

const Client Assembleur::getClient_present_1() {
	return pair_clients_presents[0];
}
const Client Assembleur::getClient_present_2() {
	return pair_clients_presents[1];
}
void Assembleur::setClient_present(Client n_cl1, Client n_cl2) {
	pair_clients_presents[0] = n_cl1;
	pair_clients_presents[1] = n_cl2;
}