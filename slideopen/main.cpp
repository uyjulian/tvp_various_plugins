
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ncbind.hpp"

static tjs_error TJS_INTF_METHOD
finishSlideOpen(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000A0E0 10002330
	return TJS_S_OK;
}

static tjs_error TJS_INTF_METHOD
drawSlideOpen(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000A15C 100020d0
	if (!numparams) return TJS_E_BADPARAMCOUNT;
	//arg1 = tTVReal tTJSVariant::AsReal() const
	
	return TJS_S_OK;
}

static tjs_error TJS_INTF_METHOD
initSlideOpen(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000A1D8 10001c70
	if (!numparams) return TJS_E_BADPARAMCOUNT;
	//arg1 = Slide Open plugin object/dictionary
	// open: tTJSVariant::operator tjs_int() const
	// dest: layer pointer
	// src: layer pointer
	// type: tTJSVariant::operator tjs_int() const
	return TJS_S_OK;
}

NCB_REGISTER_FUNCTION(finishSlideOpen, finishSlideOpen);
NCB_REGISTER_FUNCTION(drawSlideOpen, drawSlideOpen);
NCB_REGISTER_FUNCTION(initSlideOpen, initSlideOpen);
