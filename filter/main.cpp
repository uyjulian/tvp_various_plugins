
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ncbind/ncbind.hpp"
#include "LayerBitmapUtility.h"
#include <cmath>
#include <limits>

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

static struct
{
	bool enabled;
	tjs_int time;
	tjs_int intime;
	tjs_int outtime;
	tjs_real speed;
	tjs_real cycle;
	tjs_int upper;
	tjs_int center;
	tjs_int lower;
	tjs_int64 upperpow;
	tjs_int64 centerpow;
	tjs_int64 lowerpow;
	tjs_real* waves;
	tjs_real* lwaves;
} haze_args;

static tjs_real* parse_waves(tTJSVariant waves_var)
{
	tjs_real waves_tmp[96];
	ncbPropAccessor waves_accessor(waves_var);
	int c1 = waves_accessor.GetArrayCount();
	if (c1 > 32)
	{
		c1 = 32;
	}
	for (int i = 0; i < c1; i += 1)
	{
		tTJSVariant wave_var;
		if (waves_accessor.checkVariant(i, wave_var))
		{
			ncbPropAccessor waves2(wave_var);
			int c2 = waves2.GetArrayCount();
			if (c2 > 3)
			{
				c2 = 3;
			}
			for (int j = 0; j < c2; j += 1)
			{
				waves_tmp[(3 * i) + j] = waves2.getRealValue(j);
			}
		}
	}
	tjs_real* waves = new tjs_real[0x4000];
	tjs_real v18 = 0.0;
	for (int i = 0; i < 0x4000; i += 1)
	{
		tjs_real v21 = 0.0;
		tjs_real *v22 = &waves_tmp[1];
		for (int j = 0; j < c1; j += 1)
		{
			v22 += 3;
			v21 += cos(v18 * *(v22 - 4) + *(v22 - 3)) * *(v22 - 2);
			v18 += 0.001533980787885641;
		}
		waves[i] = v21 + v21;
	}
	return waves;
}

static tjs_error TJS_INTF_METHOD
initHaze(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F300 10004c90
	if (numparams == 0) return TJS_E_BADPARAMCOUNT;

	if (haze_args.enabled)
	{
		return TJS_E_FAIL;
	}
	//arg0 = Haze plugin object/dictionary
	ncbPropAccessor dict(param[0]->AsObjectNoAddRef());
	// time: tTJSVariant::operator tjs_int() const; default -1
	haze_args.time = dict.getIntValue(TJS_W("time"), -1);
	// intime: tTJSVariant::operator tjs_int() const; default 800
	haze_args.intime = dict.getIntValue(TJS_W("intime"), 800);
	// outtime: tTJSVariant::operator tjs_int() const
	haze_args.outtime = dict.getIntValue(TJS_W("outtime"), haze_args.intime);
	// speed: tTJSVariant::operator tTVReal() const; default 0.001570796326794897
	haze_args.speed = dict.getRealValue(TJS_W("speed"), 0.001570796326794897);
	// cycle: tTJSVariant::operator tTVReal() const; default 6.0
	haze_args.cycle = dict.getRealValue(TJS_W("cycle"), 6.0);
	// upper: tTJSVariant::operator tjs_int() const; default -1
	haze_args.upper = dict.getIntValue(TJS_W("upper"), -1);
	// center: tTJSVariant::operator tjs_int() const; default -1
	haze_args.center = dict.getIntValue(TJS_W("center"), -1);
	// lower: tTJSVariant::operator tjs_int() const; default -1
	haze_args.lower = dict.getIntValue(TJS_W("lower"), -1);
	// upperpow: tTJSVariant::operator tTVReal() const; default (int64)0xFFFFF
	tjs_real upperpow = dict.getRealValue(TJS_W("upperpow"), std::numeric_limits<tjs_real>::quiet_NaN());
	if (upperpow != upperpow)
	{
		haze_args.upperpow = 0xFFFFF;
	}
	else
	{
		upperpow *= 1048575.0;
		haze_args.upperpow = (tjs_int64)upperpow;
	}
	
	// centerpow: tTJSVariant::operator tTVReal() const; default (int64)0xFFFFF
	tjs_real centerpow = dict.getRealValue(TJS_W("centerpow"), std::numeric_limits<tjs_real>::quiet_NaN());
	if (centerpow != centerpow)
	{
		haze_args.centerpow = 0xFFFFF;
	}
	else
	{
		centerpow *= 1048575.0;
		haze_args.centerpow = (tjs_int64)centerpow;
	}
	// lowerpow: tTJSVariant::operator tTVReal() const; default (int64)0xFFFFF
	tjs_real lowerpow = dict.getRealValue(TJS_W("lowerpow"), std::numeric_limits<tjs_real>::quiet_NaN());
	if (lowerpow != lowerpow)
	{
		haze_args.lowerpow = 0xFFFFF;
	}
	else
	{
		lowerpow *= 1048575.0;
		haze_args.lowerpow = (tjs_int64)lowerpow;
	}
	// waves: array
	//  count: tTJSVariant::operator tjs_int() const; builtin variable of array
	tTJSVariant waves_var;
	if (dict.checkVariant(TJS_W("waves"), waves_var))
	{
		haze_args.waves = parse_waves(waves_var);
	}
	else
	{
		haze_args.waves = NULL;
	}
	// lwaves: array
	//  count: tTJSVariant::operator tjs_int() const; builtin variable of array
	tTJSVariant lwaves_var;
	if (dict.checkVariant(TJS_W("lwaves"), lwaves_var))
	{
		haze_args.lwaves = parse_waves(lwaves_var);
	}
	else
	{
		haze_args.lwaves = NULL;
	}
	haze_args.enabled = true;
	return TJS_S_OK;
}

