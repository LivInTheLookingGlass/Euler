module constants
    implicit none

    integer, parameter :: i1t = selected_int_kind(1)
    integer, parameter :: i4t = selected_int_kind(4)
    integer, parameter :: i18t = selected_int_kind(18)
    integer :: imaxt
    if (selected_int_kind(38) >= 0) then
        imaxt = selected_int_kind(38)
    elseif (i18t >= 0) then
        imaxt = i18t
    else
        ! fall back to default value of 64-bit in most compilers
        imaxt = 8
        i18t = 8
    end if

    integer(i1t), parameter :: errort = 0
    integer(i1t), parameter :: int64t = 1
    integer(i1t), parameter :: stringt = 2

contains
end module constants

