#define UNITY_SUPPORT_TEST_CASES
#include "Unity/src/unity.h"
#include "src/include/utils.hpp"
#include <stdint.h>
#include <inttypes.h>
#include "src/p0001.cpp"
#include "src/p0002.cpp"
#include "src/p0003.cpp"
#include "src/p0004.cpp"
// #include "src/p0005.cpp"
#include "src/p0006.cpp"
#include "src/p0007.cpp"
#include "src/p0008.cpp"
#include "src/p0009.cpp"
// #include "src/p0010.cpp"
#include "src/p0011.cpp"
// #include "src/p0012.cpp"
#include "src/p0013.cpp"
#include "src/p0014.cpp"
#include "src/p0015.cpp"
#include "src/p0016.cpp"
#include "src/p0017.cpp"
#include "src/p0019.cpp"
#include "src/p0020.cpp"
#include "src/p0022.cpp"
// #include "src/p0025.cpp"
// #include "src/p0030.cpp"
#include "src/p0034.cpp"
#include "src/p0076.cpp"
#include "src/p0836.cpp"

typedef struct {
	uint16_t id;
	void *(*func)();
} ProblemRef;

ProblemRef answers[] = {
	{   1,	(void *(*)())p0001 },
	{   2, 	(void *(*)())p0002 },
	{   3,	(void *(*)())p0003 },
	{   4,	(void *(*)())p0004 },
	// {   5,	(void *(*)())p0005 },
	{   6,	(void *(*)())p0006 },
	{   7,	(void *(*)())p0007 },
	{   8,	(void *(*)())p0008 },
	{   9,	(void *(*)())p0009 },
	// {  10,	(void *(*)())p0010 },
	{  11,	(void *(*)())p0011 },
	// {  12,	(void *(*)())p0012 },
	{  13,	(void *(*)())p0013 },
	{  14,	(void *(*)())p0014 },
	{  15,	(void *(*)())p0015 },
	{  16,	(void *(*)())p0016 },
	{  17,	(void *(*)())p0017 },
	{  19,	(void *(*)())p0019 },
	{  20,	(void *(*)())p0020 },
	{  22,	(void *(*)())p0022 },
	// {  25,	(void *(*)())p0025 },
	// {  30,	(void *(*)())p0030 },
	{  34,	(void *(*)())p0034 },
	{  76,	(void *(*)())p0076 },
	{ 836,	(void *(*)())p0836 },
};
const size_t ANSWERS_LEN = sizeof(answers) / sizeof(answers[0]);
static uint64_t current_index = 0;

void setUp(void) {}

void tearDown(void) {}

void test_euler_answer() {
	ProblemRef key = answers[current_index];
	Answer answer = get_answer(key.id);
	int64_t iresult;
	uint64_t uresult;
	std::string sresult;
	std::ostringstream oss;
	switch (answer.type) {
		case ERRORT:
			TEST_FAIL_MESSAGE("Unknown answer type. This should be unreachable.");
		case INT8T:
			iresult = ((int8_t (*)()) key.func)();
			oss << "Euler problem " << key.id << " should have an answer of " << answer.value.int8 << ", but we actually got " << iresult;
			TEST_ASSERT_EQUAL_INT8_MESSAGE(answer.value.int8, (int8_t)iresult, oss.str().c_str());
			break;
		case INT16T:
			iresult = ((int16_t (*)()) key.func)();
			oss << "Euler problem " << key.id << " should have an answer of " << answer.value.int16 << ", but we actually got " << iresult;
			TEST_ASSERT_EQUAL_INT8_MESSAGE(answer.value.int16, (int16_t)iresult, oss.str().c_str());
			break;
		case INT32T:
			iresult = ((int32_t (*)()) key.func)();
			oss << "Euler problem " << key.id << " should have an answer of " << answer.value.int32 << ", but we actually got " << iresult;
			TEST_ASSERT_EQUAL_INT8_MESSAGE(answer.value.int32, (int32_t)iresult, oss.str().c_str());
			break;
		case INT64T:
			iresult = ((int64_t (*)()) key.func)();
			oss << "Euler problem " << key.id << " should have an answer of " << answer.value.int64 << ", but we actually got " << iresult;
			TEST_ASSERT_EQUAL_INT64_MESSAGE(answer.value.int64, iresult, oss.str().c_str());
			break;
		case UINT8T:
			uresult = ((uint8_t (*)()) key.func)();
			oss << "Euler problem " << key.id << " should have an answer of " << answer.value.uint8 << ", but we actually got " << uresult;
			TEST_ASSERT_EQUAL_UINT8_MESSAGE(answer.value.uint8, (uint8_t) uresult, oss.str().c_str());
			break;
		case UINT16T:
			uresult = ((uint16_t (*)()) key.func)();
			oss << "Euler problem " << key.id << " should have an answer of " << answer.value.uint16 << ", but we actually got " << uresult;
			TEST_ASSERT_EQUAL_UINT16_MESSAGE(answer.value.uint16, (uint16_t) uresult, oss.str().c_str());
			break;
		case UINT32T:
			uresult = ((uint32_t (*)()) key.func)();
			oss << "Euler problem " << key.id << " should have an answer of " << answer.value.uint32 << ", but we actually got " << uresult;
			TEST_ASSERT_EQUAL_UINT32_MESSAGE(answer.value.uint32, (uint32_t) uresult, oss.str().c_str());
			break;
		case UINT64T:
			uresult = ((uint64_t (*)()) key.func)();
			oss << "Euler problem " << key.id << " should have an answer of " << answer.value.uint64 << ", but we actually got " << uresult;
			TEST_ASSERT_EQUAL_UINT64_MESSAGE(answer.value.uint64, uresult, oss.str().c_str());
			break;
		case STRINGT:
			sresult = ((std::string (*)()) key.func)();
			oss << "Euler problem " << key.id << " should have an answer of " << answer.value.string << ", but we actually got " << sresult;
			TEST_ASSERT_EQUAL_STRING_MESSAGE(answer.value.string, sresult.c_str(), oss.str().c_str());
	}
}

int main(int argc, char const *argv[]) {
	char func_name[32];
	UNITY_BEGIN();
	for (current_index = 0; current_index < ANSWERS_LEN; ++current_index) {
		snprintf(func_name, 32, "test_euler_answer[%03u]", answers[current_index].id);
		UnityDefaultTestRun(test_euler_answer, func_name, __LINE__);
	}
	return UNITY_END();
}
