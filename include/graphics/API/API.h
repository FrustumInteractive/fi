#ifndef _GFXAPI_H
#define _GFXAPI_H

#include <iostream>
#include <functional>
#include "graphics/API/shaderProgram.h"
#include "fiUtil.h"

namespace FI { namespace GFX {

typedef unsigned int FIenum;

//#define _DEBUG

#define STUB { LOG("NOT IMPLEMENTED"); }
#define STUBR { LOG("NOT IMPLEMENTED"); return 0; }

// API types
enum eAPIType
{
	API_NONE,
	API_D3D,
	API_OGL
};

enum eType // matches opengl definitions
{
	DATASIZE_BYTE 	= 0x1400,
	DATASIZE_UBYTE	= 0x1401,
	DATASIZE_SHORT	= 0x1402,
	DATASIZE_USHORT	= 0x1403,
	DATASIZE_INT	= 0x1404,
	DATASIZE_UINT 	= 0x1405,
	DATASIZE_FLOAT	= 0x1406,
	DATASIZE_DOUBLE	= 0x140A
};

enum eBufferType
{
	VERTEX_BUFFER,
	ELEMENT_BUFFER,
	CONSTANT_BUFFER,
	VS_CONSTANT_BUFFER,
	PS_CONSTANT_BUFFER,
	FRAME_BUFFER,
	RENDER_BUFFER
};

enum eUsage
{
	USAGE_DEFAULT 	= 0,
	USAGE_IMMUTABLE = 1,
	USAGE_STATIC  	= 1,
	USAGE_DYNAMIC 	= 2,
	USAGE_STAGING 	= 3
};

enum eGeomType 
{
	POINTS			= 0x0000,
	LINES			= 0x0001,
	LINE_LOOP		= 0x0002,
	LINE_STRIP		= 0x0003,
	TRIANGLES 		= 0x0004,
	TRIANGLE_STRIP	= 0x0005,
	TRIANGLE_FAN  	= 0x0006,
	QUADS 			= 0x0007
};

enum eFaceWinding
{
	FACE_CW,
	FACE_CCW
};

enum eFaceCullMode
{
	CULL_MODE_NONE,
	CULL_MODE_FRONT,
	CULL_MODE_BACK
};

enum eAttachment  //OpenGL mappings
{
	COLOR_ATTACHMENT0 = 0x8CE0,
	COLOR_ATTACHMENT1 = 0x8CE1,
	COLOR_ATTACHMENT2 = 0x8CE2,
	COLOR_ATTACHMENT3 = 0x8CE3,
	DEPTH_ATTACHMENT  = 0x8D00,
	STENCIL_ATTACHMENT= 0x8D20,
	DEPTH_STENCIL_ATTACHMENT = 0x821A
};

enum eInternalFormat
{
	RGB,
	RGBA,
	ALPHA,
	LUMINANCE,
	INTENSITY,
	DEPTH_COMPONENT,
	DEPTH_COMPONENT16,
	DEPTH_COMPONENT24,
	DEPTH_COMPONENTF32,
	DEPTH_STENCIL,
	DEPTH24_STENCIL8,
	DEPTH32F_STENCIL8,
	STENCIL_INDEX8,
	STENCIL
};

enum eFormat
{
	FORMAT_UNKNOWN                     = 0,
	FORMAT_R32G32B32A32_TYPELESS       = 1,
	FORMAT_R32G32B32A32_FLOAT          = 2,
	FORMAT_R32G32B32A32_UINT           = 3,
	FORMAT_R32G32B32A32_SINT           = 4,
	FORMAT_R32G32B32_TYPELESS          = 5,
	FORMAT_R32G32B32_FLOAT             = 6,
	FORMAT_R32G32B32_UINT              = 7,
	FORMAT_R32G32B32_SINT              = 8,
	FORMAT_R16G16B16A16_TYPELESS       = 9,
	FORMAT_R16G16B16A16_FLOAT          = 10,
	FORMAT_R16G16B16A16_UNORM          = 11,
	FORMAT_R16G16B16A16_UINT           = 12,
	FORMAT_R16G16B16A16_SNORM          = 13,
	FORMAT_R16G16B16A16_SINT           = 14,
	FORMAT_R32G32_TYPELESS             = 15,
	FORMAT_R32G32_FLOAT                = 16,
	FORMAT_R32G32_UINT                 = 17,
	FORMAT_R32G32_SINT                 = 18,
	FORMAT_R32G8X24_TYPELESS           = 19,
	FORMAT_D32_FLOAT_S8X24_UINT        = 20,
	FORMAT_R32_FLOAT_X8X24_TYPELESS    = 21,
	FORMAT_X32_TYPELESS_G8X24_UINT     = 22,
	FORMAT_R10G10B10A2_TYPELESS        = 23,
	FORMAT_R10G10B10A2_UNORM           = 24,
	FORMAT_R10G10B10A2_UINT            = 25,
	FORMAT_R11G11B10_FLOAT             = 26,
	FORMAT_R8G8B8A8_TYPELESS           = 27,
	FORMAT_R8G8B8A8_UNORM              = 28,
	FORMAT_R8G8B8A8_UNORM_SRGB         = 29,
	FORMAT_R8G8B8A8_UINT               = 30,
	FORMAT_R8G8B8A8_SNORM              = 31,
	FORMAT_R8G8B8A8_SINT               = 32,
	FORMAT_R16G16_TYPELESS             = 33,
	FORMAT_R16G16_FLOAT                = 34,
	FORMAT_R16G16_UNORM                = 35,
	FORMAT_R16G16_UINT                 = 36,
	FORMAT_R16G16_SNORM                = 37,
	FORMAT_R16G16_SINT                 = 38,
	FORMAT_R32_TYPELESS                = 39,
	FORMAT_D32_FLOAT                   = 40,
	FORMAT_R32_FLOAT                   = 41,
	FORMAT_R32_UINT                    = 42,
	FORMAT_R32_SINT                    = 43,
	FORMAT_R24G8_TYPELESS              = 44,
	FORMAT_D24_UNORM_S8_UINT           = 45,
	FORMAT_R24_UNORM_X8_TYPELESS       = 46,
	FORMAT_X24_TYPELESS_G8_UINT        = 47,
	FORMAT_R8G8_TYPELESS               = 48,
	FORMAT_R8G8_UNORM                  = 49,
	FORMAT_R8G8_UINT                   = 50,
	FORMAT_R8G8_SNORM                  = 51,
	FORMAT_R8G8_SINT                   = 52,
	FORMAT_R16_TYPELESS                = 53,
	FORMAT_R16_FLOAT                   = 54,
	FORMAT_D16_UNORM                   = 55,
	FORMAT_R16_UNORM                   = 56,
	FORMAT_R16_UINT                    = 57,
	FORMAT_R16_SNORM                   = 58,
	FORMAT_R16_SINT                    = 59,
	FORMAT_R8_TYPELESS                 = 60,
	FORMAT_R8_UNORM                    = 61,
	FORMAT_R8_UINT                     = 62,
	FORMAT_R8_SNORM                    = 63,
	FORMAT_R8_SINT                     = 64,
	FORMAT_A8_UNORM                    = 65,
	FORMAT_R1_UNORM                    = 66,
	FORMAT_R9G9B9E5_SHAREDEXP          = 67,
	FORMAT_R8G8_B8G8_UNORM             = 68,
	FORMAT_G8R8_G8B8_UNORM             = 69,
	FORMAT_BC1_TYPELESS                = 70,
	FORMAT_BC1_UNORM                   = 71,
	FORMAT_BC1_UNORM_SRGB              = 72,
	FORMAT_BC2_TYPELESS                = 73,
	FORMAT_BC2_UNORM                   = 74,
	FORMAT_BC2_UNORM_SRGB              = 75,
	FORMAT_BC3_TYPELESS                = 76,
	FORMAT_BC3_UNORM                   = 77,
	FORMAT_BC3_UNORM_SRGB              = 78,
	FORMAT_BC4_TYPELESS                = 79,
	FORMAT_BC4_UNORM                   = 80,
	FORMAT_BC4_SNORM                   = 81,
	FORMAT_BC5_TYPELESS                = 82,
	FORMAT_BC5_UNORM                   = 83,
	FORMAT_BC5_SNORM                   = 84,
	FORMAT_B5G6R5_UNORM                = 85,
	FORMAT_B5G5R5A1_UNORM              = 86,
	FORMAT_B8G8R8A8_UNORM              = 87,
	FORMAT_B8G8R8X8_UNORM              = 88,
	FORMAT_R10G10B10_XR_BIAS_A2_UNORM  = 89,
	FORMAT_B8G8R8A8_TYPELESS           = 90,
	FORMAT_B8G8R8A8_UNORM_SRGB         = 91,
	FORMAT_B8G8R8X8_TYPELESS           = 92,
	FORMAT_B8G8R8X8_UNORM_SRGB         = 93,
	FORMAT_BC6H_TYPELESS               = 94,
	FORMAT_BC6H_UF16                   = 95,
	FORMAT_BC6H_SF16                   = 96,
	FORMAT_BC7_TYPELESS                = 97,
	FORMAT_BC7_UNORM                   = 98,
	FORMAT_BC7_UNORM_SRGB              = 99,
	FORMAT_AYUV                        = 100,
	FORMAT_Y410                        = 101,
	FORMAT_Y416                        = 102,
	FORMAT_NV12                        = 103,
	FORMAT_P010                        = 104,
	FORMAT_P016                        = 105,
	FORMAT_420_OPAQUE                  = 106,
	FORMAT_YUY2                        = 107,
	FORMAT_Y210                        = 108,
	FORMAT_Y216                        = 109,
	FORMAT_NV11                        = 110,
	FORMAT_AI44                        = 111,
	FORMAT_IA44                        = 112,
	FORMAT_P8                          = 113,
	FORMAT_A8P8                        = 114,
	FORMAT_B4G4R4A4_UNORM              = 115,
	FORMAT_FORCE_UINT                  = 0xffffffffUL
};

enum eAPISupportLevel
{
	NO_SUPPORT	= 0,
	GL1X		= 10,
	GL2X		= 20,
	GLES2		= 25,
	GL3X		= 30,
	GLES3		= 32,
	GL4X		= 40
};

enum eShaderProfileSupport
{
	SM_4_0_level_9_0,
	SM_4_0_level_9_1,
	SM_4_0_level_9_3,
	SM_4_0,
	SM_4_1,
	SM_5_0
};

enum eVertexAttribute
{
	VERTEXATTRIB_POSITION,
	VERTEXATTRIB_NORMAL,
	VERTEXATTRIB_COLOR,
	VERTEXATTRIB_TEXCOORD,
	VERTEXATTRIB_BINORMAL,
	VERTEXATTRIB_TANGENT,
	VERTEXATTRIB_MATERIAL,
	VERTEXATTRIB_OBJECTID
};

struct InputLayoutDesc
{
	eVertexAttribute	 	attributeType;
	int 					index;
	eFormat 				format;
	unsigned int	 		offset;
	int 					slot;
};

// Texture Stuff
enum eFilterType	// D3D11 MAPPINGS
{
	FILTER_MIN_MAG_MIP_POINT							= 0,
	FILTER_MIN_MAG_POINT_MIP_LINEAR					= 0x1,
	FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT 			= 0x4,
	FILTER_MIN_POINT_MAG_MIP_LINEAR					= 0x5,
	FILTER_MIN_LINEAR_MAG_MIP_POINT					= 0x10,
	FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR			= 0x11,
	FILTER_MIN_MAG_LINEAR_MIP_POINT					= 0x14,
	FILTER_MIN_MAG_MIP_LINEAR 						= 0x15,
	FILTER_ANISOTROPIC								= 0x55,
	FILTER_COMPARISON_MIN_MAG_MIP_POINT				= 0x80,
	FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR		= 0x81,
	FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT	= 0x84,
	FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR		= 0x85,
	FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT		= 0x90,
	FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR= 0x91,
	FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT		= 0x94,
	FILTER_COMPARISON_MIN_MAG_MIP_LINEAR				= 0x95,
	FILTER_COMPARISON_ANISOTROPIC 					= 0xd5,
	FILTER_MINIMUM_MIN_MAG_MIP_POINT					= 0x100,
	FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR			= 0x101,
	FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT 	= 0x104,
	FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR			= 0x105,
	FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT			= 0x110,
	FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR	= 0x111,
	FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT			= 0x114,
	FILTER_MINIMUM_MIN_MAG_MIP_LINEAR 				= 0x115,
	FILTER_MINIMUM_ANISOTROPIC						= 0x155,
	FILTER_MAXIMUM_MIN_MAG_MIP_POINT					= 0x180,
	FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR			= 0x181,
	FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT 	= 0x184,
	FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR			= 0x185,
	FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT			= 0x190,
	FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR	= 0x191,
	FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT			= 0x194,
	FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR 				= 0x195,
	FILTER_MAXIMUM_ANISOTROPIC						= 0x1d5
};

enum eTextureAddressMode	// DIRECT3D3 11 MAPPINGS
{
	TEXTURE_ADDRESS_WRAP		= 1,
	TEXTURE_ADDRESS_MIRROR		= 2,
	TEXTURE_ADDRESS_CLAMP 		= 3,
	TEXTURE_ADDRESS_BORDER		= 4,
	TEXTURE_ADDRESS_MIRROR_ONCE	= 5
};

enum eCompareFunc	// D3D11 MAPPINGS
{ 
	COMPARE_NEVER 			= 1,
	COMPARE_LESS			= 2,
	COMPARE_EQUAL 			= 3,
	COMPARE_LESS_EQUAL 		= 4,
	COMPARE_GREATER 		= 5,
	COMPARE_NOT_EQUAL 		= 6,
	COMPARE_GREATER_EQUAL		= 7,
	COMPARE_ALWAYS 			= 8
};

enum eRenderState
{
	RENDERSTATE_BLEND,
	RENDERSTATE_DEPTH_TEST,
	RENDERSTATE_SCISSOR_TEST
};

struct SamplerState
{
	eFilterType		Filter;
	eTextureAddressMode	AddressU;
	eTextureAddressMode	AddressV;
	eTextureAddressMode	AddressW;
	float			MipLODBias;
	unsigned int		MaxAnisotropy;
	eCompareFunc		ComparisonFunc;
	float				BorderColor[4];
	float				MinLOD;
	float				MaxLOD;
	unsigned int			ID;
};

struct Texture2DDesc
{
	unsigned int		Width;
	unsigned int		Height;
	unsigned int		Depth;
	unsigned int		MipLevels;
	unsigned int		ArraySize;
	eInternalFormat		InternalFormat;
	eFormat 			Format;
	eUsage				Usage;
	unsigned int		ID;
};


class ShaderProgram; // forward decl

class API
{

public:
	API() :
		m_clearColor{0,0,0,0},
		m_APISupportLevel(NO_SUPPORT),
		m_shaderProfile(SM_4_0_level_9_0),
		m_backendAPI(API_NONE),
		m_defaultFramebuffer(0)
		{}
		
