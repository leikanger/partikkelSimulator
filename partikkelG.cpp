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
bool masseFjoerDempetSystemBool = false;
//double avstand MellomPartikler[ANTAL LPARTIKLER][ANTALL PARTIKLER];		// avstanden mellom to partikler 				
int partikkel::antallObjekterInitiert = 0;
//double kraftMellomPartArray[3][ANTALL PARTIKLER][ANTALL PARTIKLER];
extern bool skinn::globalAvluttProgramVariabel; 
//}1


partikkel::partikkel()
{ // ... } //{1
	
	// tilfeldig tall seed
	srand(rand()+time(NULL));

	mPos.nyeVerdier( ((0.01 * (rand()%200)) -1) * GRENSE ,  ( (0.01 * (rand()%200)) -1) * GRENSE  	,  ( (0.01 * (rand()%200)) -1) * GRENSE , "Posisjon " );
	mV.nyeVerdier( 	 mPos.getVerdi('y')*STARTFART_TANG   ,  mPos.getVerdi('x')*STARTFART_TANG  	,  mPos.getVerdi('x')*STARTFART_TANG    , "Fart " );

	masseTotal =  0.1 *( rand() % 20 ) +1;

	
	/*  KUK - Kommentert-Ut-Kode //{3 
	mV [0] = -mPos [1] * STARTFART_TANG;  //  0;//(0.0001 * (rand()%10)) ;
	mV [1] =  mPos [0] * STARTFART_TANG; // 0;//(0.0001 * (rand()%10)) ;
	mV [2] =  mPos [0] * STARTFART_TANG; // minus / pluss??
	 *   //}3 */ 

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
		 	(*masse::pAlleEnheterMapPeik)[iter]->kalkulerKraftMellomMasseSenter();
		
	
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


void partikkel::kalkulerAvstander(vector<masse*> vmpArgument)
{
	 //dirty. men for no, ok. Driver med major omvelting.
	 partikkel::kalkulerAvstander();
}

// en todo inni her.
void partikkel::kalkulerAvstander()
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

// TODO : fiks denne, og gjør kalkulerKraftMellomMasseSenter() const
//  		s.a. den tar inn (int, int) og endrer på status på de to part. med desse id-er, til nykrasja (-1)
//  		evt. bare en int., og endre den, og seg selv.
//  		og gjør den static i så fall.
//
//  		I tillegg kan eg da fjærne krasjtid og status fra masse. (desse er no dobbelt opp. masse og partikkel)
//  		XXX
void partikkel::kollisjon( int andrePartikkelId, bool denneFunksjonErKallaFraUtsida =true )
{
	//XXX Vurderer å flytte inn i masse - klassa...
	//
	
	//partikkel *pTemp= static_cast<partikkel*>(p Part[andrePartikkelId])  ;
	partikkel *hipartikkelen = static_cast<partikkel*> ( (*masse::pAlleEnheterMapPeik)[andrePartikkelId] );

	 //TODO legg inn feilsjekking. Kanskje noke alla:
	 //if( ! ( pTemp = static_cast<partikkel*>(p Part[andrePartikkelId]) )  ) throw feil_i_objektId("I kollisjon: Leiter etter partikkel m. ukjendt obj. id.");

	 if( !hipartikkelen )  throw feil_i_objektId("I kollisjon: Leiter etter partikkel m. feil i id, eller av anna grunn (*0)");//for å styre unna segf.

	 //partikkel::kollisjon( pTemp );

	double hinPartikkelPos[3];

	if( !ELASTISKEKOLLISJONER ){ return; }  //Ikkje elastiske støt? Deiligare med, men funker ikkje enda..
	else{
		
	
	// KARL SIN FORMEL:

		double hiMasseVerdi;
		//double hinFarta[3];
		koordinat hiFart;

		// gjør fra pInput-> til ppart[i]-> , der i er inputid-int som skal komme som arg.
		hiFart = hipartikkelen->getFart();
		hiMasseVerdi = hipartikkelen->getMasseTotal();
		
		double retnFaktorX =  (( masseTotal - hiMasseVerdi) + 2 * (hiMasseVerdi * hiFart['x']) /*vekt*/  /* hinFarta[0]*/ )     /   (hiMasseVerdi + masseTotal);
		double retnFaktorY =  (( masseTotal - hiMasseVerdi) + 2 * (hiMasseVerdi * hiFart['y']) /*vekt*/  /* hinFarta[0]*/ )     /   (hiMasseVerdi + masseTotal);
		double retnFaktorZ =  (( masseTotal - hiMasseVerdi) + 2 * (hiMasseVerdi * hiFart['z']) /*vekt*/  /* hinFarta[0]*/ )     /   (hiMasseVerdi + masseTotal);
		koordinat retnFaktor( retnFaktorX, retnFaktorY, retnFaktorZ );
		mV = mV  *  retnFaktor;
		//XXX ikkje heilt sikker på om denne funker etter overg. fra double[3] til koordinat

		/*  KUK - Kommentert-Ut-Kode //{3 
		mV [0] = ( mV [0] * ( masseTotal - hiMasseVerdi) + 2 * hiMasseVerdi * hinFarta[0])     /   (hiMasseVerdi + masseTotal);
		mV [1] = ( mV [1] * ( masseTotal - hiMasseVerdi) + 2 * hiMasseVerdi * hinFarta[1])     /   (hiMasseVerdi + masseTotal);
		mV [2] = ( mV [2] * ( masseTotal - hiMasseVerdi) + 2 * hiMasseVerdi * hinFarta[2])     /   (hiMasseVerdi + masseTotal);
		 *   //}3 */ 

	// SLUTT FORMEL

	// Gjør det med andre partikkel også:
	 	if( denneFunksjonErKallaFraUtsida ) 		//for å unngå PING_PONG
			hipartikkelen->kollisjon( enhetsId, false ); //kollisjon med meg. 
		//tatt med en boolverdi for å unngå pingpong-effekt.

		//himassa->mV [0] = ( himassa->mV [0] * (hiMasseVerdi - masseTotal) + 2 * masseTotal * mV [0])     /   (hiMasseVerdi + masseTotal);
		//himassa->mV [1] = ( himassa->mV [1] * (hiMasseVerdi - masseTotal) + 2 * masseTotal * mV [1])     /   (hiMasseVerdi + masseTotal);
		//himassa->mV [2] = ( himassa->mV [2] * (hiMasseVerdi - masseTotal) + 2 * masseTotal * mV [2])     /   (hiMasseVerdi + masseTotal);


	// endre status og tid.
	// Skjer også i hipartikkelen->kollisjon...
 	//	   hipartikkelen->status = -1;
				  status = -1;
	//	 hipartikkelen->krasjtid = time(0);
				krasjtid = time(0);

	}
}
/*
void partikkel::kollisjon(masse* mpInput)
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


	// Gjør det med andre partikkel også:
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

// Lag variant med sammensmelting også. Kanskje i masseklasse?. mV+=hinP.mV, pos, masseTotal, varme++(evt), slett hin partikkel fra allePartikler*vektor[nok?], 
// mF?, antallObjektInitiert--, osv.

int partikkel::kalkulerKraftMellomMasseSenter() 
{ // ... } //{1

	//XXX XXX XXX
	//TODO
	//Husk å sjekke om kraft allerede er regna ut fra andre sida (andre partikkelen).
	// eller er dette allerede ordna i utregning fra eine sida?? -> skriver til begge to, som påvirker kvarandre.. ??
	
	//G*M*\delta t
	//Trur at retur ikkje blir brukt.

	/*
	kraftMellomPartArray[0][enhetsId][enhetsId] = 0; 	// påverker seg selv med null kraft.
	kraftMellomPartArray[1][enhetsId][enhetsId] = 0; 	// påverker seg selv med null kraft.
	kraftMellomPartArray[2][enhetsId][enhetsId] = 0; 	// påverker seg selv med null kraft.
	*/

	// Løkke for å finne alleredekrasja.
	for(int i = 1; i<= masse::getAntallObjekt() ; i++)
	{
		if(i == enhetsId){ continue; }
		
		if( ! (*masse::pAlleEnheterMapPeik)[i] ) continue;

/*  KUK - Kommentert-Ut-Kode //{9 
 *		if( !ELASTISKEKOLLISJONER ) 
 *		{		// IKKJE ELASTISKE KOLLISJONER??? DEILIGARE UTEN, OG FUNKER IKKJE HEILT ENDA.
			if(avstand MellomPartikler[enhetsId][i] < MINSTEAVSTAND){
	
				double retning[2];
			      	retning[0]	= (p Part[i].pos(0) - mPos [0]) / fabs(p Part[i].pos(0)-mPos [0]);
			      	retning[1]	= (p Part[i].pos(1) - mPos [1]) / fabs(p Part[i].pos(1)-mPos [0]);		//RHER
																			// FUNKER IKKJE  FOR 3 DIMENSJONER

				kraftMellomPartArray[0][enhetsId][i] = MAXKRAFT;//1e-30 * G * MINSTEAVSTAND * retning[0] ;//
				// Y - verdiar (mF [1]) 		mF [1] += G*(allePartikkelXY[1][iter] - mPos [1]) / pow(avstand MellomPartikler[enhetsId][iter],3);
				kraftMellomPartArray[1][enhetsId][i] = MAXKRAFT;//1e-30 * G * MINSTEAVSTAND * retning[1] ;

				// kopierer F_ac til F_ca
				kraftMellomPartArray[0][i][enhetsId] = -kraftMellomPartArray[0][enhetsId][i];
				kraftMellomPartArray[1][i][enhetsId] = -kraftMellomPartArray[1][enhetsId][i];
	
				continue;
			}
		// legger inn liten vakt mot for nær akselerasjon
		// XXX Denne if-setninga er ikkje heilt forståelig. Legg inn paranteser!!! XXX
		}else*/ 	
//}9 
						 		//status 1 tyder at den har krasja, -1 at den allerede har regn ut resultat.
		if(status == 1 || ((status == 0) && ((*masse::pAlleEnheterMapPeik)[enhetsId]->getAvstandTilObjekt(i) < MINSTEAVSTAND)) )
		{
			if( time(0) - krasjtid  > 1 ) { 
				kollisjon( i );	
				printf(" KOLLISJON!! DO IT! \n");
			}

			return 0;
				
		}
	}

 	//p DEBUG<<"Itererer til ny partikkel: " <<enhetsId <<endl;
	
	for(int iter=1 ; iter < masse::getAntallObjekt() ; iter++){ //var bare: opp til enhetsId
		
		if(iter == enhetsId) continue;

		//double divident = 1/pow(avstandMellomPartikler[enhetsId][iter], 3);
		double divident =     pow( avstandTilAndreObjekt[iter], 3);
		// XXX
		// divitent er lik 1/divident. Heilt feil! sjå ned. deler på divitent, men divitent er allerede delt.
		// endrer uten å ha mulighet for å sjekke resultat.
		// XXX

		//mF [1] += G*(allePartikkelXY[1][iter] - mPos [1]) / pow(avstand MellomPartikler[enhetsId][iter],3);
		//XXX fiks dette slik at pos() returnerer en koordinat og vi kan skrive alt dette ved ei linje. 
		//koordinat kraftMellomPartUtregning; //slik. Ikkje gjort enda.

	
		double kraftMellomPartUtregningX = G*( (*masse::pAlleEnheterMapPeik)[iter]->pos(0) - mPos.getVerdi('x') ) / divident;
		double kraftMellomPartUtregningY = G*( (*masse::pAlleEnheterMapPeik)[iter]->pos(1) - mPos.getVerdi('y') ) / divident;
		double kraftMellomPartUtregningZ = G*( (*masse::pAlleEnheterMapPeik)[iter]->pos(2) - mPos.getVerdi('z') ) / divident;

		//{9	KUK / kommentert-ut-kode
		/*
		printf("enhetsId %d, iter %d \n",enhetsId, iter);

		printf("*m::p[it]->pos(0) |%f|-mPos [0] |%f| = %f\n",(*masse::pAlleEnheterMapPeik)[iter]->pos(0), mPos [0], (*masse::pAlleEnheterMapPeik)[iter]->pos(0)-mPos [0] );
		printf("*m::p[it]->pos(1) |%f|-mPos [1] |%f| = %f\n",(*masse::pAlleEnheterMapPeik)[iter]->pos(1), mPos [1], (*masse::pAlleEnheterMapPeik)[iter]->pos(1)-mPos [1] );
		printf("*m::p[it]->pos(2) |%f|-mPos [2] |%f| = %f\n",(*masse::pAlleEnheterMapPeik)[iter]->pos(2), mPos [2], (*masse::pAlleEnheterMapPeik)[iter]->pos(2)-mPos [2] );

		// a -> b (a påvirker b) like mykje som b -> a (newton)
		// kopierer F_ac til F_ca
		/ *  
		kraftMellomPartArray[0][iter][enhetsId] = -kraftMellomPartUtregningX;
		kraftMellomPartArray[0][enhetsId][iter] = kraftMellomPartUtregningX;
		kraftMellomPartArray[1][iter][enhetsId] = -kraftMellomPartUtregningY;
		kraftMellomPartArray[1][enhetsId][iter] = kraftMellomPartUtregningY;
		kraftMellomPartArray[2][iter][enhetsId] = -kraftMellomPartUtregningZ;
		kraftMellomPartArray[2][enhetsId][iter] = kraftMellomPartUtregningZ;
		*/ //}9
	

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

void partikkel::kalkulerBane()
{ // ... } //{1

	/* KUK - Kommentert-Ut-Kode //{3  Nuller ut krafta fra forrige iterasjon
	 * Flytta inn i nullUtAvstanderOgKraft_i_pAlleEnheter
	mF [0] = 0;
	mF [1] = 0;
	mF [2] = 0;
	forresten: har også bytta ut double[] med koordinat.
	mF.nullUt() gjør samme jobben.
	//}3 */

	// sjekker om partikkel treffer veggen:
	if(mPos['x'] > GRENSE  ){
		mV['x'] = -mV['x'];
		mPos['x'] = GRENSE - 0.01 ;
	}else if( mPos['x'] < -GRENSE){ 			// XXX HER ER EG. TODO gjør ferdig :denne, og resten av overføringa fra double [3] til koordinat

		//TODO plan: lær om operator, nok til å lage [] subscipt til koordinat. s.a. eg kan skrive mV['x']; XXX

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
		//if( enhetsId == 1 ) pDEBUG <<"."; //for å sjekke kvifor det er så helvetes hakkete.
		// iterasjonsprikker
		//Kvar prikk er en runde gjennom alle partikler..

		// gravitasjon funker bare når partiklane ikkje krasjer i vegg 
	
		// Summen av gravitasjonskrefter:
		for(int iter = 1; iter <= masse::getAntallObjekt() ; iter++){
			if( !(*masse::pAlleEnheterMapPeik)[iter] ) continue;  		// sikrer mot null-peiker fra pAlleEnheterMapPeik 
			if( iter == enhetsId ) continue;
			
			// p DEBUG <<enhetsId <<" - partikkelG.cpp@qwer695" <<"] -  " <<iter <<endl ;  
			/// XXX Dette er feil.  -> testa å skrive ut kvar gang !paavirkaAvDenneKraftFraAndreObj_[it] => kvar gang.
			if( !pPaavirkaAvDenneKraftFraAndreObj[iter] ) // peiker med verdi 0 ?
			{
				printf("\n\n\n\n\n\n\n\n\t\t\t\tFAA OPPMERSOMHET!!\tqwer029 Finn ut kvifor den ikkje funker (segf.) når neste linjene er utkommentert. \n\n\n");
				// p DEBUG<<"!pPaavirkaAvDenneKraftFraAndreObj[ " <<iter <<"] : " <<pPaavirkaAvDenneKraftFraAndreObj[iter] <<"  qwer43t@partikkelG.cpp" <<endl;

				// p DEBUG<<" Continue" <<iter <<endl ;
				continue; 	// sikter mot nul-verdi i pPaavirkaAvDenneKraftFraAndreObj (kvifor?) XXX 
	/*//	(jepp, funker ikkje lenger med denne utkommentert..)		*/
			}	
			/*  XXX
			 	 Det er pAlleEnheterMapPeik - iter - som skal sjekkes om har verdi. Det er allerede gjort. Her bør eg sjekke motsatt vei. om 
			  				pPaavirkaAvDenneKraftFraAndreObj finnes fra andre sida, kopier, og continue.   
			  				- men dette i kalkulerKraftMellomMasseSenter 
			*/

			/*  KUK - Kommentert-Ut-Kode //{9
			mF [0] += pPaavirkaAvDenneKraftFraAndreObj[iter]->getVerdi('x');
			mF [1] += pPaavirkaAvDenneKraftFraAndreObj[iter]->getVerdi('y');// kraftMellomPartArray[1][enhetsId][iter];
			mF [2] += pPaavirkaAvDenneKraftFraAndreObj[iter]->getVerdi('z');// kraftMellomPartArray[2][enhetsId][iter];
			 *   //}9 */ 
			mF += *pPaavirkaAvDenneKraftFraAndreObj[iter] ;
			//printf("meg(%d) til %d: ", enhetsId, iter );
			//pPaavirkaAvDenneKraftFraAndreObj[iter]->skrivUt("legger til denne kraft:");
			//mF.skrivUt("mF\t\t\t\t");
		}

			

		// LEGGER INN LIN. LUFTMOTSTAND: F = - k V
		// Gjør om mV til vektorform.
		mF += mV*LUFTMOTSTANDFAKTOR; // veit ikkje om funker enda. utesta..
		/*  KUK - Kommentert-Ut-Kode //{3 
		mF.leggTilVerdi('x', mV [0] * LUFTMOTSTANDFAKTOR );
		mF.leggTilVerdi('y', mV [1] * LUFTMOTSTANDFAKTOR );
		mF.leggTilVerdi('z', mV [2] * LUFTMOTSTANDFAKTOR );
		 *   //}3 */ 

		// LEGGER Evt til masse-fjoer-demper sys. krefter
		if( masseFjoerDempetSystemBool )
		{
			printf("masseFjoerDempetSystemBool er ikkje implementer. partikkelG.cpp:qwer555@partikkelG.cpp \n"); // XXX HER
			/*
			// fjoer: - (utg_pos - pos) * K_fjoer
			mF [0] -= (mPos [0] - allePartikkelXYZiMasseFjaerStartTidspunkt[0][enhetsId]) * FJAER_KONST;
			mF [1] -= (mPos [1] - allePartikkelXYZiMasseFjaerStartTidspunkt[1][enhetsId]) * FJAER_KONST;
			mF [2] -= (mPos [2] - allePartikkelXYZiMasseFjaerStartTidspunkt[2][enhetsId]) * FJAER_KONST;
			// demper:-  fart 	    * K_demper
			mF [0] -= mV [0] * DEMPER_KONST;
			mF [1] -= mV [1] * DEMPER_KONST;
			mF [2] -= mV [2] * DEMPER_KONST;
			*/
		}

		// Legger over mF og bruker den til aksellerasjon, integrerer (foreløpig på simpleste måte) den opp til fart og pos .
		/*  KUK - Kommentert-Ut-Kode //{3 
		partikkelA[0] = mF [0] / masseTotal;
		partikkelA[1] = mF [1] / masseTotal;	
		partikkelA[2] = mF [2] / masseTotal;
		 *   //}3 */ 
		partikkelA[0] = mF['x'] / masseTotal;
		partikkelA[1] = mF['y'] / masseTotal;	
		partikkelA[2] = mF['z'] / masseTotal;
	
		// regner ut nyV fra gammelV. Dette kan kanskje lede til småfeil->storefeil etter lang tid, men dette er måten for no..
		// rett på dette / gjør at feil ikkje gror i det uendelige..
		mV.leggTilVerdi('x', partikkelA[0]); 
		mV.leggTilVerdi('y', partikkelA[1]); 
		mV.leggTilVerdi('z', partikkelA[2]); 
		//XXX lag partikkelA til koordinat, og mV+=partikkelA
		/*  KUK - Kommentert-Ut-Kode //{3 
		mV [0] += partikkelA[0];
		mV [1] += partikkelA[1];
		mV [2] += partikkelA[2];
		 *   //}3 */ 
	
		// og kanskje samme her.
		mPos += mV;
		/*  KUK - Kommentert-Ut-Kode //{3 
		mPos [0] += mV [0];
		mPos [1] += mV [1];
		mPos [2] += mV [2];
		 *   //}3 */ 
	}

	//pDEBUG << "Kom hit. Slutt på partikkel::kalkulerBane()\n";

//{5 UKK (utkommentert kode)
/*
	/// XXX GAMMELT: SLETT XXX
	//
		// Summen av gravitasjonskrefter:
		for(int iter = 0; iter < ANTALL PARTIKLER; iter++){  										// HER XXX
		// *XXX XXX XXX
			mF [0] += kraftMellomPartArray[0][enhetsId][iter];
			mF [1] += kraftMellomPartArray[1][enhetsId][iter];
			mF [2] += kraftMellomPartArray[2][enhetsId][iter];										
		//XXX XXX XXX
		}

		// LEGGER INN LIN. LUFTMOTSTAND: F = - k V
		mF [0] -= mV [0] * LUFTMOTSTANDFAKTOR;
		mF [1] -= mV [1] * LUFTMOTSTANDFAKTOR;
		mF [2] -= mV [2] * LUFTMOTSTANDFAKTOR;

		// LEGGER Evt til masse-fjoer-demper sys. krefter
		if( masseFjoerDempetSystemBool )
		{
			// fjoer: - (utg_pos - pos) * K_fjoer
			mF [0] -= (mPos [0] - allePartikkelXYZiMasseFjaerStartTidspunkt[0][enhetsId]) * FJAER_KONST;
			mF [1] -= (mPos [1] - allePartikkelXYZiMasseFjaerStartTidspunkt[1][enhetsId]) * FJAER_KONST;
			mF [2] -= (mPos [2] - allePartikkelXYZiMasseFjaerStartTidspunkt[2][enhetsId]) * FJAER_KONST;
			// demper:-  fart 	    * K_demper
			mF [0] -= mV [0] * DEMPER_KONST;
			mF [1] -= mV [1] * DEMPER_KONST;
			mF [2] -= mV [2] * DEMPER_KONST;
		}

		// Legger over mF og bruker den til aksellerasjon, integrerer (foreløpig på simpleste måte) den opp til fart og pos .
		partikkelA[0] = mF [0] / masseTotal;
		partikkelA[1] = mF [1] / masseTotal;	
		partikkelA[2] = mF [2] / masseTotal;
	
		mV [0] += partikkelA[0];
		mV [1] += partikkelA[1];
		mV [2] += partikkelA[2];
	
		mPos [0] += mV [0];
		mPos [1] += mV [1];
		mPos [2] += mV [2];
*/ //}5

} //}1

string partikkel::getObjektType( bool taMedId ) const
{ // ... } //{1
	
	char idIstring[100]; 	   //%s-string
	sprintf( idIstring, " [%d]",  enhetsId );
	
	string returString = "partikkel";
	if( taMedId ){	returString += idIstring; }
	return returString;
 

} //}1

void toggleMasseFjoerDempetSystem()
{ //{ ... }
 	masseFjoerDempetSystemBool = !masseFjoerDempetSystemBool;

	printf("Toggler masseFjoerDempetSystemBool til %d\n", masseFjoerDempetSystemBool);	
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
