//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//  * * * * * * * * * * * 	opengl.cpp - Hovedsakelig grafikk og main(). 	  * * * * * * * * * * * * * * * * *
//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Filbeskrivelse / kommentar //{1
/*
 * 	Samlingspunkt for det grafiske ved part.sim.
 * 	Som navnet indikerer, er dette fila for opengl
 */
//}

// 		#include //{1 
// #include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
//Inkluder .h fil som bl.a. definerer classen partikkel med classefunk. og instanser av classen
#include "partikkelG.h"
//#include "gruppering.h"
#include "main.h"

 //}1
// #define /{
#define VINDUSBREDDE  	900
#define VINDUSHOEGDE  	750
//#define MAXDYBDE 	1.0f
/*
 * ##define KEY_ESC 27
 * ##define KEY_UP 101
 * ##define KEY_DOWN 103
 * */
//}1
using namespace std;
// Eksterne deklarasjoner av funk og var //{1
// tester i utproevingAvNyeAspekt.cpp
int mainTestFunk(); // ekstern funk fra utproevingAvNyeAspekt.cpp 

extern int antallPartiklerInitiert; 
//extern double allePartikkelXYZ[3][ANTALL PARTIKLER];
//XXX ta vekk allePartikkelXYZ. Er ikkje lenger,

//extern vector<masse*> pPart;

// pThread og mutex-er
extern pthread_mutex_t posmutex;
extern pthread_mutex_t mutexVent1;
//extern partikkel partikkel_variabel_pga_konstruktor_kjoerer_ikkje_i_vector_init[ANTALL PARTIKLER];
extern pthread_t kalkuleringstraad;
extern bool skinn::globalAvluttProgramVariabel;
//}1
// Definisjoner av variabler. //{1 
//int returFraPthreadCreate;


// kamera() def og var. knytta til det.
void kamera();
double xrot = 1 , yrot = 1, zrot = 0, xforrigerot = 0, yforrigerot = 0, zforrigerot = 0; 
double xkamerapos = 0 , ykamerapos = 0 , zkamerapos = -5.4;
//}1

bool init()
{ //{1 ... } 
	
	if(!SVART)
	{
		glClearColor(0.0f, 1.0f, 0.0f, 0.0f);	//Grøn
	}else{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //svart
	}

// er default:	glClearDepth( 1.0f );

	glEnable( GL_DEPTH_TEST );

	glDepthFunc( GL_ALWAYS ); //XXX jejeje?

	glEnable( GL_LIGHTING );
	
	glShadeModel( GL_SMOOTH );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_DONT_CARE );//???

	glMatrixMode( GL_PROJECTION ); //rett plass?
	glLoadIdentity();

	glViewport( 0, 0, VINDUSHOEGDE, VINDUSBREDDE);

	gluPerspective( 45.0f, 1.0f * (VINDUSBREDDE / VINDUSHOEGDE) , 0.0f, 200.0f);

	// Setter kamera i en pos. og peiker mot anna pos.
	gluLookAt( xkamerapos, ykamerapos , zkamerapos,       0, 0, 0,         0, 1, 0);
	// -> første3 var: kor skal kamera ligge.
	// -> neste3  var: ka skal kamera peike på.
	// -> siste3  var: opp-for-kamera-vektor.
	
	glMatrixMode( GL_MODELVIEW );  //skal være med?
	glLoadIdentity( );

	if( NATURLIG_LYS )
	{ //{2 ... }
		glEnable( GL_LIGHT0 );
		glEnable( GL_LIGHT1 );

		GLfloat svartfarge []   = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat kvit_farge []   = {0.7f, 0.8f, 0.8f, 1.0f};
		GLfloat lysPos [] 	= {1.0f, 0.5f, 0.5f, 1.0f};
	 	glLightfv(GL_LIGHT0, GL_AMBIENT,  svartfarge );
		glLightfv(GL_LIGHT0, GL_DIFFUSE,  kvit_farge );
		glLightfv(GL_LIGHT0, GL_POSITION, lysPos );
		glEnable( GL_LIGHT0 );
		//glLightfv(GL_LIGHT3, GL_SPECULAR,{1.0, 1.0, 1.0, 1.0});
		//

	
		// GL_LIGHT0: the white light emitting light source
		// Create light components for GL_LIGHT0
		float ambientLight2[] = { 0.6f, 0.9f, 0.4f, 1.0f };
		float diffuseLight2[] = { 0.8f, 0.8f, 0.8f, 1.0f };
		float specularLight2[] = { 0.5f, 0.5f, 0.5f, 1.0f };
		float position2[] = { -1.5f, 1.0f, -4.0f, 1.0f };	
		// Assign created components to GL_LIGHT0
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight2);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight2);
		glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight2);
		glLightfv(GL_LIGHT2, GL_POSITION, position2);
	
		// GL_LIGHT1: the red light emitting light source
		// Create light components for GL_LIGHT1
		float ambientLight1[] = { 1.0f, 0.5f, 0.5f, 1.0f };
		float diffuseLight1[] = { 1.0f, 0.5f, 0.5f, 1.0f };
		float specularLight1[] = { 1.0f, 0.5f, 0.5f, 1.0f };
		float position1[] = { 1.5f, 1.0f, 4.0f, 1.0f };	
		// Assign created components to GL_LIGHT1
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);
		glLightfv(GL_LIGHT1, GL_POSITION, position1);

	} //}2

	// For Alpha-vegger:
	//glEnable( GL_BLEND );
	//glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	return true;
} //}1

