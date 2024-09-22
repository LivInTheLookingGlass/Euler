program test
    use utils
    use Problem0001
    use Problem0002
    use Problem0006
    use Problem0008
    use Problem0009
    use Problem0011
    use Problem0836

    implicit none
    integer(kind=4), dimension(:), allocatable :: problem_ids
    logical(kind=1), dimension(:), allocatable :: long_runtime
    integer :: num_problems
    
    num_problems = 7
    allocate(problem_ids(num_problems))
    allocate(long_runtime(num_problems))
    problem_ids = (/ &
        001, &
        002, &
        006, &
        008, &
        009, &
        011, &
        836 &
    /)
    long_runtime = (/ &
        .false., &
        .false., &
        .false., &
        .false., &
        .false., &
        .false., &
        .false. &
    /)

    call process_problems(problem_ids, long_runtime)
    deallocate(problem_ids, long_runtime)

contains

    subroutine process_problems(problem_ids, long_runtime)
        integer(kind=4), dimension(:), intent(in) :: problem_ids
        logical(kind=1), dimension(:), intent(in) :: long_runtime
        type(AnswerT) :: expected, answer
        integer(kind=4) :: i
        integer :: first_count, second_count, count_rate, count_max, tmp
        real :: time_elapsed

        ! Loop through each problem
        do i = 1, size(problem_ids)
            print *, "Processing Problem ID: ", problem_ids(i)
            if (long_runtime(i)) then
                print *, "  This problem will take more than 60 seconds."
            end if
            expected = get_answer(i)
            call system_clock(first_count, count_rate, count_max)
            answer = select_function(problem_ids(i))
            call system_clock(second_count, count_rate, count_max)
            if (expected%type /= answer%type) then
                print *, "  Error: type mismatch between expected answer and returned value"
                select case (answer%type)
                    case (int64t)
                        print *, "  Returned: int (", answer%int_value, ")"
                    case (stringt)
                        print *, "  Returned: string (" // answer%string_value // ")"
                    case (errort)
                        print *, "  Returned: error"
                end select
                select case (expected%type)
                    case (int64t)
                        print *, "  Expected: int (", expected%int_value, ")"
                    case (stringt)
                        print *, "  Expected: string (" // expected%string_value // ")"
                    case (errort)
                        print *, "  Expected: error"
                end select
                stop 3
            end if
            select case(expected%type)
                case (int64t)
                    if (expected%int_value /= answer) then
                        print *, "  Error: problem ", problem_ids(i), " failed!"
                        print *, "  Expected Answer  : ", expected%int_value
                        print *, "  Solution returned: ", answer
                        stop 1
                    end if
                case (stringt)
                    if (expected%string_value /= answer) then
                        print *, "  Error: problem ", problem_ids(i), " failed!"
                        print *, "  Expected Answer  : ", expected%string_value
                        print *, "  Solution returned: ", answer
                        deallocate(answer, expected%string_value)
                        stop 1
                    end if
                    deallocate(answer, expected%string_value)
                case (errort)
                    print *, "  Error retrieving answer!"
            end select
            tmp = second_count - first_count
            if (tmp < 0) then
                tmp = tmp + count_max
            end if
            time_elapsed = real(tmp) / real(count_rate)
            if (.NOT. long_runtime(i) .AND. time_elapsed > 60.0) then
                print *, "  Error: problem ", problem_ids(i), " timed out!"
                print *, "  Solution took    : ", time_elapsed, "s"
                stop 2
            end if
            print *, "  Completed        : ", problem_ids(i), "in ", time_elapsed, "s"
        end do
    end subroutine process_problems

    type(AnswerT) function select_function(problem_id) result(answer)
        integer(kind=4), intent(in) :: problem_id

        answer%type = int64t
        select case (problem_id)
            case (1)
                answer%int_value = p0001()
            case (2)
                answer%int_value = p0002()
            case (6)
                answer%int_value = p0006()
            case (8)
                answer%int_value = p0008()
            case (9)
                answer%int_value = p0009()
            case (11)
                answer%int_value = p0011()
            case (836)
                allocate(character(len=14) :: answer%string_value)
                if (.not. allocated(answer%string_value)) then
                    print *, "  Memory allocation failed for string_value. Returning error type"
                    answer%type = errort
                else
                    answer%type = stringt
                    answer%string_value = p0836()
                end if
            case default
                print *, "Unknown problem ID!"
                answer%type = errort
        end select
    end function select_function

end program test