static void sub_100027C0(tjs_uint32 *dest_buffer, tjs_uint32 *src_buffer, tjs_int a3, tjs_int dest_width, tjs_int dest_buffer_offset, tjs_int src_buffer_offset)
{
	int v5;
	int v6;
	int v7;
	tjs_uint32 *v8;
	tjs_uint32 *v9;
	tjs_uint32 *v10;
	tjs_uint32 *v11;
	int v12;

	v5 = a3 >> 1;
	if ( a3 < 0 )
	{
		src_buffer_offset -= v5;
		v6 = dest_width + v5 - 2;
	}
	else
	{
		dest_buffer_offset += v5;
		v6 = dest_width - v5 - 2;
	}

	tjs_uint32 *a1 = dest_buffer + dest_buffer_offset;
	tjs_uint32 *a2 = src_buffer + src_buffer_offset;

	*a1 = *a2;
#if 0
	v7 = v6 + 3;
#else
	v7 = (v6 + 3) >> 2;
#endif
	v8 = a1 + 1;
	v9 = a2 + 1;
#if 0
	if ( a3 & 1 )
	{
		v10 = v8 + 1;
		v11 = v9 + 1;
		v12 = v7 - 1;
		for (tjs_int i = 1; i < v12 - 1; i += 1)
		{
			v10[i] = ((v11[i] >> 2) & 0x3F3F3F3F)
					 + (((tjs_uint32)v10[i] >> 1) & 0x7F7F7F7F)
					 + ((v11[i - 1] >> 2) & 0x3F3F3F3F);
		}
		//v10[v12] = ((v11[v12] >> 1) & 0x7F7F7F7F) + (((tjs_uint32)v10[v12] >> 1) & 0x7F7F7F7F);
	}
	else
	{
		for (tjs_int i = 1; i < v7 - 1; i += 1)
		{
			v8[i] = ((v9[i] >> 1) & 0x7F7F7F7F) + (((tjs_uint32)v8[i] >> 1) & 0x7F7F7F7F);
		}
	}
#elif 0
	if ( a3 & 1 )
	{
		v10 = v8 + 1;
		v11 = v9 + 1;
		v12 = v7 - 1;
		while ( 1 )
		{
			*v10 = ((*v11 >> 2) & 0x3F3F3F3F)
					 + (((tjs_uint32)*v10 >> 1) & 0x7F7F7F7F)
					 + ((*(v11 - 1) >> 2) & 0x3F3F3F3F);
			++v10;
			++v11;
			if ( !--v12 )
				break;
		}
		*v10 = ((*v11 >> 1) & 0x7F7F7F7F) + (((tjs_uint32)*v10 >> 1) & 0x7F7F7F7F);
	}
	else
	{
		while ( 1 )
		{
			*v8 = ((*v9 >> 1) & 0x7F7F7F7F) + (((tjs_uint32)*v8 >> 1) & 0x7F7F7F7F);
			++v8;
			++v9;
			if ( !--v7 )
				break;
		}
	}
#else
	if ( a3 & 1 )
	{
		v10 = v8 + 1;
		v11 = v9 + 1;
		v12 = v7 - 1;
		switch ( v6 % 4 )
		{
			case 0:
				goto LABEL_7;
			case 1:
				goto LABEL_6;
			case 2:
				goto LABEL_9;
			case 3:
				while ( 1 )
				{
					*v10 = ((*v11 >> 2) & 0x3F3F3F3F)
							 + (((tjs_uint32)*v10 >> 1) & 0x7F7F7F7F)
							 + ((*(v11 - 1) >> 2) & 0x3F3F3F3F);
					++v10;
					++v11;
LABEL_9:
					*v10 = ((*v11 >> 2) & 0x3F3F3F3F)
							 + (((tjs_uint32)*v10 >> 1) & 0x7F7F7F7F)
							 + ((*(v11 - 1) >> 2) & 0x3F3F3F3F);
					++v10;
					++v11;
LABEL_6:
					*v10 = ((*v11 >> 2) & 0x3F3F3F3F)
							 + (((tjs_uint32)*v10 >> 1) & 0x7F7F7F7F)
							 + ((*(v11 - 1) >> 2) & 0x3F3F3F3F);
					++v10;
					++v11;
					if ( !--v12 )
						break;
LABEL_7:
					*v10 = ((*v11 >> 2) & 0x3F3F3F3F)
							 + (((tjs_uint32)*v10 >> 1) & 0x7F7F7F7F)
							 + ((*(v11 - 1) >> 2) & 0x3F3F3F3F);
					++v10;
					++v11;
				}
				break;
			default:
				break;
		}
		*v10 = ((*v11 >> 1) & 0x7F7F7F7F) + (((tjs_uint32)*v10 >> 1) & 0x7F7F7F7F);
	}
	else
	{
		switch ( v6 % 4 )
		{
			case 0:
				goto LABEL_14;
			case 1:
				goto LABEL_13;
			case 2:
				goto LABEL_16;
			case 3:
				while ( 1 )
				{
					*v8 = ((*v9 >> 1) & 0x7F7F7F7F) + (((tjs_uint32)*v8 >> 1) & 0x7F7F7F7F);
					++v8;
					++v9;
LABEL_16:
					*v8 = ((*v9 >> 1) & 0x7F7F7F7F) + (((tjs_uint32)*v8 >> 1) & 0x7F7F7F7F);
					++v8;
					++v9;
LABEL_13:
					*v8 = ((*v9 >> 1) & 0x7F7F7F7F) + (((tjs_uint32)*v8 >> 1) & 0x7F7F7F7F);
					++v8;
					++v9;
					if ( !--v7 )
						break;
LABEL_14:
					*v8 = ((*v9 >> 1) & 0x7F7F7F7F) + (((tjs_uint32)*v8 >> 1) & 0x7F7F7F7F);
					++v8;
					++v9;
				}
				break;
			default:
				return;
		}
	}
#endif
}

