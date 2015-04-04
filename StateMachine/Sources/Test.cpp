#include <iostream>

#include "StateMachine/StateMachine.hpp"
#include "StateMachine/State.hpp"

struct Machine : public AO::StateMachine::StateMachine < Machine, int >
{
	Machine(void)
		: StateMachine(this)
	{
		return;
	}
};

struct GlobalState1 : public Machine::StateType, public AO::StateMachine::Private::Singleton<GlobalState1>
{
	friend Access;

	virtual void enter(Machine::EntityPtr entity) override final
	{
		std::cout << "Entering GlobalState1..." << std::endl;
	}

	virtual void execute(Machine::EntityPtr entity, int data) override final;

	virtual void exit(Machine::EntityPtr entity) override final
	{
		std::cout << "Exiting GlobalState1..." << std::endl;
	}
};

struct GlobalState2 : public Machine::StateType, public AO::StateMachine::Private::Singleton<GlobalState2>
{
	friend Access;

	virtual void enter(Machine::EntityPtr entity) override final
	{
		std::cout << "Entering GlobalState2..." << std::endl;
	}

	virtual void execute(Machine::EntityPtr entity, int data) override final
	{
		std::cout << "Executing GlobalState2 (" << data << ")..." << std::endl;
		if (data % 7 == 0)
		{
			entity->changeGlobalState(GlobalState1::GetInstance());
			if (entity->numberOfStates() > 1)
			{
				entity->revertToPreviousState(entity->numberOfStates() - 1);
			}
		}
	}

	virtual void exit(Machine::EntityPtr entity) override final
	{
		std::cout << "Exiting GlobalState2..." << std::endl;
	}
};

void GlobalState1::execute(Machine::EntityPtr entity, int data)
{
	std::cout << "Executing GlobalState1 (" << data << ")..." << std::endl;
	if (data % 3 == 0)
	{
		entity->changeGlobalState(GlobalState2::GetInstance());
	}
}

struct NormalState3 : public Machine::StateType, public AO::StateMachine::Private::Singleton<NormalState3>
{
	friend Access;

	virtual void enter(Machine::EntityPtr entity) override final
	{
		std::cout << "Entering NormalState3..." << std::endl;
	}

	virtual void execute(Machine::EntityPtr entity, int data) override final
	{
		std::cout << "Executing NormalState3 (" << data << ")..." << std::endl;
		if (data % 6 == 0)
		{
			entity->revertToPreviousState(2);
		}
		else
		{
			entity->revertToPreviousState();
		}
	}

	virtual void exit(Machine::EntityPtr entity) override final
	{
		std::cout << "Exiting NormalState3..." << std::endl;
	}
};

struct NormalState2 : public Machine::StateType, public AO::StateMachine::Private::Singleton<NormalState2>
{
	friend Access;

	virtual void enter(Machine::EntityPtr entity) override final
	{
		std::cout << "Entering NormalState2..." << std::endl;
	}

	virtual void execute(Machine::EntityPtr entity, int data) override final
	{
		std::cout << "Executing NormalState2 (" << data << ")..." << std::endl;
		entity->addState<NormalState3>();
	}

	virtual void exit(Machine::EntityPtr entity) override final
	{
		std::cout << "Exiting NormalState2..." << std::endl;
	}
};

struct NormalState1 : public Machine::StateType, public AO::StateMachine::Private::Singleton<NormalState1>
{
	friend Access;

	virtual void enter(Machine::EntityPtr entity) override final
	{
		std::cout << "Entering NormalState1..." << std::endl;
	}

	virtual void execute(Machine::EntityPtr entity, int data) override final
	{
		std::cout << "Executing NormalState1 (" << data << ")..." << std::endl;
		entity->addState(NormalState2::GetInstance());
	}

	virtual void exit(Machine::EntityPtr entity) override final
	{
		std::cout << "Exiting NormalState1..." << std::endl;
	}
};

static void testStateMachine(void)
{
	Machine m;
	assert(m.isInState(Machine::EmptyState::GetInstance()) && m.isInState<Machine::EmptyState>());
	m.changeState(NormalState1::GetInstance());
	assert(!m.isInState(Machine::EmptyState::GetInstance()) && !m.isInState<Machine::EmptyState>());
	assert(m.isInState(NormalState1::GetInstance()) && m.isInState<NormalState1>());
	m.changeGlobalState<GlobalState1>();
	assert(m.isInGlobalState(GlobalState1::GetInstance()) && m.isInGlobalState<GlobalState1>());
	for (int i = 0; i < 20; ++i)
	{
		std::cout << "-----------------------" << std::endl;
		m.update(i);
	}
	std::cout << "Test State OK !" << std::endl;
}

int main(int, char *[])
{
	testStateMachine();
	std::cout << "Success!" << std::endl;
	return EXIT_SUCCESS;
}
