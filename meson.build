core_src = files([
    'core/abi.cpp',
    'core/Arduino.cpp',
    'core/HardwareSerial0.cpp',
    'core/HardwareSerial1.cpp',
    'core/HardwareSerial.cpp',
    'core/Print.cpp',
    'core/Stream.cpp',
    'core/wiring.cpp',
    'core/chips/pinmap.cpp'
])

core_inc = [
    'core/', 
    '/home/james/local/avr/avr/include/'
]

core_lib = static_library(
    'core_lib', 
    core_src,
    pic: false,
    include_directories : include_directories(core_inc)
)

core_dep = declare_dependency(
    link_with: core_lib,
    include_directories : include_directories(core_inc),
)