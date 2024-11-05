# GD32E23x Demo Suites cmake

This Repository is created for cmake build system VS Code integration of **GD32E23x Demo Suites** **_2024-02-28, V2.2.0_**.

## Versions of Sub-Modules
1. **xPack GNU Arm Embedded GCC Toolchain** version is **_xpack-arm-none-eabi-gcc-11.3.1-1.1_**.
	- **Path:** _Tools/xpack-arm-none-eabi-gcc-11.3.1-1.1_
	- You can use any toolchain you want. You need to correct paths in following files:
		- _Projects/Template/cmake/arm-none-eabi-gcc.cmake:2:_
			`set(TOOLCHAIN_DIRECTORY "${CMAKE_SOURCE_DIR}/../../Tools/xpack-arm-none-eabi-gcc-11.3.1-1.1/bin")`
		- _Projects/Template/.vscode/launch.json:12:_
			`"gdbPath": "${workspaceFolder}/../../Tools/xpack-arm-none-eabi-gcc-11.3.1-1.1/bin/arm-none-eabi-gdb.exe"`
   - You can use following link to download other versions:
   		- https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack/releases

2. **OpenOCD** version is **_xpack-openocd-0.11.0-3_**.
	- **Path:** _Tools/xpack-openocd-0.11.0-3_
	- Extracted from **Embedded Builder** **_V1.4.1.23782_**.
	- I highly suggest <ins>not to use</ins> another version of OpenOCD because of lack of GD32 MCU implementation.
	- If you want to change it, you need to correct paths in following files:
		- _Projects/Template/.vscode/launch.json:14:_
			`"serverpath": "${workspaceFolder}/../../Tools/xpack-openocd-0.11.0-3/bin/openocd.exe"`
		- _Projects/Template/.vscode/launch.json:17:_
			`"${workspaceFolder}/../../Tools/xpack-openocd-0.11.0-3/scripts/target/openocd_gdlink_gd32e23x.cfg"`
			- If you want to debug another MCU, then you can use another **[.cfg]** file of OpenOCD.
		- _Projects/Template/.vscode/task.json:_
			- Find and change all following in paths:
     			`${workspaceFolder}/../../../Tools/xpack-openocd-0.11.0-3`

3. **GD32E23x_standard_peripheral** version is **_2024-02-22, V2.1.0_**.
	- **Path:** _Drivers/GD32E23x_standard_peripheral_

4. **CMSIS** version is **_V6.1_**
	- **Path:** _Drivers/CMSIS_
	- Original latest GD CMSIS version was **_V5.1_** in **GD32E23x Demo Suites** **_2024-02-28, V2.2.0_**.
	- It is updated to **_V6.1_**.

5. **CMSIS/GD/GD32E23x** version is **_2023-09-04, V2.0.1_**
	- **Path:** _Drivers/CMSIS/GD/GD32E23x_
	- This is extracted from **GD32E23x Demo Suites** **_2024-02-28, V2.2.0_**.
	
## Tutorial

### 1. Download and Install **VS Code** from following link:
- https://code.visualstudio.com/

### 2. Download and Install **git** from following link:
- https://git-scm.com/downloads
- If install directory is different, then correct following path:
	- _Projects/Template/.vscode/settings.json:5:_
		`"path": "C:\\Program Files\\Git\\bin\\bash.exe"`

### 3. Download or Clone **the Repository** into your hard drive.
- https://github.com/burakenez/gd32e23x-demo-suites-cmake.git
- Avoid longh directory paths. It can cause some building problems.

### 4. Open Project folder in VS Code, not the top level folder directory.
- For example, _Projects/Template_

### 5. Download **VS Code Extentions** mentioned in _Projects/Template/.vscode/extensions.json_.

### 6. **cmake** and **ninja** will be downloaded automatically, thanks to _Projects/Template/vcpkg-configuration.json_ file.
- If you want to change vcpkg storage location, then correct following path:
	- _Projects/Template/.vscode/settings.json:15:_
		`"vcpkg.storageLocation": "C:\\Dev\\Tools\\vcpkg"`

### 7. Select **cmake Active Preset** as **Debug** or **Release**. For **Debugging**, be sure to use **Debug Preset**.

