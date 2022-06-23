#ifndef _UITHUMBSTICK_H
#define _UITHUMBSTICK_H

#include "element.h"

namespace FI { namespace GFX {

	class UIThumbstick : public UIElement
	{
	public:
		UIThumbstick();
		UIThumbstick(std::string name,
				 const MATH::vec3 &position,
				 const MATH::vec3 &scale);

		virtual ~UIThumbstick();

	protected:

		void _onUpdate() override;
		void _onClick(float x, float y, float z) override;
		void _onRelease(float x, float y, float z) override;
		void _onDrag(float x, float y, float z) override;

		void _onValueChange() override;

		void init();	// common init routine

		float	mEdgeOffset,
				mMaxPos,
				mMinPos,
				mClickPos;
		
		Geometry::Object mStickObject;
	};

} //ns GFX
} /* namepsace FI */

#endif /*_UITHUMBSTICK_H*/
