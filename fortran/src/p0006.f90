! Project Euler Problem 6
!
! This turned out to be really easy
!
! Problem:
!
! The sum of the squares of the first ten natural numbers is,
! 1**2 + 2**2 + ... + 10**2 = 385
!
! The square of the sum of the first ten natural numbers is,
! (1 + 2 + ... + 10)**2 = 55**2 = 3025
!
! Hence the difference between the sum of the squares of the first ten natural
! numbers and the square of the sum is 3025 − 385 = 2640.
!
! Find the difference between the sum of the squares of the first one hundred
! natural numbers and the square of the sum.

module Problem0006
    implicit none
contains
    pure integer function p0006() result(answer)
        integer :: sum = 1, sum_of_squares = 1, i
        answer = 0

        do i = 2, 100
            sum = sum + i
            sum_of_squares = sum_of_squares + i * i
        end do

        answer = sum * sum - sum_of_squares
    end function p0006
end module Problem0006
