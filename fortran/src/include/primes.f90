module primes
    use constants

    implicit none
    integer, parameter :: bits_per_int = 64
    integer(i18t), allocatable :: is_prime(:)
    integer(i18t) :: current_n = 0
    logical :: initialized = .false.

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
        integer(i18t) :: new_size, new_n, i

        if (present(potential_n)) then
            new_n = max(potential_n, current_n)
        else
            new_n = current_n * 2
        end if

        if (new_n <= current_n) then
            return
        endif

        new_size = (new_n / bits_per_int) + 1
        if (allocated(is_prime)) then
            deallocate(is_prime)
        end if
        allocate(is_prime(new_size))
        do i = 1, new_size
            is_prime(i) = 2**bits_per_int - 1
        end do
        call clear_prime_bit(0_i18t)
        call clear_prime_bit(1_i18t)
        call sieve_up_to(new_n)
        current_n = new_n
    end subroutine expand_sieve

    ! Function to set a bit to 0
    subroutine clear_prime_bit(num)
        integer(i18t), intent(in) :: num
        integer(i18t) :: i, b
        i = (num / bits_per_int) + 1
        b = mod(num, bits_per_int)
        print *, "Translating bit #", num, "to", i, b
        is_prime(i) = iand(is_prime(i), ieor(-1_i18t, 2**b))
    end subroutine clear_prime_bit

    ! Function to check if a bit is set
    logical function get_prime_bit(num) result(bit)
        integer(i18t), intent(in) :: num
        bit = logical(btest(is_prime(num / bits_per_int + 1), mod(num, bits_per_int)))
    end function get_prime_bit

end module primes
