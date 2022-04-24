cmake_minimum_required(VERSION 3.1)

add_library(firefly 
	STATIC
	EntityManager.cxx 
	Engine.cxx 
	ResourceManager.cxx 
	Renderer.cxx 
	Frame.cxx
	Entity.cxx
	SystemManager.cxx
	EventManager.cxx
	EntityPrototypes.cxx
	StateMachine.cxx
	IGameState.cxx
	events/IEvent.cxx
	events/GameStateEvent.cxx
	events/SetFuelEvent.cxx
	events/SystemEvent.cxx
	events/NativeEvent.cxx
	events/EntityEvent.cxx
	events/UpdateEvent.cxx
	events/StateEvent.cxx
	events/KillEvent.cxx
	events/CollisionEvent.cxx
	events/PositionEvent.cxx
	events/SetSpeedEvent.cxx
	events/SetAccelerationEvent.cxx
	events/AddSpeedEvent.cxx
	events/AddAccelerationEvent.cxx
	events/SetAmmunitionEvent.cxx
	events/ShootEvent.cxx
	systems/ISystem.cxx
	systems/RenderingSystem.cxx)

target_link_libraries(firefly SDL2::Core SDL2::Image SDL2::TTF)
