
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ncbind.hpp"
#include "layer_util.h"

static struct
{
	tjs_int src_width, src_height, src_pitch;
	tjs_uint8 *src_buffer;
	tjs_int dest_width, dest_height, dest_pitch;
	tjs_uint8 *dest_buffer;
	iTJSDispatch2 *dest_dispatch;
	bool open;
	tjs_int type;
	tjs_int current_type;
	tjs_uint8 *buffer;
	tjs_uint8 *buffer_aligned;
	tjs_int pitch;
} slideopen_args;

static int sub_10001000(int a1, int dest_width, int dest_height)
{
	tjs_uint8* v3;
	int result;
	tjs_uint8* v5;
	int v6;
	uint32_t *v7;
	int v8;
	int *v9;
	int v10;
	int v11;
	uint32_t *v12;
	int v13;
	int v14;
	int v15;
	int v17;
	uint32_t *v18;
	int v19;
	int *v20;
	int v21;
	int v22;
	int v23;
	int v24;
	int v25;
	tjs_uint8* v26;
	int v28;
	unsigned int v29;
	int v31;
	int v32;

	v26 = slideopen_args.src_buffer;
	v29 = (unsigned int)slideopen_args.dest_pitch >> 2;
	v3 = slideopen_args.buffer_aligned;
	result = dest_width / 2;
	v5 = slideopen_args.dest_buffer;
	v28 = dest_width / 2;
	if ( slideopen_args.open )
	{
		if ( dest_height > 0 )
		{
			result -= a1;
			v31 = result;
			for (int v27 = 0; v27 < dest_height; v27 += 1)
			{
				v6 = 0;
				v7 = (uint32_t *)v5;
				v9 = (int *)(v3 + 4 * a1);
				v6 = result;
				for (v8 = 0; v8 < result; v8 += 1)
				{
					v10 = *v9;
					++v9;
					*v7 = v10;
					++v7;
				}
				result = v31;
				v12 = (uint32_t *)(v5 + 4 * v6);
				v6 = v28 + a1;
				for (v11 = 0; v11 < (v28 + a1 - v6); v11 += 1)
				{
					*v12 = *(uint32_t *)((tjs_uint8 *)v12 - v5 + v26);
					++v12;
				}
				result = v31;
				v13 = 4 * v6;
				for (v14 = 0; v14 < (dest_width - v6); v14 += 1)
				{
					v15 = v13;
					v13 += 4;
					*(uint32_t *)(v13 + v5 - 4) = *(uint32_t *)(v15 - 4 * a1 + v3);
				}
				v3 += 4 * v29;
				v5 += 4 * v29;
				v26 += 4 * v29;
			}
		}
	}
	else if ( dest_height > 0 )
	{
		result = a1;
		v17 = dest_width / 2 - a1;
		v32 = v17;
		for (int v30 = 0; v30 < dest_height; v30 += 1)
		{
			v18 = (uint32_t *)v5;
			v20 = (int *)(v26 + 4 * result);
			for (v19 = 0; v19 < v17; v19 += 1)
			{
				v21 = *v20;
				++v20;
				*v18 = v21;
				++v18;
			}
			v22 = v28 + result;
			if ( v28 + result < dest_width )
			{
				v23 = 4 * v22;
				for (v24 = 0; v24 < (dest_width - v22); v24 += 1)
				{
					v25 = v23 - 4 * result;
					v23 += 4;
					*(uint32_t *)(v23 + v5 - 4) = *(uint32_t *)(v25 + v26);
				}
				v17 = v32;
			}
			v5 += 4 * v29;
			v26 += 4 * v29;
		}
	}
	return result;
}