### 8. Build the project.
- You can Build by Clicking Build button at below panel.
- Or Press **[CTRL + SHIFT + P]**. Type **cmake** and select **CMake: Build**.
- Or Press **[CTRL + SHIFT + B]** for open tasks that are configured in _Projects/Template/.vscode/tasks.json_. Then, select **Build**.
- If you select **Debug Preset**, then your build files will be generated in _Projects/Template/Build/Debug_. It is also true for **Release Preset**.
- **hex**, **bin**, **elf**, **list**, **map**, **ssz**, **bsz** files will be generated in _Projects/Template/Build/Debug/Application/Application.*_

### 9. Start Debugging.
- Go to **RUN AND DEBUG** in **VS Code**. Select **Debug with OpenOCD**. This is configured in _Projects/Template/.vscode/launch.json_.
- Click **Start Debugging** Icon or Press **[F5]** in your keyboard.

## Folder Hierarchy and File Descriptions

- **Projects**
	- **Template:** _Main template for a project using the GD32E230 microcontroller._
		- **.vscode**
			- **extensions.json:** _Specifies recommended VS Code extensions for the project._
			- **launch.json:** _Configures the debugging settings for the project in VS Code._
			- **settings.json:** _Customizes workspace-specific VS Code settings._
			- **tasks.json:** _Defines tasks for building and other automated processes in VS Code._
		- **Application**
			- **Core**
				- **Inc**
					- **gd32e23x_it.h:** _Header file for interrupt handling functions specific to the GD32E230 microcontroller._
					- **gd32e23x_libopt.h:** _Header for library options and configurations._
					- **systick.h:** _Header for SysTick timer-related definitions and functions._
				- **Src**
					- **gd32e23x_it.c:** _Source file implementing interrupt handlers for the GD32E230._
					- **main.c:** _Main application file where the program's entry point and main loop are defined._
					- **system_gd32e23x.c:** _Contains system-level initialization, such as setting up the clock._
					- **systick.c:** _Source file for SysTick timer configurations and related functions._
			- **Startup**
				- **startup_gd32e23x.s:** _Assembly file containing the startup code, interrupt vector table, and initialization routines._
			- **User**
				- **syscalls.c:** _Implements system calls and I/O functions for the application, typically used for retargeting._
			- **CMakeLists.txt:** _Specifies CMake instructions for compiling the application._
			- **readme.txt:** _Basic information or instructions about the project setup and usage._
		- **Build**
			- **Debug**
				- **Application**
					- **Application.bin:** _Binary output file for flashing onto the device._
					- **Application.bsz:** _Binary symbol file, usually for debugging purposes._
					- **Application.elf:** _ELF format file that includes debugging symbols for detailed inspection._
					- **Application.hex:** _Intel HEX file format, another option for programming microcontrollers._
					- **Application.list:** _Assembly list of the program, useful for debugging._
					- **Application.map:** _Memory map file providing details about code and data placement._
					- **Application.ssz:** _Additional binary file, possibly for debugging or backup._
		- **cmake**
			- **arm-none-eabi-gcc.cmake:** _Toolchain file specifying settings for the ARM GCC compiler._
			- **project.cmake:** _General project-specific CMake settings._
		- **Drivers**
			- **BSP**
				- **GD32E230C_START**
					- **CMakeLists.txt:** _CMake configuration for the board support package (BSP) of the GD32E230C-START board._
			- **CMSIS**
				- **CMakeLists.txt:** _CMake configuration for CMSIS (Cortex Microcontroller Software Interface Standard)._
			- **GD32E23x_standard_peripheral**
				- **CMakeLists.txt:** _CMake configuration for the GD32E230 standard peripheral library._
		- **Middlewares:** _Folder to include any middleware libraries or software stacks required for the project._
		- **Utilities:** _Utility functions, libraries, or scripts that support the main application._
		- **.clang-format:** _Specifies code formatting rules for consistent style across files._
		- **CMakeLists.txt:** _Main CMake file that includes all necessary subdirectories and configurations for the project._
		- **CMakePresets.json:** _Defines CMake configuration presets for building the project with different settings._
		- **gd32e23x_flash.ld:** _Linker script defining memory regions and their usage for the GD32E230._
		- **GD32E230.svd:** _System View Description (SVD) file for the GD32E230 microcontroller, used for debugging and register descriptions._
		- **vcpkg-configuration.json:** _Configuration file for vcpkg, a package manager that manages C++ library dependencies for the project._
