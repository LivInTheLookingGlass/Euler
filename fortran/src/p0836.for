module Problem0836
    implicit none
contains
    character(14) function p0836() result(answer)
        answer = 'aprilfoolsjoke'
    end function p0836
end module Problem0836

program test0836
    use Problem0836
    print *, p0836()
end program test0836
