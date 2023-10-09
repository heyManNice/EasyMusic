include(FetchContent)

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG        5736b15f7ea0ffb08dd38af21067c314d6a3aae9
    GIT_PROGRESS TRUE
)
message("stb")
FetchContent_MakeAvailable(stb)