static void sub_100029C0(tjs_uint32 *dest_buffer, tjs_uint32 *src_buffer, tjs_int a3, tjs_int dest_width, tjs_int dest_buffer_offset, tjs_int src_buffer_offset)
{
	int v5;
	int v6;
	int v7;
	tjs_uint32 *v8;
	tjs_uint32 *v9;
	tjs_uint32 *v10;
	tjs_uint32 *v11;
	int v12;

	v5 = a3 >> 1;
	if ( a3 < 0 )
	{
		src_buffer_offset -= v5;
		v6 = dest_width + v5 - 2;
	}
	else
	{
		dest_buffer_offset += v5;
		v6 = dest_width - v5 - 2;
	}

	tjs_uint32 *a1 = dest_buffer + dest_buffer_offset;
	tjs_uint32 *a2 = src_buffer + src_buffer_offset;

	*a1 = *a2;
#if 0
	v7 = v6 + 3;
#else
	v7 = (v6 + 3) >> 2;
#endif
	v8 = a1 + 1;
	v9 = a2 + 1;
#if 0
	if ( a3 & 1 )
	{
		v10 = v8 + 1;
		v11 = v9 + 1;
		v12 = v7 - 1;
		for (tjs_int i = 1; i < v12 - 1; i += 1)
		{
			v10[i] = ((v11[i] >> 1) & 0x7F7F7F7F) + ((v11[i - 1] >> 1) & 0x7F7F7F7F);
		}
		//v10[v12] = ((v11[v12] >> 1) & 0x7F7F7F7F) + (((tjs_uint32)v10[v12] >> 1) & 0x7F7F7F7F);
	}
	else
	{
		for (tjs_int i = 1; i < v7 - 1; i += 1)
		{
			v8[i] = v9[i];
		}
	}
#elif 0
	if ( a3 & 1 )
	{
		v10 = v8 + 1;
		v11 = v9 + 1;
		v12 = v7 - 1;
		while ( 1 )
		{
			*v10 = ((*v11 >> 1) & 0x7F7F7F7F) + ((*(v11 - 1) >> 1) & 0x7F7F7F7F);
			++v10;
			++v11;
			if ( !--v12 )
				break;
		}
		*v10 = ((*v11 >> 1) & 0x7F7F7F7F) + (((tjs_uint32)*v10 >> 1) & 0x7F7F7F7F);
	}
	else
	{
		while ( 1 )
		{
			*v8 = *v9;
			++v8;
			++v9;
			if ( !--v7 )
				break;
		}
	}
#else
	if ( a3 & 1 )
	{
		v10 = v8 + 1;
		v11 = v9 + 1;
		v12 = v7 - 1;
		switch ( v6 % 4 )
		{
			case 0:
				goto LABEL_7;
			case 1:
				goto LABEL_6;
			case 2:
				goto LABEL_9;
			case 3:
				while ( 1 )
				{
					*v10 = ((*v11 >> 1) & 0x7F7F7F7F) + ((*(v11 - 1) >> 1) & 0x7F7F7F7F);
					++v10;
					++v11;
LABEL_9:
					*v10 = ((*v11 >> 1) & 0x7F7F7F7F) + ((*(v11 - 1) >> 1) & 0x7F7F7F7F);
					++v10;
					++v11;
LABEL_6:
					*v10 = ((*v11 >> 1) & 0x7F7F7F7F) + ((*(v11 - 1) >> 1) & 0x7F7F7F7F);
					++v10;
					++v11;
					if ( !--v12 )
						break;
LABEL_7:
					*v10 = ((*v11 >> 1) & 0x7F7F7F7F) + ((*(v11 - 1) >> 1) & 0x7F7F7F7F);
					++v10;
					++v11;
				}
				break;
			default:
				break;
		}
		*v10 = ((*v11 >> 1) & 0x7F7F7F7F) + (((tjs_uint32)*v10 >> 1) & 0x7F7F7F7F);
	}
	else
	{
		switch ( v6 % 4 )
		{
			case 0:
				goto LABEL_14;
			case 1:
				goto LABEL_13;
			case 2:
				goto LABEL_16;
			case 3:
				while ( 1 )
				{
					*v8 = *v9;
					++v8;
					++v9;
LABEL_16:
					*v8 = *v9;
					++v8;
					++v9;
LABEL_13:
					*v8 = *v9;
					++v8;
					++v9;
					if ( !--v7 )
						break;
LABEL_14:
					*v8 = *v9;
					++v8;
					++v9;
				}
				break;
			default:
				return;
		}
	}
#endif
}
static tjs_error TJS_INTF_METHOD
doHaze(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F284 100052e0
	if (numparams == 0) return TJS_E_BADPARAMCOUNT;
	tjs_int src_width, src_height, src_pitch;
	tjs_uint32 *src_buffer;
	tjs_int dest_width, dest_height, dest_pitch;
	tjs_uint32 *dest_buffer;
	//arg0 = dictionary
	ncbPropAccessor dict(param[0]->AsObjectNoAddRef());
	// src: layer
	tTJSVariant src;
	tTJSVariantClosure srcbmpobject_clo;
	if (dict.checkVariant(TJS_W("src"), src))
	{
		srcbmpobject_clo = src.AsObjectClosureNoAddRef();
		GetBitmapInformationFromObject(srcbmpobject_clo, false, &src_width, &src_height, &src_pitch, (tjs_uint8 **)&src_buffer);
	}
	// dest: layer
	tTJSVariant dest;
	tTJSVariantClosure bmpobject_clo;
	if (dict.checkVariant(TJS_W("dest"), dest))
	{
		bmpobject_clo = dest.AsObjectClosureNoAddRef();
		GetBitmapInformationFromObject(bmpobject_clo, true, &dest_width, &dest_height, &dest_pitch, (tjs_uint8 **)&dest_buffer);
	}
	// tick: tTJSVariant::operator tjs_int() const; default 0
	tjs_int tick = dict.getIntValue(TJS_W("tick"), 0);
	// per: tTJSVariant::operator tTVReal() const; default 0.0
	tjs_real per = dict.getRealValue(TJS_W("per"), 0.0);
	// bgcolor: tTJSVariant::operator tjs_int() const; unused
	// blend: tTJSVariant::operator tjs_int() const
	void (*v78)(tjs_uint32 *, tjs_uint32 *, tjs_int, tjs_int, tjs_int, tjs_int);
	v78 = sub_100029C0;
	tjs_int blend = dict.getIntValue(TJS_W("blend"), 0);
	if (blend)
	{
		v78 = sub_100027C0;
	}
	// The actual update code (not cleaned up)
	tjs_int32 v27;
	tjs_int32 v22;
	{
		unsigned int v21;
		tjs_int64 v25;
		int v26;
		tjs_int64 v31;
		int v32;
		tjs_int64 v39;
		int v40;
		tjs_int64 v44;
		int v45;
		int v59;
		tjs_int v60;
		tjs_int v61;
		tjs_int v64;
		tjs_int v66;
		int v67;
		int v70;
		unsigned int v74;
		tjs_real v79;
		int v81;
		int v82;
		int v83;
		v79 = (tjs_real)((tjs_int64)((tjs_real)tick * haze_args.speed * 651.8986469044033) & 0x3FFF);
		v74 = src_pitch >> 2;
		v21 = dest_pitch >> 2;
		v22 = dest_height;
		if ( haze_args.upper >= 0 || haze_args.lower >= 0 )
		{
			if ( haze_args.center < 0 )
			{
				v59 = dest_height;
				if ( haze_args.lower <= dest_height )
				{
					if ( haze_args.lower >= 0 )
					{
						v59 = haze_args.lower;
					}
				}
				v66 = haze_args.upperpow;
				v27 = haze_args.upper < 0 ? 0 : haze_args.upper;
				v81 = (haze_args.lowerpow - haze_args.upperpow) / (v59 - v27);
				for (tjs_int i = v27; i < v59; i += 1)
				{
					v32 = 0;
					if ( haze_args.lwaves )
					{
						v31 = (tjs_int64)((tjs_real)v66 * haze_args.lwaves[(tjs_int64)v79 & 0x3FFF] * per + 0.5);
						v32 = v74 * -i;
						if ( i - (tjs_int)v31 >= 0 )
						{
							v32 = v74 * (dest_height - i - 1);
							if ( i < (tjs_int)v31 + dest_height )
							{
								v32 = v74 * -(tjs_int)v31;
							}
						}
					}
					v78(dest_buffer, src_buffer, (tjs_int)(tjs_int64)((tjs_real)v66 * haze_args.waves[(tjs_int64)v79 & 0x3FFF] * per) >> 20, dest_width, v21 * i, (v74 * i) + v32);
					v79 += haze_args.cycle;
					v66 += v81;
				}
				v22 = v59 - v27;
				goto LABEL_99;
			}
			v67 = dest_height;
			if ( haze_args.lower <= dest_height )
			{
				v67 = haze_args.lower;
			}
			v70 = dest_height;
			if ( haze_args.center <= dest_height )
			{
				v70 = haze_args.center;
			}
			v64 = haze_args.upper < 0 ? 0 : haze_args.upper;
			v60 = haze_args.upperpow;
			v82 = (haze_args.centerpow - haze_args.upperpow) / (v70 - v64);
			for (tjs_int i = v64; i < v70; i += 1)
			{
				v40 = 0;
				if ( haze_args.lwaves )
				{
					v39 = (tjs_int64)((tjs_real)v60 * haze_args.lwaves[(tjs_int64)v79 & 0x3FFF] * per + 0.5);
					v40 = v74 * -i;
					if ( i - (tjs_int)v39 >= 0 )
					{
						v40 = v74 * (dest_height - i - 1);
						if ( i < (tjs_int)v39 + dest_height )
						{
							v40 = v74 * -(tjs_int)v39;
						}
					}
				}
				v78(dest_buffer, src_buffer, (tjs_int)(tjs_int64)((tjs_real)v60 * haze_args.waves[(tjs_int64)v79 & 0x3FFF] * per) >> 20, dest_width, v21 * i, (v74 * i) + v40);
				v79 += haze_args.cycle;
				v60 += v82;
			}
			v61 = haze_args.centerpow;
			v83 = (haze_args.lowerpow - haze_args.centerpow) / (v67 - v70);
			for (tjs_int i = v70; i < v67; i += 1)
			{
				v45 = 0;
				if ( haze_args.lwaves )
				{
					v44 = (tjs_int64)((tjs_real)v61 * haze_args.lwaves[(tjs_int64)v79 & 0x3FFF] * per + 0.5);
					v45 = v74 * -i;
					if ( i - (tjs_int)v44 >= 0 )
					{
						v45 = v74 * (dest_height - i - 1);
						if ( i < (tjs_int)v44 + dest_height )
						{
							v45 = v74 * -(tjs_int)v44;
						}
					}
				}
				v78(dest_buffer, src_buffer, (tjs_int)(tjs_int64)((tjs_real)v61 * haze_args.waves[(tjs_int64)v79 & 0x3FFF] * per) >> 20, dest_width, v70 * i, (v74 * i) + v45);
				v79 += haze_args.cycle;
				v61 += v83;
			}
			v27 = v64;
			v22 = v67 - v64;
		}
		else
		{
			for (tjs_int i = 0; i < dest_height; i += 1)
			{
				v26 = 0;
				if ( haze_args.lwaves )
				{
					v25 = (tjs_int64)(per * haze_args.lwaves[(tjs_int64)v79 & 0x3FFF]);
					v26 = v74 * -i;
					if ( i - (tjs_int)v25 >= 0 )
					{
						v26 = v74 * (dest_height - 1 - i);
						if ( i < (tjs_int)v25 + dest_height )
						{
							v26 = v74 * -(tjs_int)v25;
						}
					}
				}
				v78(dest_buffer, src_buffer, (tjs_int64)(per * haze_args.waves[(tjs_int64)v79 & 0x3FFF]), dest_width, v21 * i, (v74 * i) + v26);
				v79 += haze_args.cycle;
			}
			v22 = dest_height;
			v27 = 0;
		}
	}
LABEL_99:
	tTVPRect UpdateRect;
	UpdateRect.left = 0;
	UpdateRect.top = v27;
	UpdateRect.right = (tjs_int)dest_width;
	UpdateRect.bottom = (tjs_int)v22;
	UpdateLayerWithLayerObject(bmpobject_clo, &UpdateRect, NULL, NULL);
	return TJS_S_OK;
}

