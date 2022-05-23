#include "ncbind/ncbind.hpp"
#include "LayerBitmapUtility.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

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

typedef struct haze_slot_
{
	tjs_int *arr12[2];
	tjs_int *arr3;
	tjs_uint32 arr_count;
} haze_slot;

static haze_slot *haze_slots[10];

static tjs_uint32 find_next_free_haze_slot()
{
	for (tjs_uint32 i = 0; i < sizeof(haze_slots) / sizeof(haze_slots[0]); i += 1)
	{
		if (!haze_slots[i])
			return i;
	}
	return -1;
}

static haze_slot *prepare_haze(tjs_uint32 a1)
{
	if (a1 < 0 || a1 >= sizeof(haze_slots) / sizeof(haze_slots[0]))
		return 0;
	haze_slot *v3 = haze_slots[a1];
	if (v3)
	{
		if (v3->arr3)
			free(v3->arr3);
		v3->arr3 = 0;
		v3->arr_count = 0;
	}
	else
	{
		v3 = (haze_slot *)malloc(sizeof(haze_slot));
		haze_slots[a1] = v3;
		v3->arr12[0] = 0;
		v3->arr12[1] = 0;
		v3->arr3 = 0;
		v3->arr_count = 0;
	}
	return v3;
}

static bool free_haze_slot(tjs_uint32 a1)
{
	if (a1 < 0 || a1 >= (sizeof(haze_slots) / sizeof(haze_slots[0])) || !haze_slots[a1])
		return false;
	haze_slot *v3 = haze_slots[a1];
	for (tjs_int i = 0; i < 2; i += 1)
	{
		if (v3->arr12[i])
			free(v3->arr12[i]);
	}
	if (v3->arr3)
		free(v3->arr3);
	free(v3);
	haze_slots[a1] = NULL;
	return true;
}

static void fn_yes_alphablend(
	tjs_uint32 *mainImageBufferForWrite,
	int dl,
	tjs_uint32 *src_mainImageBuffer,
	int sl,
	int a5,
	int dw,
	int src_imageWidth)
{
	int v7;
	int v8;
	int v9;
	int v10;
	tjs_uint32 *a1a;
	int a5a;
	int a5b;

	a5a = a5 + (sl << 8);
	v10 = a5a >> 8;
	if (a5a <= 0)
	{
		if (sl >= v10)
		{
			src_mainImageBuffer += v10;
			src_imageWidth -= v10;
		}
		else
		{
			mainImageBufferForWrite -= v10;
			dw += v10;
		}
	}
	else
	{
		src_mainImageBuffer += v10;
		src_imageWidth -= v10;
	}
	a1a = &mainImageBufferForWrite[dl];
	a5b = 256 - (tjs_uint8)a5a;
	if (dw >= src_imageWidth)
		v7 = src_imageWidth;
	else
		v7 = dw;
	v9 = (v7 + 3) >> 2;
	v8 = 256 - a5b;
	switch (v7 % 4)
	{
		case 0:
			goto LABEL_10;
		case 1:
			goto LABEL_13;
		case 2:
			goto LABEL_12;
		case 3:
			while (1)
			{
				*a1a++ = ((v8 * ((src_mainImageBuffer[1] & 0xFF00FF00) >> 8) + a5b * ((*src_mainImageBuffer & 0xFF00FF00) >> 8)) & 0xFF00FF00) | (((v8 * (src_mainImageBuffer[1] & 0xFF00FF) + a5b * (*src_mainImageBuffer & 0xFF00FFu)) >> 8) & 0xFF00FF);
				src_mainImageBuffer += 1;
			LABEL_12:
				*a1a++ = ((v8 * ((src_mainImageBuffer[1] & 0xFF00FF00) >> 8) + a5b * ((*src_mainImageBuffer & 0xFF00FF00) >> 8)) & 0xFF00FF00) | (((v8 * (src_mainImageBuffer[1] & 0xFF00FF) + a5b * (*src_mainImageBuffer & 0xFF00FFu)) >> 8) & 0xFF00FF);
				src_mainImageBuffer += 1;
			LABEL_13:
				*a1a++ = ((v8 * ((src_mainImageBuffer[1] & 0xFF00FF00) >> 8) + a5b * ((*src_mainImageBuffer & 0xFF00FF00) >> 8)) & 0xFF00FF00) | (((v8 * (src_mainImageBuffer[1] & 0xFF00FF) + a5b * (*src_mainImageBuffer & 0xFF00FFu)) >> 8) & 0xFF00FF);
				src_mainImageBuffer += 1;
				v9 -= 1;
				if (!v9)
					break;
			LABEL_10:
				*a1a++ = ((v8 * ((src_mainImageBuffer[1] & 0xFF00FF00) >> 8) + a5b * ((*src_mainImageBuffer & 0xFF00FF00) >> 8)) & 0xFF00FF00) | (((v8 * (src_mainImageBuffer[1] & 0xFF00FF) + a5b * (*src_mainImageBuffer & 0xFF00FFu)) >> 8) & 0xFF00FF);
				src_mainImageBuffer += 1;
			}
			break;
		default:
			return;
	}
}

