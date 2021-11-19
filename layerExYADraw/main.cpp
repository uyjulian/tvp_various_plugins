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


#define LAST_IND(x, part_type) (sizeof(x) / sizeof(part_type) - 1)
#define HIGH_IND(x, part_type) LAST_IND(x, part_type)
#define LOW_IND(x, part_type) 0

#define BYTEn(x, n) (*((tjs_uint8 *)&(x) + n))
#define WORDn(x, n) (*((tjs_uint16 *)&(x) + n))
#define DWORDn(x, n) (*((tjs_uint32 *)&(x) + n))

#ifndef LOBYTE
#define LOBYTE(x) BYTEn(x, LOW_IND(x, tjs_uint8))
#endif
#ifndef LOWORD
#define LOWORD(x) WORDn(x, LOW_IND(x, tjs_uint16))
#endif
#define LODWORD(x) DWORDn(x, LOW_IND(x, tjs_uint32))
#ifndef HIBYTE
#define HIBYTE(x) BYTEn(x, HIGH_IND(x, tjs_uint8))
#endif
#ifndef HIWORD
#define HIWORD(x) WORDn(x, HIGH_IND(x, tjs_uint16))
#endif
#define HIDWORD(x) DWORDn(x, HIGH_IND(x, tjs_uint32))
#define BYTE1(x) BYTEn(x, 1)
#define BYTE2(x) BYTEn(x, 2)
#define BYTE3(x) BYTEn(x, 3)
#define BYTE4(x) BYTEn(x, 4)
#define BYTE5(x) BYTEn(x, 5)
#define BYTE6(x) BYTEn(x, 6)
#define BYTE7(x) BYTEn(x, 7)
#define BYTE8(x) BYTEn(x, 8)
#define BYTE9(x) BYTEn(x, 9)
#define BYTE10(x) BYTEn(x, 10)
#define BYTE11(x) BYTEn(x, 11)
#define BYTE12(x) BYTEn(x, 12)
#define BYTE13(x) BYTEn(x, 13)
#define BYTE14(x) BYTEn(x, 14)
#define BYTE15(x) BYTEn(x, 15)
#define WORD1(x) WORDn(x, 1)
#define WORD2(x) WORDn(x, 2)
#define WORD3(x) WORDn(x, 3)
#define WORD4(x) WORDn(x, 4)
#define WORD5(x) WORDn(x, 5)
#define WORD6(x) WORDn(x, 6)
#define WORD7(x) WORDn(x, 7)

unsigned int calc_pixel(unsigned int a1, unsigned int a2, int a3)
{
	return (((BYTE1(a1) + ((a3 * (BYTE1(a2) - (unsigned int)BYTE1(a1))) >> 16)) | (((BYTE2(a1) + ((a3 * (BYTE2(a2) - (unsigned int)BYTE2(a1))) >> 16)) | ((HIBYTE(a1) + ((unsigned int)(a3 * (HIBYTE(a2) - HIBYTE(a1))) >> 16)) << 8)) << 8)) << 8) | ((tjs_uint8)a1 + ((a3 * ((tjs_uint8)a2 - (unsigned int)(tjs_uint8)a1)) >> 16));
}

