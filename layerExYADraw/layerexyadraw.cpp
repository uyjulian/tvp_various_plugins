
#include <windows.h>
#include "layerexyadraw.h"

void layerExYADraw::reset()
{
	layerExBase::reset();
	// Change buffer position according to clipping
	_buffer += _clipTop * _pitch + _clipLeft * 4;
	_width  = _clipWidth;
	_height = _clipHeight;
}

void layerExYADraw::drawFocusLines(tjs_int64 cx, tjs_int64 cy, tjs_int64 cmin, tjs_int64 cmax, tjs_int64 lmin, tjs_int64 lmax, tjs_int64 emin, tjs_int64 emax, tjs_int64 color)
{

}
