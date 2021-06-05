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

#ifndef  CVIDEO_H
  #define CVIDEO_H

  // ==========
  // * Define *
  // ==========
  
  // + ---------- +
  // * Transition *
  // + ---------- +
  #define T_OUT 0
  #define T_IN 1

  // ==============================
  // * Declaration des prototypes *
  // ==============================
  void cls(); // Effacer l'écran logique et physique
  void wait_time_vbl(unsigned int value); // Attendre X vbl
  void transition(unsigned char value);   // Transition
  
#endif