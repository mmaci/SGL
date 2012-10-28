#ifndef CONTEXT_H
#define CONTEXT_H

#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <functional>

#include "sgl.h"
#include "Mathematics.h"

enum Matrices
{
	M_MVP,
	M_MODELVIEW,
	M_PROJECTION
};

struct color_rgba
{
	public:
		color_rgba(float red = 0.0f, float green = 0.0f, float blue = 0.0f) : _r(red), _g(green), _b(blue) {}

		void setRed(float value){ _r = value; }
		void setGreen(float value){ _g = value; }
		void setBlue(float value){ _b = value; }

		float red(){ return _r; }
		float green(){ return _g; }
		float blue(){ return _b; }

	private:
		float _r, _g, _b;
};

struct matrix4x4
{
	public:
		matrix4x4()
		{
			null();
		}

		// float get(int c) const { return _container[c]; }
		float get(uint8 x, uint8 y) const { return _container[y * 4 + x]; }
		void set(uint8 x, uint8 y, float value){ _container[y * 4 + x] = value; }
		
		void set(uint8 c, float value){ _container[c] = value; }
		float& operator[](uint32 pos)
		{
			return _container[pos];
		}
		float operator[](uint32 pos) const
		{
			return _container[pos];
		}

		matrix4x4& operator= (const matrix4x4& a)
		{
			for (int i = 0; i < 16; ++i)
				_container[i] = a[i];

			return *this;
		}		

		matrix4x4 operator* (const matrix4x4& a)
		{
			matrix4x4 result;

			result[0]	= _container[0] * a[0]		+ _container[1] * a[4]		+ _container[2] * a[8]		+ _container[3] * a[12];
			result[1]	= _container[0] * a[1]		+ _container[1] * a[5]		+ _container[2] * a[9]		+ _container[3] * a[13];
			result[2]	= _container[0] * a[2]		+ _container[1] * a[6]		+ _container[2] * a[10]		+ _container[3] * a[14];
			result[3]	= _container[0] * a[3]		+ _container[1] * a[7]		+ _container[2] * a[11]		+ _container[3] * a[15];

			result[4]	= _container[4] * a[0]		+ _container[5] * a[4]		+ _container[6] * a[8]		+ _container[7] * a[12];
			result[5]	= _container[4] * a[1]		+ _container[5] * a[5]		+ _container[6] * a[9]		+ _container[7] * a[13];
			result[6]	= _container[4] * a[2]		+ _container[5] * a[6]		+ _container[6] * a[10]		+ _container[7] * a[14];
			result[7]	= _container[4] * a[3]		+ _container[5] * a[7]		+ _container[6] * a[11]		+ _container[7] * a[15];

			result[8]	= _container[8] * a[0]		+ _container[9] * a[4]		+ _container[10] * a[8]		+ _container[11] * a[12];
			result[9]	= _container[8] * a[1]		+ _container[9] * a[5]		+ _container[10] * a[9]		+ _container[11] * a[13];
			result[10]	= _container[8] * a[2]		+ _container[9] * a[6]		+ _container[10] * a[10]	+ _container[11] * a[14];
			result[11]	= _container[8] * a[3]		+ _container[9] * a[7]		+ _container[10] * a[11]	+ _container[11] * a[15];

			result[12]	= _container[12] * a[0]		+ _container[13] * a[4]		+ _container[14] * a[8]		+ _container[15] * a[12];
			result[13]	= _container[12] * a[1]		+ _container[13] * a[5]		+ _container[14] * a[9]		+ _container[15] * a[13];
			result[14]	= _container[12] * a[2]		+ _container[13] * a[6]		+ _container[14] * a[10]	+ _container[15] * a[14];
			result[15]	= _container[12] * a[3]		+ _container[13] * a[7]		+ _container[14] * a[11]	+ _container[15] * a[15];
						
			return result;			
		}