static int sub_100011B0(int a1, int dest_width, int dest_height)
{
	tjs_uint8* v3;
	int v4;
	int v5;
	unsigned int v6;
	int v7;
	int v8;
	uint32_t *v9;
	int v10;
	int v11;
	tjs_uint8* v12;
	int v13;
	uint32_t *v14;
	int v15;
	tjs_uint8* v16;
	int result;
	int v18;
	int v19;
	uint32_t *v20;
	int v21;
	int v22;
	tjs_uint8* v23;
	int v24;
	uint32_t *v25;
	tjs_uint8* v26;
	tjs_uint8* v27;
	int v28;
	uint32_t *v29;
	int v30;
	unsigned int v31;
	tjs_uint8* v32;
	int v33;
	int v34;
	int v35;
	int v36;
	int v37;
	int v38;

	v3 = slideopen_args.dest_buffer;
	v4 = a1;
	v5 = dest_height / 2;
	v6 = (unsigned int)slideopen_args.dest_pitch >> 2;
	v31 = (unsigned int)slideopen_args.dest_pitch >> 2;
	v33 = dest_height / 2;
	if ( a1 > dest_height / 2 )
	{
		v4 = dest_height / 2;
		a1 = dest_height / 2;
	}
	if ( slideopen_args.open )
	{
		v37 = 0;
		v7 = v5 - v4;
		v32 = slideopen_args.buffer_aligned + 4 * v4 * v6;
		if ( v5 - v4 <= 0 )
		{
		}
		else
		{
			v37 = v5 - v4;
			for (v34 = 0; v34 < (v5 - v4); v34 += 1)
			{
				v9 = (uint32_t *)v3;
				for (v8 = 0; v8 < dest_width; v8 += 1)
				{
					*v9 = *(uint32_t *)((tjs_uint8 *)v9 - v3 + v32);
					++v9;
				}
				v6 = v31;
				v3 += 4 * v6;
				v32 += 4 * v6;
			}
			v5 = dest_height / 2;
		}
		v10 = v4 + v5;
		v11 = v37;
		v12 = slideopen_args.src_buffer + 4 * v6 * v7;
		if ( v37 < v10 )
		{
			v13 = v10 - v37;
			v11 = v13 + v37;
			v38 = v13 + v37;
			for (v35 = 0; v35 < v13; v35 += 1)
			{
				v14 = (uint32_t *)v3;
				for (v15 = 0; v15 < dest_width; v15 += 1)
				{
					*v14 = *(uint32_t *)((tjs_uint8 *)v14 - v3 + v12);
					++v14;
				}
				v6 = v31;
				v11 = v38;
				v12 += 4 * v6;
				v3 += 4 * v6;
			}
		}
		v16 = slideopen_args.buffer_aligned + 4 * v6 * v33;
		result = dest_height;
		if ( v11 < dest_height )
		{
			for (v18 = 0; v18 < dest_height - v11; v18 += 1)
			{
				if ( dest_width > 0 )
				{
					v20 = (uint32_t *)v3;
					for (v19 = 0; v19 < dest_width; v19 += 1)
					{
						*v20 = *(uint32_t *)((tjs_uint8 *)v20 - v3 + v16);
						++v20;
					}
					v6 = v31;
				}
				result = 4 * v6;
				v16 += 4 * v6;
				v3 += 4 * v6;
			}
		}
	}
	else
	{
		v21 = v4 * v6;
		v22 = v5 - v4;
		v23 = slideopen_args.src_buffer + 4 * v4 * v6;
		if ( v22 > 0 )
		{
			for (v36 = 0; v36 < v22; v36 += 1)
			{
				if ( dest_width > 0 )
				{
					v25 = (uint32_t *)v3;
					for (v24 = 0; v24 < dest_width; v24 += 1)
					{
						*v25 = *(uint32_t *)((tjs_uint8 *)v25 - v3 + v23);
						++v25;
					}
					v4 = a1;
					v6 = v31;
				}
				v23 += 4 * v6;
				v3 += 4 * v6;
			}
		}
		v26 = v3 + 8 * v21;
		result = v4 + v33;
		v27 = slideopen_args.src_buffer + 4 * v6 * v33;
		if ( v4 + v33 < dest_height )
		{
			for (v28 = 0; v28 < (dest_height - result); v28 += 1)
			{
				v29 = (uint32_t *)v26;
				for (v30 = 0; v30 < dest_width; v30 += 1)
				{
					*v29 = *(uint32_t *)((tjs_uint8 *)v29 - v26 + v27);
					++v29;
				}
				v6 = v31;
				result = 4 * v6;
				v27 += 4 * v6;
				v26 += 4 * v6;
			}
		}
	}
	return result;
}

