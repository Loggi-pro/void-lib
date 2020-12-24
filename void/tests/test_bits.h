#pragma once
#include <unity/unity_fixture_classes.h>
#include <void/bits.h>
class VoidTest_Bits : UnityTestClass<VoidTest_Bits> {
	public:
		static void setup() {}
		static void tearDown() {}


		static void setBit() {
			//one bit
			for (u08 i = 0; i < 8; ++i) {
				u08 a = 0;
				vd::setBit(a, i);
				TEST_ASSERT_EQUAL(1 << i, a);
			}

			//over bit
			EXPECT_ASSERT(
			    u08 a = 0;
			    vd::setBit(a, 8);
			);

			//1 bit setted, 1 bit set
			for (u08 i = 0; i < 8; ++i) {
				u08 a = 0x80;
				vd::setBit(a, i);
				TEST_ASSERT_EQUAL((1 << i) | 0x80, a);
			}

			//set 4 lower bits and 1 highter
			u08 a = 0;
			vd::setBit(a, 0, 1, 2, 3, 7);
			TEST_ASSERT_EQUAL(0x8F, a);
		}

		static void clearBit() {
			//one bit
			for (u08 i = 0; i < 8; ++i) {
				u08 a = 0xFF;
				vd::clearBit(a, i);
				TEST_ASSERT_EQUAL((~(1 << i)) & 0xFF, a);
			}

			//over bit
			EXPECT_ASSERT(
			    u08 a = 0xFF;
			    vd::clearBit(a, 8);
			);

			//1 bit clear, 1 bit clear
			for (u08 i = 0; i < 8; ++i) {
				u08 a = 0x7F;
				vd::clearBit(a, i);
				TEST_ASSERT_EQUAL(~(1 << i) & 0x7F, a);
			}

			//clear 4 lower bits and 1 highter
			u08 a = 0xFF;
			vd::clearBit(a, 0, 1, 2, 3, 7);
			TEST_ASSERT_EQUAL(0x70, a);
		}

		static void toggleBit() {
			//one bit set
			for (u08 i = 0; i < 8; ++i) {
				u08 a = 0;
				vd::toggleBit(a, i);
				TEST_ASSERT_EQUAL(1 << i, a);
			}

			//one bit toggle

			for (u08 i = 0; i < 8; ++i) {
				u08 a = 0xFF;
				vd::toggleBit(a, i);
				TEST_ASSERT_EQUAL((~(1 << i)) & 0xFF, a);
			}

			//over bit
			EXPECT_ASSERT(
			    u08 a = 0xFF;
			    vd::toggleBit(a, 8);
			);
			u08 a = 0xF0;
			vd::toggleBit(a, 0, 1, 2, 3, 4, 5, 6, 7);
			TEST_ASSERT_EQUAL(0x0F, a);
		}

		static void isBitSet() {
			//one bit set
			{
				u08 a = 0xF0;
				TEST_ASSERT_EQUAL(false, vd::isBitSet(a, 0));
				TEST_ASSERT_EQUAL(false, vd::isBitSet(a, 1));
				TEST_ASSERT_EQUAL(false, vd::isBitSet(a, 2));
				TEST_ASSERT_EQUAL(false, vd::isBitSet(a, 3));
				TEST_ASSERT_EQUAL(true, vd::isBitSet(a, 4));
				TEST_ASSERT_EQUAL(true, vd::isBitSet(a, 5));
				TEST_ASSERT_EQUAL(true, vd::isBitSet(a, 6));
				TEST_ASSERT_EQUAL(true, vd::isBitSet(a, 7));
			}
			//over bit
			EXPECT_ASSERT(
			    u08 a = 0xFF;
			    vd::isBitSet(a, 8);
			);
			{
				u08 a = 0xF0;
				TEST_ASSERT_EQUAL(false, vd::isBitSet(a, 0, 1, 2, 3));
				TEST_ASSERT_EQUAL(true, vd::isBitSet(a, 1, 2, 3, 4));
				TEST_ASSERT_EQUAL(true, vd::isBitSet(a, 4, 5, 6, 7));
			}
		}


		static void isBitSetMasked() {
			u08 a = 0xF0;
			TEST_ASSERT_EQUAL(false, vd::isBitSet(a, vd::Mask{ 0x0F }));
			TEST_ASSERT_EQUAL(true, vd::isBitSet(a, vd::Mask{ 0xF0 }));
			TEST_ASSERT_EQUAL(true, vd::isBitSet(a, vd::Mask{ 0x10 }));
		}

		static void run() {
			RUN_TEST_CASE_CLASS(VoidTest_Bits, setBit);
			RUN_TEST_CASE_CLASS(VoidTest_Bits, clearBit);
			RUN_TEST_CASE_CLASS(VoidTest_Bits, toggleBit);
			RUN_TEST_CASE_CLASS(VoidTest_Bits, isBitSet);
			RUN_TEST_CASE_CLASS(VoidTest_Bits, isBitSetMasked);
		}
};