
#include <windows.h>
#include "layerexfilter.h"

void
layerExFilter::reset()
{
	layerExBase::reset();
	// Change buffer position according to clipping
	_buffer += _clipTop * _pitch + _clipLeft * 4;
	_width  = _clipWidth;
	_height = _clipHeight;
}

void
layerExFilter::drawNoise(bool monocro, tjs_int64 under, tjs_int64 upper, tjs_int64 seed, tjs_int64 l, tjs_int64 t, tjs_int64 w, tjs_int64 h, tjs_int64 holdalpha)
{
#if 0
	BYTE *src = (BYTE*)_buffer;
	for (int y=0; y<_height; y++){
		BYTE *p = src;
		for (int x=0; x<_width; x++,p+=4){
			BYTE n = (BYTE)(rand()/(RAND_MAX/255));
			p[2] = p[1] = p[0] = n;
		}
		src += _pitch;
	}
#endif
	redraw();
}

void
layerExFilter::doContrast(tjs_int64 contrast)
{
#if 0
	BYTE *src = (BYTE*)_buffer;
	for (int y=0; y<_height; y++){
		BYTE *p = src;
		for (int x=0; x<_width; x++,p+=4){
			BYTE n = (BYTE)(rand()/(RAND_MAX/255));
			p[2] = p[1] = p[0] = n;
		}
		src += _pitch;
	}
#endif
	redraw();
}
