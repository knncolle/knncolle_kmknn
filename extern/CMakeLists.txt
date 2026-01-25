include(FetchContent)

FetchContent_Declare(
  knncolle
  GIT_REPOSITORY https://github.com/knncolle/knncolle
  GIT_TAG master # ^3.0.0
)

FetchContent_Declare(
  kmeans
  GIT_REPOSITORY https://github.com/libscran/kmeans
  GIT_TAG master # ^4.0.0
)

FetchContent_Declare(
  sanisizer
  GIT_REPOSITORY https://github.com/LTLA/sanisizer
  GIT_TAG master # ^0.1.0
)

FetchContent_MakeAvailable(knncolle)
FetchContent_MakeAvailable(kmeans)
FetchContent_MakeAvailable(sanisizer)
