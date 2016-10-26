//Definitions For spritelib_text Header
#include "spritelib_text.h"

//spritelib_text Constructor
spritelib_text::spritelib_text(spritelib_tex &texture,const double width,const double height,const int numFrames)
    :_texture(&texture),_width(width),_height(height),_numFrames(numFrames)
{}

//spritelib_text String Draw Function
void spritelib_text::draw(spritelib &lib,const string &str,const double x,const double y,const double scaleX,
    const double scaleY,const double angle)
{
    for(unsigned int i=0;i<str.size();i++)
    {
        lib.draw_anim(*_texture,str[i]-48,_numFrames,
            x+((cos(angle/(180.0/M_PI)))*_width*scaleX*static_cast<double>(i)),
            y+((-sin(angle/(180.0/M_PI)))*_height*scaleY*static_cast<double>(i)),
            _width*scaleX,_height*scaleY,0);
    }
}

//spritelib_text Char Draw Function
void spritelib_text::draw(spritelib &lib,const char &ch,const double x,const double y,const double scaleX,
    const double scaleY,const double angle)
{
    lib.draw_anim(*_texture,ch-48,_numFrames,
        x+((cos(angle/(180.0/M_PI)))*_width*scaleX),
        y+((-sin(angle/(180.0/M_PI)))*_height*scaleY),
        _width*scaleX,_height*scaleY,0);
}