		matrix4x4 operator* (const float* a) const
		{
			matrix4x4 result;

			result[0]	= _container[0] * a[0]		+ _container[1] * a[4]		+ _container[2] * a[8]		+ _container[3] * a[12];
			result[1]	= _container[0] * a[1]		+ _container[1] * a[5]		+ _container[2] * a[9]		+ _container[3] * a[13];
			result[2]	= _container[0] * a[2]		+ _container[1] * a[6]		+ _container[2] * a[10]		+ _container[3] * a[14];
			result[3]	= _container[0] * a[3]		+ _container[1] * a[7]		+ _container[2] * a[11]		+ _container[3] * a[15];

			result[4]	= _container[4] * a[0]		+ _container[5] * a[4]		+ _container[6] * a[8]		+ _container[7] * a[12];
			result[5]	= _container[4] * a[1]		+ _container[5] * a[5]		+ _container[6] * a[9]		+ _container[7] * a[13];
			result[6]	= _container[4] * a[2]		+ _container[5] * a[6]		+ _container[6] * a[10]		+ _container[7] * a[14];
			result[7]	= _container[4] * a[3]		+ _container[5] * a[7]		+ _container[6] * a[11]		+ _container[7] * a[15];

			result[8]	= _container[8] * a[0]		+ _container[9] * a[4]		+ _container[10] * a[8]		+ _container[11] * a[12];
			result[9]	= _container[8] * a[1]		+ _container[9] * a[5]		+ _container[10] * a[9]		+ _container[11] * a[13];
			result[10]	= _container[8] * a[2]		+ _container[9] * a[6]		+ _container[10] * a[10]	+ _container[11] * a[14];
			result[11]	= _container[8] * a[3]		+ _container[9] * a[7]		+ _container[10] * a[11]	+ _container[11] * a[15];

			result[12]	= _container[12] * a[0]		+ _container[13] * a[4]		+ _container[14] * a[8]		+ _container[15] * a[12];
			result[13]	= _container[12] * a[1]		+ _container[13] * a[5]		+ _container[14] * a[9]		+ _container[15] * a[13];
			result[14]	= _container[12] * a[2]		+ _container[13] * a[6]		+ _container[14] * a[10]	+ _container[15] * a[14];
			result[15]	= _container[12] * a[3]		+ _container[13] * a[7]		+ _container[14] * a[11]	+ _container[15] * a[15];
						
			return result;		
		}

		matrix4x4& null()
		{
			_container[0]	= 0.0f;
			_container[1]	= 0.0f;
			_container[2]	= 0.0f;
			_container[3]	= 0.0f;

			_container[4]	= 0.0f;
			_container[5]	= 0.0f;
			_container[6]	= 0.0f;
			_container[7]	= 0.0f;

			_container[8]	= 0.0f;
			_container[9]	= 0.0f;
			_container[10]	= 0.0f;
			_container[11]	= 0.0f;

			_container[12]	= 0.0f;
			_container[13]	= 0.0f;
			_container[14]	= 0.0f;
			_container[15]	= 0.0f;

			return *this;
		}

		matrix4x4& identity()
		{
			_container[0]	= 1.0f;
			_container[1]	= 0.0f;
			_container[2]	= 0.0f;
			_container[3]	= 0.0f;

			_container[4]	= 0.0f;
			_container[5]	= 1.0f;
			_container[6]	= 0.0f;
			_container[7]	= 0.0f;

			_container[8]	= 0.0f;
			_container[9]	= 0.0f;
			_container[10]	= 1.0f;
			_container[11]	= 0.0f;

			_container[12]	= 0.0f;
			_container[13]	= 0.0f;
			_container[14]	= 0.0f;
			_container[15]	= 1.0f;

			return *this;
		}

		matrix4x4& translate( float x, float y, float z )
		{
			_container[0]	= 1.0f;
			_container[1]	= 0.0f;
			_container[2]	= 0.0f;
			_container[3]	= x;

			_container[4]	= 0.0f;
			_container[5]	= 1.0f;
			_container[6]	= 0.0f;
			_container[7]	= y;

			_container[8]	= 0.0f;
			_container[9]	= 0.0f;
			_container[10]	= 0.0f;
			_container[11]	= z;

			_container[12]	= 0.0f;
			_container[13]	= 0.0f;
			_container[14]	= 0.0f;
			_container[15]	= 1.0f;

			return *this;
		}

		matrix4x4& rotate( float angle )
		{
			float s = sin(angle);
			float c = cos(angle);

			_container[0]	= c;
			_container[1]	= -s;
			_container[2]	= 0.0f;
			_container[3]	= 0.0f;

			_container[4]	= s;
			_container[5]	= c;
			_container[6]	= 0.0f;
			_container[7]	= 0.0f;

			_container[8]	= 0.0f;
			_container[9]	= 0.0f;
			_container[10]	= 0.0f;
			_container[11]	= 0.0f;

			_container[12]	= 0.0f;
			_container[13]	= 0.0f;
			_container[14]	= 0.0f;
			_container[15]	= 1.0f;

			return *this;
		}

		matrix4x4& scale( float scale_x, float scale_y, float scale_z )
		{
			_container[0]	= scale_x;
			_container[1]	= 0.0f;
			_container[2]	= 0.0f;
			_container[3]	= 0.0f;

			_container[4]	= 0.0f;
			_container[5]	= scale_y;
			_container[6]	= 0.0f;
			_container[7]	= 0.0f;

			_container[8]	= 0.0f;
			_container[9]	= 0.0f;
			_container[10]	= scale_z;
			_container[11]	= 0.0f;

			_container[12]	= 0.0f;
			_container[13]	= 0.0f;
			_container[14]	= 0.0f;
			_container[15]	= 1.0f;

			return *this;
		}

		const float* ptr() { return _container; }

