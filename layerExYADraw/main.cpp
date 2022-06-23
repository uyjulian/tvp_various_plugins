#include "ncbind/ncbind.hpp"
#include "LayerBitmapUtility.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

typedef struct layer_info_x_
{
	tjs_int imageWidth;
	tjs_int imageHeight;
	tjs_int mainImageBufferPitch;
	tjs_uint32 *mainImageBufferForWrite;
	int clipLeft;
	int clipTop;
	int clipWidth;
	int clipHeight;
} layer_info_x;


#ifndef LOBYTE
#define LOBYTE(x) (((x) >> 0) & 0xFF)
#endif
#ifndef HIBYTE
#define HIBYTE(x) (((x) >> 24) & 0xFF)
#endif
#define BYTE1(x) (((x) >> 8) & 0xFF)
#define BYTE2(x) (((x) >> 16) & 0xFF)

// FIXME: Figure out why anti aliasing and alpha blending are not working properly


static tjs_uint32 bounded_read(const layer_info_x *layerinfo, int index)
{
	if (index <= ((layerinfo->mainImageBufferPitch / 4) * (layerinfo->imageHeight - 1)) || index > 0)
	{
		return 0xFF000000;
	}
	return layerinfo->mainImageBufferForWrite[index];
}

static void bounded_write(const layer_info_x *layerinfo, int index, tjs_uint32 color)
{
	if (index <= ((layerinfo->mainImageBufferPitch / 4) * (layerinfo->imageHeight - 1)) || index > 0)
	{
		return;
	}
	layerinfo->mainImageBufferForWrite[index] = color;
}

unsigned int calc_pixel(unsigned int a1, unsigned int a2, unsigned int a3)
{
	return 0
	| ((a1 & 0xFF) + ((a3 * ((a2 & 0xFF) - (tjs_uint32)(a1 & 0xFF))) >> 16))
	| (
		(
			(tjs_uint32)BYTE1(a1)
				+ (
					(
						a3
						* (
							(tjs_uint32)BYTE1(a2) - (tjs_uint32)BYTE1(a1)
						)
					) >> 16
				)
		) << 8
	)
	| (
		(
			(tjs_uint32)BYTE2(a1)
				+ (
					(
						a3
						* (
							(tjs_uint32)BYTE2(a2) - (tjs_uint32)BYTE2(a1)
						)
					) >> 16
				)
		) << 16
	)
	| (
		(
			(tjs_uint32)HIBYTE(a1)
				+ (
					(
						a3
						* (
							(tjs_uint32)HIBYTE(a2) - (tjs_uint32)HIBYTE(a1)
						)
					) >> 16
				)
		) << 24
	);
}

