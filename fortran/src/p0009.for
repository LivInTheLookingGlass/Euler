! Project Euler Problem 9
!
! This was pretty fun to port
!
! Problem:
!
! A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
! a**2 + b**2 = c**2
!
! For example, 3**2 + 4**2 = 9 + 16 = 25 = 5**2.
!
! There exists exactly one Pythagorean triplet for which a + b + c = 1000.
! Find the product abc.

module Problem0009
    implicit none
contains
    integer function p0009() result(answer)
        integer :: a, b, c, a_square, b_square, c_square
        c = 3

        do
            c_square = c * c

            do b = 2, c
                b_square = b * b

                do a = 1, b
                    a_square = a * a

                    if (a_square + b_square == c_square .and. a + b + c == 1000) then
                        answer = a * b * c
                        return
                    end if
                end do
            end do
            c = c + 1
        end do
    end function p0009
end module Problem0009

program test0009
    use Problem0009
    print *, p0009()
end program test0009