static int sub_100013D0(int a1, int dest_width, int dest_height)
{
	int v4;
	int result;
	int v6;
	int v7;
	int v8;
	int v9;
	int v10;
	int v11;
	int v12;
	tjs_uint8* v13;
	int v14;
	int v16;
	int v17;
	uint32_t *v18;
	tjs_uint8* v19;
	int v20;
	int v21;
	tjs_uint8* v22;
	int v23;
	int v24;
	tjs_uint8* v26;
	tjs_uint8* v27;
	tjs_uint8* v28;
	tjs_uint8* v29;
	int v30;
	int v31;
	int v32;
	int v33;
	int v34;
	tjs_uint8* v35;
	int v36;
	int v37;
	int v38;
	uint32_t *v39;

	v26 = slideopen_args.dest_buffer;
	v35 = slideopen_args.src_buffer;
	v24 = slideopen_args.dest_pitch / 4;
	v4 = dest_height / 2;
	v31 = dest_width / 2;
	v34 = dest_height / 2;
	v30 = dest_width / 2 + dest_height / 2 - a1;
	result = a1 / -2;
	v6 = a1 / 2;
	v38 = a1 / -2 + a1;
	v7 = a1 - a1 / 2;
	if ( !slideopen_args.open )
		return result;
	v29 = slideopen_args.buffer_aligned + 4 * (v7 + v24 * v6);
	v27 = slideopen_args.buffer_aligned + 4 * (v7 + v24 * v6);
	v8 = v24 * result;
	v28 = slideopen_args.buffer_aligned + 4 * (v31 + v4 + v24 * result + v38);
	if ( v6 >= 0 )
	{
		if ( v6 < dest_height )
			goto LABEL_7;
		v6 -= dest_height;
	}
	else
	{
		v6 += dest_height;
	}
	v9 = v7 + v24 * v6;
	v29 = slideopen_args.buffer_aligned + 4 * v9;
	v27 = slideopen_args.buffer_aligned + 4 * v9;
LABEL_7:
	if ( result >= 0 )
	{
		v10 = a1 / -2 + a1;
		if ( result < dest_height )
			goto LABEL_12;
		v10 = dest_height + v38;
		result -= dest_height;
		v38 += dest_height;
	}
	else
	{
		v10 = v38 - dest_height;
		result += dest_height;
		v38 -= dest_height;
	}
	v8 = v24 * result;
	v28 = slideopen_args.buffer_aligned + 4 * (v31 + v34 + v24 * result + v10);
LABEL_12:
	if ( dest_height > 0 )
	{
		v33 = v8;
		v32 = dest_height * v24;
		for (v37 = 0; v37 < dest_height; v37 += 1)
		{
			v11 = v30;
			v12 = 0;
			v13 = v26;
			v12 = v30;
			for (v36 = 0; v36 < v30; v36 += 1)
			{
				v13 += 4;
				*(uint32_t *)(v13 - 4) = *(uint32_t *)(v27 - v26 + v13 - 4);
			}
			v11 = v30;
			v14 = v11 + 2 * a1;
			if ( v14 > dest_width )
				v14 = dest_width;
			if ( v12 < v14 )
			{
				v16 = v35 - v26;
				v17 = v14 - v12;
				v18 = (uint32_t *)(v26 + 4 * v12);
				v12 += v17;
				for (v17 = 0; v17 < (v14 - v12); v17 += 1)
				{
					*v18 = *(uint32_t *)((char *)v18 + v16);
					++v18;
					v16 = v35 - v26;
				}
				v10 = v38;
			}
			if ( v12 < dest_width )
			{
				v19 = v26 + 4 * v12;
				v39 = (uint32_t *)v28;
				for (v20 = 0; v20 < (dest_width - v12); v20 += 1)
				{
					v19 += 4;
					*(uint32_t *)(v19 - 4) = *v39;
					++v39;
				}
			}
			--v30;
			v26 += 4 * v24;
			++v6;
			v27 += 4 * v24;
			--v10;
			v29 += 4 * v24;
			++result;
			v38 = v10;
			v28 = v28 + 4 * v24 - 4;
			v21 = v24 + v33;
			v33 += v24;
			v35 += 4 * v24;
			if ( v6 >= 0 )
			{
				if ( v6 < dest_height )
					goto LABEL_33;
				v6 -= dest_height;
				v22 = v29 - 4 * v32;
			}
			else
			{
				v6 += dest_height;
				v22 = 4 * v32 + v29;
			}
			v29 = v22;
			v27 = v22;
LABEL_33:
			if ( result < 0 )
			{
				v10 -= dest_height;
				result += dest_height;
				v38 = v10;
				v23 = v32 + v21;
LABEL_37:
				v33 = v23;
				v28 = slideopen_args.buffer_aligned + 4 * (v31 + v34 + v10 + v23);
				goto LABEL_38;
			}
			if ( result >= dest_height )
			{
				v10 += dest_height;
				result -= dest_height;
				v38 = v10;
				v23 = v21 - v32;
				goto LABEL_37;
			}
		}
	}
LABEL_38:
	return result;
}

