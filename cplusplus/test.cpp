#define UNITY_SUPPORT_TEST_CASES
#include <stdint.h>
#include <inttypes.h>
#include "Unity/src/unity.h"
#include "src/p0001.cpp"
#include "src/p0002.cpp"
// #include "src/p0003.cpp"
#include "src/p0004.cpp"
// #include "src/p0005.cpp"
#include "src/p0006.cpp"
// #include "src/p0007.cpp"
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
	// {   3,	INT16,	(void *)6857,				(void *(*)())p0003 },
	{   4,	INT32,	(void *)906609,				(void *(*)())p0004 },
	// {   5,	INT32,	(void *)232792560,			(void *(*)())p0005 },
	{   6,	INT32,	(void *)25164150,			(void *(*)())p0006 },
	// {   7,	INT32,	(void *)104743,				(void *(*)())p0007 },
	{   8,	INT64,	(void *)23514624000,		(void *(*)())p0008 },
	{   9,	INT32,	(void *)31875000,			(void *(*)())p0009 },
	// {  10,	INT64,	(void *)142913828922,		(void *(*)())p0010 },
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
	// {  25,	INT16,	(void *)4782,				(void *(*)())p0025 },
	// {  30,	INT32,	(void *)443839,				(void *(*)())p0030 },
	{  34,	UINT16,	(void *)40730,				(void *(*)())p0034 },
	{  76,	INT32,	(void *)190569291,			(void *(*)())p0076 },
	{ 836,	STR,	(void *)"aprilfoolsjoke",	(void *(*)())p0836 },
};
const size_t ANSWERS_LEN = sizeof(answers) / sizeof(answers[0]);
static uint64_t current_index = 0;

void setUp(void) {}

void tearDown(void) {}

void test_euler_answer() {
	Answer key = answers[current_index];
	int64_t iresult;
	uint64_t uresult;
	std::string sresult;
	std::ostringstream oss;
	switch (key.type) {
		case INT8:
		case INT16:
		case INT32:
		case INT64:
			iresult = ((int64_t (*)()) key.func)();
			oss << "Euler problem " << key.id << " should have an answer of " << (int64_t) key.answer << ", but we actually got " << iresult;
			TEST_ASSERT_EQUAL_INT64_MESSAGE(key.answer, iresult, oss.str().c_str());
			break;
		case UINT8:
		case UINT16:
		case UINT32:
		case UINT64:
			uresult = ((uint64_t (*)()) key.func)();
			oss << "Euler problem " << key.id << " should have an answer of " << (uint64_t) key.answer << ", but we actually got " << uresult;
			TEST_ASSERT_EQUAL_UINT64_MESSAGE(key.answer, uresult, oss.str().c_str());
			break;
		case STR:
			sresult = ((std::string (*)()) key.func)();
			oss << "Euler problem " << key.id << " should have an answer of " << (char *) key.answer << ", but we actually got " << sresult;
			TEST_ASSERT_EQUAL_STRING_MESSAGE((const char*) key.answer, sresult.c_str(), oss.str().c_str());
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
