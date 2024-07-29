# Online Food Order System

This C++ project implements an online food ordering system that interacts with a Supabase backend. The project allows users to view a list of available food items and place orders. The food items and orders are stored in Supabase.

## Table of Contents

- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [API Endpoints](#api-endpoints)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## Prerequisites

Before you begin, ensure you have met the following requirements:

- You have a C++ compiler that supports C++17.
- You have `vcpkg` installed for managing dependencies.

### Installing `vcpkg`

1. Clone the `vcpkg` repository:

    ```sh
    git clone https://github.com/microsoft/vcpkg.git
    cd vcpkg
    ```

2. Run the bootstrap script:

    - On Linux or macOS:

      ```sh
      ./bootstrap-vcpkg.sh
      ```

    - On Windows:

      ```sh
      .\bootstrap-vcpkg.bat
      ```

3. Install the required libraries:

    ```sh
    ./vcpkg install cpr rapidjson
    ```

4. Add the `vcpkg` toolchain file path in your IDE (e.g., Visual Studio Code):

    ```json
    "cmake.configureSettings": {
        "CMAKE_TOOLCHAIN_FILE": "/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake"
    }
    ```

    Replace `/path/to/vcpkg` with the actual path to your `vcpkg` directory.

## Installation

1. Clone the repository:

    ```sh
    git clone https://github.com/yourusername/online-food-order.git
    cd online-food-order
    ```

2. Create a `build` directory and configure the project using CMake:

    ```sh
    mkdir build
    cd build
    cmake ..
    ```

3. Compile the project:

    ```sh
    make
    ```

4. Run the executable:

    ```sh
    ./Hamro_project
    ```

## Usage

Run the compiled executable and follow the on-screen instructions to view the food list and place orders.

## API Endpoints

The project interacts with the following Supabase API endpoints:

- **Get Food List**
  
  `GET https://your-supabase-url.supabase.co/rest/v1/food`

- **Place Order**

  `POST https://your-supabase-url.supabase.co/rest/v1/orders`

## Project Structure

