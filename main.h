
#include <iostream>
#include <fstream>
#include <iomanip>


// GLOBALE KONST-er

//har intensjoner om å bytte fra 100 til partikkel::ncUseAntall();
//#define ANTALLPARTIKLER 100 // må være minst n*2 dersom gruppering true..
//#define ANTALLPARTIKLER partikkel::ncUseAntall()

//#define ANTALLPARTIKLER *pncAntallPartikler
//#define ANTALLPARTIKLER 100
extern const int * pncAntallPartikler;

#define pDEBUG (*pout) // ubuffra alternativ: std::cerr
#define cDEBUG cerr 
#define QWER_Her_foer  cDEBUG << "Kom hit. QWER_Her_foer \n"
#define QWER_Her_etter cDEBUG << "Kom hit. QWER_Her_etter\n"
// ta med i class:partikkel : ncAntallPartikler
// istenden!
//


#define VENTMILLISEK 10 // det er ikkje bare her (opengl) problemer . også i kalkulerting av massepos.
#define MINSTEAVSTAND 3e-5
#define STARTFART_TANG 5e-4 
#define G 1e-8
#define LUFTMOTSTANDFAKTOR 0 //1e-3
#define GRENSE 1.3 	// definerer partikkelvegg i alle retninger. 1 er kant på skjerm.

#define FJAER_KONST 5e-4
#define DEMPER_KONST 5e-3
//#define MAXKRAFT 1e-5 

// sjå gruppering.cpp/h

#define debugMode  false
// definerer debug-utskrift-nivå. Dersom eg arbeider med en funk, blir det straks mykje 
// høgare utskriftsnivå på den. Nivå 1-4. 1-bare VIKTIGE ting, 3- skriv alt.
// God ide, Ikkje i bruk...
#define debugUtskriftNivaa 1

#define ELASTISKEKOLLISJONER 	true 

#define PARTIKKEL_FORM_BALL true
#define PARTIKKEL_FORM_KUBE false

//#define SPIN ... for seinare å evt implementere spin i prog, og i elastiske støt..

#define 	full3D 			true  //ikkje i bruk(trur eg)
#define 	partiklerPaaEitPlan 	false //ikkje i bruk(trur eg)
// Påvirker utsjånad
#define 	KOORDSYS 		true
#define 	VEGG1 			false
#define 	SVART 			false //svart bakgrunn?
#define 	KUBE 			true 
#define 	ALFA_KUBE 		false
#define  	ALFA_VERDI_KUBE 	0.2f
#define 	KUBEFARGE_R 		0.25
#define 	KUBEFARGE_G 		0.55
#define 	KUBEFARGE_B 		0.455555
#define 	NATURLIG_LYS 		true

// Bestemmer grader av paralellisering:
#define ANTALLTRAADER 3

// bestemmer statisk array eller dynamisk vector av partikler.
//#define DYNAMISK false 	deprecated..

#include <string>
using std::string;
using std::cout;
using std::cerr;
//...

namespace skinn{
	//Utskriftsstøymer:
	extern std::ofstream & useUtskriftsFil_alternativ_P( int =0);  	// kanskje std:: før ostream?
	extern std::ofstream & useUtskriftsFil_alternativ_S( int =0); 
	extern std::ostream * pout;// = &cout;
	extern std::ostream * altOut_p;// = &cout;
	// Div funk.
	extern void avsluttSafe(); 		//sørger for verdig avsluttning av tråder. forhindrer segf.
	extern int clearScreen(int ptsNr );  	//sender clear > /dev/pts/ptsNr

	extern const int ncUseArg(int); 

	//Skal inn i namespace main:
	extern bool globalAvluttProgramVariabel;
	extern bool alternativUtskrift_SkallBool; 
}

using skinn::pout;


struct kritisk_feil{
	kritisk_feil(){ 	printf("Ingen argument til kritiskfeil-konstruktor.\n"); 	}
	kritisk_feil( string tekst ) : feilmelding(tekst) {}
	static int antallF;
	void (*handter)();
	
	// ..
	string feilmelding;
	void print(){ 	std::cerr<<"Feilmelding: " <<feilmelding ;   	}
};

struct peikerfeil : public kritisk_feil {
	string peikerPaaType;
	void* peikerPaaAdr;
	peikerfeil(string peikerType, void* i) : kritisk_feil("peikerfeil"), peikerPaaType(peikerType), peikerPaaAdr(i){  /* konstruktor.*/ }
};
//struct nullPeikerFeil : public peikerfeil{
//	nullPeikerFeil(){ peikerfeil(0); }
//};
struct feil_i_objektId : public kritisk_feil {
	feil_i_objektId( string tekst ) : kritisk_feil(tekst){ /*Gjør om til fixBarFeil, og legg inn (*handter)() - funk*/ }
};

struct pThreadFeil : public kritisk_feil {
	pThreadFeil( string feiltekst ) : kritisk_feil( feiltekst ) {}
	// noke..
};

//struct feil_i_system_kall : public kritisk_feil {
//	feil_i_system_kall( string feiltekst ) : kritisk_feil( feiltekst ) {}	 
//};


struct fixBarFeil{ };
struct mangler_pNermaste : public fixBarFeil{
	masse* masseSomMangler_pNermaste;
	mangler_pNermaste(masse* meg){ masseSomMangler_pNermaste = meg; }
};


// vim: fdm=marker:fmr=/{,/}
