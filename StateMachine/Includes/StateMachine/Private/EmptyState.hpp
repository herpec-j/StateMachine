#pragma once

#include "StateMachine/State.hpp"
#include "StateMachine/Private/Singleton.hpp"

namespace AO
{
	namespace StateMachine
	{
		namespace Private
		{
			template <class Entity, typename... Args>
			class EmptyState final : public State<Entity, Args...>, public Singleton < EmptyState<Entity, Args...> >
			{
				friend typename Singleton<EmptyState<Entity, Args...>>::Access;

			public:
				using EntityType = typename State<Entity, Args...>::EntityType;

				using EntityPtr = typename State<Entity, Args...>::EntityPtr;

				using ConstEntityPtr = typename State<Entity, Args...>::ConstEntityPtr;

				// Destructor
				~EmptyState(void) = default;

			private:
				// Constructors
				EmptyState(void) = default;

				EmptyState(const EmptyState &) = default;

				// Assignment operators
				EmptyState &operator=(const EmptyState &) = default;

				// Inherited Methods
				void enter(EntityPtr entity) override final
				{
					return;
				}

				void execute(EntityPtr entity, Args... args) override final
				{
					return;
				}

				void exit(EntityPtr entity) override final
				{
					return;
				}
			};
		}
	}
}
