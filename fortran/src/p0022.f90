! Project Euler Problem 22
!
! Problem:
!
! Using names.txt (right click and 'Save Link/Target As...'), a 46K text file
! containing over five-thousand first names, begin by sorting it into
! alphabetical order. Then working out the alphabetical value for each name,
! multiply this value by its alphabetical position in the list to obtain a name
! score.
!
! For example, when the list is sorted into alphabetical order, COLIN, which is
! worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would
! obtain a score of 938 × 53 = 49714.
!
! What is the total of all the name scores in the file?

module Problem0022
    use constants
    use utils
    implicit none
    integer, parameter :: name_count = 5163
    integer, parameter :: longest_name = 11
contains
    integer(i18t) function p0022() result(answer)
        character(len=DATA_MAX_NAME_SIZE), parameter :: file_name = "p0022_names.txt"
        character(len=longest_name), dimension(name_count) :: names
        character(len=longest_name) :: temp
        character current_char
        integer(i18t) score
        integer ios, unit, i, j, k

        i = 1
        j = 1
        k = 1
        answer = 0
        names = ''
        unit = open_data_file(file_name, .true., 1)
        do
            read(unit, rec=j, IOSTAT=ios) current_char
            j = j + 1
            if (ios /= 0) then
                exit
            end if

            select case (current_char)
                case (',')
                    i = i + 1
                    k = 1
                case ('"')
                case default
                    names(i)(k:k) = current_char
                    k = k + 1
            end select
        end do
do i=1, size(names)
print *, names(i)
end do
        close(unit)
        do i = 1, size(names)
            do j = 1, size(names) - i
                if (names(j) > names(j + 1)) then
                    temp = names(j)
                    names(j) = names(j + 1)
                    names(j + 1) = temp
                end if
            end do
        end do
do i=1, size(names)
print *, names(i)
end do
        close(unit)
        do i = 1, name_count
            score = 0
            do j = 1, len_trim(names(i))
                score = score + ichar(names(i)(j:j)) - ichar('A') + 1
            end do
            answer = answer + score * i
        end do
    end function p0022
end module Problem0022
