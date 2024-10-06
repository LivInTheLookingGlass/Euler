module utils
    use constants
    implicit none

    type :: AnswerT
        integer(i18t) :: int_value
        character(len=ANSWERT_STR_SIZE), allocatable :: string_value
        integer(i1t) :: type
    end type AnswerT

    integer, private :: prev_unit = 13
    logical, private :: cache_inited = .false.
    type(AnswerT), private, dimension(1024) :: cached_answers
contains
    subroutine get_data_file(filename, contents)
        character(len=*), intent(in) :: filename
        character(len=*), intent(inout) :: contents
        character(len=64) :: line
        integer :: unit_number, iostat, file_size

        prev_unit = prev_unit + 1
        unit_number = prev_unit
        open(unit=unit_number, file=("../_data/" // filename), status='old', action='read', iostat=iostat)
        if (iostat /= 0) then
            print *, "Error opening file: ../_data/" // filename
            return
        end if

        inquire(unit=unit_number, size=file_size)
        if (file_size > 0) then
            contents = ''
            do
                read(unit_number, '(A)', iostat=iostat) line
                if (iostat /= 0) then
                    close(unit_number)
                    exit
                end if
                contents = contents // trim(line) // char(10)
            end do
        end if
        close(unit_number)
    end subroutine get_data_file

    function get_answer(id) result(answer)
        type(AnswerT) :: answer
        integer(i4t), intent(in) :: id
        integer(i18t) :: i, j
        integer :: ios, row_start, row_end, line_length
        character(len=ANSWERS_TSV_SIZE) :: text
        character(len=32) :: val
        character(len=4) :: id_, type_, length

        answer%type = errort
        answer%int_value = 0
        answer%string_value = ''

        if (id < 1 .or. id > size(cached_answers)) then
            print *, "Error: ID is out of bounds."
            return
        end if

        if (cache_inited) then
            answer = cached_answers(id)
            return
        end if

        do i=1, size(cached_answers)
            cached_answers(i)%type = errort
            cached_answers(i)%int_value = 0
            cached_answers(i)%string_value = ''
        end do

        call get_data_file("answers.tsv", text)
        row_start = 1
        line_length = 1
        do while (line_length > 0)
            line_length = index(text(row_start:), char(10))  ! Find the next line
            row_end = row_start + line_length - 1
            if (line_length > 0) then
                if (text(row_end:row_end) == char(13)) then  ! if \r
                    row_end = row_end - 1
                end if
                call parse_line(text(row_start:row_end), id_, type_, length, val)  ! Parse values
                if (id_ == "ID") then
                    row_start = row_start + line_length
                    cycle
                end if
                read(id_, *, iostat=ios) i
                if (ios /= 0) then
                    print *, "Invalid integer literal for id. Moving on without explicit error, but please debug this"
                end if
                select case (type_)
                    case ("int", "uint")
                        read(val, *, iostat=ios) j
                        if (ios /= 0) then
                            print *, "Invalid integer literal for value. Returning error type"
                        else
                            cached_answers(i)%type = int64t
                            cached_answers(i)%int_value = j
                        end if
                    case ("str")
                        cached_answers(i)%type = stringt
                        cached_answers(i)%string_value = trim(val)
                    case default
                        print *, "Invalid value type. Returning error type"
                    end select
                row_start = row_start + line_length  ! Move to the next line
            end if
        end do

        cache_inited = .true.
        answer = cached_answers(id)
    end function

    pure subroutine parse_line(line, id_out, type_out, length_out, value_out)
        character(len=*), intent(in) :: line
        character(len=32), intent(out) :: value_out
        character(len=4), intent(out) :: id_out, type_out, length_out
        integer :: pos, i, last_pos
    
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
                        if (len_trim(value_out) > 0) then
                            if (value_out(len_trim(value_out):len_trim(value_out)) == char(10)) then
                                value_out = value_out(1:len_trim(value_out) - 1)  ! strip \n
                            end if
                            if (value_out(len_trim(value_out):len_trim(value_out)) == char(13)) then
                                value_out = value_out(1:len_trim(value_out) - 1)  ! strip \r
                            end if
                        end if
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