	virtual ~API(){}

	virtual bool APIInit( int width, int height, bool vsync, void *hwnd, bool fullscreen, float nearClip, float farClip) = 0;
	virtual void APIShutdown() STUB
	virtual void clear( int target ) STUB
	virtual void present() STUB

	// Buffers
	virtual void createBuffer( eBufferType type, size_t size, const void *pData, eUsage usage, unsigned int *buffer, const char *IDString = "GlobalUniforms" ) STUB
	virtual void deleteBuffer( eBufferType type, unsigned int buffer ) STUB
	virtual void bindBuffer( eBufferType buffType, unsigned int buffer, const char *IDString="GlobalUniforms" ) STUB
	virtual void bufferSubData( eBufferType buffType, unsigned int offset, int size, const void *pData, unsigned int buffer ) STUB
    virtual void bufferSubDataAsync( eBufferType buffType, unsigned int offset, int size, const void *pData, unsigned int buffer ) STUB
	virtual void initRenderBuffer( eInternalFormat format, unsigned int width, unsigned int height, unsigned int buffer ) STUB
	virtual void attachRenderBuffer( eAttachment attachment, unsigned int buffer ) STUB
	virtual void setFrameBufferTexture(eAttachment attachment, unsigned int textureID, unsigned int mipLevel ) STUB
	virtual void setDrawBuffers( unsigned int numBufs, eAttachment *atts ) STUB
	virtual bool checkFrameBuffer() STUBR
    virtual int  setDefaultFramebufferFromCurrent() STUBR
	virtual int  getDefaultFramebuffer() STUBR
	virtual void readPixels(unsigned int x, unsigned int y, unsigned int width, unsigned int height, eInternalFormat format, eType type, void * data) STUB

