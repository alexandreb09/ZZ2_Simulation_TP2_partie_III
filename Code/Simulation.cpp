#include "Simulation.h"


void simuler(int duree_sim, 
			int duree_entre_2_cl_src_1, 
			int duree_entre_2_cl_src2, 
			int duree_traitement_cl_m1,	
			int duree_traitement_cl_m2,	
			int duree_assemblage, 
			System::Windows::Forms::RichTextBox^  richTextBox1,
			System::Windows::Forms::DataVisualization::Charting::Chart^ graphique) {
	File file_m1;
	File file_m2;
	std::vector< pair_client_t > sortie;
	Machine serveur1(libre, infini, duree_traitement_cl_m1);
	Machine serveur2(libre, infini, duree_traitement_cl_m2);
	Assembleur assemblage(libre, infini, duree_assemblage);
	Entree entree_1(libre, duree_entre_2_cl_src_1), entree_2(libre, duree_entre_2_cl_src2);

	int date_courante = 0;

	while (date_courante <= duree_sim) {
		/* Recherche DPE la plus petite */
		int P = getProchainEven(assemblage, serveur1, serveur2, entree_1, entree_2);					// Si PDE entree plus petite	

		switch (P) {
			case ENTREE_1: gerer_Entrer_1(file_m1, serveur1, entree_1, date_courante, sortie);
				break;
			case ENTREE_2: gerer_Entrer_2(file_m2, serveur2, entree_2, date_courante, sortie);
				break;
			case MACHINE_1: gerer_Machine_1(file_m1, file_m2, serveur1, serveur2, assemblage, date_courante);
				break;
			case MACHINE_2: gerer_Machine_2(file_m1, file_m2, serveur1, serveur2, assemblage, date_courante);
				break;
			case ASSEMBLAGE: gerer_Assemblage(file_m1, file_m2, serveur1, serveur2, assemblage, sortie, date_courante);
				break;
			default: break;
		}
	}

	afficher_Resultat(duree_sim, serveur1, serveur2, assemblage, sortie, file_m1, file_m2, richTextBox1, graphique);
}


void gerer_Assemblage(File &file_m1, File &file_m2, Machine &serveur1, Machine &serveur2, Assembleur &assemblage, std::vector<pair_client_t> & sortie, int & date_courante) {
	date_courante = assemblage.getDPE();
	Client cl1 = assemblage.getClient_present_1();
	Client cl2 = assemblage.getClient_present_2();
	cl1.setDate_sortie_syst(date_courante);
	cl2.setDate_sortie_syst(date_courante);
	
	pair_client_t pair_cl;
	pair_cl.liste[0] = cl1;
	pair_cl.liste[1] = cl2;
	sortie.push_back(pair_cl);

	file_m1.MAJDuree_Occupation(date_courante);
	file_m2.MAJDuree_Occupation(date_courante);

	if ((bloque == serveur1.getEtat()) & (bloque == serveur2.getEtat())) {
		Client piece1 = serveur1.getClient_present();					// La piece1 sort de la machine 1
		Client piece2 = serveur2.getClient_present();					// La piece2 sort de la machine 2

		assemblage.setClient_present(piece1, piece2);					// Et rentre sur la machine 2
		assemblage.setDPE(date_courante + assemblage.getDuree_traitement());
		assemblage.setEtat(occupe);

		serveur1.MAJ_duree_etat_bloquee(date_courante);
		serveur2.MAJ_duree_etat_bloquee(date_courante);

		if (!file_m1.test_File_Vide()) {								// Gestion machine 1
			Client piece_new;											// Recupération piece file_m1
			file_m1.suppression_file(piece_new);
			serveur1.setClient_present(piece_new);
			serveur1.setDPE(date_courante + serveur1.getDuree_traitement());
			serveur1.setEtat(occupe);
		}
		else {
			serveur1.setEtat(libre);
			serveur1.setDPE(infini);
		}

		if (!file_m2.test_File_Vide()) {								// Gestion Machine 2
			Client piece_new;											// Recupération piece file_m2
			file_m2.suppression_file(piece_new);
			serveur2.setClient_present(piece_new);
			serveur2.setDPE(date_courante + serveur2.getDuree_traitement());
			serveur2.setEtat(occupe);
		}
		else {
			serveur2.setEtat(libre);
			serveur2.setDPE(infini);
		}
	}
	else {
		assemblage.setEtat(libre);
		assemblage.setDPE(infini);
	}
}


