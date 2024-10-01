module primes
    implicit none
    integer, parameter :: bits_per_int = 32
    integer, allocatable :: is_prime(:)
    integer :: current_n = 0
    logical :: initialized = .false.

contains

    subroutine initialize_sieve(n)
        integer, intent(in) :: n
        integer :: size
        ! Calculate size of the bit array (integer array to hold bits)
        if (.not. initialized) then
            size = (n / bits_per_int) + 1
            allocate(is_prime(size))
            is_prime = -1  ! Initialize all bits to 1 (all numbers are initially prime)
            call clear_prime_bit(0)
            call clear_prime_bit(1)
            current_n = n
            initialized = .true.
            call sieve_up_to(current_n)
        end if
    end subroutine initialize_sieve

    subroutine sieve_up_to(n)
        integer, intent(in) :: n
        integer :: p, limit
        limit = sqrt(real(n))
        do p = 2, limit
            if (get_prime_bit(p)) then
                do i = p * p, n, p
                    call clear_prime_bit(i)
                end do
            end if
        end do
    end subroutine sieve_up_to

    recursive integer function next_prime(last)
        integer, intent(in) :: last
        integer :: next = last + 1

        do next = last + 1, current_n
            if (get_prime_bit(is_prime, next)) then
                next_prime = next
                return
            end if
        end do

        call expand_sieve()
        next_prime = next_prime(next)  ! Recursively find the next prime
    end function next_prime

    subroutine expand_sieve(potential_n)
        integer, intent(in), optional :: potential_n
        integer :: new_size, new_n, i

        call initialize_sieve()
        if (present(potential_n)) then
            new_n = max(potential_n, current_n)
        else
            new_n = current_n * 2
        end if

        new_size = (new_n / bits_per_int) + 1
        allocate(is_prime(new_size))
        is_prime = -1  ! All bits set to 1
        call clear_prime_bit(is_prime, 0)
        call clear_prime_bit(is_prime, 1)
        sieve_up_to(new_n)
        current_n = new_n
    end subroutine expand_sieve

    ! Function to set a bit to 0
    subroutine clear_prime_bit(num)
        integer, intent(in) :: num
        is_prime(num / bits_per_int) = bitand(is_prime(num / bits_per_int), ieor(0xFFFFFFFF, 1 << (mod(num, bits_per_int))))
    end subroutine clear_prime_bit

    ! Function to check if a bit is set
    logical function get_prime_bit(num) result(bit)
        integer, intent(in) :: num
        bit = (btest(is_prime(num / bits_per_int), mod(num, bits_per_int)) /= 0)
    end function get_prime_bit

end module primes
