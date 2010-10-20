//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//  * * * * * * * * * *	  partikkelG.cpp - Alt som har med partikkel-klassa å gjøre.  * * * * * * * * * * * * * * *
//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Filbeskrivelse / kommentar //{1
/*
 * 	Inneholder partikkel-klasse, som er arvet fra masse.
 */
//}

// 		#include //{1 
// #include <iostream>
#include "partikkelG.h"

//#include "gruppering.h"

#include "masseG.h"
#include "main.h"


#include <math.h> 	// for sin og cos
#include <cstdlib>	// for rand og srand
#include <time.h>		// tor rand seed
#include <pthread.h>
//}1
using namespace std;

//extern variabel deklarasjoner//{1
//extern double avstandMellomGrupper[ANTALLGRUPPER][ANTALLGRUPPER];
extern bool grupperPartiklerBool;
//}1
// mutex og andre varibler. 	 //{1
pthread_mutex_t posmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexVent1 = PTHREAD_MUTEX_INITIALIZER;
pthread_t litenTraa[ANTALLTRAADER];
//double allePartikkelXYZ[3][ANTALL PARTIKLER];				// posisjonen til alle partiklane. 				
//double allePartikkelXYZiMasseFjaerStartTidspunkt[3][ANTALL PARTIKLER]; 	// brukes til å kopiere den over ( når bruker trykker space ) 
bool pauseSystemBool = false;
//double avstand MellomPartikler[ANTAL LPARTIKLER][ANTALL PARTIKLER];		// avstanden mellom to partikler 				
int axon::antallObjekterInitiert = 0;
//double kraftMellomPartArray[3][ANTALL PARTIKLER][ANTALL PARTIKLER];
extern bool skinn::globalAvluttProgramVariabel; 
//}1


axon::axon()
{ // ... } //{1
	
	// tilfeldig tall seed
	srand(rand()+time(NULL));

	mPos.nyeVerdier( ((0.01 * (rand()%200)) -1) * GRENSE ,  ( (0.01 * (rand()%200)) -1) * GRENSE  	,  ( (0.01 * (rand()%200)) -1) * GRENSE , "Posisjon " );
	mV.nyeVerdier( 	 mPos.getVerdi('y')*STARTFART_TANG   ,  mPos.getVerdi('x')*STARTFART_TANG  	,  mPos.getVerdi('x')*STARTFART_TANG    , "Fart " );

	//masseTotal =  0.1 *( rand() % 20 ) +1;

	

	// slik at det er lenge siden krasjtid når den krasjer.
	krasjtid = time(0);
	status = 0;	
	
	antallObjekterInitiert++;
	
//	indexRekkefoelgeFasitForAvstVektor.push_back( enhetsId );

	/*printf("Index rekkefølge så langt: \n");
	for( vector<int>::const_iterator i = indexRekkefoelgeFasitForAvstVektor.begin() ; i != indexRekkefoelgeFasitForAvstVektor.end() ; i++ )
		printf("Index %d \n", (*i) ); // evt indexRekkefoelgeFasitForAvstVektor[i]
		*/
} //}1


// XXX IKKJE I BRUK.. XXX
void* skallFunkForTraad(void* vpSkydel)
{ // ... } //{1
			// her har vi allerede delt opp i tråder.
			// og delt opp sky  i deler.
return 0;
	/****************************************************************************************************************************
	 *
	 *
	 * 	DRIT:
	 * 		Dette må lages igjen. Tenk på 8-core til koch..
	 * 		Foreløpig (driver med anna, så dropper dette) kjører uten småtraader.
	 * 		Uansett nesten synkront uansett. Splitter for tråder, men så venter på at alle er ferdig
	 * 			før eg fortsetter. Dårlig.
	 *
	 * *************************************************************************************************************************/
	// gammelt start:
		vector<masse*> * skydel = (vector<masse*>*) vpSkydel ;


		for(vector<masse*>::iterator VI = skydel->begin(); VI != skydel->end(); VI++){
			(*VI)->kalkulerAvstander();
		}

	// gammelt slutt
		
} //}1

