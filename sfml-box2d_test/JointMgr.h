#pragma once
#include "stdafx.h"
#include "TextOnScreen.h"

struct wrapper
{
	virtual std::string operator()(const std::string& s)
	{
		return s;
	}
};
struct fullname : public wrapper
{
	virtual std::string operator()(const std::string& s) override
	{
		return "The " + s + " key";
	}
};
struct surround_with_brackets : public wrapper
{
	virtual std::string operator()(const std::string& s) override
	{
		return "( " + s + " )";
	}
};
std::string nameOf(sf::Keyboard::Key k, wrapper& w  = wrapper())
{
	std::string name = "unknown";
	
	switch (k)
	{
	case Keyboard::A:
		name = "a";
		break;
	case Keyboard::B:
		name = "b";
		break;            ///< The B key
	case Keyboard::C:
		name = "c";
		break;            ///< The C key
	case Keyboard::D:
		name = "d";
		break;            ///< The D key
	case Keyboard::E:
		name = "e";
		break;            ///< The E key
	case Keyboard::F:
		name = "f";
		break;            ///< The F key
	case Keyboard::G:
		name = "g";
		break;            ///< The G key
	case Keyboard::H:
		name = "h";
		break;            ///< The H key
	case Keyboard::I:
		name = "i";
		break;            ///< The I key
	case Keyboard::J:
		name = "j";
		break;            ///< The J key
	case Keyboard::K:
		name = "k";
		break;            ///< The K key
	case Keyboard::L:
		name = "l";
		break;            ///< The L key
	case Keyboard::M:
		name = "m";
		break;            ///< The M key
	case Keyboard::N:
		name = "n";
		break;            ///< The N key
	case Keyboard::O:
		name = "o";
		break;            ///< The O key
	case Keyboard::P:
		name = "p";
		break;            ///< The P key
	case Keyboard::Q:
		name = "q";
		break;            ///< The Q key
	case Keyboard::R:
		name = "r";
		break;            ///< The R key
	case Keyboard::S:
		name = "s";
		break;            ///< The S key
	case Keyboard::T:
		name = "t";
		break;            ///< The T key
	case Keyboard::U:
		name = "u";
		break;            ///< The U key
	case Keyboard::V:
		name = "v";
		break;            ///< The V key
	case Keyboard::W:
		name = "w";
		break;            ///< The W key
	case Keyboard::X:
		name = "x";
		break;            ///< The X key
	case Keyboard::Y:
		name = "y";
		break;            ///< The Y key
	case Keyboard::Z:
		name = "z";
		break;            ///< The Z key
	case Keyboard::Num0:
		name = "0";
		break;         ///< The 0 key
	case Keyboard::Num1:
		name = "1";
		break;         ///< The 1 key
	case Keyboard::Num2:
		name = "2";
		break;         ///< The 2 key
	case Keyboard::Num3:
		name = "3";
		break;         ///< The 3 key
	case Keyboard::Num4:
		name = "4";
		break;         ///< The 4 key
	case Keyboard::Num5:
		name = "5";
		break;         ///< The 5 key
	case Keyboard::Num6:
		name = "6";
		break;         ///< The 6 key
	case Keyboard::Num7:
		name = "7";
		break;         ///< The 7 key
	case Keyboard::Num8:
		name = "8";
		break;         ///< The 8 key
	case Keyboard::Num9:
		name = "9";
		break;         ///< The 9 key
	case Keyboard::Escape:
		name = "Escape";
		break;       ///< The Escape key
	case Keyboard::LControl:
		name = "left Control";
		break;     ///< The left Control key
	case Keyboard::LShift:
		name = "left Shift";
		break;       ///< The left Shift key
	case Keyboard::LAlt:
		name = "left Alt";
		break;         ///< The left Alt key
	case Keyboard::LSystem:
		name = "left System (Window)";
		break;      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
	case Keyboard::RControl:
		name = "right Control";
		break;     ///< The right Control key
	case Keyboard::RShift:
		name = "right Shift";
		break;       ///< The right Shift key
	case Keyboard::RAlt:
		name = "right Alt";
		break;         ///< The right Alt key
	case Keyboard::RSystem:
		name = "right System";
		break;      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
	case Keyboard::Menu:
		name = "Menu";
		break;         ///< The Menu key
	case Keyboard::LBracket:
		name = "[";
		break;     ///< The [ key
	case Keyboard::RBracket:
		name = "]";
		break;     ///< The ] key
	case Keyboard::SemiColon:
		name = ";";
		break;    ///< The ; key
	case Keyboard::Comma:
		name = ",";
		break;        ///< The , key
	case Keyboard::Period:
		name = ".";
		break;       ///< The . key
	case Keyboard::Quote:
		name = "'";
		break;        ///< The ' key
	case Keyboard::Slash:
		name = "/";
		break;        ///< The / key
	case Keyboard::BackSlash:
		name = "\\";
		break;    ///< The \ key
	case Keyboard::Tilde:
		name = "~";
		break;        ///< The ~ key
	case Keyboard::Equal:
		name = "=";
		break;        ///< The = key
	case Keyboard::Dash:
		name = "-";
		break;         ///< The - key
	case Keyboard::Space:
		name = "Space";
		break;        ///< The Space key
	case Keyboard::Return:
		name = "Enter";
		break;       ///< The Return key
	case Keyboard::BackSpace:
		name = "Backspace";
		break;    ///< The Backspace key
	case Keyboard::Tab:
		name = "Tabulation";
		break;          ///< The Tabulation key
	case Keyboard::PageUp:
		name = "Page up";
		break;       ///< The Page up key
	case Keyboard::PageDown:
		name = "Page down";
		break;     ///< The Page down key
	case Keyboard::End:
		name = "End";
		break;          ///< The End key
	case Keyboard::Home:
		name = "Home";
		break;         ///< The Home key
	case Keyboard::Insert:
		name = "Insert";
		break;       ///< The Insert key
	case Keyboard::Delete:
		name = "Delete";
		break;       ///< The Delete key
	case Keyboard::Add:
		name = "+";
		break;          ///< The + key
	case Keyboard::Subtract:
		name = "-";
		break;     ///< The - key
	case Keyboard::Multiply:
		name = "*";
		break;     ///< The * key
	case Keyboard::Divide:
		name = "/";
		break;       ///< The / key
	case Keyboard::Left:
		name = "Left arrow";
		break;         ///< Left arrow
	case Keyboard::Right:
		name = "Right arrow";
		break;        ///< Right arrow
	case Keyboard::Up:
		name = "Up arrow";
		break;           ///< Up arrow
	case Keyboard::Down:
		name = "Down arrow";
		break;         ///< Down arrow
	case Keyboard::Numpad0:
		name = "numpad 0";
		break;      ///< The numpad 0 key
	case Keyboard::Numpad1:
		name = "numpad 1";
		break;      ///< The numpad 1 key
	case Keyboard::Numpad2:
		name = "numpad 2";
		break;      ///< The numpad 2 key
	case Keyboard::Numpad3:
		name = "numpad 3";
		break;      ///< The numpad 3 key
	case Keyboard::Numpad4:
		name = "numpad 4";
		break;      ///< The numpad 4 key
	case Keyboard::Numpad5:
		name = "numpad 5";
		break;      ///< The numpad 5 key
	case Keyboard::Numpad6:
		name = "numpad 6";
		break;      ///< The numpad 6 key
	case Keyboard::Numpad7:
		name = "numpad 7";
		break;      ///< The numpad 7 key
	case Keyboard::Numpad8:
		name = "numpad 8";
		break;      ///< The numpad 8 key
	case Keyboard::Numpad9:
		name = "numpad 9";
		break;      ///< The numpad 9 key
	case Keyboard::F1:
		name = "F1";
		break;           ///< The F1 key
	case Keyboard::F2:
		name = "F2";
		break;           ///< The F2 key
	case Keyboard::F3:
		name = "F3";
		break;           ///< The F3 key
	case Keyboard::F4:
		name = "F4";
		break;           ///< The F4 key
	case Keyboard::F5:
		name = "F5";
		break;           ///< The F5 key
	case Keyboard::F6:
		name = "F6";
		break;           ///< The F6 key
	case Keyboard::F7:
		name = "F7";
		break;           ///< The F7 key
	case Keyboard::F8:
		name = "F8";
		break;           ///< The F8 key
	case Keyboard::F9:
		name = "F9";
		break;           ///< The F9 key
	case Keyboard::F10:
		name = "F10";
		break;          ///< The F10 key
	case Keyboard::F11:
		name = "F11";
		break;          ///< The F11 key
	case Keyboard::F12:
		name = "F12";
		break;          ///< The F12 key
	case Keyboard::F13:
		name = "F13";
		break;          ///< The F13 key
	case Keyboard::F14:
		name = "F14";
		break;          ///< The F14 key
	case Keyboard::F15:
		name = "F15";
		break;          ///< The F15 key
	case Keyboard::Pause:
		name = "Pause";
		break;        ///< The Pause key
	default:
		assert(false);
		break;
	}
	return w(name);
}

