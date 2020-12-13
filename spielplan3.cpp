/**************************************************************************
* Dateiename	    : spielplan.cpp
* Projekt	        : Spielplanerstellung mittels Backtracking
* Autor	            : Nora Jungierek
* E-mail		    : nora@jungierek.de
* letzte Bearbeitung: 09.12.2020
\**************************************************************************/

#include "spielplan2.hpp"

bool vollstaendig(const int anzahl_m, int laenge_spielplan){
    return laenge_spielplan == (anzahl_m * (anzahl_m - 1) / 3);
}

bool spielanzahl_erreicht(const TEAM_KONSTELLATION tk, int sta[BITS][BITS], const int anzahl_m, int max_anzahl_spiele){

    std::vector<int> teams = teams_in_konstellation(tk);

    if(DEBUG) std::cout << "Statistik: " << sta[teams[0]][teams[1]] << " " << sta[teams[0]][teams[2]] << " " << sta[teams[1]][teams[2]] << std::endl;
    if(DEBUG) std::cout << "Statistik: " << sta[teams[1]][teams[0]] << " " << sta[teams[2]][teams[0]] << " " << sta[teams[2]][teams[1]] << std::endl;
    return  
        sta[teams[0]][teams[1]] >= max_anzahl_spiele ||  
        sta[teams[0]][teams[2]] >= max_anzahl_spiele ||
        sta[teams[1]][teams[2]] >= max_anzahl_spiele;

}

void aktualisiere_statistik(int sta[BITS][BITS], const TEAM_KONSTELLATION tk, const int zaehler){  //zaehler: fuers addieren oder subtrahieren von der Statistik

    if(abs(zaehler) != 1){
        std::cout << "\nBOESER FEHLER, zaehler falsch z=" << zaehler << std::endl;
        exit(102);
    }
    std::vector<int> teams = teams_in_konstellation(tk);
    if(DEBUG) std::cout << "l=" << teams.size() << " " << teams[0] << " " << teams[1] << " " << teams[2] << std::endl;
    sta[teams[0]][teams[1]] += zaehler;
    sta[teams[0]][teams[2]] += zaehler;  
    sta[teams[1]][teams[2]] += zaehler;

}

void drucke_statistik ( int n, int statistik [BITS][BITS] ) {

    for ( int i = 0; i < n - 1; i++ ) {
        for ( int j = 0; j <= i; j++ ) {
            std::cout << " ";
        }
        for ( int j = i + 1; j < n; j++ ) {
            //std::cout << "[" << i << "," << j << "]=" << statistik [i] [j] << "|";
            std::cout << statistik [i] [j];
        }
        std::cout << std::endl;
    }
}

bool erzeuge_spielplan ( const int anzahl_mannschaften, std::vector<TEAM_KONSTELLATION> &spielplan, int statistik [BITS][BITS] ){
    
    // if(DEBUG) std::cout << "[" << spielplan.size() << "] ";

    if ( DEBUG2 ) drucke_statistik ( anzahl_mannschaften, statistik );
    if ( DEBUG2 ) drucke_vektor ( "", spielplan, true );

    if ( vollstaendig ( anzahl_mannschaften, spielplan.size() ) ){                       //Abbruch, falls gueltiger Plan gefunden
        if(DEBUG) std::cout << "VOLLSTAENDIG" << std::endl;
        // std::cout << "<<<" << std::endl;
        return true;
    }

    for ( int i = 0; i < anzahl_mannschaften - 2; i++ ) {
        if ( DEBUG2 ) std::cout << "i=" << i << std::endl;
        for ( int j = i + 1; j < anzahl_mannschaften - 1; j++ ) {
            if ( DEBUG2 ) std::cout << "j=" << j << std::endl;
            if ( statistik [i] [j] < SPIELE_JE_MANNSCHAFT ) {
                // for ( int k = j + 1; k < anzahl_mannschaften; k++ ) {
                for ( int k = anzahl_mannschaften - 1; k > j; k-- ) {
                    if ( DEBUG2 ) std::cout << "k=" << k << std::endl;
                    TEAM_KONSTELLATION tk = erzeuge_konstellation ( i, j, k );
                    if ( !ist_konstellation_in_vektor ( tk, spielplan ) ) {
                        if ( statistik [i] [k] < SPIELE_JE_MANNSCHAFT && statistik [j] [k] < SPIELE_JE_MANNSCHAFT ) {
                            if ( DEBUG2 ) std::cout << "-->" << std::endl;
                            // drucke_konstellation ( tk );
                            aktualisiere_statistik ( statistik, tk, +1 );
                            spielplan.push_back ( tk );
                            if ( erzeuge_spielplan ( anzahl_mannschaften, spielplan, statistik ) ) {
                                return true;
                            }
                            aktualisiere_statistik ( statistik, tk, -1 );
                            spielplan.pop_back();
                        }
                    }
                }
            }
         }
    }

    if ( DEBUG2 ) std::cout << "<--" << std::endl;
    return false; // falls keine Loesung gefunden wurde

}


//Alle funktionen in richtiger Reihenfolge ausfuehren und zeit stoppen
int spielplan(int n){

    //Zeitmessung start
    Timer t = Timer();
    t.start();

    std::cout << "--------------------------------------------" << std::endl;

    int statistik[BITS][BITS] = {0};
    std::vector<TEAM_KONSTELLATION> spielplan;

    if ( erzeuge_spielplan ( n, spielplan, statistik ) ) {
        drucke_vektor ( "Spielplan", spielplan, false );
    }
    else{
        std::cout << "Es gibt keine gueltige Loesung" << std::endl;
    }
    if(DEBUG) std::cout << "--------------------------------------------" << std::endl;
    if(DEBUG) std::cout << "\n--------------------------------------------" << std::endl;

    //Zeitmessung ende
    t.stop();
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Zeit: " << t.secs() << "s" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    return 0;
}