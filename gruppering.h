#ifndef Gruppering
#define Gruppering

#ifndef stdVector //{
#define stdVector
	#include <vector>
#endif //}
#ifndef String //{
#define String
	#include <string>
#endif //}

//#define ANTALLGRUPPER massePar::nConstAntallObjekterTotalt
#define ANTALLGRUPPER (ANTALLPARTIKLER/2)  //    Heiter no static const int nConstAntallObjekter;|
// Ta med i class:grupper! ncAntallGrupper
// XXX
//) // er det bug med initiering av vektor i gruppere. returListe er feil str?


class massePar : public masse
{
	public:
		massePar(masse*, masse*);
	
	// -> Vekk:	
/*XXX*/	//	static const int nConstAntallObjekterTotalt; 	//Før: def. ANTALLGRUPPER ..
							// definert i gruppering.cpp til ANTALLPARTIKLER/2 for partikkelpar.
		static int antallObjekterInitiert;
		//static int getAntallObjekt() { return antallObjekterInitiert; }
	
	//	inn fra arv:
		virtual int kalkulerKraftMellomMasseSenter(){ printf("ERROR. feil funk. Her:39@gruppering.h \n"); }	//prøve å saumløst koble inn 
																	// kalkulerKraftMellomPartikler()
	// 	skal også inn fra arv:	
		//void kalkulerAvstanderMellomGrupper(std::vector<massePar>);
		void kalkulerAvstander()  { printf("Feil. Kalkuleravstander i gruppering uten vektor<masse*> - input. \n"); }
		void kalkulerAvstander(std::vector<masse*>);
		
	// 	skal også inn fra arv: Allerede??
		void summerKrefterPaaDetteMasseSenter();

		masse *pMasseEn;
		masse *pMasseTo;

		virtual std::string getObjektType( bool ) const;
};

extern std::vector<masse*> gruppere( std::vector<masse*> );
int erViNermastePartikklerRekursFunk(int erViParSpmFraPartId, int megPartId);
//void skrivUt(massePar mp);
#endif

// vim: fdm=marker:fmr=/{,/}