static tjs_error TJS_INTF_METHOD
endHaze(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F208 10005d70
	if (haze_args.enabled)
	{
		if (haze_args.waves)
		{
			delete[] haze_args.waves;
			haze_args.waves = NULL;
		}
		if (haze_args.lwaves)
		{
			delete[] haze_args.lwaves;
			haze_args.lwaves = NULL;
		}
		haze_args.enabled = false;
		memset(&haze_args, 0, sizeof(haze_args));
	}
	return TJS_S_OK;
}

static tjs_error TJS_INTF_METHOD
Contrast(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F37C 10004860; possible replacement by LayerExImage.light
	if (numparams == 0) return TJS_E_BADPARAMCOUNT;
	tjs_int dest_width, dest_height, dest_pitch;
	tjs_uint32 *dest_buffer = NULL;
	//arg0 = dictionary
	ncbPropAccessor dict(param[0]->AsObjectNoAddRef());
	// layer: layer
	tTJSVariant dest;
	tTJSVariantClosure bmpobject_clo;
	if (dict.checkVariant(TJS_W("layer"), dest))
	{
		bmpobject_clo = dest.AsObjectClosureNoAddRef();
		GetBitmapInformationFromObject(bmpobject_clo, true, &dest_width, &dest_height, &dest_pitch, (tjs_uint8 **)&dest_buffer);
	}
	// level: tTJSVariant::operator tjs_int() const
	tjs_int level = dict.getIntValue(TJS_W("level"), 0);
	if (level && dest_buffer)
	{
		if ( level >= -127 )
		{
			if ( level > 127 )
			{
				level = 127;
			}
		}
		else
		{
			level = -127;
		}
		int v49 = dest_pitch / 4;
		tjs_uint32 v20[0x400];
		if ( level <= 0 )
		{
			int v26 = 0;
			for (tjs_int i = 0; i < 256; i += 1)
			{
				v20[i] = v26 / 255 - level;
				v26 += 2 * level + 255;
			}
		}
		else
		{
			int v22 = 255 - level;
			int v7 = 0;
			if ( level > 0 )
			{
				memset(v20, 0, 4 * level);
				v7 = level;
			}
			if ( v7 < v22 )
			{
				int v50 = 255 - 2 * level;
				for (tjs_int i = v7; i < v22; i += 1)
				{
					v20[i] = ((255 * i) - 255 * level) / v50;
				}
				v7 = 255 - level;
			}
			if ( v7 < 256 )
			{
				for (tjs_int i = v7; i < 256; i += 1)
				{
					v20[i] = 255;
				}
			}
		}
		for (tjs_int i = 0; i < dest_height; i += 1)
		{
			for (tjs_int j = 0; j < dest_width; j += 1)
			{
				dest_buffer[(i * v49) + j] = v20[dest_buffer[(i * v49) + j] & 0xFF] | (v20[(dest_buffer[(i * v49) + j] >> 8) & 0xFF] << 8) | (v20[(dest_buffer[(i * v49) + j] >> 16) & 0xFF] << 16) | (dest_buffer[(i * v49) + j] & 0xFF000000);
			}
		}
		UpdateWholeLayerWithLayerObject(bmpobject_clo);
	}
	return TJS_S_OK;
}