void sub_10001B80(const layer_info_x *layerinfo, int x1, int x2, int y1, int y2, tjs_uint32 color)
{
	int v11; // eax
	int v12; // edx
	int v13; // ebp
	int v14; // esi
	int v15; // ecx
	int v16; // ebx
	int v18; // esi
	int v19; // esi
	int v21; // esi
	int v22; // eax
	int v23; // esi
	int v24; // ebx
	int v25; // edx
	int v29; // [esp+14h] [ebp-18h]
	int v31; // [esp+18h] [ebp-14h]
	int v32; // [esp+20h] [ebp-Ch]
	int v33; // [esp+20h] [ebp-Ch]
	int v34; // [esp+24h] [ebp-8h]
	int v35; // [esp+28h] [ebp-4h]
	int mainImageBufferPitch; // [esp+34h] [ebp+8h]
	int v37; // [esp+34h] [ebp+8h]

	mainImageBufferPitch = layerinfo->mainImageBufferPitch / 4;
	if ( x2 <= x1 )
		v11 = x1 - x2;
	else
		v11 = x2 - x1;
	if ( y2 <= y1 )
		v12 = y1 - y2;
	else
		v12 = y2 - y1;
	v13 = x1 << 16;
	v14 = y1 << 16;
	v15 = x2 << 16;
	v16 = y2 << 16;
	if ( v11 < v12 )
	{
		if ( v12 == 0 )
			v12 = 1;
		v33 = (v15 - v13) / v12;
		v22 = v14 >> 16;
		v23 = ((v16 - v14) >> 31) | 1;
		v24 = v12 * v23;
		v25 = mainImageBufferPitch * v22;
		v35 = v24 + v22;
		do
		{
			v31 = v25 + (v13 >> 16);
			bounded_write(layerinfo, v31, calc_pixel(color, bounded_read(layerinfo, v31), (v13 & 0xFFFF)));
			if ( (v13 >> 16) < layerinfo->clipWidth )
				bounded_write(layerinfo, v31 + 1, calc_pixel(color, bounded_read(layerinfo, v31 + 1), 0xFFFF - (v13 & 0xFFFF)));
			v13 += v33;
			v25 += mainImageBufferPitch * v23;
			--v12;
		}
		while ( v12 );
		v37 = (v13 >> 16) + mainImageBufferPitch * v35;
		bounded_write(layerinfo, v37, calc_pixel(color, bounded_read(layerinfo, v37), (v13 & 0xFFFF)));
		if ( (v13 >> 16) < layerinfo->clipWidth )
		{
			bounded_write(layerinfo, v37 + 1, calc_pixel(color, bounded_read(layerinfo, v37 + 1), 0xFFFF - (v13 & 0xFFFF)));
		}
	}
	else
	{
		if ( v11 == 0 )
			v11 = 1;
		v29 = v13 >> 16;
		v32 = ((v15 - v13) >> 31) | 1;
		v34 = (v16 - v14) / v11;
		do
		{
			v18 = v29 + mainImageBufferPitch * (v14 >> 16);
			bounded_write(layerinfo, v18, calc_pixel(color, bounded_read(layerinfo, v18), (v14 & 0xFFFF)));
			if ( (v14 >> 16) < layerinfo->clipHeight )
				bounded_write(layerinfo, mainImageBufferPitch + v18, calc_pixel(color, bounded_read(layerinfo, mainImageBufferPitch + v18), 0xFFFF - (v14 & 0xFFFF)));
			v29 += v32;
			v14 += v34;
			--v11;
		}
		while ( v11 );
		v19 = v29 + mainImageBufferPitch * (v14 >> 16);
		bounded_write(layerinfo, v19, calc_pixel(color, bounded_read(layerinfo, v19), (v14 & 0xFFFF)));
		if ( (v14 >> 16) < layerinfo->clipHeight )
		{
			v21 = mainImageBufferPitch + v19;
			bounded_write(layerinfo, v21, calc_pixel(color, bounded_read(layerinfo, v21), 0xFFFF - (v14 & 0xFFFF)));
		}
	}
}

