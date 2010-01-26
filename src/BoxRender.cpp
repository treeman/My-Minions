#include "BoxRender.hpp"
#include "Hge/Hge.hpp"
#include "Tree/Log.hpp"

#include <vector>

void render_body( b2Body *body )
{
	HgeObj hge;
	b2Shape *shape = body->GetShapeList();
	while( shape ) {
		
		if( shape->GetType() == e_circleShape ) {
			b2CircleShape *circle = dynamic_cast<b2CircleShape*>( shape );
			
			b2Vec2 pos = body->GetPosition() + circle->GetLocalPosition();
			hgeh::render_solid_circle( hge, pos.x, pos.y, circle->GetRadius(), 12, 0xff935a80 );
		}
		else if( shape->GetType() == e_polygonShape ) {
			b2PolygonShape *poly = dynamic_cast<b2PolygonShape*>( shape );
			
			int vertex_count = poly->GetVertexCount();
			const b2Vec2 *vertices = poly->GetVertices();
			std::vector<Vec2D> coords;
			
			for( int n = 0; n < vertex_count; ++n )
			{
				Vec2D pos = Vec2D( body->GetPosition() + vertices[n] );
				coords.push_back( pos );
			}
			
			hgeh::render_lines( hge, coords, 0xfffe10af, true );
		}
		
		shape = shape->GetNext();
	}
}
