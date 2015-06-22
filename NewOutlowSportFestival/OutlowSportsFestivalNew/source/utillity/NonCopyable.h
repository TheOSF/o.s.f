#pragma once


/**
* 継承することでコピーを禁止します

* 例
* class Hoge : private cNonCopyable
* {
* };

* warning!! : privateで継承してください！
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