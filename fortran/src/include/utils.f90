module utils
    use constants
    implicit none

    type :: AnswerT
        integer(i18t) :: int_value
        character(len=ANSWERT_STR_SIZE) :: string_value
        integer(i1t) :: type
    end type AnswerT

    integer, private :: prev_unit = 13
    logical, private :: cache_inited = .false.
    type(AnswerT), private, dimension(1024) :: cached_answers
contains
    function get_data_file(filename) result(contents)
        character(len=*), intent(in) :: filename
        character(len=:), allocatable :: contents
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
            allocate(character(len=file_size) :: contents)
            if (.not. allocated(contents)) then
                print *, "Failed to allocate memory for read. Exiting."
                stop ERROR_UTILS_ALLOCATE_FAILED
            end if
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
        if (.not. allocated(contents)) then
            contents = ''
        end if
    end function get_data_file

    type(AnswerT) function get_answer(id) result(answer)
        integer(i4t), intent(in) :: id

        if (id < 1 .or. id > size(cached_answers)) then
            print *, "Error: ID is out of bounds."
            answer%type = errort
            return
        end if

        if (.not. cache_inited) then
            call init_answer_cache()
        end if

        answer = cached_answers(id)
    end function

    subroutine init_answer_cache()
        integer(i18t) :: i, j
        integer :: ios, row_start, row_end, line_length
        character(len=:), allocatable :: text
        character(len=32) :: val
        character(len=4) :: id_, type_, length

        do i=1, size(cached_answers)
            cached_answers(i)%type = errort
        end do

        text = get_data_file("answers.tsv")
        if (.not. allocated(text)) then
            text = ''  ! Ensure text is defined if allocation failed
        end if
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

        deallocate(text)
        cache_inited = .true.
    end subroutine

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
