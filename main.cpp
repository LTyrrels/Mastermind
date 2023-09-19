#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

vector<int> generateCombi(const vector<string>& colors, int color_number){
    vector<int> indice;
    vector<int> secret_combi;
    for(int i = 0; i < colors.size(); ++i){
        indice.push_back(i);
    }

    for(int i = 0; i < color_number; ++i){
        if(indice.empty()){
            cout << "Plus de couleurs disponibles." << endl; 
            break;
        }

        int random_index = rand() % indice.size();
        int selected_index = indice[random_index];
        secret_combi.push_back(selected_index);
        indice.erase(indice.begin() + random_index);
    }

    return secret_combi;
}
int main(){
    vector<string> colors = {"red", "blue", "yellow", "green", "white", "black"};
    int min_color_number = 4;
    int max_color_number = 6;
    srand(static_cast<unsigned int>(time(nullptr)));

    int color_number;
    while(true){
        cout << "Choississez la taille de la combinaison secrete (min " << min_color_number << " et max " << max_color_number << "): ";
        cin >> color_number;

        if(color_number >= min_color_number && color_number <= max_color_number){
            break;
        }

        cout << "Erreur, la taille de la combinaison doit etre entre " << min_color_number << " et " << max_color_number << "." << " Choississez a nouveau." << endl;
    }

    while(true){
        vector<int> secret_combi = generateCombi(colors, color_number);

        cout << "Combinaison secrète (à des fins de test) : ";
        for (int index : secret_combi) {
            cout << colors[index] << " ";
        }
        cout << endl;

        cout << "La combinaison de couleur a ete generee, c'est a vous de jouer maintenant, bonne chance !" << endl << "Pour ecrire la combinaison, vous devez la formatter comme cela : color1 color2 color3 color4 etc..." << endl;

        int tenta = 0;
        int tenta_max = 10;
        bool win = false;

        while (tenta < tenta_max){
            cout << "Tentative " << tenta << " | Entrez votre combinaison (couleur disponible : red, blue, yellow, green, white, black)" << endl;
            vector<string> essai(color_number);

            for(int i = 0; i < color_number; ++i){
                cin >> essai[i];
            }

            bool couleursValides = true;
            for (const string& couleur : essai) {
                if (find(colors.begin(), colors.end(), couleur) == colors.end()) {
                    cout << "Couleur invalide : '" << couleur << "'. Veuillez reessayer." << endl;
                    couleursValides = false;
                    break;
                }
            }

            if (!couleursValides) {
                continue;
            }

            cout << "Vous avez entrer : ";
            for (const string& couleur : essai) {
                cout << couleur << " ";
            }
            cout << endl;

            bool correct = true;
            for (int i = 0; i < color_number; ++i) {
                if (essai[i] != colors[secret_combi[i]]) {
                    correct = false;
                    break;
                }
            }

            if (correct) {
                cout << "Bravo, vous avez devine la combinaison secrete !" << endl;
                win = true;
                break;
            } else {
                cout << "Essai incorrect. Essayez a nouveau." << endl;
            }

            tenta++;
        }

        if(!win){
            cout << "Vous n'avez plus de tentative, vous avez perdu." << endl;
        }
    }
    return 0;
}