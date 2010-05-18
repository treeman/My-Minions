#include "BoxRender.hpp"
#include "Hge/Hge.hpp"
#include "Tree/Log.hpp"
#include "Tree/Loghelper.hpp"

#include <vector>
#include <boost/foreach.hpp>

using namespace b2Debug;

void Poly::Render()
{
    hgeh::render_lines( hge, ps, color );
}

struct Edge {
    Edge( Vec2D p1, Vec2D p2 )
    {
        int p1_x = (int)( p1.x );
        int p1_y = (int)( p1.y );
        int p2_x = (int)( p2.x );
        int p2_y = (int)( p2.y );

        if( p1_y < p2_y ) {
            y_min = p1_y;
            x = p1_x;
            y_max = p2_y;
        }
        else {
            y_min = p2_y;
            x = p2_x;
            y_max = p1_y;
        }
        if( p1_x == p2_x ) slope = 1000;
        else slope = (p1.y - p2.y) / (p1.x - p2.x);
        if( LOGHELPER->ShallLog() ) {
            L_ << " making " << p1_x << "," << p1_y << " " << p2_x << "," << p2_y;
        }
    }

    int y_min;
    int y_max;
    int x;
    float slope;
};

void Log( std::vector<Edge> edges )
{
    if( LOGHELPER->ShallLog() ) {
        for( int i = 0; i < edges.size(); ++i ) {
            L_ << "y_min: " << edges[i].y_min << " " << edges[i].x << " max: " 
                << edges[i].y_max << " slope: " << edges[i].slope;
        }
    }
}

bool min_x( Edge e1, Edge e2 )
{
    return e1.x < e2.x;
}

bool global_order( Edge e1, Edge e2 )
{
    if( e1.y_min == e2.y_min )
        return e1.x < e2.x;
    else
        return e1.y_min < e2.y_min;
}

