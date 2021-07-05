// +++++++++++++++++++++++++++++++++
// + Tuto stx engine pour atari st +
// +         05/07/2021            +                   
// +++++++++++++++++++++++++++++++++
// *                               *
// *    #2:...Picture              *
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
  Cette exemple permet d'afficher une image à l'écran de l'atari ste.
    
    * Initiation de la librairie stx.
    * Charger une image pic1 avec le st_tool
    * Tester la touche Espace.
    * Echanger l'écran logique et physique.
    * Attendre l'utilisation de la touche ESPACE.
    * Fermer proprement le programme.

 ****************************************************************************************/

// ==================
// * Fichier Header *
// ==================
#include <src/StGfxEngine.h>
#include <st_tool.h>

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
  
  // + -------------------------------------- +
  // * Charger une image dans l'écran logique *
  // + -------------------------------------- +	   
  STT_load_picture("DATA\\LENNA.PI1",STX_getworkscreen (),OP_RESOLUTION|OP_PALETTE|OP_DATA);
  
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