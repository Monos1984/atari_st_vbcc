// ****************************************************************
// * Nom ................ Happy St                                *
// * Programmeur ........ Jean Monos                              *
// * Data mise à jour.... 16/05/2021                              *
// * Fonction ........... Fonction dev pour Atari Ste VBCC        *
// * Licence ............ CC-BY-SA                                *
// ****************************************************************

// ===================
// * Fichier include *
// ===================

#include <stdio.h>
#include <string.h> 
#include <tos.h>
#include <mt_gem.h>
#include "source/header/happyst.h"
// ======================================
// * Declaration des variables globales *
// ======================================  
long* Save_Ecran_Phys;
long* Save_Ecran_Log;
int   Save_Ecran_Mode_Video;
short Save_Buffer_Palette[16];


short get_test()
{
  return 10;
}


/*
  2 octets / 2 octets / 2 octets
  
  0b10110101, 0b11010110 , - 0b10110101, 0b11010110 , - 0b10110101, 0b11010110 , - 0b10110101, 0b11010110  8 bytes
  
    (128 octets)

320/8= 40 octets * 4 = 160 octets par lignes

*/

// ===========================================================
// * Fonction ....: soft_copy_tiles()                        *
// ===========================================================
// Role .........: Copie / colle une zone de 16x16           * 
// Parametre ....: long* adr_source                          *
// ..............: long* adr_destination                     *
// ..............: unsigned char s_px                        *
// ..............: unsigned char s_py                        *
// ..............: unsigned char d_px                        *
// ..............: unsigned char d_py                        * 
// Retour .......: Aucun                                     *
// ===========================================================
void soft_copy_tiles(long* adr_source, long* adr_destination,unsigned char s_px,unsigned char s_py,unsigned char d_px,unsigned char d_py)
{
  // -------------------------------------
  // * Declaration des variables locales *
  // -------------------------------------
  unsigned char ligne;

  // -----------------
  // * Calcule de px *
  // -----------------
  d_px = d_px<<3;
  s_px = s_px<<3;
  
  // -----------------
  // * Calcule de py *
  // -----------------
  s_py = s_py<<4;
  d_py = d_py<<4;
  
  // -----------------------
  // * routine d'affichage *
  // -----------------------
  for (ligne = 0 ; ligne<16;ligne++)
  {
    memcpy((char*)adr_destination+d_px+((d_py+ligne)*160),(char*)adr_source+s_px+((s_py+ligne)*160),8);
  }

}



// ===========================================================
// * Fonction ....: save_init_st()                           *
// ===========================================================
//  Role .........: Permet de sauvegarder l'état du ST.      * 
//  ..............: (Resolution, Mode video, Adresse Ecran)  *
//  Parametre ....: Aucun                                    *
//  Retour .......: Aucun                                    *
// ===========================================================
void save_init_st()
{ 
  // -------------------------------------
  // * Declaration des variables locales *
  // -------------------------------------
  unsigned char i; 
  
  // ---------------------------
  // * Sauvegarder les données *
  // ---------------------------
  Save_Ecran_Phys = Physbase();
  Save_Ecran_Log = Logbase();
  Save_Ecran_Mode_Video = Getrez();

  // -------------------------------------
  // * Sauvegarder la palette de couleur *
  // -------------------------------------
  for (i=0;i<16;i++)
  {
    *(Save_Buffer_Palette+i) = Setcolor(i,-1);
  }
  
}

// ===========================================================
// * Fonction ....: restore_init_st()                        *
// ===========================================================
//  Role .........: Permet de retablir les parametre du st   * 
//  Parametre ....: Aucun                                    *
//  Retour .......: Aucun                                    *
// ===========================================================
void restore_init_st()
{
  Setscreen(Save_Ecran_Phys,Save_Ecran_Log,Save_Ecran_Mode_Video);
  Setpalette(Save_Buffer_Palette);
  Vsync(); // 
}