void *holdStyrPaaPart(void*) //void* (arg) er ikkje brukt foreløpig..
{ // ... } //{1
/*  KUK - Kommentert-Ut-Kode //{9

//	vector<masse*> lSkyDel[ANTALLTRAADER]; // bruker ikkje enda/lenger.

	
	//neste 15 linjene: gammel array-metode..
//	int it = 0;	

	// lag en mekanisme for å ikkje kjøre denne kvar gang / for å finne ut når det er naudsynt å kjøre denne..
	// DETTE ER DRIT METODE!! FINN PÅ SMARTARE!!
	/ *
	for( int i = 0; i < ANTALLTRAADER ; i++ )
	{
		for( ; it< (1+i) * (masse::getAntallObjekt() / ANTALLTRAADER) ; it++ )
		{
	 		if( (*masse::pAlleEnheterMapPeik)[it] ) lSkyDel[i].push_back( (*masse::pAlleEnheterMapPeik)[it] );
		}		
	}
	* /


/*
 *  Venter litt. Fikser seinere.
 *   lager for tida ikkje mange kalk.tråder.
 *
	static int antallEnheterNaarSkyBleDeltForrigeGang = 0;
	if( masse::getAntallObjekt() != antallEnheterNaarSkyBleDeltForrigeGang )
	{	
		//grupper sky.
		int antallPerTraad = masse::getAntallObjekt() / ANTALLTRAADER ;
		int traadNr=0;
		int sisteEnhIforrigeTraad = 0;


		printf("antallPerTraad %d, sisteEnhIforrigeTraad %d \n", antallPerTraad, sisteEnhIforrigeTraad);

		for( int it = 1; it <= masse::getAntallObjekt() ; it++ )
		{
			if( ! ( *masse::pAlleEnheterMapPeik)[it] ) continue; 	//sjekk om peiker har verdi. ellers continue.
										//funker.
			printf("it %d getAntallObjekt() %d  \n", it, masse::getAntallObjekt() );

			lSkyDel[traadNr].push_back( (*masse::pAlleEnheterMapPeik)[it] );
	 		
			//grov inndeling. Nøyaktig oppdeling er ikkje så viktig (trur eg) / (foreløpig)
			if( it >= sisteEnhIforrigeTraad + antallPerTraad )
			{
	 			sisteEnhIforrigeTraad = it;
				if(traadNr != ANTALLTRAADER-1)
					traadNr ++;
				printf(" %d  \n", traadNr);
			}
		}
		//oppdaterer antallEnheterNaarSkyBleGruppert
		antallEnheterNaarSkyBleDeltForrigeGang = masse::getAntallObjekt();
	}
	
	// skriv ut lSkyDel[] , for å sjå om de er rett fordelt...
*/
//}9 

	bool HarSkrevetUtGrupperPart = false;
	while(1){	

		//nuller ut avstand og kraft i alle partikler.
		masse::nullUtAvstanderOgKraft_i_pAlleEnheter();


		//for å ungå orden i avsluttinga av program:
		if( skinn::globalAvluttProgramVariabel ) pthread_exit(0);

		//Dette er noko å drive med: (bedre tråding, bedre utnytting av 8core til koch, mindre syncron tråding. osv.) Å_GJØRE
/*		for( int i = 0; i < ANTALLTRAADER ; i++ ){
			pthread_create( &litenTraa[i] , NULL, skallFunkForTraad,  & lSkyDel[i] );
		}
		for( int i = 0; i < ANTALLTRAADER ; i++ ){
			pthread_join( litenTraa[i], NULL );
		}
*/ 		// istaden gjør eg: (driter i oppdeling til tråder, og kjører bare:)
		
		if( grupperPartiklerBool && HarSkrevetUtGrupperPart == false ){
			printf("GRUPPERER PARTIKLER.\n\n\n");
			HarSkrevetUtGrupperPart = true;
 			printf("Funker ikkje heilt enda med grupperPartikler. Prøv uten -g for å unngå denne feilmeldinga. \n");
			/*
			if( grupperPartiklerBool )
			{
				// skal vm:  heileSkyGruppertIPar = gruppere( heileSky );
				//grupperPartiklerBool = false;
			}
			*/
		}
	




		// Går dette bra? 
		// XXX Istaden for å ferdigstille alle avstander, fortsetter eg på å bruke desse før de er ferdig. Skummelt XXX
		// Nei. Går tilbake til å iallefall gjøre ferdig avstandTilAndreObjekt - map først.

		// Kan gå tilbake til sekvensielt:

		for(int iter=1; iter <= masse::getAntallObjekt() ; iter++ )
		{
			if( ! (*masse::pAlleEnheterMapPeik)[iter] ) continue; 	//guard mot segf.
			
		//	printf("\t\t\t\t\t\t\t\tKALKULERER AVSTANDER: \n");
			//(*pout)<<(*masse::pAlleEnheterMapPeik)[iter] <<endl;
			(*masse::pAlleEnheterMapPeik)[iter]->kalkulerAvstander();
			//printf("status: %d->kalkulerAvstander() \n", iter);
	 
		}

		for(int iter=1; iter <= masse::getAntallObjekt() ; iter++ )
		{
			if( ! (*masse::pAlleEnheterMapPeik)[iter] ) continue; 	//guard mot segf.
				

		//	printf("\t\t\t\t\t\t\t\tKALKULERER KREFTER: \n");
			//printf("id: %d \n", (*masse::pAlleEnheterMapPeik)[i]->getId() );
		 	(*masse::pAlleEnheterMapPeik)[iter]->kalkulerKraftMotNeuronSenter();
		
	
		//	printf("\t\t\t\t\t\t\t\tSUMMERER KREFTER TIL mF og integrerer opp: \n");
			(*masse::pAlleEnheterMapPeik)[iter]->kalkulerBane();

		}


	

		
		 //* Kan være eg ikkje trenger dette:
		 //* XXX
		 
		// MUTEX LOCK
/*		pthread_mutex_lock( &posmutex ); 	

		for(int i = 0; i < (=???) masse::getAntallObjekt(); i++){ 		// HER  FEIL IGJEN. allePartikkelXYZ er statisk, og takler ikkje dynamisk
			// FEIL Å BRUKE STATISK ARRAY HER.
			// XXX BEGYNN MED masse(obj).avstandTilAndreObjekt istaden!	
			allePartikkelXYZ[0][i] =(*masse::pAlleEnheterMapPeik)[i]->pos(0);
			allePartikkelXYZ[1][i] =(*masse::pAlleEnheterMapPeik)[i]->pos(1);
			allePartikkelXYZ[2][i] =(*masse::pAlleEnheterMapPeik)[i]->pos(2);
			//(*pout) << "p _vec_part_sky[i].pos : [" <<p _vec_part_sky[i].pos(0) <<", " <<p _vec_part_sky[i].pos(1) <<"]\n";
		}

		// mutex unlock
		pthread_mutex_unlock( &posmutex ); //posmutex
*/		

	} //}3
} //}1


