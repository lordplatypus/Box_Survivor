# Box Survivor

A simple 2D, 8 bit style, roguelike, twin-stick shooter made with SFML and c++.

###### Prerequisites
- cmake 3.18 or higher
- SFML 2.4 or higher

###### Build Instructions
- Clone this repository
```
git clone https://github.com/lordplatypus/Box_Survivor.git
```
- Move to the source
```
cd ./Box_Survivor
```
- Make a build directory and move to it
```
mkdir ./build && cd ./build
```
- Use cmake to generate the make files into the build folder
```
cmake -S ../ -B ./
```
- Optional: Set debug mode
```
cmake -DCMAKE_BUILD_TYPE=Debug ..
```
- Make
```
make
```
- Move the "Resources" folder from the source files to the build folder
```
mv ../Resources ./
```
- Run the Game
```
./Game
```

###### Debug vscode launch.json
- For "program" set the path to the Game executable
- For "cwd" set the path to the build folder
```
{
    "version": "1.0.0",
    "configurations": [
        {
            "name": "g++-9 - Build and debug active file",
            "type": "cppdbg",
            "request": "launch",
            "program": "~/Box_Survivor/build/Game",
            "args": [],
            "stopAtEntry": false,
            "cwd": "~/Box_Survivor/build/",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```