; **************************************************************************
; *       ssize_t write(int fd, const void buf[.count], size_t count)      *
; **************************************************************************

; write() writes up to count bytes from the buffer starting at buf to the
; file referred to by the file descriptor fd.

; The number of bytes written may be less than  count  if,  for  example,
; there  is  insufficient space on the underlying physical medium, or the
; RLIMIT_FSIZE resource limit is encountered (see setrlimit(2)),  or  the
; call was interrupted by a signal handler after having written less than
; count bytes.  (See also pipe(7).)

; For a seekable file (i.e., one to which lseek(2) may  be  applied,  for
; example,  a  regular  file) writing takes place at the file offset, and
; the file offset is incremented by the number of bytes actually written.
; If  the  file was open(2)ed with O_APPEND, the file offset is first set
; to the end of the file before writing.  The adjustment of the file off‐
; set and the write operation are performed as an atomic step.

; POSIX  requires  that  a  read(2)  that  can be proved to occur after a
; write() has returned will return the  new  data.   Note  that  not  all
; filesystems are POSIX conforming.

; According to POSIX.1, if count is greater than SSIZE_MAX, the result is
; implementation-defined; see NOTES for the upper limit on Linux.

; On success, the number of bytes written is returned.  On error,  -1  is
; returned, and errno is set to indicate the error.
; **************************************************************************

global ft_write
extern __errno_location

section .text

ft_write:
    mov     rax, 1          ; syscall write
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
