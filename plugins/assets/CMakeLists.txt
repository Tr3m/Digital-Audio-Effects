file(GLOB SRC_FILES    
    "backgrounds/*.png"
    "knobs/*.png"
    "buttons/*.png"
    "buttons/vibrado_buttons/*.png"
    "buttons/compressor_buttons/*.png"
)

juce_add_binary_data(BinaryData SOURCES
    ${SRC_FILES}
)

# Need to build BinaryData with -fPIC flag on Linux
set_target_properties(BinaryData PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE)