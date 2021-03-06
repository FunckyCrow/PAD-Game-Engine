// EventSystem.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>

#include <System/Event/IObserver.h>
#include <System/Event/EventHandler.h>

class DerivedObserver final : public pad::sys::evnt::IObserver
{
public:
	DerivedObserver(const std::string& _name) : 
		m_name(_name)
	{
	}
	~DerivedObserver() = default;

private:
	std::string m_name;

public:
	void Update(pad::sys::evnt::Subject* const _sender, pad::sys::evnt::EventArgs* const _args) override
	{
		std::cout << m_name << " got notified." << std::endl;
	}
};

void ScreamMyName(const std::string& _name)
{
	std::cout << "MY NAME IS " << _name << "!!!" << std::endl;
}

int main()
{
	pad::sys::evnt::Subject s;
	DerivedObserver t1("1"), t2("2"), t3("3");

	s.AddObserver(&t1);
	s.AddObserver(&t2);
	s.AddObserver(&t3);

	s.Notify(&pad::sys::evnt::EventArgs());

	s.RemoveObserver(&t2);

	s.Notify(&pad::sys::evnt::EventArgs());

	std::function<void()> test = std::bind(ScreamMyName, std::string("NOTHING TO BE ASHAMED OF!"));

	pad::sys::evnt::EventHandler eh(test);

	eh.Invoke();

	eh();

	eh = test;

	eh();

    return 0;
}

