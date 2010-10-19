#include "masseG.h"
#include "main.h"
// #include <iostream>
#include <cstdlib>
//inneholder bl.a. koordinat-klasse.
//using std::string;
using namespace std;


void koordinat::skrivUt(std::string tekst/* =""*/, char retning/* =0*/ ){ 	
	if( retning=='x' || retning=='y' || retning=='z' ){
		if( ! tekst.empty()/*length()*/ ) 	(*pout)<<tekst <<" retning " <<retning <<": " <<getVerdi( retning );
		else{ 					(*pout)<<getVerdi(retning); }
		//
	}else if( retning == 0){ //skriv ut alt..
		// mulig: skrivUt(0, 'x'); skrivUt(0, 'y'); skrivUt(0, 'z');
		if( !tekst.empty() /*length()*/ ) 	(*pout)<<tekst <<": ";
		(*pout)<<"\t[  " <<getVerdi('x') <<"\t, " <<getVerdi('y') <<"\t, " <<getVerdi('z') <<" \t] ";
	}else{ printf(" FEILMELDING sdf63 : kalla koordinat::skrivUt( \"%s\", \'%c\' )\n", tekst.c_str(), retning); }
	(*pout)<<std::endl;
}
/* Ikkje naudsynt lenger:
string koordinat::toString() const
{
	std::ostringstream returverdi;
		
	returverdi <<"Vektor: " << *this ;
	return returverdi.str();
}*/

double koordinat::getVerdi (char retning) const
{
	switch(retning)
	{
		case 'x': case 'X':
			return xkoord;
		case 'y': case 'Y':
			return ykoord;
		case 'z': case 'Z':
			return zkoord;
	}	
	
	sleep(2);
	printf("\n\n\n\n\n\n\n\n\n\n\t\t\tFEILverdi.errKode1234321 \n"); 
	exit(-1);
		
}

double koordinat::getVerdi ( int retn ) const  
{ 
	switch(retn)
	{
		case 0:
			return xkoord;
		case 1:
			return ykoord;
		case 2:
			return zkoord;
	}	
	// kommer hit om den ikkje returnerer en verdi over. Feil.
 	printf(" Feil i getVerdi(int) l.30@vektor.cpp \t Sannynligvis er retning=%d ikkje lovlig retning. \n", retn);
	  sleep(3);
	  exit(0);
	return -100000;
}

void koordinat::settVerdi( char retning, double nyVerdi ){ printf(" jejeje qwer940@vektor.cpp \n");}
/*  KUK - Kommentert-Ut-Kode //{9 
// Denne kan eg no ta vekk: no kan man skrive koordinat ko; ko['x') = 1.2;
void koordinat::settVerdi( char retning, double nyVerdi )
{
	 useKoordinatRetn( retning ) = nyVerdi;
}
 *   //}9 */ 


// skal være const koordinat& (global)::operator- (const koordinat &)  eller noke
koordinat koordinat::operator- ()
{
	 return koordinat(-xkoord, -ykoord, -zkoord);
}

koordinat koordinat::operator- (koordinat hin)
{
	 return ((*this)+(-hin ) );
}

koordinat koordinat::operator+ (koordinat hin)
{
	 double x,y,z;
	 x = xkoord + hin.xkoord;
	 y = ykoord + hin.ykoord;
	 z = zkoord + hin.zkoord;
	 return koordinat(x,y,z);
}


koordinat& koordinat::operator+=(koordinat hin)
{
	 xkoord += hin.xkoord;
	 ykoord += hin.ykoord;
	 zkoord += hin.zkoord;
	 return *this;
}

koordinat& koordinat::operator-=(koordinat hin)
{
	 xkoord -= hin.xkoord;
	 ykoord -= hin.ykoord;
	 zkoord -= hin.zkoord;
	 return *this;
}

koordinat& koordinat::operator*=(double faktor)
{
	 xkoord *= faktor;
	 ykoord *= faktor;
	 zkoord *= faktor;
	 return *this;
}

//begynner på operatore som ligger utafor klassa.
//

koordinat operator* (koordinat forste, koordinat andre)
{
	 double x,y,z;
	 printf(" ikkje mulig... Husk vektorretning, osv.., men legger godviljen til, og skal implementer som om det går an. (ligg * stå) \n");
	 
	 x = forste['x'] * andre['x'];
	 y = forste['y'] * andre['y'];
	 z = forste['z'] * andre['z'];
	 return koordinat(x,y,z);
}

koordinat operator* (double faktor, koordinat vekt)
{ //ok
	 return koordinat( faktor*vekt.getVerdi('x'), faktor*vekt.getVerdi('y'), faktor*vekt.getVerdi('z') );
}

koordinat operator* (koordinat vekt, double faktor)
{ //ok
	 return koordinat( faktor*vekt.getVerdi('x'), faktor*vekt.getVerdi('y'), faktor*vekt.getVerdi('z') );
}

//ostream& operator<< (ostream & o, koordinat & k )
ostream& operator<< (ostream & o, const koordinat & koord )
{
	//std::ostringstream out;
	std::string alternativtInnrykk = "";

	
 	     if( koord.getType() 	.length() > 31)  alternativtInnrykk= "";
  	else if( koord.getType() 	.length() > 23)  alternativtInnrykk= "\t";
	else if( koord.getType() 	.length() > 15)  alternativtInnrykk= "\t\t";
        else if( koord.getType() 	.length() > 7 )  alternativtInnrykk= "\t\t\t";
        else 						 alternativtInnrykk= "\t\t\t\t";
	
	return o<<koord.getType() <<alternativtInnrykk <<"\t(  " <<setw(10) <<koord.getVerdi('x') <<"\t, " <<setw(10) <<koord.getVerdi('y') <<"\t, " <<setw(10) <<koord.getVerdi('z') <<"\t) ";
}
	

// vim:fdm=marker:fmr=//{,//} : fdl=2
