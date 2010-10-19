//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//  * * * * * * * * * * * 	masseG.cpp - implementere masse-klasse. 	  * * * * * * * * * * * * * * * * *
//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Filbeskrivelse / kommentar //{1
// masseG.cpp/h - inneholder klasse som fungerer som en forfader til partikkel- og massePar- klassene.
//}1

// 		#include //{1 
// #include <iostream>
#include "partikkelG.h"

//#include "gruppering.h"

#include "masseG.h"
#include "main.h"

#include <math.h> 		// for sin og cos
#include <cstdlib> 		// for rand og srand
#include <time.h>		// tor rand seed
#include <pthread.h>
//}1

using namespace std;


// Kommentar - vidare plan: //{6
// Lag denne static inne i partikkel i stadenfor.// var i partikkel: double alle PartikkelXYZ[3][ANTALLPARTIKLER];				// posisjonen til alle partiklane.
// gjør static i partikkel: double avstandMellomPartikler[ANTALLPARTIKLER][ANTALLPARTIKLER];		// avstanden mellom to partikler
// gjør static i grupper: double avstandMellomGrupper[ANTALLGRUPPER][ANTALLGRUPPER];
// static??? extern double kraftMellomMasseArray[3][ANTALLGRUPPER][ANTALLGRUPPER];

// static??? : double kraftMellomPartArray[3][ANTALLPARTIKLER][ANTALLPARTIKLER];
// gjør static :/ int antallPartiklerInitiert=0;
// blir ikkje brukt i akkurat masse: //}6

int masse::antallObjekterInitiert = 0;


// Fyller argument(peiker) med pos til o.
koordinat masse::getPos( ) const
{ //{1... } 
	return mPos;
	/*  KUK - Kommentert-Ut-Kode //{3 
	// var : void masse::getPos(double* fyllMeg) const
	fyllMeg[0] = mPos.getVerdi('x');
	fyllMeg[1] = mPos.getVerdi('y');
	fyllMeg[2] = mPos.getVerdi('z');   /// XXX HER 
	 *   //}3 */ 
} //}1

void masse::initStaticVariable() 
{
	// static void initStaticVariable() - init av avstandTilAndreObjekt, pPaavirkaAvDenneKraftFraAndreObj, 
 	
	for( int iterEnhId = 1; iterEnhId <= masse::antallObjekterInitiert ; iterEnhId++ ){
	 
	 	if( ! (*pAlleEnheterMapPeik)[iterEnhId] ) continue; 		// sikrer mot nullpeiker i (*pAlleEnheterMapPeik)[andreid]
		

		for(int andreid = 1; andreid <= masse::antallObjekterInitiert ; andreid++ )
		{

			if( iterEnhId == andreid ) continue; //gidder ikkje legge til kraft den påvirker seg sjølv med..

			if( ! (*pAlleEnheterMapPeik)[andreid] ) continue; 	// sikrer mot nullpeiker i (*pAlleEnheterMapPeik)[andreid]

			if( ! (*pAlleEnheterMapPeik)[iterEnhId]->pPaavirkaAvDenneKraftFraAndreObj[andreid] ){

				//printf("(*pAlleEnheterMapPeik)[%d]->pPaavirkaAvDenneKraftFraAndreObj[%d] mangler. Legger til. (iterEnhId, masse). Mld. qwer253\n"

				(*pAlleEnheterMapPeik)[iterEnhId]->pPaavirkaAvDenneKraftFraAndreObj[andreid] = new koordinat(0.0, 0.0, 0.0);
				// Trengs når legger til meir her? : continue; 
			}else{
				(*pAlleEnheterMapPeik)[iterEnhId]->pPaavirkaAvDenneKraftFraAndreObj[andreid]  ->nullUt();
				pDEBUG<<"Her qwer794@masseG.cpp";
			}

		}
	}
}

