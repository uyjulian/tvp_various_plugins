#ifndef __LayerExParticle__
#define __LayerExParticle__

#include "../../layerExDraw/LayerExBase.hpp"

class layerExParticle : public layerExBase
{
public:
	layerExParticle(DispatchT obj) : layerExBase(obj) {}

	virtual void reset();
	
	void initVectorParticle(tjs_int64 __unused, tjs_int64 mc, tjs_real gr, tjs_int64 l, tjs_int64 t, tjs_int64 w, tjs_int64 h);
	void initRotateParticle(tjs_int64 __unused, tjs_int64 mc, tjs_real gr, tjs_int64 cx, tjs_int64 cy);
	void initAccelRotateParticle(tjs_int64 __unused, tjs_int64 mc, tjs_real gr, tjs_int64 cx, tjs_int64 cy);
	void initBlinkParticle(tjs_int64 __unused, tjs_int64 mc, tjs_real gr, tjs_int64 l, tjs_int64 t, tjs_int64 w, tjs_int64 h);
	void uninitParticle();
	void updateParticle(tjs_int64 tick);
	// assignParticle not used
	// initializedParticle is a boolean property of Layer
	// particleImage is a property of Layer containing a Layer
	// setParticleBlinkMax not used
	void setParticleBlinkTime(tjs_int64 var1, tjs_int64 var2);
	// setParticleBlinkCount not used

};

#endif
