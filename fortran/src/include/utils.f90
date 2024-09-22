module utils
    implicit none

    integer(kind=1), parameter :: errort = 0
    integer(kind=1), parameter :: int64t = 1
    integer(kind=1), parameter :: stringt = 2

    type :: AnswerT
        integer(kind=8) :: int_value
        character(len=:), allocatable :: string_value
        integer(kind=1) :: type
    end type AnswerT

contains
    function get_data_file(filename) result(contents)
        character(len=*), intent(in) :: filename
        character(len=:), allocatable :: contents
        character(len=64) :: line
        integer :: unit_number, iostat, file_size

        open(newunit=unit_number, file=("../_data/" // filename), status='old', action='read', iostat=iostat)
        if (iostat /= 0) then
            print *, "Error opening file: ../_data/" // filename
            contents = ''
            return
        end if

        inquire(unit=unit_number, size=file_size)
        if (file_size > 0) then
            allocate(character(len=file_size) :: contents)
            contents = ''
            do
                read(unit_number, '(A)', iostat=iostat) line
                if (iostat /= 0) then
                    close(unit_number)
                    exit
                end if
                contents = contents // trim(line) // char(10)
            end do
        else
            contents = ''
        end if
        close(unit_number)
    end function get_data_file

    function get_answer(id) result(answer)
        type(AnswerT) :: answer
        integer(kind=4), intent(in) :: id
        integer(kind=4) :: ios, row_start, row_end, line_length
        integer(kind=8) :: i
        character(len=:), allocatable :: text
        character(len=32) :: val
        character(len=4) :: id_, type_, length

        text = get_data_file("answers.tsv")
        if (.not. allocated(text)) then
            text = ''  ! Ensure text is defined if allocation failed
        end if
        row_start = 1
        line_length = 1
        answer%type = errort
        answer%int_value = 0
        answer%string_value = ''
        do while (line_length > 0)
            line_length = index(text(row_start:), char(10))  ! Find the next line
            print *, line_length
            row_end = row_start + line_length - 1
            if (line_length > 0) then
                if (text(row_end:row_end) == char(13)) then  ! if \r
                    row_end = row_end - 1
                end if
                print *, text(row_start:row_end)
                call parse_line(text(row_start:row_end), id_, type_, length, val)  ! Parse values
                print *, id_, type_, length, val
                if (id_ == "ID") then
                    row_start = row_start + line_length
                    cycle
                end if
                read(id_, *, iostat=ios) i
                if (ios /= 0) then
                    print *, "Invalid integer literal for id. Moving on without explicit error, but please debug this"
                elseif (i == id) then
                    select case (type_)
                        case ("int", "uint")
                            read(val, *, iostat=ios) i
                            if (ios /= 0) then
                                print *, "Invalid integer literal for value. Returning error type"
                            else
                                answer%type = int64t
                                answer%int_value = i
                            end if
                        case ("str")
                            allocate(character(len=len(val)) :: answer%string_value)
                            if (.not. allocated(answer%string_value)) then
                                print *, "Memory allocation failed for string_value. Returning error type"
                            else
                                answer%type = stringt
                                answer%string_value = val
                            end if
                        case default
                            print *, "Invalid value type. Returning error type"
                        end select
                        return
                end if
                row_start = row_start + line_length  ! Move to the next line
            end if
        end do

        deallocate(text)
    end function

    subroutine parse_line(line, id_out, type_out, length_out, value_out)
        character(len=*), intent(in) :: line
        character(len=32), intent(out) :: value_out
        character(len=4), intent(out) :: id_out, type_out, length_out
        integer :: pos, last_pos, i
    
        id_out = ''
        type_out = ''
        length_out = ''
        value_out = ''
        last_pos = 0
    
        do i = 1, 4
            pos = index(line(last_pos + 1:), char(9))  ! Find tab character
            if (pos == 0) then  ! Tab not found, assign remaining part to the last variable
                select case (i)
                    case (1)
                        id_out = trim(line(last_pos + 1:))
                    case (2)
                        type_out = trim(line(last_pos + 1:))
                    case (3)
                        length_out = trim(line(last_pos + 1:))
                    case (4)
                        value_out = trim(line(last_pos + 1:))
                end select
                return
            else
                select case (i)
                    case (1)
                        id_out = trim(line(last_pos + 1:last_pos + pos - 1))
                    case (2)
                        type_out = trim(line(last_pos + 1:last_pos + pos - 1))
                    case (3)
                        length_out = trim(line(last_pos + 1:last_pos + pos - 1))
                end select
                last_pos = last_pos + pos
            end if
        end do
    end subroutine parse_line
    
end module utils

