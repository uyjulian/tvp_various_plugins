
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ncbind.hpp"
#include "layer_util.h"
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
	tjs_real upperpow;
	tjs_real centerpow;
	tjs_real lowerpow;
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
				// XXX: Check if the value to be retrieved should be i or j
				waves_tmp[(3 * i) + j] = waves2.getRealValue(j);
			}
		}
	}
	tjs_real* waves = new tjs_real[0x4000];
	tjs_real v18 = 0.0;
	for (int i = 0; i < 0x4000; i += 1)
	{
		tjs_real v21 = 0.0;
		tjs_real *v22 = waves_tmp;
		for (int j = 0; j < c1; j += 1)
		{
			v21 += cos(v18 * v22[0] + v22[1] * v22[2]);
			v22 += 24;
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
	ncbPropAccessor dict(param[0]);
	// time: tTJSVariant::operator tjs_int() const; default -1
	haze_args.time = dict.getIntValue(TJS_W("time"), -1);
	// intime: tTJSVariant::operator tjs_int() const; default 800
	haze_args.intime = dict.getIntValue(TJS_W("intime"), 800);
	// outtime: tTJSVariant::operator tjs_int() const
	haze_args.outtime = dict.getIntValue(TJS_W("outtime"), haze_args.intime);
	// speed: tTJSVariant::operator tTVReal() const; default 0.001570796326794897
	haze_args.speed = dict.getRealValue(TJS_W("speed"), 0.001570796326794897);
	// cycle: tTJSVariant::operator tTVReal() const; default 6.0
	haze_args.cycle = dict.getIntValue(TJS_W("cycle"), 6.0);
	// upper: tTJSVariant::operator tjs_int() const; default -1
	haze_args.upper = dict.getIntValue(TJS_W("upper"), -1);
	// center: tTJSVariant::operator tjs_int() const; default -1
	haze_args.center = dict.getIntValue(TJS_W("center"), -1);
	// lower: tTJSVariant::operator tjs_int() const; default -1
	haze_args.lower = dict.getIntValue(TJS_W("lower"), -1);
	// upperpow: tTJSVariant::operator tTVReal() const; default (int64)0xFFFFF
	haze_args.upperpow = dict.getRealValue(TJS_W("upperpow"), std::numeric_limits<tjs_real>::quiet_NaN());
	haze_args.upperpow *= 1048575.0;
	// centerpow: tTJSVariant::operator tTVReal() const; default (int64)0xFFFFF
	haze_args.centerpow = dict.getRealValue(TJS_W("centerpow"), std::numeric_limits<tjs_real>::quiet_NaN());
	haze_args.centerpow *= 1048575.0;
	// lowerpow: tTJSVariant::operator tTVReal() const; default (int64)0xFFFFF
	haze_args.lowerpow = dict.getRealValue(TJS_W("lowerpow"), std::numeric_limits<tjs_real>::quiet_NaN());
	haze_args.lowerpow *= 1048575.0;
	// waves: array
	//  count: tTJSVariant::operator tjs_int() const; builtin variable of array
	tTJSVariant waves_var;
	if (dict.checkVariant(TJS_W("waves"), waves_var))
	{
		haze_args.waves = parse_waves(waves_var);
	}
	// lwaves: array
	//  count: tTJSVariant::operator tjs_int() const; builtin variable of array
	tTJSVariant lwaves_var;
	if (dict.checkVariant(TJS_W("lwaves"), lwaves_var))
	{
		haze_args.lwaves = parse_waves(lwaves_var);
	}
	haze_args.enabled = true;
	return TJS_S_OK;
}

// Not cleaned up
static int sub_100029C0(tjs_uint32 *a1, tjs_uint32 *a2, int a3, int a4)
{
	int result;
	int v5;
	int v6;
	tjs_uint32 *v8;
	tjs_uint32 *v9;
	tjs_uint32 *v10;
	tjs_uint32 *v11;
	int v12;

	result = a3;
	v5 = a3 >> 1;
	if ( a3 < 0 )
	{
		a2 -= v5;
		v6 = v5 + a4 - 2;
	}
	else
	{
		a1 += v5;
		v6 = a4 - v5 - 2;
	}
	a1[0] = a2[0];
	v8 = a1 + 1;
	v9 = a2 + 1;
	if ( a3 & 1 )
	{
		v10 = v8 + 1;
		v11 = v9 + 1;
		v12 = v6 - 1;
		while ( 1 )
		{
			v10[0] = ((v11[0] >> 1) & 0x7F7F7F7F) + ((v11[-1] >> 1) & 0x7F7F7F7F);
			++v10;
			++v11;
			if ( !--v12 )
				break;
		}
		result = ((v11[0] >> 1) & 0x7F7F7F7F) + (((tjs_uint32)v10[0] >> 1) & 0x7F7F7F7F);
		v10[0] = result;
	}
	else
	{
		while ( 1 )
		{
			result = *v9;
			*v8 = *v9;
			++v8;
			++v9;
			if ( !--v6 )
				break;
		}
	}
	return result;
}

// Not cleaned up
static int sub_100027C0(tjs_uint32 *a1, tjs_uint32 *a2, int a3, int a4)
{
	int result;
	int v5;
	int v6;
	tjs_uint32 *v8;
	tjs_uint32 *v9;
	tjs_uint32 *v10;
	tjs_uint32 *v11;
	int v12;

	result = a3;
	v5 = a3 >> 1;
	if ( a3 < 0 )
	{
		a2 -= v5;
		v6 = v5 + a4 - 2;
	}
	else
	{
		a1 += v5;
		v6 = a4 - v5 - 2;
	}
	a1[0] = a2[0];
	v8 = a1 + 1;
	v9 = a2 + 1;
	if ( a3 & 1 )
	{
		v10 = v8 + 1;
		v11 = v9 + 1;
		v12 = v6 - 1;
		while ( 1 )
		{
			v10[0] = ((v11[0] >> 2) & 0x3F3F3F3F)
					 + (((tjs_uint32)v10[0] >> 1) & 0x7F7F7F7F)
					 + ((v11[-1] >> 2) & 0x3F3F3F3F);
			++v10;
			++v11;
			if ( !--v12 )
				break;
		}
		result = ((v11[0] >> 1) & 0x7F7F7F7F) + (((tjs_uint32)v10[0] >> 1) & 0x7F7F7F7F);
		v10[0] = result;
	}
	else
	{
		while ( 1 )
		{
			result = ((v9[0] >> 1) & 0x7F7F7F7F) + (((tjs_uint32)v8[0] >> 1) & 0x7F7F7F7F);
			v8[0] = result;
			++v8;
			++v9;
			if ( !--v6 )
				break;
		}
	}
	return result;
}

static tjs_error TJS_INTF_METHOD
doHaze(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F284 100052e0
	if (numparams == 0) return TJS_E_BADPARAMCOUNT;
	tjs_int src_width, src_height, src_pitch;
	tjs_uint8 *src_buffer;
	tjs_int dest_width, dest_height, dest_pitch;
	tjs_uint8 *dest_buffer;
	//arg0 = dictionary
	ncbPropAccessor dict(param[0]);
	// src: layer
	tTJSVariant src;
	if (dict.checkVariant(TJS_W("src"), src))
	{
		get_layer_pointers(src, &src_buffer, &src_width, &src_height, &src_pitch);
	}
	// dest: layer
	tTJSVariant dest;
	if (dict.checkVariant(TJS_W("dest"), dest))
	{
		get_layer_pointers(dest, &dest_buffer, &dest_width, &dest_height, &dest_pitch);
	}
	// tick: tTJSVariant::operator tjs_int() const; default 0
	tjs_int tick = dict.getIntValue(TJS_W("tick"), 0);
	// per: tTJSVariant::operator tTVReal() const; default 0.0
	tjs_real per = dict.getRealValue(TJS_W("tick"), 0.0);
	// bgcolor: tTJSVariant::operator tjs_int() const; unused
	// blend: tTJSVariant::operator tjs_int() const
	int (*v76)(tjs_uint32 *, tjs_uint32 *, int, int);
	v76 = sub_100029C0;
	tjs_int blend = dict.getIntValue(TJS_W("blend"), 0);
	if (blend)
	{
		v76 = sub_100027C0;
	}
	// The actual update code (not cleaned up)
	tjs_int32 v27;
	tjs_int32 v33;
	{
		tjs_uint8* v20;
		tjs_uint32 v21;
		tjs_int64 v25;
		int v26;
		tjs_real v29;
		tjs_int64 v31;
		int v32;
		int v34;
		tjs_int32 v35;
		tjs_uint8* v36;
		tjs_int64 v39;
		int v40;
		int v41;
		tjs_int64 v44;
		int v45;
		int v53;
		int v54;
		int v55;
		int v56;
		int v57;
		tjs_int32 v58;
		tjs_int32 v59;
		tjs_uint8* v61;
		tjs_int32 v62;
		int v63;
		tjs_int32 v64;
		int v65;
		int v66;
		int v67;
		int v68;
		tjs_uint8* v69;
		tjs_uint8* v70;
		tjs_uint8* v71;
		tjs_uint32 v72;
		int v73;
		int v74;
		tjs_real v77;
		tjs_uint32 v78;
		int v79;
		int v80;
		int v81;
		int v97;
		v20 = dest_buffer;
		v77 = (tjs_real)((tjs_int64)((tjs_real)tick * haze_args.speed * 651.8986469044033) & 0x3FFF);
		v72 = src_pitch >> 2;
		v21 = dest_pitch >> 2;
		v69 = src_buffer;
		v33 = dest_height;
		v78 = dest_pitch >> 2;
		if ( haze_args.upper >= 0 || haze_args.lower >= 0 )
		{
			if ( haze_args.center < 0 )
			{
				v27 = haze_args.upper < 0 ? 0 : haze_args.upper;
				if ( haze_args.lower <= dest_height )
				{
					v57 = dest_height;
					if ( haze_args.lower >= 0 )
						v57 = haze_args.lower;
				}
				else
				{
					v57 = dest_height;
				}
				v64 = haze_args.upperpow;
				v79 = (haze_args.lowerpow - haze_args.upperpow) / (v57 - v27);
				v61 = dest_buffer + 4 * v21 * v27;
				v70 = src_buffer + 4 * v72 * v27;
				v67 = 4 * v21;
				v97 = 4 * v72;
				v54 = -v27;
				v73 = dest_height - v27 - 1;
				for (int i = v27; i < v57; i += 1)
				{
					v29 = (tjs_real)v64;
					if ( haze_args.lwaves )
					{
						v31 = (tjs_int64)(v29 * haze_args.lwaves[(tjs_int64)v77 & 0x3FFF] * per + 0.5);
						if ( i - (tjs_int32)v31 >= 0 )
						{
							if ( i < (tjs_int32)v31 + dest_height )
								v32 = v72 * -(tjs_int32)v31;
							else
								v32 = v72 * v73;
						}
						else
						{
							v32 = v72 * v54;
						}
					}
					else
					{
						v32 = 0;
					}
					v76(
						(tjs_uint32 *)v61,
						(tjs_uint32 *)(v70 + 4 * v32),
						(tjs_int32)(tjs_int64)(v29 * haze_args.waves[(tjs_int64)v77 & 0x3FFF] * per) >> 20,
						dest_width);
					v77 = haze_args.cycle + v77;
					v64 += v79;
					v70 += v97;
					v61 += v67;
					--v54;
					--v73;
				}
				v33 = v57 - v27;
			}
			else
			{
				v65 = dest_height;
				v62 = haze_args.upper < 0 ? 0 : haze_args.upper;
				if ( haze_args.lower <= dest_height )
					v65 = haze_args.lower;
				v68 = dest_height;
				if ( haze_args.center <= dest_height )
					v68 = haze_args.center;
				v34 = haze_args.centerpow;
				v58 = haze_args.upperpow;
				v80 = (haze_args.centerpow - haze_args.upperpow) / (v68 - v62);
				v36 = dest_buffer + 4 * v78 * v62;
				v71 = src_buffer + 4 * v72 * v62;
				v74 = -v62;
				v55 = dest_height - v62 - 1;
				for (v35 = v62; v35 < v68; v35 += 1)
				{
					if ( haze_args.lwaves )
					{
						v39 = (tjs_int64)(v58 * haze_args.lwaves[(tjs_int64)v77 & 0x3FFF] * per + 0.5);
						if ( v35 - (tjs_int32)v39 >= 0 )
						{
							if ( v35 < (tjs_int32)v39 + dest_height )
								v40 = v72 * -(tjs_int32)v39;
							else
								v40 = v72 * v55;
						}
						else
						{
							v40 = v72 * v74;
						}
					}
					else
					{
						v40 = 0;
					}
					v76(
						(tjs_uint32 *)v36,
						(tjs_uint32 *)(v71 + 4 * v40),
						(tjs_int32)(tjs_int64)(v58 * haze_args.waves[(tjs_int64)v77 & 0x3FFF] * per) >> 20,
						dest_width);
					v77 = haze_args.cycle + v77;
					v58 += v80;
					v36 += 4 * v78;
					v71 += 4 * v72;
					--v74;
					--v55;
				}
				v41 = v65;
				v59 = v34;
				v81 = (haze_args.lowerpow - v34) / (v65 - v68);
				v56 = -v35;
				for (; v35 < v65; v35 += 1)
				{
					if ( haze_args.lwaves )
					{
						v44 = (tjs_int64)(v59 * haze_args.lwaves[(tjs_int64)v77 & 0x3FFF] * per + 0.5);
						if ( v35 - (tjs_int32)v44 >= 0 )
						{
							if ( v35 < (tjs_int32)v44 + dest_height )
							{
								v45 = v72 * -(tjs_int32)v44;
							}
							else
							{
								v45 = v72 * (dest_height + v56 - 1);
							}
						}
						else
						{
							v45 = v72 * v56;
						}
					}
					else
					{
						v45 = 0;
					}
					v76(
						(tjs_uint32 *)v36,
						(tjs_uint32 *)(v71 + 4 * v45),
						(tjs_int32)(tjs_int64)(v59 * haze_args.waves[(tjs_int64)v77 & 0x3FFF] * per) >> 20,
						dest_width);
					v77 = haze_args.cycle + v77;
					v59 += v81;
					v36 += 4 * v78;
					v71 += 4 * v72;
					--v56;
				}
				v41 = v65;
				v27 = v62;
				v33 = v41 - v62;
			}
		}
		else
		{
			v66 = 4 * v21;
			v63 = 0;
			v53 = dest_height - 1;
			for (int i = 0; i < dest_height; i += 1)
			{
				if ( haze_args.lwaves )
				{
					v25 = (tjs_int64)(per * haze_args.lwaves[(tjs_int64)v77 & 0x3FFF]);
					if ( i - (tjs_int32)v25 >= 0 )
					{
						if ( i < (tjs_int32)v25 + dest_height )
							v26 = v72 * -(tjs_int32)v25;
						else
							v26 = v72 * v53;
					}
					else
					{
						v26 = v72 * v63;
					}
				}
				else
				{
					v26 = 0;
				}
				v76((tjs_uint32 *)v20, (tjs_uint32 *)(v69 + 4 * v26), (tjs_int64)(per * haze_args.waves[(tjs_int64)v77 & 0x3FFF]), dest_width);
				v77 = haze_args.cycle + v77;
				v20 += v66;
				--v53;
				v33 = dest_height;
				v69 += 4 * v72;
				--v63;
			}
			v27 = 0;
		}
	}
	update_layer(dest, 0, v27, dest_width, v33);
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
	tjs_uint8 *dest_buffer;
	//arg0 = dictionary
	ncbPropAccessor dict(param[0]);
	// layer: layer
	tTJSVariant dest;
	if (dict.checkVariant(TJS_W("layer"), dest))
	{
		get_layer_pointers(dest, &dest_buffer, &dest_width, &dest_height, &dest_pitch);
	}
	// level: tTJSVariant::operator tjs_int() const
	tjs_int level = dict.getIntValue(TJS_W("level"), 0);
	if (level)
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
		int v49 = dest_pitch >> 2;
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
				int vtmp = 255 * v7;
				tjs_uint32 *v52 = (tjs_uint32 *)&v20[4 * v7];
				v7 = 255 - level;
				for (tjs_int i = 0; i < (v22 - v7); i += 1)
				{
					tjs_int v24 = (vtmp - 255 * level) / v50;
					vtmp += 255;
					v52[i] = v24;
				}
			}
			if ( v7 < 256 )
			{
				tjs_uint32 *p = (tjs_uint32 *)&v20[4 * v7];
				for (int i = 0; i < 256 - v7; i += 1)
				{
					*p++ = 255;
				}
			}
		}
		tjs_uint32 *v52 = (tjs_uint32 *)dest_buffer;
		v49 *= 4;
		for (tjs_int i = 0; i < dest_height; i += 1)
		{
			for (tjs_int j = 0; j < dest_width; j += 1)
			{
				v52[j] = *(tjs_uint32 *)&v20[4 * (tjs_uint8)v52[j]] | ((*(tjs_uint32 *)&v20[4 * ((v52[j] >> 8) & 0xFF)] | (*(tjs_uint32 *)&v20[4 * ((v52[j] >> 16) & 0xFF)] << 8)) << 8) | v52[j] & 0xFF000000;
			}
			v52 = (tjs_uint32 *)((char *)v52 + v49);
		}
	}
	update_layer(dest, 0, 0, dest_width, dest_height);
	return TJS_S_OK;
}