//////////////////////////////////////////////////////////////////////////

class Control
{
public:
	Control(const char* _name): name(_name){}

	struct Listener
	{
		std::function<void()> f = nullptr;

		using infofunc = std::function<std::string()>;
		static infofunc infostr(const char* s) {
			return [s]()->std::string {return s; };
		}
		infofunc info = infostr("...");
	};
	void setOnKeyListener(sf::Keyboard::Key k, Listener& l)
	{
		ls[k] = l;
	}

	std::string getListenersInfo() const
	{
		std::stringstream ss;
		for each (auto l in ls)
		{
			ss << "press " << nameOf(l.first, surround_with_brackets())
				<< " to " << l.second.info()
				<< std::endl;
		}
		return ss.str();
	}

	virtual bool execute(sf::Keyboard::Key k)
	{
		auto l = ls.find(k);
		if (l == ls.end())
			return false;

		l->second.f();
		return true;
	}

	virtual std::string getInfo() const = 0;

protected:
	std::map<sf::Keyboard::Key, Listener> ls;
	std::string name;
};

//////////////////////////////////////////////////////////////////////////

inline std::ostream& operator <<(std::ostream& os, b2Vec2 v)
{
	static char buf[100] = { '\0' };
	memset(buf, '\0', sizeof(buf));
	sprintf_s(buf, sizeof(buf), "[%3.2f, %2.2f]", v.x, v.y);
	os << buf;
	/*os.precision(2);
	os << std::left << "[" << v.x << ", " << v.y << "]" << std::setw(10);*/
	
	return os;
}

