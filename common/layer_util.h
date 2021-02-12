
/**
 * @file
 * Utility functions for working with Layer objects
 */

#ifndef __LAYER_UTIL_H
#define __LAYER_UTIL_H

inline bool get_layer_pointers(iTJSDispatch2 *layerobj, tjs_uint32 **buffer, tjs_int *width, tjs_int *height, tjs_int *pitch)
{
	bool success = true;

	if (buffer)
	{
		tTJSVariant var;
		if (TJS_FAILED(layerobj->PropGet(0, TJS_W("mainImageBufferForWrite"), NULL, &var, layerobj)))
		{
			success = false;
		}
		else
		{
			*buffer = reinterpret_cast<tjs_uint32 *>(var.AsInteger());
		}
	}

	if (width)
	{
		tTJSVariant var;
		if (TJS_FAILED(layerobj->PropGet(0, TJS_W("imageWidth"), NULL, &var, layerobj)))
		{
			success = false;
		}
		else
		{
			*width = (tjs_int)var;
		}
	}

	if (height)
	{
		tTJSVariant var;
		if (TJS_FAILED(layerobj->PropGet(0, TJS_W("imageHeight"), NULL, &var, layerobj)))
		{
			success = false;
		}
		else
		{
			*height = (tjs_int)var;
		}
	}

	if (pitch)
	{
		tTJSVariant var;
		if (TJS_FAILED(layerobj->PropGet(0, TJS_W("mainImageBufferPitch"), NULL, &var, layerobj)))
		{
			success = false;
		}
		else
		{
			*pitch = (tjs_int)var;
		}
	}

	return success;
	
}

inline bool update_layer(iTJSDispatch2 *layerobj, tjs_int left, tjs_int top, tjs_int width, tjs_int height)
{
	tTJSVariant var;
	if (TJS_SUCCEEDED(layerobj->PropGet(TJS_IGNOREPROP, TJS_W("update"), NULL, &var, layerobj)))
	{
		tTJSVariant val[4];
		tTJSVariant *varsp[4] = { val, val + 1, val + 2, val + 3 };
		val[0] = left;
		val[1] = top;
		val[2] = width;
		val[3] = height;
		if (TJS_SUCCEEDED(var.AsObjectNoAddRef()->FuncCall(0, NULL, NULL, NULL, 4, varsp, layerobj)))
		{
			return true;
		}
	}
	return false;
}

#endif
