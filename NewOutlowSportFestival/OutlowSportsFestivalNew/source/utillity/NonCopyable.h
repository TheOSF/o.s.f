#pragma once


/**
* �p�����邱�ƂŃR�s�[���֎~���܂�

* ��
* class Hoge : private cNonCopyable
* {
* };

* warning!! : private�Ōp�����Ă��������I
*/
class cNonCopyable
{
protected:
	cNonCopyable(){};
	virtual~cNonCopyable(){};
private:
	cNonCopyable(const cNonCopyable& src);
	cNonCopyable& operator = (const cNonCopyable& src);
};


// EOF