void sub_10001E00(const layer_info_x *layerinfo, int x1, int x2, int y1, int y2, tjs_uint32 color, int a7)
{
	int v10; // edx
	int v11; // eax
	int v12; // edi
	int v13; // ebp
	int v14; // ebx
	int v15; // ecx
	int v16; // eax
	int v17; // ebx
	int v18; // ecx
	int v19; // edi
	tjs_uint32 v21; // ebx
	int v22; // eax
	tjs_uint32 v23; // edx
	int v24; // ebp
	tjs_uint32 v25; // ebx
	int v27; // ebp
	tjs_uint32 v28; // edx
	int v29; // ebp
	int v30; // ebp
	int v32; // ebp
	tjs_uint32 v33; // edx
	int v34; // eax
	tjs_uint32 v35; // ebx
	int v36; // edx
	tjs_uint32 v37; // ecx
	int v38; // eax
	tjs_uint32 v39; // edx
	int v40; // ebp
	int mainImageBufferPitch; // [esp+10h] [ebp-30h]
	int v42; // [esp+14h] [ebp-2Ch]
	int v43; // [esp+14h] [ebp-2Ch]
	int v45; // [esp+18h] [ebp-28h]
	int v48; // [esp+1Ch] [ebp-24h]
	int v49; // [esp+1Ch] [ebp-24h]
	int v50; // [esp+20h] [ebp-20h]
	tjs_uint32 v51; // [esp+24h] [ebp-1Ch]
	int v52; // [esp+24h] [ebp-1Ch]
	int v53; // [esp+28h] [ebp-18h]
	int v55; // [esp+2Ch] [ebp-14h]
	tjs_uint32 v56; // [esp+2Ch] [ebp-14h]
	tjs_uint32 v57; // [esp+30h] [ebp-10h]
	int v58; // [esp+30h] [ebp-10h]
	int v60; // [esp+34h] [ebp-Ch]
	tjs_uint32 v61; // [esp+38h] [ebp-8h]
	tjs_uint32 v62; // [esp+38h] [ebp-8h]
	int v63; // [esp+48h] [ebp+8h]
	tjs_uint32 v64; // [esp+48h] [ebp+8h]
	int v65; // [esp+48h] [ebp+8h]
	int v66; // [esp+48h] [ebp+8h]
	tjs_uint32 v68; // [esp+4Ch] [ebp+Ch]

	mainImageBufferPitch = layerinfo->mainImageBufferPitch / 4;
	if ( x2 <= x1 )
	{
		v10 = x1 - x2;
	}
	else
	{
		v10 = x2 - x1;
	}
	if ( y2 <= y1 )
	{
		v11 = y1 - y2;
	}
	else
	{
		v11 = y2 - y1;
	}
	v12 = x1 << 16;
	v13 = y1 << 16;
	v14 = x2 << 16;
	v15 = y2 << 16;
	if ( v10 < v11 )
	{
		if ( v11 == 0 )
			v11 = 1;
		v43 = ((v15 - v13) >> 31) | 1;
		v32 = y1;
		v45 = v12;
		v60 = (v14 - v12) / v11;
		v33 = 0;
		v56 = (color & 0xFF000000) / a7;
		if ( v11 <= a7 )
		{
			a7 = v11;
		}
		v65 = a7;
		if ( a7 )
		{
			v68 = color & 0xFFFFFF;
			v34 = mainImageBufferPitch * v32;
			do
			{
				v33 += v56;
				v35 = v68 | (v33 & 0xFF000000);
				v58 = v34 + (v12 >> 16);
				v61 = v35;
				bounded_write(layerinfo, v58, calc_pixel(v35, bounded_read(layerinfo, v58), (v12 & 0xFFFF)));
				if ( (v12 >> 16) < layerinfo->clipWidth )
					bounded_write(layerinfo, v58 + 1, calc_pixel(v35, bounded_read(layerinfo, v58 + 1), 0xFFFF - (v12 & 0xFFFF)));
				v12 += v60;
				v34 += mainImageBufferPitch * v43;
				--v65;
			}
			while ( v65 );
			v32 += a7 * v43;
			v45 = v12;
		}
		else
		{
			v35 = v61;
		}
		v66 = v11 - a7;
		if ( v11 != a7 )
		{
			v36 = mainImageBufferPitch * v32;
			v37 = HIBYTE(v35);
			v49 = mainImageBufferPitch * v32;
			v50 = mainImageBufferPitch * v43;
			v52 = v66 * v43 + v32;
			do
			{
				v38 = v36 + (v12 >> 16);
				v39 = bounded_read(layerinfo, v38);
				bounded_write(layerinfo, v38, (((BYTE1(v35) + (((v12 & 0xFFFF) * (BYTE1(v39) - (unsigned int)BYTE1(v35))) >> 16)) | (((BYTE2(v35) + (((v12 & 0xFFFF) * (BYTE2(v39) - (unsigned int)BYTE2(v35))) >> 16)) | ((v37 + (((v12 & 0xFFFF) * (HIBYTE(v39) - v37)) >> 16)) << 8)) << 8)) << 8) | ((v35 & 0xFF) + (((v12 & 0xFFFF) * ((v39 & 0xFF) - (v35 & 0xFF))) >> 16)));
				v37 = HIBYTE(v35);
				if ( (v12 >> 16) < layerinfo->clipWidth )
				{
					v37 = HIBYTE(v35);
					bounded_write(layerinfo, v38 + 1, (((BYTE1(v35) + (((0xFFFF - (v12 & 0xFFFF)) * (BYTE1(bounded_read(layerinfo, v38 + 1)) - (unsigned int)BYTE1(v35))) >> 16)) | (((BYTE2(v35) + (((0xFFFF - (v12 & 0xFFFF)) * (BYTE2(bounded_read(layerinfo, v38 + 1)) - (unsigned int)BYTE2(v35))) >> 16)) | ((HIBYTE(v35) + ((unsigned int)((0xFFFF - (v12 & 0xFFFF)) * (HIBYTE(bounded_read(layerinfo, v38 + 1)) - HIBYTE(v35))) >> 16)) << 8)) << 8)) << 8) | ((v35 & 0xFF) + (((0xFFFF - (v12 & 0xFFFF)) * (LOBYTE(bounded_read(layerinfo, v38 + 1)) - (v35 & 0xFF))) >> 16)));
				}
				v45 += v60;
				v36 = v50 + v49;
				v12 = v45;
				v66 -= 1;
				v49 += v50;
			}
			while ( v66 );
			v35 = v61;
			v32 = v52;
		}
		if ( v32 >= 0 && v32 <= layerinfo->clipHeight )
		{
			v40 = (v12 >> 16) + mainImageBufferPitch * v32;
			bounded_write(layerinfo, v40, calc_pixel(v35, bounded_read(layerinfo, v40), (v12 & 0xFFFF)));
			if ( (v12 >> 16) < layerinfo->clipWidth )
			{
				bounded_write(layerinfo, v40 + 1, calc_pixel(v35, bounded_read(layerinfo, v40 + 1), 0xFFFF - (v12 & 0xFFFF)));
			}
		}
	}
	else
	{
		if ( v10 == 0 )
			v10 = 1;
		v16 = (v15 - v13) / v10;
		v17 = v14 - v12;
		v18 = v12 >> 16;
		v19 = y1 << 16;
		v48 = y1 << 16;
		v53 = (v17 >> 31) | 1;
		v21 = 0;
		v42 = v18;
		v55 = v16;
		v62 = (color & 0xFF000000) / a7;
		v22 = v10;
		if ( v10 <= a7 )
		{
			a7 = v10;
		}
		v63 = a7;
		if ( a7 )
		{
			v23 = color & 0xFFFFFF;
			do
			{
				v24 = v18 + mainImageBufferPitch * (v19 >> 16);
				v21 += v62;
				v25 = v23 | (v21 & 0xFF000000);
				v57 = v25;
				bounded_write(layerinfo, v24, calc_pixel(v25, bounded_read(layerinfo, v24), (v19 & 0xFFFF)));
				if ( (v19 >> 16) < layerinfo->clipHeight )
					bounded_write(layerinfo, mainImageBufferPitch + v24, calc_pixel(v25, bounded_read(layerinfo, mainImageBufferPitch + v24), 0xFFFF - (v19 & 0xFFFF)));
				v42 += v53;
				v19 += v55;
				v18 = v42;
				v63 -= 1;
			}
			while ( v63 );
			v22 = v10;
			v48 = v19;
		}
		else
		{
			v25 = v57;
		}
		v64 = v22 - a7;
		if ( v64 )
		{
			v51 = HIBYTE(v25);
			do
			{
				v27 = v18 + mainImageBufferPitch * (v19 >> 16);
				bounded_write(layerinfo, v27, (((BYTE1(v25) + (((v19 & 0xFFFF) * ((BYTE1(bounded_read(layerinfo, v27)) & 0xFF) - (unsigned int)BYTE1(v25))) >> 16)) | (((BYTE2(v25) + (((v19 & 0xFFFF) * ((BYTE2(bounded_read(layerinfo, v27)) & 0xFF) - (unsigned int)BYTE2(v25))) >> 16)) | ((v51 + (((v19 & 0xFFFF) * (HIBYTE(bounded_read(layerinfo, v27)) - v51)) >> 16)) << 8)) << 8)) << 8) | ((v25 & 0xFF) + (((v19 & 0xFFFF) * ((bounded_read(layerinfo, v27) & 0xFF) - (unsigned int)(v25 & 0xFF))) >> 16)));
				if ( (v19 >> 16) < layerinfo->clipHeight )
				{
					v28 = bounded_read(layerinfo, mainImageBufferPitch + v27);
					bounded_write(layerinfo, mainImageBufferPitch + v27, (((BYTE1(v25) + (((0xFFFF - (v19 & 0xFFFF)) * (BYTE1(v28) - (unsigned int)BYTE1(v25))) >> 16)) | (((BYTE2(v25) + (((0xFFFF - (v19 & 0xFFFF)) * (BYTE2(v28) - (unsigned int)BYTE2(v25))) >> 16)) | ((v51 + (((0xFFFF - (v19 & 0xFFFF)) * (HIBYTE(v28) - v51)) >> 16)) << 8)) << 8)) << 8) | ((v25 & 0xFF) + (((0xFFFF - (v19 & 0xFFFF)) * ((v28 & 0xFF) - (unsigned int)(v25 & 0xFF))) >> 16)));
				}
				v42 += v53;
				v48 += v55;
				v19 = v48;
				v18 = v42;
				v64 -= 1;
			}
			while ( v64 );
			v25 = v57;
		}
		if ( v18 >= 0 && v18 <= layerinfo->clipWidth )
		{
			v29 = v18 + mainImageBufferPitch * (v19 >> 16);
			bounded_write(layerinfo, v29, calc_pixel(v25, bounded_read(layerinfo, v29), v19 & 0xFFFF));
			if ( (v19 >> 16) < layerinfo->clipHeight )
			{
				v30 = mainImageBufferPitch + v29;
				bounded_write(layerinfo, v30, calc_pixel(v25, bounded_read(layerinfo, v30), 0xFFFF - (v19 & 0xFFFF)));
			}
		}
	}
}