	private:
		float _container[16];
};
matrix4x4 operator* (const float* a, const matrix4x4& b)
{
	matrix4x4 result;
	
	result[0]	= a[0] * b[0]		+ a[1] * b[4]		+ a[2] * b[8]		+ a[3] * b[12];
	result[1]	= a[0] * b[1]		+ a[1] * b[5]		+ a[2] * b[9]		+ a[3] * b[13];
	result[2]	= a[0] * b[2]		+ a[1] * b[6]		+ a[2] * b[10]		+ a[3] * b[14];
	result[3]	= a[0] * b[3]		+ a[1] * b[7]		+ a[2] * b[11]		+ a[3] * b[15];

	result[4]	= a[4] * b[0]		+ a[5] * b[4]		+ a[6] * b[8]		+ a[7] * b[12];
	result[5]	= a[4] * b[1]		+ a[5] * b[5]		+ a[6] * b[9]		+ a[7] * b[13];
	result[6]	= a[4] * b[2]		+ a[5] * b[6]		+ a[6] * b[10]		+ a[7] * b[14];
	result[7]	= a[4] * b[3]		+ a[5] * b[7]		+ a[6] * b[11]		+ a[7] * b[15];

	result[8]	= a[8] * b[0]		+ a[9] * b[4]		+ a[10] * b[8]		+ a[11] * b[12];
	result[9]	= a[8] * b[1]		+ a[9] * b[5]		+ a[10] * b[9]		+ a[11] * b[13];
	result[10]	= a[8] * b[2]		+ a[9] * b[6]		+ a[10] * b[10]		+ a[11] * b[14];
	result[11]	= a[8] * b[3]		+ a[9] * b[7]		+ a[10] * b[11]		+ a[11] * b[15];

	result[12]	= a[12] * b[0]		+ a[13] * b[4]		+ a[14] * b[8]		+ a[15] * b[12];
	result[13]	= a[12] * b[1]		+ a[13] * b[5]		+ a[14] * b[9]		+ a[15] * b[13];
	result[14]	= a[12] * b[2]		+ a[13] * b[6]		+ a[14] * b[10]		+ a[15] * b[14];
	result[15]	= a[12] * b[3]		+ a[13] * b[7]		+ a[14] * b[11]		+ a[15] * b[15];
	
	return result;	
}

struct vertex
{
	public:
		vertex(){ };
		vertex(float x, float y) : _x(x), _y(y), _z(0.0f), _w(1.0f) {}
		vertex(float x, float y, float z) : _x(x), _y(y), _z(z),  _w(1.0f) {}
		vertex& operator= (const vertex& a)
		{
			_x = a.x();
			_y = a.y();
			_z = a.z();
			_w = a.w();

			return *this;
		}
		
		float x() const { return _x; }
		float y() const { return _y; }
		float z() const { return _z; }
		float w() const { return _w; }

		void setX(float x){ _x = x; }
		void setY(float y){ _y = y; }
		void setZ(float z){ _z = z; }
		void setW(float w){ _w = w; }

		bool operator==(const vertex& v)
		{
			if (_x == v.x() && _y == v.y() && _z == v.z())
				return true;
		}

		vertex& operator*=(const matrix4x4& m)
		{
			float	__x = _x,
					__y = _y,
					__z = _z,
					__w = _w;

			_x = __x * m[0] +	__y * m[1] +	__z * m[2] +	__w * m[3];
			_y = __x * m[4] +	__y * m[5] +	__z * m[6] +	__w * m[7];
			_z = __x * m[8] +	__y * m[9] +	__z * m[10] +	__w * m[11];
			_w = __x * m[12] +	__y * m[13] +	__z * m[14] +	__w * m[15];

			return *this;
		}

	private:
		float _x, _y, _z, _w;
};

typedef		std::vector<vertex>::iterator VertexIterator;

struct circle
{
	public:
		circle(float x, float y, float radius) : _center(vertex(x, y, 0.0f)), _r(radius) {}
		circle(float x, float y, float z, float radius) : _center(vertex(x, y, z)), _r(radius) {} 
		circle(vertex center, float radius) : _center(center), _r(radius) {}

		float x() const { return _center.x(); }
		float y() const { return _center.y(); }
		float z() const { return _center.z(); }

		float radius() const { return _r; }

		vertex center() const { return _center; }

	private:
		vertex _center;
		float _r;
};

struct ellipse
{
	public:
		ellipse(float x, float y, float z, float a, float b) : _center(vertex(x, y, z)), _a(a), _b(b) {}
		ellipse(float x, float y, float a, float b) : _center(vertex(x, y, 0.0f)), _a(a), _b(b) {}
		ellipse(vertex center, float a, float b) : _center(center), _a(a), _b(b) {}

		float x() const { return _center.x(); }
		float y() const { return _center.y(); }
		float z() const { return _center.z(); }

