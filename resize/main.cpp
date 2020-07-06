
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ncbind.hpp"

static tjs_error TJS_INTF_METHOD
AreaAverageReducation(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 0040B8A8 0040188C; Layer.operateStretch / stAreaAvg method is used in place of this
	if (numparams < 2) return TJS_E_BADPARAMCOUNT;
	//arg1 = layer pointer
	//arg2 = layer pointer
	//arg3 = tTVInteger tTJSVariant::AsInteger() const
	//arg4 = tTVInteger tTJSVariant::AsInteger() const
	//arg5 = tTVInteger tTJSVariant::AsInteger() const
	//arg6 = tTVInteger tTJSVariant::AsInteger() const
	return TJS_E_NOTIMPL;
}

NCB_REGISTER_FUNCTION(AreaAverageReducation, AreaAverageReducation);
