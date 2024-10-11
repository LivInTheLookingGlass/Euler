! Project Euler Problem 20
!
! Problem:
!
! n! means n × (n − 1) × ... × 3 × 2 × 1
!
! For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
! and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
!
! Find the sum of the digits in the number 100!

module Problem0020
    use constants
    implicit none
contains
    pure integer function p0020() result(answer)
        integer(i18t), dimension(10) :: numbers
        integer(i18t) :: power
        integer :: i, j
        
        power = 1
        answer = 0
        numbers = (/ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 /)
        do i = 2, 100
            do j = 1, size(numbers)
                numbers(j) = numbers(j) * i
            end do
            do j = 1, size(numbers) - 1
                if (numbers(j) > ten17) then
                    numbers(j + 1) = numbers(j + 1) + numbers(j) / ten17
                    numbers(j) = mod(numbers(j), ten17)
                end if
            end do
        end do
        do i = 1, 18
            do j = 1, size(numbers)
                answer = answer + mod((numbers(j) / power) , 10_i18t)
            end do
            power = power * 10
        end do
    end function p0020
end module Problem0020