// ===========================================================
// * Fonction ....: bip_clavier_off()                        *
// ===========================================================
//  Role .........: Desactive les BIP du Clavier             * 
//  Parametre ....: Aucun                                    *
//  Retour .......: Aucun                                    *
// ===========================================================
void bip_clavier_off() 
{
  Supexec((void*)clavier_off); 
}
 
 
// ===========================================================
// * Fonction ....: bip_clavier_on()                         *
// ===========================================================
//  Role .........: Active les BIP du Clavier                * 
//  Parametre ....: Aucun                                    *
//  Retour .......: Aucun                                    *
// ===========================================================
void bip_clavier_on() 
{ 
  Supexec((void*)clavier_on);
}

// ===========================================================
// * Fonction ....: load_picture(...)                        *
// ===========================================================
//  Role .........: Charge et affiche une image              * 
//  Parametre ....: char* name                               *
//  ..............:   Adresse de l'image                     *
//  ..............: long* destination                        *
//  ..............:   Adresse cible des datas                *
//  ..............: unsigned char option                     *
//  ..............:   Option de la fonction                  *
//  Retour .......: Aucun                                    *
// ===========================================================
void load_picture(char* name,long* destination,unsigned char option)
{
  // Offset 
  // 0     = Resolution d'ecran xx yy xx (compresser ou pas) 
  // 2     = Palette de couleur (32 octets)
  //34     = Data Image (32ko)
  
  // ----------
  // * Option *
  // ----------
  /*
    xxxxxabc
    
    a = 1 : active la résolution
    b = 1 : active la palette de couleur
    c = 1 : active la copie de data
  
    Compression d'image :
    pseudo RLE :
    Ligne par ligne
    
    128*
    
    
  
  
  */
    
  // -----------------------------
  // * Declaration des variables *
  // -----------------------------
  signed int f_handles;
  unsigned char picture_buffer[32034];
 /* char *adr_palette;
 adr_palette = &picture_buffer[2];*/
  // -------------------------
  // * Chargement de l'image *
  // -------------------------  
  f_handles = Fopen(name,0);
  
  // -----------------------------------------------
  // * Tester si il n'y pas d'erreur de chargement *
  // -----------------------------------------------
  if (f_handles >= 0)
  {
    // -------------------------------
    // * Placer les donnés en buffer *
    // -------------------------------
    Fread(f_handles,32034,picture_buffer);
  
    // ---------------------
    // * Fermer le fichier *
    // ---------------------
    Fclose(f_handles);

    // ------------------------------------------
    // * Configuration de la résolution d'écran *
    // ------------------------------------------
    // * 1er octet = h0, image non compresser, et si il est égale à h80 image compresser.
    // * 2em octets de l'image 0,1,2 pour la résolution de l'image.

    if ((option&0x4)==0x4) //  %100
    {
      Setscreen(Logbase(),Physbase(),picture_buffer[1]);
    }
    
    // ------------------------------------------
    // * Configuration de la palette de couleur *
    // ------------------------------------------
   
    if ((option&0x2)==0x2)
    {
     // Setpalette((picture_buffer)+2);
       // Setpalette((void*)adr_palette);
     Setpalette((void*)&picture_buffer[2]);
   }

    // -----------------------------------
    // * Afficher l'image dans le buffer *
    // -----------------------------------
    
    if ((option&0x1)==0x1)
    {
      memcpy((char*)destination ,(picture_buffer)+34,32000);
    }
 
  }
  
  // ------------------------
  // * Erreur de chargement *
  // ------------------------
  else
  {
    draw_error(f_handles);
  }

}

