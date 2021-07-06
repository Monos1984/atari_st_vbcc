// +++++++++++++++++++++++++++++++++
// + Tuto stx engine pour atari st +
// +         06/07/2021            +                   
// +++++++++++++++++++++++++++++++++
// *                               *
// *    #3:...Blitter              *
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

/**************************************************************************************************************** 
  Cette exemple permet d'afficher une image à l'écran de l'atari ste du buffer à l'écran logique avec le blitter.
    
    * Initiation de la librairie stx.
    * Charger une image pic1 avec le st_tool dans un buffeur
    * Tester la touche Espace et Q.
    * Utiliser le blitter sur un ecran complet
    * Echanger l'écran logique et physique.
    * Fermer proprement le programme.

 ****************************************************************************************************************/

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
  // + --------------------------------- +
  // * Declaration des variables locales *
  // + --------------------------------- +
  unsigned char buffer_picture[32000]; 
  
  // + -------------------- +
  // * Initiation de la lib *
  // + -------------------- +
  STX_initstxengine(FV50,2); // Frequence Vertical, et nombre de sprite mémorisé (minimum 2 pour souris et font ?).
  
  // + -------------------------------------- +
  // * Charger une image dans l'écran logique *
  // + -------------------------------------- +	   
  STT_load_picture("DATA\\LENNA.PI1",(long int *)buffer_picture,OP_RESOLUTION|OP_PALETTE|OP_DATA);
  
  // + ----------------------------------------------------- +
  // * Attendre la touche Espace pour continuer le programme *
  // + ----------------------------------------------------- +
  while(!STX_keyboardkeypress(KEY_SPACE))
  {
    STX_waitvbl();  
  }
  
  // + ----------------------------------------------- +
  // * Utiliser le Blitter du buffer à l'écran logique *
  // + ----------------------------------------------- +
  
  /**************************************************************************
    + ------------------------ +
    * Arguement de la fonction *
    + ------------------------ +
    Adresse Source 
    Adresse de Destination
    PX source
    PY source 
    Largeur à copier
    Hauteur à copier
    PX destination
    PY destination
    
    + ---- +
    * Note *
    + ---- +
    Tout ce qui touche la largeur du buffer doivent être des multiples de 16.
    (PX source, Largeur à copier, PX destination)
    
    
  ****************************************************************************/
  
  
  STX_blitloadedpicture	((long int *)buffer_picture,STX_getworkscreen(),0,0,320,240,0,0);
  
  // + ----------------------------------- +
  // * Inverser Ecran Logique <=> Physique *
  // + ----------------------------------- +
  STX_swapscreen(FALSE);
  
  // + ----------------------------------------------------- +
  // * Attendre la touche Q pour continuer le programme *
  // + ----------------------------------------------------- +
  while(!STX_keyboardkeypress(KEY_Q))
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