void axon::kalkulerAvstander(vector<masse*> vmpArgument)
{
	 //dirty. men for no, ok. Driver med major omvelting.
	 axon::kalkulerAvstander();
}

// en todo inni her.
void axon::kalkulerAvstander()
{ // ... //{1 }

	double nesteUtregnaAvst;

 	// null fra seg sjølv.	
//	avstand MellomPartikler[enhetsId][enhetsId] = 0;	// er 0 unna seg selv. XXX
	

		//sjekker bare partikler etter seg selv. Tidligare har allerede funnet avstanden
		//for(int i = enhetsId; i < AN TALLPARTIKLER; i++){
	for(int i = 1; i <= masse::getAntallObjekt() ; i++){ 									// HER XXX

		if( ! (*masse::pAlleEnheterMapPeik)[i] ) continue; // sikrer mot 0-peiker(tomme pAlleEnheterMapPeik-slots).

		//{
		// XXX Legg til sjekk om verdi allerede finnes på andre sida:
		// 	- a->b  avst. == b->a avst. Sjekk om b->a er regna ut.
		// 	TODO Husk å nulle ut avstander i start(før) kvar iterasjon i tid.
		// 	da funker neste linja. Når du har gjort det, slett TODO //}
		/* trur denne gjør jobben: 
		 *
		  	Ser bra ut! men; no er det trålaust i testinga. Får sjå korleis det går når vi får seriøs action!

		*/
		// XXX sjekker om avstand er kalkulert ut allerede, fra andre sida/kanten..
		if( nesteUtregnaAvst = (*masse::pAlleEnheterMapPeik)[i]->getAvstandTilObjekt(enhetsId) )
		{
			avstandTilAndreObjekt[i]  	   = nesteUtregnaAvst;
			//p DEBUG<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\tjess. FANT avst " <<i <<"->" <<enhetsId <<"og slepper å regne ut på nytt fra " 	<<enhetsId <<"->" <<i <<endl;
			continue;
		}



		if( ! (*masse::pAlleEnheterMapPeik)[i] ) continue; // 0-peik

		if( i == (enhetsId) )
		{
			nesteUtregnaAvst = 0;	 	
		}else{
			nesteUtregnaAvst =	sqrt(     pow(mPos.getVerdi(0) - (*masse::pAlleEnheterMapPeik)[i]->pos(0) ,2) 
							+ pow(mPos.getVerdi(1) - (*masse::pAlleEnheterMapPeik)[i]->pos(1) ,2) 
							+ pow(mPos.getVerdi(2) - (*masse::pAlleEnheterMapPeik)[i]->pos(2) ,2)   );
		}
		
		//enhetsid er meg. i er den andre.
		if( !(*masse::pAlleEnheterMapPeik)[i] ) throw feil_i_objektId( "(*masse::pAlleEnheterMapPeik)[i] partikkelG,cpp:l.320 qwer3242" );

/*XXX*/		avstandTilAndreObjekt[i]  	   = nesteUtregnaAvst;
/*XXX*/		masse::useAvstandMap(i, enhetsId)  = nesteUtregnaAvst;
		//avstand MellomPartikler[enhetsId][i] = nesteUtregnaAvst ;
		//avstand MellomPartikler[i][enhetsId] = nesteUtregnaAvst ;

	}
} //}1


