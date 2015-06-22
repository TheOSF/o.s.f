#ifndef __DEBUG_DRAW_MANAGER_H__
#define __DEBUG_DRAW_MANAGER_H__

#include <stdio.h>
#include <d3dx9.h>
#include <list>

struct _DDM
{
	enum { BLACK = 0x00000000, RED = 0xFFFF0000, GREEN = 0xFF00FF00, BLUE = 0xFF0000FF, YELLOW = 0xFFFFFF00, MAGENTA = 0xFFFF00FF, CYAN = 0xFF00FFFF, WHITE = 0xFFFFFFFF };
	static _DDM &I()
	{
		static _DDM i;
		return i;
	}
	static void DrawLine( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3 &p0, CONST D3DXVECTOR3 &p1, D3DCOLOR c = WHITE )
	{
		static _VB vb( d3dd, sizeof( D3DXVECTOR3 ) * 2 );

		D3DXVECTOR3 *p;
		vb->Lock( 0, 0, ( void ** )&p, 0 );
		p[0] = p0;
		p[1] = p1;
		vb->Unlock();

		D3DMATERIAL9 m = { 0 };
		m.Diffuse = m.Ambient = D3DXCOLOR( c );
		d3dd->SetMaterial( &m );

		d3dd->SetFVF( D3DFVF_XYZ );
		d3dd->SetStreamSource( 0, vb, 0, sizeof( D3DXVECTOR3 ) );
		d3dd->SetTransform( D3DTS_WORLD, &D3DXMATRIX( 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 ) );
		d3dd->DrawPrimitive( D3DPT_LINELIST, 0, 1 );
	}
	static void DrawTriangle( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3 &p0, CONST D3DXVECTOR3 &p1, CONST D3DXVECTOR3 &p2, D3DCOLOR c = WHITE )
	{
		static _VB vb( d3dd, sizeof( D3DXVECTOR3 ) * 4 );

		D3DXVECTOR3 *p;
		vb->Lock( 0, 0, ( void ** )&p, 0 );
		p[0] = p0;
		p[1] = p1;
		p[2] = p2;
		p[3] = p[0];
		vb->Unlock();

		D3DMATERIAL9 m = { 0 };
		m.Diffuse = m.Ambient = D3DXCOLOR( c );
		d3dd->SetMaterial( &m );

		d3dd->SetFVF( D3DFVF_XYZ );
		d3dd->SetStreamSource( 0, vb, 0, sizeof( D3DXVECTOR3 ) );
		d3dd->SetTransform( D3DTS_WORLD, &D3DXMATRIX( 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 ) );
		d3dd->DrawPrimitive( D3DPT_LINESTRIP, 0, 3 );
	}
	static void DrawCross( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3 &p0, FLOAT s /*size*/, D3DCOLOR c = WHITE )
	{
		static _VB vb( d3dd, sizeof( D3DXVECTOR3 ) * 6 );

		D3DXVECTOR3 *p;
		vb->Lock( 0, 0, ( void ** )&p, 0 );
		p[0] = p0 + D3DXVECTOR3( -1.0f, 0.0f, 0.0f ) * s;
		p[1] = p0 + D3DXVECTOR3( 1.0f, 0.0f, 0.0f ) * s;
		p[2] = p0 + D3DXVECTOR3( 0.0f, -1.0f, 0.0f ) * s;
		p[3] = p0 + D3DXVECTOR3( 0.0f, 1.0f, 0.0f )* s;
		p[4] = p0 + D3DXVECTOR3( 0.0f, 0.0f, -1.0f ) * s;
		p[5] = p0 + D3DXVECTOR3( 0.0f, 0.0f, 1.0f ) * s;
		vb->Unlock();

		D3DMATERIAL9 m = { 0 };
		m.Diffuse = m.Ambient = D3DXCOLOR( c );
		d3dd->SetMaterial( &m );

		d3dd->SetFVF( D3DFVF_XYZ );
		d3dd->SetStreamSource( 0, vb, 0, sizeof( D3DXVECTOR3 ) );
		d3dd->SetTransform( D3DTS_WORLD, &D3DXMATRIX( 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 ) );
		d3dd->DrawPrimitive( D3DPT_LINELIST, 0, 3 );
	}
	static void DrawCircle( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3 &p0, CONST D3DXVECTOR3 &n, FLOAT r, D3DCOLOR c = WHITE )
	{
		CONST INT N = 36;

		static _VB vb( d3dd, sizeof( D3DXVECTOR3 ) * ( N + 1 ) );
		D3DXVECTOR3 *p;
		vb->Lock( 0, 0, ( void ** )&p, 0 );
		for( int i = 0; i < N; i++ )
		{
			p[i] = r * D3DXVECTOR3( sinf( 360.0f / N * 0.01745f * i ), 0, cosf( 360.0f / N * 0.01745f * i ) );
		}
		p[N] = p[0];
		vb->Unlock();

		D3DXVECTOR3 axis;
		D3DXVec3Cross( &axis, &D3DXVECTOR3( 0, 1, 0 ), &n );
		D3DXVec3Normalize( &axis, &axis );
		FLOAT angle = acosf( D3DXVec3Dot( &n, &D3DXVECTOR3( 0, 1, 0 ) ) / D3DXVec3Length(&n ) );
		D3DXMATRIX M;
		D3DXMatrixRotationAxis( &M, &axis, angle );
		M._41 = p0.x;
		M._42 = p0.y;
		M._43 = p0.z;

		D3DMATERIAL9 m = { 0 };
		m.Diffuse = m.Ambient = D3DXCOLOR( c );
		d3dd->SetMaterial( &m );

		d3dd->SetFVF( D3DFVF_XYZ );
		d3dd->SetStreamSource( 0, vb, 0, sizeof( D3DXVECTOR3 ) );
		d3dd->SetTransform( D3DTS_WORLD, &M );
		d3dd->DrawPrimitive( D3DPT_LINESTRIP, 0, N );
	}
	static void DrawSphere( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3 &p0, FLOAT r, D3DCOLOR c = WHITE )
	{
		CONST INT N = 36;

		static _VB vb( d3dd, sizeof( D3DXVECTOR3 ) * ( N + 1 ) );
		for( int n = 0; n < 3; n++ )
		{

			D3DXVECTOR3 *p;
			vb->Lock( 0, 0, ( void ** )&p, 0 );
			for( int i = 0; i < N; i++ )
			{
				switch( n )
				{
				case 0: p[i] = r * D3DXVECTOR3( sinf( 360.0f / N * 0.01745f * i ), cosf( 360.0f / N * 0.01745f * i ), 0 ) + p0; break;
				case 1: p[i] = r * D3DXVECTOR3( sinf( 360.0f / N * 0.01745f * i ), 0, cosf( 360.0f / N * 0.01745f * i ) ) + p0; break;
				case 2: p[i] = r * D3DXVECTOR3( 0, sinf( 360.0f / N * 0.01745f * i ), cosf( 360.0f / N * 0.01745f * i ) ) + p0; break;
				}
			}
			p[N] = p[0];
			vb->Unlock();

			D3DMATERIAL9 m = { 0 };
			m.Diffuse = m.Ambient = D3DXCOLOR( c );
			d3dd->SetMaterial( &m );

			d3dd->SetFVF( D3DFVF_XYZ );
			d3dd->SetStreamSource( 0, vb, 0, sizeof( D3DXVECTOR3 ) );
			d3dd->SetTransform( D3DTS_WORLD, &D3DXMATRIX( 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 ) );
			d3dd->DrawPrimitive( D3DPT_LINESTRIP, 0, N );
		}
	}
	static void DrawPlane( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3 &n, FLOAT d, FLOAT s /*size*/, D3DCOLOR c = WHITE )
	{
		static _VB vb( d3dd, sizeof( D3DXVECTOR3 ) * ( 4 + 1 ) );

		D3DXVECTOR3 *p;
		vb->Lock( 0, 0, ( void ** )&p, 0 );
		p[0] = D3DXVECTOR3( -s, 0, -s );
		p[1] = D3DXVECTOR3( s, 0, -s );
		p[2] = D3DXVECTOR3( s, 0, s );
		p[3] = D3DXVECTOR3( -s, 0, s );
		p[4] = p[0];
		vb->Unlock();

		D3DXVECTOR3 axis;
		D3DXVec3Cross( &axis, &D3DXVECTOR3( 0, 1, 0 ), &n );
		D3DXVec3Normalize( &axis, &axis );
		FLOAT angle = acosf( D3DXVec3Dot( &n, &D3DXVECTOR3( 0, 1, 0 ) ) / D3DXVec3Length( &n ) );
		D3DXMATRIX M;
		D3DXMatrixRotationAxis( &M, &axis, angle );
		M._41 = n.x * d;
		M._42 = n.y * d;
		M._43 = n.z * d;

		D3DMATERIAL9 m = { 0 };
		m.Diffuse = m.Ambient = D3DXCOLOR( c );
		d3dd->SetMaterial( &m );

		d3dd->SetFVF( D3DFVF_XYZ );
		d3dd->SetStreamSource( 0, vb, 0, sizeof( D3DXVECTOR3 ) );
		d3dd->SetTransform( D3DTS_WORLD, &M );
		d3dd->DrawPrimitive( D3DPT_LINESTRIP, 0, 4 );
	}
	static void DrawAABB( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3 &min, CONST D3DXVECTOR3 &max, D3DCOLOR c = WHITE )
	{
		static _VB vb( d3dd, sizeof( D3DXVECTOR3 ) * 12 * 2 );

		D3DXVECTOR3 *p;
		vb->Lock( 0, 0, ( void ** )&p, 0 );
		p[0] = D3DXVECTOR3( min.x, min.y, min.z );
		p[1] = D3DXVECTOR3( max.x, min.y, min.z );
		p[2] = D3DXVECTOR3( max.x, min.y, min.z );
		p[3] = D3DXVECTOR3( max.x, min.y, max.z );
		p[4] = D3DXVECTOR3( max.x, min.y, max.z );
		p[5] = D3DXVECTOR3( min.x, min.y, max.z );
		p[6] = D3DXVECTOR3( min.x, min.y, max.z );
		p[7] = D3DXVECTOR3( min.x, min.y, min.z );

		p[8] = D3DXVECTOR3( min.x, max.y, min.z );
		p[9] = D3DXVECTOR3( max.x, max.y, min.z );
		p[10] = D3DXVECTOR3( max.x, max.y, min.z );
		p[11] = D3DXVECTOR3( max.x, max.y, max.z );
		p[12] = D3DXVECTOR3( max.x, max.y, max.z );
		p[13] = D3DXVECTOR3( min.x, max.y, max.z );
		p[14] = D3DXVECTOR3( min.x, max.y, max.z );
		p[15] = D3DXVECTOR3( min.x, max.y, min.z );

		p[16] = D3DXVECTOR3( min.x, min.y, min.z );
		p[17] = D3DXVECTOR3( min.x, max.y, min.z );
		p[18] = D3DXVECTOR3( max.x, min.y, min.z );
		p[19] = D3DXVECTOR3( max.x, max.y, min.z );
		p[20] = D3DXVECTOR3( max.x, min.y, max.z );
		p[21] = D3DXVECTOR3( max.x, max.y, max.z );
		p[22] = D3DXVECTOR3( min.x, min.y, max.z );
		p[23] = D3DXVECTOR3( min.x, max.y, max.z );
		vb->Unlock();

		D3DMATERIAL9 m = { 0 };
		m.Diffuse = m.Ambient = D3DXCOLOR( c );
		d3dd->SetMaterial( &m );

		d3dd->SetFVF( D3DFVF_XYZ );
		d3dd->SetStreamSource( 0, vb, 0, sizeof( D3DXVECTOR3 ) );
		d3dd->SetTransform( D3DTS_WORLD, &D3DXMATRIX( 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 ) );
		d3dd->DrawPrimitive( D3DPT_LINELIST, 0, 12 );
	}
	static void DrawOBB ( LPDIRECT3DDEVICE9 d3dd, CONST D3DXMATRIX &o /* orientation */, CONST D3DXVECTOR3 &s /* size */, D3DCOLOR c = WHITE )
	{
		static _VB vb ( d3dd, sizeof(D3DXVECTOR3) * 12 * 2 );

		D3DXVECTOR3 _min ( -s.x * 0.5f, -s.y * 0.5f, -s.z * 0.5f );
		D3DXVECTOR3 _max ( s.x * 0.5f, s.y * 0.5f, s.z * 0.5f );

		D3DXVECTOR3 *p;
		vb->Lock ( 0, 0, (void **) &p, 0 );
		p [0] = D3DXVECTOR3 ( _min.x, _min.y, _min.z );
		p [1] = D3DXVECTOR3 ( _max.x, _min.y, _min.z );
		p [2] = D3DXVECTOR3 ( _max.x, _min.y, _min.z );
		p [3] = D3DXVECTOR3 ( _max.x, _min.y, _max.z );
		p [4] = D3DXVECTOR3 ( _max.x, _min.y, _max.z );
		p [5] = D3DXVECTOR3 ( _min.x, _min.y, _max.z );
		p [6] = D3DXVECTOR3 ( _min.x, _min.y, _max.z );
		p [7] = D3DXVECTOR3 ( _min.x, _min.y, _min.z );

		p [8] = D3DXVECTOR3 ( _min.x, _max.y, _min.z );
		p [9] = D3DXVECTOR3 ( _max.x, _max.y, _min.z );
		p [10] = D3DXVECTOR3 ( _max.x,_max.y, _min.z );
		p [11] = D3DXVECTOR3 ( _max.x,_max.y, _max.z );
		p [12] = D3DXVECTOR3 ( _max.x,_max.y, _max.z );
		p [13] = D3DXVECTOR3 ( _min.x, _max.y, _max.z );
		p [14] = D3DXVECTOR3 ( _min.x, _max.y, _max.z );
		p [15] = D3DXVECTOR3 ( _min.x, _max.y, _min.z );

		p [16] = D3DXVECTOR3 ( _min.x, _min.y, _min.z );
		p [17] = D3DXVECTOR3 ( _min.x, _max.y, _min.z );
		p [18] = D3DXVECTOR3 ( _max.x, _min.y, _min.z );
		p [19] = D3DXVECTOR3 ( _max.x, _max.y, _min.z );
		p [20] = D3DXVECTOR3 ( _max.x, _min.y, _max.z );
		p [21] = D3DXVECTOR3 ( _max.x, _max.y, _max.z );
		p [22] = D3DXVECTOR3 ( _min.x, _min.y, _max.z );
		p [23] = D3DXVECTOR3 ( _min.x, _max.y, _max.z );
		vb->Unlock ();

		D3DMATERIAL9 m = { 0 };
		m.Diffuse = m.Ambient = D3DXCOLOR ( c );
		d3dd->SetMaterial ( &m );

		d3dd->SetFVF ( D3DFVF_XYZ );
		d3dd->SetStreamSource ( 0, vb, 0, sizeof( D3DXVECTOR3 ) );
		d3dd->SetTransform ( D3DTS_WORLD, &o );
		d3dd->DrawPrimitive ( D3DPT_LINELIST, 0, 12 );
	}
	static void DrawArrow( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3 &p0, FLOAT yaw, FLOAT pitch, FLOAT roll, FLOAT s /*size*/, D3DCOLOR c = WHITE )
	{
		static _VB vb( d3dd, sizeof( D3DXVECTOR3 ) * 8 );

		D3DXVECTOR3 *p;
		vb->Lock( 0, 0, ( void ** )&p, 0 );
		p[0] = D3DXVECTOR3( 0.0f, 0.0f, 1.0f ) * s;
		p[1] = D3DXVECTOR3( 1.0f, 0.0f, 0.0f ) * s;
		p[2] = D3DXVECTOR3( 0.5f, 0.0f, 0.0f ) * s;
		p[3] = D3DXVECTOR3( 0.5f, 0.0f, -1.0f ) * s;
		p[4] = D3DXVECTOR3( -0.5f, 0.0f, -1.0f ) * s;
		p[5] = D3DXVECTOR3( -0.5f, 0.0f, 0.0f ) * s;
		p[6] = D3DXVECTOR3( -1.0f, 0.0f, 0.0f ) * s;
		p[7] = p[0];
		vb->Unlock();

		D3DXMATRIX M;
		D3DXMatrixRotationYawPitchRoll( &M, yaw, pitch, roll );
		M._41 = p0.x;
		M._42 = p0.y;
		M._43 = p0.z;

		D3DMATERIAL9 m = { 0 };
		m.Diffuse = m.Ambient = D3DXCOLOR( c );
		d3dd->SetMaterial( &m );

		d3dd->SetFVF( D3DFVF_XYZ );
		d3dd->SetStreamSource( 0, vb, 0, sizeof( D3DXVECTOR3 ) );
		d3dd->SetTransform( D3DTS_WORLD, &M );
		d3dd->DrawPrimitive( D3DPT_LINESTRIP, 0, 7 );
	}
	static void DrawVector( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3 &v, CONST D3DXVECTOR3 &p,
		FLOAT r, /* radius */
		FLOAT h, /* head */
		D3DCOLOR c = WHITE )
	{
		static struct _
		{
			LPD3DXMESH cylinder, corn;

			_( LPDIRECT3DDEVICE9 d3dd ) : cylinder( 0 ), corn( 0 )
			{
				D3DXCreateCylinder( d3dd, 1.0f, 1.0f, 1.0f, 10, 1, &cylinder, 0 );
				D3DXCreateCylinder( d3dd, 1.0f, 0.0f, 1.0f, 10, 1, &corn, 0 );
			}
			virtual ~_()
			{
				cylinder->Release();
				corn->Release();
			}
		} a( d3dd );

		D3DXVECTOR3 axis( 0, 1, 0 );
		FLOAT angle = 0;

		FLOAT l = D3DXVec3Length( &v );
		if ( l < 1.0e-8f ) return;

		const D3DXVECTOR3 z( 0, 0, 1 );
		D3DXVec3Cross( &axis, &z, &v );
		D3DXVec3Normalize( &axis, &axis );
		angle = acosf( D3DXVec3Dot( &v, &z ) / l );

		D3DMATERIAL9 m = { 0 };
		m.Diffuse = m.Ambient = D3DXCOLOR( c );
		d3dd->SetMaterial( &m );

		D3DXMATRIX m1, m2, m3, m4;

		D3DXMatrixScaling( &m1, r, r, l );
		m1._43 = 0.5f * l;
		D3DXMatrixRotationAxis( &m2, &axis, angle );
		D3DXMatrixTranslation( &m3, p.x, p.y, p.z );

		d3dd->SetTransform( D3DTS_WORLD, &( m1 * m2 * m3 ) );
		a.cylinder->DrawSubset( 0 );

		D3DXMatrixScaling( &m1, h, h, h * 1.618f );
		D3DXMatrixTranslation( &m4, v.x, v.y, v.z );
		d3dd->SetTransform( D3DTS_WORLD, &( m1 * m2 * m4 * m3 ) );
		a.corn->DrawSubset( 0 );
	}
	static void DrawPoint( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3 &p, FLOAT r, D3DCOLOR c = WHITE )
	{
		static struct _
		{
			LPD3DXMESH p;

			_( LPDIRECT3DDEVICE9 d3dd ) : p( 0 )
			{
				D3DXCreateSphere( d3dd, 1.0f, 10, 10, &p, 0 );
			}
			virtual ~_()
			{
				p->Release();
			}
		} s( d3dd );

		D3DMATERIAL9 m = { 0 };
		m.Diffuse = m.Ambient = D3DXCOLOR( c );
		d3dd->SetMaterial( &m );

		D3DXMATRIX M;
		D3DXMatrixScaling( &M, r, r, r );
		M._41 = p.x;
		M._42 = p.y;
		M._43 = p.z;
		d3dd->SetTransform( D3DTS_WORLD, &M );
		s.p->DrawSubset( 0 );
	}
	static void DrawString( LPDIRECT3DDEVICE9 d3dd, LONG x, LONG y, LPCSTR s, D3DCOLOR c = WHITE )
	{
		static struct FONT 
		{
			LPD3DXFONT p;
			FONT( LPDIRECT3DDEVICE9 d3dd ) : p( 0 )
			{
				D3DXCreateFont( d3dd, 14, 7, 0, 0, 0, SHIFTJIS_CHARSET, 0, 0, 0, "Tahoma", &p );
			}
			virtual ~FONT()
			{
				if( p ) p->Release();
			}
		} f( d3dd );
		RECT rect = { x, y, 0, 0 };
		f.p->DrawTextA( 0, s, -1, &rect, DT_CALCRECT, 0 );
		f.p->DrawTextA( 0, s, -1, &rect, DT_LEFT | DT_BOTTOM, c );
	}
	void DrawQ( LPDIRECT3DDEVICE9 d3dd )
	{
		static DWORD last = timeGetTime();
		DWORD elapse = timeGetTime() - last;
		std::list< _O * >::iterator i;
		for ( i = _Q.begin(); i != _Q.end(); )
		{
			(*i)->Draw( d3dd );
			(*i)->duration -= ( ( FLOAT )elapse / 1000.0f );
			if( (*i)->duration <= 0.0f )
			{
				delete *i;
				i = _Q.erase( i );
				continue;
			}
			i++;
		}
		last += elapse;
	}
	void AddLine( CONST D3DXVECTOR3 &p0, CONST D3DXVECTOR3 &p1, D3DCOLOR c = WHITE, FLOAT duration = 0.0f  )
	{
		_Q.push_back( new _LINE( p0, p1, c, duration ) );
	}
	void AddTriangle( CONST D3DXVECTOR3 &p0, CONST D3DXVECTOR3 &p1, CONST D3DXVECTOR3 &p2, D3DCOLOR c = WHITE, FLOAT duration = 0.0f  )
	{
		_Q.push_back( new _TRIANGLE( p0, p1, p2, c, duration ) );
	}
	void AddCross( CONST D3DXVECTOR3 &p0, FLOAT s, D3DCOLOR c = WHITE, FLOAT duration = 0.0f  )
	{
		_Q.push_back( new _CROSS( p0, s, c, duration ) );
	}
	void AddCircle( CONST D3DXVECTOR3 &p0, CONST D3DXVECTOR3 &n, FLOAT r, D3DCOLOR c = WHITE, FLOAT duration = 0.0f  )
	{
		_Q.push_back( new _CIRCLE( p0, n, r, c, duration ) );
	}
	void AddSphere( CONST D3DXVECTOR3 &p0, FLOAT r, D3DCOLOR c = WHITE, FLOAT duration = 0.0f  )
	{
		_Q.push_back( new _SPHERE( p0, r, c, duration ) );
	}	
	void AddPlane( CONST D3DXVECTOR3 &n, FLOAT d, FLOAT s, D3DCOLOR c = WHITE, FLOAT duration = 0.0f  )
	{
		_Q.push_back( new _PLANE( n, d, s, c, duration ) );
	}		
	void AddAABB( CONST D3DXVECTOR3 &min, CONST D3DXVECTOR3 &max, D3DCOLOR c = WHITE, FLOAT duration = 0.0f  )
	{
		_Q.push_back( new _AABB( min, max, c, duration ) );
	}	
	void AddOBB( CONST D3DXMATRIX &o, CONST D3DXVECTOR3 &s, D3DCOLOR c = WHITE, FLOAT duration = 0.0f  )
	{
		_Q.push_back( new _OBB( o, s, c, duration ) );
	}
	void AddArrow( CONST D3DXVECTOR3 &p0, FLOAT yaw, FLOAT pitch, FLOAT roll, FLOAT s /*size*/, D3DCOLOR c = WHITE, FLOAT duration = 0.0f  )
	{
		_Q.push_back( new _ARROW( p0, yaw, pitch, roll, s, c, duration ) );
	}
	void AddVector( CONST D3DXVECTOR3 &v, CONST D3DXVECTOR3 &p, FLOAT r, FLOAT h, D3DCOLOR c = WHITE, FLOAT duration = 0.0f  )
	{
		_Q.push_back( new _VECTOR( v, p, r, h, c, duration ) );
	}
	void AddPoint( CONST D3DXVECTOR3 &p, FLOAT r, D3DCOLOR c = WHITE, FLOAT duration = 0.0f  )
	{
		_Q.push_back( new _POINT( p, r, c, duration ) );
	}
	void AddString( LONG x, LONG y, LPCSTR s, D3DCOLOR c = WHITE, FLOAT duration = 0.0f  )
	{
		_Q.push_back( new _STRING( x, y, c, s, duration ) );
	}
	static LPCSTR FormatString( LPCSTR format, ... )
	{
		static CHAR buf[1024];
		va_list args;
		va_start( args, format );
		vsnprintf_s( buf, sizeof( buf ), 1024, format, args );
		va_end( args );
		return buf;
	}
	static void OutputString( LPCSTR format, ... )
	{
		static CHAR buf[1024];
		va_list args;
		va_start( args, format );
		vsnprintf_s( buf, sizeof( buf ), 1024, format, args );
		va_end( args );
		OutputDebugStringA( buf );
	}
private:
	_DDM()
	{
	}
	virtual ~_DDM() 
	{
		for( std::list< _O * >::iterator i = _Q.begin(); i != _Q.end(); i++ )
		{
		   delete *i;
		}
		_Q.clear();
	}
	struct _O
	{
		FLOAT duration;
		_O( FLOAT duration ) : duration( duration ) {}
		virtual ~_O() {}
		virtual void Draw(  LPDIRECT3DDEVICE9 d3dd ) = 0;
	};
	std::list< _O * > _Q;
	struct _LINE : public _O
	{
		D3DXVECTOR3 p0, p1;
		D3DCOLOR c;
		_LINE( CONST D3DXVECTOR3 &p0, CONST D3DXVECTOR3 &p1, D3DCOLOR c, FLOAT duration )
			: _O( duration ), p0( p0 ), p1( p1 ), c( c ) {}
		void Draw( LPDIRECT3DDEVICE9 d3dd )
		{
			DrawLine( d3dd, p0, p1, c );
		}
	};
	struct _TRIANGLE : public _O
	{
		D3DXVECTOR3 p0, p1, p2;
		D3DCOLOR c;
		_TRIANGLE( CONST D3DXVECTOR3 &p0, CONST D3DXVECTOR3 &p1, CONST D3DXVECTOR3 &p2, D3DCOLOR c, FLOAT duration )
			: _O( duration ), p0( p0 ), p1( p1 ), p2( p2 ), c( c ) {}
		void Draw( LPDIRECT3DDEVICE9 d3dd )
		{
			DrawTriangle( d3dd, p0, p1, p2, c );
		}
	};
	struct _CROSS : public _O
	{
		D3DXVECTOR3 p0;
		FLOAT s;
		D3DCOLOR c;
		_CROSS( CONST D3DXVECTOR3 &p0, FLOAT s, D3DCOLOR c, FLOAT duration )
			: _O( duration ), p0( p0 ), s( s ), c( c ) {}
		void Draw( LPDIRECT3DDEVICE9 d3dd )
		{
			DrawCross( d3dd, p0, s, c );
		}
	};
	struct _CIRCLE : public _O
	{
		D3DXVECTOR3 p0, n;
		FLOAT r;
		D3DCOLOR c;
		_CIRCLE( CONST D3DXVECTOR3 &p0, CONST D3DXVECTOR3 &n, FLOAT r, D3DCOLOR c, FLOAT duration )
			: _O( duration ), p0( p0 ), n( n ), r( r ), c( c ) {}
		void Draw( LPDIRECT3DDEVICE9 d3dd )
		{
			DrawCircle( d3dd, p0, n, r, c );
		}
	};
	struct _SPHERE : public _O
	{
		D3DXVECTOR3 p0;
		FLOAT r;
		D3DCOLOR c;
		_SPHERE( CONST D3DXVECTOR3 &p0, FLOAT r, D3DCOLOR c, FLOAT duration )
			: _O( duration ), p0( p0 ), r( r ), c( c ) {}
		void Draw( LPDIRECT3DDEVICE9 d3dd )
		{
			DrawSphere( d3dd, p0, r, c );
		}
	};
	struct _PLANE : public _O
	{
		D3DXVECTOR3 n;
		FLOAT d;
		FLOAT s;
		D3DCOLOR c;
		_PLANE( CONST D3DXVECTOR3 &n, FLOAT d, FLOAT s, D3DCOLOR c, FLOAT duration )
			: _O( duration ), n( n ), d( d ), s( s ), c( c ) {}
		void Draw( LPDIRECT3DDEVICE9 d3dd )
		{
			DrawPlane( d3dd, n, d, s, c );
		}
	};
	struct _AABB : public _O
	{
		D3DXVECTOR3 _min, _max;
		D3DCOLOR c;
		_AABB( CONST D3DXVECTOR3 &_min, CONST D3DXVECTOR3 &_max, D3DCOLOR c, FLOAT duration )
			: _O( duration ), _min( _min ), _max( _max ), c( c ) {}
		void Draw( LPDIRECT3DDEVICE9 d3dd )
		{
			DrawAABB( d3dd, _min, _max, c );
		}
	};
	struct _OBB : public _O
	{
		D3DXMATRIX o;
		D3DXVECTOR3 s;
		D3DCOLOR c;
		_OBB( CONST D3DXMATRIX &o, CONST D3DXVECTOR3 &s, D3DCOLOR c, FLOAT duration )
			: _O( duration ), o( o ), s( s ), c( c ) {}
		void Draw( LPDIRECT3DDEVICE9 d3dd )
		{
			DrawOBB( d3dd, o, s, c );
		}
	};
	struct _ARROW : public _O
	{
		D3DXVECTOR3 p0;
		FLOAT yaw, pitch, roll;
		FLOAT s;
		D3DCOLOR c;
		_ARROW( CONST D3DXVECTOR3 &p0, FLOAT yaw, FLOAT pitch, FLOAT roll, FLOAT s, D3DCOLOR c, FLOAT duration )
			: _O( duration ), p0( p0 ), yaw( yaw ), pitch( pitch ), roll( roll ), s( s ), c( c ) {}
		void Draw( LPDIRECT3DDEVICE9 d3dd )
		{
			DrawArrow( d3dd, p0, yaw, pitch, roll, s, c );
		}
	};
	struct _VECTOR : public _O
	{
		D3DXVECTOR3 v, p;
		FLOAT r, h;
		D3DCOLOR c;
		_VECTOR( CONST D3DXVECTOR3 &v, CONST D3DXVECTOR3 &p, FLOAT r, FLOAT h, D3DCOLOR c, FLOAT duration )
			: _O( duration ), v( v ), p( p ), r( r ), h( h ), c( c ) {}
		void Draw( LPDIRECT3DDEVICE9 d3dd )
		{
			DrawVector( d3dd, v, p, r, h, c );
		}
	};
	struct _POINT : public _O
	{
		D3DXVECTOR3 p;
		FLOAT r;
		D3DCOLOR c;
		_POINT( CONST D3DXVECTOR3 &p, FLOAT r, D3DCOLOR c, FLOAT duration )
			: _O( duration ), p( p ), r( r ), c( c ) {}
		void Draw( LPDIRECT3DDEVICE9 d3dd )
		{
			DrawPoint( d3dd, p, r, c );
		}
	};
	struct _STRING : public _O
	{
		LONG x, y;
		D3DCOLOR c;
		std::string s;
		_STRING( LONG x, LONG y, D3DCOLOR c, LPCSTR s, FLOAT duration ) : _O( duration ), x( x ), y( y ), c( c ), s( s ) {}
		void Draw( LPDIRECT3DDEVICE9 d3dd )
		{
			DrawString( d3dd, x, y, s.c_str(), c );
		}
	};
	struct _VB
	{
		LPDIRECT3DVERTEXBUFFER9 p;
		_VB( LPDIRECT3DDEVICE9 d3dd, UINT length ) : p( 0 ) { d3dd->CreateVertexBuffer( length, 0, D3DFVF_XYZ, D3DPOOL_SYSTEMMEM, &p, NULL ); }
		virtual ~_VB() { if( p ) p->Release(); }
		operator LPDIRECT3DVERTEXBUFFER9() { return p; }
		LPDIRECT3DVERTEXBUFFER9 operator ->() { return p; }
	};
};

#endif //__DEBUG_DRAW_MANAGER_H__