		float a() const { return _a; }
		float b() const { return _b; }

		vertex center() const { return _center; }

	private:
		vertex _center;
		float _a, _b;
};

class edge 
{
	public:  
		edge(vertex a, vertex b)
		{
			if(b.y() < a.y())
				std::swap( a, b );

			_dy		= b.y() - a.y();

			_dx		= ( b.x() - a.x() ) / _dy;
			_dz		= ( b.z() - a.z() ) / _dy;

			_x		= a.x();
			_y		= a.y();
			_z		= a.z();

			_start_y = a.y();
			_end_y	= b.y();
		}
    
		vertex toVertex()
		{
			return vertex(_x, _y, _z);
		}
    
		void nextStep()
		{
			_y += 1.0f;
			if (_y != _start_y)
			{
				_x += _dx;
				_z += _dz;
			}
		} 

		bool operator== (const edge& line)
		{
			return	_x == line.x() &&
					_y == line.y() &&
					_z == line.z();
		}

		float x() const { return _x; }
		float y() const { return _y; }
		float z() const { return _z; }

		float start() const { return _start_y; }
		float end() const { return _end_y; }

		struct startFunctor : public std::binary_function<edge, edge, bool>
		{
			bool operator()( edge a, edge b)
			{
				return a.start() < b.start();
			}
		};

		struct endFunctor : public std::binary_function<edge, edge, bool>
		{
			bool operator()( edge a, edge b)
			{
				return	a.end() < b.end();
			}
		};

		struct xFunctor : public std::binary_function<edge, edge, bool>
		{
			bool operator()( edge a, edge b)
			{
				return	a.x() < b.x();
			}
		};

	private:  
		float	_x, _y, _z;
		float	_dx, _dy, _dz;

		float	_start_y,
				_end_y;
};

struct arc
{
	public:
		arc(float x, float y, float z, float radius, float from, float to) : _center(vertex(x, y, z)), _r(radius), _f(from), _t(to) {}
		arc(float x, float y, float radius, float from, float to) : _center(vertex(x, y, 0.0f)), _r(radius), _f(from), _t(to) {}
		arc(vertex center, float radius, float from, float to) : _center(center), _r(radius), _f(from), _t(to) {}

		float x() const { return _center.x(); }
		float y() const { return _center.y(); }
		float z() const { return _center.z(); }

		float from() const { return _f; }
		float to() const { return _t; }
		float radius() const { return _r; }

		vertex center() const { return _center; }

	private:
		vertex _center;
		float _r, _f, _t;
};

/// A context class.
/**
	A context class represents a single scene or a context. Multiple contexts can be held in memory at the
	same time. Switching between them is done inside GUI and drawing inside the currently shown one.
*/
class Context
{
	public:
		/// Context constructor.
		/**
			Allocates a color buffer for a single scene (called context) based on width and height. Multiple contexts
			are stored in memory simultaneously. User always works only with the currently shown context.

			@param width [in] Context width.
			@param height [in] Context height.
		*/
		Context(uint32 width = 0, uint32 height = 0) : _w(width), _h(height)
		{ 
			_matrixStack		= new std::vector<matrix4x4>;
			_colorBuffer		= new color_rgba[width * height];
			
			initZBuffer();
			
			_updateMVPMneeded	= false;
		} 		

		/// Context destructor.
		/**
			Called when deleting a context. Frees all used memory.
		*/
		~Context(){ };

		/// Returns pointer to the color buffer.
		/**
			Returns the address of the start of the allocated memory used for storing color
			information (color buffer).

			@return Color buffer pointer.
		*/
		float*			getColorBufferPointer()
		{ return (float*) _colorBuffer; }

		/// Sets the color used for drawing.
		/**
			Sets the color currently used for drawing inside the current context.

			@param color[in] RGBA color value.
		*/
		void			setCurrentColor(color_rgba color)
		{ _currentColor = color; }
		
		/// Sets the color used for drawing.
		/**
			Sets the color currently used for drawing inside the current context.

			@param r[in] Red channel value.
			@param g[in] Green channel value.
			@param b[in] Blue channel value.
		*/
		void			setCurrentColor(float r, float g, float b)
		{ _currentColor = color_rgba(r, g, b); }

		/// Sets the point size used for drawing.
		/**
			Sets the point size currently being used for drawing. 1.0 corresponds to 1px.

			@param size[in] Point size in pixels.
		*/
		void			setPointSize(float size){ _pointSize = size; }

		/// Sets drawing mode.
		/** 
			Sets the element type to use for drawing (mode).

			@param mode[in] Element type to use for drawing.
		*/
		void			setDrawingMode(sglEElementType mode){ _drawingMode = mode; }

		/// Returns currently used drawing mode.
		/**
		   Returns the element type (mode) currently being used for drawing.
		 
		   @return Drawing mode.
		 */
		sglEElementType getDrawingMode(){ return _drawingMode; }

