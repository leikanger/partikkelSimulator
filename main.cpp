//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//  * * * * * * * * * * *      main,cpp - inneholder hoveddelen av prog, argumentlesing osv.  * * * * * * * * * * *
//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Filbeskrivelse / kommentar //{1
/*
 * 	inneholder main(), innlesing av argument, andre globale funksjoner, variabler osv.
 */ 
//}

// 		#include //{1   		TODO
// #include <iostream>
#include <stdlib.h>
#include <math.h>  //??

// for bra termintering av tråder/prog.
#include <signal.h>

#include "partikkelG.h"
#include "gruppering.h"
#include "main.h"

//}1
using namespace std;
// Eksterne deklarasjoner av funk og var //{1
extern int mainTestFunk(); // ekstern funk fra utproevingAvNyeAspekt.cpp 
extern int openglMain(int* argcP, char** argvPP);

//extern double allePartikkelXYZ[3][ANTALLPARTIKLER];  //Legg denne inn i partikkel-klassa som static double & -funk

//extern vector<masse*> pPart; // ANTALL PARTIKLER - stor. // eller er den det? orges i main(?)
//vector<masse*> pPartDynamisk;

// pThread og mutex-er
//
// XXX Ta inn mutex / pthread inn her? (def.)
extern pthread_mutex_t posmutex;
extern pthread_mutex_t mutexVent1;
//}1

const int ncUseArg(int argTall =10)  //Isteden for variable. Init foerste gang den blir kalt. merk & i returverdi const int &. Ikkje naudsynt. For liten var. og const.
//const int & ncUseArg(int argTall =10)  
{  	//f.eks. 10. Kan settes ved #define INIT_ANTALL_PART eller noke. //{9
	static int harVertHerFoerGanger = 0; // for å gjøre noke første gang var-funk brukes.

	if( !harVertHerFoerGanger ){ printf("INITIALISERER antall partikler til %d\n", argTall); }
 	// for debugging:	->	->	else{ printf("Variabelfunk brukt %d ganger.\n", harVertHerFoerGanger); }
	harVertHerFoerGanger ++;

	static const int nAntallPartikler = argTall;

	return nAntallPartikler; 	
} //}9

// For å lage vektor<masse> p Part:
//{9 Deklarasjon av variabler.
//Dårlig fiks(eller bra? må sende inn masse-obj i en funk, og må ha peiker for å aksessere massenes partikkel-funk.er..) (???) :
//partikkel partikkel_variabel_pga_konstruktor_kjoerer_ikkje_i_vector_init[ANTALL PARTIKLER];
//Bytte ut med new..

//trur eg har funne løysinga. XXX
// - Ha en global funk som returnerer (masse*) _ / masse& av vektor/map(?) element med id ; arg
// 		: evt objekt i.s.f. funk.	
// 			- isåfall global variabel eller lokal som sendes inn i kvar tråd som arg?
// 				- lokal, delmengde som sendes inn i tråd. (deler opp mengde)
// 				- eller noke. Trenger å tenke på at alle element skal være tilgjengelig for alle, s.a. det er mulig å hente ut b-a avst. fra a (i.s.f. at a-b kalk)
// 			- eller en lokal peiker som sendes som argument?
// 				- map<int, masse*> peiker. inneholder alle masser. 
// 				- mapen som peikes på blir laga i main. før tråder blir til.
//

// XXX lag ferdigflagg i kvar partikkel, s.a. når ferdigflagg er reist, er alle avstander for det obj. gyldige. Senke flagg i starten av kvar iterasjon, heise når alle er regna 
//  	ferdig. Da kan neste utregning -> kraftutregning - starte (denne trenger gyldige verdier i avstander. XXX
//  	kanskje la ferdigflagg være mutex som er initiellt låst i kvar iter., og blir ulåst når produsent er ferdig..
//}9

int returFraPthreadCreate;
pthread_t kalkuleringstraad;
 //for å holde styr på kva hovedtråden er, og da spesiellt for å terminere denne..
bool skinn::globalAvluttProgramVariabel = false; 
//}1

int innInt;
string strAlternativUtskriftFilAdr = "";
bool testKjoeringBool = false;
bool dynamiskBool = false;
bool displayBool = true;  	 	// i tilfelle debugging, slå av display.
bool skinn::alternativUtskrift_SkallBool=false;  	// i tilfelle debugging, slå av display.
bool grupperPartiklerBool = false;

