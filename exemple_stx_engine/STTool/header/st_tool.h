// +++++++++++++++++++++++++++++++++
// +  st_tool pour atari st        +
// +         05/07/2021            +                   
// +++++++++++++++++++++++++++++++++
// *                               *
// *    Version 0.0.0              *
// *                               *
// +++++++++++++++++++++++++++++++++

#ifndef  ST_TOOL_H
  #define ST_TOOL__H
  
  // =========================
  // * Define option_picture *
  // =========================
  #define OP_RESOLUTION 0x4
  #define OP_PALETTE 0x2
  #define OP_DATA 0x1
  
  // ===========================
  // * Signature des fonctions *
  // ===========================
  signed int STT_load_picture(char* name,long* destination,unsigned char option);
  
#endif