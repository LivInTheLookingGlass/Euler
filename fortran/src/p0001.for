module Problem0001
    implicit none
contains
    integer function p0001() result(answer)
        integer :: i
        answer = 0

        do i = 3, 1000, 3
            answer = answer + i
        end do

        do i = 5, 1000, 5
            answer = answer + i
        end do

        do i = 15, 1000, 15
            answer = answer - i
        end do
    end function p0001
end module Problem0001

program test0001
    use Problem0001
    print *, p0001()
end program test0001
