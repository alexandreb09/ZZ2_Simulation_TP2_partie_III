#include "Simulation.h"


void simuler(int duree_sim, int duree_entre_2_cl_src_1, int duree_entre_2_cl_src2, int duree_traitement_cl_m1, int duree_traitement_cl_m2, int duree_traitement_cl_m3, System::Windows::Forms::RichTextBox^  richTextBox1) {
	File file_m1;
	File file_m2;
	std::vector<Client> sortie;
	Machine serveur1(libre, infini, duree_traitement_cl_m1);
	Machine serveur2(libre, infini, duree_traitement_cl_m2);
	Assembleur assemblage(libre, infini, duree_traitement_cl_m2);
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
	afficher_Resultat(serveur1, serveur2, assemblage, sortie, file_m1, file_m2, richTextBox1);
}


void gerer_Assemblage(File &file_m1, File &file_m2, Machine &serveur1, Machine &serveur2, Assembleur &assemblage, std::vector<Client> & sortie, int & date_courante) {
	date_courante = assemblage.getDPE();
	Client cl1 = assemblage.getClient_present_1();
	Client cl2 = assemblage.getClient_present_2();
	cl1.setDate_sortie_syst(date_courante);
	cl2.setDate_sortie_syst(date_courante);

	sortie.push_back(cl1);
	sortie.push_back(cl2);
	if (bloque == serveur1.getEtat() & bloque == serveur2.getEtat()) {
		Client piece1 = serveur1.getClient_present();					// La piece1 sort de la machine 1
		Client piece2 = serveur2.getClient_present();					// La piece2 sort de la machine 2

		assemblage.setClient_present(piece1, piece2);					// Et rentre sur la machine 2
		assemblage.setDPE(date_courante + assemblage.getDuree_traitement());
		assemblage.setEtat(occupe);

		// piece.setDate_entree_machine_2(date_courante);

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
			// file_m1.setDPE(infini);
		}

		if (!file_m2.test_File_Vide()) {								// Gestion Machine 2
			Client piece_new;											// Recupération piece file_m2
			file_m2.suppression_file(piece_new);
			// file_m2.MAJDPE();
			serveur2.setClient_present(piece_new);
			serveur2.setDPE(date_courante + serveur2.getDuree_traitement());
			serveur2.setEtat(occupe);
		}
		else {
			serveur2.setEtat(libre);
			serveur2.setDPE(infini);
			// file_m2.setDPE(infini);
		}
	}
	else {
		assemblage.setEtat(libre);
		assemblage.setDPE(infini);

		// file_m2.MAJDuree_Occupation(date_courante);
	}
}


void gerer_Machine_2(File &file_m1, File & file_m2, Machine &serveur1, Machine &serveur2, Assembleur &assemblage, int & date_courante){
	date_courante = serveur2.getDPE();

	if ((libre == assemblage.getEtat()) & (bloque == serveur1.getEtat())) {
		Client piece1 = serveur1.getClient_present();					// La piece1 sort de la machine 1
		Client piece2 = serveur2.getClient_present();					// La piece2 sort de la machine 2

		assemblage.setClient_present(piece1, piece2);					// Et rentre sur la machine 2
		assemblage.setDPE(date_courante + assemblage.getDuree_traitement());
		assemblage.setEtat(occupe);

		// piece.setDate_entree_machine_2(date_courante);

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
			// file_m1.setDPE(infini);
		}

		if (!file_m2.test_File_Vide()) {								// Gestion Machine 2
			Client piece_new;											// Recupération piece file_m2
			file_m2.suppression_file(piece_new);
			// file_m2.MAJDPE();
			serveur2.setClient_present(piece_new);
			serveur2.setDPE(date_courante + serveur2.getDuree_traitement());
			serveur2.setEtat(occupe);
		}
		else {
			serveur2.setEtat(libre);
			serveur2.setDPE(infini);
			// file_m2.setDPE(infini);
		}
	}
	else {								// Assemblage bloqué
		serveur2.setEtat(bloque);
		serveur2.setDPE(infini);
		// serveur1.setDate_entree_etat_bloque(date_courante);
	}
}



void gerer_Machine_1(File & file_m1, File &file_m2, Machine &serveur1, Machine &serveur2, Assembleur &assemblage, int & date_courante) {
	date_courante = serveur1.getDPE();

	if ((libre == assemblage.getEtat()) & (bloque == serveur2.getEtat())) {
		Client piece1 = serveur1.getClient_present();					// La piece1 sort de la machine 1
		Client piece2 = serveur2.getClient_present();					// La piece2 sort de la machine 2

		assemblage.setClient_present(piece1, piece2);					// Et rentre sur la machine 2
		assemblage.setDPE(date_courante + assemblage.getDuree_traitement());
		assemblage.setEtat(occupe);

		// piece.setDate_entree_machine_2(date_courante);

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
			// file_m1.setDPE(infini);
		}

		if (!file_m2.test_File_Vide()) {								// Gestion Machine 2
			Client piece_new;											// Recupération piece file_m2
			file_m2.suppression_file(piece_new);
			// file_m2.MAJDPE();
			serveur2.setClient_present(piece_new);
			serveur2.setDPE(date_courante + serveur2.getDuree_traitement());
			serveur2.setEtat(occupe);
		}
		else {
			serveur2.setEtat(libre);
			serveur2.setDPE(infini);
			// file_m2.setDPE(infini);
		}
	}
	else {								// Assemblage bloqué
		serveur1.setEtat(bloque);
		serveur1.setDPE(infini);
		// serveur1.setDate_entree_etat_bloque(date_courante);
	}
}