void masse::nullUtAvstanderOgKraft_i_pAlleEnheter()
{
	 for( int iterEnhId = 1; iterEnhId <= masse::antallObjekterInitiert ; iterEnhId++ )
	 {
		
		// Kva med / er det mulig : (diskret) Hopp i kraft? Eller er Kraft kontinuerlig?
		// uavhengig av virkeligheten: Nuller ut kraft discret.
		// :
		/*  KUK - Kommentert-Ut-Kode //{3 
		(*masse::pAlleEnheterMapPeik)[i]->mF[0] = 0;
		(*masse::pAlleEnheterMapPeik)[i]->mF[1] = 0;
		(*masse::pAlleEnheterMapPeik)[i]->mF[2] = 0;
		 *   //}3 */ 
		 (*masse::pAlleEnheterMapPeik)[iterEnhId]->mF.nullUt();
		 // asdff XXX Har ikkje testa funk nullUt()
		 // Bruker no ikkje neste funksjon. Driver med anna no. Gjør om du har dødtid.



	 	if( ! (*pAlleEnheterMapPeik)[iterEnhId] ) continue;
		
		for(int andreid = 1; andreid <= masse::antallObjekterInitiert ; andreid++ )
		{
	 	 	if( ! (*pAlleEnheterMapPeik)[andreid] ) continue; // sikrer mot nullpeiker i (*pAlleEnheterMapPeik)[andreid]
			//kommer bare hit med verdi i *pAlleEnheterMapPeik
			//printf("kommer bare hit med verdi i *pAlleEnheterMapPeik : "); cout << (*pAlleEnheterMapPeik)[andreid] <<endl;
			//skriver ut litt for mange ganger. (sjekk sjølv)

			(*pAlleEnheterMapPeik)[iterEnhId]->avstandTilAndreObjekt[andreid]  	     	 = 0.0;
		
		
		
		

			if( ! (*pAlleEnheterMapPeik)[iterEnhId]->pPaavirkaAvDenneKraftFraAndreObj[andreid] && (iterEnhId != andreid) ){
				printf("(*pAlleEnheterMapPeik)[%d]->pPaavirkaAvDenneKraftFraAndreObj[%d] mangler. Legger til. (iterEnhId, masse). Mld. qwer253\n"
																		, iterEnhId, andreid);
				
				//forsøke å ordne:
				//Dessne testane er allerede tatt:  	if( pAlleEnheterMapPeik[i] && pAlleEnheterMapPeik[andreid] ) så:
				(*pAlleEnheterMapPeik)[iterEnhId]->pPaavirkaAvDenneKraftFraAndreObj[andreid] = new koordinat(0.0, 0.0, 0.0);

				continue; 
			}else if( iterEnhId == andreid ) continue; 
			else{
	 
				//Har feil: XXX Veit ikkje kva det var, eller om det er der no. men ser ok ut.
				((*pAlleEnheterMapPeik)[iterEnhId]->pPaavirkaAvDenneKraftFraAndreObj[andreid])->nyeVerdier(0.0, 0.0, 0.0);
				//pDEBUG << "jeje";
			}
		}
	 }
}

void masse::nullUtFraForrigeIterasjon()
{
	//denne er med siden den over er static.
	mF.nullUt();
	for(int i = 0; i < getAntallObjekt() ; i++ )
	{
		// sjekk om dette kan være dummt. Andre funk sjekker vel samme sjekk som den under. Denne = false om avstandTilAndreObjekt[i] =0...
		if(avstandTilAndreObjekt[i]) avstandTilAndreObjekt[i] = 0;
		if(pPaavirkaAvDenneKraftFraAndreObj[i]) pPaavirkaAvDenneKraftFraAndreObj[i] = 0;
		// om alt er greit med det over, så er det sikkert ikkje naudsynt med if(..)
	}
}

// Gjør ingenting i masse. Meir i partikkel. 
// Tok han med i masse som virtuell funk fordi eg eventuellt skal bruke funk i seinare obj, og kalle desse i funksjoner som skal nedarves.
void masse::kalkulerBane()
{ //{1... } 
	// KAN EGENTLIG BEGRENSE denne til å bare være i partikkel..
	//
	// må definere den siden det er virtual void. For partikkel er den som før. Heile programmet funker som før, sjølv om eg har tatt med arv. partikkel -> masse   Bra!!
	// Kan prøve å gjøre heile masse til virtuell klasse..

	// kva må gjøres for en imaginær masse??
	// summer krefter i det minste:
	printf("summer eller noke..\n");	
} //}1

// Aktuell, men ikkje implementert her (som arvbar funk) enda.
/* void masse::kalkulerAvstander()
{ //{1... } 


	// * 0 0 0 0 ' ** * * * * * * * * * * * 0 0 0 0 
	//  		Veldig aktuell!!
	//  *0 0 0 0 * * * * * * * * * * ** * * 0 0 0 0

	//men ikkje implementert enda som arvbar funk.

 	printf(":feil-> kjører kalkulerAvstander() i masse\n"); usleep(99);
} //}1 */
 
