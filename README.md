# organizeme

# Сборка проекта в режиме Debug:
cmake -B build/Debug -D CMAKE_BUILD_TYPE=Debug && cmake --build -j4 ./build/Debug

# Сборка проекта в режиме Release:
cmake -B build/Release -D CMAKE_BUILD_TYPE=Release && cmake --build -j4 ./build/Release