/*
void axon::kollisjon( int andrePartikkelId, bool denneFunksjonErKallaFraUtsida =true )
{
	//XXX Vurderer å flytte inn i masse - klassa...
	//
	
	//partikkel *pTemp= static_cast<partikkel*>(p Part[andrePartikkelId])  ;
	axon *hiaxonen = static_cast<axon*> ( (*masse::pAlleEnheterMapPeik)[andrePartikkelId] );

	 //TODO legg inn feilsjekking. Kanskje noke alla:
	 //if( ! ( pTemp = static_cast<axon*>(p Part[andrePartikkelId]) )  ) throw feil_i_objektId("I kollisjon: Leiter etter axon m. ukjendt obj. id.");

	 if( !hiaxonen )  throw feil_i_objektId("I kollisjon: Leiter etter axon m. feil i id, eller av anna grunn (*0)");//for å styre unna segf.

	 //axon::kollisjon( pTemp );

	double hinPartikkelPos[3];

	if( !ELASTISKEKOLLISJONER ){ return; }  //Ikkje elastiske støt? Deiligare med, men funker ikkje enda..
	else{
		
	
	// KARL SIN FORMEL:

		double hiMasseVerdi;
		//double hinFarta[3];
		koordinat hiFart;

		// gjør fra pInput-> til ppart[i]-> , der i er inputid-int som skal komme som arg.
		hiFart = hiaxonen->getFart();
		hiMasseVerdi = hiaxonen->getMasseTotal();
		
		double retnFaktorX =  (( masseTotal - hiMasseVerdi) + 2 * (hiMasseVerdi * hiFart['x']) )     /   (hiMasseVerdi + masseTotal);
		double retnFaktorY =  (( masseTotal - hiMasseVerdi) + 2 * (hiMasseVerdi * hiFart['y']) )     /   (hiMasseVerdi + masseTotal);
		double retnFaktorZ =  (( masseTotal - hiMasseVerdi) + 2 * (hiMasseVerdi * hiFart['z']) )     /   (hiMasseVerdi + masseTotal);
		koordinat retnFaktor( retnFaktorX, retnFaktorY, retnFaktorZ );
		mV = mV  *  retnFaktor;
		//XXX ikkje heilt sikker på om denne funker etter overg. fra double[3] til koordinat


	// SLUTT FORMEL

	// Gjør det med andre axon også:
	 	if( denneFunksjonErKallaFraUtsida ) 		//for å unngå PING_PONG
			hiaxonen->kollisjon( enhetsId, false ); //kollisjon med meg. 
		//tatt med en boolverdi for å unngå pingpong-effekt.

		//himassa->mV [0] = ( himassa->mV [0] * (hiMasseVerdi - masseTotal) + 2 * masseTotal * mV [0])     /   (hiMasseVerdi + masseTotal);
		//himassa->mV [1] = ( himassa->mV [1] * (hiMasseVerdi - masseTotal) + 2 * masseTotal * mV [1])     /   (hiMasseVerdi + masseTotal);
		//himassa->mV [2] = ( himassa->mV [2] * (hiMasseVerdi - masseTotal) + 2 * masseTotal * mV [2])     /   (hiMasseVerdi + masseTotal);


	// endre status og tid.
	// Skjer også i hiaxonen->kollisjon...
 	//	   hiaxonen->status = -1;
				  status = -1;
	//	 hiaxonen->krasjtid = time(0);
				krasjtid = time(0);

	}
}
*/