bool bound_check_inner(
				const layer_info_x *layerinfo,
				int left_bound,
				int top_bound,
				int a4,
				int right_bound,
				int bottom_bound,
				int *a7,
				int *a8)
{
	int v9; // eax
	int v11; // eax
	int v12; // eax
	int v13; // eax

	if ( (a4 & 1) != 0 )
	{
		v9 = top_bound + (bottom_bound - top_bound) * (layerinfo->clipLeft - left_bound) / (right_bound - left_bound);
		if ( v9 >= layerinfo->clipTop && v9 <= layerinfo->clipHeight )
		{
			*a7 = layerinfo->clipLeft;
			*a8 = v9;
			return true;
		}
	}
	if ( (a4 & 2) != 0 )
	{
		v11 = top_bound + (bottom_bound - top_bound) * (layerinfo->clipWidth - left_bound) / (right_bound - left_bound);
		if ( v11 >= layerinfo->clipTop && v11 <= layerinfo->clipHeight )
		{
			*a7 = layerinfo->clipWidth;
			*a8 = v11;
			return true;
		}
	}
	if ( (a4 & 4) != 0 )
	{
		v12 = left_bound + (right_bound - left_bound) * (layerinfo->clipTop - top_bound) / (bottom_bound - top_bound);
		if ( v12 >= layerinfo->clipLeft && v12 <= layerinfo->clipWidth )
		{
			*a7 = v12;
			*a8 = layerinfo->clipTop;
			return true;
		}
	}
	if ( (a4 & 8) != 0 )
	{
		v13 = left_bound + (right_bound - left_bound) * (layerinfo->clipHeight - top_bound) / (bottom_bound - top_bound);
		if ( v13 >= layerinfo->clipLeft && v13 <= layerinfo->clipWidth )
		{
			*a7 = v13;
			*a8 = layerinfo->clipHeight;
			return true;
		}
	}
	return false;
}

