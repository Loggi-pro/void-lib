#include <unity/unity_fixture.h>
#include <void/tests/tests.h>
#include <void/platform_specific.h>
#include <void/packed.h>
int main(int argc, const char* argv[]) {
	UnityMain(argc, argv, RunVoidTests);
}