		/// Clear the vertex buffer.
		/**
			Clears the vertex buffer storing all the vertices used to draw the current element and calls appropriate destructors.
		*/
		void			clearVertexBuffer(){ _vertexBuffer.clear(); }

		/// Adds a vertex inside the vertex container.
		/**
			Adds a vertex to the vertex container, later on used for drawing after calling sglEnd().

			@param vertex[in] A vertex.
		*/
		void			addVertex( vertex v )
		{ 
			MVPTransform( v );
			normalize( v );

			_vertexBuffer.push_back( v );
		}

		/// Draws an arc
		/**
			Draws an arc based on parameters given in sglArc (center point, radius and from/to angle). It adds pairs
			of vertices inside vertex buffer and when done it calls line strip rasterization to display an arc.

			@param arc[in] An arc.
		*/
		void			addArc( arc a, bool filled = false )
		{
			const float from		= a.from(),
						to			= a.to(),
						radius		= a.radius(),
						n_segments	= ceil( ARC_SEGMENTS_F * (to - from) / (2.0f * PI_F) ),
						center_x	= a.x(),
						center_y	= a.y(),
						c			= (to - from) / n_segments;

			float x, y, old_x, old_y;
			
			for (float i = from; i < to; i += c)
			{
				x = radius * sin( i - PI_F / 2 );
				y = radius * cos( i - PI_F / 2 );

				if (i > from)
				{
					addVertex( vertex( center_x - old_x, center_y + old_y ) );
					addVertex( vertex( center_x - x, center_y + y) );
				}

				old_x = x;
				old_y = y;
			}
			x = radius * sin( to - PI_F / 2.0f );
			y = radius * cos( to - PI_F / 2.0f );

			addVertex( vertex( center_x - old_x, center_y + old_y ) );
			addVertex( vertex( center_x - x, center_y + y) );

			if ( filled )
			{
				addVertex( vertex( center_x, center_y ) );
				addFilledPolygon();
			}
			else
			{
				rasterizeLineStrip();
			}
			clearVertexBuffer();
		}

		/// Draws an ellipse
		/**
			Draws an ellipse based on parameters given in sglEllipse (center and a,b - check any geometry
			math book/wikipedia on what these are. Works the same as addArc( arc ), only adds pairs of
			vertices for a whole ellipse and then calls line loop rasterization.

			@param ellipse[in] An ellipse.
		*/
		void			addEllipse( ellipse e, bool filled = false )
		{
			const float	a = e.a(),
						b = e.b();

			float		x = e.x() - a,
						y = e.y() - b,

						old_x,
						old_y;
						
			const float	center_x = x,
						center_y = y;

			for (uint8 i = 0; i < ELLIPSE_SEGMENTS_UI; ++i)
			{
				x = a * sin( (static_cast<float>(i) / ELLIPSE_SEGMENTS_F) * (PI_F * 2.0f) );
				y = b * cos( (static_cast<float>(i) / ELLIPSE_SEGMENTS_F) * (PI_F * 2.0f) );

				if (i)				
				{
					addVertex( vertex( a + center_x + old_x, b + center_y - old_y ) );
					addVertex( vertex( a + center_x + x, b + center_y - y ) );
				}

				old_x = x;
				old_y = y;
			}

			filled ? addFilledPolygon() : rasterizeLineLoop();
			clearVertexBuffer();
		}

