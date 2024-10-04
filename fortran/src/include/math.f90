module math
    use constants
    implicit none

contains

    pure integer(i18t) function factorial(n) result(answer)
        integer, intent(in) :: n
        integer :: i
        answer = 1
        do i = 2, n
            answer = answer * i
        end do
    end function

end module math

