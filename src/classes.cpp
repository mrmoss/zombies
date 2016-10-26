//Linker for Game.h
#include "classes.h"

//Between Function Definition
bool between(const double b1,const double b2,const double val)
{
    if(val>=b1&&val<=b2)
    {
        return true;
    }

    return false;
}

//Sound C String Constructor
Sound::Sound(ISoundEngine *engine,const char *fileName,const bool loop,ik_f32 volume=1.0):_engine(engine),_fileName(fileName),_isPlaying(false),
    _isPaused(false),_isLooped(loop)
{
    if(volume>1.0)
    {
        volume=1.0;
    }

    if(volume<0.0)
    {
        volume=0.0;
    }

    _volume=volume;

    _irrPointer=_engine->play2D(_fileName.c_str(),_isLooped,true,true);
    _irrPointer->setVolume(_volume);
}

//Sound String Constructor
Sound::Sound(ISoundEngine *engine,const string fileName,const bool loop,ik_f32 volume=1.0):_engine(engine),_fileName(fileName),_isPlaying(false),
    _isPaused(false),_isLooped(loop)

{
    if(volume>1.0)
    {
        volume=1.0;
    }

    if(volume<0.0)
    {
        volume=0.0;
    }

    _volume=volume;

    _irrPointer=_engine->play2D(_fileName.c_str(),_isLooped,true,true);
    _irrPointer->setVolume(_volume);
}

//Sound Destructor
Sound::~Sound()
{
    if(_irrPointer)
    {
        _irrPointer->drop();
        _irrPointer=NULL;
    }
}

//Sound Play Mutator
void Sound::play()
{
    if(_irrPointer)
    {
        if(_isPaused)
        {
            _isPaused=false;
            _irrPointer->setIsPaused(_isPaused);
        }

        if(!_isPlaying||isFinished())
        {
            _isPlaying=true;
            _irrPointer=_engine->play2D(_fileName.c_str(),_isLooped,true,true);
            _irrPointer->setVolume(_volume);
            _irrPointer->setIsPaused(false);
        }
    }
}

//Sound Stop Mutator
void Sound::stop()
{
    if(_irrPointer)
    {
        if(_isPlaying)
        {
            _isPlaying=false;
            _irrPointer->stop();
        }
    }
}

//Sound Pause Mutator
void Sound::pause()
{
    if(_isPlaying&&!_isPaused)
    {
        _isPaused=true;
        _irrPointer->setIsPaused(_isPaused);
    }
}

//Sound Looped Mutator
void Sound::setLooped(const bool loop)
{
    if(_irrPointer)
    {
        _isLooped=loop;
        _irrPointer->setIsLooped(_isLooped);
    }
}

//Sound Is Playing Accessor
bool Sound::isPlaying()
{
    if(_irrPointer)
    {
        if(!_isPlaying||_isPaused||isFinished())
        {
            return false;
        }

        return true;
    }

    return false;
}

//Sound Is Finished Accessor
bool Sound::isFinished()
{
    if(_irrPointer)
    {
        return _irrPointer->isFinished();
    }

    return true;
}

//Sound Irrklang Pointer Accessor
ISound * Sound::getPointer()
{
    return _irrPointer;
}

//Sound Volume Mutator
void Sound::setVolume(ik_f32 volume)
{
    if(_irrPointer)
    {
        if(volume>0.0)
        {
            volume=1.0;
        }

        if(volume<0.0)
        {
            volume=0.0;
        }

        _volume=volume;
        _irrPointer->setVolume(_volume);
    }
}

//Parent Object Static Variables
vector<Object *> Object::Objects;

//Parent Object Constructor
Object::Object(const double x,const double y):_x(x),_y(y),_width(2.0),_height(2.0),_xscale(1.0),_depth(0)
{
    //Add to Objects Vector
    Objects.push_back(this);
}

//Parent Object Destructor
Object::~Object()
{
    bool found=false;

    for(unsigned int i=0;i<Objects.size();i++)
    {
        if(Objects[i]==this)
        {
            Objects.erase(Objects.begin()+i);
            found=true;
            break;
        }
    }

    if(!found)
    {
        throw logic_error("Cannot find Object in Objects vector.");
    }
}

//Parent Object X Accessor
double Object::getX() const
{
    return _x;
}

//Parent Object X Mutator
void Object::setX(const double x)
{
    _x=x;
}

//Parent Object Y Accessor
double Object::getY() const
{
    return _y;
}

//Parent Object Y Mutator
void Object::setY(const double y)
{
    _y=y;
}

//Parent Object xScale Accessor
double Object::getXScale() const
{
    return _xscale;
}

//Parent Object xScale Mutator
void Object::setXScale(const double xscale)
{
    _xscale=xscale;
}

//Parent Object Width Accessor
double Object::getWidth() const
{
    return _width;
}

//Parent Object Width Mutator
void Object::setWidth(const double width)
{
    _width=width;
}

//Parent Object Height Accessor
double Object::getHeight() const
{
    return _height;
}

//Parent Object Height Mutator
void Object::setHeight(const double height)
{
    _height=height;
}

//Parent Object Depth Accessor
int Object::getDepth() const
{
    return _depth;
}

//Parent Object xScale Mutator
void Object::setDepth(const int depth)
{
    _depth=depth;
}

