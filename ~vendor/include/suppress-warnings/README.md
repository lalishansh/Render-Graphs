# suppress-warnings (wip)
<b> suppress-warnings </b> is a header only library that allows you to suppress warnings in a specific scope. It is useful when you want to suppress warnings in a specific scope without having to disable them globally.

**Note:** This library is only supported on MSVC, GCC and Clang (for now).

**Table of Contents**
- [Installation](#installation)
- [Usage](#usage)
- [Credits](#credits)


## Installation
To use this library, simply add the header directory in your project as an include directory and start using it.
```cmake
# CMakeLists.txt
TARGET_INCLUDE_DIRECTORIES(${YOUR_TARGET} PUBLIC /path/to/suppress-warnings/include)
# HERE '/path/to/suppress-warnings/include' is "${CMAKE_SOURCE_DIR}/~vendor/include"
```

## Usage
```cpp
// push the warning suppression
#include <suppress-warnings/push>

// suppress the warning
#include <suppress-warnings/all>             // suppress all warnings
#include <suppress-warnings/unused-variable> // suppress unused-variable warning
// ... other warnings to suppress

// ...
// your code here
// ...

// pop the warning suppression
#include <suppress-warnings/pop>
```

Since this library is WIP, you can add new warnings by running `scripts/add_new_warning.ps1` script.
```bash
# run the script
./~vendor/include/suppress-warnings/scripts/add_new_warning.ps1 -Name "your-warning-name"
```

## Credits
This library is inspired by [Alexhuszagh/warnings](https://github.com/Alexhuszagh/warnings) GitHub Repository.
