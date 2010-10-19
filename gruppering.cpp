//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//  * * * * * * * * * * * 	grupperinger.cpp - implementere massePar-klasse. 	* * * * * * * * * * * * * *
//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Filbeskrivelse / kommentar //{1
/*
 * 	Grupperinger. Skal innføre grupper, der summen av krefter er ikkje lik null, men lik gruppas samla F.
 *  	Kan såleis regne ut kraft mellom p Part i sys, for så å vektoriellt plusse på felles F - fordelt utover p Part. i sys.
 * 	Skal regne ut F vha allerede innførte og fungerende funker. vha avst. mellom grupper og kalkulerKrefter-funk.
 *	Grupperinger velges to og to basert på nermeste-utvalg. og evt videre omigjen.
 */
//}

//		#include //{1  














			HEILE FILA ER UTKOMMENTERT / IKKJE KOMPILERT

			/*

			FOR NÅR EG STARTA MED utfasing av avst. array og å ta masse*-map * som static i masse, trengte (trenger) eg å konse på det, og 
								gruppering var ikkje lenger aktuelt/nødvendig for å få utfordring. Ta igjen når du kjeder deg..














#include <iostream>
#include "partikkelG.h"
#include "gruppering.h"
#include "main.h"
#include <math.h>
#include <pthread.h>

// for exit (-1) - funk
#include <cstdlib>

#include <list>
#include <map>
//}1 

using namespace std;

//{1 		mutex, globale variablar o.l.
pthread_mutex_t gruppeMutexAvstandMellomGrupper = PTHREAD_MUTEX_INITIALIZER;

double avstandMellomGrupper[ANTALLGRUPPER][ANTALLGRUPPER];
double kraftMellomMasseArray[3][ANTALLGRUPPER][ANTALLGRUPPER];
//extern double avstand MellomPartikler[ANTALLPARTIKLER][ANTALLPARTIKLER];

bool boolHarSjekkaPartikkelNr[ANTALLPARTIKLER]; 	// For rekursiv-finn-nermast-funk.

bool boolHarTattPartNrIgruppe[ANTALLPARTIKLER];

// HER  GJØR OM!
//extern vector<masse*> p Part;

//int antallGrupperInitiert = 0;
int massePar::antallObjekterInitiert = 0;
//const int massePar::nConstAntallObjekterTotalt = ANTALLPARTIKLER /2 ;

//} start kode


massePar::massePar(masse* pEn, masse* pTo)
{ //{1... } 
	// (ikkje i bruk enda...)
	pMasseEn = pEn;
	pMasseTo = pTo;


	double part1Masse = pMasseEn->getMasseTotal();
	double part2Masse = pMasseTo->getMasseTotal();

	// Regner ut fellesMassene i gruppene.	
	masseTotal = part1Masse + part2Masse; 
		
	mPos[0] = 	(part1Masse * pMasseEn->pos(0) +
	             	(part2Masse * pMasseTo->pos(0)))
	   	 	/ masseTotal;

	mPos[1] = 	(part1Masse * pMasseEn->pos(1) +
	       		(part2Masse * pMasseTo->pos(1)))
	       	 	/ masseTotal;
		
	mPos[2] = 	(part1Masse * pMasseEn->pos(2) +
	      	 	(part2Masse * pMasseTo->pos(2)))
	       	 	/ masseTotal;

	
	enhetsId = antallObjekterInitiert;
	antallObjekterInitiert++;
	
	return;
} //}

void massePar::kalkulerAvstander(vector<masse*> lpPInput)
{ //{1 ... }
	// mutex start. -> slutter før funk slutter.
	pthread_mutex_lock( &gruppeMutexAvstandMellomGrupper );

	vector<masse*>::iterator lpiI = lpPInput.begin();

	double nesteUtregnaAvst;
	masse* tempNermastePartikkelPp; //endre navn. orker ikkje no med alle feilmeldingene eg kjem til å fa..

	// Finn avstander. 	//sjekker bare partikler etter seg selv. Tidligare har allerede funnet avstanden
	avstandMellomGrupper[enhetsId][enhetsId] = 0; // er 0 unna seg selv.

	int i;
	//(*pout)<< "kalk.avs.m.g. enhetsId: " <<enhetsId <<"\n";

	for( i=0; i<enhetsId; i++ ){ lpiI++; } //setter lpiI til +=enhetsId (på einaste måten eg kjem på)
	// Skal i starte på 1 - kanskje?

	// lpiI peiker no på enhetsId-gruppa.
	
	for( ; lpiI != lpPInput.end(); ++lpiI){ //{2

		nesteUtregnaAvst = 		sqrt( 	pow( mPos[0] - (*lpiI)->pos(0) , 2)
			       			      + pow( mPos[1] - (*lpiI)->pos(1) , 2)
						      + pow( mPos[2] - (*lpiI)->pos(2) , 2)  );

//		c out<<"a [" 	<< mPos[0] <<", "  	<< mPos[1]  <<", " 	<<mPos[2] <<"]\n";
//		c out<<"b ["  << lpiI->mPos[0] <<", "  << lpiI->mPos[1]  <<", " <<lpiI->mPos[2] <<"]\n";

		// Kanskje løysinga er å for i (16 linjer opp) å starte på 1. 1-indexert; ikkje 0-i
		//
		avstandMellomGrupper[enhetsId-1][i] = nesteUtregnaAvst ;  // har ikkje tenkt igjennom kvifor, men funker slik, funker ikkje uten *-1
		avstandMellomGrupper[i][enhetsId-1] = nesteUtregnaAvst ;


		// Her skal eg etter kvart implementere at kvar gruppe har peiker til nermaste gruppe for 
		// seinare å lage denne grupperinga rekursiv.
			
		i++;
	} //}2

	// mutex unlock. starter på start av funk.
	pthread_mutex_unlock( &gruppeMutexAvstandMellomGrupper );
	printf("\t\t\t\t\t\tTrur denne funksjonen er ubrukt feløpig. massePar::kalkulerAvstander( .. ) . gruppering.cpp:l.128 \n\t\t\t\t\t\t\tGå hit om du ser denne feilmld.\n");
//(*pout)<<"nermaste m asse: " <<p Part[enhetsId].pNermaste->m asseTotal;
} //}1 

/* 
SKAL VÆRE MED:   
int massePar::kalkulerKraftMellomMasseSenter(vector<massePar> lpPInputAllePartikkelpar)
{ //{1 ... }
	vector<massePar>::iterator lpPIter = lpPInputAllePartikkelpar.begin();

	//{ Regner ut avstander... Skriv inn initverdi i løkke sjølv om det er gjort to liner opp.
	for( ; lpPIter != lpPInputAllePartikkelpar.end() ; lpPIter++){
		lpPIter->kalkulerAvstanderMellomGrupper( lpPInputAllePartikkelpar ); 	// er det noko her???
	}//}
	
	//G*M*\delta t

	// Mutex start. Stopper lenger nede i funk. . En til i kalkulerAvstanderMellomGrupper.
	pthread_mutex_unlock( &gruppeMutexAvstandMellomGrupper );

	// for for-løkke:
	int iter = 0;// sjå tre linjer ned.  								// også 1-indexert/0-indexert - problem.
	// Sørger for at lpPIter peiker på denne gruppa(enhetsId-gr)
	lpPIter = lpPInputAllePartikkelpar.begin();
	for( ; iter < enhetsId ; iter++ ){ lpPIter++; } 						// her (sjå opp)

	// Kan funke (skitten fix) TODO if( iter > ANTALLGRUPPER ){ return 0; }

	// lpPIter peiker no på meg-gruppa.
	
	// avslutter om har iterert forbi [alleGrupper]
	if( iter > ANTALLGRUPPER ){ (*pout)<<"FEIL. iter > ANTALLGRUPPER. Feilkode: 123\n"<<"iter, enhetsId, ANTALLGRUPPER\t" <<iter <<", " <<enhetsId <<", " <<ANTALLGRUPPER <<"\n";	return (-1); }
	
	
	for(  ; lpPIter != lpPInputAllePartikkelpar.end(); lpPIter++){ // iterer til lpPIter peiker på siste objektet+1 - så slutt.
	//{
		iter++;

		// av ukjendt grunn er avs.array tom fom iterasjoner etter 2. gj.g inn i if:
		//if(iter == enhetsId){ (*pout)<<"  -:continue\n"; continue; }
		
		// Karkulerer kraftMellomGr.[][] - array
		// Alle x-verdiane i a-b  og y-verdiane i b-a. og a-a (mellom)
		// a -> b (a påvirker b) like mykje som b -> a (newton)
		// X - verdiar (partikkelF[0]:
	


		// Trur det er noko feil med indexen igjen. Fakta[ 1-2 er egentlig 2-3 og 1-3 er egentlig 2-4 (bare 3 i bredden, så out of bounds???)
//		print f( "gI,it : avstMG[%d][%d] = %.2f %.2f " ,enhetsId, (iter-1) , avstandMellomGrupper[enhetsId][iter-1], avstandMellomGrupper[enhetsId][iter-1] );

//		print f( "\tgI,it :(1-i) avstMG[%d][%d] = %.2f\n " , (enhetsId-0), (iter-0) , avstandMellomGrupper[enhetsId-1][iter-1] ); // enhetsId og iter er 1-indexert. array er 0-indexert
//		print f( "\tplanv.:(1-i) avstMG[%d][%d] = %.2f\n " , (iter-0),(enhetsId-0) , avstandMellomGrupper[enhetsId-1][iter-1] ); // enhetsId og iter er 1-indexert. array er 0-indexert
		//(*pout)<<"\n" <<avstandMellomGrupper[enhetsId][iter] <<"\tavstMG(*pout)\n";
		
		double divident = pow( avstandMellomGrupper[enhetsId-1][iter-1], 3); 				// iter-1], 3);
		// Feilsøking (ingen skal skje, uansett):
		if( enhetsId == iter ){ (*pout)<<"no-no\n"; }
		if( divident == 0 ){ (*pout)<<"\n... IKKJA DIVIDEIRA PAO NOLL..\n";  return (-1); }

		// NO ER DET HER DET ER NOKO BUG. Får ut 0 kvar gang. eller ca 0 i kraftArray.
		double kraftMellomGruppX  = (G*( lpPIter->mPos[0] - mPos[0] )) / divident;
		double kraftMellomGruppY  = (G*( lpPIter->mPos[1] - mPos[1] )) / divident;
		double kraftMellomGruppZ  = (G*( lpPIter->mPos[2] - mPos[2] )) / divident;

		/*{	
			print f( "       ->m assesenter        \t\t %.2f  *  %.2f  *  %.2f\n", lpPIter->mPos[0],  lpPIter->mPos[1], lpPIter->mPos[2] );
			print f( "          m assesenter       \t\t %.2f  *  %.2f  *  %.2f\n", mPos[0],  mPos[1], mPos[2] );
			print f( "->Masses-m asses.        \t\t %.2f  *  %.2f  *  %.2f\n", lpPIter->mPos[0]-mPos[0],  lpPIter->mPos[1]-mPos[1], lpPIter->mPos[2]-mPos[2] );
			print f(    "Kraft: G*->Masses - m asses./ d\t\t");
			(*pout)<<"["		<<(G*(lpPIter->mPos[0]-mPos[0])/divident) 
						<<", "  <<(G*(lpPIter->mPos[1]-mPos[1])/divident)
						<<", "  <<(G*(lpPIter->mPos[2]-mPos[2])/divident)  <<"]";
		}* /
		
		
		// kopierer F_ac til F_ca
		kraftMellomMasseArray[0][enhetsId-1][iter-1]  = kraftMellomGruppX;
		kraftMellomMasseArray[0][iter-1][enhetsId-1] = -kraftMellomGruppX;
		kraftMellomMasseArray[1][enhetsId-1][iter-1]  = kraftMellomGruppY;
		kraftMellomMasseArray[1][iter-1][enhetsId-1] = -kraftMellomGruppY;
		kraftMellomMasseArray[2][enhetsId-1][iter-1]  = kraftMellomGruppZ;
		kraftMellomMasseArray[2][iter-1][enhetsId-1] = -kraftMellomGruppZ;	


/* Skriv ut:
		c out<<"\n";
		system("clear");
		for(int a = 0; a < ANTALLPARTIKLER; a++){
			c out<< "\n a: " <<a <<"\t\t";; 
			for(int b = 0; b < ANTALLPARTIKLER; b++){
				c out <<avstand MellomPartikler[a][b] << "\t\t" <<avstand MellomPartikler[a][b] <<"\t\t|||\t";
			}
		}
* /
	} //}
	
	// mutex stopp
	pthread_mutex_unlock( &gruppeMutexAvstandMellomGrupper );

	kraftMellomMasseArray[0][enhetsId-1][enhetsId-1] = 0; 	// påverker seg selv med null kraft.
	kraftMellomMasseArray[1][enhetsId-1][enhetsId-1] = 0; 	// påverker seg selv med null kraft.
	kraftMellomMasseArray[2][enhetsId-1][enhetsId-1] = 0; 	// påverker seg selv med null kraft.

} //}1
*/
void massePar::summerKrefterPaaDetteMasseSenter()
{ //{1 ... }
	// Nuller ut kraft fra forrige it.
	mF[0] = 0;
	mF[1] = 0;
	mF[2] = 0;
	//mF.nyeVerdier(0,0,0);


	// fysikkens regler funker bare når partiklane ikkje krasjer
	// i vegg eller anna partikkel
	for(int iter = 0; iter < ANTALLPARTIKLER; iter++){  
		mF[0] += kraftMellomMasseArray[0][enhetsId][iter];   // enhetsId -1?? Har hatt prob med dette før
		mF[1] += kraftMellomMasseArray[1][enhetsId][iter];
		mF[2] += kraftMellomMasseArray[2][enhetsId][iter];										
	}
	(*pout)<<"Kraft tot. på Masse " <<enhetsId <<": [" <<mF[0] <<", " <<mF[1] <<", " <<mF[2] <<"]\n";
} //}1

