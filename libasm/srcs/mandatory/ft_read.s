; **************************************************************************
; *         ssize_t read(int fd, void buf[.count], size_t count)           *
; **************************************************************************

; read()  attempts to read up to count bytes from file descriptor fd into
; the buffer starting at buf.

; On files that support seeking, the read operation commences at the file
; offset, and the file offset is incremented by the number of bytes read.
; If the file offset is at or past the end of file, no  bytes  are  read,
; and read() returns zero.

; If count is zero, read() may detect the errors described below.  In the
; absence of any errors, or if read() does not check for errors, a read()
; with a count of 0 returns zero and has no other effects.

; According to POSIX.1, if count is greater than SSIZE_MAX, the result is
; implementation-defined; see NOTES for the upper limit on Linux.

; On success, the number of bytes read is returned (zero indicates end of
; file),  and the file position is advanced by this number.  It is not an
; error if this number is smaller than the  number  of  bytes  requested;
; this  may happen for example because fewer bytes are actually available
; right now (maybe because we were close to end-of-file,  or  because  we
; are reading from a pipe, or from a terminal), or because read() was in‐
; terrupted by a signal.  See also NOTES.

; On error, -1 is returned, and errno is set to indicate the  error.   In
; this  case,  it  is left unspecified whether the file position (if any)
; changes.
; **************************************************************************

global ft_read
extern __errno_location

section .text

ft_read:
    mov     rax, 0          ; syscall read
    syscall

    cmp     rax, 0
    jge     .ok             ; si rax >= 0 → éxito

    ; error: rax = -errno
    neg     rax             ; rax = errno positivo
    mov     rdi, rax        ; rdi = errno
    call    __errno_location  ; rax = &errno
    mov     [rax], rdi      ; *errno = errno
    mov     rax, -1         ; return -1
    ret

.ok:
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
