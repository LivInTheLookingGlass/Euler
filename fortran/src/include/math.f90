module math
    use constants
    implicit none
contains
    pure integer(i18t) function factorial(n) result(answer)
        integer, intent(in) :: n
        integer :: i
        answer = 1
        do i = 2, n
            answer = answer * i
        end do
    end function

    pure integer(i18t) function n_choose_r(n, r) result(answer)
        integer, intent(in) :: n, r
        if (n <= MAX_FACTORIAL_64) then
            answer = factorial(n) / factorial(r) / factorial(n-r)  ! fast path if small enough
        else
            answer = n_choose_r_slow(n, r)  ! slow path for larger numbers
        end if
    end function

    integer(i18t) function n_choose_r_slow(n, r) result(answer)
        integer, intent(in) :: n, r
        integer(i2t), allocatable :: factors(:)
        integer(i18t) :: tmp
        integer :: i, j
        allocate(factors(n))
        if (.not. allocated(factors)) then
            print *, "n_choose_r allocation failed. Exiting."
            stop ERROR_ALLOCATE_FAILED
        end if
        factors = 0
        ! collect factors of final number
        do i = 2, n
            factors(i) = 1
        end do
        ! negative factor values indicate need to divide
        do i = 2, r
            factors(i) = factors(i) - 1_i2t
        end do
        do i = 2, n - r
            factors(i) = factors(i) - 1_i2t
        end do
        do i = n, 2, -1  ! this loop reduces to prime factors only
            do j = 2, i - 1
                if (mod(i, j) == 0) then
                    factors(j) += factors(i)
                    factors(i / j) += factors(i)
                    factors(i) = 0;
                    exit
                end if
            end do
        end do
        i = 2
        j = 2
        answer = 1
        do while (i <= n)
            do while (factors(i) > 0)
                tmp = answer
                answer = answer * i
                do while (answer < tmp .and. j <= n)
                    do while (factors(j) < 0)
                        tmp = tmp / j
                        factors(j) = factors(j) + 1_i2t
                    end do
                    j = j + 1_i2t
                    answer = tmp * i
                end do
                if (answer < tmp) then
                    answer = -1  ! this indicates an overflow
                    return
                end if
                factors(i) = factors(i) - 1_i2t
            end do
            i = i + 1_i2t
        end do
        do while (j <= n)
            do while (factors(j) < 0)
                answer = answer / j
                factors(j) = factors(j) + 1_i2t
            end do
            j = j + 1_i2t
        end do
        deallocate(factors)
    end function
end module math