/*
void axon::kollisjon(masse* mpInput)
{ // ... } //{1

	double hinPartikkelPos[3];

	if( !ELASTISKEKOLLISJONER ){ return; }  //Ikkje elastiske støt? Deiligare med, men funker ikkje enda..
	else{
		
	
	// KARL SIN FORMEL:

		double hiMassa;
		double hinFarta[3];

		// gjør fra pInput-> til ppart[i]-> , der i er inputid-int som skal komme som arg.
		mpInput->getFart(hinFarta);
		hiMassa = mpInput->getMasseTotal();

		mV [0] = ( mV [0] * ( masseTotal - hiMassa) + 2 * hiMassa * hinFarta[0])     /   (hiMassa + masseTotal);
		mV [1] = ( mV [1] * ( masseTotal - hiMassa) + 2 * hiMassa * hinFarta[1])     /   (hiMassa + masseTotal);
		mV [2] = ( mV [2] * ( masseTotal - hiMassa) + 2 * hiMassa * hinFarta[2])     /   (hiMassa + masseTotal);
		//TODO legg sammen utregninger her. trenger bare gange med samme tallet på alle, og lese ut x-y-z-verdiane på før-farta...

	// SLUTT FORMEL


	// Gjør det med andre axon også:
		mpInput->mV [0] = ( mpInput->mV [0] * (hiMassa - masseTotal) + 2 * masseTotal * mV [0])     /   (hiMassa + masseTotal);
		mpInput->mV [1] = ( mpInput->mV [1] * (hiMassa - masseTotal) + 2 * masseTotal * mV [1])     /   (hiMassa + masseTotal);
		mpInput->mV [2] = ( mpInput->mV [2] * (hiMassa - masseTotal) + 2 * masseTotal * mV [2])     /   (hiMassa + masseTotal);



	// endre status og tid.
	/* XXX skal være med!
	 * mpInput->status = -1;
			   status = -1;
		mpInput->krasjtid = time(0);
			   krasjtid = time(0);
* /

	}
	printf(" HER \n");
} //}1 
*/

// Lag variant med sammensmelting også. Kanskje i masseklasse?. mV+=hinP.mV, pos, masseTotal, varme++(evt), slett hin axon fra allePartikler*vektor[nok?], 
// mF?, antallObjektInitiert--, osv.