void gerer_Machine_2(File &file_m1, File & file_m2, Machine &serveur1, Machine &serveur2, Assembleur &assemblage, int & date_courante){
	date_courante = serveur2.getDPE();
	file_m1.MAJDuree_Occupation(date_courante);							// Stats
	file_m2.MAJDuree_Occupation(date_courante);

	if ((libre == assemblage.getEtat()) & (bloque == serveur1.getEtat())) {
		Client piece1 = serveur1.getClient_present();					// La piece1 sort de la machine 1
		Client piece2 = serveur2.getClient_present();					// La piece2 sort de la machine 2

		assemblage.setClient_present(piece1, piece2);					// Et rentre sur la machine 2
		assemblage.setDPE(date_courante + assemblage.getDuree_traitement());
		assemblage.setEtat(occupe);

		serveur1.MAJ_duree_etat_bloquee(date_courante);
		if (bloque == serveur2.getEtat()) {
			serveur2.MAJ_duree_etat_bloquee(date_courante);
		}

		if (!file_m1.test_File_Vide()) {								// Gestion machine 1
			Client piece_new;											// Recupération piece file_m1
			file_m1.suppression_file(piece_new);
			// file_m1.MAJDPE();
			serveur1.setClient_present(piece_new);
			serveur1.setDPE(date_courante + serveur1.getDuree_traitement());
			serveur1.setEtat(occupe);
		}
		else {
			serveur1.setEtat(libre);
			serveur1.setDPE(infini);
		}

		if (!file_m2.test_File_Vide()) {								// Gestion Machine 2
			Client piece_new;											// Recupération piece file_m2
			file_m2.suppression_file(piece_new);
			serveur2.setClient_present(piece_new);
			serveur2.setDPE(date_courante + serveur2.getDuree_traitement());
			serveur2.setEtat(occupe);
		}
		else {
			serveur2.setEtat(libre);
			serveur2.setDPE(infini);
		}
	}
	else {								// Assemblage bloqué
		if (bloque == serveur2.getEtat()) {
			serveur2.MAJ_duree_etat_bloquee(date_courante);
		}
		serveur2.setDate_entree_etat_bloque(date_courante);
		serveur2.setEtat(bloque);
		serveur2.setDPE(infini);
	}
}



void gerer_Machine_1(File & file_m1, File &file_m2, Machine &serveur1, Machine &serveur2, Assembleur &assemblage, int & date_courante) {
	date_courante = serveur1.getDPE();
	file_m1.MAJDuree_Occupation(date_courante);							// Stats
	file_m2.MAJDuree_Occupation(date_courante);

	if ((libre == assemblage.getEtat()) & (bloque == serveur2.getEtat())) {
		Client piece1 = serveur1.getClient_present();					// La piece1 sort de la machine 1
		Client piece2 = serveur2.getClient_present();					// La piece2 sort de la machine 2

		assemblage.setClient_present(piece1, piece2);					// Et rentre sur la machine 2
		assemblage.setDPE(date_courante + assemblage.getDuree_traitement());
		assemblage.setEtat(occupe);

		serveur2.MAJ_duree_etat_bloquee(date_courante);
		if (bloque == serveur1.getEtat()) {
			serveur1.MAJ_duree_etat_bloquee(date_courante);
		}

		if (!file_m1.test_File_Vide()) {								// Gestion machine 1
			Client piece_new;											// Recupération piece file_m1
			file_m1.suppression_file(piece_new);
			serveur1.setClient_present(piece_new);
			serveur1.setDPE(date_courante + serveur1.getDuree_traitement());
			serveur1.setEtat(occupe);
		}
		else {
			serveur1.setEtat(libre);
			serveur1.setDPE(infini);
		}

		if (!file_m2.test_File_Vide()) {								// Gestion Machine 2
			Client piece_new;											// Recupération piece file_m2
			file_m2.suppression_file(piece_new);
			serveur2.setClient_present(piece_new);
			serveur2.setDPE(date_courante + serveur2.getDuree_traitement());
			serveur2.setEtat(occupe);
		}
		else {
			serveur2.setEtat(libre);
			serveur2.setDPE(infini);
		}
	}
	else {								// Assemblage bloqué
		if (bloque == serveur1.getEtat()) {
			serveur1.MAJ_duree_etat_bloquee(date_courante);
		}
		serveur1.setDate_entree_etat_bloque(date_courante);
		serveur1.setEtat(bloque);
		serveur1.setDPE(infini);
	}
}