void SolidPolygon::Render()
{
    if( ps.empty() ) return;

    if( LOGHELPER->ShallLog() ) {
        L_ << "rendering solid polygon";
    }

    typedef std::vector<Edge> Edges;
    Edges edges;

    //initialize edges
    for( int i = 0; i < ps.size(); ++i ) {
        int j = i + 1;
        if( j < ps.size() ) {
            edges.push_back( Edge( ps[i], ps[j] ) );
        }
    }
    edges.push_back( Edge( ps.front(), ps.back() ) );

    if( LOGHELPER->ShallLog() ) {
        L_ << "edges: " << edges.size();
        Log( edges );
    }

    Edges global_edges;

    //init global edges
    for( int i = 0, g = 0; i < edges.size(); ++i ) {
        if( edges[i].slope == 0 ) continue;
        else global_edges.push_back( edges[i] );

        /*if( global_edges.empty() ) {
            global_edges.push_back( edges[i] );
        }
        else {
            if( edges[i].y_min > global_edges[g].y_min ) {
                if( i != global_edges.size() ) ++g;
            }
            else if( edges[i].x > global_edges[g].x ) {
                if( i != global_edges.size() ) ++g;
            }

            if( g < global_edges.size() ) {
                global_edges.insert( global_edges.begin() + g, edges[i] );
            }
            else {
                global_edges.push_back( edges[i] );
            }
        }*/
    }
    std::stable_sort( global_edges.begin(), global_edges.end(), global_order );
    if( LOGHELPER->ShallLog() ) {
        L_ << "global edges: " << global_edges.size();
        Log( global_edges );
    }

    //initialize parity
    int parity = 0;

    //and scan line
    float scan_line = global_edges[0].y_min;
    if( LOGHELPER->ShallLog() ) {
        L_ << "lowest y: " << scan_line;
    }

    Edges active_edges;

    //init active edges
    for( int i = 0; i < global_edges.size(); ++i ) {
        if( global_edges[i].y_min == scan_line ) {
            active_edges.push_back( global_edges[i] );
        }
    }

    if( LOGHELPER->ShallLog() ) {
        L_ << "active edges: " << active_edges.size();
        Log( active_edges );
    }

    //render loop
    while( !active_edges.empty() ) {

        if( LOGHELPER->ShallLog() ) {
            L_ << "looping";
        }

        //draw a line
        for( int i = 0; i < active_edges.size(); i += 2 ) {
            int n = i + 1;
            if( n < active_edges.size() ) {
                Edge e1 = active_edges[i];
                Edge e2 = active_edges[n];

                if( LOGHELPER->ShallLog() ) {
                    L_ << "drawing line: " << e1.x << " " << e2.x << " " << scan_line;
                }
                hge->Gfx_RenderLine( e1.x, scan_line, e2.x, scan_line, color );

                //change parity
                if( parity ) parity = 0;
                else parity = 1;
            }
        }

        //go up
        scan_line++;

        //remove edges that y_max == scan_line
        Edges next_active_edges;
        for( int i = 0; i < active_edges.size(); ++i ) {
            if( active_edges[i].y_max != scan_line ) {
                active_edges[i].x = (int)( (float)active_edges[i].x + 1 / active_edges[i].slope );
                next_active_edges.push_back( active_edges[i] );
            }
        }
        active_edges = next_active_edges;
        if( LOGHELPER->ShallLog() ) {
            L_ << "active_edges: " << active_edges.size();
            Log( active_edges );
        }

        //take the next lines we're scanning from global
        Edges new_global_edges;
        for( int i = 0; i < global_edges.size(); ++i ) {
            if( global_edges[i].y_min == scan_line ) {
                active_edges.push_back( global_edges[i] );
            }
            else {
                new_global_edges.push_back( global_edges[i] );
            }
        }
        global_edges = new_global_edges;
        if( LOGHELPER->ShallLog() ) {
            L_ << "global_edges: " << global_edges.size();
            Log( global_edges );
        }

        //reorder active_edges table to have min x at the top
        std::sort( active_edges.begin(), active_edges.end(), min_x );
        if( LOGHELPER->ShallLog() ) {
            L_ << "sorted active edges!";
            Log( active_edges );
        }
    }

    if( LOGHELPER->ShallLog() ) {
        L_ << " done!";
    }
    hgeh::render_lines( hge, ps, color );
}
void Circle::Render()
{
    hgeh::render_circle( hge, center.x, center.y, radius, 14, color );
}

void SolidCircle::Render()
{
    hgeh::render_solid_circle( hge, center.x, center.y, radius, 14, color );
}
void Segment::Render()
{
    hge->Gfx_RenderLine( p1.x, p1.y, p2.x, p2.y, color );
}

void Drawer::DrawPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color )
{
    boost::shared_ptr<Shape> s( new Poly( vertices, vertexCount, color ) );
    shapes.push_back( s );
}

void Drawer::DrawSolidPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color )
{
    boost::shared_ptr<Shape> s( new SolidPolygon( vertices, vertexCount, color ) );
    shapes.push_back( s );
}

void Drawer::DrawCircle( const b2Vec2& center, float32 radius, const b2Color& color )
{
    boost::shared_ptr<Shape> s( new Circle( center, radius, color ) );
    shapes.push_back( s );
}

void Drawer::DrawSolidCircle( const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color )
{
    boost::shared_ptr<Shape> s( new SolidCircle( center, radius, color ) );
    shapes.push_back( s );
}

void Drawer::DrawSegment( const b2Vec2& p1, const b2Vec2& p2, const b2Color& color )
{
    boost::shared_ptr<Shape> s( new Segment( p1, p2, color ) );
    shapes.push_back( s );
}

void Drawer::DrawXForm( const b2XForm& xf )
{

}

void Drawer::Render()
{
    BOOST_FOREACH( boost::shared_ptr<Shape> s, shapes ) {
        s->Render();
    }
    shapes.clear();
}