void sub_10001B80(int a1, int a2, int a3, layer_info_x *layerinfo, int a5, int a6)
{
	tjs_uint32 *mainImageBufferForWrite;
	bool v9;
	int v11;
	int v12;
	int v13;
	int v14;
	int v15;
	int v16;
	int v17;
	int v18;
	int v19;
	int v21;
	int v22;
	int v23;
	int v24;
	int v25;
	int v26;
	int v27;
	int v28;
	int v29;
	int v30;
	int v31;
	int v32;
	int v33;
	int v34;
	int v35;
	int v36;
	int v37;

	mainImageBufferForWrite = layerinfo->mainImageBufferForWrite;
	v9 = a3 <= a5;
	v36 = (int)layerinfo->mainImageBufferPitch >> 2;
	if (v9)
		v11 = a5 - a3;
	else
		v11 = a3 - a5;
	v26 = v11;
	if (a1 <= a2)
		v12 = a2 - a1;
	else
		v12 = a1 - a2;
	v13 = a5 << 16;
	v14 = a2 << 16;
	v15 = a3 << 16;
	v16 = a1 << 16;
	v28 = v12;
	if (v11 < v12)
	{
		if (!v12)
			v28 = 1;
		v27 = v28;
		v33 = (v15 - v13) / v28;
		v22 = v14 >> 16;
		v23 = ((v16 - v14) >> 31) | 1;
		v24 = v28 * v23;
		v25 = v36 * v22;
		v30 = v36 * v22;
		v35 = v24 + v22;
		while (1)
		{
			v31 = v25 + (v13 >> 16);
			mainImageBufferForWrite[v31] = calc_pixel(a6, mainImageBufferForWrite[v31], (tjs_uint16)v13);
			if (v13 >> 16 < layerinfo->clipWidth)
				mainImageBufferForWrite[v31 + 1] = calc_pixel(
					a6,
					mainImageBufferForWrite[v31 + 1],
					0xFFFF - (tjs_uint16)v13);
			v13 += v33;
			v30 += v36 * v23;
			if (!--v27)
				break;
			v25 = v30;
		}
		v37 = (v13 >> 16) + v36 * v35;
		mainImageBufferForWrite[v37] = calc_pixel(a6, mainImageBufferForWrite[v37], (tjs_uint16)v13);
		if (v13 >> 16 < layerinfo->clipWidth)
		{
			mainImageBufferForWrite[v37 + 1] = calc_pixel(a6, mainImageBufferForWrite[v37 + 1], 0xFFFF - (tjs_uint16)v13);
		}
	}
	else
	{
		if (!v11)
			v26 = 1;
		v29 = v13 >> 16;
		v32 = ((v15 - v13) >> 31) | 1;
		v17 = v14;
		v34 = (v16 - v14) / v26;
		do
		{
			v18 = v29 + v36 * (v17 >> 16);
			mainImageBufferForWrite[v18] = calc_pixel(a6, mainImageBufferForWrite[v18], (tjs_uint16)v17);
			if (v17 >> 16 < layerinfo->clipHeight)
				mainImageBufferForWrite[v36 + v18] = calc_pixel(
					a6,
					mainImageBufferForWrite[v36 + v18],
					0xFFFF - (tjs_uint16)v17);
			v29 += v32;
			v17 += v34;
			--v26;
		} while (v26);
		v19 = v29 + v36 * (v17 >> 16);
		mainImageBufferForWrite[v19] = calc_pixel(a6, mainImageBufferForWrite[v19], (tjs_uint16)v17);
		if (v17 >> 16 < layerinfo->clipHeight)
		{
			v21 = v36 + v19;
			mainImageBufferForWrite[v21] = calc_pixel(a6, mainImageBufferForWrite[v21], 0xFFFF - (tjs_uint16)v17);
		}
	}
}

