#ifndef _ELEMENT_H
#define _ELEMENT_H

#include <stdio.h>
#include <vector>
#include <string>
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/matrix.h"
#include "application/event.h"
#include "graphics/geometry/object.h"

namespace FI{ namespace GFX {

//class UIEvent;
//class UIEventListener;

class UIElement : public FI::EventListener
{
public:
	UIElement()
	{
		s_totalElements++;
	}

    UIElement(std::string name, const FI::MATH::vec3 &position, const FI::MATH::vec3 &scale);

	virtual ~UIElement();

	// rendering related
	Geometry::Object &geometryObject(); // returns pointer to GeometryObject for this element (hierarchy is intact)

	// core data members
	const char* name(){ return mName.c_str(); };
	float *values(){return mValues;}
	float xValue(){return mValues[0];}
	float yValue(){return mValues[1];}
	void setXValue(float value);
	void setYValue(float value);

	// position
	float x();
	float y();
	float z();
	FI::MATH::vec3 position();
	void setPosition( const FI::MATH::vec3 &v );

	// size / scale
	float w();
	float h();
	float d();
	FI::MATH::vec3 scale();
	void setScale( const FI::MATH::vec3 &v );

	// color
	float r();
	float g();
	float b();
	float a();
	FI::MATH::vec3 color();
	void setColor(const FI::MATH::vec3 &c);
    void setActiveColor(const FI::MATH::vec3 &c);
    void setDisabledColor(const FI::MATH::vec3 &c);
	void setAlpha(float a);

	// texture
	void setTextureID( unsigned int id );
	void setTexCoords(float smin, float tmin, float smax, float tmax);
    void setTexCoordsActive(float smin, float tmin, float smax, float tmax);

	// animation
	void setAnimationTicks( unsigned int ticks );

	// state
	void setDrawable( bool d );
	void activate();
	void deactivate();
	void show();
	void hide();
	void enable();
	void disable();
	bool isHidden();
	bool isEnabled();
	bool isActive();

	// resize
	//virtual void resize();

	// drawing / events
	//void registerEventListener( UIEventListener *el );
	//void unregisterEventListener( UIEventListener *el );
	virtual void update();

	// hierarchy
	void addChild( UIElement *child );
	UIElement *child( size_t index );
	UIElement *parent() { return mParent; }
	void removeChild( UIElement *child );
	void removeChild( size_t childNumber );

protected:

	virtual void _onShow(){}
	virtual void _onHide(){}
	virtual void _onUpdate(){}
	virtual void _onValueChange(){}

	virtual void _onDrag(float x, float y, float z){}
	virtual void _onHover(float x, float y, float z){}
	virtual void _onClick(float x, float y, float z){}
	virtual void _onRelease(float x, float y, float z){}

	virtual void _onRightDrag(float x, float y, float z){}
	virtual void _onRightClick(float x, float y, float z){}
	virtual void _onRightRelease(float x, float y, float z){}

	// geom
	void transform(FI::MATH::vec3 position, FI::MATH::vec3 rotationAxis, float rotationAngle, FI::MATH::vec3 scale);

	void setCurrentColor(const FI::MATH::vec3 &c);
	void setCurrentAlpha(float a);
	void setCurrentTC(float smin, float tmin, float smax, float tmax);

	std::string	mName;

	FI::MATH::vec3
		mPosition{0,0,0},
		mRotationAxis{0,0,0},
		mScale{1.0f, 1.0f, 1.0f},
		mColor{0.8f, 0.8f, 0.8f},  // original spec'd color
		mCurrentColor{0,0,0}, // color currentl set to render
		mActiveColor{mColor},  // can be used as hover color too
		mDisabledColor{0.4f, 0.4f, 0.4f};

	bool
		mIsEnabled{true},
		mIsHidden{false},
		mIsActive{false},
		mIsHovering{false},
		mIsActiveColorSet{false},
		mIsActiveTCSet{false};

	int mIsDrawableUserSetting{-1}; // -1 means never set by user

	uint32_t
		mTickCount{0}, //for animation
		mAnimationTicks{25};

	float
		mValues[2]{0,0},
		mAlpha{1},
		mCurrentAlpha{mAlpha},
		mRotationAngle{0},
		mTcRect[4]{0,0,1,1}, // texcoords sent to shader specifying tile in tex atlas
		mTcRectCurrent[4]{0,0,1,1},
		mTcRectActive[4]{0,0,1,1};

	UIElement *mParent{nullptr};

	FI::MATH::Matrix mMatrix;

	Geometry::Object mObject{"UIElement", 0, 4, 0 ,2}; //the first 4 verts / 2 faces in VBO/IBO as UI quad

	std::vector<UIElement *> mChildren;

	// STATIC
	static uint32_t
		s_totalElements,	// total number of elements ever created
		s_textureID;		// use same global texture for all UI elements in form of texture atlas

private:

	// Application overrides
	void onResize(FI::Event e) override;
	void onMove(FI::Event e) override;
	void onShow(FI::Event e) override;
	void onHide(FI::Event e) override;
	void onRedraw(FI::Event e) override;
	void onUpdate(FI::Event e) override;

	void onMouseMove(FI::Event e) override;
	void onMouseLeftClick(FI::Event e) override;
	void onMouseLeftRelease(FI::Event e) override;
	void onMouseLeftDrag(FI::Event e) override;
	void onMouseRightClick(FI::Event e) override;
	void onMouseRightRelease(FI::Event e) override;
	void onMouseRightDrag(FI::Event e) override;
	void onKeyPress(FI::Event e) override;
	void onKeyRelease(FI::Event e) override;
	void onValueChange(FI::Event e) override;
};

} // ns GFX
} /* namespace FI */

#endif /*_ELEMENT_H*/
