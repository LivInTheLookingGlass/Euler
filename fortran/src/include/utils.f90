module utils
    implicit none

    contains
        function get_data_file(filename) result(contents)
        character(len=*), intent(in) :: filename
        character(len=:), allocatable :: contents
        integer :: unit_number, iostat, file_size

        filename = "../_data/" // filename

        ! Open the file in read mode
        open(newunit=unit_number, file=filename, status='old', action='read', iostat=iostat)
        if (iostat /= 0) then
            print *, "Error opening file: ", filename
            contents = ''
            return
        end if

        ! Move to the end of the file to get the size
        inquire(unit=unit_number, size=file_size)

        allocate(character(len=file_size) :: contents)
        read(unit_number, '(A)') contents
        close(unit_number)
    end function get_data_file

end module utils

! program test_get_data_file
!     use utils
!     implicit none
!     character(len=:), allocatable :: file_contents
!     file_contents = get_data_file('yourfile.txt')
!     print *, file_contents
! end program test_get_data_file
