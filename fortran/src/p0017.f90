! Project Euler Problem 17
!
! The key here was remembering I don't need to return the whole string, just the length
!
! Problem:
!
! If the numbers 1 to 5 are written out in words: one, two, three, four, five,
! then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
!
! If all the numbers from 1 to 1000 (one thousand) inclusive were written out in
! words, how many letters would be used?
!
! NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and
! forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20
! letters. The use of "and" when writing out numbers is in compliance with
! British usage.

module Problem0017
    implicit none
contains
    pure integer recursive function to_string_len(n) result(answer)
        integer, intent(in) :: n
        integer :: tmp
        answer = 0
        if (n >= 1000) then
            answer = to_string_len(mod(n / 1000, 100)) + 8
            tmp = mod(n, 1000)
            if (tmp /= 0) then
                answer = answer + to_string_len(tmp)
            end if

        elseif (n >= 100) then
            answer = to_string_len(mod(n / 100, 10)) + 7
            tmp = mod(n, 100)
            if (tmp /= 0) then
                answer = answer + 3 + to_string_len(tmp)
            end if

        elseif (n >= 20) then
            select case (n / 10)
                case (4, 5, 6)
                    answer = 5
                case (2, 3, 8, 9)
                    answer = 6
                case (7)
                    answer = 7
            end select

            tmp = mod(n, 10)
            if (tmp /= 0) then
                answer = answer + to_string_len(tmp)
            end if

        else
            select case (n)
                case (1, 2, 6, 10)
                    answer = 3
                case (0, 4, 5, 9)
                    answer = 4
                case (3, 7, 8)
                    answer = 5
                case (11, 12)
                    answer = 6
                case (15, 16)
                    answer = 7
                case (13, 14, 18, 19)
                    answer = 8
                case (17)
                    answer = 9
            end select
        end if
    end function

    pure integer function p0017() result(answer)
        integer :: x

        answer = 0
        do x = 1, 1000
            answer = answer + to_string_len(x)
        end do
    end function p0017
end module Problem0017
