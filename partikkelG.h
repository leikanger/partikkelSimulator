//#include "gruppering.h"
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

class partikkel : public masse
{	
	private:	
		//int enhetsId;
		double partikkelA[3];
//		double partikkelV[3]; 		-> mV[3]
//		double partikkelPos[3]; 	-> mPos[3]
//		double partikkelF[3]; 		-> m F[3] - endra til koord. mF
//		double gruppeEksternKraft[3]; 	-> eksternKraftPaaMeg[3]
 		
						/* plan: (skal brukes til) /{ double partikkelRotasjon[3];
						// 	- rotasjon (visuellt reelt)
						// 	- etter kvart ta med i elastisk støt, s.a. nyrot regnes ut ved støt.
						// 	- evt. andre fysiske fenomen.
						// 	- kamera festa i en partikkel, s.a. kamera translateres og roteres. /} */

	public:
		partikkel();
		//partikkel(double, double,double,double);
		//~partikkel(){ antallObjekter--; }

		static int antallObjekterInitiert;
		//static int getAntallObjekt() { return antallObjekter; }

		virtual int kalkulerKraftMellomMasseSenter() ;
		
		void kalkulerAvstander(std::vector<masse*>);
		void kalkulerAvstander();
		int krasjtid;
		void kollisjon(int partikkelId, bool);
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

extern void toggleMasseFjoerDempetSystem(); 	//leik! (prøv space)
#endif

// vim: fdm=marker:fmr=/{,/}
