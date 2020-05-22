#ifndef __LayerExYADraw__
#define __LayerExYADraw__

#include "../../layerExDraw/LayerExBase.hpp"

class layerExYADraw : public layerExBase
{
public:
	layerExYADraw(DispatchT obj) : layerExBase(obj) {}

	virtual void reset();
	
	void drawFocusLines(tjs_int64 cx, tjs_int64 cy, tjs_int64 cmin, tjs_int64 cmax, tjs_int64 lmin, tjs_int64 lmax, tjs_int64 emin, tjs_int64 emax, tjs_int64 color);
};

#endif
