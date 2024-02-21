cmake_minimum_required(VERSION 3.10)

# set the project name
project(Game)

# set path to findSFML.cmake file
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules")

# find SFML components
find_package(SFML 2.4 COMPONENTS graphics window system audio REQUIRED)

# list .cpp files
set(SOURCES main.cpp EL.cpp LP.cpp Game.cpp GameObject.cpp GameObjectManager.cpp MP.cpp IP.cpp Camera.cpp Particle.cpp 
            ParticleManager.cpp TileMap.cpp Layer.cpp Player.cpp Map.cpp MapTitle.cpp SceneTitle.cpp Staircase.cpp
            Bullet.cpp PlayerStats.cpp PlayerManager.cpp UIHP.cpp UIExp.cpp MapDungeon.cpp Challenge.cpp ChallengeKills.cpp 
            UIChallenge.cpp Enemy.cpp EnemyZombie.cpp SceneDungeon.cpp SceneFloor1.cpp EnemySlime.cpp EnemyShooter.cpp 
            EnemyBullet.cpp GameOver.cpp)

# add sub directories
# add_subdirectory(FolderName)

# EXAMPLE: CMakeList.txt in sub directory
# set(SOURCES
# ${SOURCES}
# ${Game_SOURCE_DIR}/FolderName/FileName.cpp
# PARENT_SCOPE
# )

# add the executable
add_executable(Game ${SOURCES})

# link sub directories
# target_link_directories(Game PUBLIC "${Game_SOURCE_DIR}/FolderName")

# link SFML libraries
target_link_libraries(Game sfml-graphics sfml-window sfml-system sfml-audio)