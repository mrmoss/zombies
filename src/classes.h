#ifndef ZOMBIE_CLASSES_H
#define ZOMBIE_CLASSES_H

//Spritelib Headers
#include "spritelib/spritelib.h"
#include "spritelib/spritelib_anim.h"

//Vector Header
#include <vector>
    using std::vector;

//General Utilities Header
#include <cstdlib>
    using std::srand;
    using std::rand;

//Exceptions Header
#include <stdexcept>
    using std::runtime_error;
    using std::logic_error;

//Math Header
#include <cmath>
    using std::min;
    using std::max;
    using std::cos;
    using std::sin;

//TESTING Header
//#include <iostream>
    //using std::cout;
    //using std::endl;

//String Header
#include <string>
    using std::string;

//Sound Engine
#include <irrKlang/irrKlang.h>
#include <irrKlang/ik_ISound.h>
using irrklang::ISoundEngine;
using irrklang::createIrrKlangDevice;
using irrklang::ISound;
using irrklang::ik_f32;

//Externals
extern const int MAXDEPTH;
extern double viewX;
extern double viewY;
extern int credits;
extern bool gameover;
extern double fadeValue;
extern bool fade;
extern bool lightingToggle;
extern bool blooded;
extern double bloodedValue;
extern double bloodedDecay;
extern int spawnHorde;
extern ISoundEngine* sound_engine;

//Between Function Declaration
bool between(const double,const double,const double);

//Sound Class
class Sound
{
    public:
        Sound(ISoundEngine *,const char *,const bool,ik_f32);
        Sound(ISoundEngine *,const string,const bool,ik_f32);
        ~Sound();

        void play();
        void stop();
        void pause();
        void setLooped(const bool);
        bool isPlaying();
        bool isFinished();
        ISound * getPointer();
        void setVolume(ik_f32);

    private:
        Sound(const Sound &);

        ISoundEngine *_engine;
        string _fileName;
        bool _isPlaying;
        bool _isPaused;
        bool _isLooped;
        ISound *_irrPointer;
        ik_f32 _volume;
};

//Parent Object Definition
class Object
{
    public:
        static vector<Object *> Objects;
        Object(const double,const double);
        virtual ~Object();

        double getX() const;
        void setX(const double);
        double getY() const;
        void setY(const double);
        double getWidth() const;
        void setWidth(const double);
        double getHeight() const;
        void setHeight(const double);
        double getXScale() const;
        void setXScale(const double);
        int getDepth() const;
        void setDepth(const int);

        bool placeMeeting(const double,const double,const Object &);

        //Parent Object Collision Checker (Whole Vector of Objects)
        template <typename T>
        bool placeMeeting(const double x,const double y,const vector<T> &vect)
        {
            for(unsigned int i=0;i<vect.size();i++)
            {
                if(placeMeeting(x,y,*vect[i]))
                {
                    return true;
                }
            }

            return false;
        }

        virtual void update(spritelib &)=0;
        virtual void draw(spritelib &)=0;


    protected:
        double _x;
        double _y;
        double _width;
        double _height;
        double _xscale;
        int _depth;

    private:
        Object(const Object &);
};

//Player Object Definition
class Player:public Object
{
    public:
        static vector<Player *> Players;
        Player(const double,const double);
        ~Player();

        double getHp() const;
        void setHp(const double);

        void setWeapon(const int);

        void update(spritelib &);
        void draw(spritelib &);

        static void getTextures(spritelib &);

        double _weaptimer;

        bool _instakill;
        double _instakilltimer;

        bool _starpower;
        double _starpowertimer;

        void setHurt();

    private:
        Player(const Player &);

        Sound *_sndFix;
        Sound *_sndStarPower;
        Sound *_hurtSound[4];

        enum legsAnim
        {
            marco_legs_none,
            marco_legs_idle,
            marco_legs_run,
            marco_legs_jump=10
        };

        enum torsoAnim
        {
            marco_torso_none,
            marco_torso_pistol_idle=3,
            marco_torso_pistol_shoot,
            marco_torso_uzi_idle,
            marco_torso_uzi_shoot,
            marco_torso_shotgun_idle,
            marco_torso_shotgun_shoot,
            marco_dead
        };

