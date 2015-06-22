#pragma once


//これってinline展開されるの？？？


//チェック付きdelete
template <typename T> void safe_delete ( T*& p )
{
	typedef char type_must_be_complete [sizeof( T ) ? 1 : -1];
	( void ) sizeof( type_must_be_complete );
	if ( p != nullptr ) { delete ( p ); ( p ) = nullptr; }
}

template <typename T> void safe_delete(T **p)
{
	typedef char type_must_be_complete[sizeof(T) ? 1 : -1];
	(void) sizeof(type_must_be_complete);
	if ((*p) != nullptr) { delete (*p); (*p) = nullptr; }
}

//チェック付きdelete(配列用)
template <typename T> void safe_array_delete ( T*& p )
{
	typedef char type_must_be_complete [sizeof( T ) ? 1 : -1];
	( void ) sizeof( type_must_be_complete );
	if ( p != nullptr ) { delete[] ( p ); ( p ) = nullptr; }
}

template <typename T> void safe_array_delete(T **p)
{
	typedef char type_must_be_complete[sizeof(T) ? 1 : -1];
	(void) sizeof(type_must_be_complete);
	if ((*p) != nullptr) { delete[](*p); (*p) = nullptr; }
}


//チェック付きRelease
template <typename T> void safe_release(T*& p)
{
	typedef char type_must_be_complete[sizeof(T) ? 1 : -1];
	(void) sizeof(type_must_be_complete);
	if (p != nullptr) { (p)->Release(); (p) = nullptr; }
}

template <typename T> void safe_release(T **p)
{
	typedef char type_must_be_complete[sizeof(T) ? 1 : -1];
	(void) sizeof(type_must_be_complete);
	if ((*p) != nullptr) { (*p)->Release(); (*p) = nullptr; }
}



// ポインタの先が存在するかどうかチェックする
template <typename T> bool is_nullptr(T*& p)
{
	typedef char type_must_be_complete[sizeof(T) ? 1 : -1];
	(void) sizeof(type_must_be_complete);
	return (p == nullptr);
}

template <typename T> bool is_nullptr(T **p)
{
	typedef char type_must_be_complete[sizeof(T) ? 1 : -1];
	(void) sizeof(type_must_be_complete);
	return ((*p) == nullptr);
}


//EOF