//////////////////////////////////////////////////////////////////////////

template<typename T>
class VarControl : public Control
{
public:
	VarControl(const char* _name) : Control(_name) {}

	using GetValCallback = std::function<T()>;
	void setGetValCallback(GetValCallback f)
	{
		assert(f);
		getVal = f;
	}

	using SetValCallback = std::function<void(T)>;
	void setUpdateCallback(SetValCallback f)
	{
		assert(f);
		setVal = f;
	}

	virtual std::string getInfo() const override
	{
		std::stringstream ss;
		ss.precision(2);
		ss << std::setw(6) << std::fixed;
		ss << name << " = " << getVal() << std::endl;
		
		ss << getListenersInfo();

		return ss.str();
	}

protected:
	GetValCallback getVal = nullptr;
	SetValCallback setVal = nullptr;
};

//////////////////////////////////////////////////////////////////////////

//class BoolControl : public Control
//{
//public:
//	BoolControl(const char* _name) : Control(_name) {}
//
//	using EnableCallback = std::function<void()>;
//	void setEnableCallback(EnableCallback f)
//	{
//		enable = f;
//	}
//
//	using IsEnabledCallback = std::function<bool(void)>;
//	void setIsEnabledCallback(IsEnabledCallback f)
//	{
//		isEnabled = f;
//	}
//
//	void assignEnableKey(sf::Keyboard::Key k)
//	{
//	actionKey = k;
//	}
//	virtual std::string getInfo() override
//	{
//	std::stringstream ss;
//	ss << name << " is " << (isEnabled()? "enabled" : "disabled") << std::endl;
//
//	if (actionKey != Keyboard::Key::Unknown)
//	{
//	ss << "press " << nameOf(actionKey, surround_with_brackets())
//	<< " to " << (isEnabled() ? "disable" : "enable") << std::endl;
//	}
//	return ss.str();
//	}
//	virtual bool execute(sf::Keyboard::Key k) override
//	{
//	if (k == actionKey)
//	{
//	enable();
//	return true;
//	}
//	return false;
//	}
//
//private:
//	EnableCallback enable = nullptr;
//	IsEnabledCallback isEnabled = nullptr;
//	sf::Keyboard::Key actionKey = Keyboard::Unknown;
//};

