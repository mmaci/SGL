#ifndef __RAY_TRACER_H__
#define __RAY_TRACER_H__
#include <iostream>

class RayTracer
{
	public:	
		void addLight( PointLight* light )
		{
			// TODO: There might be more light types in the future, atm leave
			// just PointLight, because inheritance is a pretty large overhead
			
			_lights.push_back( light );
		}

		void addSphere( Sphere* sphere )
		{
			addPrimitive( sphere );
		}

		void addTriangle( Triangle* triangle )
		{
			addPrimitive( triangle );
		}

		void addPrimitive( Primitive* primitive )
		{
			primitive->setMaterial( _currentMaterial );

			_primitives.push_back( primitive );
		}

		void setCurrentMaterial( material m )
		{
			_currentMaterial = m;
		}

		/// Casts a ray at an [x, y] coordinate
		/**
			Casts a ray at an [x, y] coordinate in viewport space.

			@param		x[in] X coord
			@param		y[in] Y coord
			@return		color of the reflection
		*/
		const rgb<float> castRay( uint32 x, uint32 y )
		{			
			HitInfo hitInfo;

			return intersectRayWithScene( generateRay(x, y), &hitInfo );		
		}

		/// Generates a ray for an [x, y] coordinate
		/**
			Based on given [x, y] coordinates, it returns a ray. Therefore we need to set ray origin (0, 0, 0) and 
			a direction inverse-transformation-matrix * x-y-vector.

			@param		x[in] X coord
			@param		y[in] Y coord
			@return		Ray
		*/
		Ray* generateRay( uint32 x, uint32 y )
		{				
					

			vector3<float>vecX(static_cast<float>(x) / static_cast<float>(_viewport.width()), 0.0f, 0.0f);
			vector3<float>vecY(0.0f, static_cast<float>(y) / static_cast<float>(_viewport.height()), 0.0f);
			
			vector3<float>camera(0.0f, 0.0f, 0.0f);
			vector3<float>origin(0.0f, 0.0f, -0.5f);				

			vector3<float>dir = vecX + vecY + camera - origin;						
			dir.normalize();

			// std::cout << "normalized [" << dir.x() << ", " << dir.y() << ", " << dir.z() << "]" << std::endl;
			
			return new Ray( origin, 
							dir );
		}

		/// Intersection of the scene and a ray
		/**
			Intersects the ray with all the primitives in the scene. If it hits a primitive, it writes the details
			inside hitInfo and calculates the color of the reflection based on the Phong model. The color then bubbles up
			to castRay-renderScene and is written inside the color buffer.

			@param		ray
			@param		hitInfo	Info structure to describe the intersection of the ray and the scene
			@return		color
		*/
		const rgb<float> intersectRayWithScene( Ray* ray, HitInfo* hitInfo )
		{
			for ( std::vector<Primitive*>::iterator it = _primitives.begin(); it != _primitives.end(); ++it )
			{
				// we cast the ray at every primitive (sphere, triangle) in the scene
				// and see what happens
				if ( (*it)->intersect( ray, hitInfo ) )
				{
					// we hit a primitive								
					return phong( ray, hitInfo );
				}
			}
			return BLACK;
		}

		const rgb<float> phong( Ray* ray, HitInfo *hitInfo )
		{
			// TODO
			return WHITE;
		}

		void setInverseMatrix( matrix4x4 const& matrix )
		{
			_inverseMVP = matrix;
		}

		void setViewportMatrix( viewport viewport, matrix4x4 const& matrix )
		{
			_viewportM = matrix;
			_viewport = viewport;
		}

	private:
		std::vector<PointLight*>	_lights;
		std::vector<Primitive*>		_primitives;

		matrix4x4					_inverseMVP;
		matrix4x4					_viewportM;
		viewport					_viewport;

		material					_currentMaterial;
};

#endif