static int sub_100016C0(int a1, int dest_width, int dest_height)
{
	int v4;
	int v5;
	unsigned int v6;
	int result;
	int v8;
	int v9;
	int v10;
	int v11;
	tjs_uint8* v12;
	int v13;
	tjs_uint8* v15;
	int v16;
	int v17;
	uint32_t *v18;
	tjs_uint8* v19;
	int v20;
	int v21;
	tjs_uint8* v22;
	int v23;
	tjs_uint8* v24;
	unsigned int v25;
	tjs_uint8* v26;
	tjs_uint8* v27;
	tjs_uint8* v28;
	int v29;
	int v30;
	int v31;
	int v32;
	int v33;
	int v34;
	int v35;
	int v36;
	int v37;
	uint32_t *v38;
	tjs_uint8* v39;
	int v40;
	tjs_uint8* v41;

	v27 = slideopen_args.dest_buffer;
	v39 = slideopen_args.src_buffer;
	v24 = slideopen_args.buffer_aligned;
	v4 = dest_height / 2;
	v30 = dest_width / 2;
	v34 = dest_height / 2;
	v29 = dest_width / 2 - dest_height / 2 - a1;
	v5 = a1 / -2;
	v6 = (unsigned int)slideopen_args.dest_pitch >> 2;
	v25 = (unsigned int)slideopen_args.dest_pitch >> 2;
	v32 = a1 / -2 + a1;
	result = a1 / 2;
	v8 = a1 - a1 / 2;
	if ( !slideopen_args.open )
		return result;
	v28 = slideopen_args.buffer_aligned + 4 * (v32 + v6 * v5);
	v41 = slideopen_args.buffer_aligned + 4 * (v32 + v6 * v5);
	v9 = v25 * result;
	v26 = slideopen_args.buffer_aligned + 4 * (v30 + v8 + v25 * result - v4);
	if ( v5 >= 0 )
	{
		if ( v5 < dest_height )
			goto LABEL_7;
		v5 -= dest_height;
	}
	else
	{
		v5 += dest_height;
	}
	v28 = slideopen_args.buffer_aligned + 4 * (v32 + v25 * v5);
	v41 = slideopen_args.buffer_aligned + 4 * (v32 + v25 * v5);
LABEL_7:
	if ( result >= 0 )
	{
		if ( result < dest_height )
			goto LABEL_12;
		v8 -= dest_height;
		result -= dest_height;
	}
	else
	{
		v8 += dest_height;
		result += dest_height;
	}
	v9 = v25 * result;
	v26 = slideopen_args.buffer_aligned + 4 * (v30 + v8 + v25 * result - v34);
LABEL_12:
	if ( dest_height > 0 )
	{
		v33 = v9;
		v31 = dest_height * v25;
		for (v40 = 0; v40 < dest_height; v40 += 1)
		{
			v10 = v29;
			v11 = 0;
			if ( v29 > 0 )
			{
				v12 = v27;
				v11 = v29;
				for (v35 = 0; v35 < v29; v35 += 1)
				{
					v12 += 4;
					*(uint32_t *)(v12 - 4) = *(uint32_t *)(v12 - v27 + v41 - 4);
				}
				v10 = v29;
			}
			v13 = v10 + 2 * a1;
			v36 = v13;
			if ( v13 > dest_width )
			{
				v13 = dest_width;
				v36 = dest_width;
			}
			if ( v11 < v13 )
			{
				v15 = v27 + 4 * v11;
				v16 = v39 - v27;
				v17 = v36 - v11;
				v11 += v17;
				v18 = (uint32_t *)v15;
				for (v37 = 0; v37 < v17; v37 += 1)
				{
					*v18 = *(uint32_t *)((char *)v18 + v16);
					++v18;
					v16 = v39 - v27;
				}
			}
			if ( v11 < dest_width )
			{
				v19 = v27 + 4 * v11;
				v38 = (uint32_t *)v26;
				for (v20 = 0; v20 < (dest_width - v11); v20 += 1)
				{
					v19 += 4;
					*(uint32_t *)(v19 - 4) = *v38;
					++v38;
				}
			}
			++v29;
			v27 += 4 * v25;
			++v5;
			v41 += 4 * v25;
			++v8;
			v28 += 4 * v25;
			++result;
			v26 += 4 * v25 + 4;
			v21 = v25 + v33;
			v33 += v25;
			v39 += 4 * v25;
			if ( v5 >= 0 )
			{
				if ( v5 < dest_height )
					goto LABEL_33;
				v5 -= dest_height;
				v22 = v28 - 4 * v31;
			}
			else
			{
				v5 += dest_height;
				v22 = 4 * v31 + v28;
			}
			v28 = v22;
			v41 = v22;
LABEL_33:
			if ( result < 0 )
			{
				v8 += dest_height;
				result += dest_height;
				v23 = v31 + v21;
LABEL_37:
				v33 = v23;
				v26 = v24 + 4 * (v30 + v8 + v23 - v34);
				goto LABEL_38;
			}
			if ( result >= dest_height )
			{
				v8 -= dest_height;
				result -= dest_height;
				v23 = v21 - v31;
				goto LABEL_37;
			}
		}
	}
LABEL_38:
	return result;
}


