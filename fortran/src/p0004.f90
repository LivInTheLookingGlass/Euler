! Project Euler Problem 4
!
! I modeled this after the C++ solution, because it was by far the simplest
!
! Problem:
!

module Problem0004
    implicit none
contains
    integer function p0004() result(answer)
        integer :: i, j, k, prod, length
        logical :: is_palindrome
        character(len=8) :: string

        do i = 100, 999
            do j = 100, 999
                prod = i * j
                is_palindrome = .true.
                write(string, '(I0)') prod
                length = len(string)

                do k = 1, length
                    if (string(k) /= string(length - k + 1)) then
                        is_palindrome = .false.
                        exit
                    end if
                end do

                if (is_palindrome) then
                    answer = answer + prod
                end if
            end do
        end do
    end function p0004
end module Problem0004
