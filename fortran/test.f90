program test
    use Problem0001
    use Problem0002
    use Problem0006
    use Problem0008
    use Problem0009
    use Problem0011
    use Problem0836

    implicit none
    integer(kind=2), dimension(:), allocatable :: problem_ids
    integer(kind=8), dimension(:), allocatable :: answers
    logical(kind=1), dimension(:), allocatable :: long_runtime
    integer :: num_problems
    
    num_problems = 7
    allocate(problem_ids(num_problems), answers(num_problems), long_runtime(num_problems))
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
    answers = (/ &
        233168, &
        4613732, &
        25164150, &
        23514624000, &
        31875000, &
        70600674, &
        0 &
    /)

    call process_problems(problem_ids, answers, long_runtime)
    deallocate(problem_ids, answers, long_runtime)

contains

    subroutine process_problems(problem_ids, answers, long_runtime)
        integer(kind=2), dimension(:), intent(in) :: problem_ids
        integer(kind=8), dimension(:), intent(in) :: answers
        logical(kind=1), dimension(:), intent(in) :: long_runtime
        integer(kind=8) :: answer
        integer(kind=2) :: i
        integer :: first_count, second_count, count_rate, count_max, tmp
        real :: time_elapsed

        ! Loop through each problem
        do i = 1, size(problem_ids)
            print *, "Processing Problem ID: ", problem_ids(i)
            if (long_runtime(i)) then
                print *, "  This problem will take more than 60 seconds."
            end if
            call system_clock(first_count, count_rate, count_max)
            answer = select_function(problem_ids(i))
            call system_clock(second_count, count_rate, count_max)
            if (answers(i) /= answer) then
                print *, "  Error: problem ", problem_ids(i), " failed!"
                print *, "  Expected Answer  : ", answers(i)
                print *, "  Solution returned: ", answer
                stop 1
            end if
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

    integer(kind=8) function select_function(problem_id)
        integer(kind=2), intent(in) :: problem_id
        character(len=14) :: str

        select case (problem_id)
            case (1)
                select_function = p0001()
            case (2)
                select_function = p0002()
            case (6)
                select_function = p0006()
            case (8)
                select_function = p0008()
            case (9)
                select_function = p0009()
            case (11)
                select_function = p0011()
            case (836)
                str = p0836()
                if ((str == "aprilfoolsjoke")) then
                    select_function = 0
                else
                    print *, "  Solution returned: ", str
                    select_function = -2
                end if
            case default
                print *, "Unknown problem ID!"
                select_function = -1
        end select
    end function select_function

end program test