	// Texture
	virtual void createTexture2D( const Texture2DDesc *pDesc, const void *pData, unsigned int *textureID ) STUB
	virtual void deleteTexture( unsigned int textureID ) STUB
	virtual void createSamplerState( SamplerState *pSS) STUB
	virtual void setSamplerState( unsigned int index, SamplerState *pSS ) STUB
	virtual void bindTexture( unsigned int location, unsigned int *textureID ) STUB;

	// Input Data
	virtual void createInputLayout(
		const InputLayoutDesc *inputLayoutDesc,
		int numElements,
		int stride,
		ShaderProgram *spc,
		unsigned int *inputLayout
	) STUB
	virtual void deleteInputLayout(unsigned int inputLayout) STUB
	virtual void setInputLayout(unsigned int inputLayout) STUB

	virtual void clearColor(float r, float g, float b, float a) STUB

	// Draw
	virtual void drawArrays(eGeomType gt, unsigned int first, unsigned int count) STUB
	virtual void drawArraysInstanced(eGeomType gt, unsigned int first, unsigned int count, unsigned int instanceCount) STUB
	virtual void drawElements( eGeomType gt, unsigned int count, eType type, unsigned int startOffset) STUB
	virtual void drawElementsInstanced( eGeomType gt, unsigned int count, eType type, unsigned int startOffset, unsigned int instanceCount) STUB
	virtual void drawElementsBaseVertex( eGeomType gt, unsigned int count, eType type, unsigned int startOffset, unsigned int baseVertex) STUB