void display()
{ //{1 tegnefunksjon, oppdaterer skjermbilde.  ... }
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity(); 

	// roterer kamera
	kamera();

	if (  KUBE )
	{ 
		glColor3f( 0.1 , 0.1 , 0.1 );
		glutWireCube( 2*GRENSE ); 
	}

	if( ALFA_KUBE ){

		// sjå videotutorialsrock.com - opengl-alphablending - tutor. Bra..
		glColor4f( KUBEFARGE_R, KUBEFARGE_G, KUBEFARGE_B, ALFA_VERDI_KUBE );

		// Lager en alpha-kube litt større enn wire-kuben min.
		glutSolidCube( 2*GRENSE -0.001 );
	/* glDisable(GL_TEXTURE_2D);
	   glNormal3f(face.out[0], face.out[1], face.out[2]);*/
	}
//	glLineWidth( 0.000001 );
	if ( KOORDSYS ){
	// LAG FLEIRE VALG. Vegger fra her til uendelig, tak, thepots, osv for å sjå perspektiveffekt.
		// Teikn akser i koordinatsystem.
		//KLASSISK KOORDSYS:
		
		glBegin( GL_LINES );
			glColor3f( 0.1 , 0.1 , 0.1 );
			glVertex3f( -1.0 , 0 , 0 );
			glVertex3f( 1.0 , 0 , 0 );
		glEnd( );
 		glBegin( GL_LINES );
			glColor3f( 0.1 , 0.1 , 0.1 );
			glVertex3f( 0, -1.0 , 0 );
			glVertex3f( 0,  1.0 , 0 );
		glEnd( );
		glBegin( GL_LINES );
			glColor3f( 0.1 , 0.1 , 0.1 );
			glVertex3f( 0 ,0 ,-1.0 );
			glVertex3f( 0 ,0 , 1.0 );
		glEnd();

	}

	if( VEGG1 )
	{
		glColor3f( 1.0f, 0.3f, 0.3f );
		glPushMatrix();
			glTranslatef( 1.4*GRENSE, 0, 2*GRENSE);
			glutSolidCube( 2.2*GRENSE );
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 1.4*GRENSE, 0, -1*GRENSE);
			glutSolidCube( 1.2*GRENSE );
		glPopMatrix();
		glPushMatrix();
			glTranslatef( -4.4*GRENSE, 0, -1*GRENSE);
			glutSolidCube( 3.2*GRENSE );
		glPopMatrix();
	}
	// MUTEX for allePartikkelXYZ
	pthread_mutex_lock( &posmutex );
	
	// FAKTISK TEIKNING AV VARIABLER //{2
	//if ( full3D ) //gjelder prikker eller 3d-baller
	{  // full3D true. baller heller enn prikker

		koordinat partNrpos;

		for(int i =0; i< masse::getAntallObjekt() ; i++){

			if( !(*masse::pAlleEnheterMapPeik)[i] ) continue; //sikrer mot segf.

			glPushMatrix();
				
				if( SVART ){
					glColor3f(0.2, 0.3 , 0.4);
				} else { // Kvit bakgrunn
					glColor3f(0.0, 0.1 , 0.2);
				}

				//koordinat partNrpos :
				partNrpos = (*masse::pAlleEnheterMapPeik)[i]->getPos();
				
				glTranslatef( partNrpos['x'], partNrpos['y'], partNrpos['z'] );
				

				if( PARTIKKEL_FORM_BALL ){
					glutSolidSphere(0.01f ,7, 7);
				}else if( PARTIKKEL_FORM_KUBE ){
	 				glutSolidCube  (0.01f);
				}else throw kritisk_feil();
			glPopMatrix();
		}
	} //}2
	
	// Mutex unlock
	pthread_mutex_unlock( &posmutex );
	
	glutSwapBuffers();

	// gjør at rekn ut bane kan regne ut neste (mutex involvert)
	pthread_mutex_unlock( &mutexVent1 );
} //}1

