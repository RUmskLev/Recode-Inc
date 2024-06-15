# Plague-Inc with AI assistant

## Run on local machine:
Install SDL2, SDL2_image, SDL2_gfx, SDL2_ttf on official sites or use libraries in repository

Run to generate cache:
```shell
mkdir build && cd build && cmake ..
```

Then build via:
```shell
cmake --build .
```

## Run training

To train an AI compile neural_net_main.cpp


## Options

Read CMakeLists.txt for more info.

 You can toggle on and off sdl2 dependencies and build without it.
 Also it has parameter for logger, if ON - it will create new shell window and reassign std::cout std::cin and std::err to it. Easy use for Graphical applications.