	// Shaders
	virtual void buildShaderProgram( ShaderProgram *sp ) STUB
	virtual void deleteShaderProgram( ShaderProgram *sp ) STUB
	virtual void useShaderProgram ( const ShaderProgram *sp ) STUB
	virtual void setShaderProfileSupport( eShaderProfileSupport sps ) STUB
	virtual void setShaderConstantiv( const char *name, const int *data, int intSize, int count) STUB
	virtual void setShaderConstantfv( const char *name, const float *data, int floatSize, int count) STUB
	virtual void setShaderConstantMatrix4fv( const char *name, int count, int transpose, const float *data) STUB

	virtual void setViewport( unsigned x, unsigned y, unsigned width, unsigned height ) STUB

	// States
	virtual void setFaceWinding( eFaceWinding w ) STUB
	virtual void setFaceCulling( eFaceCullMode c ) STUB
	virtual void setRenderState( eRenderState state, bool enable ) STUB
	virtual void setScissor( int x, int y, int width, int height) STUB

	// Sync
	virtual void finish() STUB
	virtual void flush() STUB

	// concrete methods
	eAPISupportLevel getAPISupportLevel() { return m_APISupportLevel; }
	eAPIType getBackendAPI() { return m_backendAPI; }
	void setBackendAPI( eAPIType api ){m_backendAPI = api;}

protected:
	float					m_clearColor[4];
	eAPISupportLevel 		m_APISupportLevel;
	eShaderProfileSupport 	m_shaderProfile;
	eAPIType				m_backendAPI;

	int			m_defaultFramebuffer;
};


// ----- UTILITY -----
template <class T> 
inline const T& _max(const T& a, const T& b) 
{
	return (a<b)?b:a;
}

inline int numMipLevels(int width, int height)
{
	int numLevels = 1;
	while((width > 1) || (height > 1))
	{
		width = _max(width / 2, 1);
		height = _max(height / 2, 1);
		++numLevels;
	}
	return numLevels;
}
// -----         -----

} //NS GFX
} //ns FI

#endif /*_GFXAPI*/
