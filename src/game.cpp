//Linker for Game.h
#include "game.h"

//Initialization for Switching to Highscores Stage
void initHighscores(const bool insert)
{
    //Check if Inserting
    if(!insert)
    {
        spawnWave=-1;
    }

    //Highscores Temporary Variables
    string tempName;
    int tempScore;

    //Read in Highscores
    ifstream istr("scores.txt");

    while(istr>>tempName&&istr>>tempScore)
    {
        highscoreNames.push_back(tempName);
        highscoreScores.push_back(tempScore);
    }

    istr.close();

    //Fill In Empty Highscore Names
    while(highscoreNames.size()<10)
    {
        highscoreNames.push_back("ABC");
    }

    //Fill In Empty Highscore Scores
    while(highscoreScores.size()<10)
    {
        highscoreScores.push_back(0);
    }

    //Get Highscore Position
    for(int i=0;i<10;i++)
    {
        if(spawnWave>=highscoreScores[i])
        {
            highscorePosition=i;
            break;
        }
    }

}

//Spritelib Loop
void spritelib_draw_screen(spritelib &lib)
{
    //Stage Switching Variable
    static int stageNext=stage;

    //Pause Variables
    static double dtOld=1.0;

    //Play Music
    static Sound sndTitle(sound_engine,"sounds/sndTitle.wav",true,0.8);

    //Global Create Variable
    static bool created=false;

    //Create
    if(!created)
    {
        //Fullscreen
        glutFullScreen();

        //Hide Mouse
        glutSetCursor(GLUT_CURSOR_NONE);

        //Set Global Fader Variables
        fadeValue=1.0;
        fadeDecay=5.0;
        fade=false;

        /*//Set Global Day/Night Variables
        lightingDay=1.0;
        lightingNight=0.4;
        lighting=lightingDay;
        lightingDecay=5.0;
        lightingToggle=true;*/

        //Set Global Heath Level Indicator Variables
        blooded=false;
        bloodedValue=0.0;
        bloodedDecay=5.0;

        //Seed Random
        srand(lib.dt*lib.dt);

        //Load Textures
        Player::getTextures(lib);
        Zombie::getTextures(lib);
        Barricade::getTextures(lib);
        Effect::getTextures(lib);
        Pickup::getTextures(lib);

        //No More Creating
        created=true;
    }

    //Screen Scale
    lib.screenscale=lib.screenh/92.0;

    //Stage Create Variables
    static bool menuCreated=false;
    static bool gameCreated=false;
    static bool infoCreated=false;
    static bool highscoreCreated=false;

    //Fade In
    if(fade&&fadeValue>0.0)
    {
        fadeValue-=fadeDecay*lib.dt;
    }
    else if(fadeValue==0.0&&fade)
    {
        while(Object::Objects.size()>0)
        {
            delete Object::Objects[Object::Objects.size()-1];
        }

        blooded=false;
        fade=false;
        stage=stageNext;
        paused=false;
        menuCreated=false;
        gameCreated=false;
        infoCreated=false;
        highscoreCreated=false;
    }

    //Fade Out
    if(!fade&&fadeValue<1.0)
    {
        fadeValue+=fadeDecay*lib.dt;
    }

    //Fade Restraints
    if(fadeValue>1.0)
    {
        fadeValue=1.0;
    }
    else if(fadeValue<0.0)
    {
        fadeValue=0.0;
    }

    /*//Fade In to Night
    if(!lightingToggle&&lighting>lightingNight)
    {
        lighting-=lightingDecay*lib.dt;
    }

    //Fade Out to Day
    if(lightingToggle&&lighting<lightingDay)
    {
        lighting+=lightingDecay*lib.dt;
    }

    //Day/Night Constraints
    if(lighting>1.0)
    {
        lighting=1.0;
    }
    else if(lighting<0.0)
    {
        lighting=0.0;
    }*/

    //Health Indicator Fade Out
    if(blooded&&bloodedValue<1.0)
    {
        bloodedValue+=bloodedDecay;
    }
    else if(blooded&&bloodedValue>=1.0&&!gameover)
    {
        blooded=false;
    }

    //Health Indicator Fade Out
    if(!blooded&&bloodedValue>0.0)
    {
        bloodedValue-=bloodedDecay;
    }

    //Health Indicator Restraints
    if(bloodedValue>1.0)
    {
        bloodedValue=1.0;
    }
    else if(bloodedValue<0.0)
    {
        bloodedValue=0.0;
    }

    //Text Cursor Blinker Code
    if(blink&&blinkValue>0.0)
    {
        blinkValue-=blinkDecay*lib.dt;
    }
    else if(blink&&blinkValue<=0.0)
    {
        blink=false;
    }

    if(!blink&&blinkValue<1.0)
    {
        blinkValue+=blinkDecay*lib.dt;
    }
    else if(!blink&&blinkValue>=1.0)
    {
        blink=true;
    }

    //Fader Code
    glColor3f(fadeValue,fadeValue-bloodedValue,fadeValue-bloodedValue);

    //Day/Night Lighting
    //glColor3f(min(fadeValue,lighting),min(fadeValue,lighting)-bloodedValue,min(fadeValue,lighting)-bloodedValue);

    //Load Background Texture
    static spritelib_tex background=lib.read_tex("sprites/backgrounds/background.png");

    //Load Tracks Texture
    static spritelib_tex track=lib.read_tex("sprites/backgrounds/tracks.png");

    //Load Trains Texture
    static spritelib_tex trains=lib.read_tex("sprites/backgrounds/trains.png");

    //Load Cursor
    static spritelib_tex tex_hud_cursor=lib.read_tex("sprites/hud/hud_cursor.png");
    static spritelib_anim hud_cursor(tex_hud_cursor,40.0,26.0,2,1);

    //Load Text
    static spritelib_tex tex_hud_text_cursor=lib.read_tex("sprites/hud/hud_text_cursor.png");
    static spritelib_tex tex_hud_text_large=lib.read_tex("sprites/hud/hud_text_large.png");
    static spritelib_text hud_text_large(tex_hud_text_large,20.0,20.0,43);

    //Load Hud Keys
    static spritelib_tex tex_hud_keys=lib.read_tex("sprites/hud/hud_keys.png");
    static spritelib_anim hud_keys(tex_hud_keys,42.0,40.0,10,1);

    //Load Pickup Sprites
    static spritelib_tex tex_hud_pickup_uzi=lib.read_tex("sprites/pickups/pickup_uzi.png");
    static spritelib_tex tex_hud_pickup_shotgun=lib.read_tex("sprites/pickups/pickup_shotgun.png");
    static spritelib_tex tex_hud_pickup_instakill=lib.read_tex("sprites/pickups/pickup_instakill.png");
    static spritelib_tex tex_hud_pickup_nuke=lib.read_tex("sprites/pickups/pickup_nuke.png");
    static spritelib_tex tex_hud_pickup_star=lib.read_tex("sprites/pickups/pickup_star.png");
    static spritelib_anim hud_pickup_uzi(tex_hud_pickup_uzi,30.0,30.0,6,1);
    static spritelib_anim hud_pickup_shotgun(tex_hud_pickup_shotgun,30.0,30.0,6,1);
    static spritelib_anim hud_pickup_instakill(tex_hud_pickup_instakill,30.0,30.0,5,1);
    static spritelib_anim hud_pickup_nuke(tex_hud_pickup_nuke,30.0,30.0,1,1);
    static spritelib_anim hud_pickup_star(tex_hud_pickup_star,30.0,30.0,4,1);

    //If In Menu
    if(stage==0)
    {
        //Static Variables
        static int menuOption=0;

        //Create Menu
        if(!menuCreated)
        {
            //Check Music
            sndTitle.play();

            //Set Menu Option Variable
            //menuOption=0;

            //Set Highscore Variables to Defaults
            playerName="";
            highscoreNames.clear();
            highscoreScores.clear();
            highscorePosition=10;

            //Stop Creating
            menuCreated=true;
        }

        //Menu Variables
        double optionX[4];
        optionX[0]=(lib.screenw/lib.screenscale)-((10.0*0.5)*3.0);
        optionX[1]=(lib.screenw/lib.screenscale)-((10.0*0.5)*3.0);
        optionX[2]=(lib.screenw/lib.screenscale)-((10.0*0.5)*9.0);
        optionX[3]=(lib.screenw/lib.screenscale)-((10.0*0.5)*3.0);

        double optionY[4];
        optionY[0]=20.0+(20.0*2.75);
        optionY[1]=20.0+(20.0*3.75);
        optionY[2]=20.0+(20.0*4.75);
        optionY[3]=20.0+(20.0*5.75);

        //Move Cursor Up
        if(keyboard_check_pressed(kb_up)&&menuOption>0)
        {
            menuOption--;
            sound_engine->play2D("sounds/snd_beepUp.wav");
        }

        //Move Cursor Down
        if(keyboard_check_pressed(kb_down)&&menuOption<3)
        {
            menuOption++;
            sound_engine->play2D("sounds/snd_beepDown.wav");
        }

        //Draw Title
        hud_text_large.draw(lib,"ZOMBIES",(lib.screenw/lib.screenscale)-((10.0*0.5)*6.0),(20.0*1.0),0.5,0.5,0.0);

        //Draw Credits
        hud_text_large.draw(lib,"CREATED BY",(lib.screenw/lib.screenscale)-((10.0*0.25)*9.0),20.0+(20.0*0.5),0.25,0.25,0.0);
        hud_text_large.draw(lib,"CHARLES CARLSON",(lib.screenw/lib.screenscale)-((10.0*0.25)*14.0),20.0+(20.0*0.75),0.25,0.25,0.0);
        hud_text_large.draw(lib,"DUSTIN DODSON",(lib.screenw/lib.screenscale)-((10.0*0.25)*12.0),20.0+(20.0*1.0),0.25,0.25,0.0);
        hud_text_large.draw(lib,"MIKE MOSS",(lib.screenw/lib.screenscale)-((10.0*0.25)*8.0),20.0+(20.0*1.25),0.25,0.25,0.0);

        //Draw Menu
        hud_text_large.draw(lib,"PLAY",optionX[0],optionY[0],0.5,0.5,0.0);
        hud_text_large.draw(lib,"INFO",optionX[1],optionY[1],0.5,0.5,0.0);
        hud_text_large.draw(lib,"HIGHSCORES",optionX[2],optionY[2],0.5,0.5,0.0);
        hud_text_large.draw(lib,"EXIT",optionX[3],optionY[3],0.5,0.5,0.0);

        //Draw Copyright Notice
        hud_text_large.draw(lib,"THIS GAME IS FREE",(lib.screenw/lib.screenscale)-((10.0*0.25)*16.0),7.5+(20.0*7.75),0.25,0.25,0.0);
        hud_text_large.draw(lib,"ALL TRADEMARKS BELONG TO THEIR RIGHTFUL OWNERS",(lib.screenw/lib.screenscale)-((10.0*0.25)*45.0),
            7.5+(20.0*8.0),0.25,0.25,0.0);

        //Draw Cursor
        hud_cursor.draw(lib,keyboard_check(kb_z),optionX[menuOption]-10.0,optionY[menuOption],0.5,0.5,0.0);

        //Make a Selection
        if(keyboard_check_pressed(kb_z)&&!fade)
        {
            //Set Variables
            gameover=false;
            paused=true;
            fade=true;

            //Switch Stage
            switch(menuOption)
            {
                case 0:
                    stageNext=1;
                    gameCreated=false;
                    sndTitle.stop();
                    break;
                case 1:
                    stageNext=2;
                    break;
                case 2:
                    initHighscores(false);
                    stageNext=3;
                    break;
                case 3:
                default:
                    stageNext=4;
                    break;
            }

            if(menuOption!=3)
            {
                switch(rand()%4)
                {
                    case 0:
                        sound_engine->play2D("sounds/snd_argh01.wav");
                        break;
                    case 1:
                        sound_engine->play2D("sounds/snd_argh02.wav");
                        break;
                    case 2:
                        sound_engine->play2D("sounds/snd_argh03.wav");
                        break;
                    case 3:
                        sound_engine->play2D("sounds/snd_argh04.wav");
                        break;
                    default:
                        break;
                }
            }
        }
    }

    //If In Game
    else if(stage==1)
    {
        //Static Background Music Variable
        static Sound *sndBackgroundMusic;
        static int sndBackgroundMusicNum=rand()%4;
        static Sound sndBackground01(sound_engine,"sounds/snd_background01.wav",false,0.6);
        static Sound sndBackground02(sound_engine,"sounds/snd_background02.wav",false,0.6);
        static Sound sndBackground03(sound_engine,"sounds/snd_background03.wav",false,0.6);
        static Sound sndBackground04(sound_engine,"sounds/snd_background04.wav",false,0.8);

        //Create Game
        if(!gameCreated)
        {
            //Music
            sndBackground01.play();
            sndBackground01.stop();
            sndBackground02.play();
            sndBackground02.stop();
            sndBackground03.play();
            sndBackground03.stop();
            sndBackground04.play();
            sndBackground04.stop();

            //Credits
            credits=0;

            //Zombie Spawning System
            spawnWait=spawnTime;
            spawnChange=true;
            spawnMax=1;
            spawnHorde=1;
            spawnSquad=0;
            spawnWave=0;

            //Create Barricades
            new Barricade(254.0,108.0);
            Object *optr=new Barricade(800.0,108.0);
            optr->setXScale(-1.0);

            //Make a Player
            new Player(512.0,92.0);

            //Stop Creating
            gameCreated=true;
        }

        //Draw Background
        lib.draw(background,492.0-(viewX*0.80),92.0-viewY,1024.0,184.0,0.0);

        //Draw Tracks
        lib.draw(track,512.0-viewX,92.0-viewY,1024.0,184.0,0.0);

        //Draw Trains
        lib.draw(trains,512.0-viewX,92.0-viewY,1024.0,184.0,0.0);

        //Undo Lighting Changes
        glColor3f(1.0,1.0,1.0);

        //Music
        if(stageNext==1)
        {
            //Check for Player Star Power Effect
            for(unsigned int i=0;i<Player::Players.size();i++)
            {
                if(Player::Players[i]->_starpower)
                {
                    sndBackgroundMusic->pause();
                    break;
                }

                if(sndBackgroundMusic!=NULL&&!sndBackgroundMusic->isFinished())
                {
                    sndBackgroundMusic->play();
                }
            }

            //Random Background Music
            if(sndBackgroundMusic==NULL||(sndBackgroundMusic!=NULL&&sndBackgroundMusic->isFinished()))
            {
                 int sndMusicRandom=rand()%4;

                 while(sndMusicRandom==sndBackgroundMusicNum)
                 {
                     sndMusicRandom=rand()%4;
                 }

                 sndBackgroundMusicNum=sndMusicRandom;

                 switch(sndBackgroundMusicNum)
                 {
                      case 0:
                           sndBackgroundMusic=&sndBackground01;
                           break;
                      case 1:
                           sndBackgroundMusic=&sndBackground02;
                           break;
                      case 2:
                           sndBackgroundMusic=&sndBackground03;
                           break;
                      case 3:
                           sndBackgroundMusic=&sndBackground04;
                           break;
                      default:
                           sndBackgroundMusic=&sndBackground01;
                           break;
                 }

                 sndBackgroundMusic->play();
            }
        }

        //Update Objects
        if(!paused&&Object::Objects.size()>0)
        {
            for(unsigned int i=0;i<Object::Objects.size();i++)
            {
                if(Object::Objects[i]!=NULL)
                {
                    Object::Objects[i]->update(lib);
                }
            }
        }

        //Draw Objects
        if(Object::Objects.size()>0)
        {
            //Variable to Keep Track of the Number of Objects Drawn
            unsigned int count=0;

            while(count<Object::Objects.size())
            {
                for(int i=0;i<MAXDEPTH;i++)
                {
                    for(unsigned int k=0;k<Object::Objects.size();k++)
                    {
                        if(Object::Objects[k]->getDepth()==i)
                        {
                            if(Object::Objects[k]!=NULL)
                            {
                                Object::Objects[k]->draw(lib);
                            }
                            count++;
                        }
                    }
                }
            }
        }

        //Pause Toggle
        if(keyboard_check_pressed(kb_space))
        {
            paused=!paused;
            Sound sndPause(sound_engine,"sounds/snd_beepSelect.wav",false,1.0);
            sndPause.play();

            if(paused)
            {
                dtOld=lib.dt;
            }

            if(!paused)
            {
                lib.dt=dtOld;
            }
        }

        //Zombie Spawning System
        if(spawnWait>0.0&&!paused)
        {
            spawnWait-=lib.dt;
        }
        else if(spawnWait>-50.0&&!paused)
        {
            spawnWave++;

            if(spawnChange)
            {
                spawnMax*=2;
                if(spawnSquad<16)
                {
                    spawnSquad+=2;
                }
            }

            spawnHorde=spawnMax;

            spawnChange=!spawnChange;

            spawnWait=-100.0;
        }

        if(Zombie::Zombies.size()<spawnSquad&&spawnHorde>0&&!paused)
        {
            double spawnWidth[2];
            spawnWidth[0]=-125.0;
            spawnWidth[1]=925.0;

            new Zombie(spawnWidth[rand()%2]+static_cast<double>(rand()%222),92.0);
            spawnHorde--;
        }
        else if(spawnHorde==0&&Zombie::Zombies.size()==0&&!paused)
        {
            spawnWait=spawnTime;
            spawnHorde=-1;
        }

        //Switch Room When Game is Over
        if(gameover&&!fade)
        {
            //Initiate Highscores Stage
            initHighscores(true);

            //Stop Music
            sndBackgroundMusic->stop();
            sound_engine->stopAllSounds();

            //Switch Room
            gameover=false;
            paused=true;
            fade=true;
            stageNext=3;
        }

        //Cheat Key
        if(keyboard_check(kb_f10))
        {
            credits+=100;
        }

        //Draw Wave
        string waveZeros="";
        ostringstream waveStream;
        waveStream<<spawnWave;

        while(waveStream.str().size()+waveZeros.size()<4)
        {
            waveZeros+="0";
        }

        hud_text_large.draw(lib,"WAVE "+waveZeros+waveStream.str(),(lib.screenw/lib.screenscale)-100.0-((10.0*0.5)*8.0),10.0,0.5,0.5,0.0);

        //Draw Score
        string creditZeros="";
        ostringstream creditStream;
        creditStream<<credits;

        while(creditStream.str().size()+creditZeros.size()<11)
        {
            creditZeros+="0";
        }

        hud_text_large.draw(lib,"CREDITS "+creditZeros+creditStream.str(),(lib.screenw/lib.screenscale)-10.0-((10.0*0.5)*6.0),10.0,0.5,0.5,0.0);

        //Draw Hud Keys
        if(credits>=200)
        {
            glColor4f(fadeValue-(keyboard_check(kb_1)*!paused),fadeValue-(keyboard_check(kb_1)*!paused),
                fadeValue-(keyboard_check(kb_1)*!paused),1.0);
            hud_keys.draw(lib,0,(lib.screenw/lib.screenscale)-((42.0*0.25)*4.0),22.5,0.35,0.35,0.0);
            glColor4f(fadeValue,fadeValue,fadeValue,1.0);
            hud_pickup_uzi.draw(lib,4,(lib.screenw/lib.screenscale)-((42.0*0.25)*4.0)-((30.0*0.25)*0.5),
                22.5+((30.0*0.25)*0.5),0.25,0.25,0.0);
            hud_text_large.draw(lib,"200",(lib.screenw/lib.screenscale)-((42.0*0.25)*4.0)-((10.0*0.25)*2.0),32.5,0.25,0.25,0.0);
        }
        else
        {
            glColor4f(fadeValue,fadeValue,fadeValue,0.5);
            hud_keys.draw(lib,0,(lib.screenw/lib.screenscale)-((42.0*0.25)*4.0),22.5,0.35,0.35,0.0);
            hud_pickup_uzi.draw(lib,4,(lib.screenw/lib.screenscale)-((42.0*0.25)*4.0)-((30.0*0.25)*0.5),
                22.5+((30.0*0.25)*0.5),0.25,0.25,0.0);
            hud_text_large.draw(lib,"200",(lib.screenw/lib.screenscale)-((42.0*0.25)*4.0)-((10.0*0.25)*2.0),32.5,0.25,0.25,0.0);
            glColor4f(fadeValue,fadeValue,fadeValue,1.0);
        }

        if(credits>=300)
        {
            glColor4f(fadeValue-(keyboard_check(kb_2)*!paused),fadeValue-(keyboard_check(kb_2)*!paused),
                fadeValue-(keyboard_check(kb_2)*!paused),1.0);
            hud_keys.draw(lib,1,(lib.screenw/lib.screenscale)-((42.0*0.25)*2.0),22.5,0.35,0.35,0.0);
            glColor4f(fadeValue,fadeValue,fadeValue,1.0);
            hud_pickup_shotgun.draw(lib,1,(lib.screenw/lib.screenscale)-((42.0*0.25)*2.0)-((30.0*0.25)*0.5),
                22.5+((30.0*0.25)*0.5),0.25,0.25,0.0);
            hud_text_large.draw(lib,"300",(lib.screenw/lib.screenscale)-((42.0*0.25)*2.0)-((10.0*0.25)*2.0),32.5,0.25,0.25,0.0);
        }
        else
        {
            glColor4f(fadeValue,fadeValue,fadeValue,0.5);
            hud_keys.draw(lib,1,(lib.screenw/lib.screenscale)-((42.0*0.25)*2.0),22.5,0.35,0.35,0.0);
            hud_pickup_shotgun.draw(lib,1,(lib.screenw/lib.screenscale)-((42.0*0.25)*2.0)-((30.0*0.25)*0.5),
                22.5+((30.0*0.25)*0.5),0.25,0.25,0.0);
            hud_text_large.draw(lib,"300",(lib.screenw/lib.screenscale)-((42.0*0.25)*2.0)-((10.0*0.25)*2.0),32.5,0.25,0.25,0.0);
            glColor4f(fadeValue,fadeValue,fadeValue,1.0);
        }

        if(credits>=400)
        {
            glColor4f(fadeValue-(keyboard_check(kb_3)*!paused),fadeValue-(keyboard_check(kb_3)*!paused),
                fadeValue-(keyboard_check(kb_3)*!paused),1.0);
            hud_keys.draw(lib,2,(lib.screenw/lib.screenscale),22.5,0.35,0.35,0.0);
            glColor4f(fadeValue,fadeValue,fadeValue,1.0);
            hud_pickup_instakill.draw(lib,0,(lib.screenw/lib.screenscale)-((30.0*0.25)*0.5),
                22.5+((30.0*0.25)*0.5),0.25,0.25,0.0);
            hud_text_large.draw(lib,"400",(lib.screenw/lib.screenscale)-((10.0*0.25)*2.0),32.5,0.25,0.25,0.0);
        }
        else
        {
            glColor4f(fadeValue,fadeValue,fadeValue,0.5);
            hud_keys.draw(lib,2,(lib.screenw/lib.screenscale),22.5,0.35,0.35,0.0);
            hud_pickup_instakill.draw(lib,0,(lib.screenw/lib.screenscale)-((30.0*0.25)*0.5),
                22.5+((30.0*0.25)*0.5),0.25,0.25,0.0);
            hud_text_large.draw(lib,"400",(lib.screenw/lib.screenscale)-((10.0*0.25)*2.0),32.5,0.25,0.25,0.0);
            glColor4f(fadeValue,fadeValue,fadeValue,1.0);
        }

        if(credits>=800)
        {
            glColor4f(fadeValue-(keyboard_check(kb_4)*!paused),fadeValue-(keyboard_check(kb_4)*!paused),
                fadeValue-(keyboard_check(kb_4)*!paused),1.0);
            hud_keys.draw(lib,3,(lib.screenw/lib.screenscale)+((42.0*0.25)*2.0),22.5,0.35,0.35,0.0);
            glColor4f(fadeValue,fadeValue,fadeValue,1.0);
            hud_pickup_nuke.draw(lib,0,(lib.screenw/lib.screenscale)+((42.0*0.25)*2.0)-((30.0*0.25)*0.5),
                22.5+((30.0*0.25)*0.5),0.25,0.25,0.0);
            hud_text_large.draw(lib,"800",(lib.screenw/lib.screenscale)+((42.0*0.25)*2.0)-((10.0*0.25)*2.0),32.5,0.25,0.25,0.0);
        }
        else
        {
            glColor4f(fadeValue,fadeValue,fadeValue,0.5);
            hud_keys.draw(lib,3,(lib.screenw/lib.screenscale)+((42.0*0.25)*2.0),22.5,0.35,0.35,0.0);
            hud_pickup_nuke.draw(lib,0,(lib.screenw/lib.screenscale)+((42.0*0.25)*2.0)-((30.0*0.25)*0.5),
                22.5+((30.0*0.25)*0.5),0.25,0.25,0.0);
            hud_text_large.draw(lib,"800",(lib.screenw/lib.screenscale)+((42.0*0.25)*2.0)-((10.0*0.25)*2.0),32.5,0.25,0.25,0.0);
            glColor4f(fadeValue,fadeValue,fadeValue,1.0);
        }

        if(credits>=1000)
        {
            glColor4f(fadeValue-(keyboard_check(kb_5)*!paused),fadeValue-(keyboard_check(kb_5)*!paused),
                fadeValue-(keyboard_check(kb_5)*!paused),1.0);
            hud_keys.draw(lib,4,(lib.screenw/lib.screenscale)+((42.0*0.25)*4.0),22.5,0.35,0.35,0.0);
            glColor4f(fadeValue,fadeValue,fadeValue,1.0);
            hud_pickup_star.draw(lib,0,(lib.screenw/lib.screenscale)+((42.0*0.25)*4.0)-((30.0*0.25)*0.5),
                22.5+((30.0*0.25)*0.5),0.25,0.25,0.0);
            hud_text_large.draw(lib,"1000",(lib.screenw/lib.screenscale)+((42.0*0.25)*4.0)-((10.0*0.25)*2.0),32.5,0.25,0.25,0.0);
        }
        else
        {
            glColor4f(fadeValue,fadeValue,fadeValue,0.5);
            hud_keys.draw(lib,4,(lib.screenw/lib.screenscale)+((42.0*0.25)*4.0),22.5,0.35,0.35,0.0);
            hud_pickup_star.draw(lib,0,(lib.screenw/lib.screenscale)+((42.0*0.25)*4.0)-((30.0*0.25)*0.5),
                22.5+((30.0*0.25)*0.5),0.25,0.25,0.0);
            hud_text_large.draw(lib,"1000",(lib.screenw/lib.screenscale)+((42.0*0.25)*4.0)-((10.0*0.25)*2.0),32.5,0.25,0.25,0.0);
            glColor4f(fadeValue,fadeValue,fadeValue,1.0);
        }

        //Draw Pause Menu
        if(paused)
        {
            if(keyboard_check_pressed(kb_x))
            {
                gameover=true;
            }

            glColor4f(fadeValue,fadeValue,fadeValue,blinkValue);
            hud_text_large.draw(lib,"PRESS X TO RETURN TO MENU",(lib.screenw/lib.screenscale)-((10.0*0.5)*24.0),
                (lib.screenh/lib.screenscale),0.5,0.5,0.0);
        }
    }

    //If In Info
    else if(stage==2)
    {
        //Create Info Menu
        if(!infoCreated)
        {
            //Check Music
            sndTitle.play();

            //View
            viewX=0.0;
            viewY=0.0;

            //Stop Creating
            infoCreated=true;
        }

        //Go Back to Menu
        if(keyboard_check_pressed(kb_z))
        {
            gameover=false;
            paused=true;
            fade=true;
            stageNext=0;
        }

        //Draw Title
        hud_text_large.draw(lib,"INFO",(lib.screenw/lib.screenscale)-((10.0*0.5)*3.0),(20.0*1.0),0.5,0.5,0.0);

        //Draw Instructions
        double infoHudYOff=15.0;
        hud_text_large.draw(lib,"CONTROLS",(lib.screenw/lib.screenscale)-((10.0*0.25)*39.0),
            30.0+infoHudYOff,0.35,0.35,0.0);
        hud_text_large.draw(lib,"Z            SHOOT",(lib.screenw/lib.screenscale)-((10.0*0.25)*39.0),
            40.0+infoHudYOff,0.25,0.25,0.0);
        hud_text_large.draw(lib,"X            REPAIR BARRICADE",(lib.screenw/lib.screenscale)-((10.0*0.25)*39.0),
            50.0+infoHudYOff,0.25,0.25,0.0);
        hud_text_large.draw(lib,"SPACE        PAUSE",(lib.screenw/lib.screenscale)-((10.0*0.25)*39.0),
            60.0+infoHudYOff,0.25,0.25,0.0);

        hud_text_large.draw(lib,"PICKUPS",(lib.screenw/lib.screenscale)-((10.0*0.25)*39.0),
            80.0+infoHudYOff,0.35,0.35,0.0);
        hud_text_large.draw(lib,"  UZI          SHOOTS FASTER",(lib.screenw/lib.screenscale)-((10.0*0.25)*39.0),
            90.0+infoHudYOff,0.25,0.25,0.0);
        hud_text_large.draw(lib,"  SHOTGUN      KILLS GOODLY",(lib.screenw/lib.screenscale)-((10.0*0.25)*39.0),
            100.0+infoHudYOff,0.25,0.25,0.0);
        hud_text_large.draw(lib,"  INSTAKILL    ONE SHOT KILLS",(lib.screenw/lib.screenscale)-((10.0*0.25)*39.0),
            110.0+infoHudYOff,0.25,0.25,0.0);
        hud_text_large.draw(lib,"  NUKE         KILLS ALL ZOMBIES IN WAVE",(lib.screenw/lib.screenscale)-((10.0*0.25)*39.0),
            120.0+infoHudYOff,0.25,0.25,0.0);
        hud_text_large.draw(lib,"  STAR POWER   STAR POWER",(lib.screenw/lib.screenscale)-((10.0*0.25)*39.0),
            130.0+infoHudYOff,0.25,0.25,0.0);

        //Draw Sprites
        hud_pickup_uzi.draw(lib,4,(lib.screenw/lib.screenscale)-((10.0*0.25)*39.0),90.0-0.5+infoHudYOff,0.3,0.3,0.0);
        hud_pickup_shotgun.draw(lib,1,(lib.screenw/lib.screenscale)-((10.0*0.25)*39.0),100.0-0.5+infoHudYOff,0.3,0.3,0.0);
        hud_pickup_instakill.draw(lib,0,(lib.screenw/lib.screenscale)-((10.0*0.25)*39.0),110.0-0.5+infoHudYOff,0.3,0.3,0.0);
        hud_pickup_nuke.draw(lib,0,(lib.screenw/lib.screenscale)-((10.0*0.25)*39.0),120.0-0.5+infoHudYOff,0.3,0.3,0.0);
        hud_pickup_star.draw(lib,0,(lib.screenw/lib.screenscale)-((10.0*0.25)*39.0),130.0-0.5+infoHudYOff,0.3,0.3,0.0);
    }

    //If In Highscore
    else if(stage==3)
    {
        //Check Music
        sndTitle.play();

        //Static Variables
        static int highscoreCursorPosition=0;
        static bool highscoreFinished=false;

        //Create Highscores
        if(!highscoreCreated)
        {
            //View
            viewX=0.0;
            viewY=0.0;

            //Text Cursor Posistion
            highscoreCursorPosition=0;

            //Highscore Finished Variable
            highscoreFinished=false;

            //Insert Highscore
            highscoreNames.insert(highscoreNames.begin()+highscorePosition,"   ");
            highscoreScores.insert(highscoreScores.begin()+highscorePosition,spawnWave);

            //Stop Creating
            highscoreCreated=true;
        }

        //Text Cursor Variables
        const char *scoreKeyboard="QWERTYUIOPASDFGHJKLZXCVBNM";
        double cursorX=-90.5;
        double cursorY=30.0;
        double colHeight;
        double xOff;

        //Set Text Cursor
        if(highscoreCursorPosition>=0&&highscoreCursorPosition<=9)
        {
            colHeight=0.0;
            xOff=0.0;
        }
        else if(highscoreCursorPosition>=10&&highscoreCursorPosition<=18)
        {
            colHeight=20.0;
            xOff=9.5;
        }
        else
        {
            colHeight=40.0;
            xOff=17.5;
        }

        //Move Text Cursor Right
        if(keyboard_check_pressed(kb_right)&&highscorePosition<10)
        {
            if((highscoreCursorPosition>=0&&highscoreCursorPosition<=8)||(highscoreCursorPosition>=10&&highscoreCursorPosition<=17)
                ||(highscoreCursorPosition>=19&&highscoreCursorPosition<=24))
            {
                highscoreCursorPosition++;
                sound_engine->play2D("sounds/snd_beepEnter.wav");
            }
        }

        //Move Text Cursor Left
        if(keyboard_check_pressed(kb_left)&&highscorePosition<10)
        {
            if((highscoreCursorPosition>=1&&highscoreCursorPosition<=9)||(highscoreCursorPosition>=11&&highscoreCursorPosition<=18)
                ||(highscoreCursorPosition>=20&&highscoreCursorPosition<=25))
            {
                highscoreCursorPosition--;
                sound_engine->play2D("sounds/snd_beepEnter.wav");
            }
        }

        //Move Text Cursor Up
        if(keyboard_check_pressed(kb_up)&&highscorePosition<10)
        {

            if(highscoreCursorPosition>=10&&highscoreCursorPosition<=18)
            {
                highscoreCursorPosition-=10;
                sound_engine->play2D("sounds/snd_beepEnter.wav");
            }
            else if(highscoreCursorPosition>=19&&highscoreCursorPosition<=25)
            {
                highscoreCursorPosition-=8;
                sound_engine->play2D("sounds/snd_beepEnter.wav");
            }
        }

        //Move Text Cursor Down
        if(keyboard_check_pressed(kb_down)&&highscorePosition<10)
        {

            if(highscoreCursorPosition==0)
            {
                highscoreCursorPosition+=10;
                sound_engine->play2D("sounds/snd_beepEnter.wav");
            }
            else if(highscoreCursorPosition>=1&&highscoreCursorPosition<=9)
            {
                highscoreCursorPosition+=9;
                sound_engine->play2D("sounds/snd_beepEnter.wav");
            }
            else if(highscoreCursorPosition==10)
            {
                highscoreCursorPosition=19;
                sound_engine->play2D("sounds/snd_beepEnter.wav");
            }
            else if(highscoreCursorPosition>=11&&highscoreCursorPosition<=17)
            {
                highscoreCursorPosition+=8;
                sound_engine->play2D("sounds/snd_beepEnter.wav");
            }
            else if(highscoreCursorPosition==18)
            {
                highscoreCursorPosition=25;
                sound_engine->play2D("sounds/snd_beepEnter.wav");
            }
        }

        //Text Cursor Enter Character
        if(keyboard_check_pressed(kb_z)&&playerName.size()<3&&!highscoreFinished&&highscorePosition<10)
        {
            playerName+=scoreKeyboard[highscoreCursorPosition];
            sound_engine->play2D("sounds/snd_beepUp.wav");
        }

        //Text Cursor Delete Character
        if(keyboard_check_pressed(kb_x)&&playerName.size()>0&&!highscoreFinished&&highscorePosition<10)
        {
            playerName.erase(playerName.begin()+(playerName.size()-1));
            sound_engine->play2D("sounds/snd_beepDown.wav");
        }

        //Text Cursor Submit Name and Score
        if(keyboard_check_pressed(kb_space)&&highscorePosition<10)
        {
            if(playerName.size()>0&&!highscoreFinished&&highscorePosition<10)
            {
                //Check Player Name Size
                while(playerName.size()<3)
                {
                    playerName+=" ";
                }

                //Save Player Name
                highscoreNames[highscorePosition]=playerName;

                //Write Highscores
                ofstream ostr("scores.txt");

                for(int i=0;i<10;i++)
                {
                    ostr<<highscoreNames[i]<<endl;
                    ostr<<highscoreScores[i]<<endl;
                }

                ostr.close();

                //Set Finished Variable
                highscoreFinished=true;
                sound_engine->play2D("sounds/snd_beepSelect.wav");
            }

        }

        //Exit to Menu
        if(keyboard_check_pressed(kb_z))
        {
            if((playerName.size()>0&&highscoreFinished&&highscorePosition<10)||highscorePosition>=10)
            {
                gameover=false;
                paused=true;
                fade=true;
                stageNext=0;
            }
        }

        //Draw Highscores Table
        hud_text_large.draw(lib,"HIGHSCORES",(lib.screenw/lib.screenscale)-45.0,20.0,0.5,0.5,0.0);

        for(unsigned int i=0;i<10;i++)
        {
            ostringstream listingTemp;

            string space=" ";
            string name="";

            int sideOff=0;
            double xOff=-110.0;

            if(i>=5)
            {
                sideOff=5;
                xOff=40.0;
            }

            if(i==9)
            {
                space="";
            }

            if(i==highscorePosition)
            {
                name=playerName;
            }
            else
            {
                name=highscoreNames[i];
            }

            while(name.size()<3)
            {
                name+=" ";
            }

            listingTemp<<i+1<<" "<<space<<name<<"\t"<<highscoreScores[i];

            hud_text_large.draw(lib,listingTemp.str(),(lib.screenw/lib.screenscale)+xOff,50.0+(10.0*(i-sideOff)),0.5,0.5,0.0);
        }

        //Draw Keyboard
        if(highscorePosition<10&&!highscoreFinished)
        {
            double xPos=(lib.screenw/lib.screenscale)-100.0;
            double yPos=(lib.screenh/lib.screenscale)+30.0;

            for(int i=0;i<26;i++)
            {
                double colHeight;
                double xOff;

                if(i>=0&&i<=9)
                {
                    colHeight=0.0;
                    xOff=0.0;
                }
                else if(i>=10&&i<=18)
                {
                    colHeight=20.0;
                    xOff=9.5;
                }
                else
                {
                    colHeight=40.0;
                    xOff=17.5;
                }

                hud_text_large.draw(lib,scoreKeyboard[i],xPos+(20.0*(i-xOff)),yPos+colHeight,0.5,0.5,0.0);
            }
        }

        //Draw Text Cursor
        if(highscorePosition<10&&highscoreCursorPosition>=0&&highscoreCursorPosition<=25&&!highscoreFinished)
        {
            glColor4f(1.0,1.0,1.0,blinkValue);
            lib.draw(tex_hud_text_cursor,(lib.screenw/lib.screenscale)+cursorX+((highscoreCursorPosition-xOff)*20.0),
                (lib.screenh/lib.screenscale)+cursorY+colHeight,14.0,14.0,0.0);
            glColor4f(1.0,1.0,1.0,1.0);
        }
    }

    //If Exit
    else if(stage==4)
    {
        //Delete All Objects
        while(Object::Objects.size()>0)
        {
            delete Object::Objects[Object::Objects.size()-1];
        }

        //Clear Vectors
        Object::Objects.clear();
        Player::Players.clear();
        Zombie::Zombies.clear();
        Barricade::Barricades.clear();
        Effect::Effects.clear();
        Pickup::Pickups.clear();

        //Stop Sound Engine
		sound_engine->drop();

        //End Game
        exit(0);
    }
}