bool bound_check(const layer_info_x *layerinfo, int *left_bound, int *top_bound, int *right_bound, int *bottom_bound)
{
	int v8; // ecx
	int v11; // ebp

	v8 = 0;
	if ( *left_bound >= layerinfo->clipLeft )
	{
		if ( *left_bound > layerinfo->clipWidth )
			v8 = 2;
	}
	else
	{
		v8 = 1;
	}
	if ( *top_bound >= layerinfo->clipTop )
	{
		if ( *top_bound > layerinfo->clipHeight )
			v8 |= 8;
	}
	else
	{
		v8 |= 4;
	}
	v11 = 0;
	if ( *right_bound >= layerinfo->clipLeft )
	{
		if ( *right_bound > layerinfo->clipWidth )
			v11 = 2;
	}
	else
	{
		v11 = 1;
	}
	if ( *bottom_bound >= layerinfo->clipTop )
	{
		if ( *bottom_bound > layerinfo->clipHeight )
			v11 |= 8;
	}
	else
	{
		v11 |= 4;
	}
	return ((v8 + v11) != 0 || (v11 & v8) == 0) && (!v8 || bound_check_inner(layerinfo, *left_bound, *top_bound, v8, *right_bound, *bottom_bound, left_bound, top_bound)) && (!v11 || bound_check_inner(layerinfo, *left_bound, *top_bound, v11, *right_bound, *bottom_bound, right_bound, bottom_bound));
}

