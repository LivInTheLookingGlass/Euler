#define UNITY_SUPPORT_TEST_CASES
#include "Unity/src/unity.h"
#include "p0001.c"
#include "p0002.c"
#include "p0003.c"
#include "p0004.c"
#include "p0005.c"
#include "p0006.c"
#include "p0007.c"
#include "p0008.c"
#include "p0009.c"
#include "p0010.c"
#include "p0011.c"
// #include "p0012.c"
#include "p0013.c"
#include "p0014.c"
#include "p0015.c"
#include "p0016.c"
#include "p0034.c"
#include "p0076.c"

typedef struct {
	unsigned int id;
	unsigned long long answer;
	unsigned long long (*func)();
} Answer;

#define ANSWERS_LEN (sizeof(answers) / sizeof(answers[0]))
static const Answer answers[] = {
	{1,		233168,			p0001},
	{2,		4613732, 		p0002},
	{3,		6857,			p0003},
	{4,		906609,			(unsigned long long (*)()) p0004},
	{5,		232792560,		p0005},
	{6,		25164150,		p0006},
	{7,		104743,			p0007},
	{8,		23514624000,	p0008},
	{9,		31875000,		p0009},
	{10,	142913828922,	p0010},
	{11,	70600674,		p0011},
	{13,	5537376230,		p0013},
	{14,	837799,			p0014},
	{15,	137846528820,	p0015},
	{16,	1366,			p0016},
	{34,	40730,			p0034},
	{76,	190569291,		(unsigned long long (*)()) p0076},
};
static unsigned long long current_index = 0;

void setUp(void) {
	// set stuff up here
}

void tearDown(void) {
	// clean stuff up here
}

void test_euler_answer() {
	Answer key = answers[current_index];
	unsigned long long result = key.func();
	char *msg = (char*)malloc(256 * sizeof(char));
	snprintf(msg, 256, "Euler problem %u should have an answer of %llu, but we actually got %llu", key.id, key.answer, result);
	TEST_ASSERT_EQUAL_INT64_MESSAGE(key.answer, result, msg);
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
