#pragma once

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
	}
}
