module ranges
    use constants
    implicit none
contains
    pure integer function range_entry3(start, step, idx) result(answer)
        integer, intent(in) :: start, step, idx
        answer = start + (step * idx)
    end function

    pure integer function range_entry4(start, end, step, idx) result(answer)
        integer, intent(in) :: start, end, step, idx
        integer :: length, l_idx

        l_idx = idx
        if (step > 0 .and. start < end) then
            length = 1 + (end - 1 - start) / step
        elseif (step < 0 .and. start > end) then
            length = 1 + (start - 1 - end) / (-step)
        else
            answer = huge(kind(answer))  ! error
            return
        end if

        if (l_idx < 0) then
            l_idx = length + l_idx
        end if

        if (l_idx < 0 .or. l_idx >= length) then
            answer = huge(kind(answer))  ! error
            return
        end if

        answer = range_entry3(start, step, l_idx)
    end function
end module ranges
