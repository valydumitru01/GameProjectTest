# Table of Contents

1. [Game design](#gamedesign)
2. [Required Tools](#tools)
3. [Important Information and tutorials](#importantinformation)
4. [Application Dependencies](#dependencies)
   1. [MinGW/GCC](#gcc)
   2. [SDL2](#sdl)
   3. [OpenGL](#opengl)
   4. [GLEW](#glew)
   5. [GLM](#glm)
   6. [OpenAL](#openal)
   7. [Bullet](#bullet)
5. [Documentation](#documentation)

# Game design `<a name="gamedesign"></a>`

![](/doc/images/Game_Prototype_1.png)

## What is this game about?

This game will be an isometric 2D turn based game with a lot of familiar/minion/companion functionalities. Such as being able to gather a team to fight on your side and owning pets.

### Main character

The basic idea is that a main character goes around finding team members and convincing them to join him/her. The main character should be strong compared to the other team members, but not necessarily the strongest, that could change depending on the build you try.

### Team members

The team members are monsters (or people) you find around the world. You have to gather them to make your team stronger, althogh you can only use a limited amount of them at once in a battle.

### Pets

Pets are little friends (primarily monsters) you find around the world. These pets can be obtained fighting enemies, dropping them as if they were their "children". They can also be found around the world, like fairies or monkeys. They dont (usually) attack but only give buffs and bonuses to the character they follow. Each team member can have their own pet.

### Battle

Battles are turn based with tactical positioning. It includes mechanics such as AOE abilities, ground advantage, use of environment (push boulder) between others.

![](/doc/images/Prototype_Battle_1.png)


# Important information and tutorials `<a name="importantinformation"></a>`
## 32 Bits project

This game uses 32 bits, which means we can only use 4 GB of ram (even less due to some operating system space). This is not a big restriction for us hence the game will be simple and 2D. This will be a first touch with game development for most of the integrants of our team, and it should be ok. We must learn how to avoid memory leaks and to occupy too much memory. This will be a learning experience for all of us.

## SDL Wiki

A good source of information on how to use SDL, the difference between SDL2 and SDL 1.2, what does it do, etc.

[SDL Official Wiki](https://wiki.libsdl.org)


## Relationship between SDL2 and OpenGL

Explanation why are SDL and OpenGL related, so we can understand better what we are doing.

[Why is SDL and OpenGL related?](https://stackoverflow.com/questions/5769031/why-are-sdl-and-opengl-related)

## Examples of other games on Github

[Games in Github](https://github.com/leereilly/gameshttps://github.com/leereilly/games)

## Original structure from where the project started (Github)

[Original Project](https://github.com/kbrawley95/VSCode-OpenGL-Game-Engine)

# Required Tools `<a name="tools"></a>`

1. [Git](https://git-scm.com/) / [Github](https://desktop.github.com/)
2. (Optional) [Visual Studio Code](https://code.visualstudio.com/)
3. (Optional) [Vmware Player Virtual Machine](https://www.vmware.com/products/player/playerpro-evaluation.html) for testing your code on different operating systems.

# Application Dependencies `<a name="dependencies"></a>`
**Important:** The only dependecy you need to actually install is Mingw32 64 bits, the rest are portable. Which means they are inside the repository (`<span style="color:red">`_include_`</span>` and `<span style="color:red">`_lib_ `</span>`folder)
## 1. MinGW/GNU Compiler Collection (GCC) `<a name="gcc"></a>`


In order to execute our code, we will require GNU utilities. This contains numerous compilers for various languages (e.g. Fortran, C++ etc.) classified as the **GNU Compiler Collection (GCC)**, and their respective debuggers.

**MinGW ("Minimalist GNU for Windows")** is a free and open source software development environment to create Microsoft Windows applications.

MinGW includes a port of the **GNU Compiler Collection (GCC)**, GNU Binutils for Windows (assembler, linker, archive manager), a set of freely distributable Windows specific header files and static import libraries which enable the use of the Windows API, a Windows native build of the GNU Project's GNU Debugger, and miscellaneous utilities.

[Download here (Installer)](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download)

> _**IMPORTANT:** MUST SELECT x86_64 (which is 64 bits) **NOT** i686 (which is 32 bits)_

In case the installer doesn't work (which is likely):

[Download here (folder with 64 bits version)](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-win32/seh/x86_64-8.1.0-release-win32-seh-rt_v6-rev0.7z/download)

> _**HOW TO INSTALL:**_
>
> - Unzip the folder, copy it somewhere logical (for example C:/MinGW or C:/Program Files/MinGW).
> - Add to the path of the Environment Variables the bin folder.

---

## 2. SDL `<a name ="sdl"></a>`

**Simple DirectMedia Layer (SDL)** is a cross-platform software development library designed to provide a hardware abstraction layer for computer multimedia hardware components.
SDL manages video, audio, input devices, CD-ROM, threads, shared object loading, networking and timers.[5] For 3D graphics

[Download here](http://libsdl.org/download-2.0.php)

> _**IMPORTANT:** MUST SELECT 32 Bits VERSION **NOT** 64 Bits_

---

## 3. OPENGL `<a name ="opengl"></a>`

The **Open Graphics Library (OpenGL)** is a specification of various operations (functions) that facilite the rendering and manipulation of images, and other graphical niceties on our displays. The functions and the specification as a whole is maintain by the Khronos Group; a body of various industry experts, GPU manufactors, and related companies that collaborate to continually improve upon the capabilties of OpenGL -and the core requirements that supporting hardware should implement. The key word there is 'should'.

As OpenGL is **NOT** actually a set of classes/libaries or Application Programming Interfaces (APIs), it falls upon the Graphics Card Manufactors to implement the defined requirements i.e. they create the libraries, and classes that help you to run your favourite games via software called drivers. Installing these drivers will allow you to access core OpenGL functuality, and any further extensions to the specification which were supported by your Graphics card at the time of release.

---

## 4. GLEW `<a name ="glm"></a>`

The OpenGL Extension Wrangler Library. 
GLEW provides efficient run-time mechanisms for determining which OpenGL extensions are supported on the target platform. 
It allows us to check at runtime which extensions are present and which functions may be used.

[Download](http://glew.sourceforge.net/install.html)


# Documentation `<a name="documentation"></a>`

For more information on the materials provided, refer to the sources below:

### Minimalist GNU for Windows

* [MinGW](http://mingw.org/)

### OpenGL & Related Libraries

* [GLEW](https://github.com/nigels-com/glew#authors)
* [OpenGL](https://www.opengl.org/)

### SDL 

* [SDL2](http://wiki.libsdl.org/FrontPage)
* [SDL_net, SDL_mixer, SDL_ttf and SDL_image](https://wiki.libsdl.org/Libraries)