ostream * skinn::pout = &cout;
ostream * skinn::altOut_p = &cerr; //default. sikrer mot segf.
int skinn::clearScreen(int ptsNr )
{
	std::ostringstream kommando;
	kommando << "clear < " <<"/dev/pts/" <<ptsNr <<std::endl;
	string temp = kommando.str();
	// Velger å skrive ut på standardplass for feilsøking av utskrift. minst mulig kluss..
	cout  	<<temp;
	return system( temp.c_str() );
}

ofstream & skinn::useUtskriftsFil_alternativ_P( int ptsNr /*=0*/ )
{ //{4

	if( ! skinn::alternativUtskrift_SkallBool && ptsNr ) //Første gang denne funk kalles, og ptsNr arg er med => OK
	{
		// Det ser ut til å være ok.
		if( ptsNr > 9 || ptsNr < 1 ){ cerr<<"Må ha gyldige verdier mellom 1 og 9. Ikkje " <<ptsNr <<endl; exit(-1); }
		ostringstream ptsFilAdrStream;
		ptsFilAdrStream <<"/dev/pts/" <<ptsNr;
		strAlternativUtskriftFilAdr = "";
		strAlternativUtskriftFilAdr = ptsFilAdrStream.str();			
		
		cerr<<"Opner utskrift til alternativ utskrifts(fil) " <<strAlternativUtskriftFilAdr <<endl;
	}else if( ! skinn::alternativUtskrift_SkallBool ){ cerr<<"Feil ved init av skinn::useUtskriftsFil_alternativ_P( int ) . Tallet er dårlig. =0 (har du glømt å sende inn arg? )."; }

	static ofstream utskriftsFil( strAlternativUtskriftFilAdr.c_str() ); 

	if( ! skinn::alternativUtskrift_SkallBool ){ //kjører første gangen.
	      	if( !utskriftsFil ){ 
			cerr<<"FEIL Klarte ikkje åpne utskrift(sfil) " <<strAlternativUtskriftFilAdr <<endl; 
			exit(-1); 
		}
		strAlternativUtskriftFilAdr = "clear > " + strAlternativUtskriftFilAdr;
		
		if( system( strAlternativUtskriftFilAdr.c_str() ))  utskriftsFil << "\n\n\n\n\n\n\n\n\n\n\n\n" ; // renser alternativ-uts-(fil)-pts litt. (bare frste kjring av funk
		cout<<strAlternativUtskriftFilAdr <<endl;
	}

	// Må være med:
	skinn::alternativUtskrift_SkallBool = true;
	skinn::altOut_p = &utskriftsFil;

	return utskriftsFil;
} //}4


// XXX lag en skikkelig ofstream-klasse der det ligger peiker til gyldig ostream, init av bool, ostream, osv..

// gjør om til ofstream * .... -funk. Tenk på Rett over her skinn::altOut_p blir init inne i funk, og blir brukt derretter. Lag noke slik returverdi og.
ofstream & skinn::useUtskriftsFil_alternativ_S( int ptsNr /*=0*/ )
{ //{4

	if( ptsNr ) //Første gang denne funk kalles, og ptsNr arg er med => OK
	{
		cout<<"Inne i skinn::useUtskriftsFil_alternativ_S(int). Int er ikkje tom. qwer230\tDette skal skje EN gang per kjøring.\n";
		// Det ser ut til å være ok.
		if( ptsNr > 9 || ptsNr < 1 ){ cout<<"Må ha gyldige verdier mellom 1 og 9. Ikkje " <<ptsNr <<endl; exit(-1); }
		ostringstream ptsFilAdrStream;
		ptsFilAdrStream <<"/dev/pts/" <<ptsNr;
		strAlternativUtskriftFilAdr = ptsFilAdrStream.str();			
		
		cout<<"Opner utskrift til alternativ utskrifts(fil) " <<strAlternativUtskriftFilAdr <<endl;
	}

	static ofstream utskriftsFil( strAlternativUtskriftFilAdr.c_str() ); 

	if( ptsNr )
	{
		string superTemp;
		superTemp = "clear > " + strAlternativUtskriftFilAdr;
		if( system( superTemp.c_str() )  ) utskriftsFil<<"\n\n\n\n\n\n\n\n\n\n";
	 	cout<< superTemp <<" - Dette skal skje bare en gang også. Dersom qwer231 to-tre-EN er fra før, så er dette feil. Ellers, forventa.\n";
	}
	return utskriftsFil;
} //}4





