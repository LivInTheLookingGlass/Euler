module constants
    implicit none

    ! kinds
    integer, parameter :: i1t = selected_int_kind(1)
    integer, parameter :: i2t = selected_int_kind(2)
    integer, parameter :: i4t = selected_int_kind(4)
    integer, parameter :: i18t = selected_int_kind(18)

    ! type codes
    integer(i1t), parameter :: errort = 0
    integer(i1t), parameter :: int64t = 1
    integer(i1t), parameter :: stringt = 2

    ! error codes
    integer, parameter :: ERROR_ANSWER_MISMATCH = 1
    integer, parameter :: ERROR_ANSWER_TIMEOUT = 2
    integer, parameter :: ERROR_ANSWER_TYPE_MISMATCH = 3
    integer, parameter :: ERROR_ALLOCATE_FAILED = 4
    integer, parameter :: ERROR_FILE_READ_FAILED = 5

    ! file/string sizes
    integer, parameter :: DATA_MAX_NAME_SIZE = 32
    integer, parameter :: ANSWERT_STR_SIZE = 16

    ! misc
    integer, parameter :: MAX_FACTORIAL_64 = 20
    integer(i18t), parameter :: ten16 = 10000000000000000_i18t
    integer(i18t), parameter :: ten17 = 100000000000000000_i18t
end module constants