		/// Draws a circle
		/**					
			@param circle[in] A circle.
			@param filled[in] To be or not to be FILLED ! - Hamlet (http://en.wikipedia.org/wiki/Hamlet)
		*/
		void			addCircle( circle c , bool filled = false )
		{		
			// center normalization
			vertex center = c.center();
			MVPTransform(center);
			normalize(center);

			// TODO: add documentation
			float det = ( (_viewport_w / 2) * _matrix[M_MVP][0] * 
						(_viewport_h / 2) * _matrix[M_MVP][5] ) -
						( (_viewport_w / 2) * _matrix[M_MVP][1] *
						(_viewport_h / 2) * _matrix[M_MVP][4] );

			int32 radius = static_cast<int32>(sqrt(det) * c.radius());

			// midpoint alg. (modified bressenham)
			int32	x = radius, 
					y = 0;

			int32	center_x = static_cast<int32>(center.x()),
					center_y = static_cast<int32>(center.y());

			int32	cd2 = 0;
 
			if ( filled )
			{
				fillBetweenPoints( center_x - radius, center_x + radius, center_y );
			}
			else
			{
				setPixel(static_cast<uint32>(center_x - radius), static_cast<uint32>(center_y));
				setPixel(static_cast<uint32>(center_x + radius), static_cast<uint32>(center_y));
				setPixel(static_cast<uint32>(center_x),			 static_cast<uint32>(center_y - radius));
				setPixel(static_cast<uint32>(center_x),			 static_cast<uint32>(center_y + radius));
			}

			while ( x > y )
			{
				cd2 -= (--x) - (++y);
				
				if ( cd2 < 0 ) 
					cd2 += x++;

				if ( filled )
				{
					fillBetweenPoints( center_x - x, center_x + x, center_y - y );
					fillBetweenPoints( center_x - y, center_x + y, center_y + x );
					fillBetweenPoints( center_x - x, center_x + x, center_y + y );
					fillBetweenPoints( center_x - y, center_x + y, center_y - x );				
				}
				else
				{
					// draws 8ths of the circle at the same time
					setPixel(static_cast<uint32>(center_x - x), static_cast<uint32>(center_y - y) );	// <135; 180>
					setPixel(static_cast<uint32>(center_x - y), static_cast<uint32>(center_y - x) );	// <90; 135>
					setPixel(static_cast<uint32>(center_x + y), static_cast<uint32>(center_y - x) );	// <45; 90>
					setPixel(static_cast<uint32>(center_x + x), static_cast<uint32>(center_y - y) );	// <0; 45>

					setPixel(static_cast<uint32>(center_x - x), static_cast<uint32>(center_y + y) );	// <180; 225>
					setPixel(static_cast<uint32>(center_x - y), static_cast<uint32>(center_y + x) );	// <225; 270>
					setPixel(static_cast<uint32>(center_x + y), static_cast<uint32>(center_y + x) );	// <270; 315>
					setPixel(static_cast<uint32>(center_x + x), static_cast<uint32>(center_y + y) );	// <315; 0>
				}

			 } 		
		}
	
		/// Draws a filled polygon
		/**
			Fills a polygon shaped object based on vertices in vertex buffer. Uses a scan-line fill algorithm.
			(more info google or here: http://www.cmpe.boun.edu.tr/~sahiner/cmpe460web/FALL2009/scanlinefill.pdf)

			First it constructs edges of the polygon and pushes them into a non-active buffer. Then it determines
			the max. and min. y-coordinates and loops incrementally from min to max. Every time it finds a 
			starting y-coordinate inside the non-active buffer, it adds the edge to the active buffer and removes it
			from the non-active buffer. The same happens for ending y-coordinates and corresponding edges inside
			the active buffer.

			While looping it fills segments based on the active buffer.
		*/
		void			addFilledPolygon( void )
		{		       			    	
			for (std::vector<vertex>::iterator it = _vertexBuffer.begin(); it != _vertexBuffer.end(); ) 
			{
				vertex tmp = *it;

				if (++it == _vertexBuffer.end())
					break;

				edge e(tmp, *it);
				_nonActiveEdges.push_back(e);
			}

			edge e(_vertexBuffer.back(), _vertexBuffer.front());
			_nonActiveEdges.push_back(e);
			std::sort( _nonActiveEdges.begin(), _nonActiveEdges.end(), edge::startFunctor() );
			
			int32 minY = sglmath::round(_nonActiveEdges.front().start());
			int32 maxY = sglmath::round(_nonActiveEdges.back().end());

			std::vector<edge>::iterator it;
			for (int32 y = minY; y < maxY; ++y)
			{								
				// edge activation
				it = _nonActiveEdges.begin();
				while (!_nonActiveEdges.empty() && sglmath::round(it->start()) == y)
				{
					_activeEdges.push_back(*it);
					_nonActiveEdges.erase(it);
					it = _nonActiveEdges.begin();
				}

				std::sort( _activeEdges.begin(), _activeEdges.end(), edge::endFunctor() );

				// edge deactivation
				it = _activeEdges.begin();
				while (!_activeEdges.empty() && sglmath::round(it->end()) == y)
				{
					_activeEdges.erase(it);
					it = _activeEdges.begin();
				}

				if (_activeEdges.empty())
					continue;
				
				for (it = _activeEdges.begin(); it != _activeEdges.end(); ++it)
				{
					edge& e = *it;
					e.nextStep();
				}				
		
				std::sort( _activeEdges.begin(), _activeEdges.end(), edge::xFunctor() );
				for (it = _activeEdges.begin(); it != _activeEdges.end(); ++it)
				{				
					vertex a = it->toVertex();

					++it;
					if (it == _activeEdges.end())
						break;

					vertex b = it->toVertex();
					fillBetweenPoints(a.x(), b.x(), y);
				}
			}
			_activeEdges.clear();
			_nonActiveEdges.clear();
		}

		void addFilledCircle( circle c )
		{
					
		}

		void fillBetweenPoints(float a, float b, int32 y)
		{		
			int32 from = static_cast<int32>( a );
			int32 to = static_cast<int32>( b );

			if (from > to)
				std::swap(from, to);

			for (int32 x = from; x <= to; ++x)
				setPixel(x, y);
		}


