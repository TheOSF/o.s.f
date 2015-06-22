#pragma once

#include "NonCopyable.h"


/**
* シングルトン基底クラス
* 継承することでSingleton化します。

* 例
* class Hoge : public cSingleton<Hoge>
* {
* private:
*    Hoge();
*    ~Hoge();
* };

* ※ 使う前に StartUp() 、使い終わった後に ShutDown() 関数を呼んでください！

*/
template<class _Ty>
class cSingleton
	:private cNonCopyable
{
public:
	typedef typename _Ty InstanceType;

private:
	static InstanceType*  instance_;         // インスタンス
	bool                           is_initialized_;  // 初期化済みフラグ

protected:
	inline cSingleton() :is_initialized_(false){}  // コンストラクタ
	inline virtual~cSingleton(){}                       // デストラクタ

public:

	/**
	* インスタンスを取得します。
	*/
	inline static InstanceType& GetInstance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new InstanceType();
		}

		return *instance_;
	}


	/**
	* インスタンス解放します。
	*/
	inline static void ReleaseInstance()
	{

		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

	/**
	* 利用開始します。
	*/
	bool StartUp()
	{
		// 既に初期化済み
		if (is_initialized_ == true)
		{
			return false;
		}

		if (Initialize() == false)
		{
			return false;
		}

		is_initialized_ = true;
		return true;
	}


	/**
	* 利用終了します。
	*/
	bool ShutDown(bool release_instance = false)
	{
		// 既に解放済み
		if (is_initialized_ == false)
		{
			return false;
		}

		// 解放処理
		if (Release() == false)
		{
			return false;
		}

		is_initialized_ = false;

		// インスタンス解放
		if (release_instance == true)
		{
			ReleaseInstance();
		}

		return true;
	}


protected:
	/**
	* 初期化します。
	*/
	virtual bool Initialize() = 0;
	
	/**
	* 解放します。
	*/
	virtual bool Release() = 0;

};

// インスタンス
template<class _Ty> 
typename cSingleton<_Ty>::InstanceType* cSingleton<_Ty>::instance_ = nullptr;





// EOF