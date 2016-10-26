//Definitions For spritelib_anim Header
#include "spritelib_anim.h"

//spritelib_anim Constructor
spritelib_anim::spritelib_anim(spritelib_tex &tex,const double width,const double height,const int numFrames,const int direction)
    :_index(&tex),_width(width),_height(height),_aniFrame(0.0),_curFrame(0),_numFrames(numFrames),_direction(direction)
{}

//spritelib_anim Texture Accessor
spritelib_tex * spritelib_anim::getTexture()
{
    return _index;
}

//spritelib_anim Width Accessor
double spritelib_anim::getWidth() const
{
    return _width;
}

//spritelib_anim Height Accessor
double spritelib_anim::getHeight() const
{
    return _height;
}

//spritelib_anim Number of Frames Accessor
int spritelib_anim::getNumFrames() const
{
    return _numFrames;
}

//spritelib_anim Frame Direction Mutator (Sets Playback Direction, Positive for Forward Negative of Reverse)
void spritelib_anim::setFrameDir(const int dir)
{
    if(dir>0)
    {
        _direction=1;
    }
    else if(dir<0)
    {
        _direction=-1;
    }
}

//spritelib_anim Frame Direction Accessor
int spritelib_anim::getFrameDir() const
{
    return _direction;
}

//spritelib_anim Current Frame Accessor
int spritelib_anim::getCurFrame() const
{
    return _curFrame;
}

//spritelib_anim Current Frame Mutator
void spritelib_anim::setCurFrame(const int frame)
{
    if(frame<_numFrames)
    {
        _curFrame=frame;
        _aniFrame=static_cast<double>(_curFrame);
    }
}

//spritelib_anim Updater
void spritelib_anim::update(const double dt)
{
    _aniFrame+=abs(dt)*static_cast<double>(_direction);

    if(_aniFrame<0.0)
    {
        _aniFrame=static_cast<double>(_numFrames)-0.2;
    }

    if(_aniFrame>static_cast<double>(_numFrames))
    {
        _aniFrame=0.0;
    }

    _curFrame=static_cast<int>(_aniFrame);
}

//spritelib_anim Draw Function
void spritelib_anim::draw(spritelib &lib,int frame,const double x,const double y,const double scaleX,const double scaleY,const double angle)
{
    if(frame<0||frame>=_numFrames)
    {
        frame=0;
    }

    lib.draw_anim(*_index,frame,_numFrames,x,y,_width*scaleX,_height*scaleY,angle);
}
