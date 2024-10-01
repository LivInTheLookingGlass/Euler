module primes
    implicit none
    integer, parameter :: bits_per_int = 32
    integer, allocatable :: is_prime(:)
    integer :: current_n = 0

contains

    function initialize_sieve(n)
        integer, intent(in) :: n
        integer :: size
        ! Calculate size of the bit array (integer array to hold bits)
        size = (n / bits_per_int) + 1
        allocate(is_prime(size))
        is_prime = -1  ! Initialize all bits to 1 (all numbers are initially prime)
        clear_prime_bit(0)
        clear_prime_bit(1)
        current_n = n
        sieve_up_to(current_n)
    end function initialize_sieve

    function sieve_up_to(n)
        integer, intent(in) :: n
        integer :: p, limit
        limit = sqrt(real(n))
        do p = 2, limit
            if (get_prime_bit(p)) then
                do i = p * p, n, p
                    clear_prime_bit(i)
                end do
            end if
        end do
    end function sieve_up_to

    recursive integer function next_prime(last)
        integer, intent(in) :: last
        integer :: next = last + 1

        do next = last + 1, current_n
            if (get_prime_bit(is_prime, next)) then
                next_prime = next
                return
            end if
        end do

        expand_sieve()
        next_prime = next_prime(next)  ! Recursively find the next prime
    end function next_prime

    function expand_sieve(potential_n)
        integer, intent(in), optional :: potential_n
        integer :: new_size, new_n, i

        if (present(potential_n)) then
            new_n = max(potential_n, current_n)
        else
            new_n = current_n * 2
        end if

        new_size = (new_n / bits_per_int) + 1
        allocate(is_prime(new_size))
        is_prime = -1  ! All bits set to 1
        clear_prime_bit(is_prime, 0)
        clear_prime_bit(is_prime, 1)
        sieve_up_to(new_n)
        current_n = new_n
    end function expand_sieve

    ! Function to set a bit to 0
    function clear_prime_bit(num)
        integer, intent(in) :: num
        is_prime(num / bits_per_int) = bitand(is_prime(num / bits_per_int), ieor(0xFFFFFFFF, 1 << (mod(num, bits_per_int))))
    end function clear_prime_bit

    ! Function to check if a bit is set
    logical function get_prime_bit(num) result(bit)
        integer, intent(in) :: num
        bit = (btest(is_prime(num / bits_per_int), mod(num, bits_per_int)) /= 0)
    end function get_prime_bit

end module primes
