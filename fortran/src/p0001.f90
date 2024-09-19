! Project Euler Question 1
!
! I did it the old-fashioned way in this language
!
! Problem:
!
! If we list all the natural numbers below 10 that are multiples of 3 or 5, we
! get 3, 5, 6 and 9. The sum of these multiples is 23.
!
! Find the sum of all the multiples of 3 or 5 below 1000.

module Problem0001
    implicit none
contains
    integer function p0001() result(answer)
        integer :: i
        answer = 0

        do i = 3, 999, 3
            answer = answer + i
        end do

        do i = 5, 999, 5
            answer = answer + i
        end do

        do i = 15, 999, 15
            answer = answer - i
        end do
    end function p0001
end module Problem0001
