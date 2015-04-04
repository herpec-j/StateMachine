#pragma once

#include "StateMachine/Private/Singleton.hpp"

namespace AO
{
	namespace StateMachine
	{
		template <class Entity, typename... Args>
		class StateMachine;

		template <class Entity, typename... Args>
		class State
		{
			friend class StateMachine<Entity, Args...>;

		public:
			using EntityType = Entity;

			using EntityPtr = EntityType *;

			using ConstEntityPtr = const EntityPtr;

			// Constructors
			State(void) = default;

			State(const State &) = delete;

			// Assignment operators
			State &operator=(const State &) = delete;

			// Destructor
			virtual ~State(void) = default;

		protected:
			// Methods
			virtual void enter(EntityPtr entity) = 0;

			virtual void execute(EntityPtr entity, Args... args) = 0;

			virtual void exit(EntityPtr entity) = 0;
		};

		template <class Entity, typename... Args>
		class EmptyState final : public State<Entity, Args...>, public Private::Singleton<EmptyState<Entity, Args...>>
		{
			friend typename Private::Singleton<EmptyState<Entity, Args...>>::Access;

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
