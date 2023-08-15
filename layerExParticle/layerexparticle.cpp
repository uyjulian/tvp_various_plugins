
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <objidl.h>
#include "layerexparticle.h"

void layerExParticle::reset()
{
	layerExBase::reset();
	// Change buffer position according to clipping
	_buffer += _clipTop * _pitch + _clipLeft * 4;
	_width  = _clipWidth;
	_height = _clipHeight;
}

void layerExParticle::initVectorParticle(tjs_int64 __unused, tjs_int64 mc, tjs_real gr, tjs_int64 l, tjs_int64 t, tjs_int64 w, tjs_int64 h)
{

}

void layerExParticle::initRotateParticle(tjs_int64 __unused, tjs_int64 mc, tjs_real gr, tjs_int64 cx, tjs_int64 cy)
{

}

void layerExParticle::initAccelRotateParticle(tjs_int64 __unused, tjs_int64 mc, tjs_real gr, tjs_int64 cx, tjs_int64 cy)
{

}

void layerExParticle::initBlinkParticle(tjs_int64 __unused, tjs_int64 mc, tjs_real gr, tjs_int64 l, tjs_int64 t, tjs_int64 w, tjs_int64 h)
{

}

void layerExParticle::uninitParticle()
{

}

void layerExParticle::updateParticle(tjs_int64 tick)
{

}

void layerExParticle::setParticleBlinkTime(tjs_int64 var1, tjs_int64 var2)
{

}

