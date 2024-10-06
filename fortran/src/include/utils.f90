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
    type(AnswerT) function get_answer(id) result(answer)
        integer(i4t), intent(in) :: id

        if (id < 1 .or. id > size(cached_answers)) then
            print *, "Error: ID is out of bounds."
            answer = AnswerT(0, '', errort)
            return
        end if

        if (.not. cache_inited) then
            call init_answer_cache()
        end if

        answer = cached_answers(id)
    end function

    subroutine init_answer_cache()
        character(len=64) :: line
        character(len=32) :: val
        character(len=4) :: id_, type_, length
        integer(i18t) :: i, j
        integer :: ios, line_length, unit_number

        cached_answers = AnswerT(0, '', errort)
        do i=1, size(cached_answers)
        end do

        unit_number = prev_unit + 1
        prev_unit = unit_number
        open(unit=unit_number, file=("../_data/answers.tsv"), status='old', action='read', iostat=ios)
        if (ios /= 0) then
            print *, "Error opening file: ../_data/answers.tsv"
            return
        end if

        line_length = 1
        do while (line_length > 0)
            line = ''
            read(unit_number, '(A)', iostat=ios) line
            if (ios /= 0) then
                close(unit_number)
                exit
            end if

            line = trim(line)
            line_length = len(line)
            if (line_length > 0) then
                call parse_line(line, id_, type_, length, val)  ! Parse values
                if (id_ == "ID") then
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
            end if
        end do

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
