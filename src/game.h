#ifndef ZOMBIES_GAME_H
#define ZOMBIES_GAME_H

//Icon (Windows Only)
#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <winver.h>
#endif

//General Utilities Header
#include <cstdlib>
    using std::exit;
    using std::srand;
    using std::rand;

//Vector Header
#include <vector>
    using std::vector;

//Math Header
#include <cmath>
    using std::min;
    using std::max;

//TESTING Header
//#include <iostream>
    //using std::cout;
    //using std::endl;

//File Stream
#include <fstream>
    using std::fstream;
    using std::ifstream;
    using std::ofstream;
    using std::endl;

//String Header
#include <string>
    using std::string;

//String Stream Header
#include <sstream>
    using std::ostringstream;

//Sound Engine
#include <irrKlang/irrKlang.h>
#include <irrKlang/ik_ISound.h>
using irrklang::ISoundEngine;
using irrklang::createIrrKlangDevice;
using irrklang::ISound;
using irrklang::ik_f32;

//Creates Sound Engine
ISoundEngine *sound_engine=createIrrKlangDevice();

//Constant Globals
const int MAXDEPTH=100;

//Globals
double viewX=0.0;
double viewY=0.0;
bool paused=false;
int stage=0;
int credits=0;
bool gameover=false;

//Name and Score Variables
string playerName="";
vector<string> highscoreNames;
vector<int> highscoreScores;
unsigned int highscorePosition=-1;

//Global Spawning System Variables
double spawnWait=0.0;
bool spawnChange=true;
int spawnMax=0;
int spawnHorde=0;
unsigned int spawnSquad=0;
int spawnWave=0;
double spawnTime=5.0;

//Global Fader Variables
double fadeValue=0.0;
double fadeDecay=0.0;
bool fade=false;

/*//Global Day/Night Variables
double lightingDay=0.0;
double lightingNight=0.0;
double lighting=0.0;
double lightingDecay=0.0;
bool lightingToggle=false;*/

//Global Heath Level Indicator Variables
bool blooded=false;
double bloodedValue=0.0;
double bloodedDecay=0.0;

//Global Text Cursor Blink Variables
double blink=true;
double blinkValue=1.0;
double blinkDecay=10.0;

//Spritelib Headers
#include "spritelib/spritelib.h"
#include "spritelib/spritelib_anim.h"
#include "spritelib/spritelib_text.h"

//Classes Header
#include "classes.h"

//End Game
void endGame();

//Initialization for Switching to Highscores Stage Prototype
void initHighscores(const bool);

//Main Spritelib Loop Prototype
void spritelib_draw_screen(spritelib &);

//Main Loop
int main()
{
    //Check Sound Engine
    if(!sound_engine)
    {
        return 0;
    }

    //Create Spritelib Instance
    spritelib_run("Zombies!",184.0*1.6,184.0);

    //Return
    return 0;
}

#endif
