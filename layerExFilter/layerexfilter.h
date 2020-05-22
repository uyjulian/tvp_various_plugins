#ifndef __LayerExFilter__
#define __LayerExFilter__

#include "../../layerExDraw/LayerExBase.hpp"

class layerExFilter : public layerExBase
{
public:
	layerExFilter(DispatchT obj) : layerExBase(obj) {}

	virtual void reset();
	
	void drawNoise(bool monocro, tjs_int64 under, tjs_int64 upper, tjs_int64 seed, tjs_int64 l, tjs_int64 t, tjs_int64 w, tjs_int64 h, tjs_int64 holdalpha);
	void doContrast(tjs_int64 contrast);
#if 0
	int initHazeCopy(int waveinfono, /*Array*/ waves, /*Array*/ lwaves, /*Array*/ powers);
	void uninitHazeCopy(int waveinfono);
	void hazeCopy(int waveinfono, /*Layer*/ srcLayer, tjs_int64 left, tjs_int64 top, tjs_int64 rad, tjs_int64 delta, tjs_int64 per, bool alphablend, tjs_int64 destLeft, tjs_int64 destTop, tjs_int64 destWidth, tjs_int64 destHeight, tjs_int64 realImageWidth, tjs_int64 realImageHeight);
#endif

};

#endif
