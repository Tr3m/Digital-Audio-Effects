target_sources(${PROJECT_NAME}
    PRIVATE
        Delay.cpp
        Delay.h
        IIRFilter.cpp
        IIRFilter.h
        Compressor.cpp
        Compressor.h
        Limiter.cpp
        Limiter.h
        Chorus.cpp
        Chorus.h
        Vibrado.cpp
        Vibrado.h
        Flanger.cpp
        Flanger.h
        Reverb.cpp
        Reverb.h
        Distortion.cpp
        Distortion.h
)

add_subdirectory(utils)
include_directories(utils)

add_subdirectory(base)
include_directories(base)