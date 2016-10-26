#ifndef SPRITELIB_ANIM_H
#define SPRITELIB_ANIM_H

#define ANIM_FORWARD 1
#define ANIM_REVERSE -1

//Spritelib Headers
#include "spritelib.h"

//Math Headers
#include <cmath>
    using std::abs;

//spritelib_anim Declaration
class spritelib_anim
{
    public:
        spritelib_anim(spritelib_tex &,const double,const double,const int,const int);
        spritelib_tex * getTexture();
        double getWidth() const;
        double getHeight() const;
        int getNumFrames() const;
        void setFrameDir(const int);
        int getFrameDir() const;
        int getCurFrame() const;
        void setCurFrame(const int);
        void update(const double);
        void draw(spritelib &,int,const double,const double,const double,const double,const double);

    private:
        spritelib_anim(const spritelib_anim &);
        spritelib_tex *_index;
        double _width;
        double _height;
        double _aniFrame;
        int _curFrame;
        int _numFrames;
        int _direction;

};

#endif
