core_src = files(
    'core/Arduino.cpp',
    'core/HardwareSerial.cpp',
    'core/HardwareSerial0.cpp',
    'core/HardwareSerial1.cpp',
    'core/Print.cpp',
    'core/Stream.cpp',
    'core/abi.cpp',
    'core/chips/pinmap.cpp',
    'core/wiring.cpp',
)

core_inc = ['core/', '/usr/local/avr/include/']

core_lib = static_library(
    'core_lib',
    core_src,
    pic: false,
    cpp_args: [
        '-mmcu=atmega644p',
        '-DF_CPU=7372800',
    ],
    c_args: [
        '-mmcu=atmega644p',
        '-DF_CPU=7372800',
    ],
    include_directories: include_directories(core_inc),
)

core_dep = declare_dependency(
    link_with: core_lib,
    include_directories: include_directories(core_inc),
)