		/// Model-View-Projection Transformation
		/**
			In case an MVP update is needed, a Model-View-Projection matrix is recalculated based on stored Modelview and
			Projection matrices. Then it's applied on a give vertex 

			@param vertex[in] A vertex.
		*/
		void			MVPTransform( vertex& v ) //  MVP : Model-View-Projection
		{
			if (_updateMVPMneeded)
				callMVPMupdate();

			v *= _matrix[M_MVP];
		}

		void			MVPMupdate()
		{
			_updateMVPMneeded = true;
		}

		void			normalize( vertex& v )
		{
			v.setX( (v.x() + 1.0f) * static_cast<float>(_viewport_w) / 2.0f + _viewport_min_x );
			v.setY( (v.y() + 1.0f) * static_cast<float>(_viewport_h) / 2.0f + _viewport_min_y );
		}


		/// Inserts points into memory
		/**
			Inserts all the vertices inside vertex buffer as points with given point size into memory
		*/
		void			rasterizePoints()
		{
			uint32 size = static_cast<uint32>( _pointSize/2 );

			for (std::vector<vertex>::iterator it = _vertexBuffer.begin(); it != _vertexBuffer.end(); ++it)
			{
				vertex v = *it;
				uint32 x = static_cast<uint32>(v.x());
				uint32 y = static_cast<uint32>(v.y());

				if (!size)
					setPixel(x, y);
				else
				{
					for (uint32 i = 0; i < size; ++i)
					{
						setPixel(x, y);
						setPixel(x+size, y+size);
						setPixel(x+size, y);
						setPixel(x, y+size);
						setPixel(x-size, y-size);
						setPixel(x-size, y);
						setPixel(x, y-size);
					}
				}
			}
		}

		/// Inserts a line segment into memory
		/**
			Based on vertices inside vertex buffer (must be 2), calculates points using Bressenham algorithm
			and inserts them into memory. 
			
			Note that in case the absolute value of Y coord rises faster, than the absolute value of X coord
			(in the I quadrant its angle towards X axis is over 45deg), we swap the X coord with the Y coord and
			the other way around. Also when the end vertex is closer to [0, 0], we swap the end vertex with the
			start vertex.

			Also instead of using division, we use bit shift to divite by 2.

			@param start[in] Starting vertex.
			@param end[in] Ending vertex.
		*/
		void		rasterizeLineSegment(vertex start, vertex end)
		{
			int32 y_2 = static_cast<int32>( end.y() );
			int32 y_1 = static_cast<int32>( start.y() );

			int32 x_2 = static_cast<int32>( end.x() );
			int32 x_1 = static_cast<int32>( start.x() );

			const bool over45 = (fabs(end.y() - start.y()) > fabs(end.x() - start.x()));
			if (over45)
			{
				std::swap(x_1, y_1);
				std::swap(x_2, y_2);
			}
 
			if (x_1 > x_2)
			{
				std::swap(x_1, x_2);
				std::swap(y_1, y_2);
			}
 
			const int32 dx = x_2 - x_1;
			const int32 dy = abs(y_2 - y_1);
 
			int32 err = 0;
			const int32 y_step = (y_1 < y_2) ? 1 : -1;
			for (; x_1 < x_2; ++x_1)
			{
				over45 ? setPixel( y_1, x_1 ) : setPixel( x_1, y_1 );
				err += dy;

				if ( ( err << 1 ) >= dx)
				{
					y_1 += y_step;
					err -= dx;
				}
			}
		}

		/// Calls rasterization for one segment
		void			rasterizeLines()
		{
			VertexIterator old;
			for (VertexIterator it = _vertexBuffer.begin(); it < _vertexBuffer.end(); it += 2)
				rasterizeLineSegment(*it, *(it+1));
		}

		/// Calls rasterization for a line strip
		void			rasterizeLineStrip()
		{
			VertexIterator old;
			for (VertexIterator it = _vertexBuffer.begin(); it != _vertexBuffer.end(); ++it)
			{
				if (it == _vertexBuffer.begin())
				{
					old = it;
					continue;
				}

				rasterizeLineSegment(*old, *it);
				old = it;
			}
		}



		/// Calls rasterization for a line loop
		/**
			Line loop behaves the same as a line strip except there is an extra line from end to start.
		*/
		void			rasterizeLineLoop()
		{
			rasterizeLineStrip();
			rasterizeLineSegment(_vertexBuffer.back(), _vertexBuffer.front());
		}

		/// Sets a given pixel
		/*
			Sets a given pixel with whatever color is currently being used.

			@param x[in] X coordinate.
			@param y[in] Y coordinate.
		*/
		void			setPixel(uint32 x, uint32 y)
		{
			setColorBuffer(x, y, _currentColor);
		}

