cmake_minimum_required(VERSION 3.30.0)
project(MyApp)

# Definir padrão do C++
set(CMAKE_CXX_STANDARD 17)

# Encontre SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Adicione o executavel
add_executable(MyApp main.cpp Game.cpp)

# Vincule as bibliotecas do SFML ao executavel
target_link_libraries(MyApp sfml-graphics sfml-window sfml-system)