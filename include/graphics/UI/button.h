#ifndef _UIBUTTON_H
#define _UIBUTTON_H

#include "element.h"

namespace FI { namespace GFX{

class UIButton : public UIElement
{
public:
	UIButton();
	UIButton(std::string name,
             const FI::MATH::vec3 &position,
             const FI::MATH::vec3 &scale );

	virtual ~UIButton();

	void setActivationColor( const FI::MATH::vec3 &c );
	void setOnColor( const FI::MATH::vec3 &c );
	void setOffColor( const FI::MATH::vec3 &c );

	void setActivationTC( float mins, float mint, float maxs, float maxt );
	void setOnTC( float mins, float mint, float maxs, float maxt );
	void setOffTC( float mins, float mint, float maxs, float maxt );

	void setToggle( bool state );

protected:

	void _onUpdate() override;
	void _onHover(float x, float y, float z) override;
	void _onClick(float x, float y, float z) override;
	void _onRightClick(float x, float y, float z) override;

	MATH::vec3
		mActivationColor, // while mouse is held down on button
		mOnColor,
		mOffColor;

	bool
		mIsActivating,
		mIsOn,
		mIsToggle,
		mIsChanged;

	float
		*mActivationTC,
		*mOnTC,
		*mOffTC,
		*mHoverTC;
};

} //ns GFX
} /* namespace FI */

#endif /*_UIBUTTON_H*/
