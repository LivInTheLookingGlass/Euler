module primes
    implicit none
    integer, parameter :: bits_per_int = 32
    integer, allocatable :: is_prime(:)
    integer :: current_n = 0
    logical :: initialized = .false.

contains

    subroutine sieve_up_to(n)
        integer, intent(in) :: n
        integer :: p, i, limit

        limit = ceiling(sqrt(real(n)))
        do p = 2, limit
            if (get_prime_bit(p)) then
                do i = p * p, n, p
                    call clear_prime_bit(i)
                end do
            end if
        end do
    end subroutine sieve_up_to

    recursive integer function next_prime(last) result(ret)
        integer, intent(in) :: last
        integer :: next

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
        integer, intent(in), optional :: potential_n
        integer :: new_size, new_n, i

        if (present(potential_n)) then
            new_n = max(potential_n, current_n)
        else
            new_n = current_n * 2
        end if

        new_size = (new_n / bits_per_int) + 1
        if (allocated(is_prime)) then
            deallocate(is_prime)
        end if
        allocate(is_prime(new_size))
        do i = 1, new_size
            is_prime(i) = 2**bits_per_int - 1
        end do
        call clear_prime_bit(0)
        call clear_prime_bit(1)
        current_n = new_n
        call sieve_up_to(new_n)
    end subroutine expand_sieve

    ! Function to set a bit to 0
    subroutine clear_prime_bit(num)
        integer, intent(in) :: num
        is_prime(num / bits_per_int + 1) = iand(is_prime(num / bits_per_int + 1), ieor(-1, 2**(mod(num, bits_per_int))))
    end subroutine clear_prime_bit

    ! Function to check if a bit is set
    logical function get_prime_bit(num) result(bit)
        integer, intent(in) :: num
        bit = logical(btest(is_prime(num / bits_per_int + 1), mod(num, bits_per_int)))
    end function get_prime_bit

end module primes
