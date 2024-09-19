program test
  use Problem0001
  use Problem0002
  use Problem0006
  use Problem0009
  use Problem0836

  implicit none

  integer, dimension(:), allocatable :: problem_ids, answers
  logical, dimension(:), allocatable :: long_runtime
  integer :: num_problems

  allocate(problem_ids(num_problems), answers(num_problems), long_runtime(num_problems))

  problem_ids = (/ &
    001, &
    002, &
    006, &
    009, &
    836 &
  /)
  long_runtime = (/ &
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
    31875000, &
    0 &
  /)

  call process_problems(problem_ids, answers, long_runtime)
  deallocate(problem_ids, answers, long_runtime)

contains

  subroutine process_problems(problem_ids, answers, long_runtime)
    integer, dimension(:), intent(in) :: problem_ids
    integer, dimension(:), intent(in) :: answers
    logical, dimension(:), intent(in) :: long_runtime
    integer :: i, answer, first_count, second_count, count_rate, count_max, tmp
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
      end if
      tmp = second_count - first_count
      tmp = tmp % count_max
      time_elapsed = real(tmp)
      time_elapsed = time_elapsed / real(count_rate)
      if (.NOT. long_runtime(i) .AND. time_elapsed > 60.0) then
        print *, "  Error: problem ", problem_ids(i), " timed out!"
        print *, "  Solution took    : ", time_elapsed, "s"
      end if
      print *, "  Completed        : ", problem_ids(i), "in ", time_elapsed, "s"
    end do
  end subroutine process_problems

  integer function select_function(problem_id)
    integer, intent(in) :: problem_id
    character, dimension(:), allocatable :: str

    select case (problem_id)
      case (1)
        select_function = p0001()
      case (2)
        select_function = p0002()
      case (6)
        select_function = p0006()
      case (9)
        select_function = p0009()
      case (836)
        allocate(str(14))
        str = p0836()
        if ((str /= "aprilfoolsjoke")) then
          select_function = 0
        else
          select_function = -2
        end if
        deallocate(str)
      case default
        print *, "Unknown problem ID!"
        select_function = -1
    end select
  end function select_function

end program test