class EnabledControl: public VarControl<bool>
{
public:
	EnabledControl(const char* _name): VarControl(_name){}

	void assignEnableKey(sf::Keyboard::Key k)
	{
		Listener l;
		l.f = [this]() { setVal(!getVal()); };
		l.info = [this]()->auto{return getVal() ? "disable" : "enable"; };
		setOnKeyListener(k, l);
	}
	virtual std::string getInfo() const override
	{
		std::stringstream ss;
		ss << name << " is " << (getVal() ? "enabled" : "disabled") << std::endl;

		ss << getListenersInfo();
		
		return ss.str();
	}
};

//////////////////////////////////////////////////////////////////////////

namespace cmd
{
	enum Type {
		Increase, Decrease, Max, Min, Reset, Inverse, _commandCount_
	};
}

class RangeControl : public VarControl<float>
{
public:
	RangeControl(const char* _name) : VarControl(_name) {}
	
	void assignKey(cmd::Type c, sf::Keyboard::Key k)
	{
		Listener l;
		
		switch (c)
		{
		case cmd::Increase:
			l.f = [this]() {increase(); };
			l.info = Listener::infostr("Increase");
			break;
		case cmd::Decrease:
			l.f = [this]() {decrease(); };
			l.info = Listener::infostr("Decrease");
			break;
		case cmd::Max:
			l.f = [this]() {max(); };
			l.info = Listener::infostr("Max");
			break;
		case cmd::Min:
			l.f = [this]() {min(); };
			l.info = Listener::infostr("Min");
			break;
		case cmd::Reset:
			l.f = [this]() {reset(); };
			l.info = Listener::infostr("Reset");
			break;
		case cmd::Inverse:
			l.f = [this]() {inverse(); };
			l.info = Listener::infostr("Inverse");
			break;
		default:
			assert(false);
		}
		ls[k] = l;
	}

	void setGetValCallback(GetValCallback f)
	{
		VarControl::setGetValCallback(f);
		
		default = getVal();
	}
	void setRange(float _min, float _max)
	{
		assert(min_ <= max_);
		min_ = _min;
		max_ = _max;
	}
	void setDelta(float _delta)
	{
		delta = _delta;
	}

private:
	void reset()
	{
		setVal(default);
	}
	void inverse()
	{
		const float val = getVal();
		const float inv = val > 0 ? std::min(min_, -val) : std::max(max_, -val);
		setVal(inv);
	}
	void increase()
	{
		setVal( std::min(getVal() + delta, max_));
	}
	void decrease()
	{
		setVal(std::max(getVal() - delta, min_));
	}
	void min()
	{
		setVal(min_);
	}
	void max()
	{
		setVal(max_);
	}

private:
	float min_ = 0.f;
	float max_ = 100'000.f;
	float delta = 1.f;
	float default;
};
//class FloatControl: public Control
//{
//public:
//	FloatControl(const char* _name): Control(_name) {}
//	
//	using AssignKey = const std::function<void(sf::Keyboard::Key)>;
//	void assignKey(cmd::Type c, sf::Keyboard::Key k)
//	{
//		Listener l;
//
//		switch (c)
//		{
//		case cmd::Increase:
//			l.callback = &FloatControl::increase;
//			l.cmd.name = "Increase";
//			break;
//		case cmd::Decrease:
//			l.callback = &FloatControl::decrease;
//			l.cmd.name = "Decrease";
//			break;
//		case cmd::Max:
//			l.callback = &FloatControl::max;
//			l.cmd.name = "Max";
//			break;
//		case cmd::Min:
//			l.callback = &FloatControl::min;
//			l.cmd.name = "Min";
//			break;
//		case cmd::Reset:
//			l.callback = &FloatControl::reset;
//			l.cmd.name = "Reset";
//			break;
//		case cmd::Inverse:
//			l.callback = &FloatControl::inverse;
//			l.cmd.name = "Inverse";
//			break;
//		default:
//			assert(false);
//		}
//		l.cmd.type = c;
//		listeners[k] = l;
//	}
//
//	using SetValCallback = std::function<void(float)>;
//	void setUpdateCallback(SetValCallback f)
//	{
//		assert(f);
//		setVal = f;
//	}
//
//	using GetValCallback = std::function<float(void)>;
//	void setGetValCallback(GetValCallback f)
//	{
//		assert(f);
//		getVal = f;
//		
//		default = getVal();
//		val = default;
//	}
//
//	virtual std::string getInfo() const override
//	{
//		assert(getVal);
//
//		std::stringstream ss;
//		ss << name << " = " << getVal() << std::endl;
//
//		for each (auto i in listeners)
//		{
//			ss << "press " << nameOf(i.first, surround_with_brackets()) 
//				<< " to " << i.second.cmd.name << std::endl;
//		}
//		return ss.str();
//	}
//	virtual bool execute(sf::Keyboard::Key k) override
//	{
//		auto itr = listeners.find(k);
//		if (itr == listeners.end())
//			return false;
//
//		(this->*(itr->second.callback))();
//
//		assert(setVal);
//		setVal(val);
//
//		return true;
//	}
//
//	void setRange(float _min, float _max)
//	{
//		assert(min_ <= max_);
//		min_ = _min;
//		max_ = _max;
//	}
//	void setDelta(float _delta) 
//	{
//		delta = _delta;
//	}
//
//	
//	
//
//private:
//	void reset()
//	{
//		val = default;
//	}
//	void inverse()
//	{
//		val = val > 0 ? std::min(min_, -val) : std::max(max_, -val);
//	}
//	void increase()
//	{
//		val = std::min(val + delta, max_);
//	}
//	void decrease()
//	{
//		val = std::max(val - delta, min_);
//	}
//	void min()
//	{
//		val = min_;
//	}
//	void max()
//	{
//		val = max_;
//	}
//
//private:
//	float min_ = 0.f;
//	float max_ = 100'000.f;
//	float delta = 1.f;
//	float default;
//	float val;
//
//	SetValCallback setVal = nullptr;
//	GetValCallback getVal = nullptr;
//
//	typedef void(FloatControl::*CmdCallback)();
//
//	struct Listener {
//		CmdCallback callback;
//		
//		struct {
//			cmd::Type type;
//			std::string name;
//		} cmd;
//	};
//	std::map<sf::Keyboard::Key, Listener> listeners;
//};