int axon::kalkulerKraftMotNeuronSenter() 
{ // ... } //{1

	// Løkke for å finne alleredekrasja.
	for(int i = 1; i<= masse::getAntallObjekt() ; i++)
	{
		if(i == enhetsId){ continue; }
		
		if( ! (*masse::pAlleEnheterMapPeik)[i] ) continue;

	
		/* XXX :
	 	//status 1 tyder at den har krasja, -1 at den allerede har regn ut resultat.
		if(status == 1 || ((status == 0) && ((*masse::pAlleEnheterMapPeik)[enhetsId]->getAvstandTilObjekt(i) < MINSTEAVSTAND)) )
		{
			if( time(0) - krasjtid  > 1 ) { 
				kollisjon( i );	
				printf(" KOLLISJON!! DO IT! \n");
			}

			return 0;
				
		}
		*/
	}

	

	for(int iter=1 ; iter < masse::getAntallObjekt() ; iter++){ //var bare: opp til enhetsId
		
		if(iter == enhetsId) continue;

		//double divident = 1/pow(avstandMellomPartikler[enhetsId][iter], 3);
		double divident =     pow( avstandTilAndreObjekt[iter], 3);

		//mF [1] += G*(allePartikkelXY[1][iter] - mPos [1]) / pow(avstand MellomPartikler[enhetsId][iter],3);
		//XXX fiks dette slik at pos() returnerer en koordinat og vi kan skrive alt dette ved ei linje. 
		//koordinat kraftMellomPartUtregning; //slik. Ikkje gjort enda.

	
		double kraftMellomPartUtregningX = G*( (*masse::pAlleEnheterMapPeik)[iter]->pos(0) - mPos.getVerdi('x') ) / divident;
		double kraftMellomPartUtregningY = G*( (*masse::pAlleEnheterMapPeik)[iter]->pos(1) - mPos.getVerdi('y') ) / divident;
		double kraftMellomPartUtregningZ = G*( (*masse::pAlleEnheterMapPeik)[iter]->pos(2) - mPos.getVerdi('z') ) / divident;


		//NY METODE: XX start
//		if( pPaavirkaAvDenneKraftFraAndreObj[iter]->erTom() )  // dersom oppføring ikkje finnes. Lag den.
//		{ 
//			pPaavirkaAvDenneKraftFraAndreObj[iter] = new koordinat( kraftMellomPartUtregningX, kraftMellomPartUtregningY, kraftMellomPartUtregningZ, "kraft");
//			printf("pPaavirkaAvDenneKraftFraAndreObj[%d] - vektor var ikkje. Lager ny. qwer585\n",iter);
//			(*pout)<<"Nye adressa til pPaavirkaAvDenneKraftFraAndreObj[]: " <<pPaavirkaAvDenneKraftFraAndreObj[iter] <<endl;

//		}else{ 
 		{
			/*** TODO fiks dette, slik at den får all funksjonaliteten til allePartikkelXYZ-kraft
			 *  s.a. den slepper å regne ut kvar verdi to ganger. 
			 */
			if( ! ((*masse::pAlleEnheterMapPeik)[iter]->getPaavirkningsKraftFraMasseId(enhetsId)).erTom() )  	// sjekker om oppføring finnes på andre sia
			{													// = fra andre partikkel.
				//pDEBUG 	<<"Fann verdi fra andre sida. (" <<iter <<") Her: (" <<enhetsId <<")"
				//	<< (*masse::pAlleEnheterMapPeik)[iter]->getPaavirkningsKraftFraMasseId(enhetsId) <<std::endl;

				(*pPaavirkaAvDenneKraftFraAndreObj[iter]) =   (*masse::pAlleEnheterMapPeik)[iter]->getPaavirkningsKraftFraMasseId(enhetsId) ;
			}
			/*  ***/

			//TODO Sjekk om -/+ verdiene stemmer, at det ikkje er motsatt / skal være likt . osv.
/* XXX	*/		pPaavirkaAvDenneKraftFraAndreObj[iter]-> nyeVerdier(  kraftMellomPartUtregningX,  kraftMellomPartUtregningY,  kraftMellomPartUtregningZ );
			masse::useKraftKoordinatMap(iter, enhetsId)   -> nyeVerdier( -kraftMellomPartUtregningX, -kraftMellomPartUtregningY, -kraftMellomPartUtregningZ );
			//p DEBUG<<"iter-kraft finnes " <<iter <<": " <<pPaavirkaAvDenneKraftFraAndreObj[iter] <<*pPaavirkaAvDenneKraftFraAndreObj[iter] <<endl;
			//p DEBUG<<"*pPaavirkaAvDenneKraftFraAndreObj[iter] " <<*pPaavirkaAvDenneKraftFraAndreObj[iter] <<endl;
		}
		//          slutt XX

		//skriver ut for å sjå om den regner en eller to ganger for to part.
		//p DEBUG<<enhetsId <<"-" <<iter <<" kraftutregning." <<endl <<*pPaavirkaAvDenneKraftFraAndreObj[iter] <<"  (" <<enhetsId <<", "  <<iter <<")" <<endl;
	}

	status = 0;
	return 0;	
} //}1