static tjs_error TJS_INTF_METHOD
finishSlideOpen(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000A0E0 10002330
	if (slideopen_args.buffer)
	{
		free(slideopen_args.buffer);
		slideopen_args.buffer = NULL;
	}
	return TJS_S_OK;
}

static tjs_error TJS_INTF_METHOD
drawSlideOpen(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000A15C 100020d0
	if (!numparams) return TJS_E_BADPARAMCOUNT;
	//arg1 = tTVReal tTJSVariant::AsReal() const
	tjs_real a1 = param[0]->AsReal();
	if (!slideopen_args.open)
	{
		a1 = 1.0 - a1;
	}
	tjs_real a2 = (double)(slideopen_args.dest_width / 2) * a1 + 0.5;
	tjs_int a3 = (signed __int64)a2;
	switch (slideopen_args.type)
	{
		case 0:
			sub_10001000(a3, slideopen_args.dest_width, slideopen_args.dest_height);
			break;
		case 1:
			sub_100011B0(a3, slideopen_args.dest_width, slideopen_args.dest_height);
			break;
		case 2:
			sub_100013D0((signed __int64)((double)a3 * 1.75), slideopen_args.dest_width, slideopen_args.dest_height);
			break;
		case 3:
			sub_100016C0((signed __int64)((double)a3 * 1.75), slideopen_args.dest_width, slideopen_args.dest_height);
			break;
		default:
			break;
	}
	update_layer(slideopen_args.dest_dispatch, 0, 0, slideopen_args.dest_width, slideopen_args.dest_height);
	return TJS_S_OK;
}