static void fn_no_alphablend(
	tjs_uint32 *mainImageBufferForWrite,
	int dl,
	tjs_uint32 *src_mainImageBuffer,
	int sl,
	int a5,
	int dw,
	int src_imageWidth)
{
	int v7;
	int v8;
	int v9;
	tjs_uint32 *a1a;
	int a5a;

	a5a = a5 + (sl << 8);
	v9 = a5a >> 8;
	if (a5a <= 0)
	{
		if (sl >= v9)
		{
			src_mainImageBuffer += v9;
			src_imageWidth -= v9;
		}
		else
		{
			mainImageBufferForWrite -= v9;
			dw += v9;
		}
	}
	else
	{
		src_mainImageBuffer += v9;
		src_imageWidth -= v9;
	}
	a1a = &mainImageBufferForWrite[dl];
	if (dw >= src_imageWidth)
		v7 = src_imageWidth;
	else
		v7 = dw;
	v8 = (v7 + 3) >> 2;
	switch (v7 % 4)
	{
		case 0:
			goto LABEL_10;
		case 1:
			goto LABEL_13;
		case 2:
			goto LABEL_12;
		case 3:
			while (1)
			{
				*a1a++ = *src_mainImageBuffer++;
			LABEL_12:
				*a1a++ = *src_mainImageBuffer++;
			LABEL_13:
				*a1a++ = *src_mainImageBuffer++;
				v8 -= 1;
				if (!v8)
					break;
			LABEL_10:
				*a1a++ = *src_mainImageBuffer++;
			}
			break;
		default:
			return;
	}
}

class LayerLayerExFilter
{
public:
	static tjs_error TJS_INTF_METHOD initHazeCopy(
		tTJSVariant *result,
		tjs_int numparams,
		tTJSVariant **param,
		iTJSDispatch2 *objthis)
	{
		bool v13;
		double v28[32][3];

		tjs_uint32 haze_slot_index = (numparams > 0 && param[0]->Type() != tvtVoid) ? (tjs_uint32)(tTVInteger)*param[0] : find_next_free_haze_slot();
		haze_slot *haze_slot_struct = prepare_haze(haze_slot_index);
		if (!haze_slot_struct)
		{
			return -1;
		}
		if (result)
		{
			*result = (tTVInteger)(tjs_int)haze_slot_index;
		}
		tTJSVariant tmpvariant;
		for (tjs_int i = 1; i <= 2; i += 1)
		{
			if (i != 2 || (numparams <= 2 ? (v13 = 0) : (v13 = (param[i]->Type() != tvtVoid)), v13 && (param[i]->Type() != tvtVoid)))
			{
				tjs_int *v29 = haze_slot_struct->arr12[i - 1];
				if (!v29)
				{
					haze_slot_struct->arr12[i - 1] = (tjs_int *)malloc(0x10000u);
					v29 = haze_slot_struct->arr12[i - 1];
				}
				v28[0][0] = 1.0;
				v28[0][1] = 0.0;
				v28[0][2] = 1.0;
				memset(v28[1], 0, 0x2E8u);
				tjs_int count_1 = 1;
				if (numparams > i && param[i]->Type() != tvtVoid)
				{
					tTJSVariantClosure v27 = param[i]->AsObjectClosureNoAddRef();
					v27.PropGet(0, TJS_W("count"), 0, &tmpvariant, NULL);
					count_1 = tmpvariant;
					if (count_1 > 32)
						count_1 = 32;
					for (tjs_int j = 0; j < count_1; j += 1)
					{
						v27.PropGetByNum(0, j, &tmpvariant, NULL);
						if (tmpvariant.Type() != tvtVoid)
						{
							tTJSVariantClosure v24 = tmpvariant.AsObjectClosureNoAddRef();
							v24.PropGet(0, TJS_W("count"), 0, &tmpvariant, NULL);
							tjs_int count_2 = tmpvariant;
							if (count_2 > 3)
								count_2 = 3;
							for (tjs_int k = 0; k < count_2; k += 1)
							{
								v24.PropGetByNum(0, k, &tmpvariant, NULL);
								v28[j][k] = tmpvariant;
							}
						}
					}
				}
				double v30 = 0.0;
				for (tjs_int m = 0; m < 0x4000; m += 1)
				{
					double v21 = 0.0;
					for (tjs_int n = 0; n < count_1; n += 1)
					{
						v21 = cos(v30 * v28[n][0] + v28[n][1]) * v28[n][2] + v21;
						v30 += 0.001533980787885641;
					}
					v29[m] = (int)(v21 * 256.0);
				}
			}
			else
			{
				if (haze_slot_struct->arr12[i - 1])
					free(haze_slot_struct->arr12[i - 1]);
				haze_slot_struct->arr12[i - 1] = 0;
			}
		}
		if (numparams > 3 && param[3]->Type() != tvtVoid)
		{
			tTJSVariantClosure v19 = param[3]->AsObjectClosureNoAddRef();
			v19.PropGet(0, TJS_W("count"), 0, &tmpvariant, NULL);
			haze_slot_struct->arr_count = (tjs_uint32)(tTVInteger)tmpvariant;
			tjs_uint32 arr_count = haze_slot_struct->arr_count;
			if (arr_count > 0)
			{
				tjs_int *v15 = (tjs_int *)malloc(8 * arr_count);
				haze_slot_struct->arr3 = v15;
				for (tjs_uint32 ii = 0; ii < arr_count; ii += 1)
				{
					v19.PropGetByNum(0, ii, &tmpvariant, NULL);
					tTJSVariantClosure v16 = tmpvariant.AsObjectClosureNoAddRef();
					v16.PropGetByNum(0, 0, &tmpvariant, NULL);
					v15[2 * ii] = (tjs_int)(tTVInteger)tmpvariant;
					v16.PropGetByNum(0, 1, &tmpvariant, NULL);
					v15[2 * ii + 1] = (tjs_int)((tjs_real)tmpvariant * 256.0);
				}
			}
		}
		return TJS_S_OK;
	}
	static tjs_error TJS_INTF_METHOD uninitHazeCopy(
		tTJSVariant *result,
		tjs_int numparams,
		tTJSVariant **param,
		iTJSDispatch2 *objthis)
	{
		if (numparams > 0 && param[0]->Type() != tvtVoid)
		{
			tjs_uint32 v9 = free_haze_slot((tjs_uint32)(tTVInteger)*param[0]);
			if (result)
				*result = v9 ? 1 : 0;
		}
		else
		{
			return -1;
		}
		return TJS_S_OK;
	}

