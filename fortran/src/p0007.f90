! Project Euler Problem 7
!
! Problem:
!
! By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that
! the 6th prime is 13.
!
! What is the 10 001st prime number?

module Problem0007
    use constants
    use primes
    implicit none
contains
    integer(i18t) function p0007() result(answer)
        integer :: i

        answer = 1
        call expand_sieve(2_i18t**17)
        do i = 1, 10001
            answer = next_prime(answer)
        end do
    end function p0007
end module Problem0007
