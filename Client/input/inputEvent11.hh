//#include ""

#ifndef _CF_INPUT_EVENT_DEF_H_
#define _CF_INPUT_EVENT_DEF_H_

#include "../common/vec2.h"

namespace CF
{
	namespace Input
	{
		enum EventType
		{
			MouseDown,
			MouseUp,
			MouseWheel,
			MouseMove,
			KeyDown,
			KeyUp,
			JoystickButton,
			JoystickAxis,
		};

		class Event
		{
		public:
			Event(){}
			Event(EventType tp , int tm)
				:m_eType(tp),m_time(tm){}
			
			EventType	GetType() { return	m_eType ; }
			int GetTm()	{ return m_time ; }
		protected:
			EventType		m_eType;
			int				m_time;
		};

		class MouseDownEvent : public Event
		{
		public:
			MouseDownEvent(){}
			void Set( int ky , float x , float y ,int flg)
			{
				m_key = ky;
				m_flg = flg;
				m_pos.Set(x, y);
			}

			void Set(int ky, const CFMath::Vec2f& p, int flg)
			{
				m_key = ky;
				m_flg = flg;
				m_pos = p;
			}

			int Key()	{ return m_key ; }
			const CFMath::Vec2f& Pos()	{ return m_pos; }
			int Flag()	{ return m_flg; }
		protected:
			int			m_key;
			int			m_flg;
			CFMath::Vec2f	m_pos;
		};

		typedef MouseDownEvent MouseUpEvent;

		class MouseMoveEvent : public Event
		{
		public:
			MouseMoveEvent(){}
			void Set( float x, float y , int flg )
			{
				m_flg = flg;
				m_pos.Set(x, y);
			}

			void Set(int ky, const CFMath::Vec2f& p , int flg)
			{
				m_flg = flg;
				m_pos = p;
			}

			int Flag()	{ return m_flg ; }
			const CFMath::Vec2f& Pos()	{ return m_pos ; }
		protected:
			int					m_flg ;
			CFMath::Vec2f	m_pos ;
		};

		class MouseWheelEvent : public Event
		{
		public:
			MouseWheelEvent(){}
			void Set(float x, float y, int delta , int flg)
			{
				m_flg = flg;
				m_delta = delta;
				m_pos.Set(x, y);
			}

			void Set(int ky, const CFMath::Vec2f& p, int delta, int flg)
			{
				m_flg = flg;
				m_delta = delta;
				m_pos = p;
			}

			int Flag()	{ return m_flg; }
			int Delta()	{ return m_delta; }
			const CFMath::Vec2f& Pos()	{ return m_pos; }
		protected:
			int					m_flg;
			int					m_delta;
			CFMath::Vec2f	m_pos;
		};
	}
}

#endif