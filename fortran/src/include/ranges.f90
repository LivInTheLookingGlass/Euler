module ranges
    use constants
    implicit none

contains

    integer function range_entry3(start, step, idx) result(answer)
        integer, intent(in) :: start, step, idx
        answer = start + (step * idx)
    end function

    integer function range_entry4(start, stop, step, idx) result(answer)
        integer, intent(in) :: start, stop, step, idx
        integer :: length

        if (step > 0 .and. start < stop) then
            length = 1 + (stop - 1 - start) / step
        elseif (step < 0 .and. start > stop) then
            length = 1 + (start - 1 - stop) / (-step)
        end if

        if (idx < 0) then
            idx = length + idx
        end if

        if (idx < 0 .or. idx >= length) then
            answer = huge(kind(answer))  ! error
            return
        end if

        answer = range_entry3(start, step, idx)
    end function

end module ranges