		/// Sets a given point (pixel) in 3D space
		/**
			Sets a given point in 3D space. We only project in a 2D plane, therefore we check with the
			z-buffer if the currently displayed pixel is nearer or further than the one we want to draw
			and if that is so, we redraw the pixel.

			@param x[in] X coordinate.
			@param y[in] Y coordinate.
			@param z[in] Depth
		*/
		void			setPixel3D(uint32 x, uint32 y, float z)
		{
			uint32 pos = y * _w + x;
			if (z < _zbuffer[pos])
			{
				_zbuffer[pos] = z; // update z-buffer
				setPixel(x, y);
			}
		}

		/// Sets a color for a given pixel inside memory
		/*
			Sets a specific place inside memory with a given color.

			@param x[in] X coordinate.
			@param y[in] Y coordinate.
			@param color[in] A color.
		*/
		void			setColorBuffer(uint32 x, uint32 y, color_rgba color)
		{
			uint32 i = _w * y + x;
			 // we may want to draw outside of viewport, so better check
			if ( i > _w * _h )
				return;

			_colorBuffer[i] = color;
		}

		/**
			Sets a mode in which we operate when multiplying matrices.
			
			@param mode[in] Mode to apply matrix transformation.
		*/
		void			setMatrixMode( sglEMatrixMode mode )
		{ _currentMatrixMode = mode; }

		sglEMatrixMode	getMatrixMode()
		{ return _currentMatrixMode; }

		void			setViewport(int width, int height)
		{ 
			_viewport_w = width;
			_viewport_h = height;
		}

		uint32		getViewportWidth()
		{ return _viewport_w; }

		uint32		getViewportHeight()
		{ return _viewport_h; }

		void			depthTest(bool value)
		{ _depthTest = value; }

		matrix4x4		getCurrentMatrix() const
		{ return _currentMatrix; }

		const float*	getCurrentMatrixPointer()
		{ return _currentMatrix.ptr(); }

		void			setCurrentMatrix(matrix4x4 matrix)
		{ 
			_currentMatrix = matrix; 
		}

		bool isInCycle() const
		{
			return _inCycle;
		}

		void setInCycle(bool value)
		{
			_inCycle = value;
		}

		std::vector<matrix4x4>* getMatrixStack()
		{
			return _matrixStack;
		}

		void setMatrix( Matrices m )
		{ _matrix[m] = _currentMatrix; }

		matrix4x4 getMatrix( Matrices m ) const
		{ return _matrix[m]; }

		void setViewportMin( uint32 min_x, uint32 min_y )
		{
			_viewport_min_x = min_x;
			_viewport_min_y = min_y;
		}

		void setAreaMode( sglEAreaMode mode )
		{ _currentAreaMode = mode; }

		sglEAreaMode getAreaMode() const
		{ return _currentAreaMode; }
		

	protected:
		void callMVPMupdate()
		{
			_matrix[M_MVP] =  _matrix[M_PROJECTION] * _matrix[M_MODELVIEW];

			_updateMVPMneeded = false;
		}

		void initZBuffer()
		{
			uint32 size = _w * _h;
			_zbuffer = new float[_w * _h];

			for (uint32 i = 0; i < size; ++i)
				_zbuffer[i] = Z_BUFFER_INFINITY;
		}

	private:
		uint32 _w, _h;
		
		color_rgba*				_colorBuffer;
		float*					_zbuffer;

		float					_pointSize;

		color_rgba				_currentColor;
		std::vector<vertex>		_vertexBuffer;
		std::vector<matrix4x4>*	_matrixStack;
		std::vector<uint32>		_edgeBuffer;
		
		uint32					_viewport_w;
		uint32					_viewport_h;
		uint32					_viewport_min_x;
		uint32					_viewport_min_y;
		
		matrix4x4				_currentMatrix;
		matrix4x4				_matrix[3];

		sglEMatrixMode			_currentMatrixMode;
		sglEAreaMode			_currentAreaMode;
		sglEElementType			_drawingMode;

		bool					_inCycle;
		bool					_depthTest;
		bool					_updateMVPMneeded;

		std::vector<edge>		_nonActiveEdges;
		std::vector<edge>		_activeEdges;

};

class ContextManager
{
	public:
		Context* currentContext(){ return _currentContext; }
		uint32 addContext(Context* context)
		{
			_contextContainer.push_back(context);

			return _contextContainer.size()-1;
		}
		void setCurrentContext(Context* c){ _currentContext = c; }
		void setCurrentContext(uint32 id){ _currentContext = _contextContainer[id]; }

		uint32 contextId(){ return _contextContainer.size()-1; }
		uint32 contextSize(){ return _contextContainer.size(); }

		void destroyContext(uint32 id)
		{
			delete _contextContainer[id];

			_contextContainer[id] = 0;
		} 

	private:
		Context* _currentContext;
		std::vector<Context*> _contextContainer;
};

#endif