int main(int argc, char *argv[])
{ // ... } //{1
	// renser skjerm til debuggingutskrift.

	//if( system("clear") ) cout<<"Fekk ikkje til system(\"clear\"). Drite no ej i!" ;

	// Leser inn argument: //{2 if( argc>1 && ((innInt=atoi(argv[1]))>0) )
	if( argc>1 )
 	{
		int innIntPos =1;

		while( argv[innIntPos][0] == '-' )
		{
			printf("argv[%d]: %s \n", innIntPos, argv[innIntPos]);

			switch( argv[innIntPos][1] )
			{
	 			case 'd':
					printf("Setter utførelse av partikler til dynamisk.   \t -%c som argument. \n", argv[innIntPos][1] );
					dynamiskBool = true;
					break;
				case 'n':
					printf("M.a.o. uten skjermbilde. \t -%c som argument. \n", argv[innIntPos][1] );
					displayBool = false;
					break;
				case 't': case 'T':
					printf("Testkjøring, \t jmf. -%c som argument.\n", argv[innIntPos][1] );
					testKjoeringBool = true;
					break;
				case 'g': case 'G':
					printf("Slår på gruppering av partikler, \t jmf. -%c som argument.\n", argv[innIntPos][1] );
					printf("Men funker ikkje heilt enda... \n");
					grupperPartiklerBool = true;
					break;
				case 'p': case 'P':
					//char tempc[3] = argv[innIntPos];
					if( innInt = atoi( &argv[innIntPos][2] )   )
					{
						skinn::useUtskriftsFil_alternativ_P( innInt ); //initialiserer useUtskriftsFil_alternativ_P med innInt
						//alternativ UtskriftPtsBool = true;
					
					}else if( innInt = atoi( argv[++innIntPos] )   )
					{
						//sjekker neste pos også:
						// og kommer hit om den gjelder.
						skinn::useUtskriftsFil_alternativ_P( innInt ); //initialiserer useUtskriftsFil_alternativ_P med innInt
					}else 
					{ 
						printf("Forstår ikkje argument. rydd opp, og prøv igjen. \n");
						exit(0); //Eg gir opp!
					}	

					// useUtskriftsFil_alternativ_P() er no initialisert, og klar til bruk. (pts # %d)
					
	 				
					if( innInt>9 ){ printf("Feil. Ikkje støtte for slike tall for pts/%d Prøv igjen mellom 1-9.\n",innInt); exit(0); } 
					//sjekker pts, og avslutter om verdien er useriøs..
					
					skinn::useUtskriftsFil_alternativ_P() 	<<"\n" <<argv[innIntPos] 	<<". printalternativ . Sender alternativutskrift til /dev/pts/"
								<<innInt <<" (hit..) \t\t useUtskriftsFil_alternativ_P()" <<"\"(denne linja er skrevetut slik.)\"\n\n\n\n\n\n" ;
					cout<< "Suplementær utskrift til " <<strAlternativUtskriftFilAdr <<", slått på.\t jmf. arg: " <<argv[innIntPos];
					break;
				case 's':
					if( innInt = atoi( &argv[innIntPos][2] )   )
					{
						if(innInt > 0 && innInt < 10 )
							skinn::useUtskriftsFil_alternativ_S( innInt ); //initialiserer useUtskriftsFil_alternativ_S med innInt
						else{
							pDEBUG<<"FEIL. qwer625 ugyldig adresse/ nummer til alternativ utskriftsplass. (-s): " <<argv[innIntPos] <<std::endl;
							exit(0);
						}
					
						pout = &skinn::useUtskriftsFil_alternativ_S();
					}else if( innInt = atoi( argv[++innIntPos] )   )
					{
						//sjekker neste pos også:
						// og kommer hit om den gjelder.
						if(innInt > 0 && innInt < 10 )
							skinn::useUtskriftsFil_alternativ_S( innInt ); //initialiserer skinn::useUtskriftsFil_alternativ_S med innInt
						else{
							pDEBUG<<"FEIL. qwer625 ugyldig adresse/ nummer til alternativ utskriftsplass. (-s): " <<argv[innIntPos] <<std::endl;
							exit(0);
						}
						
						pout = &skinn::useUtskriftsFil_alternativ_S();
					}else 
					{ 
						printf("Forstår ikkje argument. rydd opp, og prøv igjen. \n");
						exit(0); //Eg gir opp!
					}
					cout    <<"\n" <<argv[innIntPos] <<" . send . Sender utskrift til /dev/pts/" <<innInt <<" \t\t\t\t(*pout)<<_\n\n" ;
					(*pout) <<argv[innIntPos] 	<<". send . Sender utskrift til /dev/pts/" <<innInt <<" (hit..) \t\t\t\t(*pout)<<_\n\n\n\n\n\n" ;

					break;
				// og anna ...
				case '0':
					printf("Jejeje. -0 betyr kanskje nullpeiker. Du ba om det [neste linje] : \n");
					printf("*((int*)0); : %d\n",*((int*)0) ); //segfault!!
					break;
				default:
					printf("Ukjendt parameter. %s \n", argv[innIntPos] );
			}
			// evt andre options..
		
			// går vidare til neste option:
			if( argv[ innIntPos+1 ] )
				innIntPos++;
			else
				break;
		}
	 
		if( argc-1 == innIntPos )
		{
			//innIntPos p. på siste.
			if (( (innInt=atoi(argv[innIntPos])) >0) && innInt < 10000 )
			{
	 
				printf("Foreslådd antall partikler: %d \n",innInt); 
			
				//if(innInt % 2 != 0) printf("Antall partikler bør være partall. fikser.\nForeslådd antall partikler: %d \n",++innInt);
				if(innInt > 1000){
				     	printf("Kanskje litt mange med over 1000 partikler. Maskinen sliter med 400. \n");
			 		return 0;
				}
			}else if( innInt==0)
			{
				// innInt er lik null.
				printf("Antall partikkler må være > 0. \n");
				return 0;
			}else{ 
				printf("Du har ikkje lagt inn antallPartikler. Format: \n\t\t\t\t\t\t%s [-opt] [antallpartikler] \n", argv[0] );
				return 0; 
			}
		}else{
			printf("Du har glømt argument. avslutter.\n");
			return 0;
		}
	}else{
		printf("Tom innverdi. Format på kommando: %s [-options] [antallPartikler]\n", argv[0] ); 
		printf("\t- options er foreløpig begrensa til: \
					\n\t\t-p[*] - \talternativ utskrift til pts [*] (brukes ved useUtskriftsFil_alternativ_P()<<\"jepp\";)  \
					\n\t\t-n    - \tingen opengl-visning. for feilsøking. \
					\n\t\t-d    - \tdynamisk antall enheter. \
					\n\t\t-t    - \ttestfunk. \
					\n\t\t-s    - \tsilent - ingen utskrift her, eventuellt ustkrift i pts/? \
					\n\t\t-0    - \t???.\n\n"); 
		return 0;
	}  //}2
	// Initialiserer: //{3
	
	// Initialiserer ncUseArg():
	if(innInt < 10000 && innInt > 0) 	//liten feilsjekk, for å unngå feiltolka double-som-int eller tilsvarande..
		ncUseArg(innInt); 	// initialiserer ncUseArg()
	

	printf("Const antall partikkler er %d \n", ncUseArg() );


	// INITIALISERER masse::pAlleEnheterMapPeik :
	map<int, masse*> mapAlleEnheter;
	masse::pAlleEnheterMapPeik = &mapAlleEnheter;
	//}3

	
//{2 ordning av *pAlleEnheterMapPeik
	
	try{

		//default false
		if( testKjoeringBool )
			mainTestFunk();
			// det er kanskje mulig å bruke denne til å ta stikkprøver av prog. i tid også. dvs en tråd som startes, venter i n sek. , tar prøve (skriver ut til -p)
			// kommer ikkje videre om det er testKjøring. (-t, -T)	 exit(0) ...  foreløpig..

	
		if( dynamiskBool ){ 
		//{
			printf("Dynamisk er ikkje implementert enda. -d skal kjøre Partikkel.out dynamisk \n");
		//}
		}else{ //{3 ... }
		} //}3
		(*pout)<<"pForeløpig ingen forskjell mellom -d og ikkje -d. dynamiskBool har ingen betydning. Kanskje seinare, når masser kan deles/smelte ihop..\n";
		if( skinn::alternativUtskrift_SkallBool )  (*skinn::altOut_p)<<"aForeløpig ingen forskjell mellom -d og ikkje -d. \
							dynamiskBool har ingen betydning. Kanskje seinare, når masser kan deles/smelte ihop..\n";
		pout->flush(); skinn::altOut_p->flush(); //if( skinn::alternativUtskrift_SkallBool ) skinn::altOut_p->flush();

		if( skinn::alternativUtskrift_SkallBool ){
			(*skinn::altOut_p)<<"Jess. (*skall::altOut_p)<<\"funker\";" <<std::endl;
		}	
		// Lager instanser av partikkel (siste arg.-antall partikler. : )
		for( int it = 0; it < ncUseArg() ; it++)
		{
			partikkel* pPtemp = new partikkel(); 
								// kan segfaulten komme av at eg new-er for mykje? //{9
								//tester med statisk array av partikler. (5l. opp)
								//
								// Har funnet feilen etter  en og en halv dag med feilsøking!
								// 	Det har noke med ANTALLPARTIKLER å gjøre. om eg tar nok over ANTALLPARTIKLER, får eg segfaulten. 
								// 	FIXME Varierer med ANTALLPARTIKLER i main.h , ikkje lineært, ikkje likt, men øker når den øker, og
								// 		minker når den minker.
								// 	AHA! Inne i kalkulerKraftMellomMasser skriver den til kraftMellomPartArray[][] som er 
								// 				kraftMellomPartArray[ANTALLPARTIKLER][ANTALLPARTIKLER] - stor.
								// 	AHA!
								// 	Ohh jeah!
								//
								// 	Je og je.. No har eg såtte i snart to dager på dette. Laga en mektig koordinat klasse
								// 	istadenfor double[3] osv. med operatore osv.
								// 	jeje - kjekt er det!
								//}9

			(*masse::pAlleEnheterMapPeik)[ pPtemp->getId() ] = pPtemp;

		}

		masse::initStaticVariable(); // For å unngå alle feilmeldingene = antallPartikler ^ 2   utskrifter. Tar tid. For 100 part. 10000 utskrifter. Overaskende lang tid.

		if( (returFraPthreadCreate = pthread_create( &kalkuleringstraad , NULL,  holdStyrPaaPart , 0)) ) 		throw pThreadFeil( "!dynamiskBool" );

		


		if( displayBool )
			openglMain(&argc, argv);
		else{
			printf("\nDropper display etter ønske (-n) \n");
			while(1){ sleep(1); printf("HOVEDTRAAD kvart sek. \n"); (*pout)<<"HOVEDTRAAD kvart sek.\n"; 
				if(skinn::alternativUtskrift_SkallBool) skinn::useUtskriftsFil_alternativ_P() <<"HOVEDTRAAD kvart sek.\n"; }
		}
		// TODO Når eg lærer meir om ostreams, lag en ubuffra broadcast-variant av ?out som skriver på alle (1?2?3) skjerane.



		// ferdig med kode. klar for catch-statements:	



	}catch (peikerfeil pF){ 
		cerr<<"peikerfeil.\nPeikertype:\t" <<pF.peikerPaaType <<"\nVerdi \t\t[" <<pF.peikerPaaAdr <<"]\n"; 
		cerr<<"Kritisk feil. Terminerer\n";
		exit(-1); 
	}catch (kritisk_feil pKF)	{
		cerr<<"Kritisk feil. Terminerer.\n\n";
		pKF.print();
		printf("\n");
		exit(-1); 
	}
//}2



	return 0;
} //}1

// namespace main
void skinn::avsluttSafe()
{
	 
		//*****************************************
		printf("Prøver å avslutte på trådsafe måte (uten sf.)  \n");
		skinn::globalAvluttProgramVariabel = true;
		usleep(33); 			
		exit(0);
		//*****************************************
}

// vim:fdm=marker:fmr=//{,//} : fdl=2
