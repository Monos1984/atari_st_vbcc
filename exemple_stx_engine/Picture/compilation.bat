@echo off
rem *************************************************
rem * Fichier bat de compilation VBCC pour Atari st *
rem * et le librairie STGFXEngine                   *
rem * 01/07/2021                                    *
rem * Jean Monos                                    *
rem *************************************************

rem ===================================
rem * Lien de configuration du projet *
rem ===================================

rem -------------------
rem * Lien du dossier *
rem ------------------- 
set link_sdk=C:\Users\monos\Desktop\atari_tuto

rem ---------------------------------
rem * Lien du code source du projet *
rem ---------------------------------
set SOURCE=source

rem ----------------------------------------------------------
rem * Lien du dossier ou se trouve les outils de compilation *
rem ----------------------------------------------------------
set COMPILE_BIN=%link_sdk%\VBCC\bin\

rem ---------------------------------
rem * lien des includes de la cible *
rem ---------------------------------
set F_INCLUDE=%link_sdk%\VBCC\targets\m68k-atari\include


rem -------------------------------------
rem * lien de sortie du fichier binaire *
rem -------------------------------------
set OUT=bin

rem --------------------------
rem * nom du fichier binaire *
rem --------------------------
set NAME=picture.prg

rem -------------------------------------------
rem * lien du fichier o de la librairie STGFX *
rem -------------------------------------------
set GFX_LIB=%link_sdk%/STGFXEngine/bin/STGFXLIB.o

rem -----------------------------
rem * lien du dossier GFXENGINE *
rem -----------------------------
set GFX_INCLUDE=%link_sdk%/STGFXEngine

rem --------------------------------------
rem * lien du dossier include personelle *
rem --------------------------------------
set HEADER_INCLUDE="source/header/"

rem --------------------------------------
rem * lien du dossier include du st_tool *
rem --------------------------------------
set HEADER_ST_TOOL="%link_sdk%/STTool/header"
set OBJET_ST_TOOL="%link_sdk%/STTool/objet"

rem -----------------------
rem * Lien du compilateur *
rem -----------------------
set CC=%COMPILE_BIN%vbccm68ks
set CA=%COMPILE_BIN%vasmm68k_mot
set CL=%COMPILE_BIN%vlink

rem ========================================
rem * Deroulement du script de compilation * 
rem ========================================

echo ================================
echo - Effacement des fichiers      -
echo ================================
if exist %OUT%\%NAME% del %OUT%\%NAME%
if exist %SOURCE%\*.asm del %SOURCE%\*.asm
if exist %SOURCE%\*.o del %SOURCE%\*.o

echo ===========================================
echo - Preprocesseur et Compilation (C en ASM) -
echo ===========================================

for %%i in (%SOURCE%\*.c) do ( 
echo ----------------------------
echo %%~nxi
echo ----------------------------
%CC% -c99 -quiet %SOURCE%/%%~nxi -DID_LANGUE=%LANGUE% -O=1 -I%F_INCLUDE% -I%GFX_INCLUDE% -I%HEADER_INCLUDE% -I%HEADER_ST_TOOL%
)

echo =========================
echo - Assemblage (ASM en o) -
echo =========================

for %%i in (%SOURCE%\*.asm) do ( 
echo ----------------------------
echo %%~nxi
echo ----------------------------
%CA% -quiet -Faout -mid=0 -phxass -nowarn=62  source/%%~nxi -o source/%%~ni.o

)

echo ===================
echo - Editeur de lien -
echo ===================

%CL% -EB -bataritos -x -Bstatic -Cvbcc -nostdlib "%link_sdk%\VBCC\targets\m68k-atari\lib\startup16.o"  source/*.o  %OBJET_ST_TOOL%/*.o %GFX_LIB% -s -L"%link_sdk%\VBCC\targets\m68k-atari\lib" -lvc16 -o %OUT%\%NAME%

echo -------------------------------------------------------
if exist %OUT%\%NAME% ( echo %NAME% is create in folder %OUT% ) else (%NAME% not compiled)
echo -------------------------------------------------------

pause

echo ===========================
echo - Effacement des fichiers -
echo ===========================
if exist %SOURCE%\*.asm del %SOURCE%\*.asm
if exist %SOURCE%\*.o del %SOURCE%\*.o
pause