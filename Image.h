#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include "Pixel.h"

#ifdef _WIN32
#define u_int uint32_t
#define u_char uint8_t
#endif

class Image
{
public:

    Image();
    Image( u_int width, u_int height );
    Image( QImage* qImage );
    Image( const char* fileName );
    ~Image();
    bool save();
    bool load();
    Pixel& getPixel( u_int x, u_int y );
    void setPixel( u_int x, u_int y, Pixel pixel );
    u_int getSize();
    u_int getWidth();
    u_int getHeight();
    u_int getWidthStep();
    QImage* getQImage();
    QImage* getQImageFromBuffer();
    Pixel* getBuffer();
    inline u_char pixel( u_int x, u_int y );
    void fillBufferRGB();
    void fillQImageRGB();
    void createTest();
    void getInterpolatedPixel( float i, float j, Pixel& interpolatedPixel );
    void interpolatePixels( const Pixel& a, const Pixel& b, float fraction,
                            Pixel& interpolatedPixel );


private:

    Pixel* _buffer;
    QImage* _qImage;
    u_int _size;
    u_int _width;
    u_int _height;
    u_int _widthStep;
    u_int _nChannels;
};

#endif // IMAGE_H