void sub_10001450(
	const layer_info_x *layerinfo,
	tTVPRect *updaterect,
	int cx,
	int cy,
	int cmin,
	int cmax,
	int lmin,
	int lmax,
	int emin,
	int emax,
	tjs_uint32 color)
{
	int v12 = TVPGetTickCount();
	int v13 = (32 * (((((v12 - 0x6D29735E) << 13) ^ (v12 - 0x6D29735E)) >> 7) ^ ((v12 - 0x6D29735E) << 13) ^ (v12 - 0x6D29735E))) ^ ((((v12 - 0x6D29735E) << 13) ^ (v12 - 0x6D29735E)) >> 7) ^ ((v12 - 0x6D29735E) << 13) ^ (v12 - 0x6D29735E);
	int v38 = lmin + ((((v13 & 0xffff0000) >> 16) * (lmax - lmin)) >> 16);
	if (v38)
	{
		int ediff = emax - emin;
		int cdiff = cmax - cmin;
		while (1)
		{
			int v16 = (((v13 << 13) ^ v13) >> 7) ^ (v13 << 13) ^ v13;
			int v17 = (32 * v16) ^ v16;
			int ccalc = cmin + ((cdiff * ((v17 & 0xffff0000) >> 16)) >> 16);
			int v18 = (((v17 << 13) ^ v17) >> 7) ^ (v17 << 13) ^ v17;
			int v19 = (32 * v18) ^ v18;
			int v21 = (((v19 << 13) ^ v19) >> 7) ^ (v19 << 13) ^ v19;
			v13 = (32 * v21) ^ v21;
			int ecalc = emin + ((ediff * ((v19 & 0xffff0000) >> 16)) >> 16);
			
			double v36 = (double)v13 * 2.328306436538696e-10 * 3.141592653589793 + (double)v13 * 2.328306436538696e-10 * 3.141592653589793;
			int left_bound = (int)((double)ccalc * cos(v36) + (double)cx);
			int top_bound = (int)((double)ccalc * sin(v36) + (double)cy);
			int right_bound = (int)((double)ecalc * cos(v36) + (double)cx);
			int bottom_bound = (int)((double)ecalc * sin(v36) + (double)cy);
			if (bound_check(layerinfo, &left_bound, &top_bound, &right_bound, &bottom_bound))
			{
				if (cdiff <= 0)
					sub_10001B80(layerinfo, left_bound, right_bound, top_bound, bottom_bound, color);
				else
					sub_10001E00(layerinfo, left_bound, right_bound, top_bound, bottom_bound, color, cdiff);
			}
			v38 -= 1;
			if (!v38)
				break;
		}
	}
	int clipLeft = cx - cmax;
	int clipTop = cy - cmax;
	int clipWidth = cx + cmax;
	int clipHeight = cy + cmax;
	if (clipLeft < layerinfo->clipLeft)
		clipLeft = layerinfo->clipLeft;
	if (clipTop < layerinfo->clipTop)
		clipTop = layerinfo->clipTop;
	if (clipWidth > layerinfo->clipWidth)
		clipWidth = layerinfo->clipWidth;
	if (clipHeight > layerinfo->clipHeight)
		clipHeight = layerinfo->clipHeight;
	updaterect->set_offsets(clipLeft, clipTop);
	updaterect->set_size(clipWidth, clipHeight);
}

