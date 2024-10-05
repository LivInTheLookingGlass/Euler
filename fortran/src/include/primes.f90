module primes
    use constants
    implicit none
    integer, private, parameter :: bits_per_int = 64
    integer(i18t), private, allocatable :: prime_sieve(:)
    integer(i18t), private :: current_n = 0
contains
    subroutine sieve_up_to(n)
        integer(i18t), intent(in) :: n
        integer(i18t) :: p, i

        do p = 2, n
            if (get_prime_bit(p)) then
                do i = p * p, n, p
                    call clear_prime_bit(i)
                end do
            end if
        end do
    end subroutine sieve_up_to

    recursive integer(i18t) function next_prime(last) result(ret)
        integer(i18t), intent(in) :: last
        integer(i18t) :: next

        do next = last + 1, current_n
            if (get_prime_bit(next)) then
                ret = next
                return
            end if
        end do

        call expand_sieve()
        ret = next_prime(next)
    end function next_prime

    subroutine expand_sieve(potential_n)
        integer(i18t), intent(in), optional :: potential_n
        integer(i18t) :: new_size, new_n

        if (present(potential_n)) then
            new_n = potential_n
        else
            new_n = current_n * 2
        end if

        if (new_n <= current_n) then
            return
        endif

        new_size = (new_n / bits_per_int) + 1
        ! recalculate n to fit boundaries
        new_n = bits_per_int * (new_size - 1)
        if (allocated(prime_sieve)) then
            deallocate(prime_sieve)
        end if
        allocate(prime_sieve(new_size))
        if (.not. allocated(prime_sieve)) then
            print *, "Memory allocation failed for prime sieve. Exiting."
            stop ERROR_PRIME_ALLOCATE_FAILED
        end if
        prime_sieve = -1
        call clear_prime_bit(0_i18t)
        call clear_prime_bit(1_i18t)
        call sieve_up_to(new_n)
        current_n = new_n
    end subroutine expand_sieve

    ! Function to set a bit to 0
    subroutine clear_prime_bit(num)
        integer(i18t), intent(in) :: num
        integer(i18t) :: i
        i = (num / bits_per_int) + 1
        prime_sieve(i) = iand(prime_sieve(i), ieor(-1_i18t, 2**int(mod(num, bits_per_int), kind(prime_sieve(1)))))
    end subroutine clear_prime_bit

    ! Function to check if a bit is set
    pure logical function get_prime_bit(num) result(bit)
        integer(i18t), intent(in) :: num
        bit = logical(btest(prime_sieve(num / bits_per_int + 1), int(mod(num, bits_per_int), kind(prime_sieve(1)))))
    end function get_prime_bit

    subroutine prime_factor(num, factor)
        integer(i18t), intent(inout) :: num
        integer(i18t), intent(out) :: factor
        if (num < 0) then
            factor = -1
            num = -num
        elseif (num <= 1) then
            factor = num
        else
            factor = 2
            call expand_sieve(int(sqrt(real(num)), i18t) + 1)
            do while (factor <= num)
                if (mod(num, factor) == 0) then
                    num = num / factor
                    return
                end if
                factor = next_prime(factor)
            end do
        endif
    end subroutine

    integer(i18t) function is_composite(num) result(factor)
        integer(i18t), intent(in) :: num
        integer(i18t) :: localnum
        localnum = num
        call prime_factor(localnum, factor)
        if (factor == num) then
            factor = 0
        endif
    end function

    logical function is_prime(num) result(ip)
        integer(i18t), intent(in) :: num
        integer(i18t) check
        if (num < 2) then
            ip = .false.
        elseif (num <= 3) then
            ip = .true.
        else
            check = mod(num, 6_i18t)
            ip = (check == 1 .or. check == 5) .and. is_composite(num) == 0
        endif
    end function
end module primes