        legsAnim _legs;
        torsoAnim _torso;

        double _spriteWidth;
        double _spriteHeight;

        spritelib_tex *_spriteTexture[11];
        int _spriteNumFrames[11];

        static spritelib_tex tex_marco_legs_idle;
        static spritelib_tex tex_marco_legs_run;
        static spritelib_tex tex_marco_legs_jump;
        static spritelib_tex tex_marco_torso_pistol_idle;
        static spritelib_tex tex_marco_torso_pistol_shoot;
        static spritelib_tex tex_marco_torso_uzi_idle;
        static spritelib_tex tex_marco_torso_uzi_shoot;
        static spritelib_tex tex_marco_torso_shotgun_idle;
        static spritelib_tex tex_marco_torso_shotgun_shoot;
        static spritelib_tex tex_marco_die;

        spritelib_anim *_spriteLegs;
        spritelib_anim *_spriteTorso;

        int _weapon;
        torsoAnim _weaponSprite[2][3];
        double _weaponDamage[3];
        bool _weaponAuto[3];
        double _weaponFireRate[3];
        double _weaponDistance[3];
        string _weaponSound[3];

        bool _shootable;
        double _shoottimer;

        double _hp;
        bool _dead;
        double _deadtimer;

        int _pickupCost[5];

        bool _inAir;
        double _vspeed;
};

//Zombie Object Definition
class Zombie:public Object
{
    public:
        static vector<Zombie *> Zombies;
        bool _dead;

        Zombie(const double,const double);
        ~Zombie();

        double getHp() const;
        void setHp(const double);

        void update(spritelib &);
        void draw(spritelib &);

        void setSprite(const int);
        void setHurt();

        static void getTextures(spritelib &);

    private:
        Zombie(const Zombie &);

        Sound *_sndBarricadeHit;
        Sound *_sndPlayerHit;

        static spritelib_tex tex_zombie_rebel_move;
        static spritelib_tex tex_zombie_rebel_attack;
        static spritelib_tex tex_zombie_rebel_die;
        spritelib_anim *_sprite;

        double _spriteWidth;
        double _spriteHeight;
        int _anim;
        int _spriteNumFrames[3];
        spritelib_tex *_spriteTex[3];

        double _hp;
        double _moantimer;
        Sound *_sndMoan[6];
};

//Barricade Object Definition
class Barricade:public Object
{
    public:
        static vector<Barricade *> Barricades;
        static int _numAlive;

        Barricade(const double,const double);
        ~Barricade();

        double getHp() const;
        void setHp(const double);
        spritelib_anim * getSprite();

        void update(spritelib &);
        void draw(spritelib &);

        static void getTextures(spritelib &);

    private:
        Barricade(const Barricade &);

        double _hp;
        bool _dead;

        static spritelib_tex tex_barricade;
        spritelib_anim *_sprite;
};

//Effect Object Definition
class Effect:public Object
{
    public:
        static vector<Effect *> Effects;
        Effect(const double,const double, const int);
        ~Effect();

        void update(spritelib &);
        void draw(spritelib &);

        static void getTextures(spritelib &);

    private:
        Effect(const Effect &);

        static spritelib_tex tex_blood_effect;
        static spritelib_tex tex_fix_effect;

        double _type;
        double _lifetimer;
        double _direction;
        double _speed;
        double _scale;
};

//Pickup Object Class
class Pickup:public Object
{
    public:
        static vector<Pickup *> Pickups;
        Pickup(const double,const double,const int);
        ~Pickup();

        void update(spritelib &);
        void draw(spritelib &);

        static void getTextures(spritelib &);

    private:
        Pickup(const Pickup &);

        spritelib_anim *_sprite;
        spritelib_tex *_spriteTex[5];
        int _spriteNumFrames[5];
        double _yOff[5];

        static spritelib_tex tex_pickup_uzi;
        static spritelib_tex tex_pickup_shotgun;
        static spritelib_tex tex_pickup_instakill;
        static spritelib_tex tex_pickup_nuke;
        static spritelib_tex tex_pickup_star;

        int _type;
        bool _dead;
        double _vspeed;
};

#endif