class LayerLayerExYADraw
{
public:
	static tjs_error TJS_INTF_METHOD drawFocusLines(
		tTJSVariant *result,
		tjs_int numparams,
		tTJSVariant **param,
		iTJSDispatch2 *objthis)
	{
		if (numparams < 2)
			return -1004;

		int cx = *param[0]; // Center X coordinate
		int cy = *param[1]; // Center Y coordinate
		int cmin = 50; // Minimum distance from the center to the appearance of the line
		if (numparams > 2 && param[2]->Type() != tvtVoid)
			cmin = *param[2];
		int cmax = 100; // Maximum distance from the center to the appearance of the line
		if (numparams > 3 && param[3]->Type() != tvtVoid)
			cmax = *param[3];
		int lmin = 25; // Minimum number of lines
		if (numparams > 4 && param[4]->Type() != tvtVoid)
			lmin = *param[4];
		int lmax = 50; // Maximum number of lines
		if (numparams > 5 && param[5]->Type() != tvtVoid)
			lmax = *param[5];
		int emin = 2000; // Minimum distance from the center until the line disappears
		if (numparams > 6 && param[6]->Type() != tvtVoid)
			emin = *param[6];
		int emax = 2000; // Maximum distance from the center until the line disappears
		if (numparams > 7 && param[7]->Type() != tvtVoid)
			emax = *param[7];
		tjs_uint32 color = 0xFF000000; // Line color
		if (numparams > 8 && param[8]->Type() != tvtVoid)
			color = (tjs_uint32)(tTVInteger)*param[8];

		if (cmin > cmax)
		{
			int tmp = cmax;
			cmax = cmin;
			cmin = tmp;
		}

		if (lmin > lmax)
		{
			int tmp = lmax;
			lmax = lmin;
			lmin = tmp;
		}

		if (emin > emax)
		{
			int tmp = emax;
			emax = emin;
			emin = tmp;
		}

		if (objthis == NULL)
			TVPThrowExceptionMessage(TJS_W("Specify Layer or Bitmap class object"));
		tTJSVariant bmpobject = tTJSVariant(objthis, objthis);
		tTJSVariantClosure bmpobject_clo = bmpobject.AsObjectClosureNoAddRef();

		// Now get information (this will independ the bitmap)
		layer_info_x layerinfo;
		GetBitmapInformationFromObject(bmpobject_clo, true, &(layerinfo.imageWidth), &(layerinfo.imageHeight), &(layerinfo.mainImageBufferPitch), (tjs_uint8 **)&(layerinfo.mainImageBufferForWrite));
		if (!layerinfo.mainImageBufferForWrite)
			TVPThrowExceptionMessage(TJS_W("Specify Layer or Bitmap class object"));

		tTVPRect UpdateRect;
		tTVPRect ClipRect;
		tjs_int ImageLeft = 0;
		tjs_int ImageTop = 0;

		GetLayerInformationFromLayerObject(bmpobject_clo, NULL, NULL, &ClipRect, NULL, &ImageLeft, &ImageTop, NULL);
		layerinfo.clipLeft = ClipRect.left;
		layerinfo.clipTop = ClipRect.top;
		layerinfo.clipWidth = ClipRect.get_width();
		layerinfo.clipHeight = ClipRect.get_height();

		sub_10001450(&layerinfo, &UpdateRect, cx, cy, cmin, cmax, lmin, lmax, emin, emax, color);

		//UpdateLayerWithLayerObject(bmpobject_clo, &UpdateRect, &ImageLeft, &ImageTop);
		UpdateWholeLayerWithLayerObject(bmpobject_clo);
		return TJS_S_OK;
	}
};

NCB_ATTACH_CLASS(LayerLayerExYADraw, Layer)
{
#if 0
	// not used @ 0x10002570
	RawCallback("YAdrawLine", &Class::YAdrawLine, 0);
#endif
	// @ 0x100028F0
	RawCallback("drawFocusLines", &Class::drawFocusLines, 0);
};
