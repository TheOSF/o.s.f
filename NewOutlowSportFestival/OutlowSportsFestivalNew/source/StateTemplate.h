#ifndef __STATE_TEMPLATE_H__
#define __STATE_TEMPLATE_H__

//********************************************************
//		ステートマシン テンプレートクラス
//********************************************************

//bool より intのほうが高速?なため
typedef int BOOL;

//********************************************************
//		ステートクラス
//********************************************************
/*
	Enter関数はステート開始時
	Execute関数はステート実行時
	Exit関数はステート終了時
	に呼ばれる
*/
template <
	class _Client,
	class _ret_type=BOOL>
class State
{
public:
	typedef _Client*_Client_type_ptr;
	typedef _ret_type _Return_value_type;
public:
	virtual _Return_value_type Enter(_Client_type_ptr)
	{
		return 0;
	}
	virtual _Return_value_type Execute(_Client_type_ptr)
	{
		return 0;
	}
	virtual _Return_value_type Exit(_Client_type_ptr)
	{
		return 0;
	}
};
//********************************************************
//		ステートクラス特殊化ver(戻り値がvoidの場合)
//********************************************************
template <class _Client>
class State
<_Client,void>
{
public:
	typedef _Client*_Client_type_ptr;
public:
	virtual void Enter(_Client_type_ptr){}
	virtual void Execute(_Client_type_ptr){}
	virtual void Exit(_Client_type_ptr){}
};
//********************************************************
//		ステートマシンクラス
//********************************************************
/*
	set_state関数で現在のステートのExit関数を呼び出し、
	新たなステートをセットしEnter関数を呼び出す。

	state_execute関数で現在のステートのExecute関数を呼び出す。
	ステートが設定されていない場合は０を返す
*/
template <
	class _Client,
	class _ret_value=BOOL>
class StateMachine
{
public:
	typedef _Client*_Client_type_ptr;
	typedef _ret_value _Return_value_type;
	typedef State<_Client,_ret_value>*_MyState_ptr;
private:
	_Client_type_ptr		m_pClient;
	_MyState_ptr			m_pState;
	_MyState_ptr			m_pNextState;
public:
	StateMachine(_Client_type_ptr Client):
		m_pState(0),
		m_pNextState(0),
		m_pClient(Client)
	{
	}
	virtual~StateMachine()
	{
		if(m_pState)delete m_pState;
		if(m_pNextState)delete m_pNextState;
	}
public:
	void set_state(_MyState_ptr const Newstate)
	{
		if(m_pNextState)
			delete m_pNextState;
		m_pNextState=Newstate;
	}
	_Return_value_type state_execute()
	{
		if(m_pNextState){
			if(m_pState){
				m_pState->Exit(m_pClient);
				delete m_pState;
			}
			m_pNextState->Enter(m_pClient);
			m_pState=m_pNextState;
			m_pNextState=0;
		}
		if(m_pState)
			return m_pState->Execute(m_pClient);
		return 0;
	}
};
//********************************************************
//		ステートクラス特殊化ver(戻り値がvoidの場合)
//********************************************************
template <class _Client>
class StateMachine
	<_Client,void>
{
public:
	typedef _Client*_Client_type_ptr;
	typedef void _Return_value_type;
	typedef State<_Client,_Return_value_type>*_MyState_ptr;
private:
	_Client_type_ptr		m_pClient;
	_MyState_ptr			m_pState;
	_MyState_ptr			m_pNextState;
public:
	StateMachine(_Client_type_ptr Client):
		m_pState(0),
		m_pNextState(0),
		m_pClient(Client)
	{
	}
	virtual~StateMachine()
	{
		if(m_pState)delete m_pState;
		if(m_pNextState)delete m_pNextState;
	}
public:
	void set_state(_MyState_ptr const Newstate)
	{
		if(m_pNextState)
			delete m_pNextState;
		m_pNextState=Newstate;
	}
	_Return_value_type state_execute()
	{
		if(m_pNextState){
			if(m_pState){
				m_pState->Exit(m_pClient);
				delete m_pState;
			}
			m_pNextState->Enter(m_pClient);
			m_pState=m_pNextState;
			m_pNextState=0;
		}
		if(m_pState)
			return m_pState->Execute(m_pClient);
	}
};
#endif