#include "ncbind/ncbind.hpp"

#include "layerexyadraw.h"

// ----------------------------------- Class registration

NCB_GET_INSTANCE_HOOK(layerExYADraw)
{
	// Instance getter
	NCB_INSTANCE_GETTER(objthis) { // objthis as an argument of type iTJSDispatch2*
		ClassT* obj = GetNativeInstance(objthis);	// Get Native Instance Pointer
		if (!obj) {
			obj = new ClassT(objthis);				// Generate if not
			SetNativeInstance(objthis, obj);		// Register obj as a native instance in objthis
		}
		obj->reset();
		return obj;
	}
	// Destructor (called after the actual method is called)
	~NCB_GET_INSTANCE_HOOK_CLASS () {
	}
};


// Attach with hook
NCB_ATTACH_CLASS_WITH_HOOK(layerExYADraw, Layer) {
	NCB_METHOD(drawFocusLines);
}