void gerer_Entrer_1(File & file_m1, Machine &serveur1, Entree & entree_1, int & date_courante, std::vector<Client> & sortie) {
	date_courante = entree_1.getDPE();
	Client cl(date_courante);
	entree_1.setDPE(date_courante + entree_1.getDuree_inter_arrivee());
	if (file_m1.test_File_pleine()) {
		/*
		cl.setDate_sortie_syst(-1);			// On ne s'occupe pas des clients qui sortent
		sortie.push_back(cl);
		*/
	}
	else {
		if (libre == serveur1.getEtat()) {						// Si serveur libre
			serveur1.setEtat(occupe);
			serveur1.setClient_present(cl);
			serveur1.setDPE(date_courante + serveur1.getDuree_traitement());

			// cl.setDate_entree_machine_1(date_courante);				// Stats
		}
		else {													// si serveur occupe
			file_m1.ajout_file(cl);								// Ajout dans la file
			/*
			if (1 == file_m1.getTaille()) {						// Si c'est le premier element
				file_m1.MAJDPE();								// MAJ DPE file
			}
			*/
		}
		// file_m1.MAJDuree_Occupation(date_courante);
	}
	entree_1.setDPE(date_courante + entree_1.getDuree_inter_arrivee());
}

void gerer_Entrer_2(File & file_m2, Machine &serveur2, Entree & entree_2, int & date_courante, std::vector<Client> & sortie) {
	date_courante = entree_2.getDPE();
	Client cl(date_courante);
	entree_2.setDPE(date_courante + entree_2.getDuree_inter_arrivee());
	if (file_m2.test_File_pleine()) {
		/*
		cl.setDate_sortie_syst(-1);			// On ne s'occupe pas des clients qui sortent
		sortie.push_back(cl);
		*/
	}
	else {
		if (libre == serveur2.getEtat()) {						// Si serveur libre
			serveur2.setEtat(occupe);
			serveur2.setClient_present(cl);
			serveur2.setDPE(date_courante + serveur2.getDuree_traitement());

			// cl.setDate_entree_machine_1(date_courante);		// Stats
		}
		else {													// si serveur occupe
			file_m2.ajout_file(cl);								// Ajout dans la file
			/*
			if (1 == file_m1.getTaille()) {						// Si c'est le premier element
				file_m1.MAJDPE();								// MAJ DPE file
			}
			*/
		}
		// file_m1.MAJDuree_Occupation(date_courante);
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



/*=======================================================*/
/*							AFFICHAGE   				 */
/*=======================================================*/

void afficher_Resultat(Machine serveur_1, Machine serveur_2, Assembleur assembleur, std::vector<Client> sortie, File &file_mA, File &file_mB, System::Windows::Forms::RichTextBox^  richTextBox1) {
	std::ostringstream oss;
	std::ostringstream oss_tmp;
	std::string res;

	Client cl;
	int nb_piece = 0, temps_moyen = 0;

	std::sort(sortie.begin(), sortie.end(), sortByID);

	for (Client cl : sortie) {
		nb_piece++;
		oss << "id : " << cl.getId() << "   || entree : " << cl.getDate_entree_syst() << "   || sortie : " << cl.getDate_sortie_syst() << "   || Gamme : ";
		for (int i = 0; i < cl.getNb_machines_vues(); i++) {
			oss << cl.getMachine(i) << " ";
		}
		oss << "\n";
		temps_moyen += cl.getDate_sortie_syst(); // -cl.getDate_entree_syst();
		// chart->Series[0]->Points->AddXY(nb_piece, temps_moyen / nb_piece);
	}

	afficher_Contenu_machine(oss, serveur_1, file_mA, MACHINE_1);
	afficher_Contenu_machine(oss, serveur_2, file_mB, MACHINE_2);

	oss << "\nListe des pièces dans l'assembleur :\n";
	Client cl_1 = assembleur.getClient_present_1();
	oss << "id : " << cl.getId() << "   || entree : " << cl.getDate_entree_syst() << "   || sortie : " << cl.getDate_sortie_syst() << "\n";
	Client cl_2 = assembleur.getClient_present_2();
	oss << "id : " << cl.getId() << "   || entree : " << cl.getDate_entree_syst() << "   || sortie : " << cl.getDate_sortie_syst() << "\n";

	res = oss.str();
	afficher_Textbox(res, richTextBox1);
}


void afficher_Contenu_machine(std::ostringstream &oss, Machine machine, File file, int numero) {
	Client cl;
	oss << "\nListe des pièces dans la machine " << numero << ":\n";
	cl = machine.getClient_present();
	oss << "id : " << cl.getId() << "   || entree : " << cl.getDate_entree_syst() << "   || sortie : " << cl.getDate_sortie_syst() << "\n";

	while (!file.test_File_Vide()) {
		file.suppression_file(cl);
		oss << "id : " << cl.getId() << "   || entree : " << cl.getDate_entree_syst() << "   || sortie : " << cl.getDate_sortie_syst() << "\n";
	}
}

void afficher_Textbox(std::string str, System::Windows::Forms::RichTextBox^  richTextBox1) {
	std::ostringstream oss;
	oss << str;
	std::string ch = oss.str();
	System::String^ result = gcnew System::String(ch.c_str());
	richTextBox1->AppendText(result);
}