int sub_10001E00(int a1, int a2, int a3, layer_info_x *layerinfo, int a5, int a6, int a7)
{
	tjs_uint32 *mainImageBufferForWrite;
	int v10;
	int v11;
	int v12;
	int v13;
	int v14;
	int v15;
	int v16;
	int v17;
	int v18;
	int v19;
	int v20;
	int v21;
	int v22;
	int v23;
	int v24;
	unsigned int v25;
	int result;
	int v27;
	unsigned int v28;
	int v29;
	int v30;
	int v31;
	int v32;
	int v33;
	int v34;
	unsigned int v35;
	int v36;
	unsigned int v37;
	int v38;
	unsigned int v39;
	int v40;
	int v41;
	int v42;
	int v43;
	int v44;
	int v45;
	int v46;
	int v47;
	int v48;
	int v49;
	int v50;
	unsigned int v51;
	int v52;
	int v53;
	int v54;
	int v55;
	unsigned int v56;
	unsigned int v57;
	int v58;
	int v59;
	int v60;
	unsigned int v61;
	unsigned int v62;
	int v63;
	unsigned int v64;
	int v65;
	int v66;
	int i;
	int v68;

	mainImageBufferForWrite = layerinfo->mainImageBufferForWrite;
	v41 = (int)layerinfo->mainImageBufferPitch >> 2;
	if (a1 <= a2)
	{
		v44 = a2 - a1;
		v10 = a2 - a1;
	}
	else
	{
		v10 = a1 - a2;
		v44 = a1 - a2;
	}
	if (a3 <= a5)
		v11 = a5 - a3;
	else
		v11 = a3 - a5;
	v12 = a2 << 16;
	v13 = a5 << 16;
	v14 = a1 << 16;
	v15 = a3 << 16;
	v47 = v11;
	if (v10 < v11)
	{
		if (!v11)
			v47 = 1;
		v43 = ((v15 - v13) >> 31) | 1;
		v31 = a7;
		v32 = (tjs_int16)a5;
		v45 = v12;
		v60 = (v14 - v12) / v47;
		v33 = 0;
		v56 = (a6 & 0xFF000000) / a7;
		if (v47 <= a7)
		{
			a7 = v47;
			v31 = v47;
		}
		v65 = v31;
		if (v31)
		{
			v68 = a6 & 0xFFFFFF;
			v34 = v41 * v32;
			v46 = v41 * v32;
			while (1)
			{
				v54 = v56 + v33;
				v35 = v68 | ((v56 + v33) & 0xFF000000);
				v58 = v34 + (v12 >> 16);
				v61 = v35;
				mainImageBufferForWrite[v58] = calc_pixel(v35, mainImageBufferForWrite[v58], (tjs_uint16)v12);
				if (v12 >> 16 < layerinfo->clipWidth)
					mainImageBufferForWrite[v58 + 1] = calc_pixel(
						v35,
						mainImageBufferForWrite[v58 + 1],
						0xFFFF - (tjs_uint16)v12);
				v12 += v60;
				v46 += v41 * v43;
				if (!--v65)
					break;
				v34 = v46;
				v33 = v54;
			}
			v32 += a7 * v43;
			v31 = a7;
			v45 = v12;
		}
		else
		{
			v35 = v61;
		}
		result = v47 - v31;
		v66 = v47 - v31;
		if (v47 != v31)
		{
			v36 = v41 * v32;
			v37 = HIBYTE(v35);
			v49 = v41 * v32;
			v50 = v41 * v43;
			v52 = v66 * v43 + v32;
			do
			{
				v38 = v36 + (v12 >> 16);
				v39 = mainImageBufferForWrite[v38];
				mainImageBufferForWrite[v38] = (((BYTE1(v35) + (((tjs_uint16)v12 * (BYTE1(v39) - (unsigned int)BYTE1(v35))) >> 16)) | (((BYTE2(v35) + (((tjs_uint16)v12 * (BYTE2(v39) - (unsigned int)BYTE2(v35))) >> 16)) | ((v37 + (((tjs_uint16)v12 * (HIBYTE(v39) - v37)) >> 16)) << 8)) << 8)) << 8) | ((tjs_uint8)v35 + (((tjs_uint16)v12 * ((tjs_uint8)v39 - (unsigned int)(tjs_uint8)v35)) >> 16));
				v37 = HIBYTE(v35);
				if (v12 >> 16 < layerinfo->clipWidth)
				{
					v37 = HIBYTE(v35);
					mainImageBufferForWrite[v38 + 1] = (((BYTE1(v35) + (((0xFFFF - (tjs_uint16)v12) * (BYTE1(mainImageBufferForWrite[v38 + 1]) - (unsigned int)BYTE1(v35))) >> 16)) | (((BYTE2(v35) + (((0xFFFF - (tjs_uint16)v12) * (BYTE2(mainImageBufferForWrite[v38 + 1]) - (unsigned int)BYTE2(v35))) >> 16)) | ((HIBYTE(v35) + ((unsigned int)((0xFFFF - (tjs_uint16)v12) * (HIBYTE(mainImageBufferForWrite[v38 + 1]) - HIBYTE(v35))) >> 16)) << 8)) << 8)) << 8) | ((tjs_uint8)v35 + (((0xFFFF - (tjs_uint16)v12) * (LOBYTE(mainImageBufferForWrite[v38 + 1]) - (unsigned int)(tjs_uint8)v35)) >> 16));
				}
				v45 += v60;
				v36 = v50 + v49;
				v12 = v45;
				result = v66 - 1;
				v66 = result;
				v49 += v50;
			} while (result);
			v35 = v61;
			v32 = v52;
		}
		if (v32 >= 0)
		{
			if (v32 <= layerinfo->clipHeight)
			{
				v40 = (v12 >> 16) + v41 * v32;
				mainImageBufferForWrite[v40] = calc_pixel(v35, mainImageBufferForWrite[v40], (tjs_uint16)v12);
				result = v12 >> 16;
				if (v12 >> 16 < layerinfo->clipWidth)
				{
					result = calc_pixel(v35, mainImageBufferForWrite[v40 + 1], 0xFFFF - (tjs_uint16)v12);
					mainImageBufferForWrite[v40 + 1] = result;
				}
			}
		}
	}
	else
	{
		if (!v10)
			v44 = 1;
		v16 = (v15 - v13) / v44;
		v17 = v14 - v12;
		v18 = v12 >> 16;
		v19 = a5 << 16;
		v48 = a5 << 16;
		v20 = a7;
		v53 = (v17 >> 31) | 1;
		v21 = 0;
		v42 = v18;
		v55 = v16;
		v62 = (a6 & 0xFF000000) / a7;
		v22 = v44;
		if (v44 <= a7)
		{
			a7 = v44;
			v20 = v44;
		}
		v63 = v20;
		if (v20)
		{
			v23 = a6 & 0xFFFFFF;
			for (i = a6 & 0xFFFFFF;; v23 = i)
			{
				v24 = v18 + v41 * (v19 >> 16);
				v59 = v62 + v21;
				v25 = v23 | ((v62 + v21) & 0xFF000000);
				v57 = v25;
				mainImageBufferForWrite[v24] = calc_pixel(v25, mainImageBufferForWrite[v24], (tjs_uint16)v19);
				if (v19 >> 16 < layerinfo->clipHeight)
					mainImageBufferForWrite[v41 + v24] = calc_pixel(
						v25,
						mainImageBufferForWrite[v41 + v24],
						0xFFFF - (tjs_uint16)v19);
				v42 += v53;
				v19 += v55;
				v18 = v42;
				if (!--v63)
					break;
				v21 = v59;
			}
			v22 = v44;
			v20 = a7;
			v48 = v19;
		}
		else
		{
			v25 = v57;
		}
		result = v22 - v20;
		v64 = result;
		if (result)
		{
			v51 = HIBYTE(v25);
			do
			{
				v27 = v18 + v41 * (v19 >> 16);
				mainImageBufferForWrite[v27] = (((BYTE1(v25) + (((tjs_uint16)v19 * ((tjs_uint8)BYTE1(mainImageBufferForWrite[v27]) - (unsigned int)BYTE1(v25))) >> 16)) | (((BYTE2(v25) + (((tjs_uint16)v19 * ((tjs_uint8)BYTE2(mainImageBufferForWrite[v27]) - (unsigned int)BYTE2(v25))) >> 16)) | ((v51 + (((tjs_uint16)v19 * (HIBYTE(mainImageBufferForWrite[v27]) - v51)) >> 16)) << 8)) << 8)) << 8) | ((tjs_uint8)v25 + (((tjs_uint16)v19 * ((tjs_uint8)mainImageBufferForWrite[v27] - (unsigned int)(tjs_uint8)v25)) >> 16));
				if (v19 >> 16 < layerinfo->clipHeight)
				{
					v28 = mainImageBufferForWrite[v41 + v27];
					mainImageBufferForWrite[v41 + v27] = (((BYTE1(v25) + (((0xFFFF - (tjs_uint16)v19) * (BYTE1(v28) - (unsigned int)BYTE1(v25))) >> 16)) | (((BYTE2(v25) + (((0xFFFF - (tjs_uint16)v19) * (BYTE2(v28) - (unsigned int)BYTE2(v25))) >> 16)) | ((v51 + (((0xFFFF - (tjs_uint16)v19) * (HIBYTE(v28) - v51)) >> 16)) << 8)) << 8)) << 8) | ((tjs_uint8)v25 + (((0xFFFF - (tjs_uint16)v19) * ((tjs_uint8)v28 - (unsigned int)(tjs_uint8)v25)) >> 16));
				}
				v42 += v53;
				v48 += v55;
				v19 = v48;
				v18 = v42;
				result = v64 - 1;
				v64 = result;
			} while (result);
			v25 = v57;
		}
		if (v18 >= 0)
		{
			if (v18 <= layerinfo->clipWidth)
			{
				v29 = v18 + v41 * (v19 >> 16);
				mainImageBufferForWrite[v29] = calc_pixel(v25, mainImageBufferForWrite[v29], (tjs_uint16)v19);
				result = v19 >> 16;
				if (v19 >> 16 < layerinfo->clipHeight)
				{
					v30 = v41 + v29;
					result = calc_pixel(v25, mainImageBufferForWrite[v30], 0xFFFF - (tjs_uint16)v19);
					mainImageBufferForWrite[v30] = result;
				}
			}
		}
	}
	return result;
}

