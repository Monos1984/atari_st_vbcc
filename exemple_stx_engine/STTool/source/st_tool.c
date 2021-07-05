// +++++++++++++++++++++++++++++++++
// +  st_tool pour atari st        +
// +         05/07/2021            +                   
// +++++++++++++++++++++++++++++++++
// *                               *
// *    Version 0.0.0              *
// *                               *
// +++++++++++++++++++++++++++++++++


// ===================
// * Fichier include *
// ===================
#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 
#include <tos.h>

// ===========================================================
// * Fonction ....: STT_load_picture(...)                    *
// ===========================================================
//  Role .........: Charge et affiche une image              * 
//  Parametre ....: char* name                               *
//  ..............:   Adresse de l'image                     *
//  ..............: long* destination                        *
//  ..............:   Adresse cible des datas                *
//  ..............: unsigned char option                     *
//  ..............:   Option de la fonction                  *
//  Retour .......: f_handles                                *
// ===========================================================
signed int STT_load_picture(char* name,long* destination,unsigned char option)
{
  // + ------------------------ +
  // * Organisation d'une image *
  // + ------------------------ +
  
  /*
    Offset     
      0      Resolution d'ecran xx yy xx (compresser ou pas) 
      2      Palette de couleur (32 octets)
      34     Data Image (32ko)
  */
      
  // + ------------------------- +
  // * Declaration des variables *
  // + ------------------------- +
  signed int f_handles;
  unsigned char picture_buffer[32034];
 
  // + --------------------- +
  // * Chargement de l'image *
  // + --------------------- + 
  f_handles = Fopen(name,0);
  
  // + ------------------------------------------- +
  // * Tester si il n'y pas d'erreur de chargement *
  // + ------------------------------------------- +
  if (f_handles >= 0)
  {
    // + ---------------------------- +
    // * Placer les données en buffer *
    // + ---------------------------- +
    Fread(f_handles,32034,picture_buffer);
  
    // + ----------------- +
    // * Fermer le fichier *
    // + ----------------- +
    Fclose(f_handles);

    // + -------------------------------------- +
    // * Configuration de la résolution d'écran *
    // + -------------------------------------- +    
    /*
       * 1er octet = h0, image non compresser, et si il est égale à h80 image compresser.
       * 2em octets de l'image 0,1,2 pour la résolution de l'image.
    */

    if ((option&0x4)==0x4) //  %100
    {
      Setscreen(Logbase(),Physbase(),picture_buffer[1]);
    }
    
    // + -------------------------------------- +
    // * Configuration de la palette de couleur *
    // + -------------------------------------- +
    if ((option&0x2)==0x2)
    {     
     Setpalette((void*)&picture_buffer[2]);
    }

    // + ---------------- +
    // * Afficher l'image *
    // + ---------------- +
    if ((option&0x1)==0x1)
    {
      memcpy((char*)destination ,(picture_buffer)+34,32000);
    }
  }
  
  
  return f_handles;
}