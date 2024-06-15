# Plague-Inc with AI assistant

## Run on local machine:
Install SDL2, SDL2_image, SDL2_gfx, SDL2_ttf on official sites or use libraries in repository

Run to generate cache:
mkdir build && cd build && cmake ..

Then build via:
cmake --build .

## Run training

To train an AI compile neural_net_main.cpp


## Options

Read CMakeLists.txt for more info.

 You can toggle on and off sdl2 dependencies and build without it.
 Also it has parameter for logger, if ON - it will create new shell window and reassign std::cout std::cin and std::err to it. Easy use for Graphical applications. 

You can start, choose the first country for infection. While you virus is spreading, you are going to catch points and upgrade your virus. 

There is the virus's mene where you can choose witch parametr you want to upgrade.

![image](https://github.com/RUmskLev/Recode-Inc/assets/74106956/502d8509-5108-43cc-81f2-127b6046f734)

You will win, if you infect all people around the world and lose if the cure creats faster.


If you want, you can quit from the game.
You can see your faults and winnnings in the counter in the menu.
