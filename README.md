## Jamie's CMake Training Course

### Prerequisites

#### Knowledge
At least CS103 or equivalent experience with C++ code is recommended to be able to complete the session exercises.  However, if you don't have this experience, you're welcome to attend and listen to the lecture or work with someone else on the exercises.

#### Computer
You will need access to a proper command line environment with a C++ compiler and CMake installed.  The easiest way to get this is to use the CS104 course virtual machine, or (if you have a Mac) install cmake and g++ via Homebrew.  If you use Windows then WSL is a good option, you can install it using [Microsoft's guide here](https://docs.microsoft.com/en-us/windows/wsl/install-win10).  Please setup the environment a couple days in advance to leave time for any issues, and message Jamie if you have any trouble.

It's also highly recommended to install CMake syntax highlighting for your favorite text editor.  For Sublime Text I recommend the `CMake` package. 

Note: MinGW on Windows can work but requires you to change the file extensions in the commands I give so is for advanced users only.

#### Repository
Clone the repository `https://github.com/multiplemonomials/CMakeTraining` to a folder on your computer to get access to the powerpoints and the files needed for the exercises. 

### Course Outline

	• Session 1: CMake and Building C++
		○ Intro: Why we Care about Build Systems
		○ How C++ Code is Built
		○ Exercise: Compiling C++ Manually
		○ Basics of CMake Syntax (variables, statements, basic functions)
		○ CMake Directory Structure (source, binary, list dir)
		○ Exercise: My First CMakeLists.txt
	• Session 2: More Advanced CMake
		○ Types of Library and Executable Targets
		○ Properties, Setting Them, and Things You Can Set Them On
		○ Common Properties
			§ Compile flags, include directories, definitions
			§ CXX standard
		○ Interface Properties
		○ Exercise: Creating a Static Library
		○ CMake Cache Variables
		○ Compile Flags and Configuration Compile Flags
		○ To Sum Up: Sources of Compile Flags
		○ Build Configurations
		○ Exercise: Fleshing Out the CMakeLists.txt
	• Session 3: Shared Libraries: The Horror and the Triumph
		○ Aside: how and why I know all this stuff
		○ Motivation for Shared Libraries
		○ Function of Shared Libraries in Linux
		○ Shared Library Dependencies
		○ Exercise: Analyzing Dependencies
		○ RPATHs and SOVERSIONs
		○ Exercise: building a library
		○ Finding Libraries and Headers in CMake
		○ Using Find Modules
		○ Exercise: Using some libraries in your thing (Python, matplotlib)
		○ Appendix: Shared Libraries on Windows MinGW, Windows MSVC, and Mac
	• Session 4: Really Advanced CMake
		○ Generator Expressions
		○ Custom Commands and Targets
		○ Functions, Macros, and Keyword Arguments
		○ Exercise: Building a Complex Library
		○ Importing Libraries
		○ System Introspection
			§ Checking the platform
			§ Finding types
			§ Finding headers
			§ Finding functions
		○ Exercise: Writing a find module
	• Session 5: Offensive and Defensive CMake  …or… How to Debug Build Systems
		○ Symbols and Mangling
		○ Symbol Exporting
		○ Debugging Undefined References
		○ ABIs: the Root of All Evil
		○ Cross-Compiling and Toolchain Files
		○ Exploring the CMake Cache
		○ Exercise: Cross-Compiling Something Hard (libhackrf?)