static int noise_current_seed = 0;

static tjs_error TJS_INTF_METHOD
Noise(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F3F8 10003f20; possible replacement by LayerExImage.noise
	if (numparams == 0) return TJS_E_BADPARAMCOUNT;
	tjs_int dest_width, dest_height, dest_pitch;
	tjs_uint32 *dest_buffer;
	//arg0 = dictionary
	ncbPropAccessor dict(param[0]->AsObjectNoAddRef());
	// layer: layer
	tTJSVariant dest;
	tTJSVariantClosure bmpobject_clo;
	if (dict.checkVariant(TJS_W("layer"), dest))
	{
		bmpobject_clo = dest.AsObjectClosureNoAddRef();
		GetBitmapInformationFromObject(bmpobject_clo, true, &dest_width, &dest_height, &dest_pitch, (tjs_uint8 **)&dest_buffer);
	}
	// monocro: tTJSVariant::operator tjs_int() const; defualt 1
	tjs_int monocro = dict.getIntValue(TJS_W("monocro"), 1);
	// seed: tTJSVariant::operator tjs_int() const; default TVPGetTickCount()
	tjs_int seed = dict.getIntValue(TJS_W("seed"), (tjs_int)TVPGetTickCount());
	// under: tTJSVariant::operator tjs_int() const; default 0
	tjs_int under = dict.getIntValue(TJS_W("under"), 0);
	// upper: tTJSVariant::operator tjs_int() const; default 255
	tjs_int upper = dict.getIntValue(TJS_W("upper"), 255);
	if ( upper < under )
	{
		tjs_int tmp = upper;
		upper = under;
		under = tmp;
	}
	{
		tjs_uint32 v24;
		tjs_uint32 *v26;
		tjs_uint32 *v27;
		tjs_int32 v28;
		int v29;
		tjs_int64 v30;
		tjs_uint32 *v31;
		int v32;
		tjs_uint16 v33;
		tjs_uint32 *v35;
		int v36;
		int v37;
		int v38;
		int v39;
		tjs_uint32 *v40;
		tjs_uint32 v41;
		tjs_uint32 v43;
		int v44;
		tjs_uint32 *v45;
		tjs_int32 v46;
		tjs_uint32 v47;
		tjs_uint32 v48;
		tjs_uint32 *v49;
		tjs_uint32 v50;
		tjs_uint32 v51;
		tjs_int32 v52;
		tjs_uint32 *v53;
		tjs_uint32 *v55;
		int v56;
		int v57;
		int v58;
		int v59;
		tjs_uint32 *v60;
		int v62;
		tjs_uint32 v63;
		tjs_uint32 v74;
		tjs_uint32 v75;
		tjs_uint32 *v87;
		tjs_uint32 *v90;
		v24 = upper - under;
		v26 = (tjs_uint32 *)dest_buffer;
		noise_current_seed = seed;
		v90 = (tjs_uint32 *)dest_buffer;
		if ( monocro )
		{
			if ( v24 == 255 )
			{
				for (tjs_int i = 0; i < dest_height; i += 1)
				{
					v90 = v26;
					v74 = v24;
					v27 = v26;
					v29 = noise_current_seed;
					for (v28 = dest_width; (tjs_uint32)v28 >= 3; v28 -= 3)
					{
						v30 = 1566083941ll * (tjs_uint32)v29;
						v29 = v30 + 1;
						(*((tjs_uint32*)&(v30)+1)) = ((v29 & 0xFF000000) >> 24) | ((v29 & 0xFF000000) >> 16) | ((v29 & 0xFF000000) >> 8) | ((*((tjs_uint32*)&(v30)+1)) & 0xFF000000);
						v27[0] = (*((tjs_uint32*)&(v30)+1));
						v31 = v27 + 1;
						(*((tjs_uint32*)&(v30)+1)) = ((v29 & 0xFF0000u) >> 16) | ((v29 & 0xFF0000u) >> 8) | (v29 & 0xFF0000) | ((*((tjs_uint32*)&(v30)+1)) & 0xFF000000);
						v31[0] = (*((tjs_uint32*)&(v30)+1));
						++v31;
						v31[0] = ((v29 & 0xFF00u) << 8 >> 16) | ((v29 & 0xFF00) << 8) | (v29 & 0xFF00) | ((*((tjs_uint32*)&(v30)+1)) & 0xFF000000);
						v27 = v31 + 1;
					}
					v24 = v74;
					v32 = 1566083941 * v29 + 1;
					noise_current_seed = v32;
					v87 = (tjs_uint32 *)v32;
					if ( v28 > 1 )
					{
						(*((tjs_uint8*)&(v33))) = 0;
						(*((tjs_uint8*)&(v33)+1)) = (*((tjs_uint8*)&(v87)+2));
						v24 = v32 & 0xFFFF0000;
						v26[0] = (v32 & 0xFFFF0000) | (((v32 & 0xFF0000) | v33) >> 8) | 0xFF000000;
						v90 = v26 + 1;
					}
					if ( v28 > 0 )
						v90[0] = (tjs_uint16)(v32 & 0xFF00) | (*((tjs_uint8*)&(v32)+1)) | (((v32 & 0xFF00) | 0xFFFF0000) << 8);
					v26 = (tjs_uint32 *)((tjs_uint8 *)v26 + (tjs_uint32)dest_pitch);
				}
			}
			else
			{
				for (tjs_int i = 0; i < dest_height; i += 1)
				{
					v35 = v90;
					v36 = dest_width;
					if ( (tjs_int32)dest_width >= 2 )
					{
						for (tjs_int j = 0; j < (dest_width >> 1); j += 1)
						{
							v37 = 1566083941 * seed + 1;
							v38 = v24 * (tjs_uint16)v37;
							noise_current_seed = v37;
							v39 = (tjs_uint8)(under + (v24 * ((v37 >> 16) & 0xFFFF) >> 16));
							v35[0] = (tjs_uint8)(under + (*((tjs_uint8*)&(v38)+2))) | (((tjs_uint8)(under + (*((tjs_uint8*)&(v38)+2))) | ((((tjs_uint8)under + (*((tjs_uint8*)&(v38)+2))) | 0xFFFFFF00) << 8)) << 8);
							v40 = v35 + 1;
							v41 = v39 | ((v39 | ((v39 | 0xFFFFFF00) << 8)) << 8);
							v40[0] = v41;
							v35 = v40 + 1;
							seed = noise_current_seed;
						}
						seed = noise_current_seed;
						v36 = dest_width - 2 * (dest_width >> 1);
					}
					for (tjs_int j = 0; j < v36; j += 1)
					{
						v43 = 1566083941 * seed + 1;
						noise_current_seed = v43;
						v44 = (tjs_uint8)(under + (v24 * (v43 >> 16) >> 16));
						v35[0] = v44 | ((v44 | ((v44 | 0xFFFFFF00) << 8)) << 8);
						++v35;
						seed = noise_current_seed;
					}
					seed = noise_current_seed;
					v90 = (tjs_uint32 *)((tjs_uint8 *)v90 + (tjs_uint32)dest_pitch);
				}
			}
		}
		else if ( v24 == 255 )
		{
			for (tjs_int i = 0; i < dest_height; i += 1)
			{
				v90 = v26;
				v75 = v24;
				v45 = v26;
				v47 = noise_current_seed;
				for (v46 = dest_width; (tjs_uint32)v46 >= 4; v46 -= 4)
				{
					v48 = 1566083941 * v47 + 1;
					v45[0] = (v48 >> 8) | 0xFF000000;
					v49 = v45 + 1;
					v50 = 1566083941 * v48 + 1;
					v49[0] = (v50 >> 8) | 0xFF000000;
					++v49;
					v51 = 1566083941 * v50 + 1;
					v49[0] = (v51 >> 8) | 0xFF000000;
					++v49;
					v47 = 1566083941 * v51 + 1;
					v49[0] = (v47 >> 8) | 0xFF000000;
					v45 = v49 + 1;
				}
				noise_current_seed = v47;
				v24 = v75;
				v52 = v46;
				if ( v46 <= 2 )
				{
					v53 = v90;
				}
				else
				{
					noise_current_seed = 1566083941 * noise_current_seed + 1;
					v53 = v26 + 1;
					v26[0] = ((tjs_uint32)noise_current_seed >> 8) | 0xFF000000;
					v90 = v26 + 1;
				}
				if ( v52 > 1 )
				{
					noise_current_seed = 1566083941 * noise_current_seed + 1;
					v53[0] = ((tjs_uint32)noise_current_seed >> 8) | 0xFF000000;
					++v53;
					v90 = v53;
				}
				if ( v52 > 0 )
				{
					noise_current_seed = 1566083941 * noise_current_seed + 1;
					v53[0] = ((tjs_uint32)noise_current_seed >> 8) | 0xFF000000;
				}
				v26 = (tjs_uint32 *)((tjs_uint8 *)v26 + (tjs_uint32)dest_pitch);
			}
		}
		else
		{
			for (tjs_int i = 0; i < dest_height; i += 1)
			{
				v55 = v90;
				v87 = v90;
				v56 = dest_width;
				if ( (tjs_int32)dest_width >= 2 )
				{
					for (tjs_int j = 0; j < (dest_width >> 1); j += 1)
					{
						v57 = 1566083941 * seed + 1;
						v58 = v57;
						v59 = 1566083941 * v57 + 1;
						noise_current_seed = 1566083941 * v59 + 1;
						v60 = v87;
						v87[0] = (tjs_uint8)(under + (v24 * (tjs_uint16)v59 >> 16)) | (((under + ((tjs_int32)(v24 * (tjs_uint16)v58) >> 16)) << 16) & 0xFFFF0000) | ((((tjs_uint16)under + (v24 * ((v58 >> 16) & 0xFFFF) >> 16)) << 8) & 0xFF00) | 0xFF000000;
						++v60;
						v60[0] = ((((tjs_uint16)under + (v24 * (tjs_uint16)v59 >> 16)) << 8) & 0xFF00) | (tjs_uint8)(under + (v24 * ((v59 >> 16) & 0xFFFF) >> 16)) | (((under + ((tjs_int32)(v24 * ((v59 >> 16) & 0xFFFF)) >> 16)) << 16) & 0xFFFF0000) | 0xFF000000;
						v55 = v60 + 1;
						v87 = v55;
						seed = noise_current_seed;
					}
					seed = noise_current_seed;
					v56 = dest_width - 2 * (dest_width >> 1);
				}
				for (tjs_int j = 0; j < v56; j += 1)
				{
					v62 = 1566083941 * seed + 1;
					noise_current_seed = 1566083941 * v62 + 1;
					v63 = (tjs_uint8)(under + (v24 * (tjs_uint16)noise_current_seed >> 16)) | (((under + ((tjs_int32)(v24 * (tjs_uint16)v62) >> 16)) << 16) & 0xFFFF0000) | ((((tjs_uint16)under + (v24 * ((v62 >> 16) & 0xFFFF) >> 16)) << 8) & 0xFF00);
					v55[0] = v63 | 0xFF000000;
					++v55;
					seed = noise_current_seed;
				}
				seed = noise_current_seed;
				v90 = (tjs_uint32 *)((tjs_uint8 *)v90 + (tjs_uint32)dest_pitch);
			}
		}
	}
	UpdateWholeLayerWithLayerObject(bmpobject_clo);
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
NCB_REGISTER_FUNCTION(initHaze, initHaze);
NCB_REGISTER_FUNCTION(doHaze, doHaze);
NCB_REGISTER_FUNCTION(endHaze, endHaze);
NCB_REGISTER_FUNCTION(Contrast, Contrast);
NCB_REGISTER_FUNCTION(Noise, Noise);
#if 0
NCB_REGISTER_FUNCTION(ReleaseLens, ReleaseLens);
NCB_REGISTER_FUNCTION(InitLens, InitLens);
NCB_REGISTER_FUNCTION(Lens, Lens);
NCB_REGISTER_FUNCTION(Blur, Blur);
NCB_REGISTER_FUNCTION(Smudge, Smudge);
#endif