static tjs_error TJS_INTF_METHOD
initSlideOpen(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000A1D8 10001c70
	if (!numparams) return TJS_E_BADPARAMCOUNT;

	//arg0 = Slide Open plugin object/dictionary
	ncbPropAccessor dict(param[0]->AsObjectNoAddRef());
	// open: tTJSVariant::operator tjs_int() const
	TVPAddLog(TJS_W("0.5"));
	slideopen_args.open = dict.getIntValue(TJS_W("open"), 1);
	// dest: layer pointer
	tTJSVariant dest;
	TVPAddLog(TJS_W("1"));
	if (dict.checkVariant(TJS_W("dest"), dest))
	{
		get_layer_pointers(dest, &slideopen_args.dest_buffer, &slideopen_args.dest_width, &slideopen_args.dest_height, &slideopen_args.dest_pitch);
		slideopen_args.dest_dispatch = dest.AsObject();
	}
	else
	{
		return TJS_E_FAIL;
	}
	TVPAddLog(TJS_W("2"));
	// src: layer pointer
	tTJSVariant src;
	if (dict.checkVariant(TJS_W("src"), src))
	{
		get_layer_pointers(src, &slideopen_args.src_buffer, &slideopen_args.src_width, &slideopen_args.src_height, &slideopen_args.src_pitch);
	}
	else
	{
		return TJS_E_FAIL;
	}
	TVPAddLog(TJS_W("3"));
	// type: tTJSVariant::operator tjs_int() const
	tTJSVariant type_var;
	if (dict.checkVariant(TJS_W("type"), type_var))
	{
		slideopen_args.type = dict.getIntValue(TJS_W("type"));
	}
	TVPAddLog(TJS_W("4"));

	if (slideopen_args.src_width != slideopen_args.dest_width || slideopen_args.src_height != slideopen_args.dest_height || slideopen_args.src_pitch != slideopen_args.dest_pitch)
	{
		return TJS_E_FAIL;
	}
	if (slideopen_args.open)
	{
		slideopen_args.buffer = malloc(4 * slideopen_args.dest_height * slideopen_args.dest_width + 4);
		slideopen_args.buffer_aligned = (tjs_uint8*)((char *)slideopen_args.buffer - ((size_t)slideopen_args.buffer & 3) + 4);
		if (slideopen_args.dest_pitch < 1)
		{
			slideopen_args.buffer_aligned -= slideopen_args.dest_pitch * (slideopen_args.dest_height - 1);
		}
		uint8_t *v21 = slideopen_args.dest_buffer;
		uint32_t *v22 = (uint32_t *)(slideopen_args.buffer_aligned);
		tjs_uint32 v33 = (tjs_uint32)slideopen_args.dest_pitch >> 2;
		for (tjs_int i = 0; i < slideopen_args.dest_height; i += 1)
		{
			tjs_uint32* v25 = v22;
			for (tjs_int j = 0; j < slideopen_args.dest_width; j += 1)
			{
				*v25 = *(uint32_t *)(v25 - v22 + v21);
				++v25;
			}
			v22 += v33;
			v21 += 4 * v33;
		}
	}
	if ( slideopen_args.type < 0 )
	{
		slideopen_args.type = TVPGetTickCount() & 3;
		if ( slideopen_args.current_type != slideopen_args.type )
			goto LABEL_52;
		slideopen_args.type += 1;
	}
	slideopen_args.type &= 3u;
LABEL_52:
	if ( !slideopen_args.open )
	{
		slideopen_args.type &= 1u;
	}
	slideopen_args.current_type = slideopen_args.type;
	return TJS_S_OK;
}

NCB_REGISTER_FUNCTION(finishSlideOpen, finishSlideOpen);
NCB_REGISTER_FUNCTION(drawSlideOpen, drawSlideOpen);
NCB_REGISTER_FUNCTION(initSlideOpen, initSlideOpen);
