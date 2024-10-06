! Project Euler Problem 10
!
! Problem:
!
! The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
!
! Find the sum of all the primes below two million.

module Problem0010
    use constants
    use primes
    implicit none
contains
    integer(i18t) function p0010() result(answer)
        integer(i18t) :: tmp

        answer = 0
        tmp = 0
        do while (tmp < 2000000)
            tmp = next_prime(tmp)
            answer = answer + tmp
        end do
    end function p0010
end module Problem0010
