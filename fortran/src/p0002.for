module Problem0002
    implicit none
contains
    integer function p0002() result(answer)
        integer :: a
        integer :: b
        integer :: i
        integer :: tmp
        answer = 0
        a = 1
        b = 2

        do while (b < 4000000)
            answer = answer + b

            do i = 1, 3
                tmp = b
                b = a + b
                a = tmp
            end do
        end do
    end function p0002
end module Problem0002

program test0002
    use Problem0002
    print *, p0002()
end program test0002
