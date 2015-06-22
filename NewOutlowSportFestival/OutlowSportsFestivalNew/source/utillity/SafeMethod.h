#pragma once


//�������inline�W�J�����́H�H�H


//�`�F�b�N�t��delete
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

//�`�F�b�N�t��delete(�z��p)
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


//�`�F�b�N�t��Release
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



// �|�C���^�̐悪���݂��邩�ǂ����`�F�b�N����
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