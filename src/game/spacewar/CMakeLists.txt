cmake_minimum_required(VERSION 3.1)

add_subdirectory(data)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(spacewar WIN32 
	main.cxx
	GameBuilder.cxx
	EntityBuilder.cxx
	SystemBuilder.cxx
	misc/Quadtree.cxx
	misc/VelocityHelpers.cxx
	misc/UIHelpers.cxx
	states/MainState.cxx
	states/MenuState.cxx
	states/GameOverState.cxx
	systems/ShipControlSystem.cxx
	systems/FuelSystem.cxx
	systems/RespawnSystem.cxx
	systems/PositioningSystem.cxx
	systems/PlayerUISystem.cxx
	systems/GravitationalSystem.cxx
	systems/StateSystem.cxx
	systems/CollisionSystem.cxx
	systems/LifetimeSystem.cxx
	systems/VelocitySystem.cxx
	systems/WeaponSystem.cxx)
target_link_libraries(spacewar firefly SDL2::Main)

install(TARGETS spacewar RUNTIME DESTINATION .)