	static tjs_error TJS_INTF_METHOD hazeCopy(
		tTJSVariant *result,
		tjs_int numparams,
		tTJSVariant **param,
		iTJSDispatch2 *objthis)
	{
		if (numparams < 2)
			return -1004;

		if (objthis == NULL)
			TVPThrowExceptionMessage(TJS_W("Specify Layer or Bitmap class object"));
		tTJSVariant bmpobject = tTJSVariant(objthis, objthis);
		tTJSVariantClosure bmpobject_clo = bmpobject.AsObjectClosureNoAddRef();

		tjs_uint32 haze_slot_index = 0;
		if (numparams > 0 && param[0]->Type() != tvtVoid)
		{
			tTVInteger haze_slot_index_tmp = *param[0];
			if (haze_slot_index_tmp >= 0)
			{
				haze_slot_index = (tjs_uint32)haze_slot_index_tmp;
			}
			else
			{
#if 0
				TVPAddLog(ttstr(TJS_W("初期化が終了していません。先に initHazeCopy を実行してください。(__waveinfono = "))) + haze_slot_index + ttstr(TJS_W(")")));
#endif
				return -1;
			}
		}
		else
		{
			return -1;
		}
		haze_slot *haze_slot_struct = prepare_haze(haze_slot_index);
		tjs_int *v94 = haze_slot_struct->arr12[0];
		tjs_int *v122 = haze_slot_struct->arr12[1];
		tjs_int *arr3 = haze_slot_struct->arr3;
		tjs_uint32 arr_count = haze_slot_struct->arr_count;

		// Now get information (this will independ the bitmap)
		tjs_int imageWidth = 0;
		tjs_int imageHeight = 0;
		tjs_int mainImageBufferPitch = 0;
		tjs_uint32 *mainImageBufferForWrite = NULL;
		GetBitmapInformationFromObject(bmpobject_clo, true, &imageWidth, &imageHeight, &mainImageBufferPitch, (tjs_uint8 **)&mainImageBufferForWrite);
		if (!mainImageBufferForWrite)
			TVPThrowExceptionMessage(TJS_W("Specify Layer or Bitmap class object"));

		if (numparams > 1 && param[1]->Type() != tvtVoid)
		{
			// ...
		}
		else
		{
#if 0
			TVPAddLog(TJS_W("転送元のレイヤーが指定されていません。"));
#endif
			return -1;
		}
		tTJSVariantClosure srcbmpobject_clo = param[1]->AsObjectClosureNoAddRef();

		tjs_int src_imageWidth = 0;
		tjs_int src_imageHeight = 0;
		tjs_int src_mainImageBufferPitch = 0;
		tjs_uint32 *src_mainImageBuffer = NULL;
		GetBitmapInformationFromObject(srcbmpobject_clo, false, &src_imageWidth, &src_imageHeight, &src_mainImageBufferPitch, (tjs_uint8 **)&src_mainImageBuffer);
		if (!src_mainImageBuffer)
			TVPThrowExceptionMessage(TJS_W("Specify Layer or Bitmap class object"));

