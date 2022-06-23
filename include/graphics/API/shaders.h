#ifndef _GEOMSHADERS_H_
#define _GEOMSHADERS_H_

// *****************
// * SHADER SOURCE 
// *
// * Copywrite (C) Frustum Interactive 2012
// *
// *****************

namespace FI { namespace SHADERS {

	namespace GL2
	{
		const char *vertexShader();
		const char *fragmentShader();
		const char *vertexShaderPhong();
		const char *fragmentShaderPhong();

		namespace SHAPES
		{
			const char *circleShader();
			const char *ellipseShader();
			const char *squareShader();
			const char *rectangleShader();
			const char *triangleShader();
			const char *ngonShader();
		}
	}

	namespace GL3
	{
		const char *vertexShader();
		const char *fragmentShader();
		const char *vertexShaderPhong();
		const char *fragmentShaderPhong();

		namespace SHAPES
		{
			const char *circleShader();
			const char *ellipseShader();
			const char *squareShader();
			const char *rectangleShader();
			const char *triangleShader();
			const char *ngonShader();
		}
	}

	namespace GLES2
	{
		const char *vertexShader();
		const char *fragmentShader();
		const char *vertexShaderPhong();
		const char *fragmentShaderPhong();

		namespace SHAPES
		{
			const char *circleShader();
			const char *ellipseShader();
			const char *squareShader();
			const char *rectangleShader();
			const char *triangleShader();
			const char *ngonShader();
		}
	}

	namespace GLES3
	{
		const char *vertexShader();
		const char *fragmentShader();
		const char *vertexShaderPhong();
		const char *fragmentShaderPhong();

		namespace SHAPES
		{
			const char *circleShader();
			const char *ellipseShader();
			const char *squareShader();
			const char *rectangleShader();
			const char *triangleShader();
			const char *ngonShader();
		}
	}

	namespace HLSL
	{
		const char *vertexShader();
		const char *fragmentShader();

		namespace SHAPES
		{
			const char *circleShader();
			const char *ellipseShader();
			const char *squareShader();
			const char *rectangleShader();
			const char *triangleShader();
			const char *ngonShader();
		}
	}

} // ns SHADERS
} // ns FI

#endif // _GEOMSHADERS_H