//Parent Object Collision Checker (Single Object)
bool Object::placeMeeting(const double x,const double y,const Object &obj)
{
    if(this!=&obj)
    {
        for(double xi=x-(_width/2.0);xi<=x+(_width/2.0);xi+=1.0)
        {
            for(double yi=y-(_height/2.0);yi<=y+(_height/2.0);yi+=1.0)
            {
                if(between(obj._x-(obj._width/2.0),obj._x+(obj._width/2.0),xi)
                    &&between(obj._y-(obj._height/2.0),obj._y+(obj._height/2.0),yi))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

//Player Object Static Vector
vector<Player *> Player::Players;

//Player Object Static Textures
spritelib_tex Player::tex_marco_legs_idle=0;
spritelib_tex Player::tex_marco_legs_run=0;
spritelib_tex Player::tex_marco_legs_jump=0;
spritelib_tex Player::tex_marco_torso_pistol_idle=0;
spritelib_tex Player::tex_marco_torso_pistol_shoot=0;
spritelib_tex Player::tex_marco_torso_uzi_idle=0;
spritelib_tex Player::tex_marco_torso_uzi_shoot=0;
spritelib_tex Player::tex_marco_torso_shotgun_idle=0;
spritelib_tex Player::tex_marco_torso_shotgun_shoot=0;
spritelib_tex Player::tex_marco_die=0;

//Player Object Constructor
Player::Player(const double x,const double y):Object(x,y),_weaptimer(-100.0),_instakill(false),
    _instakilltimer(-100.0),_starpower(false),_starpowertimer(-100.0),_legs(marco_legs_none),
    _torso(marco_torso_none),_weapon(0),_shootable(true),_shoottimer(-100.0),_hp(100.0),
    _dead(false),_deadtimer(-100.0),_inAir(false),_vspeed(0.0)
{
    //Set Depth
    setDepth(6);

    //Mask Size
    _width=20.0;
    _height=32.0;

    //Fixing Sound
    _sndFix=new Sound(sound_engine,"sounds/snd_fix.wav",false,0.5);

    //Star Power Sound
    _sndStarPower=new Sound(sound_engine,"sounds/snd_star_power.wav",true,0.8);

    //Hurt Sounds
    _hurtSound[0]=new Sound(sound_engine,"sounds/snd_argh01.wav",false,0.4);
    _hurtSound[1]=new Sound(sound_engine,"sounds/snd_argh02.wav",false,0.4);
    _hurtSound[2]=new Sound(sound_engine,"sounds/snd_argh03.wav",false,0.4);
    _hurtSound[3]=new Sound(sound_engine,"sounds/snd_argh04.wav",false,0.4);

    //Sprite Settings
    _spriteWidth=116.0;
    _spriteHeight=52.0;
    _spriteTexture[0]=0;
    _spriteTexture[1]=&tex_marco_legs_idle;
    _spriteTexture[2]=&tex_marco_legs_run;
    _spriteTexture[3]=&tex_marco_torso_pistol_idle;
    _spriteTexture[4]=&tex_marco_torso_pistol_shoot;
    _spriteTexture[5]=&tex_marco_torso_uzi_idle;
    _spriteTexture[6]=&tex_marco_torso_uzi_shoot;
    _spriteTexture[7]=&tex_marco_torso_shotgun_idle;
    _spriteTexture[8]=&tex_marco_torso_shotgun_shoot;
    _spriteTexture[9]=&tex_marco_die;
    _spriteTexture[10]=&tex_marco_legs_jump;
    _spriteNumFrames[0]=1;
    _spriteNumFrames[1]=3;
    _spriteNumFrames[2]=12;
    _spriteNumFrames[3]=6;
    _spriteNumFrames[4]=4;
    _spriteNumFrames[5]=6;
    _spriteNumFrames[6]=4;
    _spriteNumFrames[7]=6;
    _spriteNumFrames[8]=4;
    _spriteNumFrames[9]=6;
    _spriteNumFrames[10]=1;

    //Weapon Settings
    _weaponSprite[0][0]=marco_torso_pistol_idle;
    _weaponSprite[1][0]=marco_torso_pistol_shoot;
    _weaponDamage[0]=34.0;
    _weaponAuto[0]=false;
    _weaponFireRate[0]=20.0;
    _weaponDistance[0]=150.0;
    _weaponSound[0]="sounds/snd_pistol_shoot.wav";
    _weaponSprite[0][1]=marco_torso_uzi_idle;
    _weaponSprite[1][1]=marco_torso_uzi_shoot;
    _weaponDamage[1]=10.0;
    _weaponAuto[1]=true;
    _weaponFireRate[1]=5.0;
    _weaponDistance[1]=150.0;
    _weaponSound[1]="sounds/snd_uzi_shoot.wav";
    _weaponSprite[0][2]=marco_torso_shotgun_idle;
    _weaponSprite[1][2]=marco_torso_shotgun_shoot;
    _weaponDamage[2]=100.0;
    _weaponAuto[2]=false;
    _weaponFireRate[2]=30.0;
    _weaponDistance[2]=150.0;
    _weaponSound[2]="sounds/snd_shotgun_shoot.wav";

    //Pickup Settings
    _pickupCost[0]=200;
    _pickupCost[1]=300;
    _pickupCost[2]=400;
    _pickupCost[3]=800;
    _pickupCost[4]=1000;

    //Sprites
    _legs=marco_legs_idle;
    _spriteLegs=new spritelib_anim(*_spriteTexture[_legs],_spriteWidth,
        _spriteHeight,_spriteNumFrames[_legs],1);

    _torso=_weaponSprite[0][_weapon];
    _spriteTorso=new spritelib_anim(*_spriteTexture[_torso],_spriteWidth,
        _spriteHeight,_spriteNumFrames[_torso],1);

    //Add to Players Vector
    Players.push_back(this);
}

//Player Object Destructor
Player::~Player()
{
    bool found=false;

    for(unsigned int i=0;i<Players.size();i++)
    {
        if(Players[i]==this)
        {
            Players.erase(Players.begin()+i);
            delete _sndFix;
            delete _sndStarPower;
            delete _spriteLegs;
            delete _spriteTorso;
            delete _hurtSound[0];
            delete _hurtSound[1];
            delete _hurtSound[2];
            delete _hurtSound[3];
            found=true;
            break;
        }
    }

    if(!found)
    {
        throw logic_error("Cannot find Player in Players vector.");
    }
}

//Player Object HP Accessor
double Player::getHp() const
{
    return _hp;
}

//Player Object HP Mutator
void Player::setHp(const double hp)
{
    _hp=hp;
}

//Player Object Weapon Mutator
void Player::setWeapon(const int type)
{
    if(type>2||type<0)
    {
        _weapon=0;
    }
    else
    {
        _weapon=type;
    }

    if(_torso!=_weaponSprite[static_cast<int>(!_shootable)][_weapon])
    {
        delete _spriteTorso;
        _torso=_weaponSprite[static_cast<int>(!_shootable)][_weapon];
        _spriteTorso=new spritelib_anim(*_spriteTexture[_torso],_spriteWidth,
            _spriteHeight,_spriteNumFrames[_torso],1);
    }
}

//Player Object Update Function
void Player::update(spritelib &lib)
{
    //If Not Dead
    if(!_dead)
    {
        //Temporary Variables
        double legsAnimSpeed=30.0*lib.dt;
        double torsoAnimSpeed=18.0*lib.dt;
        double moveSpeed=150.0*lib.dt;
        double gravity=500.0*lib.dt;
        double jumpSpeed=250.0;

        //Gravity
        _y+=(_vspeed+=gravity)*lib.dt;

        //Collision with "Ground"
        if(_y<92.0)
        {
            if(_legs!=marco_legs_jump)
            {
                delete _spriteLegs;
                _legs=marco_legs_jump;
                _spriteLegs=new spritelib_anim(*_spriteTexture[_legs],_spriteWidth,
                    _spriteHeight,_spriteNumFrames[_legs],1);
            }

            _inAir=true;
        }
        else
        {
            _vspeed=0.0;
            _y=92.0;
            _inAir=false;
        }

        //Jumping Quick Fix
        if(_y<23.5&&_vspeed<0.0)
        {
            _vspeed=0.0;
        }

        //Jumping
        if(keyboard_check_pressed(kb_up)&&!_inAir)
        {
            _vspeed=-jumpSpeed;
        }

        //Weapon Timer
        if(_weaptimer<=0.0&&_weaptimer>-50.0)
        {
            setWeapon(0);
            _weaptimer=-100.0;
        }
        else if(_weaptimer>-50)
        {
            _weaptimer-=lib.dt;
        }

        //Instakill Timer
        if(_instakilltimer<=0.0&&_instakilltimer>-50.0)
        {
            _instakill=false;
            _instakilltimer=-100.0;
        }
        else if(_instakilltimer>-50.0)
        {
            _instakilltimer-=lib.dt;
        }

        //Star Power Timer
        if(_starpowertimer<=0.0&&_starpowertimer>-50.0)
        {
            _starpower=false;
            _starpowertimer=-100.0;
        }
        else if(_starpowertimer>-50.0)
        {
            _starpowertimer-=lib.dt;
        }

        //Star Power Music
        if(_starpower)
        {
            _sndStarPower->play();
        }
        else
        {
            _sndStarPower->stop();
        }

        //Shoot Timer
        if(_shoottimer<=0.0&&_shoottimer>-50.0)
        {
            _shootable=true;
            _shoottimer=-100.0;
        }
        else if(_shoottimer>-50.0)
        {
            _shoottimer-=lib.dt;
        }

        //If Idle
        if(_legs==marco_legs_idle)
        {
            legsAnimSpeed=10.0*lib.dt;
        }

        //Update Sprites
        if(_legs!=marco_legs_none)
        {
            _spriteLegs->update(legsAnimSpeed);
        }

        if(_torso!=marco_torso_none)
        {
            _spriteTorso->update(torsoAnimSpeed);
        }

        //Move Right
        if(keyboard_check(kb_right)&&_x<768.0)
        {
            //Flip Sprite
            _xscale=1.0;

            //Set Legs Animation
            if(!_inAir)
            {
                if(_legs!=marco_legs_run)
                {
                    delete _spriteLegs;
                    _legs=marco_legs_run;
                    _spriteLegs=new spritelib_anim(*_spriteTexture[_legs],_spriteWidth,
                        _spriteHeight,_spriteNumFrames[_legs],1);
                }
            }

            //Move
            _x+=moveSpeed;
        }

        //Move Left
        if(keyboard_check(kb_left)&&_x>286.0)
        {
            //Flip Sprite
            _xscale=-1.0;

            //Set Legs Animation
            if(!_inAir)
            {
                if(_legs!=marco_legs_run)
                {
                    delete _spriteLegs;
                    _legs=marco_legs_run;
                    _spriteLegs=new spritelib_anim(*_spriteTexture[_legs],_spriteWidth,
                        _spriteHeight,_spriteNumFrames[_legs],1);
                }
            }

            //Move
            _x-=moveSpeed;
        }

        //Switch to Idle Animation If Not Pressing Right or Left or If Pressing Both Right and Left or If Stopped
        if((!keyboard_check(kb_right)&&!keyboard_check(kb_left))||(keyboard_check(kb_right)&&keyboard_check(kb_left))
            ||_x<=286.0||_x>=768.0)
        {
            //Set Legs Animation
            if(!_inAir)
            {
                if(_legs!=marco_legs_idle)
                {
                    delete _spriteLegs;
                    _legs=marco_legs_idle;
                    _spriteLegs=new spritelib_anim(*_spriteTexture[_legs],_spriteWidth,
                        _spriteHeight,_spriteNumFrames[_legs],1);
                }
            }
        }

        //Shooting
        if(((keyboard_check_pressed(kb_z)&&!_weaponAuto[_weapon])||(keyboard_check(kb_z)&&_weaponAuto[_weapon]))&&_shootable)
        {
            //Set Torso Animation
            if(_torso!=_weaponSprite[1][_weapon])
            {
                delete _spriteTorso;
                _torso=_weaponSprite[1][_weapon];
                _spriteTorso=new spritelib_anim(*_spriteTexture[_torso],_spriteWidth,
                    _spriteHeight,_spriteNumFrames[_torso],1);
            }

            //Play Shooting Sound
            ik_f32 volume=1.0;

            if(_weapon!=2)
            {
                volume=0.2;
            }

            Sound shoot(sound_engine,_weaponSound[_weapon].c_str(),false,volume);
            shoot.play();

            //Start Shooting
            _shootable=false;
            _shoottimer=_weaponFireRate[_weapon]/100.0;

            //Do Damage
            if(Zombie::Zombies.size()>0)
            {
                int count=0;

                for(double i=0;i<_weaponDistance[_weapon];i+=5.0)
                {
                    for(unsigned int j=0;j<Zombie::Zombies.size();j++)
                    {
                        if(placeMeeting(_x+(i*_xscale),_y,*Zombie::Zombies[j]))
                        {
                            if(!(Zombie::Zombies[j]->_dead))
                            {
                                if(_instakill)
                                {
                                    Zombie::Zombies[j]->setHp(0.0);
                                }
                                else
                                {
                                    Zombie::Zombies[j]->setHp(Zombie::Zombies[j]->getHp()-_weaponDamage[_weapon]);
                                }

                                Sound sndFleshShot(sound_engine,"sounds/snd_flesh_shot.wav",false,0.4);
                                sndFleshShot.play();
                                Zombie::Zombies[j]->setHurt();

                                for(int l=0;l<20*(1+(rand()%11));l++)
                                {
                                    double direction=static_cast<double>(rand()%360);
                                    double distance=static_cast<double>(rand()%10);
                                    new Effect(_x+((i+(Zombie::Zombies[j]->getWidth()/2.0))*_xscale)+
                                        (cos(direction*(180/3.1415926))*distance),
                                        _y+(-sin(direction*(180/3.1415926))*distance),0);
                                }

                                count++;
                                break;
                            }
                        }
                    }

                    if((count>0&&_weapon!=2)||(count>5&&_weapon==2))
                    {
                        break;
                    }
                }
            }
        }

        //Switch to Idle Animation If Not Shooting
        if(((!_weaponAuto[_weapon])||(_weaponAuto[_weapon]&&!keyboard_check(kb_z)))&&_torso==_weaponSprite[1][_weapon]&&_spriteTorso->getCurFrame()>=_spriteTorso->getNumFrames()-1)
        {
            //Set Torso Animation
            if(_torso!=_weaponSprite[0][_weapon])
            {
                delete _spriteTorso;
                _torso=_weaponSprite[0][_weapon];
                _spriteTorso=new spritelib_anim(*_spriteTexture[_torso],_spriteWidth,
                    _spriteHeight,_spriteNumFrames[_torso],1);
            }
        }

        //Fixing Code
        if(keyboard_check(kb_x))
        {
            double range=5.0;
            double fixRate=10.0*lib.dt;;

            bool fixing=false;

            for(unsigned int i=0;i<Barricade::Barricades.size();i++)
            {
                if(!_inAir&&(placeMeeting(_x+(_width/2.0)+range,_y,*Barricade::Barricades[i])
                    ||placeMeeting(_x-range,_y,*Barricade::Barricades[i]))&&Barricade::Barricades[i]->getHp()<100.0)
                {
                    Barricade::Barricades[i]->setHp(Barricade::Barricades[i]->getHp()+fixRate);

                    //Effect
                    if(Barricade::Barricades[i]->getHp()<100.0&&rand()%2)
                    {
                        double direction=static_cast<double>(rand()%360);
                        double distance=static_cast<double>(rand()%5);
                        new Effect(_x+((i+(Barricade::Barricades[i]->getWidth()/2.0))*_xscale)+
                            (cos(direction*(180/3.1415926))*distance),
                            _y+(-sin(direction*(180/3.1415926))*distance),1);
                    }

                    fixing=true;
                    break;
                }
            }

            //Play Sound
            if(!fixing)
            {
                _sndFix->stop();
            }
            else
            {
                _sndFix->play();
            }
        }
        else
        {
            _sndFix->stop();
        }

        //Buy Uzi Pickup
        if(keyboard_check_pressed(kb_1)&&credits>=_pickupCost[0])
        {
            new Pickup(276.0+static_cast<double>(rand()%500),0.0,0);
            credits-=_pickupCost[0];
            sound_engine->play2D("sounds/snd_money.wav",false);
        }

        //Buy Shotgun Pickup
        if(keyboard_check_pressed(kb_2)&&credits>=_pickupCost[1])
        {
            new Pickup(276.0+static_cast<double>(rand()%500),0.0,1);
            credits-=_pickupCost[1];
            sound_engine->play2D("sounds/snd_money.wav",false);
        }

        //Buy Instakill Pickup
        if(keyboard_check_pressed(kb_3)&&credits>=_pickupCost[2])
        {
            new Pickup(276.0+static_cast<double>(rand()%500),0.0,2);
            credits-=_pickupCost[2];
            sound_engine->play2D("sounds/snd_money.wav",false);
        }

        //Buy Nuke Pickup
        if(keyboard_check_pressed(kb_4)&&credits>=_pickupCost[3])
        {
            new Pickup(276.0+static_cast<double>(rand()%500),0.0,3);
            credits-=_pickupCost[3];
            sound_engine->play2D("sounds/snd_money.wav",false);
        }

        //Buy Star Power Pickup
        if(keyboard_check_pressed(kb_5)&&credits>=_pickupCost[4])
        {
            new Pickup(276.0+static_cast<double>(rand()%500),0.0,4);
            credits-=_pickupCost[4];
            sound_engine->play2D("sounds/snd_money.wav",false);
        }

        //Views
        viewX=_x-(lib.screenw/lib.screenscale);

        if(!_inAir)
        {
            viewY=_y-(lib.screenh/lib.screenscale);
        }

        //Health Stuff
        if(_hp<100.0)
        {
            bloodedDecay=((100.0-_hp)/10.0)*lib.dt;
            _hp+=1.0*lib.dt;

            //If Hurt
            if(!blooded&&bloodedValue<=0.0)
            {
                blooded=true;
            }

            //If Dead
            if(_hp<=0.0)
            {
                _dead=true;
                _deadtimer=5.0;

                if(_legs!=marco_legs_none)
                {
                    delete _spriteLegs;
                    _legs=marco_legs_none;
                    _spriteLegs=new spritelib_anim(*_spriteTexture[_legs],_spriteWidth,
                        _spriteHeight,_spriteNumFrames[_legs],1);
                }

                if(_torso!=marco_dead)
                {
                    delete _spriteTorso;
                    _torso=marco_dead;
                    _spriteTorso=new spritelib_anim(*_spriteTexture[_torso],_spriteWidth,
                        _spriteHeight,_spriteNumFrames[_torso],1);
                }
                _hurtSound[0]->stop();
                _hurtSound[1]->stop();
                _hurtSound[2]->stop();
                _hurtSound[3]->stop();

                Sound sndScream(sound_engine,"sounds/snd_scream.wav",false);
                sndScream.play();
            }
        }
        else
        {
            blooded=false;
            bloodedValue=0.0;

            if(_hp>100.0)
            {
                _hp=100.0;
            }
        }
    }
    else
    {
        //Blooded
        blooded=true;

        //Temporary Variables
        double animSpeed=18.0*lib.dt;
        _spriteTorso->update(animSpeed);

        //Dead Timer
        if(_deadtimer<=0.0&&_deadtimer>-50.0)
        {
            gameover=true;
        }
        else if(_deadtimer>-50)
        {
            _deadtimer-=lib.dt;
        }
    }
}

//Player Object Draw Function
void Player::draw(spritelib &lib)
{
    //Temporary Variables
    double yOff=1.5;

    //If Idle Animation Draw Torso Lower
    if(_legs==marco_legs_idle)
    {
        yOff+=3.0;
    }

    //Star Power Effect
    if(_starpower)
    {
        glColor3f(fadeValue-static_cast<double>(rand()%10)/10.0,fadeValue-static_cast<double>(rand()%10)/10.0,
            fadeValue-static_cast<double>(rand()%10)/10.0);
    }
    else
    {
        //Fader Code
        glColor3f(fadeValue,fadeValue-bloodedValue,fadeValue-bloodedValue);
    }

    //Draw Legs
    if(_legs!=marco_legs_none)
    {
        _spriteLegs->draw(lib,_spriteLegs->getCurFrame(),_x-viewX,_y-viewY,_xscale,1.0,0.0);
    }

    //Draw Torso
    if(_torso!=marco_torso_none)
    {
        _spriteTorso->draw(lib,_spriteTorso->getCurFrame(),_x-viewX,_y-viewY+yOff,_xscale,1.0,0.0);
    }

    //Undo Lighting Changes
    glColor3f(1.0,1.0,1.0);
}

//Player Object Get Textures Function
void Player::getTextures(spritelib &lib)
{
    //Load All Textures From Disk
    tex_marco_legs_idle=lib.read_tex("sprites/marco/marco_legs_idle.png");
    tex_marco_legs_run=lib.read_tex("sprites/marco/marco_legs_run.png");
    tex_marco_legs_jump=lib.read_tex("sprites/marco/marco_legs_jump.png");
    tex_marco_torso_pistol_idle=lib.read_tex("sprites/marco/marco_torso_pistol_idle.png");
    tex_marco_torso_pistol_shoot=lib.read_tex("sprites/marco/marco_torso_pistol_shoot.png");
    tex_marco_torso_uzi_idle=lib.read_tex("sprites/marco/marco_torso_uzi_idle.png");
    tex_marco_torso_uzi_shoot=lib.read_tex("sprites/marco/marco_torso_uzi_shoot.png");
    tex_marco_torso_shotgun_idle=lib.read_tex("sprites/marco/marco_torso_shotgun_idle.png");
    tex_marco_torso_shotgun_shoot=lib.read_tex("sprites/marco/marco_torso_shotgun_shoot.png");
    tex_marco_die=lib.read_tex("sprites/marco/marco_die.png");
}

//Player Object Hurt Sound Mutator
void Player::setHurt()
{
    if(!_dead&&!_hurtSound[0]->isPlaying()&&!_hurtSound[1]->isPlaying()&&!_hurtSound[2]->isPlaying()&&!_hurtSound[3]->isPlaying())
    {
        _hurtSound[rand()%4]->play();
    }
}

//Zombie Object Static Vector
vector<Zombie *> Zombie::Zombies;

//Zombie Object Static Textures
spritelib_tex Zombie::tex_zombie_rebel_move=0;
spritelib_tex Zombie::tex_zombie_rebel_attack=0;
spritelib_tex Zombie::tex_zombie_rebel_die=0;

//Zombie Object Constructor
Zombie::Zombie(const double x,const double y):Object(x,y),_dead(false),_anim(0),_hp(100.0),
    _moantimer(0.5+static_cast<double>(rand()%10))
{
    //Sounds
    _sndBarricadeHit=new Sound(sound_engine,"sounds/snd_barricade_hit.wav",false,0.2);
    _sndBarricadeHit->stop();
    _sndPlayerHit=new Sound(sound_engine,"sounds/snd_flesh_shot.wav",false,0.2);
    _sndPlayerHit->stop();

    //Moan Settings
    _sndMoan[0]=new Sound(sound_engine,"sounds/snd_zombie_groan01.wav",false,0.8);
    _sndMoan[1]=new Sound(sound_engine,"sounds/snd_zombie_groan02.wav",false,0.8);
    _sndMoan[2]=new Sound(sound_engine,"sounds/snd_zombie_groan03.wav",false,0.8);
    _sndMoan[3]=new Sound(sound_engine,"sounds/snd_zombie_groan04.wav",false,0.8);
    _sndMoan[4]=new Sound(sound_engine,"sounds/snd_zombie_groan05.wav",false,0.8);
    _sndMoan[5]=new Sound(sound_engine,"sounds/snd_zombie_groan06.wav",false,0.8);

    //Set Depth
    setDepth(5+(rand()%3));

    //Mask Size
    _width=10.0;
    _height=40.0;

    //Sprite Settings
    _spriteWidth=128.0;
    _spriteHeight=116.0;
    _spriteNumFrames[0]=16;
    _spriteNumFrames[1]=8;
    _spriteNumFrames[2]=15;
    _spriteTex[0]=&tex_zombie_rebel_move;
    _spriteTex[1]=&tex_zombie_rebel_attack;
    _spriteTex[2]=&tex_zombie_rebel_die;

    //Create Sprite
    _sprite=new spritelib_anim(*_spriteTex[_anim],_spriteWidth,_spriteHeight,_spriteNumFrames[_anim],1);

    //Add to Zombies Vector
    Zombies.push_back(this);

    //Creation Collision Check
    while(placeMeeting(_x,_y,Zombie::Zombies))
    {
        _x-=0.1*_xscale;
    }
    while(placeMeeting(_x+1.0,_y,Zombie::Zombies))
    {
        _x-=0.1*_xscale;
    }
    while(placeMeeting(_x-1.0,_y,Zombie::Zombies))
    {
        _x+=0.1*_xscale;
    }
}

//Zombie Object Destructor
Zombie::~Zombie()
{
    bool found=false;

    for(unsigned int i=0;i<Zombies.size();i++)
    {
        if(Zombies[i]==this)
        {
            Zombies.erase(Zombies.begin()+i);
            delete _sndBarricadeHit;
            delete _sndPlayerHit;

            for(int j=0;j<6;j++)
            {
                delete _sndMoan[j];
            }

            found=true;
            break;
        }
    }

    if(!found)
    {
        throw logic_error("Cannot find Zombie in Zombies vector.");
    }
}

//Zombie Object HP Accessor
double Zombie::getHp() const
{
    return _hp;
}

//Zombie Object HP Mutator
void Zombie::setHp(const double hp)
{
    _hp=hp;
}

//Zombie Object Update Function
void Zombie::update(spritelib &lib)
{
    //Temporary Variables
    double animSpeed=15.0*lib.dt;
    double moveSpeed=28.0*lib.dt;
    double damageRate=10.0*lib.dt;

    //Update Sprite
    _sprite->update(animSpeed);

    //Set Y
    _y=81.0+(_height/2.0);

    //If Alive
    if(!_dead)
    {
        //Moan Timer
        if(_moantimer<=0.0)
        {
            _moantimer=0.5+static_cast<double>(rand()%5);

            if(!_sndMoan[0]->isPlaying()&&!_sndMoan[1]->isPlaying()&&!_sndMoan[2]->isPlaying()&&
                !_sndMoan[3]->isPlaying()&&!_sndMoan[4]->isPlaying()&&!_sndMoan[5]->isPlaying())
            {
                _sndMoan[1+rand()%5]->play();
            }
        }
        else if(_moantimer>0.0)
        {
            _moantimer-=lib.dt;
        }

        //Get Direction
        if(Player::Players.size()>0)
        {
            if(Player::Players[0]->getX()>_x)
            {
                _xscale=1.0;
            }
            else
            {
                _xscale=-1.0;
            }
        }

        //Collision Checking
        bool hit=false;

        //Collide with Barricades and Do Damage
        for(unsigned int i=0;i<Barricade::Barricades.size();i++)
        {
            if(placeMeeting(_x+(moveSpeed*_xscale),_y,*(Barricade::Barricades[i]))&&
                Barricade::Barricades[i]->getHp()>0.0)
            {
                hit=true;
                Barricade::Barricades[i]->setHp(Barricade::Barricades[i]->getHp()-damageRate);

                //Effect
                if(rand()%2)
                {
                    double direction=static_cast<double>(rand()%360);
                    double distance=static_cast<double>(rand()%5);
                    new Effect(_x+((i+(Barricade::Barricades[i]->getWidth()/2.0))*_xscale)+
                        (cos(direction*(180/3.1415926))*distance),
                        _y+(-sin(direction*(180/3.1415926))*distance),1);
                }

                break;
            }
        }

        //Collision Checking
        bool hit2=false;

        //Collide with Players and Do Damage
        for(unsigned int i=0;i<Player::Players.size();i++)
        {
            if(placeMeeting(_x+(moveSpeed*_xscale),_y,*(Player::Players[i])))
            {
                hit2=true;

                if(Player::Players[i]->_starpower)
                {
                    _hp=0.0;
                }
                else
                {
                    Player::Players[i]->setHp(Player::Players[i]->getHp()-damageRate);
                    Player::Players[i]->setHurt();

                    double direction=static_cast<double>(rand()%360);
                    double distance=static_cast<double>(rand()%10);
                    new Effect(_x+((i+(Player::Players[i]->getWidth()/2.0))*_xscale)+
                        (cos(direction*(180/3.1415926))*distance),
                        _y+(-sin(direction*(180/3.1415926))*distance),0);
                }

                break;
            }
        }

        //Move
        if(!hit&&!hit2)
        {
            //Check For Other Zombies
            bool hit3=false;

            for(unsigned int j=0;j<Zombie::Zombies.size();j++)
            {
                if(Zombie::Zombies[j]!=this&&placeMeeting(_x+(moveSpeed*_xscale),_y,*(Zombie::Zombies[j]))
                   &&!Zombie::Zombies[j]->_dead&&Zombie::Zombies[j]->getDepth()==_depth)
                {
                    hit3=true;
                    break;
                }
            }

            //If No Zombies and Walking Animation Move
            if(!hit3&&_anim==0)
            {
                _x+=moveSpeed*_xscale;
            }

            //Set Animation
            if((_anim==1&&_sprite->getCurFrame()>=_sprite->getNumFrames()-1)||_anim==0)
            {
                setSprite(0);
            }
        }
        else
        {
            //Else Set to Attack
            setSprite(1);
            _anim=1;

            //Make Attack Sound
            if(_sprite->getCurFrame()==3&&!hit2)
            {
                _sndBarricadeHit->play();
            }
            else if(_sprite->getCurFrame()==3)
            {
                _sndPlayerHit->play();
            }
        }

        //If Dead
        if(_hp<=0.0)
        {
            _dead=true;
            setSprite(2);
            credits+=max(1,Barricade::_numAlive*5);
            Sound sndDead(sound_engine,"sounds/snd_zombie_die.wav",false,0.8);
            sndDead.play();
        }
    }

    //Destroy After Death Animation
    if(_dead&&_anim==2&&_sprite->getCurFrame()==_sprite->getNumFrames()-1)
    {
        delete this;
    }
}

//Zombie Object Draw Function
void Zombie::draw(spritelib &lib)
{
    //Fader Code
    glColor3f(fadeValue,fadeValue-bloodedValue,fadeValue-bloodedValue);

    //Draw Sprite
    _sprite->draw(lib,_sprite->getCurFrame(),_x-viewX,_y-viewY,_xscale,1.0,0.0);

    //Undo Lighting Changes
    glColor3f(1.0,1.0,1.0);
}

//Zombie Object Sprite Mutator
void Zombie::setSprite(const int anim)
{
    if(_anim!=anim)
    {
        _anim=anim;

        if(_sprite!=0)
        {
            delete _sprite;
        }

        _sprite=new spritelib_anim(*_spriteTex[_anim],_spriteWidth,_spriteHeight,_spriteNumFrames[_anim],1);
    }
}

//Zombie Object Hurt Mutator
void Zombie::setHurt()
{
    for(int i=1;i<6;i++)
    {
        _sndMoan[i]->stop();
    }

    if(!_sndMoan[0]->isPlaying())
    {
        _sndMoan[0]->play();
    }
}

//Zombie Object Get Textures Function
void Zombie::getTextures(spritelib &lib)
{
    //Load All Textures From Disk
    tex_zombie_rebel_move=lib.read_tex("sprites/zombies/zombie_rebel_move.png");
    tex_zombie_rebel_attack=lib.read_tex("sprites/zombies/zombie_rebel_attack.png");
    tex_zombie_rebel_die=lib.read_tex("sprites/zombies/zombie_rebel_die.png");
}

//Barricade Object Static Vector
vector<Barricade *> Barricade::Barricades;

//Barricade Object Static Alive Variables
int Barricade::_numAlive;

//Barricade Object Static Textures
spritelib_tex Barricade::tex_barricade=0;

//Barricade Object Constructor
Barricade::Barricade(const double x,const double y):Object(x,y),_hp(100.0),_dead(false)
{
    //Set Depth
    setDepth(4);

    //Mask Size
    _width=38.0;
    _height=22.0;

    //Create Sprite
    _sprite=new spritelib_anim(tex_barricade,54.0,34.0,4,1);
    _sprite->setCurFrame(3);

    //Add to Barricades Vector
    Barricades.push_back(this);

    //Increment Number of Barricades Alive
    _numAlive++;
}

//Barricade Object Destructor
Barricade::~Barricade()
{
    bool found=false;

    for(unsigned int i=0;i<Barricades.size();i++)
    {
        if(Barricades[i]==this)
        {
            Barricades.erase(Barricades.begin()+i);
            delete _sprite;
            found=true;
            break;
        }
    }

    if(!found)
    {
        throw logic_error("Cannot find Barricade in Barricades vector.");
    }
}

//Barricade Object HP Accessor
double Barricade::getHp() const
{
    return _hp;
}

//Barricade Object HP Mutator
void Barricade::setHp(const double hp)
{
    _hp=hp;
}

//Barricade Object Update Function
void Barricade::update(spritelib &lib)
{
    //HP Constraints
    if(_hp<=0.0)
    {
        _hp=0.0;
    }
    if(_hp>100.0)
    {
        _hp=100.0;
    }

    //Destruction
    _sprite->setCurFrame(static_cast<int>(_hp/25.0));

    //Decrement Number of Barricades Alive
    if(_hp<=0.0&&!_dead)
    {
        _numAlive--;
        _dead=true;
    }

    //If Dead
    if(_dead&&_hp>0.0)
    {
        _numAlive++;
        _dead=false;
    }
}

//Barricade Object Draw Function
void Barricade::draw(spritelib &lib)
{
    //Fader Code
    glColor3f(fadeValue,fadeValue-bloodedValue,fadeValue-bloodedValue);

    //Draw Barricade
    _sprite->draw(lib,_sprite->getCurFrame(),_x-viewX,_y-viewY,_xscale,1.0,0.0);

    //Undo Lighting Changes
    glColor3f(1.0,1.0,1.0);
}

//Barricade Object Sprite Accessor
spritelib_anim * Barricade::getSprite()
{
    return _sprite;
}

//Barricade Object Get Textures Function
void Barricade::getTextures(spritelib &lib)
{
    //Load All Textures From Disk
    tex_barricade=lib.read_tex("sprites/obstacle/barricade.png");
}

//Effect Object Static Vector
vector<Effect *> Effect::Effects;

//Effect Object Static Textures
spritelib_tex Effect::tex_blood_effect=0;
spritelib_tex Effect::tex_fix_effect=0;

//Effect Object Constructor
Effect::Effect(const double x,const double y,const int type):Object(x,y),_type(type),_lifetimer(-100.0),
    _direction(static_cast<double>(rand()%360)),_speed(static_cast<double>(100+(rand()%10))),
    _scale(2.0/static_cast<double>(rand()&11))
{
    //Set Depth
    setDepth(10);

    //Add to Effects Vector
    Effects.push_back(this);
}

//Effect Object Destructor
Effect::~Effect()
{
    bool found=false;

    for(unsigned int i=0;i<Effects.size();i++)
    {
        if(Effects[i]==this)
        {
            Effects.erase(Effects.begin()+i);
            found=true;
            break;
        }
    }

    if(!found)
    {
        throw logic_error("Cannot find Effect in Effects vector.");
    }
}

//Effect Object Draw Function
void Effect::update(spritelib &lib)
{
    //Move
    _x+=cos(_direction/(180.0/M_PI))*(_speed*lib.dt);
    _y-=sin(_direction/(180.0/M_PI))*(_speed*lib.dt);

    _y+=20.0*lib.dt;

    //Rotate
    _direction+=static_cast<double>(25+(rand()%30))*lib.dt;

    //Scale
    if(_scale>0.0)
    {
        _scale-=10.0*lib.dt;
    }
    else if(_scale<0.0)
    {
        _scale=0.0;
    }

    //Alive Timer
    if(_lifetimer<=-100.0)
    {
        _lifetimer=2.0;
    }
    else if(_lifetimer>0.0)
    {
        _lifetimer-=lib.dt;
    }

    //Delete if Alive Timer Less than 0
    if(_lifetimer<=0.0&&_lifetimer>-50.0)
    {
        delete this;
    }
}

//Effect Object Draw Function
void Effect::draw(spritelib &lib)
{
    //Fader Code
    glColor3f(fadeValue,fadeValue-bloodedValue,fadeValue-bloodedValue);

    //Draw Effect
    if(_type==0)
    {
        lib.draw(tex_blood_effect,_x-viewX,_y-viewY,16.0*_scale,14.0*_scale,_direction);
    }
    else
    {
        lib.draw(tex_fix_effect,_x-viewX,_y-viewY,16.0*_scale,14.0*_scale,_direction);
    }

    //Undo Lighting Changes
    glColor3f(1.0,1.0,1.0);
}

//Effect Object Get Textures Function
void Effect::getTextures(spritelib &lib)
{
    //Load All Textures From Disk
    tex_blood_effect=lib.read_tex("sprites/effects/blood_effect.png");
    tex_fix_effect=lib.read_tex("sprites/effects/fix_effect.png");
}

//Pickup Object Static Vector
vector<Pickup*> Pickup::Pickups;

//Pickup Object Static Textures
spritelib_tex Pickup::tex_pickup_uzi=0;
spritelib_tex Pickup::tex_pickup_shotgun=0;
spritelib_tex Pickup::tex_pickup_instakill=0;
spritelib_tex Pickup::tex_pickup_nuke=0;
spritelib_tex Pickup::tex_pickup_star=0;

//Pickup Object Constructor
Pickup::Pickup(const double x,const double y,const int type):Object(x,y),_type(type),_dead(false),_vspeed(0.0)
{
    //Set Depth
    setDepth(7);

    //Mask Size
    _width=20.0;
    _height=20.0;

    //Type Bounds
    if(_type<0||_type>4)
    {
        _type=0;
    }

    //Sprite Settings
    _spriteTex[0]=&tex_pickup_uzi;
    _spriteTex[1]=&tex_pickup_shotgun;
    _spriteTex[2]=&tex_pickup_instakill;
    _spriteTex[3]=&tex_pickup_nuke;
    _spriteTex[4]=&tex_pickup_star;
    _spriteNumFrames[0]=6;
    _spriteNumFrames[1]=6;
    _spriteNumFrames[2]=5;
    _spriteNumFrames[3]=1;
    _spriteNumFrames[4]=4;
    _yOff[0]=0.0;
    _yOff[1]=0.0;
    _yOff[2]=1.0;
    _yOff[3]=2.0;
    _yOff[4]=0.0;

    //Create Sprite
    _sprite=new spritelib_anim(*_spriteTex[_type],20.0,20.0,_spriteNumFrames[_type],1);

    //Add to Pickups Vector
    Pickups.push_back(this);
}

//Pickup Object Destructor
Pickup::~Pickup()
{
    bool found=false;

    for(unsigned int i=0;i<Pickups.size();i++)
    {
        if(Pickups[i]==this)
        {
            Pickups.erase(Pickups.begin()+i);
            delete _sprite;
            found=true;
            break;
        }
    }

    if(!found)
    {
        throw logic_error("Cannot find Pickup in Pickups vector.");
    }
}

//Pickup Object Update Function
void Pickup::update(spritelib &lib)
{
    //Temporary Variables
    double animSpeed=15.0*lib.dt;
    double gravity=500.0*lib.dt;

    //Gravity
    _y+=(_vspeed+=gravity)*lib.dt;

    //Update Sprite
    _sprite->update(animSpeed);

    //Drop to Ground
    if(_y>=102.0+(_height/2.0))
    {
        _y=102.0+(_height/2.0);
    }

    //Pickup Code
    for(unsigned int i=0;i<Player::Players.size();i++)
    {
        double goodyTime=30.0;

        if(placeMeeting(_x,_y-(_width/2.0),*Player::Players[i]))
        {
            Sound sndPickup(sound_engine,"sounds/snd_pickup.wav",false,0.3);

            if(_type==0)
            {
                Player::Players[i]->setWeapon(1);
                Player::Players[i]->_weaptimer=goodyTime;
                sndPickup.play();
            }
            else if(_type==1)
            {
                Player::Players[i]->setWeapon(2);
                Player::Players[i]->_weaptimer=goodyTime;
                sndPickup.play();
            }
            else if(_type==2)
            {
                Sound sndInstakill(sound_engine,"sounds/snd_pickup_instakill.wav",false,0.8);
                Player::Players[i]->_instakill=true;
                Player::Players[i]->_instakilltimer=goodyTime;
                sndPickup.play();
                sndInstakill.play();
            }
            else if(_type==3)
            {
                Sound sndExplode01(sound_engine,"sounds/snd_explode01.wav",false,0.8);
                Sound sndExplode02(sound_engine,"sounds/snd_explode02.wav",false,0.8);
                Sound sndExplode03(sound_engine,"sounds/snd_explode03.wav",false,0.8);
                Sound sndFleshShot(sound_engine,"sounds/snd_flesh_shot.wav",false,0.4);
                Sound sndNuke(sound_engine,"sounds/snd_pickup_nuke.wav",false,0.8);

                sndPickup.play();

                if(Zombie::Zombies.size()>0)
                {
                    spawnHorde=0;

                    for(unsigned int j=0;j<Zombie::Zombies.size();j++)
                    {
                        if(Zombie::Zombies[j]->getHp()>0.0)
                        {
                           switch(rand()%3)
                            {
                                case 0:
                                    sndExplode01.play();
                                    break;
                                case 1:
                                    sndExplode02.play();
                                    break;
                                case 2:
                                    sndExplode03.play();
                                    break;
                            }

                            sndFleshShot.play();
                            Zombie::Zombies[j]->setHp(0.0);
                        }
                    }
                }

                sndNuke.play();
            }
            else if(_type==4)
            {
                sound_engine->play2D("sounds/snd_powerup.wav",false);
                Player::Players[i]->_starpower=true;
                Player::Players[i]->_starpowertimer=goodyTime/2.0;
            }

            _dead=true;
            break;
        }
    }

    //Dead Code
    if(_dead)
    {
        delete this;
    }
}

//Pickup Object Update Function
void Pickup::draw(spritelib &lib)
{
    //Fader Code
    glColor3f(fadeValue-bloodedValue,fadeValue-bloodedValue,fadeValue-bloodedValue);

    //Draw Sprite
    _sprite->draw(lib,_sprite->getCurFrame(),_x-viewX,(_y-_yOff[_type])-viewY,_xscale,1.0,0.0);

    //Undo Lighting Changes
    glColor3f(1.0,1.0,1.0);
}

//Pickup Object Get Textures Function
void Pickup::getTextures(spritelib &lib)
{
    //Load All Textures From Disk
    tex_pickup_uzi=lib.read_tex("sprites/pickups/pickup_uzi.png");
    tex_pickup_shotgun=lib.read_tex("sprites/pickups/pickup_shotgun.png");
    tex_pickup_instakill=lib.read_tex("sprites/pickups/pickup_instakill.png");
    tex_pickup_nuke=lib.read_tex("sprites/pickups/pickup_nuke.png");
    tex_pickup_star=lib.read_tex("sprites/pickups/pickup_star.png");
}
