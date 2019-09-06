cmake_minimum_required(VERSION 3.2.3)
project(Matasano)
add_executable(Matasano src/test_all.cc)

include(FindOpenSSL)
if(${OPENSSL_VERSION} VERSION_LESS "1.1")
    message(FATAL_ERROR "OpenSSL version ${OPENSSL_VERSION} has to be later than 1.1")
endif()

message(STATUS "libcrypto ${OPENSSL_INCLUDE_DIR}")
message(STATUS "libcrypto ${OPENSSL_CRYPTO_LIBRARY}")

add_library(libcrypto INTERFACE)
target_include_directories(libcrypto INTERFACE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(libcrypto INTERFACE ${OPENSSL_CRYPTO_LIBRARY})

target_link_libraries(Matasano PUBLIC libcrypto)

message(STATUS "Getting GoogleTest library")
execute_process(COMMAND git submodule update --init -- googletest
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(BUILD_GMOCK OFF)
add_subdirectory(googletest)
target_link_libraries(Matasano PUBLIC gtest_main)

add_subdirectory(src)

target_link_libraries(Matasano PUBLIC b64)
target_link_libraries(Matasano PUBLIC fixed_xor)
target_link_libraries(Matasano PUBLIC aes_ecb)
target_link_libraries(Matasano PUBLIC random)
target_link_libraries(Matasano PUBLIC aes_cbc)
target_link_libraries(Matasano PUBLIC padding)
target_link_libraries(Matasano PUBLIC aes_ctr)
target_link_libraries(Matasano PUBLIC sha1)

