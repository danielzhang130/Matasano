#include "gtest/gtest.h"
#include "set2/ecb_byte_decrypt_thread.cc"
#include "set2/ecb_byte_decrypt.cc"

TEST(SET2, ECB_BYTE_DECRYPT){
    using namespace ecb_byte_decrypt;
    decrypt(&ecb_oracle);
}

TEST(SET2, ECB_BYTE_DECRYPT_MULTITHREAD){
    using namespace ecb_byte_decrypt_thread;
    decrypt(&ecb_oracle);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
