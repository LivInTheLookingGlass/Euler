! Project Euler Problem 16
!
! Problem:
!
! 2**15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
!
! What is the sum of the digits of the number 2**1000?

module Problem0016
    use constants
    implicit none
    integer(i18t), parameter :: ten17 = 100000000000000000_i18t
contains
    pure integer(i18t) function p0016() result(answer)
        integer(i18t), dimension(18) :: numbers
        integer(i18t) :: power
        integer :: i, j

        numbers = 0
        numbers(1) = 1
        do i = 1, 1000
            do j = 1, size(numbers)
                numbers(j) = numbers(j) * 2
            end do
            do j = 1, size(numbers) - 1
                if (numbers(j) > ten17) then
                    numbers(j + 1) = numbers(j + 1) + numbers(j) / ten17;
                    numbers(j) = mod(numbers(j), ten17)
                end if
            end do
        end do
        answer = 0
        power = 1
        do i = 1, 18
            do j = 1, size(numbers)
                answer = answer + mod((numbers(j) / power), 10_i18t)
            end do
            power = power * 10
        end do
    end function p0016
end module Problem0016
