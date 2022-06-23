/*
* d3d11Binding.h
*
*  Created on: Aug 10, 2015
*      Author: Roger Dass
*		Copyright Frustum Interactive Inc. - All rights reserved.
*/

#ifndef _3DAPID3D_H
#define _3DAPID3D_H

#include "graphicsAPI/graphicsAPI.h"

#include <vector>

#include <D3DCommon.h>
#include <dxgi.h>
#include <d3d11.h>

//#pragma comment (lib, "d3d11.lib")
//#pragma comment (lib, "dxgi.lib")
//#pragma comment (lib, "d3dcompiler.lib")

typedef struct InputLayout_D3D
{
	int numElements;
	int stride;
	ID3D11InputLayout *pD3DInputLayout;
}InputLayoutContainer;

typedef struct TextureInput
{
	ID3D11Texture2D *pTexture;
	ID3D11ShaderResourceView *pSRV;
	SamplerState samplerState;
}TextureInput;

class D3D11GraphicsAPI : public GraphicsAPI
{
public:
	D3D11GraphicsAPI();
	~D3D11GraphicsAPI();

	bool APIInit( int width, int height, bool vsync, HWND hwnd, bool fullscreen, float nearClip, float farClip);
	void APIShutdown();
	void clear( int target );
	void present();

	// Buffers
	void createBuffer( eBufferType type, int size, const void *pData, eUsage usage, unsigned int *buffer );
	void deleteBuffer( unsigned int buffer );
	void bindBuffer( eBufferType buffType, unsigned int buffer );
	void bufferSubData( eBufferType buffType, unsigned int offset, int size, const void *pData, unsigned int buffer );

	// Texture
	void createTexture2D( const Texture2DDesc *pDesc, const void *pData, unsigned int *textureID );
	void createSamplerState( SamplerState *pSS);
	void setSamplerState( unsigned int index, SamplerState *pSS );
	void bindTexture( unsigned int location, unsigned int *textureID );

	// Input Data
	void createInputLayout( const InputLayoutDesc *inputLayoutDesc, int numElements, int stride, ShaderProgram *spc, unsigned int *inputLayout);
	void deleteInputLayout( unsigned int inputLayout );
	void setInputLayout( unsigned int inputLayout );

	void clearColor ( float r, float g, float b, float a);

	void drawArrays(FIenum mode, unsigned int first, unsigned int count );
	void drawElements(FIenum mode, unsigned int count, eType type, unsigned int startOffset);

	// Shaders
	void buildShaderProgram( ShaderProgram *sp );
	void deleteShaderProgram( ShaderProgram *sp );
	void UseShaderProgram ( ShaderProgram *spc );
	void SetShaderProfileSupport( eShaderProfileSupport sps );

	void setViewport( int x, int y, int width, int height );

private:

	int		m_videoCardMemory;
	char	m_videoCardDescription[128];
	bool	m_vsyncEnabled;

	int		m_currentInputLayout;

	IDXGISwapChain*				m_swapChain;
	ID3D11Device*				m_device;
	ID3D11DeviceContext*		m_deviceContext;
	ID3D11RenderTargetView*		m_renderTargetView;
	ID3D11Texture2D*			m_depthStencilBuffer;
	ID3D11DepthStencilState*	m_depthStencilState;
	ID3D11DepthStencilView*		m_depthStencilView;
	ID3D11RasterizerState*		m_rasterState;

	// TODO: use an STL::map for this instead!
	std::vector<ID3D11Buffer*>			m_vBufferPtrArray;
	std::vector<ID3D11VertexShader*>	m_vVertexShaderPtrArray;
	std::vector<ID3D11PixelShader*>		m_vPixelShaderPtrArray;
	std::vector<ID3D11SamplerState*>	m_vSamplerStatePtrArray;
	
	std::vector<TextureInput*>			m_vTexturePtrArray;
	std::vector<InputLayoutContainer*>	m_vInputLayoutPtrArray;
	
};

#endif
