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
        integer :: i, j, k
        answer = 1
        factor_tracker = 0
        local_factor_tracker = 0
        do i = 2, 20
            j = i
            do while (j > 1)
                call prime_factor(j, k)
                local_factor_tracker(k) = local_factor_tracker(k) + 1
            end do
            do i = 2, 19
                factor_tracker(i) = max(factor_tracker(i), local_factor_tracker(i))
                local_factor_tracker(i) = 0
            end do
        end do
        do i = 2, 19
            do j = 1, factor_tracker(i)
                answer = answer * i
            end do
        end do
    end function p0005
end module Problem0005