//////////////////////////////////////////////////////////////////////////
class JointControlMgr;

class JointControl
{
public:
	JointControl(const std::string& _name, const std::string& _typename)
		: jname(_name + " ( " + _typename + " )") {}

	virtual void update(sf::Keyboard::Key pressed)
	{
		for each (auto i in ctrls)
			i->execute(pressed);
	}
	std::string getInfo()
	{
		std::stringstream ss;
		ss << jname << std::endl;

		for each (auto i in ctrls)
			ss << i->getInfo() << std::endl;

		return ss.str();
	}
protected:
	void addControl(Control& c)
	{
		ctrls.push_back(&c);
	}

protected:
	std::string jname;
	std::vector<Control*> ctrls;

	JointControlMgr* mgr = nullptr;
	friend class JointControlMgr;
};

class JointControlMgr : public sf::Drawable
{
public:
	JointControlMgr(const sf::RenderTarget& rt, int viewportRatio = 4, sf::Font& f = g_font)
	{
		sf::FloatRect viewBounds(0, 0, float(rt.getSize().x) / viewportRatio, float(rt.getSize().y));
		v.reset(viewBounds);
		v.setViewport({ 0, 0, 1.f / viewportRatio, 1.f });
		t.options.gameField = FloatRect(v.getCenter() - v.getSize() / 2.f, v.getSize());
		t.options.font = f;

		viewField.setPointCount(4);
		viewField.setPoint(0, { viewBounds.left, viewBounds.top });
		viewField.setPoint(1, { viewBounds.left, viewBounds.top + viewBounds.height });
		viewField.setPoint(2, { viewBounds.left + viewBounds.width, viewBounds.top + viewBounds.height });
		viewField.setPoint(3, { viewBounds.left + viewBounds.width, viewBounds.top });
		viewField.setFillColor({ 0,0,255,50 });
		
	}
	