static int noise_current_seed = 0;

static tjs_error TJS_INTF_METHOD
Noise(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000F3F8 10003f20; possible replacement by LayerExImage.noise
	if (numparams == 0) return TJS_E_BADPARAMCOUNT;
	tjs_int dest_width, dest_height, dest_pitch;
	tjs_uint8 *dest_buffer;
	//arg0 = dictionary
	ncbPropAccessor dict(param[0]);
	// layer: layer
	tTJSVariant dest;
	if (dict.checkVariant(TJS_W("layer"), dest))
	{
		get_layer_pointers(dest, &dest_buffer, &dest_width, &dest_height, &dest_pitch);
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
						(*((tjs_uint32*)&(v30)+1)) = ((v29 & 0xFF000000) >> 24) | ((v29 & 0xFF000000) >> 16) | ((v29 & 0xFF000000) >> 8) | (*((tjs_uint32*)&(v30)+1)) & 0xFF000000;
						v27[0] = (*((tjs_uint32*)&(v30)+1));
						v31 = v27 + 1;
						(*((tjs_uint32*)&(v30)+1)) = ((v29 & 0xFF0000u) >> 16) | ((v29 & 0xFF0000u) >> 8) | v29 & 0xFF0000 | (*((tjs_uint32*)&(v30)+1)) & 0xFF000000;
						v31[0] = (*((tjs_uint32*)&(v30)+1));
						++v31;
						v31[0] = ((v29 & 0xFF00u) << 8 >> 16) | ((v29 & 0xFF00) << 8) | v29 & 0xFF00 | (*((tjs_uint32*)&(v30)+1)) & 0xFF000000;
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
						v26[0] = v32 & 0xFFFF0000 | ((v32 & 0xFF0000 | v33) >> 8) | 0xFF000000;
						v90 = v26 + 1;
					}
					if ( v28 > 0 )
						v90[0] = (tjs_uint16)(v32 & 0xFF00) | (*((tjs_uint8*)&(v32)+1)) | ((v32 & 0xFF00 | 0xFFFF0000) << 8);
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
						v87[0] = (tjs_uint8)(under + (v24 * (tjs_uint16)v59 >> 16)) | ((under + ((tjs_int32)(v24 * (tjs_uint16)v58) >> 16)) << 16) & 0xFFFF0000 | (((tjs_uint16)under + (v24 * ((v58 >> 16) & 0xFFFF) >> 16)) << 8) & 0xFF00 | 0xFF000000;
						++v60;
						v60[0] = (((tjs_uint16)under + (v24 * (tjs_uint16)v59 >> 16)) << 8) & 0xFF00 | (tjs_uint8)(under + (v24 * ((v59 >> 16) & 0xFFFF) >> 16)) | ((under + ((tjs_int32)(v24 * ((v59 >> 16) & 0xFFFF)) >> 16)) << 16) & 0xFFFF0000 | 0xFF000000;
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
					v63 = (tjs_uint8)(under + (v24 * (tjs_uint16)noise_current_seed >> 16)) | ((under + ((tjs_int32)(v24 * (tjs_uint16)v62) >> 16)) << 16) & 0xFFFF0000 | (((tjs_uint16)under + (v24 * ((v62 >> 16) & 0xFFFF) >> 16)) << 8) & 0xFF00;
					v55[0] = v63 | 0xFF000000;
					++v55;
					seed = noise_current_seed;
				}
				seed = noise_current_seed;
				v90 = (tjs_uint32 *)((tjs_uint8 *)v90 + (tjs_uint32)dest_pitch);
			}
		}
	}
	update_layer(dest, 0, 0, dest_width, dest_height);
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
