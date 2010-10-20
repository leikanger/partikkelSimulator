//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//  * * * * * * * * * *	  utproevingAvNyeAspekt.cpp - for å teste ut ting uten å ødelegge kildekode.  * * * * * * * * *
//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

//{6 		#include 
// #include <iostream>
#include "partikkelG.h"

//#include "gruppering.h"

#include "masseG.h"
#include "main.h"


#include <math.h> 	// for sin og cos
#include <cstdlib>	// for rand og srand
#include <time.h>		// tor rand seed
#include <pthread.h>
//}6
using namespace std;
//{6 		eksterne variable, globale variablar osv.

//extern double allePartikkelXYZ[3][ANTALLPARTIKLER];
//extern int antallPartiklerInitiert; 
extern bool skinn::alternativUtskrift_SkallBool;
//extern ofstream *pUtskriftsFil;
//extern string strAlternativUtskriftFilAdr;
extern void skrivUtGrupper(vector<masse*>); //extern?
extern void skrivUt(string, char); ///XXX ? kor kjem den fra? kem bruker den?

extern const int ncUseArg(int argTall =10);  //Isteden for variable. Init foerste gang den blir kalt. merk & i returverdi const int &
// Var: extern const int & ncUseArg(int argTall =10);  //Isteden for variable. Init foerste gang den blir kalt. merk & i returverdi const int &

//int clearScreen(int);
vector<masse*> mpMasseVektor;
vector<axon*> ppVektor;

extern map<int, masse*> * masse::pAlleEnheterMapPeik;
//extern map<int, masse*> alleEnheter;
//}6



/*
void skaffNestePos()
{ //{6 hjelpefunk for å etterligne holdStyrPaaPart
	//nuller ut avstander:
	masse::nullUtAvstanderOgKraft_i_pAlleEnheter();


	for( int i = 1; i <= axon::getAntallObjekt() ; i++ )
	{
		// forsikrer meg om at pAlleEnheterMapPeik[i] har verdi (peikerverdi - at peiker er initialisert, og ikkje er null-peiker)
		if( (! (*masse::pAlleEnheterMapPeik)[i]) )  continue;



		(*masse::pAlleEnheterMapPeik)[i] -> kalkulerAvstander();

	// Lag noke alla:
		(*masse::pAlleEnheterMapPeik)[i] -> kalkulerKraftMellomMasseSenter();
	// Lag noke alla:
		(*masse::pAlleEnheterMapPeik)[i] -> kalkulerBane();
	}
		
} //}6
*/


int mainTestFunk( )
{ //{1 ... }

/*	axon P ;
	(*pout) << P.getPos() 		    <<endl; 
	(*pout) << P.getFart() 		    <<endl;
	(*pout) << P.getPaaVirkningsKraft() <<endl;
*/
//	koordinat A(1.1,2.2,2.2,"jejeje, Kjempelang type lleeeeenger!");
//	(*pout) << A <<std::endl;
	

	clog<<"j clog\n";
	cerr<<"j cerr - unbuffered\n";


//	(*pout)<<"no er eg i p - eller .. *pout\t";
//	skinn::useUtskriftsFil_alternativ_S()<<"useUtskriftsFil_alternativ_S(SSS)";


	//if( skinn::clearScreen( 1 ) ) cerr<<"errormld fra skinn::clearScreen(3)\n" ;
	//if( skinn::clearScreen( 5 ) ) cerr<<"error qwer2315 utprøving.\n";
	

	//funker ikkje? XXX Her er noko TODO
	if( skinn::alternativUtskrift_SkallBool )  (*skinn::altOut_p)<<"altOut\n";  (*pout)<<"pout\n";
	pout->flush(); skinn::altOut_p->flush();

exit(8);
//DEI FUNKER IKKJE
	(*pout)<<"Prøver de ulike stømmane mine.\n";
	//if( skinn::alternativUtskrift_SkallBool ) skinn::useUtskriftsFil_alternativ_P()<<"skinn::useUtskriftsFil_alternativ_P()";
	if( skinn::alternativUtskrift_SkallBool ) cDEBUG<<"\n\n skinn::alternativUtskrift_SkallBool == true \n\n\n"; 
	else 				cDEBUG<<"\n\n skinn::alternativUtskrift_SkallBool == false\n\n\n";
//	if( skinn::alternativUtskrift_SkallBool ) skinn::useUtskriftsFil_alternativ_S()<<"skinn::useUtskriftsFil_alternativ_S()";

//	skinn::useUtskriftsFil_alternativ_P()<<"alternativ p\n";
//	skinn::useUtskriftsFil_alternativ_S()<<"alternativ s\n";
//	cerr<< "Her funker det ikkje heilt med støymane.. qwer693\n";
//	cerr<< "HER FUNKER DET IKKJE, sa eg. qwer693";


	if( skinn::alternativUtskrift_SkallBool ){
	}


	printf("Avslutter test-run. \n");
	exit(0);	





} //}1


// vim:fdm=marker:fmr=//{,//} : fdl=2
