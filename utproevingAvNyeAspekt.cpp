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
vector<partikkel*> ppVektor;

extern map<int, masse*> * masse::pAlleEnheterMapPeik;
//extern map<int, masse*> alleEnheter;
//}6

void skaffNestePos()
{ //{6 hjelpefunk for å etterligne holdStyrPaaPart
	//nuller ut avstander:
	masse::nullUtAvstanderOgKraft_i_pAlleEnheter();


	for( int i = 1; i <= partikkel::getAntallObjekt() ; i++ )
	{
		// forsikrer meg om at pAlleEnheterMapPeik[i] har verdi (peikerverdi - at peiker er initialisert, og ikkje er null-peiker)
		if( (! (*masse::pAlleEnheterMapPeik)[i]) )  continue;



		(*masse::pAlleEnheterMapPeik)[i] -> kalkulerAvstander();

	// Lag noke alla:
		(*masse::pAlleEnheterMapPeik)[i] -> kalkulerKraftMellomMasseSenter();
	// Lag noke alla:
		(*masse::pAlleEnheterMapPeik)[i] -> kalkulerBane();

/*
 * 	kalkulerAvstander
 * 	kalkulerKraftMellomMasseSenter
 * 	kalkulerBane
 */			

	}
		
} //}6



int mainTestFunk( )
{ //{1 ... }

/*	partikkel P ;
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

	// FUnker ikkje 
	/*
	skinn::useUtskriftsFil_alternativ_S()<<"Jepp. Utskriftsfil s\n";
	skinn::useUtskriftsFil_alternativ_P()<<"Jepp. Utskriftsfil p\n";
	skinn::useUtskriftsFil_alternativ_P().flush(); skinn::useUtskriftsFil_alternativ_S().flush();
	*/
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
/* 	 	ofstream & useUtskriftsFil_alternativ_P( int ptsNr =0 )
	 	skinn::useUtskriftsFil_alternativ_P()<<"Nokre testpartikler: " <<endl; 	
		skinn::useUtskriftsFil_alternativ_P()<< P.getPos() 		 	<<endl; 
		skinn::useUtskriftsFil_alternativ_P()<< P.getFart() 		<<endl;
		skinn::useUtskriftsFil_alternativ_P()<< P.getPaaVirkningsKraft() 	<<endl;
*/
	}


/*
	(*pout)<<"\n\n\n\n";
	koordinat test( 1.1 , 2.1, 3.1, "UtprøvingAvNyeAspekt.testkoord" );
	if( skinn::alternativUtskrift_SkallBool ){
		skrivUtTekstIpts( nAlterativUtkriftPts, test.toString() );
		skrivUtTekstIpts( nAlterativUtkriftPts, P.getPos() .toString() );
		skrivUtTekstIpts( nAlterativUtkriftPts, P.getFart() .toString() );
		skrivUtTekstIpts( nAlterativUtkriftPts, P.getPaaVirkningsKraft() .toString() );

	}else{
		(*pout)<<"else -> skinn::alternativUtskrift_SkallBool == 0\n";
	}
*/
/*  KUK - Kommentert-Ut-Kode //{8 
	//map<int, masse*> * pAlleEnheterMapPeik;  flytta inn i masse... //masse::pAlleEnheterMapPeik = &alle Enheter;

	// DEFINERING AV OBJ.:
	for(int i = 0 ; i< ncUseArg() ; i++ )
	{
		partikkel *A = new partikkel();

		(*masse::pAlleEnheterMapPeik)[A->getId()] = A;
		printf("Fyller *masse::pAlleEnheterMapPeik med part. id. %d \n", A->getId() );
	}


	while(1){
		
		skaffNestePos();
		
		printf(" SKRIV UT (*masse::pAlleEnheterMapPeik)[it] :\n");
		for( int it = 1; it <= masse::getAntallObjekt() ; it++ )
		{
			masse::skrivUt( (*masse::pAlleEnheterMapPeik)[it] );
		}
		
		
		
		//Denne er feit!!! :
		//masse::useAvstandMap(1, 2) = 10e3-10e-7;

		/* / UTSKRIFT!:  KUK - Kommentert-Ut-Kode //{9 
		double verdi=0; 
		for(int i = 1; i <= masse::getAntallObjekt() ; i++ )
		{
			for(int t=1 ; t <= masse::getAntallObjekt() ; t++ )
			{
				if( (*masse::pAlleEnheterMapPeik)[i] && (*masse::pAlleEnheterMapPeik)[t] ) //sjekker om aktuell index er eit part.obj.
				{
					//if( verdi = (*masse::pAlleEnheterMapPeik)[i]->getAvstandTilObjekt( t ) ) 

					if( i == 3 && t == 2 && (verdi = (*masse::pAlleEnheterMapPeik)[i]->getAvstandTilObjekt( t ) ) )
						printf("Avst. fra %d til %d: %f\n", i, t, verdi );
				}
			}
		}
		 *  //}9 * /  


//koordinat K = (*masse::pAlleEnheterMapPeik)[2]->getKraftFraAndreObj(3);
//printf("fra 2 til 3  Kraft: |%f, %f, %f| Avst.: |%f| \n",  K.getVerdi('x'), K.getVerdi('y'), K.getVerdi('z'), (*masse::pAlleEnheterMapPeik)[2]->getAvstandTilObjekt(3) );

sleep(2);

	}//evig while(1)

 *   //}8 */ 

	printf("Avslutter test-run. \n");
	exit(0);	





// KUK - Kommentert-Ut-Kode //{9  -  gruppering-testing
/* 
	vector<masse*> jeje;
	vector<masse*> jeje2;
	vector<masse*> jeje3;
	vector<masse*> jeje4;
	vector<masse*> jeje5;
	jeje  = gruppere( mpMasseVektor );
	printf(" FERDIG MED EN \n");
//	jeje2 = gruppere( jeje );

//	printf(" FERDIG MED TO \n");
//	jeje3 = gruppere( jeje2 );
//	jeje4 = gruppere( jeje3 );
//	jeje5 = gruppere( jeje4 );

	skrivUtGrupper( mpMasseVektor );
	skrivUtGrupper( jeje  );
	printf("\n\n\n");
//	printf(" OG TO: ************  \n");
//	skrivUtGrupper( jeje2 );
//	skrivUtGrupper( jeje3 );
//	skrivUtGrupper( jeje4 );
//	skrivUtGrupper( jeje5 );
//	printf("Legger til en masse \n");

	printf("Antall partikler initiert:\t%d\nAntall grupper initiert:\t%d\nAntall masser initiert: \t%d\n", 
			partikkel::getAntallObjekt(), massePar::getAntallObjekt(), masse::getAntallObjekt() );
*/ //}9
} //}1

// vim:fdm=marker:fmr=//{,//} : fdl=2
