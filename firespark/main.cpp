
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ncbind.hpp"

static tjs_error TJS_INTF_METHOD
drawFireSpark(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000D108 100014d0
	if (numparams <= 0) {
		// grab value from tjs_uint64 ::TVPGetTickCount()
	}
	else {
		//arg1 = dictionary
		// tick: tTJSVariant::operator tjs_int() const
	}
	return TJS_S_OK;
}

static tjs_error TJS_INTF_METHOD
changeFireSpark(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000D184 10002de0
	if (numparams < 1) return TJS_E_BADPARAMCOUNT;
	//arg1 = dictionary
	// maxgen: tTJSVariant::operator tjs_int() const
	// transtime: tTJSVariant::operator tjs_int() const
	// pause: tTJSVariant::operator tjs_int() const
	// effect: tTJSVariant::operator tjs_int() const
	// layer: iTJSDispatch2 * tTJSVariant::AsObjectNoAddRef() const (layer pointer; destination)
	// 
	return TJS_S_OK;
}

static tjs_error TJS_INTF_METHOD
finishFireSpark(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000D200 10002db0
	return TJS_S_OK;
}

static tjs_error TJS_INTF_METHOD
initFireSpark(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000D27C 10001ec0
	if (numparams < 1) return TJS_E_BADPARAMCOUNT;
	//arg1 = iTJSDispatch2 * tTJSVariant::AsObjectNoAddRef() const (layer pointer; destination)
	//arg2 = dictionary
	// maxgen: tTJSVariant::operator tjs_int() const
	// basevelocity: tTJSVariant::operator tTVReal() const
	// velocityrange: tTJSVariant::operator tTVReal() const
	// baselifetime: tTJSVariant::operator tjs_int() const
	// lifetimerange: tTJSVariant::operator tjs_int() const
	// baseaccel: tTJSVariant::operator tjs_int() const
	// accelrange: tTJSVariant::operator tjs_int() const
	// directionbase: tTJSVariant::operator tTVReal() const
	// basetop: tTJSVariant::operator tjs_int() const
	// heightrange: tTJSVariant::operator tjs_int() const
	// basesizew: tTJSVariant::operator tjs_int() const
	// sizewrange: tTJSVariant::operator tjs_int() const
	// basesizeh: tTJSVariant::operator tjs_int() const
	// sizehrange: tTJSVariant::operator tjs_int() const
	// windvelocity: tTJSVariant::operator tjs_int() const
	// windvariancecapability: tTJSVariant::operator tTVReal() const
	// maxwindvelocity: tTJSVariant::operator tTVReal() const
	// samesize: tTJSVariant::operator tjs_int() const
	// colortable: tTJSString::tTJSString(const tTJSVariant &)
	return TJS_S_OK;
}

NCB_REGISTER_FUNCTION(drawFireSpark, drawFireSpark);
NCB_REGISTER_FUNCTION(changeFireSpark, changeFireSpark);
NCB_REGISTER_FUNCTION(finishFireSpark, finishFireSpark);
NCB_REGISTER_FUNCTION(initFireSpark, initFireSpark);
