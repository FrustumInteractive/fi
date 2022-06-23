#ifndef _UISLIDER_H
#define _UISLIDER_H

#include "element.h"

namespace FI { namespace GFX {

class UISlider : public UIElement
{
public:
	UISlider();
	UISlider(std::string name,
             const MATH::vec3 &position,
             const MATH::vec3 &scale,
			 float value = 0 );

	virtual ~UISlider();

protected:

	void _onUpdate() override;
	void _onHover(float x, float y, float z) override;
	void _onClick(float x, float y, float z) override;
	void _onRelease(float x, float y, float z) override;
	void _onDrag(float x, float y, float z) override;
	void _onRightClick(float x, float y, float z) override;
	void _onRightRelease(float x, float y, float z) override;
	void _onRightDrag(float x, float y, float z) override;
	void _onValueChange() override;

	void initSlider();	// common init routine

	float	mEdgeOffset,
			mMaxPos,
			mMinPos,
			mClickPos;
	
	UIElement 	*mSlide,
				*mSlideTrack;
	
};

} //ns GFX
} /* namepsace FI */

#endif /*_UISLIDER_H*/
