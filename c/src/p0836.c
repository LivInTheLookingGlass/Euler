/*
Project Euler Problem 836

Alright, this was funny

Problem:

Let A be an **affine plane** over a **radically integral local field** F with residual characteristic p.

We consider an **open oriented line section** U of A with normalized Haar measure m.

Define f(m,p) as the maximal possible discriminant of the **jacobian** associated to the
**orthogonal kernel embedding** of U into A.

Find f(20230401, 57). Give as your answer the concatenation of the first letters of each bolded word.
*/
#ifndef EULER_P0836
#define EULER_P0836
#include <stdio.h>

char *p0836() {
    return "aprilfoolsjoke";
}

#ifndef UNITY_END
int main(int argc, char const *argv[]) {
    printf("%s", p0836());
    return 0;
}
#endif
#endif
