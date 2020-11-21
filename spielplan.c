/*
 * 21.11.2020 junand
 *  
 * Die ersten Schritte im Spielplan für Nora
 * 
 */

#include <stdint.h>
#include <stdio.h>

typedef uint32_t TEAM_TUPEL;

#define ANZAHL_MANNSCHAFTEN 6
#define ANZAHL_TUPEL (ANZAHL_MANNSCHAFTEN * (ANZAHL_MANNSCHAFTEN - 1) * (ANZAHL_MANNSCHAFTEN - 2) )

TEAM_TUPEL alle_tupel [ANZAHL_TUPEL] = { 0 };
TEAM_TUPEL spielplan [ANZAHL_TUPEL] = { 0 };

int naechstes_tupel = 0;
int naechstes_spiel = 0;

const int BITS = 8 * sizeof ( TEAM_TUPEL );

#define MAX_SPIELE 1

TEAM_TUPEL erzeuge_tupel ( int team1, int team2, int team3 ) {

    return (TEAM_TUPEL) 0 | (1 << team1) | (1 << team2) | (1 << team3);

}

int ist_team_im_tupel ( int team, TEAM_TUPEL tupel ) {

    return tupel & (1 << team);

}

int ist_bereits_gespielt ( TEAM_TUPEL tupel ) {

    for ( int i = 0; i < ANZAHL_TUPEL; i++ ) {
        if ( tupel == spielplan [i] ) return 1;
    }

    return 0;
    
}

void erzuege_alle_tupel () {

    int n = 0;

    for ( int i = 0; i < ANZAHL_MANNSCHAFTEN; i++ ) {
        for ( int j = 0; j < ANZAHL_MANNSCHAFTEN; j++ ) {
            if ( j == i ) continue;
            for ( int k = 0; k < ANZAHL_MANNSCHAFTEN; k++ ) {
                if ( k == j || k == i ) continue;
                TEAM_TUPEL t =  erzeuge_tupel ( i, j, k );
                //printf ( "i=%d j=%d k=%d n=%d t=0x%04x\n", i, j, k, n, t );
                alle_tupel [n++] = t;
            }
        }
    }
}

void drucke_tupel ( TEAM_TUPEL t ) {

    char delimiter = '(';
    for ( int b = 0; b < BITS; b++ ) {
        if ( ist_team_im_tupel ( b, t ) ) {
            printf ( "%c%d", delimiter, b + 1 );
            delimiter = ',';
        }
    }
    printf ( ")" );

}

void drucke_alle_tupel () {

    for ( int i = 0; i < ANZAHL_TUPEL; i++ ) {
        drucke_tupel ( alle_tupel [i] );
        printf ( "\n" );
    }

}

void drucke_spielplan () {

    int i = 0;

    while ( spielplan [i] != 0 ) {
        drucke_tupel ( spielplan [i++] );
        printf ( "\n" );
    }

}

int anzahl_spiele ( int t1, int t2 ) {

    //printf ( "anzahl_spiele: %d %d\n", t1, t2 );

    int n = 0;

    for ( int i = 0; i < naechstes_spiel; i++ ) {
        if ( ( spielplan [i] & (1 << t1) ) && ( spielplan [i] & (1<< t2) ) ) n++;
    }

    //printf ( "anzahl_spiele: %d %d -> %d\n", t1, t2, n );

    return n;

}

int main () {

    printf ( "Start\n" );
    printf ( "Anzahl Tupel=%d\n", ANZAHL_TUPEL );
    //printf ( "sizeof tupel=%d\n", sizeof ( TEAM_TUPEL ) );

    erzuege_alle_tupel ();
    printf ( "Tupel erzeugt\n" );

    //drucke_alle_tupel ();

    printf ( "Erzeuge Spielplan\n" );

    while ( naechstes_tupel < ANZAHL_TUPEL ) {

        TEAM_TUPEL kandidat = alle_tupel [naechstes_tupel++];
        if ( ist_bereits_gespielt ( kandidat ) ) continue;

        int team [3] = { 0 };
        int t = 0;
        for ( int b = 0; b < BITS; b++ ) {
            if ( kandidat & (1 << b) ) {
                team [t++] = b;
            }
        }

        printf ( "\n" ); drucke_tupel ( kandidat ); 
        //printf ( "kandidat: t1=%d t2=%d t3=%d ", team [0], team [1], team [2] ); drucke_tupel ( kandidat ); 
        //printf ( " %d %d %d\n", anzahl_spiele ( team [0], team [1] ), anzahl_spiele ( team [0], team [2] ), anzahl_spiele ( team [1], team [2] ) );
        //printf ( "\n" );

        if ( anzahl_spiele ( team [0], team [1] ) >= MAX_SPIELE ) continue;
        if ( anzahl_spiele ( team [0], team [2] ) >= MAX_SPIELE ) continue;
        if ( anzahl_spiele ( team [1], team [2] ) >= MAX_SPIELE ) continue;

        printf ( " hat überlebt" );

        spielplan [naechstes_spiel++] = kandidat;

    }

    printf ( "\n\nSpielplan\n" );

    drucke_spielplan ();

    printf ( "Schluss\n" );

    return 0;

}
