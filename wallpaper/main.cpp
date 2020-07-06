
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ncbind.hpp"

#if 0
static tjs_error TJS_INTF_METHOD
getwallpaper(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 10008110 10001C40 not used
	//ret = string
	return TJS_E_NOTIMPL;
}
#endif

static tjs_error TJS_INTF_METHOD
setwallpaper(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000818C 10001200
	if (!numparams) return TJS_E_BADPARAMCOUNT;
	//possible 3 arguments with varying types
	//arg1 = iTJSDispatch2 * tTJSVariant::AsObjectNoAddRef() const
	// storage: 
	// tile: tTVInteger tTJSVariant::AsInteger() const
	// magnify: tTVInteger tTJSVariant::AsInteger() const
	// center: (not read by code)
	return TJS_S_OK;
}

#if 0
NCB_REGISTER_FUNCTION(getwallpaper, getwallpaper);
#endif
NCB_REGISTER_FUNCTION(setwallpaper, setwallpaper);