void gerer_Entrer_1(File & file_m1, Machine &serveur1, Entree & entree_1, int & date_courante, std::vector<pair_client_t> & sortie) {
	date_courante = entree_1.getDPE();
	Client cl(date_courante);
	entree_1.setDPE(date_courante + entree_1.getDuree_inter_arrivee());
	file_m1.MAJDuree_Occupation(date_courante);

	if (file_m1.test_File_pleine()) {
		/*
		Traitements des clients qui quittent la queue quand ils voient qu'ils vont 
		attendre 45 min pour les brioches de la belle-mère ...
		*/
	}
	else {
		if (libre == serveur1.getEtat()) {						// Si serveur libre
			serveur1.setEtat(occupe);
			serveur1.setClient_present(cl);
			serveur1.setDPE(date_courante + serveur1.getDuree_traitement());
		}
		else {													// si serveur occupe
			file_m1.ajout_file(cl);								// Ajout dans la file
		}
	}
	entree_1.setDPE(date_courante + entree_1.getDuree_inter_arrivee());
}

void gerer_Entrer_2(File & file_m2, Machine &serveur2, Entree & entree_2, int & date_courante, std::vector<pair_client_t> & sortie) {
	date_courante = entree_2.getDPE();
	Client cl(date_courante);
	entree_2.setDPE(date_courante + entree_2.getDuree_inter_arrivee());
	file_m2.MAJDuree_Occupation(date_courante);

	if (file_m2.test_File_pleine()) {
		/*
		Traitements des clients qui quittent la queue quand ils voient qu'ils vont
		attendre 45 min pour les brioches de la belle-mère ...
		*/
	}
	else {
		if (libre == serveur2.getEtat()) {						// Si serveur libre
			serveur2.setEtat(occupe);
			serveur2.setClient_present(cl);
			serveur2.setDPE(date_courante + serveur2.getDuree_traitement());
		}
		else {													// si serveur occupe
			file_m2.ajout_file(cl);								// Ajout dans la file
		}
	}
	entree_2.setDPE(date_courante + entree_2.getDuree_inter_arrivee());
}




int getProchainEven(Assembleur assemblage, Machine serveur1, Machine serveur2, Entree entree_1, Entree entree_2) {
	int rep = ENTREE_1;					//entree
	if ((assemblage.getDPE() <= serveur1.getDPE()) & (assemblage.getDPE() <= serveur2.getDPE()) & (assemblage.getDPE() <= entree_1.getDPE()) & (assemblage.getDPE() <= entree_2.getDPE())) {
		rep = ASSEMBLAGE;
	}
	else {
		if ((serveur1.getDPE() <= serveur2.getDPE()) & (serveur1.getDPE() <= entree_1.getDPE()) & (serveur1.getDPE() <= entree_2.getDPE())) {
			rep = MACHINE_1;
		}
		else {
			if ((serveur2.getDPE() <= entree_1.getDPE()) & (serveur2.getDPE() <= entree_2.getDPE())) {
				rep = MACHINE_2;
			}
			else {
				if (entree_2.getDPE() < entree_1.getDPE()) {
					rep = ENTREE_2;
				}
			}
		}
	}
	return rep;
}


bool sortByID(Client &lhs, Client &rhs) { return lhs.getId() < rhs.getId(); }
bool sortByDateEntree(Client &lhs, Client &rhs) { return lhs.getDate_entree_syst() < rhs.getDate_sortie_syst(); }