bool bound_check_inner(
	layer_info_x *layerinfo,
	int a2,
	int a3,
	char a4,
	int a5,
	int a6,
	int *a7,
	int *a8)
{
	int v8;
	int v9;
	int v11;
	int v12;
	int v13;

	v8 = a5;
	if ((a4 & 1) != 0)
	{
		v9 = a3 + (a6 - a3) * (layerinfo->clipLeft - a2) / (a5 - a2);
		if (v9 >= layerinfo->clipTop && v9 <= layerinfo->clipHeight)
		{
			*a7 = layerinfo->clipLeft;
			*a8 = v9;
			return true;
		}
		v8 = a5;
	}
	if ((a4 & 2) != 0)
	{
		v11 = a3 + (a6 - a3) * (layerinfo->clipWidth - a2) / (v8 - a2);
		if (v11 >= layerinfo->clipTop && v11 <= layerinfo->clipHeight)
		{
			*a7 = layerinfo->clipWidth;
			*a8 = v11;
			return true;
		}
		v8 = a5;
	}
	if ((a4 & 4) != 0)
	{
		v12 = a2 + (v8 - a2) * (layerinfo->clipTop - a3) / (a6 - a3);
		if (v12 >= layerinfo->clipLeft && v12 <= layerinfo->clipWidth)
		{
			*a7 = v12;
			*a8 = layerinfo->clipTop;
			return true;
		}
		v8 = a5;
	}
	if ((a4 & 8) == 0)
		return false;
	v13 = a2 + (v8 - a2) * (layerinfo->clipHeight - a3) / (a6 - a3);
	if (v13 < layerinfo->clipLeft || v13 > layerinfo->clipWidth)
		return false;
	*a7 = v13;
	*a8 = layerinfo->clipHeight;
	return true;
}