void keyboard(unsigned char key, int x, int y)
{ //Tar imot knappetrykk og musebevegelser. ... } //{1
	if (key == 27){
//		LagreTilstandsvariableIFil();
//		glutLeaveGameMode();
		printf("Trykte på esc. quit om ei linje. (exit(1))\n");
		// Trenger vi noko som sørger for ingen seg-fault?
		skinn::globalAvluttProgramVariabel = true;
		printf("Avslutter program. \n");
		
		// ikkje nødvendig å vente så:
		// lenge, men kult..
		for(int i=0; i<84; i++ )
		{
			if(i==42)printf("\n");
			usleep(4000);
			cerr<<"*"; //unbuffered.. 
		}
		printf("\n");
		// her unngår eg segf. som har plaga meg ei stund :
		pthread_cancel( kalkuleringstraad );
	//	pthread_exit(0);
		exit(0);
		//her ligger sikkert problemet som gjør at eg får segfault heile tida, når eg terminerer..
		//prøv med pthread-metod for å drepe tråd..
	}

//	if (key == ) glutEnterGameMode();


	/* * * * * * *  * * * * * * * 
	 * * * neste to knapper * * * 
	 * * * er viktige..     * * *
	 * * * * * * *  * * * * * * */

	if (key == ' ') toggleMasseFjoerDempetSystem();

	if (key == 'm')
	{
		mainTestFunk();
	}


	if (key == 'd') yrot -= 2;
	if (key == 'a') yrot += 2;
	if (key == 'f') yrot -= 2;
	if (key == 'w') xrot += 2;
	if (key == 's') xrot -= 2;
	if (key == 'e') zrot += 2;
	if (key == 'q') zrot -= 2;

	//if (key == 'p') glutFullScreen();  //for eksempel 'p' Funker bare ei retning..

	if (key == 'k') 
	{

		/*double xrotrad, yrotrad, zrotrad;
		xrotrad = (xrot / 180 * 3.141592654f); 
		yrotrad = (yrot / 180 * 3.141592654f);
		zrotrad = (zrot / 180 * 3.141592654f); 
*/
//		xkamerapos -=  0.01 *double( sin( xrotrad )) ;
//		ykamerapos +=  0.01 *double( sin( yrotrad )) ;
		zkamerapos -= 1.0 ;//*double( cos( yrotrad )) ;
		
		glLoadIdentity();
		glTranslated( -xkamerapos, -ykamerapos, -zkamerapos);
	}

	if (key == 'i')
	{
		/*
		double xrotrad, yrotrad, zrotrad;
		xrotrad = (xrot / 180 * 3.141592654f); 
		yrotrad = (yrot / 180 * 3.141592654f);
		zrotrad = (zrot / 180 * 3.141592654f); 

//		xkamerapos +=  0.01 *double( sin( xrotrad )) ;
//		ykamerapos -=  0.01 *double( sin( yrotrad )) ;
	*/	zkamerapos +=  1.0;// *double( cos( yrotrad )) ;
		
		glLoadIdentity();
		glTranslated( -xkamerapos, -ykamerapos, -zkamerapos);
	}
	if (key == 'o')
	{
		//funker ikkje heilt rett vei..
		double xrotrad, yrotrad, zrotrad;
		xrotrad = (xrot / 180 * 3.141592654f); 
		yrotrad = (yrot / 180 * 3.141592654f);
		zrotrad = (zrot / 180 * 3.141592654f); 

		xkamerapos +=  0.1 *double( sin( xrotrad )) ;
		ykamerapos -=  0.1 *double( sin( yrotrad )) ;
		zkamerapos +=  0.1 *double( cos( yrotrad )) ;
		
		glLoadIdentity();
		glTranslated( -xkamerapos, -ykamerapos, -zkamerapos);
	}

} //}1

void kamera()
{ //Rotasjon av kamera ... } //{1
	// prøv med loadIdentity eller kva det heiter istadenfor xrot-xforrigerot. 
	// Istedenfor dette:

	glRotatef( xrot - xforrigerot , 1.0 , 0, 0);
	xforrigerot = xrot;

	glRotatef( yrot - yforrigerot , 0 , 1.0 , 0);
	yforrigerot = yrot;

	glRotatef( zrot - zforrigerot , 0 , 0 , 1.0);
	zforrigerot = zrot;
		

} //}1

void Timer(int extra)
{ //sørger for å gå videre til neste tidssteg... } //{1
	glutPostRedisplay();
//	(*pout)<<"    -     \n";
	glutTimerFunc(VENTMILLISEK,Timer,0);
} //}1

int openglMain(int* argcP, char** argvPP ){
	//kall: openglMain(&argc, argv);
	// ta bort resten tili openglMain
	if( !debugMode )
	{
		if( !full3D ){
			glHint( GL_POINT_SMOOTH_HINT , GL_DONT_CARE );
		}

		glutInit(argcP, argvPP);

		//glutGameModeString( "800x600:8@60" );	
		
		glutInitWindowPosition(5, 5);
		glutInitWindowSize( VINDUSBREDDE, VINDUSHOEGDE);

		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

		if( !glutCreateWindow(argvPP[0]) ) throw kritisk_feil();
		
		glutKeyboardFunc(keyboard);

		glutDisplayFunc(display);

		glutTimerFunc(10,Timer,0);

		if (!   init()  ) return 1;

		glutMainLoop();
	}else{
		mainTestFunk();
		printf("Husk: er no inne i while(1) [sjå opengl.cpp:261]\n");
		printf("Går inn i egenDefMainLoop() \n");
		while (1);
	}
	return 0;
}

// vim:fdm=marker:fmr=//{,//} : fdl=1
