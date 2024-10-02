program test
    use constants
    use utils
    use problems

    implicit none

    call process_problems()

contains

    subroutine process_problems()
        type(AnswerT) :: expected, answer
        integer :: i, first_count, second_count, count_rate, count_max, tmp
        real :: time_elapsed

        ! Loop through each problem
        do i = 1, size(problem_ids)
            print *, "Processing Problem ID: ", problem_ids(i)
            if (is_slow(problem_ids(i))) then
                print *, "  This problem will take more than 60 seconds."
            end if
            expected = get_answer(problem_ids(i))
            call system_clock(first_count, count_rate, count_max)
            answer = run_problem(problem_ids(i))
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
                    if (expected%int_value /= answer%int_value) then
                        print *, "  Error: problem ", problem_ids(i), " failed!"
                        print *, "  Expected Answer  : ", expected%int_value
                        print *, "  Solution returned: ", answer%int_value
                        stop 1
                    end if
                case (stringt)
                    if (expected%string_value /= answer%string_value) then
                        print *, "  Error: problem ", problem_ids(i), " failed!"
                        print *, "  Expected Answer  : ", expected%string_value
                        print *, "  Solution returned: ", answer%string_value
                        stop 1
                    end if
                    deallocate(answer%string_value, expected%string_value)
                case (errort)
                    print *, "  Error retrieving answer!"
            end select
            tmp = second_count - first_count
            if (tmp < 0) then
                tmp = tmp + count_max
            end if
            time_elapsed = real(tmp) / real(count_rate)
            if (.NOT. is_slow(problem_ids(i)) .AND. time_elapsed > 60.0) then
                print *, "  Error: problem ", problem_ids(i), " timed out!"
                print *, "  Solution took    : ", time_elapsed, "s"
                stop 2
            end if
            print *, "  Completed        : ", problem_ids(i), "in ", time_elapsed, "s"
        end do
    end subroutine process_problems

end program test
