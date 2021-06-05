// ************************************************
// *                Class video                   *
// * -------------------------------------------- *
// * Code par Jean Monos                          *
// * Extension pour la STX_Engine                 *
// * de Laurent Gaillard                          *
// * https://github.com/frgailll/Atari-STX_Engine *
// * Mise à jour le 5/6/2021                      *
// * Pour VBCC                                    *
// ************************************************

// ====================
// * Fichier includes *
// ====================
#include <class_video.h>
#include <src/StGfxEngine.h>
#include <tos.h>

#include <string.h>


// =========
// * cls() *
// =========
void cls()
{
  STX_clearlogscreen ();
  STX_swapscreen(FALSE);
  STX_clearlogscreen ();
}

// =================
// * wait_time_vbl *
// =================
void wait_time_vbl(unsigned int value)
{
  // + ------------------------- +
  // * Declaration des variables *
  // + ------------------------- +
  unsigned int i;
  
  // + ----------- +
  // * Routine vbl *
  // + ----------- +
  for (i=0;i<value;i++)
  {
    STX_waitvbl();
  }
  
}

// ==============
// * Transition *
// ==============
void transition(unsigned char value)
{
  /* + ------------- +
     * Mode d'emploi *
     + ------------- +
  
  - Préparer l'image dans l'écran logique de la librairie STX pour faire une transition T_IN
  - Utiliser la fonction transition(T_OUT) pour une transition mode image => Rideau (couleur index 0)
  - Utiliser la fonction transition(T_IN) pour une transition Rideau qui s'ouvre => écran logique.
    
  */
  
  // + ------------------------- +
  // * Declaration des variables *
  // + ------------------------- +
  unsigned short i; // Boucle
  unsigned int adr_i; // Valeur Boucle * tailles octet à copier/coller
  long* adr_ph; // Adresse ecran physique
  long* adr_log; // Adresse ecran logique 
  
  // + -------------------- +
  // * Get l'écran physique *
  // + -------------------- +
  adr_ph = Physbase();
  
  // + ----------------------- +
  // * Get l'écran logique stx *
  // + ----------------------- +
  adr_log = STX_getworkscreen () ;
  
  // + -------------- +
  // * Transition out *
  // + -------------- +
  if (value == T_OUT)
  {
    // + -------------------- +
    // * Boucle de la routine *
    // + -------------------- +
    for(i=0;i<51;i++)
    {
      adr_i = i * 320;
      memset((char*)adr_ph+adr_i,0,320);
      memset((char*)adr_ph+31840-adr_i,0,320);
      STX_waitvbl();
    }
  
  }
  
  // + ------------- +
  // * Transition in *
  // + ------------- +
  if (value == T_IN)
  {
    // + -------------------- +
    // * Boucle de la routine *
    // + -------------------- +
    for (i=0;i<50;i++)
    {
      adr_i=i*320;
      memcpy((char*)adr_ph+15840-adr_i,(char*)adr_log+15840-adr_i,320);
      memcpy((char*)adr_ph+16000+adr_i,(char*)adr_log+16000+adr_i,320);
      STX_waitvbl();
    }
    
  }
  
}