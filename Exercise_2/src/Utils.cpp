#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "utils.hpp"

using namespace std;

void leggifile(const std::string &filename, double &S, int &n, double *&w, double *&r) {

    // Apro il file
    ifstream inputFile;
    inputFile.open(filename);
    if (inputFile.fail())
    {
        cerr<< "file open failed"<< endl;
    }

    string weight;
    string rate;
    string line;
    string nomevalore;
    int i = 1;
    // questo mi serve per stampare i valori sottoforma di stringa
    istringstream portafoglio;  // S
    istringstream peso; // w
    istringstream tassoritorno; // r
    istringstream asset; //n è il numero di asset

    while(!inputFile.eof())
    {
        if(i==1)
        {
            getline(inputFile,nomevalore, ';'); //prende la riga prima del ;
            getline(inputFile,line); //prende il resto della riga dopo ;
            portafoglio.str(line); // così prendo solo il valore di S
            portafoglio >> S;
        }
        else if(i==2)
        {
            getline(inputFile, nomevalore, ';');
            getline(inputFile,line);
            asset.str(line);
            asset >> n;
            w = new double[n]; //ora che so la dimensione n posso creare i vettori
            r = new double[n];
        }

        else if(i==3) //la terza riga del file che leggo è intestazione
        {
            getline(inputFile, nomevalore); // questa riga non la stampo, contiene solo le lettere w e r
        }
        else
        {
            getline(inputFile,weight, ';'); //la prima del ; è w (weight)
            getline(inputFile,rate); // la seconda parte è r (rate)
            peso.str(weight);
            tassoritorno.str(rate);
            peso.clear();
            tassoritorno.clear();
            peso >> w[i-4]; //ogni riga ha la prossima componente del vettore w, solo che parto dalla quarta riga
            tassoritorno >> r[i-4];
        }
        i = i+1;

    }

    inputFile.close();
}

// calcolo il valore del portafoglio e il tasso di ritorno
void valoreportafoglio(double S, int n, double *w, double *r, double &V, double &rateOfReturn) {
    V = 0.0;

    for (int i = 0; i < n; ++i) {
        V += S*w[i] * (1 + r[i]);
    }
    rateOfReturn = (V - S) / S;
}

// stampo i risultati
void stamporisultati(double S, int n, double *w, double *r, double V, double rateOfReturn) {

    // stampo i risultati sull'output c++
    cout << "S = " << fixed << setprecision(2) << S << ", n = " << n << endl; // precisione 2
    cout << "w = [ ";
    for (int i = 0; i < n; ++i) {
        cout << fixed << setprecision(2) << w[i] << " ";
    }
    cout << "]" << endl;

    cout << "r = [ ";
    for (int i = 0; i < n; ++i) {
        cout << fixed << setprecision(2) << r[i] << " ";
    }
    cout << "]" << endl;

    cout << "Rate of return of the portfolio: " << fixed << setprecision(4) << rateOfReturn << endl; // nell'output aveva 4 cifre dopo la virgola
    cout << "V: " << fixed << setprecision(2) << V << endl;


    // stampo i risultati nel file result.txt
    ofstream outputFile("result.txt"); // scrivo la stessa cosa con outputFile
    if (outputFile.is_open()) {
        outputFile << "S = " << fixed << setprecision(2) << S << ", n = " << n << endl;
        outputFile << "w = [ ";
        for (int i = 0; i < n; ++i) {
            outputFile << fixed << setprecision(2) << w[i] << " ";
        }
        outputFile << "]" << endl;

        outputFile << "r = [ ";
        for (int i = 0; i < n; ++i) {
            outputFile << fixed << setprecision(2) << r[i] << " ";
        }
        outputFile << "]" << endl;

        outputFile << "Rate of return of the portfolio: " << fixed << setprecision(4) << rateOfReturn << endl;
        outputFile << "V: " << fixed << setprecision(2) << V << endl;

        outputFile.close();
    } else {
        cerr << "Errore: impossibile aprire il file. " << endl;
    }
}
