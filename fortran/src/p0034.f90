! Project Euler Problem 34
!
! This ended up being a filtering problem. The problem with my solution is that I
! am not satisfied with my filter at all. I feel like there is a more efficient
! way to go about it.
!
! Problem:
!
! 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
!
! Find the sum of all numbers which are equal to the sum of the factorial of
! their digits.
!
! Note: as 1! = 1 and 2! = 2 are not sums they are not included.

module Problem0034
    use constants
    use math
    implicit none
contains

    integer(i18t) function p0034() result(answer)
        integer :: i, j
        integer(i18t) tmp
        character(len=5) string

        answer = 0
        do i = 10, 99999
            tmp = 0
            write(string, '(I0)') i

            do j = 1, len_trim(string)
                tmp = tmp + factorial(ichar(string(j:j)) - ichar('0'))
            end do

            if (tmp == i) then
                answer = answer + i
            end if
        end do
    end function p0034
end module Problem0034
