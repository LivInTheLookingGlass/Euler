! Project Euler Problem 3
!
! Problem:
!
! The prime factors of 13195 are 5, 7, 13 and 29.
!
! What is the largest prime factor of the number 600851475143 ?

module Problem0003
    use constants
    use primes
    implicit none
contains
    integer function p0003() result(answer)
        integer(i18t) :: num = 600851475143_i18t
        answer = 0
        do while (num > 1)
            call prime_factor(num, answer)
        end do
    end function p0003
end module Problem0003
