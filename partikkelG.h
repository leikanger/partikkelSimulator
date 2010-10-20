#include "masseG.h"

#ifndef String //{
#define String
	#include <string>
#endif //}
#ifndef stdVector //{
#define stdVector
	#include <vector>
#endif //}
#ifndef stdMap //{
#define stdMap
	#include <map>
#endif //}


// redo-guard /{
#ifndef Partikk
#define Partikk
//}


/***********************************************************************************************
******                                                                                  ********
******      axon: for å simulere vekst av axon. Etterkvart kan også desse kanskje       ********
******            brukes i ferdig neuralnett?                                           ********
******                                                                                  ********
******      Trenger tidsforseinking i axonal overføring. Dette kan eg gjøre ved at      ********
******            alle segmenta i axon (vekststega) er lagt til i en lenka liste.       ********
******            Når overføring skal skje, kan axonsegmenta tilogmed axonsegment som   ********
******            er med i tidsiterasjonen til systemet, overføre. Neste blir i neste   ********
******            iterasjon..                                                           ********
******                                                                                  ********
******     Når det gjelder repulsion, så kan kanskje axona sjølv skille ut repulsor-ligand******
******            slik at to akson ikkje kan ligge på samme sted? Får litt avstand..    ********
******            Dette kan også bidra i å avslutte vekstfasen (når A = R avsluttes fasen)******
******                                                                                  ********
***********************************************************************************************/

/*
** 	Planlegging:

** 	Lenka liste:
* 	 	(sørger for kausalitet (retning) for axon overføring. Kan også holde styr på tidsdelay ved axon-overføring)
 			- Axon-segment skal legges til i lenka liste, slik at det blir retning på de. 
 			- Dersom 'collateral', skal eit collateral-element legges til, med to lenker vidare
			ellers heilt likt. Dette kan være nedarva klasse fra class axon-segment.

** 	Growth cone: 
*		(tuppen på vaksande axon. Har andre egenskaper enn axonSegment, i tillegg. Nedarva fra axonSegment)
 			- Fremst i eit voksande axon skal det være en 'growth cone', som kan vakse vidare. Denne er ansvarlig for å legge til sin posisjon i axonSegment-lenka 
				liste når den gror vidare. Også andre ting som er viktig for axonet...
 		 	- 

** 	AxonSegment:
* 		(discret axon-segment, med posisjon, repulion ligand, ...)
			- skal sende ut litt 'repulsion ligand' for å hindre at to gror over kvarandre. Spesielt viktig i 'growth cone'?

** 	AxonHillock: 	( Dette skal være det som neuronet inneheld.. )
* 		(er ikkje sikker på kvifor eg skal ha med denne, men kan være nyttig seinare? --Lettare å innføre denne funksjonaliteten. Kan peike på eit felles hillock-obj.)

*/



// Begynner med axonSegment
/**********************************************************
*** 							***
***  	class axonSegment 				***
*** 		- variabler: 				***
*** 			- koordinat posisjon; 		***
*** 			- float repulsionFaktor 	***
*** 			(grad av utskilling av R-ligand)***
*** 			
*/
class axonSegment{
 	private:
		koordinat Koord_posisjon;
		float fRepulsionFaktor;

		axonSegment* pSegm_forrigeSegment;
		axonSegment* pSegm_nesteSegment;
	public: // XXX eller protected? skal kun lages av growt-cone... Finn ut om dette går an for constructor.

		//(skal kun initieres av axon-growt-cone:)
		axonSegment(axonSegment* pForrigeSegmArg, koordinat posArg, float fR_FaktorArg) :
			pSegm_forrigeSegment(pForrigeSegmArg), Koord_posisjon(posArg), fRepulsionFaktor(fR_FaktorArg) {}

};


/******************************************************************************************
*** 	class axonGrowthCone : public axonSegment 					***
*** 		- variabler: 								***
*** 			Nedarva fra axonSegment:  	 				***
*			posisjon, retning, repulsionFaktor 				*** 
***			- koordinat retning (normalisert retningsvektor) 		***
***
*** 		- funksjoner:
***

*/
class axonGrowthCone : public axonSegment{


};

/******************************************************************************************
	class axonHillock : public axonSegment
		skal være medlem av neuron-klassa. Veit ikkje kvifor, men for lettare innføring av alternativt nye funksjonaliteter..
*/


class axon : public masse
{	
	private:	
		// XXX legg inn lenka liste for å lage retning på aksonet. Bare siste element kan vakse.. Og har axonF, osv.
		// Alle segmenta kan skille ut repulsion-ligand..
		double axonF[3];
//		double axonV[3]; 		-> mV[3]
//		double axonPos[3]; 	-> mPos[3]
//		double axonF[3]; 		-> m F[3] - endra til koord. mF
//		double gruppeEksternKraft[3]; 	-> eksternKraftPaaMeg[3]
 		
						/* plan: (skal brukes til) /{ double axonRotasjon[3];
						// 	- rotasjon (visuellt reelt)
						// 	- etter kvart ta med i elastisk støt, s.a. nyrot regnes ut ved støt.
						// 	- evt. andre fysiske fenomen.
						// 	- kamera festa i en axon, s.a. kamera translateres og roteres. /} */

	public:
		axon();
		//axon(double, double,double,double);
		//~axon(){ antallObjekter--; }

		static int antallObjekterInitiert;
		//static int getAntallObjekt() { return antallObjekter; }

		virtual int kalkulerKraftMotNeuronSenter() ;
		
		void kalkulerAvstander(std::vector<masse*>);
		void kalkulerAvstander();
		int krasjtid;
		void kollisjon(int axonId, bool);
		void kollisjon(masse*);
		int status;
		//double color[3]; 		// skal bort. // VARME??
		void kalkulerBane();
								
	
		virtual std::string getObjektType( bool taMedId ) const;
};

extern void LagreTilstandsvariableIFil();  //funker ikkje.
extern int  LesUtTilstandsvariableFraFil();//funker ikkje.

extern void * holdStyrPaaPart(void*); 		//for tråder.
extern void * skallFunkForTraad(void*); 	//for tråder.

//extern void toggleMasseFjoerDempetSystem(); 	//XXX endre til pause...
#endif

// vim: fdm=marker:fmr=/{,/}