bool bound_check(layer_info_x *layerinfo, int *a2, int *a3, int *a4, int *a5)
{
	int v5;
	int clipLeft;
	int v7;
	int v8;
	int v9;
	int v10;
	int v11;

	v5 = *a3;
	clipLeft = layerinfo->clipLeft;
	v7 = *a2;
	v8 = 0;
	if (*a2 >= clipLeft)
	{
		if (v7 > layerinfo->clipWidth)
			v8 = 2;
	}
	else
	{
		v8 = 1;
	}
	if (v5 >= layerinfo->clipTop)
	{
		if (v5 > layerinfo->clipHeight)
			v8 |= 8u;
	}
	else
	{
		v8 |= 4u;
	}
	v9 = *a5;
	v10 = *a4;
	v11 = 0;
	if (*a4 >= clipLeft)
	{
		if (v10 > layerinfo->clipWidth)
			v11 = 2;
	}
	else
	{
		v11 = 1;
	}
	if (v9 >= layerinfo->clipTop)
	{
		if (v9 > layerinfo->clipHeight)
			v11 |= 8u;
	}
	else
	{
		v11 |= 4u;
	}
	return !(v8 + v11) || ((v11 & v8) == 0 && (!v8 || bound_check_inner(layerinfo, v7, *a3, v8, v10, v9, a2, a3)) && (!v11 || bound_check_inner(layerinfo, *a2, *a3, v11, *a4, *a5, a4, a5)));
}