// ======================================================================
// * Fonction ....: load_data(char* source,char* destination,long size) *
// ======================================================================
//  Role .........: Charge un fichier et memorise son contenue          *
//  ..............: a partir d'une adresse                              * 
//  Parametre ....: char* source                                        *
//  ..............:   Adresse du fichier                                *
// ...............: char* destination                                   *
// ...............:   Adresse de destination                            *
// ...............: long size                                           *
// ...............:   Taille des donnés à copier                        *
//  Retour .......: Aucun                                               *
// ======================================================================
void load_data(char* source,char* destination,long size)
{
  // -------------------------------------
  // * Declaration des variables locales *
  // -------------------------------------
  signed int f_handles;
  DTA dta;
  
  // -------------------------
  // * Ouverture du fichier  *
  // -------------------------
  f_handles = Fopen(source,0);

  // -------------------------------
  // * Fichier correctement ouvert *
  // -------------------------------
  if (f_handles >= 0)
  {
    // -----------------------------------------------
    // * Calcule automatique de la taille du fichier *
    // -----------------------------------------------
    if (size==-1)
    {
      // -------------------------------
      // * preparation des données dta *
      // -------------------------------
      Fsetdta(&dta);
      Fsfirst(source,0);

      // ----------------------------------
      // * Recuperer la taille du fichier *
      // ----------------------------------
      size = dta.d_length;    

    }

    // ----------------------------------------------
    // * Placer les donnés en dans le buffer voulu  *
    // ----------------------------------------------
    Fread(f_handles,size,destination);
    // ---------------------
    // * Fermer le fichier *
    // ---------------------
    Fclose(f_handles);
  }
  else
  {    
    draw_error(f_handles);
  }

}

// ======================================================================================
// * Fonction ....: draw_text(unsigned char position_x,unsigned char position_y,        *
// * .............: char* texte,unsigned char couleur, unsigned char bakckground_color) *
// ======================================================================================
//  Role .........: Affiche un texte à l'écran                                          *
//  Parametre ....: unsigned char position_x                                            *
//  ..............:   Position X du texte                                               *
// ...............: unsigned char position_y                                            *
// ...............:   Position Y du texte                                               *
// ...............: char* texte                                                         *
// ...............:   Texte à afficher                                                  *
// ...............: unsigned char couleur                                               *
// ...............:   Couleur du texte                                                  *
// ...............: unsigned char bakckground_color                                     *
// ...............:   Couleur du background                                             *
//  Retour .......: Aucun                                                               *
// ======================================================================================

void draw_text(unsigned char position_x,unsigned char position_y,char* texte,unsigned char couleur, unsigned char bakckground_color)
{
  printf("\033Y%c%c", 32+position_y, 32+position_x ); 
  printf("\033b%c" , couleur);
  printf("\033c%c", bakckground_color);fflush(stdout);
  Cconws(texte);
}

// ===========================================================
// * Fonction ....: draw_error(int id_error)                 *
// ===========================================================
//  Role .........: Affiche une erreur à l'écran             * 
//  Parametre ....: int id_error                             *
//  ..............:   Id de l'erreur                         *
//  Retour .......: Aucun                                    *
// ===========================================================
void draw_error(int id_error)
{
  // -------------------------------
  // * Tester et Afficher l'erreur *
  // -------------------------------
  switch (id_error)
  {
    case -33 :  draw_text(0,0,"FILLE NOT FOUND",1,0); break;
    case -34 :  draw_text(0,0,"PATH NOT FOUND",1,0); break;
  }
}

// ===========================================================
// * Fonction ....: get_keyboard()                           *
// ===========================================================
// Role .........: Recupere une touche du clavier            * 
// Parametre ....: Aucun                                     *
// Retour .......: short                                     *
// ..............:  Id de la touche                          *
// note .........: Attention c'est du short                  *
// ===========================================================
short get_keyboard()
{
  // ---------------------------
  // * Declaration de variable *
  // ---------------------------
  short id_key;
  
  // --------------------
  // * Tester la rouche *
  // --------------------
  if(Cconis()!= 0)
  {     
    id_key = Crawcin()>>16;   
  }
 
  // -----------------------------
  // * Renvois l'id de la touche *
  // -----------------------------
  return id_key;
}



// =======================
// * Bip Clavier routine *
// =======================
void clavier_off() 
{
   CONTERM &= 0xFE;
}
 
void clavier_on() 
{ 
  CONTERM |= 0x01;
}