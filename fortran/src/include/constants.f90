module constants
    implicit none

    integer, parameter :: i1t = selected_int_kind(1)
    integer, parameter :: i4t = selected_int_kind(4)
    integer, parameter :: i19t = selected_int_kind(19)

    integer(i1t), parameter :: errort = 0
    integer(i1t), parameter :: int64t = 1
    integer(i1t), parameter :: stringt = 2

contains
end module constants

