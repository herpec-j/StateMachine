#pragma once

namespace AO
{
	namespace StateMachine
	{
		inline namespace Version_1
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

				using ConstEntityPtr = EntityPtr const;

				// Constructors
				State(void) = default;

				State(State const &) = delete;

				State(State &&) = default;

				// Assignment operators
				State &operator=(State const &) = delete;

				State &operator=(State &&) = default;

				// Destructor
				virtual ~State(void) = default;

			protected:
				// Virtual Methods
				virtual void enter(EntityPtr entity) = 0;

				virtual void execute(EntityPtr entity, Args... args) = 0;

				virtual void exit(EntityPtr entity) = 0;
			};
		}
	}
}
