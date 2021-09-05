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

class LayerLayerExFilter
{
public:
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
					for (tjs_int i = h; i; --i)
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
					for (tjs_int k = h; k; --k)
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
							--m;
						}
						write_buffer_offset += mainImageBufferPitch / sizeof(tjs_uint32);
					}
				}
				goto LABEL_159;
			}
			if (upper_under_diff != 255)
			{
				for (tjs_int n = h; n; --n)
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
						--ii;
					}
					write_buffer_offset += mainImageBufferPitch / sizeof(tjs_uint32);
				}
				goto LABEL_159;
			}
			for (tjs_int jj = h;; --jj)
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
				for (tjs_int mm = h;; --mm)
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
						++v57;
						*v57 = BYTE2(v60) | ((v60 >> 8) & 0xFF00) | (v60 & 0xFF0000) | (*v57 & 0xFF000000);
						++v57;
						*v57 = BYTE1(v60) | (v60 & 0xFF00) | ((v60 << 8) & 0xFF0000) | (*v57 & 0xFF000000);
						++v57;
					}
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					tjs_int v60 = cur_seed;
					if (nn != 1)
					{
						if (nn != 2)
							goto LABEL_81;
						*v57 = HIBYTE(v60) | ((v60 >> 16) & 0xFF00) | ((v60 >> 8) & 0xFF0000) | (*v57 & 0xFF000000);
						++v57;
					}
					*v57 = BYTE2(v60) | ((v60 >> 8) & 0xFF00) | (v60 & 0xFF0000) | (*v57 & 0xFF000000);
					++v57;
				LABEL_81:
					write_buffer_offset += mainImageBufferPitch / sizeof(tjs_uint32);
				}
			}
			for (tjs_int i1 = h; i1; --i1)
			{
				tjs_uint32 *v55 = &write_buffer_offset[l];
				tjs_int i2;
				for (i2 = w; i2 >= 2; i2 -= 2)
				{
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					tjs_int v60 = cur_seed;
					*v55 = (((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)cur_seed) >> 16)) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)cur_seed) >> 16)) << 8) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)cur_seed) >> 16)) << 16)) & 0xFFFFFF) | (*v55 & 0xFF000000);
					++v55;
					tjs_int v59 = (tjs_uint8)(under + ((upper_under_diff * (unsigned int)HIWORD(v60)) >> 16));
					*v55 = ((v59 | (v59 << 8) | (v59 << 16)) & 0xFFFFFF) | (*v55 & 0xFF000000);
					++v55;
				}
				while (i2)
				{
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					tjs_int v59 = (tjs_uint8)(under + ((upper_under_diff * (unsigned int)HIWORD(cur_seed)) >> 16));
					*v55 = ((v59 | (v59 << 8) | (v59 << 16)) & 0xFFFFFF) | (*v55 & 0xFF000000);
					++v55;
					--i2;
				}
				write_buffer_offset += mainImageBufferPitch / sizeof(tjs_uint32);
			}
		}
		else if (upper_under_diff == 255)
		{
			for (tjs_int i3 = h; i3; --i3)
			{
				tjs_uint32 *v49 = &write_buffer_offset[l];
				tjs_int i4;
				for (i4 = w; i4 >= 4; i4 -= 4)
				{
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					*v49 = ((cur_seed >> 8) & 0xFFFFFF) | (*v49 & 0xFF000000);
					++v49;
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					*v49 = ((cur_seed >> 8) & 0xFFFFFF) | (*v49 & 0xFF000000);
					++v49;
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					*v49 = ((cur_seed >> 8) & 0xFFFFFF) | (*v49 & 0xFF000000);
					++v49;
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					*v49 = ((cur_seed >> 8) & 0xFFFFFF) | (*v49 & 0xFF000000);
					++v49;
					cur_seed = 0x7D2B89DD * cur_seed + 1;
				}
				if (i4 > 2)
				{
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					*v49 = ((cur_seed >> 8) & 0xFFFFFF) | (*v49 & 0xFF000000);
					++v49;
				}
				if (i4 > 1)
				{
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					*v49 = ((cur_seed >> 8) & 0xFFFFFF) | (*v49 & 0xFF000000);
					++v49;
				}
				if (i4 > 0)
				{
					cur_seed = 0x7D2B89DD * cur_seed + 1;
					*v49 = ((cur_seed >> 8) & 0xFFFFFF) | (*v49 & 0xFF000000);
					++v49;
				}
				write_buffer_offset += mainImageBufferPitch / sizeof(tjs_uint32);
			}
		}
		else
		{
			for (tjs_int i5 = h; i5; --i5)
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
					++v46;
					*v46 = (((tjs_uint8)(under + ((upper_under_diff * (unsigned int)HIWORD(v52)) >> 16)) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)(tjs_uint16)v52) >> 16)) << 8) | ((tjs_uint8)(under + ((upper_under_diff * (unsigned int)HIWORD(v53)) >> 16)) << 16)) & 0xFFFFFF) | (*v46 & 0xFF000000);
					++v46;
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
					++v46;
					--i6;
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
				for (int i = 0; i < 256; ++i)
					Block[i] = i * (2 * contrast + 255) / 255 - contrast;
			}
			else
			{
				int j = 0;
				for (j = 0; j < contrast; ++j)
					Block[j] = 0;
				while (j < (255 - contrast))
				{
					Block[j] = 255 * (j - contrast) / (255 - 2 * contrast);
					++j;
				}
				while (j < 256)
					Block[j++] = 255;
			}
			tjs_uint32 *v26 = mainImageBufferForWrite;
			for (tjs_int k = imageHeight; k; --k)
			{
				tjs_uint32 *v13 = v26;
				for (tjs_int m = imageWidth; m; --m)
				{
					*v13 = Block[(tjs_uint8)*v13] | (Block[(tjs_uint8)BYTE1(*v13)] << 8) | (Block[(tjs_uint8)BYTE2(*v13)] << 16) | (*v13 & 0xFF000000);
					++v13;
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
	// @ 0x100018BC
	RawCallback("drawNoise", &Class::drawNoise, 0);
	// @ 0x100030A0
	RawCallback("doContrast", &Class::doContrast, 0);
};
