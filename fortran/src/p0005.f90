! Project Euler Problem 5
!
! I modeled this after the C++ solution, because it was by far the simplest
!
! Problem:
!
! A palindromic number reads the same both ways. The largest palindrome made from
! the product of two 2-digit numbers is 9009 = 91 × 99.
!
! Find the largest palindrome made from the product of two 3-digit numbers.

module Problem0005
    use constants
    use primes
    implicit none
contains
    integer function p0005() result(answer)
        integer(i2t), dimension(20) :: factor_tracker, local_factor_tracker
        integer(i18t) :: p, q
        integer :: i, j
        answer = 1
        factor_tracker = 0
        local_factor_tracker = 0
        do i = 2, 20
            q = i
            do while (q > 1)
                call prime_factor(q, p)
                local_factor_tracker(p) = local_factor_tracker(p) + 1
            end do
            do j = 2, 19
                factor_tracker(j) = max(factor_tracker(j), local_factor_tracker(j))
                local_factor_tracker(j) = 0
            end do
        end do
        do i = 2, 19
            do j = 1, factor_tracker(i)
                answer = answer * i
            end do
        end do
    end function p0005
end module Problem0005