string massePar::getObjektType( bool taMedId ) const
{ //{1 ... }
//	int mEnId = pMasseEn->getId();
//	int mToId = pMasseTo->getId();  / gjort under, der det var påtenkt å brukes.. Slett no.
	char idEnIstring[100]; 
	char idToIstring[100]; 	
	sprintf( idEnIstring, "%d",  pMasseEn->getId() );
	sprintf( idToIstring, "%d",  pMasseTo->getId() );
	
	string returString = "massePar(";
	returString += pMasseEn->getObjektType( true );
	returString += " ";
    	returString += idEnIstring;
	returString += ", ";
    	returString += idToIstring;
	returString += pMasseTo->getObjektType( true );
	returString += ")";
	return returString;
} //}1

// rekursiv nermaste - funksjon
int erViNermastePartikklerRekursFunk(int erViParSpmFraPartId, int megPartId)
{ //{1 ... }
/* * * * * * * * * * * * * * * * * * *
 * * * Rekursiv finnPar - 	   * *
 * * * funksjon. 		   * *
 * * * a   b c   		   * *
 * * * A nermest B, men ikkje par. * *
 * * * * * * * * * * * * * * * * * * */
	map<double, int> mapSortertAvstIdArray;
	map<double, int>::iterator mIter = mapSortertAvstIdArray.begin();
 	// Går ut fra at finnAvstander er kjørt, og avstandMellomGrupper[][] er fyllt. 

	if( boolHarSjekkaPartikkelNr[megPartId] ){ return -1;/*ikkje gjør noko-return*/ }
	int iReturFraRekurs = 4; // default. test om dette skjer nokon plass om du har probl.

	// hugs a-b !=> b-a 	a   b c
	for( int i=0; i<ANTALLPARTIKLER ; i++ )
	{
		if( boolHarSjekkaPartikkelNr[i] ){ continue; }
		if( i == megPartId  ){ continue; }


		// metode 1:
//		mapSortertAvstIdArray[ avstand MellomPartikler[megPartId][i] ] = i;
 		mapSortertAvstIdArray[ (*masse::pAlleEnheterMapPeik)[megPartId]->getAvstandTilObjekt(i) ] = i;
		// metode 2:
//		mapSortertAvstIdArray.insert(pair<double,int>(avstandMellomPartikler[megPartId][i], i));


	}

//{3 utskrift av avstander og derretter nermaste-liste.
//		for( mIter = mapSortertAvstIdArray.begin() ; mIter != mapSortertAvstIdArray.end() ; mIter++)
//		{
//			print f("avst. %f . %d\n", mIter->first, mIter->second);
//		}
//		//for(int i=0; i<ANTALLPARTIKLER ; i++) print f("avst. %f . %d\n", mapSortertAvstIdArray.first, mapSortertAvstIdArray.second);
//		if( debugUtskriftNivaa > 2){	for( int i = 0; i<4; i++){ print f("nermaste %d : %d\n", megPartId, tempNermasteAvstId[i]); }  } //}3
	
	// sjekker om spm til rek funk stemmer, isåfall returner true.
	mIter = mapSortertAvstIdArray.begin();
	if( mIter->second == erViParSpmFraPartId ) // second er id-feltet.
	{
		return 1;
	}

	//Har no laga nermaste-liste.
	//for( lfIterTNL = tempNermastListe.begin(), liIterTNLId = tempNermastListeId.begin();lfIterTNL != tempNermastListe.end();lfIterTNL++,liIterTNLId++ )
	for( mIter = mapSortertAvstIdArray.begin() ; mIter != mapSortertAvstIdArray.end() ; mIter++)
	{ //{
		if( mIter->first == 0.0 ){ printf("\nFeil. Avstand = 0.0 gruppering.cpp:179\n");  exit(-99); } // skal ikkje skje, nemmelig.
			
		if( (iReturFraRekurs = erViNermastePartikklerRekursFunk( megPartId, mIter->second )) == 1 ) // dersom returnerer true.
		{
			// Retur er mao true.
			// Vi er mao nermast kvarandre.
					
			// Lag "par" av dei.
			int partNr = mIter->second;// tempNermasteAvstId[iter];

			boolHarSjekkaPartikkelNr[megPartId] 	= true;
			boolHarSjekkaPartikkelNr[partNr] 	= true;
//print f("Nermaste: %d og %d\n - parrrer", megPartId, partNr);
			// Må endrast fra *.* til *->*  og frærne & fra høgresida?
		
	//	print f("Etter %d\n",megPartId);
			// ikkje naudsynt lenger??
			if( megPartId<0 || partNr<0)
			{ 
				return (-1); //return "gjør ingenting som resultat av denne returnen"
			}
				
			//XXX er dette rett?: (overgang fra pPart til (*masse::pAlleEnheterMapPeik)
			//Kanskje legge inn en sjekk om pAlleEnheterMapPeik[id] finnes? XXX
			(*masse::pAlleEnheterMapPeik)[megPartId]->pNermaste 	= (*masse::pAlleEnheterMapPeik)[ partNr ];      //Er allerede peiker
			(*masse::pAlleEnheterMapPeik)[ partNr ]->pNermaste 	= (*masse::pAlleEnheterMapPeik)[ megPartId ]; 	//Er allerede peiker
			
			return 0; // Eg vart enig med meg sjølv at return false når lager par. sjå ./kladdForRekursFunk
		//}else if(iReturFraRekurs == 0){
			// returner vidare. skal ikkje gjøre noko med partiklane og par osv. er gjort lenger inn i rekurs.
		//	return -2; // dersom 0, gå vidare ut, -1: ikkje gjør det..
		}/*else if( iter == 3 ){
			// har no gått igjennom heile nærleikskø. hånter.
			print f("Gjekk gjennom heile nærleikskø. sjå gruppering.cpp:170. Potensiellt Feil.\n, men muligens ikkje. oddetal partikler?\n"); // sjå ./kladdForRekursFunk 
			
			if( erViParSpmFraPartId == -100 ) // ytterste rekurs. spes modus.
			{
				// returnerte 0 fra neste rekurs, og er i ytterste rekurs.
				// Setter parre med seg sjølv??
				// Sjå eksempelet i ./kladdRekursivFunk
				print f("\nSalig feilmelding. ikkje parra med noken. ytterste rekurs. retur -37 no. gruppering.cpp:138\n");
				//exit  (-37);	
				return -37;											 // Ensom partikkel på fære? 
			}											 // oddetal partikkler?
		}else{ // mao false
			// Sjekk neste i nærleikskø. fortsett? 
			// continue
		}*/


	} //}

	//ellers:
	// stemmer ikkje: print f("\n\n\t feil! gruppering.cpp:213\n"); 
} //}1

