#define UNITY_SUPPORT_TEST_CASES
#include <stdint.h>
#include <inttypes.h>
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

typedef enum {
	INT8,
	INT16,
	INT32,
	INT64,
	UINT8,
	UINT16,
	UINT32,
	UINT64,
	STR,
} AnswerType;

typedef struct {
	uint32_t id;
	AnswerType type;
	void *answer;
	void *(*func)();
} Answer;

const Answer answers[] = {	
	{   1,	INT32,	(void *)233168,				(void *(*)())p0001 },
	{   2,	INT32,	(void *)4613732, 			(void *(*)())p0002 },
	{   3,	INT16,	(void *)6857,				(void *(*)())p0003 },
	{   4,	INT32,	(void *)906609,				(void *(*)())p0004 },
	{   5,	INT32,	(void *)232792560,			(void *(*)())p0005 },
	{   6,	INT32,	(void *)25164150,			(void *(*)())p0006 },
	{   7,	INT32,	(void *)104743,				(void *(*)())p0007 },
	{   8,	INT64,	(void *)23514624000,		(void *(*)())p0008 },
	{   9,	INT32,	(void *)31875000,			(void *(*)())p0009 },
	{  10,	INT64,	(void *)142913828922,		(void *(*)())p0010 },
	{  11,	INT32,	(void *)70600674,			(void *(*)())p0011 },
	// {  12,	INT32,	(void *)76576500,			(void *(*)())p0012 },
	{  13,	INT64,	(void *)5537376230,			(void *(*)())p0013 },
	{  14,	INT32,	(void *)837799,				(void *(*)())p0014 },
	{  15,	INT64,	(void *)137846528820,		(void *(*)())p0015 },
	{  16,	INT16,	(void *)1366,				(void *(*)())p0016 },
	{  17,	INT16,	(void *)21124,				(void *(*)())p0017 },
	{  19,	UINT8,	(void *)171,				(void *(*)())p0019 },
	{  20,	INT16,	(void *)648,				(void *(*)())p0020 },
	{  22,	INT32,	(void *)871198282,			(void *(*)())p0022 },
	{  25,	INT16,	(void *)4782,				(void *(*)())p0025 },
	{  30,	INT32,	(void *)443839,				(void *(*)())p0030 },
	{  34,	UINT16,	(void *)40730,				(void *(*)())p0034 },
	{  76,	INT32,	(void *)190569291,			(void *(*)())p0076 },
	{ 836,	STR,	(void *)"aprilfoolsjoke",	(void *(*)())p0836 },
};
const size_t ANSWERS_LEN = sizeof(answers) / sizeof(answers[0]);
static size_t current_index = 0;

void setUp(void) {}

void tearDown(void) {}

void test_euler_answer() {
	Answer key = answers[current_index];
	char *msg = (char*)malloc(256 * sizeof(char)), *sresult;
	int64_t iresult;
	uint64_t uresult;
	switch (key.type) {
		case INT8:
		case INT16:
		case INT32:
		case INT64:
			iresult = ((uint64_t (*)()) key.func)();
			snprintf(msg, 256, "Euler problem %u should have an answer of %" PRId64 ", but we actually got %" PRId64, key.id, (int64_t) key.answer, iresult);
			TEST_ASSERT_EQUAL_INT64_MESSAGE(key.answer, iresult, msg);
			break;
		case UINT8:
		case UINT16:
		case UINT32:
		case UINT64:
			uresult = ((uint64_t (*)()) key.func)();
			snprintf(msg, 256, "Euler problem %u should have an answer of %" PRIu64 ", but we actually got %" PRIu64, key.id, (uint64_t) key.answer, uresult);
			TEST_ASSERT_EQUAL_UINT64_MESSAGE(key.answer, uresult, msg);
			break;
		case STR:
			sresult = ((char *(*)()) key.func)();
			snprintf(msg, 256, "Euler problem %u should have an answer of %s, but we actually got %s", key.id, (char *) key.answer, sresult);
			TEST_ASSERT_EQUAL_STRING_MESSAGE(key.answer, sresult, msg);
	}
	free(msg);
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
