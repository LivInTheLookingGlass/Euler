! Project Euler Problem 836
!
! Alright, this was funny
!
! Problem:
!
! Let A be an **affine plane** over a **radically integral local field** F with residual characteristic p.
!
! We consider an **open oriented line section** U of A with normalized Haar measure m.
!
! Define f(m,p) as the maximal possible discriminant of the **jacobian** associated to the
! **orthogonal kernel embedding** of U into A.
!
! Find f(20230401, 57). Give as your answer the concatenation of the first letters of each bolded word.

module Problem0836
    implicit none
    integer, parameter :: p0836_len = 14
contains
    character(p0836_len) function p0836()
        p0836 = 'aprilfoolsjoke'
    end function p0836
end module Problem0836

