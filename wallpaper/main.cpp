
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ncbind.hpp"
#include <wininet.h>
#include <shlobj.h>
#include <shlguid.h>

static tjs_error TJS_INTF_METHOD
getwallpaper(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 10008110 10001C40 not used
	//ret = string
	HKEY key;
	wchar_t buf[1024];
	memset(&buf, 0, sizeof(buf));
	DWORD bufsize = 1024;
	RegOpenKeyW(HKEY_CURRENT_USER, TJS_W("Control Panel\\desktop\\"), &key);
	RegQueryValueExW(key, TJS_W("Wallpaper"), NULL, NULL, (LPBYTE)buf, &bufsize);
	RegCloseKey(key);
	if (result)
	{
		*result = ttstr(buf);
	}
	return TJS_S_OK;
}

static tjs_error TJS_INTF_METHOD
setwallpaper(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000818C 10001200
	//possible 3 arguments with varying types
	//arg1 = iTJSDispatch2 * tTJSVariant::AsObjectNoAddRef() const
	// storage: 
	// tile: tTVInteger tTJSVariant::AsInteger() const
	// magnify: tTVInteger tTJSVariant::AsInteger() const
	// center: (not read by code)
	iTJSDispatch2 *v14;
	tjs_int magnify_var;
	tjs_int v42;
	ttstr v44;
	IActiveDesktop *ppv;
	ttstr v78;
	HKEY phkResult;
	tjs_int tile_var;
	ttstr v82;
	ttstr v83;
	COMPONENTSOPT v84;
	tTJSVariant storage_variant;
	ttstr v88;

	if (numparams == 0)
	{
		return TJS_E_BADPARAMCOUNT;
	}
	if (param[0]->Type() == tvtObject)
	{
		tTJSVariant tmp_var;
		v14 = param[0]->AsObjectNoAddRef();
		if (v14->PropGet(TJS_MEMBERMUSTEXIST, TJS_W("storage"), 0, &storage_variant, v14) < 0)
		{
			TVPThrowExceptionMessage(TJS_W("storage(設定する壁紙)が指定されていないよ。\n壁紙を消すときは「storage=\"\"」って指定してね。"));
			return TJS_E_INVALIDPARAM;
		}
		if ((&storage_variant)->Type() != tvtString)
		{
			TVPThrowExceptionMessage(TJS_W("storageが文字列じゃないよ。"));
			return TJS_E_INVALIDPARAM;
		}
		tile_var = (v14->PropGet(TJS_MEMBERMUSTEXIST, TJS_W("tile"), 0, (tTJSVariant *)&tmp_var, v14) >= 0 && (&tmp_var)->AsInteger()) ? 1 : 0;
		magnify_var = (v14->PropGet(TJS_MEMBERMUSTEXIST, TJS_W("magnify"), 0, (tTJSVariant *)&tmp_var, v14) >= 0 && (&tmp_var)->AsInteger()) ? 1 : 0;
	}
	else
	{
		if (param[0]->Type() != tvtString)
		{
			TVPThrowExceptionMessage(TJS_W("storageが文字列じゃないよ。"));
			return TJS_E_INVALIDPARAM;
		}
		storage_variant = param[0];
		tile_var = (numparams > 1 && param[1]->Type() == tvtInteger && param[1]->AsInteger()) ? 1 : 0;
		magnify_var = (numparams > 2 && param[2]->Type() == tvtInteger && param[2]->AsInteger()) ? 1 : 0;
	}
	static const tjs_char *wallpaper_image_extensions[] = {TJS_W(".bmp"), TJS_W(".png"), TJS_W(".jpg")};
	v42 = 0;
	v44 = storage_variant.AsString();
	v83 = TVPExtractStorageExt(v44);
	if ((&v83)->GetLen() > 0)
	{
		(&v83)->ToLowerCase();
		v42 = 2;
		do
		{
			// Matching against ".bmp", ".png", ".jpg"
			if (v83 == wallpaper_image_extensions[v42])
			{
				break;
			}
			v42 -= 1;
		}
		while (v42 >= 0);
	}
	v88 = TVPChopStorageExt(v44);
	v78 = TJS_W("");
	if (v42 < 3)
	{
		for (;;)
		{
			// Matching against ".bmp", ".png", ".jpg"
			v82 = v88 + ttstr(wallpaper_image_extensions[v42]);
			if (TVPIsExistentStorage(v82))
			{
				break;
			}
			v42 += 1;
			if (v42 >= 3)
			{
				goto LABEL_116;
			}
		}
		v78 = TVPGetPlacedPath(v82);
		TVPGetLocalName(v78);
	}
LABEL_116:
	TVPAddLog(ttstr(TJS_W("search result: ")) + v78);
	RegOpenKeyW(HKEY_CURRENT_USER, TJS_W("Control Panel\\desktop\\"), &phkResult);
	RegSetValueExW(phkResult, TJS_W("Wallpaper"), 0, REG_SZ, (const BYTE *)v78.c_str(), (v78.GetLen() + 1) * sizeof(tjs_char));
	RegSetValueExW(phkResult, TJS_W("TileWallpaper"), 0, REG_SZ, (const BYTE *)(tile_var ? TJS_W("1") : TJS_W("0")), 4);
	RegSetValueExW(phkResult, TJS_W("WallpaperStyle"), 0, REG_SZ, (const BYTE *)(magnify_var ? TJS_W("2") : TJS_W("0")), 4);
	RegCloseKey(phkResult);
	wchar_t *str_fn = wcsdup(v78.c_str());
	if (str_fn != NULL)
	{
		SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, str_fn, SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);
		free(str_fn);
	}
	if (v42 != 0) // not bmp
	{
		if (v78 != TJS_W(""))
		{
			CoInitialize(0);
			if (CoCreateInstance(CLSID_ActiveDesktop, 0, 1u, IID_IActiveDesktop, (LPVOID *)&ppv) >= 0)
			{
				v84.dwSize = sizeof(COMPONENTSOPT);
				v84.fEnableComponents = TRUE;
				v84.fActiveDesktop = TRUE;
				if (ppv->SetDesktopItemOptions(&v84, 0) >= 0)
				{
					ppv->ApplyChanges(7);
				}
				ppv->Release();
			}
			CoUninitialize();
		}
	}
	if (result)
	{
		*result = TJS_W("success");
	}
	TVPAddLog(ttstr(TJS_W("setwallpaper(")) + v78 + ttstr(TJS_W(") succeeded.")));
	return TJS_S_OK;
}

NCB_REGISTER_FUNCTION(getwallpaper, getwallpaper);
NCB_REGISTER_FUNCTION(setwallpaper, setwallpaper);
