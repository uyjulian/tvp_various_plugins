
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ncbind.hpp"

static ttstr getLocalName() {
	ttstr tmp;
	TVPGetLocalName(tmp);
	return tmp;
}

static tjs_error TJS_INTF_METHOD
SelectDirectory(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000C190 100036b0
	if (!numparams) return TJS_E_BADPARAMCOUNT;
	//arg1 = string
	//arg2 = (narrow?) string
	//arg3 = (narrow?) string
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
CalcPCID(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000C20C 100035c0 not used
	if (!numparams) return TJS_E_BADPARAMCOUNT;
	//arg1 = tTJSVariantType tTJSVariant::Type()

	//set passed type .PCID = something
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
IsActiveWindow(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000C288 10003420
	if (!numparams) return TJS_E_BADPARAMCOUNT;
	//arg1 = window pointer

	//ret = int/bool?
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
ExistDirectory(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000C304 100024d0 not used
	if (!numparams) return TJS_E_BADPARAMCOUNT;
	//arg1 = string
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
RemoveDirectory(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000C380 10002480 not used
	if (!numparams) return TJS_E_BADPARAMCOUNT;
	//arg1 = string
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
CreateDirectory(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000C3FC 10002430 not used
	if (!numparams) return TJS_E_BADPARAMCOUNT;
	//arg1 = string
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
GetDatetime(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000C478 10003030
	//ret = dictionary
	// year: 
	// mon:
	// wday:
	// day:
	// hour: 
	// minute: 
	// second:
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
IsWindowShow(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000C4F4 10002e70 not used
	if (!numparams) return TJS_E_BADPARAMCOUNT;
	//arg1 = window pointer

	//ret = int/bool?
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
ShowWindow(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000C570 10002d30 not used
	if (!numparams) return TJS_E_BADPARAMCOUNT;
	//arg1 = window pointer
	//arg2 = tTJSVariant::operator tjs_int() const
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
SetClipboardText(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000C5EC 10002a30
	if (!numparams) return TJS_E_BADPARAMCOUNT;
	//arg1 = tTJSVariantString * tTJSVariant::AsStringNoAddRef() const
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
GetClipboardTextWithoutControlChar(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000C668 10002890 not used
	//ret = string
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
GetClipboardText(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000C6E4 10002760 not used
	//ret = string
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
GetFileTime(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000C760 10002650 not used
	//ret = integer
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
GetFileSize(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000C7DC 10002580 not used
	//ret = integer
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
CopyFile(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000C858 10002370 not used
	if (numparams < 2) return TJS_E_BADPARAMCOUNT;
	//arg1 = string
	//arg2 = string
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
MoveFile(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000C8D4 100023d0 not used
	if (numparams < 2) return TJS_E_BADPARAMCOUNT;
	//arg1 = string
	//arg2 = string
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
DeleteFile(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000C950 10002320
	if (!numparams) return TJS_E_BADPARAMCOUNT;
	//arg1 = string
	return TJS_E_NOTIMPL;
}

static tjs_error TJS_INTF_METHOD
enumFont(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000C9CC 10002180
	//arg1 = iTJSDispatch2 * tTJSVariant::AsObjectNoAddRef() const
	// showFixedPitchOnlyInFontSelector: tTJSVariant::operator tjs_int() const
	//arg2 = iTJSDispatch2 * tTJSVariant::AsObjectNoAddRef() const
	//ret = array of strings?
	return TJS_E_NOTIMPL;
}

NCB_REGISTER_FUNCTION(SelectDirectory, SelectDirectory);
NCB_REGISTER_FUNCTION(CalcPCID, CalcPCID);
NCB_REGISTER_FUNCTION(IsActiveWindow, IsActiveWindow);
NCB_REGISTER_FUNCTION(ExistDirectory, ExistDirectory);
NCB_REGISTER_FUNCTION(RemoveDirectory, RemoveDirectory);
NCB_REGISTER_FUNCTION(CreateDirectory, CreateDirectory);
NCB_REGISTER_FUNCTION(GetDatetime, GetDatetime);
NCB_REGISTER_FUNCTION(IsWindowShow, IsWindowShow);
NCB_REGISTER_FUNCTION(ShowWindow, ShowWindow);
NCB_REGISTER_FUNCTION(SetClipboardText, SetClipboardText);
NCB_REGISTER_FUNCTION(GetClipboardTextWithoutControlChar, GetClipboardTextWithoutControlChar);
NCB_REGISTER_FUNCTION(GetClipboardText, GetClipboardText);
NCB_REGISTER_FUNCTION(GetFileTime, GetFileTime);
NCB_REGISTER_FUNCTION(GetFileSize, GetFileSize);
NCB_REGISTER_FUNCTION(CopyFile, CopyFile);
NCB_REGISTER_FUNCTION(MoveFile, MoveFile);
NCB_REGISTER_FUNCTION(DeleteFile, DeleteFile);
NCB_REGISTER_FUNCTION(enumFont, enumFont);
