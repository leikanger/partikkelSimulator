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

class neuron
{	
	private:	
		//int enhetsId;
		double neuronPos[3];


		float mengdeAtractionLigandSkiltUt_forsterking;
		int antallSynapserSomNeuronetVilHa;
 		int antallSynapser;//std::list<vektor> synapser; TODO lag om til liste av synapser. for å sjekke lagingstidspkt.

		axon neuronetsAxon;

	public:
		neuron();

		static int antallNeuronInitiert;
		//static int getAntallObjekt() { return antallObjekter; }

		virtual int kalkulerKraftMellomMasseSenter() ;
		float oppdaterAR_ligand(){
			// XXX har bare atraction implementert. Skal ha repulsion også ved nydannelse av synapse, eller som går mot null når synapse er ferdiggrodd...
			return mengdeAtractionLigandSkiltUt_forsterking * (antallSynapserSomNeuronetVilHa-antallSynapser);
		}
		
		//double color[3]; 		// skal bort. // VARME??
								
	
		virtual std::string getObjektType( bool taMedId ) const;

		friend class axon;
};


extern void LagreTilstandsvariableIFil();  //funker ikkje.
extern int  LesUtTilstandsvariableFraFil();//funker ikkje.

extern void * holdStyrPaaPart(void*); 		//for tråder.
extern void * skallFunkForTraad(void*); 	//for tråder.

//extern void toggleMasseFjoerDempetSystem(); 	//endre til pause..
#endif

// vim: fdm=marker:fmr=/{,/}
