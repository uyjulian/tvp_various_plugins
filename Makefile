
SOURCES += common/LayerBitmapUtility.cpp drawer/main.cpp filter/main.cpp layerExYADraw/main.cpp layerExFilter/main.cpp wallpaper/main.cpp

INCFLAGS += -Icommon

LDLIBS += -luuid -lole32

PROJECT_BASENAME = krkr_various_plugins

include external/ncbind/Rules.lib.make
