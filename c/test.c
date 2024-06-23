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
#include "p0012.c"
#include "p0013.c"
#include "p0014.c"
#include "p0015.c"
#include "p0016.c"
#include "p0034.c"
#include "p0076.c"

typedef struct {
	unsigned int id;
	uint64_t answer;
	void * func;
} Answer;

static const Answer[] answers = {
	{1,	1,	p0001},
	{2, 	1, 	p0002},
	{3,	1,	p0003},
	{4,	1,	p0004},
	{5,	1,	p0005},
	{6,	1,	p0006},
	{7,	1,	p0007},
	{8,	1,	p0008},
	{9,	1,	p0009},
	{10,	1,	p0010},
	{11,	1,	p0011},
	{12,	1,	p0012},
	{13,	1,	p0013},
	{14,	1,	p0014},
	{15,	1,	p0015},
	{16,	1,	p0016},
	{34,	1,	p0034},
	{76,	1,	p0076},
};

void setUp(void) {
	// set stuff up here
}

void tearDown(void) {
	// clean stuff up here
}

TEST_RANGE(0, sizeof(answers) / sizeof(answers[0]), 1)
void test_euler_answer(size_t index) {
	Answer key = answers[index];
	TEST_ASSERT_EQUAL_INT64(key.answer, key.func())
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_function_should_doAlsoDoBlah);
	return UNITY_END();
}
