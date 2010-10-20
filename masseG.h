#include <cstdio>


#ifndef String //{
#define String
	#include <string>
#endif //}
#include <map> //trur ikkje det er nødvendig med ifndef for std-lib.

#ifndef stdVector //{
#define stdVector
	#include <vector>
#endif //}

//for toString , << og andre sting-streams
#include <sstream>


#ifndef Masse
#define Masse

// Lær meir
// SKAL VÆRE INTERFACE, skal ikkje være mulig å lage objekt av klasse.
// Trenger å lære meir om dette..
// Ok, Er no interface (pga. kalkulerAvstander =0) er rein virtuell funksjon. Var godt å rytta opp litt i dette. oppdaga at instans av masse som ikkje var peiker var arg i
// en funksjon (som ikkje var i bruk)

// Husk å ha med i alle filer som bruker det?(?)
// extern std::map<int, masse*> * masse::pAlleEnheterMapPeik;


class koordinat {
	private: 
		double xkoord, ykoord, zkoord;
		std::string type; 		//for utskrift.
	
		double * useKoordinatRetn(char retning)       { if(     retning == 'x' || retning == 'X'){ return & xkoord; }
		       				 	 	else if(retning == 'y' || retning == 'Y'){ return & ykoord; }
					    	   		else if(retning == 'z' || retning == 'Z'){ return & zkoord; }
			 					else{ printf("\n\n\n\n\n\n\n\n\n\n\t\t\tFEILverdi.errKode1234321 \n");  } 		  }


	public:
		koordinat( double x, double y, double z, std::string typeArg = "Gen.Vektor" )  	: xkoord(x), ykoord(y), zkoord(z), type(typeArg) {}
		koordinat( std::string typeArg ="default" )					: xkoord(0), ykoord(0), zkoord(0), type(typeArg) {}


		std::string getType()  			const {return type; }

		void skrivUt(std::string tekst ="", char retning =0 );
		//XXX skal vekk. luke beddet!
		
		void nyeVerdier( double x, double y, double z , std::string nyType ="") 	{ xkoord = x; ykoord=y; zkoord=z; if(!nyType.empty()){ type = nyType;} }
	//	void nyeVerdier( koordinat* pKoord ) 			{ xkoord = pKoord->xkoord; ykoord = pKoord->ykoord; zkoord = pKoord->zkoord; }
		
		std::string toString() const;

		double getVerdi( char retning )	const;
		double getVerdi( int retn ) 	const;
		// bruk: if( !vekt.erTom() ) ..	
		bool erTom()  			const  			{ if(xkoord || ykoord || xkoord){ return false; }else{ return true; }    	}

		//koordinat getKopi() const { return *this; } // foreløpig ubrukt
		
		void nullUt() 						{ xkoord = 0; ykoord = 0; zkoord = 0;  	}
		void leggTilVerdi( 	char retning, double verdi  ) 	{ (*useKoordinatRetn(retning) ) += verdi; 	} //utesta
		// den over kan være den under, om eg kaller den med leggTilVerdi( (0,2,0) ) eller leggTilVerdi( koordinat(0,2,0) );
		void leggTilVerdi( 	const koordinat * argKoordP ) 	{ xkoord += argKoordP->xkoord; 	ykoord+=argKoordP->ykoord; 	zkoord+=argKoordP->zkoord; 	}
		void settVerdi( char retning, double nyVerdi );
		// koordinat operator= double[] - eller noke..
		// Flytt ut av klassa.
		koordinat  operator+  (koordinat); 
		koordinat  operator-  (); //feil rekkefølge???
		koordinat  operator-  (koordinat); 

		koordinat& operator+= (koordinat);
		koordinat& operator-= (koordinat);
		koordinat& operator*= (double);
		//double  operator[] (char c) const{ return getVerdi(c); }
		double  &  operator[] (char retn)	{ return (*useKoordinatRetn(retn) );	}
		//neste er ikkje i bruk. bare for getVerdi uansett.
		//double  operator[] (int retn ) 	{ if( retn <0 || retn > 2){ printf(" FEIL på koordinat[int] \n"); } return getVerdi(retn); }
		//operator -> (retning)
		// osv.
		//
};

koordinat operator*  (koordinat, koordinat); 
koordinat operator*  (koordinat, double); 
koordinat operator*  (double, koordinat); 

std::ostream& operator<< (std::ostream&,const koordinat&);





class masse
{
	protected:
		koordinat mPos;//XXX //var double mPos[3]; 
		koordinat mV; // XXX //var double mV[3]; 
		koordinat mF; //   a  //var double mF [3]

		double masseTotal; // Gir en treighet til groande axon..
		
		int enhetsId;
	

//{ |start
		//XXX fra her
		//static std::vector<int> indexRekkefoelgeFasitForAvstVektor;
		 	//inneholder id til alle partikler som eksisterer, (evt i rett rekkefølge).
			// dette er dermed fasit på utregningsrekkefølge for part.
		
		//std::map<int, double> avstandTilAndreObjekt; 
			/*
			 * Plan:
			 *  	- lage avstandTilAndreObjekt i alle instanser av axon.
			 *  	- Denne skal følge indexRekkefoelgeFasitForAvstVektor for alle enkeltpartiklane.
			 * 		- lag metoder for å forsikre at alle er med.
			 */

		//void forsikreAtRekkefoelgeStemmerMedFasit(); 	// skal sjekke rekkefølge på avst. og kraft. opp i mot fasit, og evt. rette på rekkefølgen.
								//  	ikkje naudsynt lenger, med map?
		//void sjekkRekkefFasit();//eller noke	 	// - Bør kanskje også ha en funk for å holde fasit rett. F.eks. alle part. sjekker om de er med i fasit. 
							 	//						- bør også ha måte å oppdage falske oppføringer.

