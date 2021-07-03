// +++++++++++++++++++++++++++++++++
// + Tuto stx engine pour atari st +
// +         03/07/2021            +                   
// +++++++++++++++++++++++++++++++++
// *                               *
// *    #1:...Hello World          *
// *                               *
// +++++++++++++++++++++++++++++++++

// ====================
// * Atari STX Engine *
// ====================

// * ---------------------------------------------------------- *
// * Lien github : https://github.com/frgailll/Atari-STX_Engine *
// * ---------------------------------------------------------- * 

// ===============
// * Description *
// ===============

/**************************************************************************************** 
  Cette exemple permet d'afficher un texte (Hello World) à l'écran de l'atari ste.
    
    * Initiation de la librairie stx.
    * Ouverture d'un fichier font. 
    * Afficher le texte à l'écran.
    * Tester la touche Espace.
    * Attendre le signale VBL.
    * Echanger l'écran logique et physique.
    * Attendre l'utilisation de la touche ESPACE.
    * Fermer proprement le programme.

 ****************************************************************************************/

// ==================
// * Fichier Header *
// ==================
#include <src/StGfxEngine.h>

// ====================
// * Interruption DMA *
// ====================

// * A placer automatiquement même si c'est vide * 
 
void STX_dmasampleendframe();
void STX_dmasampleendframe()                                           
{
    
}

// ===================
// * Fonction main() *
// ===================
int main()
{  
  // + -------------------- +
  // * Initiation de la lib *
  // + -------------------- +
  STX_initstxengine(FV50,2); // Frequence Vertical, et nombre de sprite mémorisé (minimum 2 pour souris et font ?).
  
  // + ---------------------------------- +
  // * Chargement d'une police d'ecriture *
  // + ---------------------------------- +
  STX_loadcharset ("DATA\\char.crs");
 
  // + ----------------------- +
  // * Afficher le Hello World *
  // + ----------------------- +
  //              (X,Y,Index Couleur...)
  STX_printstring (0,0,1,REPLACE,HOR,"Hello World"); 
  
  // + -------- +
  // * wait vbl *
  // + -------- +
  STX_waitvbl();
  
  // + ----------------------------------- +
  // * Inverser Ecran Logique <=> Physique *
  // + ----------------------------------- +
  STX_swapscreen(FALSE);
  
  // + ----------------------------------------------------- +
  // * Attendre la touche Espace pour continuer le programme *
  // + ----------------------------------------------------- +
  while(!STX_keyboardkeypress(KEY_SPACE))
  {
    STX_waitvbl();  
  }
  
  // + ---------------------------------------- +
  // * Decharge en mémoire la police d'écriture *
  // + ---------------------------------------- +  
  STX_Unloadcharset();
  
  // + ------------------- +
  // * Fermeture de la lib *
  // + ------------------- +
  STX_uninitstxengine();  
  
  // + ------------------ +
  // * Retour de fonction *
  // + ------------------ +
  return 0;
}