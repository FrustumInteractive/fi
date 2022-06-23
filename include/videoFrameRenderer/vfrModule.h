#ifndef _VFR_MODULE_H
#define _VFR_MODULE_H

#include <unordered_map>
#include <vector>
#include <iostream>

namespace FI {
	enum UniformType
	{
		INT,
		INT2,
		INT3,
		INT4,
		FLOAT,
		FLOAT2,
		FLOAT3,
		FLOAT4,
		MAT3,
		MAT4
	};

	typedef std::unordered_map<std::string, std::string> VFRParamMap;
}

struct VFRFrame
{
	VFRFrame()
		: width(0)
		, height(0)
		, channels(0)
		, data(nullptr)
	{}

	unsigned int
		width,
		height,
		channels;

	uint8_t *data;
};

struct VFRUniform
{
	int location;
	FI::UniformType type;

	union {
		float fval[4];
		int ival[4];
		float mat4[16];
		float mat3[9];
	};
};

struct VFRPass
{
	const char
		*vsCode,
		*fsCode;

	bool isTexture; // output will be texture for next

	size_t
		width, // dimensions of output texture
		height;

	std::unordered_map<const char*, VFRUniform> uniformMap;
};

class VFRModule
{
public:

	VFRModule()
		: name("unknown")
		, vsCode(nullptr)
		, fsCode(nullptr)
		, pixelAspectRatio(1.0f)
	{
		passes.clear();
		fileTypes.clear();
		uniformMap.clear();
	}

	virtual ~VFRModule()
	{
		passes.clear();
		fileTypes.clear();
		uniformMap.clear();
	}

	virtual void initUniforms() {}
	virtual void setUniforms(
		int x,
		int y,
		int w,
		int h,
		int videoWidth,
		int videoHeight,
		int dispResX,
		int dispRexY,
		const FI::VFRParamMap *pm = nullptr
	){}
	virtual void activate() {}
	virtual void deactivate() {}
	virtual void resize(int w, int h) {}

	virtual bool open(const char* path) { return false; }

	virtual VFRFrame frameData() { VFRFrame out; return out; }

	void printParameters(const FI::VFRParamMap *pm)
	{
		if(!pm) {
			std::cout << " error: no parameters set\n";
			return;
		}

		std::cout << name << " paramters: " << "\n";
		for(auto p : *pm) {
			std::cout << "  key: " << p.first << " val: " << p.second << std::endl;
		}
	}

	const char
		*name,
		*vsCode,
		*fsCode;

	float pixelAspectRatio;

	std::vector<VFRPass> passes;

	std::vector<const char*> fileTypes;

	std::unordered_map<const char*, VFRUniform> uniformMap;
};

#endif /*_VFR_MODULE_H*/