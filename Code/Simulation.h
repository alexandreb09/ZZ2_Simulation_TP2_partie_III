#pragma once

#include <ostream>
#include <string>

#include <algorithm>
#include <cstdlib>						// aléatoire

#include "Machine.h"
#include "Assemblage.h"
#include "Entree.h"
#include "File.h"
#include "Affichage.h"


//==============================================



void gerer_Entrer_1(File& file_m1, Machine &serveur1, Entree & entree, int & date_courante, std::vector<pair_client_t> & sortie);
void gerer_Entrer_2(File & file_m2, Machine &serveur2, Entree & entree_2, int & date_courante, std::vector<pair_client_t> & sortie);
void gerer_Machine_1(File & file_m1, File &file_m2, Machine &serveur1, Machine &serveur2, Assembleur &assemblage, int & date_courante);
void gerer_Machine_2(File & file_m1, File &file_m2, Machine &serveur1, Machine &serveur2, Assembleur &assemblage, int & date_courante);
void gerer_Assemblage(File &file_m1, File &file_m2, Machine &serveur1, Machine &serveur2, Assembleur &assemblage, std::vector<pair_client_t> & sortie, int & date_courante);
void simuler(int duree_sim, int duree_entre_2_cl_src1, int duree_entre_2_cl_src2, int duree_traitement_cl_m1, int duree_traitement_cl_m2, int duree_assemblage, System::Windows::Forms::RichTextBox^  richTextBox1, System::Windows::Forms::DataVisualization::Charting::Chart^ graphique);

int getProchainEven(Assembleur assemblage, Machine serveur1, Machine serveur2, Entree entree_1, Entree entree_2);

bool sortByID(Client &lhs, Client &rhs);
bool sortByDateEntree(Client &lhs, Client &rhs);