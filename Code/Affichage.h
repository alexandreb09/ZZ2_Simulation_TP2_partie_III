#pragma once


#include <vector>
#include <sstream>

#include "File.h"
#include "Machine.h"
#include "Assemblage.h"
#include "Constante.h"

void afficher_Textbox(std::string str, System::Windows::Forms::RichTextBox^  richTextBox1);
void afficher_Resultat(int duree_sim, Machine serveur_1, Machine serveur_2, Assembleur assembleur, std::vector<pair_client_t> sortie, File &file_mA, File &file_mB, System::Windows::Forms::RichTextBox^  richTextBox1, System::Windows::Forms::DataVisualization::Charting::Chart^ graphique);
void afficher_Contenu_machine(std::ostringstream &oss, Machine machine, File file, int numero);
void affichage_graph(std::vector<pair_client_t> sortie, System::Windows::Forms::DataVisualization::Charting::Chart^ chart);