		int sl = 0;
		if (numparams > 2 && param[2]->Type() != tvtVoid)
			sl = *param[2];
		int st = 0;
		if (numparams > 3 && param[3]->Type() != tvtVoid)
			st = *param[3];
		int rad = 0;
		if (numparams > 4 && param[4]->Type() != tvtVoid)
			rad = (tjs_int)*param[4] & 0x3FFF;
		int delta = 7;
		if (numparams > 5 && param[5]->Type() != tvtVoid)
			delta = *param[5];
		int per = 2560; // XXX: forgot to put a period?
		if (numparams > 6 && param[6]->Type() != tvtVoid)
			per = (int)(((tjs_real)*param[6]) * 256.0);
		void (*alphablend)(tjs_uint32 *, int, tjs_uint32 *, int, int, int, int) = fn_yes_alphablend;
		if (numparams > 7 && param[7]->Type() != tvtVoid && (((tjs_int)*param[7]) == 0))
			alphablend = fn_no_alphablend;
		int dl = 0;
		if (numparams > 8 && param[8]->Type() != tvtVoid)
			dl = *param[8];
		int dt = 0;
		if (numparams > 9 && param[9]->Type() != tvtVoid)
			dt = *param[9];
		int dw = imageWidth;
		if (numparams > 10 && param[10]->Type() != tvtVoid)
			dw = *param[10];
		int dh = imageHeight;
		if (numparams > 11 && param[11]->Type() != tvtVoid)
			dh = *param[11];
		int sw = imageWidth;
		if (numparams > 12 && param[12]->Type() != tvtVoid)
			sw = *param[12];
		int sh = imageHeight;
		if (numparams > 13 && param[13]->Type() != tvtVoid)
			sh = *param[13];
		if (dl < 0)
			dl = 0;
		if (dt < 0)
			dt = 0;
		if (dw + dl > sw)
			dw = sw - dl;
		if (dh + dt > sh)
			dh = sh - dt;
		if (dh > src_imageHeight - st)
			dh = src_imageHeight - st;
		// Inner haze related code.
		tjs_int v103 = 0;
		tjs_int v119 = 0;
		{
			int v92 = mainImageBufferPitch / 4;
			tjs_uint32 *v118 = &mainImageBufferForWrite[dt * (mainImageBufferPitch / 4)];
			int v105 = src_mainImageBufferPitch / 4;
			tjs_uint32 *v110 = &src_mainImageBuffer[st * (src_mainImageBufferPitch / 4)];
			if (arr3 && arr_count != 1)
			{
				tjs_int v80 = *arr3;
				v103 = dt + v80;
				tjs_int v82 = arr3[1];
				v118 += v80 * v92;
				v110 += v80 * v105;
				tjs_int v81;
				for (tjs_uint32 i = 1; i < arr_count; i += 1)
				{
					v81 = arr3[2 * i];
					tjs_int v79 = ((arr3[2 * i + 1] - arr3[2 * i - 1]) << 8) / (v81 - v80);
					if (v81 > dh)
						v81 = dh;
					if (v122)
					{
						tjs_int v73 = (v82 * per) >> 8;
						tjs_int v70 = (v73 * v122[rad & 0x3FFF]) >> 16;
						tjs_int v18;
						if (v80 - v70 >= 0)
						{
							v18 = v80 < dh + v70 ? -v70 : dh - v80 - 1;
						}
						else
						{
							v18 = -v80;
						}
						tjs_int v69 = v18;
						tjs_int v72 = dh + st + v18 - 1;
						tjs_int v16;
						if (v72 >= 0)
						{
							v16 = v72 <= src_imageHeight - 2 ? v69 : src_imageHeight - st - 2;
						}
						else
						{
							v16 = -st;
						}
						v69 = v105 * v16;
						v70 = (v73 * v94[rad & 0x3FFF]) >> 16;
						tjs_int v71 = src_imageWidth - dw;
						if (v70 <= src_imageWidth - dw)
						{
							if (v70 < -v71)
								v70 = -v71;
						}
						else
						{
							v70 = v71;
						}
						alphablend(v118, dl, &v110[v69], sl, v70, dw, src_imageWidth);
						for (tjs_int j = v72 + 1; j < v81 - 1; j += 1)
						{
							tjs_int v73 = (v82 * per) >> 8;
							v70 = (v73 * v122[rad & 0x3FFF]) >> 16;
							if (j - v70 >= 0)
							{
								if (j < dh + v70)
									v69 = -v70;
								else
									v69 = dh - j - 1;
							}
							else
							{
								v69 = -j;
							}
							v72 = dh + st + v69 - 1;
							tjs_int v12;
							if (v72 >= 0)
							{
								if (v72 <= src_imageHeight - 2)
									v12 = v69;
								else
									v12 = src_imageHeight - st - j - 2;
							}
							else
							{
								v12 = -st - j;
							}
							v69 = v105 * v12;
							alphablend(v118, dl, &v110[v105 * v12], sl, (v73 * v94[rad & 0x3FFF]) >> 16, dw, src_imageWidth);
							rad += delta;
							v82 += v79;
							v118 += v92;
							v110 += v105;
						}
						v73 = (v82 * per) >> 8;
						v70 = (v73 * v122[rad & 0x3FFF]) >> 16;
						if (v81 - 1 - v70 >= 0)
						{
							v69 = v81 - 1 < dh + v70 ? -v70 : dh - v81;
						}
						else
						{
							v69 = 1 - v81;
						}
						v72 = dh + st + v69 - 1;
						tjs_int v8;
						if (v72 >= 0)
						{
							v8 = v72 <= src_imageHeight - 2 ? v69 : src_imageHeight - st - dh - 1;
						}
						else
						{
							v8 = -st - dh + 1;
						}
						v69 = v105 * v8;
						v70 = (v73 * v94[rad & 0x3FFF]) >> 16;
						v71 = src_imageWidth - dw;
						if (v70 <= src_imageWidth - dw)
						{
							if (v70 < -v71)
								v70 = -v71;
						}
						else
						{
							v70 = v71;
						}
						alphablend(v118, dl, &v110[v69], sl, v70, dw, src_imageWidth);
					}
					else
					{
						tjs_int v77 = (v82 * per) >> 8;
						tjs_int v75 = (v77 * v94[rad & 0x3FFF]) >> 16;
						tjs_int v76 = src_imageWidth - dw;
						if (v75 <= src_imageWidth - dw)
						{
							if (v75 < -v76)
								v75 = -v76;
						}
						else
						{
							v75 = v76;
						}
						alphablend(v118, dl, v110, sl, v75, dw, src_imageWidth);
						for (tjs_int k = v80 + 1; k < v81 - 1; k += 1)
						{
							alphablend(v118, dl, v110, sl, (((v82 * per) >> 8) * v94[rad & 0x3FFF]) >> 16, dw, src_imageWidth);
							rad += delta;
							v82 += v79;
							v118 += v92;
							v110 += v105;
						}
						v77 = (v82 * per) >> 8;
						v75 = (v77 * v94[rad & 0x3FFF]) >> 16;
						v76 = src_imageWidth - dw;
						if (v75 <= src_imageWidth - dw)
						{
							if (v75 < -v76)
								v75 = -v76;
						}
						else
						{
							v75 = v76;
						}
						alphablend(v118, dl, v110, sl, v75, dw, src_imageWidth);
					}
					if (v81 == dh)
						break;
					v80 = v81;
				}
				v119 = dt + v81;
			}
			else
			{
				if (v122)
				{
					tjs_int v85 = (per * v122[rad & 0x3FFF]) >> 16;
					tjs_int v84;
					if (v85 <= 0)
					{
						if (dh + v85 > 0)
							v84 = -v85;
						else
							v84 = dh - 1;
					}
					else
					{
						v84 = 0;
					}
					tjs_int v87 = v84 + st;
					tjs_int v28;
					if (v84 + st >= 0)
					{
						if (v87 <= src_imageHeight - 2)
							v28 = v84;
						else
							v28 = src_imageHeight - st - 2;
					}
					else
					{
						v28 = -st;
					}
					v84 = v105 * v28;
					v85 = (per * v94[rad & 0x3FFF]) >> 8;
					tjs_int v86 = src_imageWidth - dw;
					if (v85 <= src_imageWidth - dw)
					{
						if (v85 < -v86)
							v85 = -v86;
					}
					else
					{
						v85 = v86;
					}
					alphablend(v118, dl, &v110[v84], sl, v85, dw, src_imageWidth);
					rad += delta;
					v118 += v92;
					v110 += v105;
					for (tjs_int m = 1; m < dh - 1; m += 1)
					{
						v85 = (per * v122[rad & 0x3FFF]) >> 16;
						if (m - v85 >= 0)
						{
							if (m < dh + v85)
								v84 = -v85;
							else
								v84 = dh - m - 1;
						}
						else
						{
							v84 = -m;
						}
						v87 = v84 + m + st;
						tjs_int v24;
						if (v87 >= 0)
						{
							if (v87 <= src_imageHeight - 2)
								v24 = v84;
							else
								v24 = src_imageHeight - st - m - 2;
						}
						else
						{
							v24 = -st - m;
						}
						v84 = v105 * v24;
						alphablend(v118, dl, &v110[v105 * v24], sl, (per * v94[rad & 0x3FFF]) >> 8, dw, src_imageWidth);
						rad += delta;
						v118 += v92;
						v110 += v105;
					}
					v85 = (per * v122[rad & 0x3FFF]) >> 16;
					if (dh - 1 - v85 >= 0)
					{
						if (v85 > -1)
							v84 = -v85;
						else
							v84 = 0;
					}
					else
					{
						v84 = 1 - dh;
					}
					v87 = dh + st + v84 - 1;
					tjs_int v20;
					if (v87 >= 0)
					{
						if (v87 <= src_imageHeight - 2)
							v20 = v84;
						else
							v20 = src_imageHeight - st - dh - 1;
					}
					else
					{
						v20 = -st - dh + 1;
					}
					v84 = v105 * v20;
					v85 = (per * v94[rad & 0x3FFF]) >> 8;
					v86 = src_imageWidth - dw;
					if (v85 <= src_imageWidth - dw)
					{
						if (v85 < -v86)
							v85 = -v86;
					}
					else
					{
						v85 = v86;
					}
					alphablend(v118, dl, &v110[v84], sl, v85, dw, src_imageWidth);
				}
				else
				{
					tjs_int v89 = (per * v94[rad & 0x3FFF]) >> 8;
					tjs_int v90 = src_imageWidth - dw;
					if (v89 <= src_imageWidth - dw)
					{
						if (v89 < -v90)
							v89 = -v90;
					}
					else
					{
						v89 = v90;
					}
					alphablend(v118, dl, v110, sl, v89, dw, src_imageWidth);
					rad += delta;
					v118 += v92;
					v110 += v105;
					for (tjs_int n = 1; n < dh - 1; n += 1)
					{
						alphablend(v118, dl, v110, sl, (per * v94[rad & 0x3FFF]) >> 8, dw, src_imageWidth);
						rad += delta;
						v118 += v92;
						v110 += v105;
					}
					v89 = (per * v94[rad & 0x3FFF]) >> 8;
					v90 = src_imageWidth - dw;
					if (v89 <= src_imageWidth - dw)
					{
						if (v89 < -v90)
							v89 = -v90;
					}
					else
					{
						v89 = v90;
					}
					alphablend(v118, dl, v110, sl, v89, dw, src_imageWidth);
				}
				v103 = dt;
				v119 = dh + dt;
			}
		}

