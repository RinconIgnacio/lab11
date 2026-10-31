# GoogleTest: Use the system copy if there is one, otherwise download it.
find_package(GTest QUIET)
if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
        GIT_SHALLOW TRUE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    set(gtest_main_target gtest_main)
else()
    set(gtest_main_target GTest::gtest_main)
endif()

include(GoogleTest)

# Lab 10: Deck. These pass in this starter (the Lab 10 solution is included).
add_executable(deck_tests test_deck.cpp)
target_link_libraries(deck_tests PRIVATE arcade_lib ${gtest_main_target})
gtest_discover_tests(deck_tests)

# Lab 11: these fail until the Card operators and Hand are finished. That is
# the point.
add_executable(hand_tests test_hand.cpp)
target_link_libraries(hand_tests PRIVATE arcade_lib ${gtest_main_target})
gtest_discover_tests(hand_tests)