void axon::kalkulerBane()
{ // ... } //{1

	// sjekker om axon treffer veggen:
	if(mPos['x'] > GRENSE  ){
		mV['x'] = -mV['x'];
		mPos['x'] = GRENSE - 0.01 ;
	}else if( mPos['x'] < -GRENSE){ 		
		mV['x'] = -mV['x'];											// VEGG VEGG VEGG
		mPos['x'] = -GRENSE + 0.01;
	}else if(mPos['y'] > GRENSE){
	       mV['y'] = -mV['y'];
	       mPos['y'] = GRENSE - 0.01;
	}else if( mPos['y'] < -GRENSE){
		mV['y'] = -mV['y'];
		mPos['y'] = -GRENSE + 0.01;
	}else if(mPos['z'] > GRENSE){
	       mV['z'] = -mV['z'];
	       mPos['z'] = GRENSE - 0.01;
	}else if( mPos['z'] < -GRENSE){
		mV['z'] = -mV['z'];
		mPos['z'] = -GRENSE + 0.01;
	}else 
	{

		// gravitasjon gjelder bare når partiklane ikkje krasjer i vegg 
	
		// Summen av gravitasjonskrefter:
		for(int iter = 1; iter <= masse::getAntallObjekt() ; iter++){
			if( !(*masse::pAlleEnheterMapPeik)[iter] ) continue;  		// sikrer mot null-peiker fra pAlleEnheterMapPeik 
			if( iter == enhetsId ) continue;
			
			if( !pPaavirkaAvDenneKraftFraAndreObj[iter] ) // peiker med verdi 0 ?
			{
				printf("\n\n\n\n\n\n\n\n\t\t\t\tFAA OPPMERSOMHET!!\tqwer029 Finn ut kvifor den ikkje funker (segf.) når neste linjene er utkommentert. \n\n\n");

				continue; 	// sikter mot nul-verdi i pPaavirkaAvDenneKraftFraAndreObj (kvifor?) XXX 
			}	

			mF += *pPaavirkaAvDenneKraftFraAndreObj[iter] ;
		}

			

		// LEGGER INN LIN. LUFTMOTSTAND: F = - k V
		// Gjør om mV til vektorform.
		mF += mV*LUFTMOTSTANDFAKTOR; // veit ikkje om funker enda. utesta..

		// LEGGER Evt til masse-fjoer-demper sys. krefter
		if( pauseSystemBool )
		{
			printf("pauseSystemBool er aktivert. partikkelG.cpp:qwer555@partikkelG.cpp \n");

			return;
		}

		// Legger over mF og bruker den til aksellerasjon, integrerer (foreløpig på simpleste måte) den opp til fart og pos .
		/*  KUK - Kommentert-Ut-Kode //{3 
		axonF[0] = mF [0] / masseTotal;
		axonF[1] = mF [1] / masseTotal;	
		axonF[2] = mF [2] / masseTotal;
		 *   //}3 */ 
		axonF[0] = mF['x'] / masseTotal;
		axonF[1] = mF['y'] / masseTotal;	
		axonF[2] = mF['z'] / masseTotal;
	
		// regner ut nyV fra gammelV. Dette kan kanskje lede til småfeil->storefeil etter lang tid, men dette er måten for no..
		// rett på dette / gjør at feil ikkje gror i det uendelige..
		mV.leggTilVerdi('x', axonF[0]); 
		mV.leggTilVerdi('y', axonF[1]); 
		mV.leggTilVerdi('z', axonF[2]); 
		//XXX lag axonF til koordinat, og mV+=axonF
		/*  KUK - Kommentert-Ut-Kode //{3 
		mV [0] += axonF[0];
		mV [1] += axonF[1];
		mV [2] += axonF[2];
		 *   //}3 */ 
	
		// og kanskje samme her.
		mPos += mV;
		/*  KUK - Kommentert-Ut-Kode //{3 
		mPos [0] += mV [0];
		mPos [1] += mV [1];
		mPos [2] += mV [2];
		 *   //}3 */ 
	}

	//pDEBUG << "Kom hit. Slutt på axon::kalkulerBane()\n";


} //}1

string axon::getObjektType( bool taMedId ) const
{ // ... } //{1
	
	char idIstring[100]; 	   //%s-string
	sprintf( idIstring, " [%d]",  enhetsId );
	
	string returString = "axon";
	if( taMedId ){	returString += idIstring; }
	return returString;
 

} //}1

void togglePauseSystem()
{ //{ ... }
 	pauseSystemBool = !pauseSystemBool;

	printf("Toggler pauseSystemBool til %d\n", pauseSystemBool);	
	// initierer no-pos-array ( for utregning av frær-krefter )
	// einaste måten eg får til lett:

	/* // KUK - Kommentert-Ut-Kode //{3 
	// mutex
	pthread_mutex_lock( &posmutex ); //posmutex

	for(int retn = 0; retn<3 ; retn++)
	{
		for(int part_nr=0; part_nr < ANTALL PARTIKLER ; part_nr++) 										// HER XXX
		{
		
			allePartikkelXYZiMasseFjaerStartTidspunkt[retn][part_nr] = alle PartikkelXYZ[retn][part_nr] + ( 0.003 * ( / *-5 til 5:* / rand()%10 - 5) );
		}
	} 

	// mutex
	pthread_mutex_unlock( &posmutex ); //posmutex
	*/ //}3 
} //}1

// vim:fdm=marker:fmr=//{,//} : fdl=2