	void add(JointControl& jc)
	{
		jc.mgr = this;

		jcs.push_back(&jc);
		
		updateInfo();
		//ss << jc.getInfo() << std::endl;
	}
	void update(const Event& event)
	{
		if (event.type == Event::KeyPressed)
		{ 
			for each (auto jc in jcs)
			{
				jc->update(event.key.code);
			}
			updateInfo();
		}
		/*t.create(ss.str(), base::Size::FIT);
		t.setPositionOnScreen(base::Position::LEFT | base::Position::TOP);*/
	}
	void updateInfo()
	{
		ss.str("");
		ss.clear();

		for each (auto jc in jcs)
		{
			ss << jc->getInfo() << std::endl;
		}
		t.create(ss.str(), base::Size::FIT);
		t.setPositionOnScreen(base::Position::LEFT | base::Position::TOP);
	}

protected:
	virtual void draw(RenderTarget& target, RenderStates states) const override
	{
		assert(t.options.font.getInfo().family.length());
		sf::View activeView = target.getView();
		target.setView(v);
		target.draw(viewField);
		target.draw(tf);
		target.draw(t);
		target.setView(activeView);
	}

private:
	sf::View v;
	sf::ConvexShape tf;
	sf::ConvexShape viewField;
	base::TextOnScreen t;
	std::vector<JointControl*> jcs;
	std::stringstream ss;
};

//////////////////////////////////////////////////////////////////////////

class PrismaticJointControl: public JointControl
{
	b2PrismaticJoint* j;

public:
	EnabledControl limit = "Limit";
	EnabledControl motor = "Motor";
	RangeControl speed = "Speed";
	RangeControl force = "MaxForce";

public:
	PrismaticJointControl(b2PrismaticJoint* _j, const std::string& _name)
		: JointControl(_name, "Prismatic joint")
		, j(_j)
	{
		limit.setUpdateCallback([this](auto v) {j->EnableLimit(v); });
		limit.setGetValCallback([this]() -> bool {return j->IsLimitEnabled(); });
		addControl(limit);

		motor.setUpdateCallback([this](auto v) {j->EnableMotor(v); });
		motor.setGetValCallback([this]()->auto{return j->IsMotorEnabled(); });
		addControl(motor);

		auto setSpeed = [this](auto s) {j->SetMotorSpeed(s); };
		speed.setUpdateCallback(setSpeed);
		speed.setGetValCallback([this]()->auto{return j->GetMotorSpeed(); });
		speed.setDelta(1);
		speed.setRange(-50, 50);
		addControl(speed);

		auto setForce = [this](auto f) {j->SetMaxMotorForce(f); };
		force.setUpdateCallback(setForce);
		force.setGetValCallback([this]()->auto{return j->GetMaxMotorForce(); });
		force.setDelta(100);
		force.setRange(-100'000, 100'000);
		addControl(force);
	}
};


class WheelJointControl : public JointControl
{
	b2WheelJoint* j = nullptr;

public:
	EnabledControl motor = "Motor";
	RangeControl torque = "Torque";
	RangeControl speed = "Speed";
	RangeControl damping = "Damping Ratio";
	RangeControl freq = "Frequency";

public:
	WheelJointControl(b2WheelJoint* _j, std::string _name)
		: JointControl(_name, "WheelJoint")
		, j(_j)
	{
		motor.setUpdateCallback([this](auto v) { j->EnableMotor(v); });
		motor.setGetValCallback([this]()->auto{return j->IsMotorEnabled(); });
		addControl(motor);

		auto setTorq = [this](auto v) { j->SetMaxMotorTorque(v); };
		torque.setUpdateCallback(setTorq);
		torque.setGetValCallback([this]()->auto{return j->GetMaxMotorTorque(); });
		torque.setDelta(10);
		torque.setRange(-100'000, 100'000);
		addControl(torque);

		auto setSpeed = [this](auto v) { j->SetMotorSpeed(v); };
		speed.setUpdateCallback(setSpeed);
		speed.setGetValCallback([this]()->auto{return j->GetMotorSpeed(); });
		speed.setDelta(1);
		speed.setRange(-50, 50);
		addControl(speed);

		auto setDamping = [this](auto v) { j->SetSpringDampingRatio(v); };
		damping.setUpdateCallback(setDamping);
		damping.setGetValCallback([this]()->auto{return j->GetSpringDampingRatio(); });
		damping.setDelta(1);
		damping.setRange(0, 10);
		addControl(damping);

		auto setFreq = [this](auto v) { j->SetSpringFrequencyHz(v); };
		freq.setUpdateCallback(setFreq);
		freq.setGetValCallback([this]()->auto{return j->GetSpringFrequencyHz(); });
		freq.setDelta(0.1);
		freq.setRange(0, 2);
		addControl(freq);
	}
};


