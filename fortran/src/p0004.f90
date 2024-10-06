! Project Euler Problem 4
!
! I modeled this after the C++ solution, because it was by far the simplest
!
! Problem:
!
! A palindromic number reads the same both ways. The largest palindrome made from
! the product of two 2-digit numbers is 9009 = 91 × 99.
!
! Find the largest palindrome made from the product of two 3-digit numbers.

module Problem0004
    implicit none
contains
    pure integer function p0004() result(answer)
        integer :: i, j, k, n, prod, length
        logical :: is_palindrome
        character(len=8) :: string

        answer = 0
        do i = 100, 999
            do j = 100, 999
                prod = i * j
                is_palindrome = .true.
                write(string, '(I0)') prod
                length = len_trim(string)

                do k = 1, length
                    n = length - k + 1
                    if (string(k:k) /= string(n:n)) then
                        is_palindrome = .false.
                        exit
                    end if
                end do

                if (is_palindrome) then
                    answer = max(answer, prod)
                end if
            end do
        end do
    end function p0004
end module Problem0004