//utkommentert kode.//{1
/* 
{
	double nesteUtregnaAvst;

	// Finn avstander. 	//sjekker bare partikler etter seg selv. Tidligare har allerede funnet avstanden
	avstandMellomObjekt[enhetsId][enhetsId] = 0;	// er 0 unna seg selv.
	
	for(int i = 0; i < static: ANTALLPARTIKLER; i++){
		
		
		if( i == (enhetsId)) continue; 

		nesteUtregnaAvst =	sqrt(     pow(enhetsPos[0] - masse[i].pos (0) ,2) 
						+ pow(enhetsPos[1] - masse[i].pos (1) ,2) 
						+ pow(enhetsPos[2] - masse[i].pos (2) ,2)   );
		avstandMellomMasser[partikkelId][i] = nesteUtregnaAvst ;
		avstandMellomMasser[i][partikkelId] = nesteUtregnaAvst ;

	}
}

// Aktuell, men ikkje implementert her (som arvbar funk) enda.
int masse::kalkulerKraftMellomMasser()
{
	//G*M*\delta t

	// gjør static i partikkel: kraftMellomPartArray[0][partikkelId][partikkelId] = 0; 	// påverker seg selv med null kraft.


	// For løkke for å finne alleredekrasja. ( gjelder bare for partikkel )
	for(int i = 0; i< antallMasserInitiert; i++)
		if....	//gjelder bare for part : if(status == 1 || (( status == 0 ) && ((avstandMellomPartikler[partikkelId][i] < MINSTEAVSTAND) )) )//status 1: den har krasja, -1 at den allerede har regna ut.
	}


//
//ikkje endra herifra:
	for(int iter=0 ; iter < partikkelId; iter++){

		
		double divident = 1/pow(avstandMellomPartikler[partikkelId][iter], 3);
		
		// X - verdiar (partikkelF[0]:
		double kraftMellomPartUtregningX = G*(enhet[iter].pos(0) - enhetsPos[0]  ) / divident;//Skal være i 3-je
		// Y - verdiar (partikkelF[1]) 		partikkelF[1] += G*(allePartikkelXY[1][iter] - partikkelPos[1]) / pow(avstandMellomPartikler[partikkelId][iter],3);
		double kraftMellomPartUtregningY = G*(enhet[iter].pos(1) - enhetsPos[1]  ) / divident;//Skal være i 3-je
		//Z - retn
		double kraftMellomPartUtregningZ = G*(enhet[iter].pos(2) - enhetsPos[2]  ) / divident;//Skal være i 3-je
		
		//(*pout) << "kraft mellom part.[" <<kraftMellomPartArray[0] << ", " << kraftMellomPartArray[1] <<"]\n"; 
		//(*pout) << "avstand mellom part.1 og meg[" <<avstandMellomPartikler[0][partikkelId] <<"]\n"; 

		
		// kopierer F_ac til F_ca
/ * STATIC* /	kraftMellomEnhetsArray[0][iter][enhetsId] = -kraftMellomUtregningX;
		kraftMellom..
		kraftMellom..
		kraftMellom..
		kraftMellom..
	}
	
	status = 0;
	return 0;	
}// ikkje endra siste halvdel..

*/ //}1

void masse::skrivUt( masse *inputMasse ) //ikkje const siden den er static
// Skriver ut masse, id, pos, obj.type. og evt. underobj. //{1
{  
	
	printf("Id: %d,\t\tPos [%f,%f,%f],\t masseTotal: %f  \t\tAv type:\t", inputMasse->getId(), 
			inputMasse->pos(0), inputMasse->pos(1), inputMasse->pos(2), inputMasse->getMasseTotal() ); 
	(*pout) <<inputMasse->getObjektType( true ) 
	 	  <<"\n";
} //}1

/*
 * gjør om til () - tom argliste. og returverdi :  koordinat */
/// XXX  VIKTIG . men ikkje viktig nok til NO... XXX
koordinat masse::getFart() const
{ //{1
	return mV;
	/*  KUK - Kommentert-Ut-Kode //{3 
	// var av type: returverdi void, arg double [3] 
	fyllMeg[0] = mV.getVerdi('x');
	fyllMeg[1] = mV.getVerdi('y');
	fyllMeg[2] = mV.getVerdi('z');
	//  //}3 */ 
} //}1

// vim:fdm=marker:fmr=//{,//} : fdl=2
