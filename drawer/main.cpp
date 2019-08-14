
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ncbind.hpp"

static tjs_error TJS_INTF_METHOD
drawAATriangle(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 100090E0 10002350 not used
	if (numparams == 0) return TJS_E_BADPARAMCOUNT;
	//arg0 = tTJSVariant::AsObjectNoAddRef
	//arg1 = tTVInteger tTJSVariant::AsInteger() const
	//arg2 = tTVInteger tTJSVariant::AsInteger() const
	//arg3 = tTVInteger tTJSVariant::AsInteger() const
	//arg4 = tTVInteger tTJSVariant::AsInteger() const
	//arg5 = tTVInteger tTJSVariant::AsInteger() const
	//arg6 = tTVInteger tTJSVariant::AsInteger() const
	//arg7 = tTVInteger tTJSVariant::AsInteger() const
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
drawAALine(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000915C 100021b0; possible replacement by LayerExDraw.drawLine
	if (numparams == 0) return TJS_E_BADPARAMCOUNT;
	//arg0 = tTJSVariant::AsObjectNoAddRef
	//arg1 = tTVInteger tTJSVariant::AsInteger() const
	//arg2 = tTVInteger tTJSVariant::AsInteger() const
	//arg3 = tTVInteger tTJSVariant::AsInteger() const
	//arg4 = tTVInteger tTJSVariant::AsInteger() const
	//arg5 = tTVInteger tTJSVariant::AsInteger() const

	//get layer stuff
	//setting of global variables
	//call sub_100012A0
	//update layer
	
	return TJS_S_OK;
}

static tjs_error TJS_INTF_METHOD
drawLine(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 100091D8 10002010; possible replacement by LayerExDraw.drawLine
	if (numparams < 6) return TJS_E_BADPARAMCOUNT;
	//arg0 = tTJSVariant::AsObjectNoAddRef
	//arg1 = tTVInteger tTJSVariant::AsInteger() const
	//arg2 = tTVInteger tTJSVariant::AsInteger() const
	//arg3 = tTVInteger tTJSVariant::AsInteger() const
	//arg4 = tTVInteger tTJSVariant::AsInteger() const
	//arg5 = tTVInteger tTJSVariant::AsInteger() const

	//get layer stuff
	//setting of global variables
	//call sub_100012A0
	//update layer

	return TJS_S_OK;
}

NCB_REGISTER_FUNCTION(drawAATriangle, drawAATriangle);
NCB_REGISTER_FUNCTION(drawAALine, drawAALine);
NCB_REGISTER_FUNCTION(drawLine, drawLine);
