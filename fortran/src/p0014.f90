! Project Euler Problem 14
!
! Problem:
!
! The following iterative sequence is defined for the set of positive integers:
!
! n → n/2 (n is even)
! n → 3n + 1 (n is odd)
!
! Using the rule above and starting with 13, we generate the following sequence:
! 13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
!
! It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been
! proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.
!
! Which starting number, under one million, produces the longest chain?
!
! NOTE: Once the chain starts the terms are allowed to go above one million.

module Problem0014
    use constants
    implicit none
    integer, parameter :: collatz_cache_size = 1000000
contains
    integer(i18t) function p0014() result(answer)
        integer, dimension(collatz_cache_size), allocatable :: collatz_len_cache
        integer(i18t) :: test
        integer :: tmp, length = 2
        allocate(collatz_len_cache(collatz_cache_size))
        if (.not. allocated(collatz_len_cache)) then
            print *, "Allocation of collatz length cache failed. Stopping run."
            stop ERROR_PROB_ALLOCATE_FAILED
        end if
        collatz_len_cache = 0
        collatz_len_cache(1) = 1
        answer = 2
        do test = 3, 999999
            call collatz_len(tmp, test, collatz_len_cache)
            if (tmp > length) then
                answer = test
                length = tmp
            end if
        end do
    end function p0014

    recursive subroutine collatz_len(answer, n, collatz_len_cache)
        integer(i18t), intent(in) :: n
        integer, intent(out) :: answer
        integer, intent(inout), dimension(:) :: collatz_len_cache
        if (n < collatz_cache_size .and. collatz_len_cache(int(n)) /= 0) then
            answer = collatz_len_cache(int(n))
            return
        end if
        answer = 0
        if (mod(n, 2_i18t) == 1) then
            call collatz_len(answer, (3 * n + 1) / 2, collatz_len_cache)
            answer = answer + 2
        else
            call collatz_len(answer, n / 2, collatz_len_cache)
            answer = answer + 1
        end if
        if (n < collatz_cache_size) then
            collatz_len_cache(int(n)) = answer
        end if
    end subroutine
end module Problem0014
