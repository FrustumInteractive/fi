#ifndef _TEXTELEMENT_H
#define _TEXTELEMENT_H

#include "element.h"

namespace FI { namespace GFX {

class UIText : public UIElement
{

public:
	UIText();
	UIText(std::string name,
           std::string text,
           const FI::MATH::vec3 &position,
           const FI::MATH::vec3 &scale);

	virtual ~UIText();

	void _onUpdate() override;

	void setSpacingPercent( float percent );

	void setFontSize(float size);

	void setFontAspect(float aspect);

	void setText( std::string s );

protected:

	void clearCharObjects();

	std::string mTextString;	
	float mSpacing;
	float mFontSize;
	float mFontAspect;

	size_t mStringSize;

	static Geometry::TexCoordRect4f s_charTCList[256]; // 256 possible chars (16X16)
	static bool	s_isCharTCListBuilt;                   // flag for if the TC list has been generated
	static void buildCharTCList();                     // one time build of char tc list based on 16x16 grid
};

} // ns GFX
} // ns FI

#endif /*_TEXTELEMENT_H*/