		tjs_int ImageLeft = 0;
		tjs_int ImageTop = 0;

		GetLayerInformationFromLayerObject(bmpobject_clo, NULL, NULL, NULL, NULL, &ImageLeft, &ImageTop, NULL);

		tTVPRect UpdateRect;
		UpdateRect.set_offsets(dl, v103);
		UpdateRect.set_size(dw, v119);
		UpdateLayerWithLayerObject(bmpobject_clo, &UpdateRect, &ImageLeft, &ImageTop);
		return TJS_S_OK;
	}

	static tjs_error TJS_INTF_METHOD drawNoise(
		tTJSVariant *result,
		tjs_int numparams,
		tTJSVariant **param,
		iTJSDispatch2 *objthis)
	{
		if (numparams < 0)
			return -1004;

		if (objthis == NULL)
			TVPThrowExceptionMessage(TJS_W("Specify Layer or Bitmap class object"));
		tTJSVariant bmpobject = tTJSVariant(objthis, objthis);
		tTJSVariantClosure bmpobject_clo = bmpobject.AsObjectClosureNoAddRef();

		// Now get information (this will independ the bitmap)
		tjs_int imageWidth = 0;
		tjs_int imageHeight = 0;
		tjs_int mainImageBufferPitch = 0;
		tjs_uint32 *mainImageBufferForWrite = NULL;
		GetBitmapInformationFromObject(bmpobject_clo, true, &imageWidth, &imageHeight, &mainImageBufferPitch, (tjs_uint8 **)&mainImageBufferForWrite);
		if (!mainImageBufferForWrite)
			TVPThrowExceptionMessage(TJS_W("Specify Layer or Bitmap class object"));

		// Parse parameters
		int monocro = 0;
		if (numparams > 0 && param[0]->Type() != tvtVoid)
			monocro = *param[0];
		int under = 0;
		if (numparams > 1 && param[1]->Type() != tvtVoid)
			under = *param[1];
		int upper = 0;
		if (numparams > 2 && param[2]->Type() != tvtVoid)
			upper = *param[2];
		int seed = 0;
		if (numparams > 3 && param[3]->Type() != tvtVoid)
			seed = *param[3];
		int l = 0;
		if (numparams > 4 && param[4]->Type() != tvtVoid)
			l = *param[4];
		int t = 0;
		if (numparams > 5 && param[5]->Type() != tvtVoid)
			t = *param[5];
		int w = 0;
		if (numparams > 6 && param[6]->Type() != tvtVoid)
			w = *param[6];
		int h = 0;
		if (numparams > 7 && param[7]->Type() != tvtVoid)
			h = *param[7];
		int holdalpha = 0;
		if (numparams > 8 && param[8]->Type() != tvtVoid)
			holdalpha = *param[8];
		if (upper < under)
		{
			int tmp = under;
			under = upper;
			upper = tmp;
		}
		tjs_int upper_under_diff = upper - under;
		if (l < 0)
			l = 0;
		if (t < 0)
			t = 0;
		if (w + l > imageWidth)
			w = imageWidth - l;
		if (h + t > imageHeight)
			h = imageHeight - t;
		tjs_int cur_seed = seed;
		tjs_uint32 *write_buffer_offset = mainImageBufferForWrite + ((mainImageBufferPitch / sizeof(tjs_uint32)) * t);
		if (!holdalpha)
		{
			if (!monocro)
			{
				if (upper_under_diff == 255)
				{
					for (tjs_int i = h; i; i -= 1)
					{
						tjs_uint32 *v32 = &write_buffer_offset[l];
						tjs_int j;
						for (j = w; j >= 4; j -= 4)
						{
							cur_seed = 0x7D2B89DD * cur_seed + 1;
							*v32++ = ((cur_seed >> 8) & 0xFFFFFF) | 0xFF000000;
							cur_seed = 0x7D2B89DD * cur_seed + 1;
							*v32++ = ((cur_seed >> 8) & 0xFFFFFF) | 0xFF000000;
							cur_seed = 0x7D2B89DD * cur_seed + 1;
							*v32++ = ((cur_seed >> 8) & 0xFFFFFF) | 0xFF000000;
							cur_seed = 0x7D2B89DD * cur_seed + 1;
							*v32++ = ((cur_seed >> 8) & 0xFFFFFF) | 0xFF000000;
						}
						if (j > 2)
						{
							cur_seed = 0x7D2B89DD * cur_seed + 1;
							*v32++ = ((cur_seed >> 8) & 0xFFFFFF) | 0xFF000000;
						}
						if (j > 1)
						{
							cur_seed = 0x7D2B89DD * cur_seed + 1;
							*v32++ = ((cur_seed >> 8) & 0xFFFFFF) | 0xFF000000;
						}
						if (j > 0)
						{
							cur_seed = 0x7D2B89DD * cur_seed + 1;
							*v32++ = ((cur_seed >> 8) & 0xFFFFFF) | 0xFF000000;
						}
						write_buffer_offset += mainImageBufferPitch / sizeof(tjs_uint32);
					}
				}
				else
				{
					for (tjs_int k = h; k; k -= 1)
					{
						tjs_uint32 *v29 = &write_buffer_offset[l];
						tjs_int m;
						for (m = w; m >= 2; m -= 2)
						{
							cur_seed = 0x7D2B89DD * cur_seed + 1;
							tjs_int v34 = cur_seed;
							cur_seed = 0x7D2B89DD * cur_seed + 1;
							tjs_int v36 = cur_seed;
							cur_seed = 0x7D2B89DD * cur_seed + 1;
							tjs_int v35 = cur_seed;
							*v29++ = (((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)v36) >> 16)) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)HIWORD(v34)) >> 16)) << 8) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)v34) >> 16)) << 16)) & 0xFFFFFF) | 0xFF000000;
							*v29++ = (((tjs_uint8)(under + ((upper_under_diff * (unsigned int)HIWORD(v35)) >> 16)) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)v35) >> 16)) << 8) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)HIWORD(v36)) >> 16)) << 16)) & 0xFFFFFF) | 0xFF000000;
						}
						while (m)
						{
							cur_seed = 0x7D2B89DD * cur_seed + 1;
							tjs_int v34 = cur_seed;
							cur_seed = 0x7D2B89DD * cur_seed + 1;
#if 0
							// Not used. Oops
							tjs_int v36 = cur_seed;
#endif
							*v29++ = (((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)cur_seed) >> 16)) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)HIWORD(v34)) >> 16)) << 8) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)v34) >> 16)) << 16)) & 0xFFFFFF) | 0xFF000000;
							m -= 1;
						}
						write_buffer_offset += mainImageBufferPitch / sizeof(tjs_uint32);
					}
				}
				goto LABEL_159;
			}
			if (upper_under_diff != 255)
			{
				for (tjs_int n = h; n; n -= 1)
				{
					tjs_uint32 *v38 = &write_buffer_offset[l];
					tjs_int ii;
					for (ii = w; ii >= 2; ii -= 2)
					{
						cur_seed = 0x7D2B89DD * cur_seed + 1;
						tjs_int v43 = cur_seed;
						*v38++ = (((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)cur_seed) >> 16)) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)cur_seed) >> 16)) << 8) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)cur_seed) >> 16)) << 16)) & 0xFFFFFF) | 0xFF000000;
						tjs_int v42 = (tjs_uint8)(under + ((upper_under_diff * (unsigned int)HIWORD(v43)) >> 16));
						*v38++ = ((v42 | (v42 << 8) | (v42 << 16)) & 0xFFFFFF) | 0xFF000000;
					}
					while (ii)
					{
						cur_seed = 0x7D2B89DD * cur_seed + 1;
						tjs_int v42 = (tjs_uint8)(under + ((upper_under_diff * (unsigned int)HIWORD(cur_seed)) >> 16));
						*v38++ = ((v42 | (v42 << 8) | (v42 << 16)) & 0xFFFFFF) | 0xFF000000;
						ii -= 1;
					}
					write_buffer_offset += mainImageBufferPitch / sizeof(tjs_uint32);
				}
				goto LABEL_159;
			}
			for (tjs_int jj = h;; jj -= 1)
			{
				if (!jj)
					goto LABEL_159;
				tjs_uint32 *v40 = &write_buffer_offset[l];
				tjs_int kk;
				for (kk = w; kk >= 3; kk -= 3)
				{
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					tjs_int v43 = cur_seed;
					*v40++ = HIBYTE(cur_seed) | ((cur_seed >> 16) & 0xFF00) | ((cur_seed >> 8) & 0xFF0000) | 0xFF000000;
					*v40++ = BYTE2(v43) | ((v43 >> 8) & 0xFF00) | (v43 & 0xFF0000) | 0xFF000000;
					*v40++ = BYTE1(v43) | (v43 & 0xFF00) | ((v43 << 8) & 0xFF0000) | 0xFF000000;
				}
				cur_seed = 0x7D2B89DD * cur_seed + 1;
				tjs_int v43 = cur_seed;
				if (kk != 1)
				{
					if (kk != 2)
						goto LABEL_126;
					*v40++ = HIBYTE(v43) | ((v43 >> 16) & 0xFF00) | ((v43 >> 8) & 0xFF0000) | 0xFF000000;
				}
				*v40++ = BYTE2(v43) | ((v43 >> 8) & 0xFF00) | (v43 & 0xFF0000) | 0xFF000000;
			LABEL_126:
				write_buffer_offset += mainImageBufferPitch / sizeof(tjs_uint32);
			}
		}
		if (monocro)
		{
			if (upper_under_diff == 255)
			{
				for (tjs_int mm = h;; mm -= 1)
				{
					if (!mm)
						goto LABEL_159;
					tjs_uint32 *v57 = &write_buffer_offset[l];
					tjs_int nn;
					for (nn = w; nn >= 3; nn -= 3)
					{
						cur_seed = 0x7D2B89DD * cur_seed + 1;
						tjs_int v60 = cur_seed;
						*v57 = HIBYTE(cur_seed) | ((cur_seed >> 16) & 0xFF00) | ((cur_seed >> 8) & 0xFF0000) | (*v57 & 0xFF000000);
						v57 += 1;
						*v57 = BYTE2(v60) | ((v60 >> 8) & 0xFF00) | (v60 & 0xFF0000) | (*v57 & 0xFF000000);
						v57 += 1;
						*v57 = BYTE1(v60) | (v60 & 0xFF00) | ((v60 << 8) & 0xFF0000) | (*v57 & 0xFF000000);
						v57 += 1;
					}
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					tjs_int v60 = cur_seed;
					if (nn != 1)
					{
						if (nn != 2)
							goto LABEL_81;
						*v57 = HIBYTE(v60) | ((v60 >> 16) & 0xFF00) | ((v60 >> 8) & 0xFF0000) | (*v57 & 0xFF000000);
						v57 += 1;
					}
					*v57 = BYTE2(v60) | ((v60 >> 8) & 0xFF00) | (v60 & 0xFF0000) | (*v57 & 0xFF000000);
					v57 += 1;
				LABEL_81:
					write_buffer_offset += mainImageBufferPitch / sizeof(tjs_uint32);
				}
			}
			for (tjs_int i1 = h; i1; i1 -= 1)
			{
				tjs_uint32 *v55 = &write_buffer_offset[l];
				tjs_int i2;
				for (i2 = w; i2 >= 2; i2 -= 2)
				{
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					tjs_int v60 = cur_seed;
					*v55 = (((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)cur_seed) >> 16)) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)cur_seed) >> 16)) << 8) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)cur_seed) >> 16)) << 16)) & 0xFFFFFF) | (*v55 & 0xFF000000);
					v55 += 1;
					tjs_int v59 = (tjs_uint8)(under + ((upper_under_diff * (unsigned int)HIWORD(v60)) >> 16));
					*v55 = ((v59 | (v59 << 8) | (v59 << 16)) & 0xFFFFFF) | (*v55 & 0xFF000000);
					v55 += 1;
				}
				while (i2)
				{
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					tjs_int v59 = (tjs_uint8)(under + ((upper_under_diff * (unsigned int)HIWORD(cur_seed)) >> 16));
					*v55 = ((v59 | (v59 << 8) | (v59 << 16)) & 0xFFFFFF) | (*v55 & 0xFF000000);
					v55 += 1;
					i2 -= 1;
				}
				write_buffer_offset += mainImageBufferPitch / sizeof(tjs_uint32);
			}
		}
		else if (upper_under_diff == 255)
		{
			for (tjs_int i3 = h; i3; i3 -= 1)
			{
				tjs_uint32 *v49 = &write_buffer_offset[l];
				tjs_int i4;
				for (i4 = w; i4 >= 4; i4 -= 4)
				{
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					*v49 = ((cur_seed >> 8) & 0xFFFFFF) | (*v49 & 0xFF000000);
					v49 += 1;
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					*v49 = ((cur_seed >> 8) & 0xFFFFFF) | (*v49 & 0xFF000000);
					v49 += 1;
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					*v49 = ((cur_seed >> 8) & 0xFFFFFF) | (*v49 & 0xFF000000);
					v49 += 1;
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					*v49 = ((cur_seed >> 8) & 0xFFFFFF) | (*v49 & 0xFF000000);
					v49 += 1;
					cur_seed = 0x7D2B89DD * cur_seed + 1;
				}
				if (i4 > 2)
				{
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					*v49 = ((cur_seed >> 8) & 0xFFFFFF) | (*v49 & 0xFF000000);
					v49 += 1;
				}
				if (i4 > 1)
				{
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					*v49 = ((cur_seed >> 8) & 0xFFFFFF) | (*v49 & 0xFF000000);
					v49 += 1;
				}
				if (i4 > 0)
				{
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					*v49 = ((cur_seed >> 8) & 0xFFFFFF) | (*v49 & 0xFF000000);
					v49 += 1;
				}
				write_buffer_offset += mainImageBufferPitch / sizeof(tjs_uint32);
			}
		}
		else
		{
			for (tjs_int i5 = h; i5; i5 -= 1)
			{
				tjs_uint32 *v46 = &write_buffer_offset[l];
				tjs_int i6;
				for (i6 = w; i6 >= 2; i6 -= 2)
				{
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					tjs_int v51 = cur_seed;
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					tjs_int v53 = cur_seed;
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					tjs_int v52 = cur_seed;
					*v46 = (((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)v53) >> 16)) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)HIWORD(v51)) >> 16)) << 8) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)v51) >> 16)) << 16)) & 0xFFFFFF) | (*v46 & 0xFF000000);
					v46 += 1;
					*v46 = (((tjs_uint8)(under + ((upper_under_diff * (unsigned int)HIWORD(v52)) >> 16)) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)v52) >> 16)) << 8) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)HIWORD(v53)) >> 16)) << 16)) & 0xFFFFFF) | (*v46 & 0xFF000000);
					v46 += 1;
				}
				while (i6)
				{
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					tjs_int v51 = cur_seed;
					cur_seed = 0x7D2B89DD * cur_seed + 1;
#if 0
					// not used. Oops
					tjs_int v53 = cur_seed;
#endif
					*v46 = (((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)cur_seed) >> 16)) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)HIWORD(v51)) >> 16)) << 8) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)v51) >> 16)) << 16)) & 0xFFFFFF) | (*v46 & 0xFF000000);
					v46 += 1;
					i6 -= 1;
				}
				write_buffer_offset += mainImageBufferPitch / sizeof(tjs_uint32);
			}
		}
	LABEL_159:
		UpdateWholeLayerWithLayerObject(bmpobject_clo);
		return TJS_S_OK;
	}

	static tjs_error TJS_INTF_METHOD doContrast(
		tTJSVariant *result,
		tjs_int numparams,
		tTJSVariant **param,
		iTJSDispatch2 *objthis)
	{
		if (numparams < 0)
			return -1004;

		int contrast = 0;
		if (numparams > 0 && param[0]->Type() != tvtVoid)
			contrast = *param[0];

		if (objthis == NULL)
			TVPThrowExceptionMessage(TJS_W("Specify Layer or Bitmap class object"));
		tTJSVariant bmpobject = tTJSVariant(objthis, objthis);
		tTJSVariantClosure bmpobject_clo = bmpobject.AsObjectClosureNoAddRef();

		// Now get information (this will independ the bitmap)
		tjs_int imageWidth = 0;
		tjs_int imageHeight = 0;
		tjs_int mainImageBufferPitch = 0;
		tjs_uint32 *mainImageBufferForWrite = NULL;
		GetBitmapInformationFromObject(bmpobject_clo, true, &imageWidth, &imageHeight, &mainImageBufferPitch, (tjs_uint8 **)&mainImageBufferForWrite);
		if (!mainImageBufferForWrite)
			TVPThrowExceptionMessage(TJS_W("Specify Layer or Bitmap class object"));
		if (contrast)
		{
			if (contrast >= -127)
			{
				if (contrast > 127)
					contrast = 127;
			}
			else
			{
				contrast = -127;
			}
			tjs_uint32 Block[0x100];
			if (contrast <= 0)
			{
				for (int i = 0; i < 256; i += 1)
					Block[i] = i * (2 * contrast + 255) / 255 - contrast;
			}
			else
			{
				int j = 0;
				for (j = 0; j < contrast; j += 1)
					Block[j] = 0;
				while (j < (255 - contrast))
				{
					Block[j] = 255 * (j - contrast) / (255 - 2 * contrast);
					j += 1;
				}
				while (j < 256)
				{
					Block[j] = 255;
					j += 1;
				}
			}
			tjs_uint32 *v26 = mainImageBufferForWrite;
			for (tjs_int k = imageHeight; k; k -= 1)
			{
				tjs_uint32 *v13 = v26;
				for (tjs_int m = imageWidth; m; m -= 1)
				{
					*v13 = Block[(tjs_uint8)*v13] | (Block[(tjs_uint8)BYTE1(*v13)] << 8) | (Block[(tjs_uint8)BYTE2(*v13)] << 16) | (*v13 & 0xFF000000);
					v13 += 1;
				}
				v26 += mainImageBufferPitch / sizeof(tjs_uint32);
			}
			UpdateWholeLayerWithLayerObject(bmpobject_clo);
		}
		return TJS_S_OK;
	}
};

NCB_ATTACH_CLASS(LayerLayerExFilter, Layer)
{
	// @ 0x10003550
	RawCallback("initHazeCopy", &Class::initHazeCopy, 0);
	// @ 0x10003C30
	RawCallback("uninitHazeCopy", &Class::uninitHazeCopy, 0);
	// @ 0x10004160
	RawCallback("hazeCopy", &Class::hazeCopy, 0);
	// @ 0x100018BC
	RawCallback("drawNoise", &Class::drawNoise, 0);
	// @ 0x100030A0
	RawCallback("doContrast", &Class::doContrast, 0);
};