void sub_10001450(
	layer_info_x *layerinfo,
	tTVPRect *updaterect,
	int cx,
	int cy,
	int cmax,
	int cmin,
	int lmax,
	int lmin,
	int emax,
	int emin,
	int color)
{
	int v12 = TVPGetTickCount();
	int v13 = (32 * (((((v12 - 1831433054) << 13) ^ (v12 - 1831433054)) >> 7) ^ ((v12 - 1831433054) << 13) ^ (v12 - 1831433054))) ^ ((((v12 - 1831433054) << 13) ^ (v12 - 1831433054)) >> 7) ^ ((v12 - 1831433054) << 13) ^ (v12 - 1831433054);
	int v38 = lmax + ((((v13 & 0xffff) >> 16) * (lmax - lmin)) >> 16);
	if (v38)
	{
		// TODO: check if emax/emin are in the correct variables
		int v14 = emax - emin;
		int v15 = cmax - cmin;
		while (1)
		{
			int v16 = (((v13 << 13) ^ v13) >> 7) ^ (v13 << 13) ^ v13;
			int v17 = (32 * v16) ^ v16;
			int v35 = cmax + ((v15 * ((v17 & 0xffff) >> 16)) >> 16);
			int v18 = (((v17 << 13) ^ v17) >> 7) ^ (v17 << 13) ^ v17;
			int v19 = (32 * v18) ^ v18;
			int v21 = (((v19 << 13) ^ v19) >> 7) ^ (v19 << 13) ^ v19;
			int v34 = emax + ((v14 * ((v19 & 0xffff) >> 16)) >> 16);
			v13 = (32 * v21) ^ v21;
			double v36 = (double)v13 * 2.328306436538696e-10 * 3.141592653589793 + (double)v13 * 2.328306436538696e-10 * 3.141592653589793;
			int v33X = (int)((double)v35 * cos(v36) + (double)cy);
			int v36X = (int)((double)v35 * sin(v36) + (double)cx);
			int v35X = (int)((double)v34 * cos(v36) + (double)cy);
			int v34X = (int)((double)v34 * sin(v36) + (double)cx);
			if (bound_check(layerinfo, &v33X, &v36X, &v35X, &v34X))
			{
				if (v15 <= 0)
					sub_10001B80(v34X, v36X, v35X, layerinfo, v33X, color);
				else
					sub_10001E00(v35X, v33X, v34X, layerinfo, v36X, color, v15);
			}
			if (!--v38)
				break;
		}
	}
	int clipLeft = cy - cmax;
	int clipTop = cx - cmax;
	int clipWidth = cy + cmax;
	int clipHeight = cx + cmax;
	if (cy - lmax < layerinfo->clipLeft)
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
		int cmin = 100; // Minimum distance from the center to the appearance of the line
		if (numparams >= 3 && param[2]->Type() != tvtVoid)
			cmin = *param[2];
		int cmax = 100; // Maximum distance from the center to the appearance of the line
		if (numparams >= 4 && param[3]->Type() != tvtVoid)
			cmax = *param[3];
		int lmin = 50; // Minimum number of lines
		if (numparams >= 5 && param[4]->Type() != tvtVoid)
			lmin = *param[4];
		int lmax = 50; // Maximum number of lines
		if (numparams >= 6 && param[5]->Type() != tvtVoid)
			lmax = *param[5];
		int emin = 2000; // Minimum distance from the center until the line disappears
		if (numparams >= 7 && param[6]->Type() != tvtVoid)
			emin = *param[6];
		int emax = 2000; // Maximum distance from the center until the line disappears
		if (numparams >= 8 && param[7]->Type() != tvtVoid)
			emax = *param[7];
		int color = 0xFF000000; // Line color
		if (numparams >= 9 && param[8]->Type() != tvtVoid)
			color = *param[8];

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

		sub_10001450(&layerinfo, &UpdateRect, cx, cy, cmax, cmin, lmax, lmin, emax, emin, color);

		UpdateLayerWithLayerObject(bmpobject_clo, &UpdateRect, &ImageLeft, &ImageTop);
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
