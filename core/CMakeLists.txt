target_sources(sqdelcore PRIVATE 
    abi.cpp
    Arduino.cpp
    HardwareSerial0.cpp
    HardwareSerial1.cpp
    HardwareSerial.cpp
    Print.cpp
    Stream.cpp
    wiring.cpp
)

add_subdirectory(chips)