class WeldJointsControl : public JointControl
{
	std::vector<b2WeldJoint*> js;
public:
	RangeControl damping = "Damping Ratio";
	RangeControl freq = "Frequency";
public:
	WeldJointsControl(std::string _groupName)
		: JointControl(_groupName, "WeldJoints")
	{
		auto setDamping = [this](auto v) {
			for each (auto j in js)
				j->SetDampingRatio(v); 
		};
		damping.setUpdateCallback(setDamping);
		damping.setGetValCallback([this]()->auto{return js[0]->GetDampingRatio(); });
		damping.setDelta(1);
		damping.setRange(0, 10);
		addControl(damping);

		auto setFreq = [this](auto v) { 
			for each (auto j in js)
				j->SetFrequency(v); 
		};
		freq.setUpdateCallback(setFreq);
		freq.setGetValCallback([this]()->auto{return js[0]->GetFrequency(); });
		freq.setDelta(0.1);
		freq.setRange(0, 100.f);
		addControl(freq);
	}
	void add(b2WeldJoint* j)
	{
		js.push_back(j);
	}
};


class RopeJointControl : public JointControl
{
	b2RopeJoint* j = nullptr;
public:
	RangeControl len = "Length";

public:
	RopeJointControl(b2RopeJoint* _j, const char* _name)
		: JointControl(_name, "RopeJoint")
		, j(_j)
	{
		len.setUpdateCallback([this](auto v) {j->SetMaxLength(v); });
		len.setGetValCallback([this]()->auto{return j->GetMaxLength(); });
		len.setRange(0, 30);
		addControl(len);
	}
};


class MotorJointControl : public JointControl, public sf::Drawable
{
	b2MotorJoint* j = nullptr;
	VarControl<b2Vec2> linearOffset = "LinearOffset";
	VarControl<float> angularOffset = "AngularOffset";
public:
	RangeControl force = "Force";
	RangeControl torque = "Torque";
	
public:
	MotorJointControl(b2MotorJoint* _j, const char* _name)
		: JointControl(_name, "MotorJoint")
		, j(_j)
	{
		linearOffset.setUpdateCallback([this](auto v) {j->SetLinearOffset(v); });
		linearOffset.setGetValCallback([this]()->auto{return j->GetLinearOffset(); });
		addControl(linearOffset);

		angularOffset.setUpdateCallback([this](auto v) {j->SetAngularOffset(v); });
		angularOffset.setGetValCallback([this]()->auto{return j->GetAngularOffset(); });
		addControl(angularOffset);

		force.setUpdateCallback([this](auto v) {j->SetMaxForce(v); });
		force.setGetValCallback([this]()->auto{return j->GetMaxForce(); });
		addControl(force);

		torque.setUpdateCallback([this](auto v) {j->SetMaxForce(v); });
		torque.setGetValCallback([this]()->auto{return j->GetMaxTorque(); });
		addControl(torque);

		pt.setRadius(0.2f);
		pt.setOrigin(pt.getRadius(), pt.getRadius());
		pt.setFillColor(sf::Color::Blue);
	}
	void assignRunKey(sf::Keyboard::Key k)
	{
		Control::Listener l;
		l.f = [this]() mutable {
			go = !go;
			if (go)
			{
				pt.setFillColor(sf::Color::Blue);
				timer.restart();
			}
			else
			{
				pt.setFillColor(sf::Color::Transparent);
			}
		};
		l.info = [this]()->auto { return go ? "stop" : "run"; };
		linearOffset.setOnKeyListener(k, l);
	}
	void run(sf::Vector2f& center)
	{
		if (go)
		{
			float t = timer.getElapsedTime().asSeconds();
			b2Vec2 p = { 6 * sin(2.f*t), 20 + 4 * sin(t) };
			j->SetLinearOffset(p);
			j->SetAngularOffset(t);

			mgr->updateInfo();

			pt.setPosition(box2dToSfml(p, center));
		}
	}

protected:
	virtual void draw(RenderTarget& target, RenderStates states) const override
	{
		target.draw(pt);
	}

private:
	bool go = false;
	sf::Clock timer;
	sf::CircleShape pt;
};