		//    til her XXX
//}

		std::map<int, double> avstandTilAndreObjekt; //ok
		
		std::map<int, koordinat*> pPaavirkaAvDenneKraftFraAndreObj;
		// har eg grunn til at det er koordinat* her ?
		
		// XXX Trenger ferdigflagg som flagger om avstander er gyldige/ferdig utregna. Dei nulles uansett ut før start, så ei if() er kanskje nok?
		// tenk litt meir på dette, sjå evt i main.cpp etter XXX

//{ slutt|
//}





	private:
		static int antallObjekterInitiert;  // denne skal også def i kvar underklasse.
//		static int nAntallObjekterTotalt; 	//XXX ny, ikkje i bruk enda. mai09
		// TODO : Lag
		// 	       static double avstandMellomObjekt[3][ant.obj.][ant.obj.]; med variabelt antall element. kanskje vector?
	public:
		// konstruktor( ikkje naudsynt.. ? )
		masse() : mPos( "mPos" ), mV( "mV" ), mF( "mF" ) 	{  enhetsId = ++antallObjekterInitiert; }

		// XXX ny, og uprøvd (får ikkje komp. no..)
		void nullUtFraForrigeIterasjon();
		// XXX og ubrukt, trur eg. Ta i bruk.
		static void nullUtAvstanderOgKraft_i_pAlleEnheter(); 
		static void initStaticVariable();


		koordinat getPaavirkningsKraftFraMasseId( int i ) /*const*/ { return *(pPaavirkaAvDenneKraftFraAndreObj[i]); } 	//samme
		koordinat getKraftFraAndreObj( int annaObjId ){   return *pPaavirkaAvDenneKraftFraAndreObj[annaObjId]; 	} 	//samme
//{ |start
//}
		// ta nederst eller noke. Den er static:
		// NICE!!! returnerer referanse, slik at eg kan få tilgang til privat variabel ved dette eksplisitte kallet. HURRA!
		static double & useAvstandMap( int nArgFra, int nArgTil )
		{
			// XXX MUTEX XXX ? isåfall inn her!
			if( nArgFra && nArgTil ) //sikrer mot tomme verdier. index > 0
	 		 	return (*masse::pAlleEnheterMapPeik)[nArgFra]->avstandTilAndreObjekt[nArgTil];
			//om eg vil ha mutex, så bruk alltid litt (10e-3s) tid før man berører variabel. På denne måte kan mutex låses, og avlåses(trygt) før man returnerer med 
			//referansen fra denne funk. Om alle plasser følger denne konvensjonen, vil det være heilt trygt.. Genialt XXX GENIALT XXX!
			
			//XXX prøv å videreføre dette til ref-returnerande mutex-funk som venter litt før den returnerer referanse, 
			//XXX  							eller mutex-låse-funk som også venter litt før den låser. (og er einaste måte å skaffe mutexen.)

		}
		static koordinat * useKraftKoordinatMap( int nArgFra, int nArgTil )
		{
			// XXX MUTEX ?
			if( nArgFra && nArgTil ) //sikrer mot tomme verdier. index > 0
	 		 	return (*masse::pAlleEnheterMapPeik)[nArgFra]->pPaavirkaAvDenneKraftFraAndreObj[nArgTil];
		}
		
		// løysing: istadenfor global variabel alleMasseP*, ha static masse* var. her inne, som peiker på alle masser :
		static std::map<int, masse*> * pAlleEnheterMapPeik;


		double getAvstandTilObjekt( int andreId ) //siden avstand er private..
		{
	 		return avstandTilAndreObjekt[andreId];	
		}
		// kanskje det kan være lurt å lagre partiklane i en map istadenfor en vector, med [id] som subscript? (enhetsId) - def i masse

//{ slutt|
//}



		virtual int  kalkulerKraftMotNeuronSenter() =0;// { printf("feil->: bruker nedarva funk fra masseG.h l38 \n"); }
	


		// rein virtuell: gjør at klasse blir abstrakt..
		virtual void kalkulerAvstander() =0; 	// rein virtuell funk => virtuell klasse!
		virtual void kalkulerAvstander( std::vector<masse*>) =0;
		koordinat getPos ( ) 	const;
		koordinat getFart( ) 	const;
		koordinat getPaaVirkningsKraft()const { return mF; }
		// var void getFart(koordinat* fyllMeg) 	const;
		// var void    getPos(double* fyllMeg) const;
		double  pos(int retning) 	const { return mPos.getVerdi( retning ); }	//funker som axonPos[retning] bare med ()-paranteser.
		double  getMasseTotal()  	const { return masseTotal;    }
		int 	getId() 	 	const { return enhetsId; 	 }	
		// skal være virtual uansett..
		virtual void kalkulerBane(); // tom for enkelte klasser? evt bare summer eksterne krefter. ( funk er vel egentlig bare aktuell i axon..) tenk tenk..
		virtual std::string getObjektType( bool ) const {  return "masse";  } //poenget med bool? - for arv. virtual. Sjå andre utførelser...
		static int getAntallObjekt() { return antallObjekterInitiert; }
		static void skrivUt( masse* );		
//		void skrivUt(){ skrivUt( this );
		masse* pNermaste;
		

// NESTE STORHENDING:
//		static double avstandMellomObjekt[][];
//		eller vector? (dynamisk antall part.)


};


#endif

// vim: fdm=marker:fmr=/{,/}
