#define UNITY_SUPPORT_TEST_CASES
#include <stdint.h>
#include <inttypes.h>
#include "src/include/utils.h"
#include "Unity/src/unity.h"
#include "src/p0001.c"
#include "src/p0002.c"
#include "src/p0003.c"
#include "src/p0004.c"
#include "src/p0005.c"
#include "src/p0006.c"
#include "src/p0007.c"
#include "src/p0008.c"
#include "src/p0009.c"
#include "src/p0010.c"
#include "src/p0011.c"
#include "src/p0012.c"
#include "src/p0013.c"
#include "src/p0014.c"
#include "src/p0015.c"
#include "src/p0016.c"
#include "src/p0017.c"
#include "src/p0019.c"
#include "src/p0020.c"
#include "src/p0022.c"
#include "src/p0025.c"
#include "src/p0030.c"
#include "src/p0034.c"
#include "src/p0076.c"
#include "src/p0836.c"

typedef struct {
	uint16_t id;
	void *(*func)();
} ProblemRef;

ProblemRef answers[] = {	
	{   1,	(void *(*)())p0001 },
	{   2, 	(void *(*)())p0002 },
	{   3,	(void *(*)())p0003 },
	{   4,	(void *(*)())p0004 },
	{   5,	(void *(*)())p0005 },
	{   6,	(void *(*)())p0006 },
	{   7,	(void *(*)())p0007 },
	{   8,	(void *(*)())p0008 },
	{   9,	(void *(*)())p0009 },
	{  10,	(void *(*)())p0010 },
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
	{  25,	(void *(*)())p0025 },
	{  30,	(void *(*)())p0030 },
	{  34,	(void *(*)())p0034 },
	{  76,	(void *(*)())p0076 },
	{ 836,	(void *(*)())p0836 },
};
const size_t ANSWERS_LEN = sizeof(answers) / sizeof(answers[0]);
static size_t current_index = 0;

void setUp(void) {}

void tearDown(void) {}

void test_euler_answer() {
	ProblemRef key = answers[current_index];
	Answer answer = get_answer(key.id);
	char msg[256], *sresult;
	int64_t iresult;
	uint64_t uresult;
	switch (answer.type) {
		case ERROR:
			TEST_FAIL_MESSAGE("Unknown answer type. This should be unreachable.");
		case INT8:
			iresult = ((int8_t (*)()) key.func)();
			snprintf(msg, 256, "Euler problem %" PRIu16 " should have an answer of %" PRId8 ", but we actually got %" PRId8, key.id, answer.value.INT8, (int8_t)iresult);
			TEST_ASSERT_EQUAL_INT8_MESSAGE(answer.value.INT8, iresult, msg);
			break;
		case INT16:
			iresult = ((int16_t (*)()) key.func)();
			snprintf(msg, 256, "Euler problem %" PRIu16 " should have an answer of %" PRId16 ", but we actually got %" PRId16, key.id, answer.value.INT16, (int16_t)iresult);
			TEST_ASSERT_EQUAL_INT16_MESSAGE(answer.value.INT16, iresult, msg);
			break;
		case INT32:
			iresult = ((int32_t (*)()) key.func)();
			snprintf(msg, 256, "Euler problem %" PRIu16 " should have an answer of %" PRId32 ", but we actually got %" PRId32, key.id, answer.value.INT32, (int32_t)iresult);
			TEST_ASSERT_EQUAL_INT32_MESSAGE(answer.value.INT32, iresult, msg);
			break;
		case INT64:
			iresult = ((int64_t (*)()) key.func)();
			snprintf(msg, 256, "Euler problem %" PRIu16 " should have an answer of %" PRId64 ", but we actually got %" PRId64, key.id, answer.value.UINT64, iresult);
			TEST_ASSERT_EQUAL_INT64_MESSAGE(answer.value.INT64, iresult, msg);
			break;
		case UINT8:
			uresult = ((uint8_t (*)()) key.func)();
			snprintf(msg, 256, "Euler problem %" PRIu16 " should have an answer of %" PRIu8 ", but we actually got %" PRIu8, key.id, answer.value.UINT8, (uint8_t)uresult);
			TEST_ASSERT_EQUAL_UINT8_MESSAGE(answer.value.UINT8, uresult, msg);
			break;
		case UINT16:
			uresult = ((uint16_t (*)()) key.func)();
			snprintf(msg, 256, "Euler problem %" PRIu16 " should have an answer of %" PRIu16 ", but we actually got %" PRIu16, key.id, answer.value.UINT16, (uint16_t)uresult);
			TEST_ASSERT_EQUAL_UINT16_MESSAGE(answer.value.UINT16, uresult, msg);
			break;
		case UINT32:
			uresult = ((uint32_t (*)()) key.func)();
			snprintf(msg, 256, "Euler problem %" PRIu16 " should have an answer of %" PRIu32 ", but we actually got %" PRIu32, key.id, answer.value.UINT32, (uint32_t)uresult);
			TEST_ASSERT_EQUAL_UINT32_MESSAGE(answer.value.UINT32, uresult, msg);
			break;
		case UINT64:
			uresult = ((uint64_t (*)()) key.func)();
			snprintf(msg, 256, "Euler problem %" PRIu16 " should have an answer of %" PRIu64 ", but we actually got %" PRIu64, key.id, answer.value.UINT64, uresult);
			TEST_ASSERT_EQUAL_UINT64_MESSAGE(answer.value.UINT64, uresult, msg);
			break;
		case STR:
			sresult = ((char *(*)()) key.func)();
			snprintf(msg, 256, "Euler problem %u should have an answer of %s, but we actually got %s", key.id, answer.value.STR, sresult);
			TEST_ASSERT_EQUAL_STRING_MESSAGE(answer.value.STR, sresult, msg);
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