vector<masse*> gruppere( vector<masse*> partInput )
{ //{1 ... }
/******************************************************************************************
 *** Returnerer vektor til massePar, som er laget i denne funk vha. new()		***
 *** 											***
 ***************************************************************************************///

//XXX Her er noko pøkk!	kalkulerKraftMellomMasseSenter  XXX


	vector<masse*> returListe;//( ANTALLGRUPPER );  // gammelt med ANTALLGRUPPER	
	vector<masse*>::iterator lppi = returListe.begin(); 

	// kan nok ta bort lPartIt
	//vector<masse*>::iterator lPartIt = partInput.begin();
		
	//{2 null ut  boolHarTattPartNrIgruppe for ny gjennomkjøring.
	for( int it = 0; it < ANTALLPARTIKLER; it ++)
	{
		boolHarSjekkaPartikkelNr[it] = false;
		boolHarTattPartNrIgruppe[it] = false; 
	} //}2

	for(int iter = 0 ; iter < partInput.size() ; lppi++, iter++){ //{2

		//{3 no er det litt rotete.
	
		// Gå over til å brute iterator istedefor [iter]


		// Lag en if-test her.
		// if boolHarTattPartNrIgruppe[iter]
		//}   continue; // fortsett med løkka, og iter går opp til ++

		if( (-37) == erViNermastePartikklerRekursFunk( -100, partInput[iter]->getId() ) ) //dersom returnerer false:
 		{ //{3 ... }
			// gjør noko
			printf("Partikkel (%d) er antagelig aleine. vart ikkje parra med nokon\ngruppering.cpp:174\n", partInput[iter]->getId() );
	//		exit(-1);
		}//else{ //} den returnerer da true.
											// skal her stå megPartId istadenfor -100??
		if( partInput[ iter ]->pNermaste == NULL && erViNermastePartikklerRekursFunk( -100, partInput[iter]->getId() )){ 
			//{ pNermaste er NULL, kaller erViNermastePartikklerRekursFunk igjen for å endre dette.
															// dersom dette mislykkes, går vi inn i if.
//			lPartIt->kalkulerAvstander();
			//VEIT IKKJE HEILT KVA, men gjer noke!
			// (alltid lag utskrift ved exit)
			printf("\n\t\tEXIT l 213.exit(0)\t\tfra %d: pNermaste == NULL\n", iter);
			printf("\t\tMen Kanskje det er fiksa allerede.. I if-testen som bestemmer at skal skrive ut dette. gruppering:232  \n");
			exit(0); // for å hindre segfault seinare om [5-50 L]
			//Ivertfall feil:
			//lPartIt->pNermaste = &*lPartIt;
		} 	//}

		int nermasteId = (partInput[ iter ]->pNermaste)->getId();

		if( boolHarTattPartNrIgruppe[iter] ||  boolHarTattPartNrIgruppe[nermasteId]) 		{ continue; } 
	
		boolHarTattPartNrIgruppe[iter] 			= true;
		boolHarTattPartNrIgruppe[ nermasteId ] 		= true;

		// ER IKKJE SIKKER OM FUNKER ENDA. TANKEN ER GOD, MEN HAR NOKRE SIDER MED error FRA g++ for tida.. FIXME
		returListe.push_back( new massePar( partInput[iter], partInput[ nermasteId ]) );	// var &p Part.. men p Part er gjort om til vektor av peikere.

//{ komentarer og utkommenterte linjer.
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * 
		 * * * OK - laga returliste osv. = halvparten så stor
		 * * * som input.
		 * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*	
		lppi->fellesMasse =  sammenlagtMasse;
		
		lppi->mPos[0] = 	(part1Masse * (lppi->pMasseEn)->pos(0) +
		            	 	(part2Masse * (lppi->pMasseTo)->pos(0)))
			       	 	/ sammenlagtMasse;

		lppi->mPos[1] = 	(part1Masse * (lppi->pMasseEn)->pos(1) +
		            		(part2Masse * (lppi->pMasseTo)->pos(1)))
			       	 	/ sammenlagtMasse;
		
		lppi->mPos[2] = 	(part1Masse * (lppi->pMasseEn)->pos(2) +
		            	 	(part2Masse * (lppi->pMasseTo)->pos(2)))
			       	 	/ sammenlagtMasse;
*/ //}
	} //}2
	
	return returListe;
}//}1


//XXX flytt til main.cpp
void skrivUtGrupper(vector<masse*> mpV)
{//{2 Skriv ut grupper.
	 
	
	double pos1[3];
	double pos2[3];
	//prøver å lage en ny iterator.
//	for( vector<massePar>::iterator lppiny = mp.begin() ; lppiny < mp.end()  ; lppiny++){ 
//		print f("ID [%d, %d]\n", (lppiny->pMasseEn)->getId(), (lppiny->pMasseTo)->getId());

	// skriv ut grupper	
	printf("_____________________________________________________________________________________________________________________________________________________ \n\n");
	for(int iter=0 ; mpV[iter] != *mpV.end() ; iter++){
		
		masse::skrivUt( mpV[iter] );
	}

}      	//}2

// vim:fdm=marker:fmr=//{,//} : fdl=1
