// ****************************************************************
// * Nom ................ Happy St                                *
// * Programmeur ........ Jean Monos                              *
// * Data mise à jour.... 17/05/2021                              *
// * Fonction ........... Fonction dev pour Atari Ste VBCC        *
// * Licence ............ CC-BY-SA                                *
// ****************************************************************

#ifndef HAPPST_H
	#define  HAPPST_H
  
  // ===================
  // * Fichier include *
  // ===================

   
  // ==========
  // * Define *
  // ==========

  #define CONTERM *((unsigned char *) 0x484)
  

  // ==================
  // * Define keybord *
  // ==================

  #define K_KEY_UP     0x48
  #define K_KEY_LEFT   0x4B
  #define K_KEY_RIGHT  0x4D
  #define K_KEY_DOWN   0x50

  #define K_KEY_ESC    0x01 // Bug ?
  #define K_KEY_RETURN 0x1C
  #define K_KEY_SPACE  0x39
  #define K_KEY_ENTER  0x72
  
  // =========================
  // * Define option_picture *
  // =========================
  #define OP_RESOLUTION 0x4
  #define OP_PALETTE 0x2
  #define OP_DATA 0x1
  
  
  // ===========================
  // * Signature des fonctions *
  // ===========================
  void save_init_st();
  void restore_init_st();
  void clavier_off();
  void clavier_on();
  void bip_clavier_off();
  void bip_clavier_on();
  void load_picture(char* name,long* destination,unsigned char option);
  void load_data(char* source,char* destination,long size);
  void draw_text(unsigned char position_x,unsigned char position_y,char* texte,unsigned char couleur, unsigned char bakckground_color);
  void draw_error(int id_error);
  short get_keyboard();
  void soft_copy_tiles(long* adr_source, long* adr_destination,unsigned char s_px,unsigned char s_py,unsigned char d_px,unsigned char d_py);
  short get_joy()  ;
#endif