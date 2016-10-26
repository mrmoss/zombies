#ifndef _SOUND_
#define _SOUND_

//Sound Engine
#include <include/irrKlang.h>
using namespace irrklang;

#include <stdexcept>
using std::runtime_error;
using std::logic_error;

class backgroundSound
{
	public:
	//Constructor
	backgroundSound(): _trackNum(rand() % 5), _playing(false), _engine(createIrrKlangDevice())
	{
	    if(_engine)
		{
			//Initializes Filenames
			filenames[0] = _engine->addSoundSourceFromFile("sounds\\Background\\Track_1.mp3");
			filenames[1] = _engine->addSoundSourceFromFile("sounds\\Background\\Track_2.mp3");
			filenames[2] = _engine->addSoundSourceFromFile("sounds\\Background\\Track_3.mp3");
			filenames[3] = _engine->addSoundSourceFromFile("sounds\\Background\\Track_4.mp3");
			filenames[4] = _engine->addSoundSourceFromFile("sounds\\Background\\Track_5.mp3");

			//Initializes Background Music Objects
			//Regular Background Music
			background_music[0] = _engine->play2D(filenames[0], false, true, true);
			background_music[1] = _engine->play2D(filenames[1], false, true, true);
			background_music[2] = _engine->play2D(filenames[2], false, true, true);
			background_music[3] = _engine->play2D(filenames[3], false, true, true);
			background_music[4] = _engine->play2D(filenames[4], false, true, true);
			//Star Power Background Music
			star_power = _engine->play2D("sounds\\Pickups\\Star Power.ogg", true, true, true);

			//This functions initially starts the background music
			if(!_playing)
			{
				background_music[_trackNum]->setIsPaused(false);
				_playing = true;
			}
		}
		else
		{throw runtime_error("_engine member variable did not start!");}
	}

	//Destructor
	~backgroundSound()
	{
        for(int i = 0; i < 5; i++)
	    {
	        background_music[i]->drop();
	        filenames[i]->drop();
	    }

	    _engine->drop();
    }

	//Update Function to go with all other update functions
	void update()
	{
		//If the current track has ended, it switches to a new one
		if(background_music[_trackNum]->isFinished())
		{
		    //resets previous song
		    background_music[_trackNum] = _engine->play2D(filenames[_trackNum], false, true, true);
			_trackNum = (rand() % 5);
			//Plays new song
			background_music[_trackNum]->setIsPaused(false);
		}
	}

	//Background music setIsPaused function
	void setIsPaused(bool _paused)
	{background_music[_trackNum]->setIsPaused(_paused);}

	//Function for dealing with star power music
	void setStarPower(bool starpower)
	{
		//If star power is active, this function switches music
		if(starpower)
		{
			//Pauses background music
			background_music[_trackNum]->setIsPaused(true);
			//Unpauses star power music
			star_power->setIsPaused(false);
		}

		else
		{
			//Pauses star power music
			star_power->setIsPaused(true);
			//Unpauses background music
			background_music[_trackNum]->setIsPaused(false);
		}
	}

	private:
	int _trackNum;                 //Current playing track
	bool _playing;                 //Initial check for backgroun music
	ISoundEngine * _engine;        //Sound engine object
	ISoundSource * filenames[5];   //For filenames
	ISound * background_music[5];  //Background Music Array
	ISound * star_power;           //Star Power Music
};

#endif
