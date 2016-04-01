#include "CRTFilter.h"

CRTFilter::CRTFilter( Image* inputImage, float scaleFactor ) :
    Filter( inputImage, scaleFactor )
{
}


CRTFilter::~CRTFilter()
{
}


void CRTFilter::apply()
{
    #pragma omp parallel for
    for(u_int w = 0; w < _inputImage->getWidth(); w++)
    {
        for(u_int h = 0; h < _inputImage->getHeight(); h++)
        {
            const Pixel& pixel = _inputImage->getPixel( w, h );

                u_int outW = w * _scaleFactor;
                u_int outH = h * _scaleFactor;

                Pixel redPixel = Pixel( pixel.red, 0, 0 );
                Pixel greenPixel = Pixel( 0, pixel.green, 0 );
                Pixel bluePixel = Pixel( 0, 0, pixel.blue );

                for( u_int outH_t = outH; outH_t < outH + _scaleFactor; outH_t++ )
                {
                    for( u_int outW_t = outW; outW_t < outW + _scaleFactor / 3; outW_t++ )
                    {
                        _outputImage->setPixel( outW_t, outH_t, redPixel );
                    }

                    for( u_int outW_t = outW + _scaleFactor / 3; outW_t < outW + ( 2 *_scaleFactor ) / 3; outW_t++ )
                    {
                        _outputImage->setPixel( outW_t, outH_t, greenPixel );
                    }

                    for( u_int outW_t = outW + ( 2 *_scaleFactor ) / 3; outW_t < outW + _scaleFactor; outW_t++ )
                    {
                        _outputImage->setPixel( outW_t, outH_t, bluePixel );
                    }
                }
        }
    }

    _outputImage->fillQImageRGB();
}
