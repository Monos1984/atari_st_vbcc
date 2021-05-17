@echo off
rem =================================================
rem * Fichier bat de compilation VBCC pour Atari st *
rem * 17/05/2021                                    *
rem * Jean Monos                                    *
rem =================================================

rem ===========================
rem * Configuration des liens *
rem ===========================

rem ------------------
rem * Lien du projet *
rem ------------------
set SOURCE=source
set F_INCLUDE=I:\0000-atari\targets\m68k-atari\include
set OUT=bin
set NAME=hello.tos

rem -----------------------
rem * Lien du compilateur *
rem -----------------------
set CC=vbccm68ks
set CA=vasmm68k_mot
set CL=vlink


echo =================
echo - Menage        -
echo =================
if exist %OUT%\%NAME% del %OUT%\%NAME%

echo =================
echo - Compilation C -
echo =================
for %%i in (%SOURCE%\*.c) do ( 
echo ----------------------------
echo %%~nxi
echo ----------------------------
%CC% -c99  %SOURCE%/%%~nxi -I%F_INCLUDE% 
)

echo ===================
echo - Compilation ASM -
echo ===================

for %%i in (%SOURCE%\*.asm) do ( 
echo ----------------------------
echo %%~nxi
echo ----------------------------
%CA% -Faout -mid=0 -phxass -nowarn=62  source/%%~nxi -o source/%%~ni.o

)

echo ===================
echo - Editeur de lien -
echo ===================
%CL% -EB -bataritos -x -Bstatic -Cvbcc -nostdlib "I:\0000-atari\targets\m68k-atari\lib\startup16.o" source/*.o -L"I:\0000-atari\targets\m68k-atari\lib" -lvc16 I:\0000-atari\targets\m68k-atari\lib\libgem16.a -o %OUT%\%NAME%

echo -------------------------------------------------------
if exist %OUT%\%NAME% ( echo %NAME% is create in folder %OUT%  ) else (%NAME% not compiled)
echo -------------------------------------------------------

pause

echo ===========================
echo - Effacement des fichiers -
echo ===========================
if exist %SOURCE%\*.asm del %SOURCE%\*.asm
if exist %SOURCE%\*.o del %SOURCE%\*.o
pause