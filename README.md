## Chronodir

Chronodir is a simple cross-compiled CLI tool that creates directories with timestamp prefixes. This helps you organize your files by automatically including the current date and time in the folder name.

## Installation

### Windows (MSVC)

#### Prerequisites

Before you begin, ensure you have the following installed:

- [CMake](https://cmake.org/download/)
- [Visual Studio](https://visualstudio.microsoft.com/) with C++ development tools

#### Steps

1. **Open a Developer Command Prompt for Visual Studio**:
   - You can find this in the Start Menu under Visual Studio.

2. **Navigate to the project directory**:
   - Use the `cd` command to change to your project directory.

3. **Create a build directory and navigate into it**:
   ```sh
   mkdir build
   cd build
   ```

4. **Run CMake to configure the project**:
   ```sh
   cmake ..
   ```

5. **Build the project**:
   ```sh
   cmake --build . --config Release
   ```

6. **Install the executable**:
   ```sh
   cmake --install . --config Release
   ```

### Linux (GCC/Clang)

#### Prerequisites

Before you begin, ensure you have the following installed:

- CMake:
  ```sh
  sudo apt-get install cmake
  ```
- GCC or Clang:
  ```sh
  sudo apt-get install build-essential
  ```
  or
  ```sh
  sudo apt-get install clang
  ```

#### Steps

1. **Open a terminal**:
   - You can use any terminal emulator of your choice.

2. **Navigate to the project directory**:
   - Use the `cd` command to change to your project directory.

3. **Create a build directory and navigate into it**:
   ```sh
   mkdir build
   cd build
   ```

4. **Run CMake to configure the project**:
   ```sh
   cmake ..
   ```

5. **Build the project**:
   ```sh
   make
   ```

6. **Install the executable**:
   ```sh
   sudo make install
   ```

## Usage

Once you have successfully installed Chronodir on your system, you can start using it to create directories with timestamp prefixes. Use the following command:

```sh
cdir "your folder name"
```