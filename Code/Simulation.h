#pragma once




#include <ostream>
#include <sstream>
#include <string>

#include <vector>
#include <algorithm>
#include <cstdlib>						// aléatoire

#include "Machine.h"
#include "Assemblage.h"
#include "Entree.h"
#include "File.h"


const int libre = 0;
const int occupe = 1;
const int bloque = 2;
const int ENTREE_1 = 0;
const int ENTREE_2 = 1;
const int MACHINE_1 = 2;
const int MACHINE_2 = 3;
const int ASSEMBLAGE = 4;
const int SORTIE = 5;

//==============================================


void gerer_Entrer_1(File& file_m1, Machine &serveur1, Entree & entree, int & date_courante, std::vector<Client> & sortie);
void gerer_Entrer_2(File & file_m2, Machine &serveur2, Entree & entree_2, int & date_courante, std::vector<Client> & sortie);
void gerer_Machine_1(File & file_m1, File &file_m2, Machine &serveur1, Machine &serveur2, Assembleur &assemblage, int & date_courante);
void gerer_Machine_2(File & file_m1, File &file_m2, Machine &serveur1, Machine &serveur2, Assembleur &assemblage, int & date_courante);
void gerer_Assemblage(File &file_m1, File &file_m2, Machine &serveur1, Machine &serveur2, Assembleur &assemblage, std::vector<Client> & sortie, int & date_courante);
void simuler(int duree_sim, int duree_entre_2_cl_src1, int duree_entre_2_cl_src2, int duree_traitement_cl_m1, int duree_traitement_cl_m2, int duree_traitement_cl_m3, System::Windows::Forms::RichTextBox^  richTextBox1);

int getProchainEven(Assembleur assemblage, Machine serveur1, Machine serveur2, Entree entree_1, Entree entree_2);

bool sortByID(Client &lhs, Client &rhs);
bool sortByDateEntree(Client &lhs, Client &rhs);

void afficher_Textbox(std::string str, System::Windows::Forms::RichTextBox^  richTextBox1);
void afficher_Resultat(Machine serveur_1, Machine serveur_2, Assembleur assembleur, std::vector<Client> sortie, File &file_mA, File &file_mB, System::Windows::Forms::RichTextBox^  richTextBox1);
void afficher_Contenu_machine(std::ostringstream &oss, Machine machine, File file, int numero);