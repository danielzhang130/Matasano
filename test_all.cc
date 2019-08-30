#include "gtest/gtest.h"
#include "set2/ecb_cbc_oracle.cc"
#include "set2/ecb_byte_decrypt_thread.cc"
#include "set2/ecb_byte_decrypt.cc"
#include "set2/ecb_cut_paste.cc"
#include "set2/cbc_bitflip.cc"
#include "set3/cbc_padding_oracle.cc"

TEST(SET2, ECB_CBC_ORACLE){
    using namespace ecb_cbc_oracle;
    detection_oracle(&ecb_or_cbc_encrypt);
}

TEST(SET2, ECB_BYTE_DECRYPT){
    using namespace ecb_byte_decrypt;
    decrypt(&ecb_oracle);
}

TEST(SET2, ECB_BYTE_DECRYPT_MULTITHREAD){
    using namespace ecb_byte_decrypt_thread;
    decrypt(&ecb_oracle);
}

TEST(SET2, ECB_CUT_AND_PASTE){
    using namespace ecb_cut_and_paste;
    read_profile(make_admin());
}

TEST(SET2, CBC_BITFLIP){
    using namespace cbc_bitflip;
    ASSERT_TRUE(isAdmin(bitflip()));
}

TEST(SET3, CBC_PADDING_ORACLE){
    using namespace cbc_padding_oracle;
    decrypt();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
