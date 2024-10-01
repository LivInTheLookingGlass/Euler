! Project Euler Problem 76
!
! I ended up having to do this iteratively, which I'm not super happy with. I feel like there is almost certainly a
! closed-form solution to this, but I was unable to figure it out.
!
! Revision 1:
!
! Have counts store values instead of numeral counts to shave a few seconds off
!
! Revision 2:
!
! Manually expand the sum loop in the preprocessor to try and get TCC output to be faster. Shaved a ~1/3 of runtime in
! both CL and GCC in my initial testing.
!
! Revision 3:
!
! After testing on non-Windows systems, I found that Revision 2 royally borked it up. I reverted this, then applied an
! optimization I found earlier today. The number of solutions to a + 2b + n = 100, where a, b, n in [0, 100] is
! (100 - n) / 2 + 1. This brought runtime on TCC from ~3min -> ~1min and clang from ~6s -> ~2s. 
!
! Revision 4:
!
! Repeat an earlier optimization for the 2s case, so now it tries to keep the 2s value as close to the missing piece as
! possible, cutting out a lot of useless loops. Runtime is approximately halved on TCC.
!
! Problem:
!
! It is possible to write five as a sum in exactly six different ways:
!
! 4 + 1
! 3 + 2
! 3 + 1 + 1
! 2 + 2 + 1
! 2 + 1 + 1 + 1
! 1 + 1 + 1 + 1 + 1
!
! How many different ways can one hundred be written as a sum of at least two
! positive integers?

module Problem0076
    use constants
    implicit none
contains

    integer function p0076() result(answer)
        integer :: idx, i, sum
        integer, dimension(100) :: counts
        sum = 100
        answer = 0
        counts = 0
        counts(2) = 100
        do while (counts(100) == 0)
            counts(2) = counts(2) + 2
            if (sum >= 100) then
                answer = answer + (100 + counts(2) - sum) / 2
                idx = 2
                sum = 101  ! because no do-while loops
                do while (sum > 100)
                    counts(idx) = 0
                    idx = idx + 1
                    counts(idx) = counts(idx) + idx
                    sum = counts(2)
                    do i = 3, 99
                        sum = sum + counts(i)
                    end do
                end do
                counts(2) = 100 - sum - mod(sum, 2)
            end if
            sum = counts(2)
            do i = 3, 99
                sum = sum + counts(i)
            end do
        end do
    end function p0076
end module Problem0076
