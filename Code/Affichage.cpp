/*=======================================================*/
/*							AFFICHAGE   				 */
/*=======================================================*/


#include "Affichage.h"

void afficher_Resultat(int duree_simulation, 
							Machine serveur_1, 
							Machine serveur_2, 
							Assembleur assembleur, 
							std::vector<pair_client_t > sortie, 
							File &file_mA, File &file_mB,
							System::Windows::Forms::RichTextBox^  richTextBox1,
							System::Windows::Forms::DataVisualization::Charting::Chart^ graphique) {
	std::ostringstream oss;

	Client cl;
	int nb_piece = 0, temps_moyen = 0;
	
	for (unsigned i = 0; i < sortie.size(); ++i) {
		oss << "Assemblage " << i << "\n";
		nb_piece++;
		cl = sortie[i].liste[0];
		oss << "    id : " << cl.getId() << "   || entree : " << cl.getDate_entree_syst() << "   || sortie : " << cl.getDate_sortie_syst() << "\n";
		cl = sortie[i].liste[1];
		oss << "    id : " << cl.getId() << "   || entree : " << cl.getDate_entree_syst() << "   || sortie : " << cl.getDate_sortie_syst() << "\n";
		
		temps_moyen += cl.getDate_sortie_syst(); // -cl.getDate_entree_syst();
		// chart->Series[0]->Points->AddXY(nb_piece, temps_moyen / nb_piece);
	}

	afficher_Contenu_machine(oss, serveur_1, file_mA, MACHINE_1);
	afficher_Contenu_machine(oss, serveur_2, file_mB, MACHINE_2);

	oss << "\nListe des pièces dans l'assembleur :\n";
	cl = assembleur.getClient_present_1();
	oss << "id : " << cl.getId() << "   || entree : " << cl.getDate_entree_syst() << "   || sortie : " << cl.getDate_sortie_syst() << "\n";
	cl = assembleur.getClient_present_2();
	oss << "id : " << cl.getId() << "   || entree : " << cl.getDate_entree_syst() << "   || sortie : " << cl.getDate_sortie_syst() << "\n";

	oss << "\n\nNombre moyen client file1 : " << (float) file_mA.getDuree_occupation() / duree_simulation;
	oss << "\nNombre moyen client file2 : " << (float) file_mB.getDuree_occupation() / duree_simulation;
	oss << "\n\nTemps moyen mach1 bloquee : " << (float)100 * serveur_1.getDuree_etat_bloquee() / duree_simulation << "%";
	oss << "\n\nTemps moyen mach2 bloquee : " << (float)100 * serveur_2.getDuree_etat_bloquee() / duree_simulation << "%";

	affichage_graph(sortie, graphique);

	afficher_Textbox(oss.str(), richTextBox1);
}


void afficher_Contenu_machine(std::ostringstream &oss, Machine machine, File file, int numero) {
	oss << "\nListe des pièces dans la machine " << numero << ":\n";
	Client cl = machine.getClient_present();
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


void affichage_graph(std::vector<pair_client_t> sortie, System::Windows::Forms::DataVisualization::Charting::Chart^ chart) {
	int nb_piece = 0, temps_moyen = 0;
	Client cl;
	for (unsigned i = 0; i < sortie.size(); ++i) {
		nb_piece++;
		cl = sortie[i].liste[0];
		temps_moyen += cl.getDate_sortie_syst() - cl.getDate_entree_syst();
		chart->Series[0]->Points->AddXY(nb_piece, temps_moyen / nb_piece);

		cl = sortie[i].liste[1];
		temps_moyen += cl.getDate_sortie_syst() - cl.getDate_entree_syst();
		chart->Series[1]->Points->AddXY(nb_piece, temps_moyen / nb_piece);
	}
}