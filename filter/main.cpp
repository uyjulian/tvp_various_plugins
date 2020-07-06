
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ncbind.hpp"

#if 0
static tjs_error TJS_INTF_METHOD
Vortex(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F110 10006ca0 not used
	if (numparams == 0) return TJS_E_BADPARAMCOUNT;
	//arg0 = dictionary
	// src: layer pointer
	// dest: layer pointer
	// rad: tTJSVariant::operator tTVReal() const; default 0.0
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
Stretch(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F18C 10005db0 not used but referenced by script (zoomming)
	if (numparams == 0) return TJS_E_BADPARAMCOUNT;
	//arg0 = dictionary
	// src: layer
	// dest: layer
	// sleft: tTJSVariant::operator tjs_int() const
	// stop: tTJSVariant::operator tjs_int() const
	// swidth: tTJSVariant::operator tjs_int() const
	// sheight: tTJSVariant::operator tjs_int() const
	// dleft: tTJSVariant::operator tjs_int() const; default 0
	// dtop: tTJSVariant::operator tjs_int() const; default 0.0
	// dwidth: tTJSVariant::operator tjs_int() const
	// dheight: tTJSVariant::operator tjs_int() const
	// opa: tTJSVariant::operator tjs_int() const
	return TJS_E_NOTIMPL;
}
#endif

static tjs_error TJS_INTF_METHOD
endHaze(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F208 10005d70
	return TJS_S_OK;
}

static tjs_error TJS_INTF_METHOD
doHaze(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F284 100052e0
	if (numparams == 0) return TJS_E_BADPARAMCOUNT;
	//arg0 = dictionary
	// src: layer
	// dest: layer
	// tick: tTJSVariant::operator tjs_int() const; default 0
	// per: tTJSVariant::operator tTVReal() const; default 0.0
	// bgcolor: tTJSVariant::operator tjs_int() const
	// blend: tTJSVariant::operator tjs_int() const
	return TJS_S_OK;
}

static tjs_error TJS_INTF_METHOD
initHaze(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F300 10004c90
	if (numparams == 0) return TJS_E_BADPARAMCOUNT;
	//arg0 = Haze plugin object/dictionary
	// time: tTJSVariant::operator tjs_int() const; default -1
	// intime: tTJSVariant::operator tjs_int() const; default 800
	// outtime: tTJSVariant::operator tjs_int() const
	// speed: tTJSVariant::operator tTVReal() const; default 0.001570796326794897
	// cycle: tTJSVariant::operator tTVReal() const; default 6.0
	// upper: tTJSVariant::operator tjs_int() const; default -1
	// center: tTJSVariant::operator tjs_int() const; default -1
	// lower: tTJSVariant::operator tjs_int() const; default -1
	// upperpow: tTJSVariant::operator tTVReal() const; default (int64)0xFFFFF
	// centerpow: tTJSVariant::operator tTVReal() const; default (int64)0xFFFFF
	// lowerpow: tTJSVariant::operator tTVReal() const; default (int64)0xFFFFF
	// waves: array
	//  count: tTJSVariant::operator tjs_int() const; builtin variable of array
	// lwaves: array
	//  count: tTJSVariant::operator tjs_int() const; builtin variable of array
	return TJS_S_OK;
}

static tjs_error TJS_INTF_METHOD
Contrast(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F37C 10004860; possible replacement by LayerExImage.light
	if (numparams == 0) return TJS_E_BADPARAMCOUNT;
	//arg0 = dictionary
	// layer: layer
	// level: tTJSVariant::operator tjs_int() const
	return TJS_S_OK;
}

static tjs_error TJS_INTF_METHOD
Noise(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F3F8 10003f20; possible replacement by LayerExImage.noise
	if (numparams == 0) return TJS_E_BADPARAMCOUNT;
	//arg0 = dictionary
	// layer: layer
	// monocro: tTJSVariant::operator tjs_int() const
	// seed: tTJSVariant::operator tjs_int() const
	// under: tTJSVariant::operator tjs_int() const
	// upper: tTJSVariant::operator tjs_int() const
	return TJS_S_OK;
}

#if 0
static tjs_error TJS_INTF_METHOD
ReleaseLens(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F474 10003f00 not used
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
InitLens(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F4F0 10003ee0 not used
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
Lens(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F56C 10003ae0 not used
	if (numparams < 1) return TJS_E_BADPARAMCOUNT;
	//arg0 = dictionary
	// src: layer
	// dest: layer
	// zoom: tTJSVariant::operator tTVReal() const
	// power: tTJSVariant::operator tjs_int() const
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
Blur(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F5E8 10003730 not used but referenced by script
	if (numparams < 1) return TJS_E_BADPARAMCOUNT;
	//arg0 = dictionary
	// layer: layer
	// level: tTJSVariant::operator tjs_int() const
	// type: tTJSVariant::operator tjs_int() const
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
Smudge(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F664 100033d0 not used but referenced by script
	if (numparams < 1) return TJS_E_BADPARAMCOUNT;
	//arg0 = dictionary
	// layer: layer
	// level: tTJSVariant::operator tjs_int() const
	return TJS_E_NOTIMPL;
}
#endif

#if 0
NCB_REGISTER_FUNCTION(Vortex, Vortex);
NCB_REGISTER_FUNCTION(Stretch, Stretch);
#endif
NCB_REGISTER_FUNCTION(endHaze, endHaze);
NCB_REGISTER_FUNCTION(doHaze, doHaze);
NCB_REGISTER_FUNCTION(initHaze, initHaze);
NCB_REGISTER_FUNCTION(Contrast, Contrast);
NCB_REGISTER_FUNCTION(Noise, Noise);
#if 0
NCB_REGISTER_FUNCTION(ReleaseLens, ReleaseLens);
NCB_REGISTER_FUNCTION(InitLens, InitLens);
NCB_REGISTER_FUNCTION(Lens, Lens);
NCB_REGISTER_FUNCTION(Blur, Blur);
NCB_REGISTER_FUNCTION(Smudge, Smudge);
#endif
