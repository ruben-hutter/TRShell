# Project TODO list

## Tobi

## Ruben

[~] make file refactor
[] tilde for path change

---

==32180== Invalid write of size 8
==32180==    at 0x109C76: append_entry_to_list (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109C3E: append_string_to_history (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109BA9: apply_history_changes (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109728: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==  Address 0x4aabc60 is 8 bytes after a block of size 8 alloc'd
==32180==    at 0x4845888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x109C17: append_string_to_history (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109BA9: apply_history_changes (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109728: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==
==32180== Invalid write of size 8
==32180==    at 0x109C89: append_entry_to_list (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109C3E: append_string_to_history (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109BA9: apply_history_changes (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109728: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==  Address 0x4aabc58 is 0 bytes after a block of size 8 alloc'd
==32180==    at 0x4845888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x109C17: append_string_to_history (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109BA9: apply_history_changes (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109728: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==
==32180== Invalid read of size 8
==32180==    at 0x109E07: free_complete_history (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x1097DA: free_everything (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10973B: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==  Address 0x4aabc58 is 0 bytes after a block of size 8 alloc'd
==32180==    at 0x4845888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x109C17: append_string_to_history (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109BA9: apply_history_changes (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109728: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==
==32180== Invalid read of size 8
==32180==    at 0x109DC1: free_history_entry (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109E1A: free_complete_history (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x1097DA: free_everything (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10973B: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==  Address 0x4aabc50 is 0 bytes inside a block of size 8 free'd
==32180==    at 0x484826F: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x109DE3: free_history_entry (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109E1A: free_complete_history (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x1097DA: free_everything (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10973B: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==  Block was alloc'd at
==32180==    at 0x4845888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x109C17: append_string_to_history (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109BA9: apply_history_changes (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109728: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==
==32180== Invalid read of size 8
==32180==    at 0x109DCD: free_history_entry (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109E1A: free_complete_history (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x1097DA: free_everything (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10973B: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==  Address 0x4aabc50 is 0 bytes inside a block of size 8 free'd
==32180==    at 0x484826F: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x109DE3: free_history_entry (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109E1A: free_complete_history (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x1097DA: free_everything (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10973B: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==  Block was alloc'd at
==32180==    at 0x4845888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x109C17: append_string_to_history (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109BA9: apply_history_changes (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109728: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==
==32180== Invalid free() / delete / delete[] / realloc()
==32180==    at 0x484826F: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x109DD7: free_history_entry (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109E1A: free_complete_history (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x1097DA: free_everything (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10973B: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==  Address 0x4aab430 is 0 bytes inside a block of size 6 free'd
==32180==    at 0x484826F: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x109DD7: free_history_entry (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109E1A: free_complete_history (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x1097DA: free_everything (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10973B: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==  Block was alloc'd at
==32180==    at 0x4845888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x10BC68: read_from_input (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x1096B0: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==
==32180== Invalid free() / delete / delete[] / realloc()
==32180==    at 0x484826F: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x109DE3: free_history_entry (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109E1A: free_complete_history (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x1097DA: free_everything (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10973B: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==  Address 0x4aabc50 is 0 bytes inside a block of size 8 free'd
==32180==    at 0x484826F: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x109DE3: free_history_entry (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109E1A: free_complete_history (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x1097DA: free_everything (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10973B: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==  Block was alloc'd at
==32180==    at 0x4845888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x109C17: append_string_to_history (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109BA9: apply_history_changes (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109728: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==
==32180==
==32180== Process terminating with default action of signal 2 (SIGINT)
==32180==    at 0x484826F: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x109DD7: free_history_entry (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109E1A: free_complete_history (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x1097DA: free_everything (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10973B: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==
==32180== HEAP SUMMARY:
==32180==     in use at exit: 3,176 bytes in 8 blocks
==32180==   total heap usage: 191 allocs, 2,372,756 frees, 10,318 bytes allocated
==32180==
==32180== 6 bytes in 1 blocks are definitely lost in loss record 1 of 8
==32180==    at 0x4845888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x10AE78: get_malloced_empty_string (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10AEAE: get_malloced_copy (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10A528: get_user_name (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10A0D6: print_prompt (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x1096A6: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==
==32180== 6 bytes in 1 blocks are definitely lost in loss record 2 of 8
==32180==    at 0x4845888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x10AE78: get_malloced_empty_string (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10AEAE: get_malloced_copy (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10A528: get_user_name (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10A12D: print_prompt_1 (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10A100: print_prompt (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x1096A6: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==
==32180== 6 bytes in 1 blocks are definitely lost in loss record 3 of 8
==32180==    at 0x4845888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x10AE78: get_malloced_empty_string (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10AEAE: get_malloced_copy (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10A528: get_user_name (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10A583: get_current_working_dir (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10A136: print_prompt_1 (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10A100: print_prompt (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x1096A6: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==
==32180== 6 bytes in 1 blocks are definitely lost in loss record 4 of 8
==32180==    at 0x4845888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x10AE78: get_malloced_empty_string (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10AEAE: get_malloced_copy (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10A528: get_user_name (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10A58C: get_current_working_dir (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10A136: print_prompt_1 (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10A100: print_prompt (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x1096A6: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==
==32180== 80 bytes in 1 blocks are still reachable in loss record 5 of 8
==32180==    at 0x4845888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x109ACA: append_string_to_changes (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109723: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==
==32180== 1,024 bytes in 1 blocks are still reachable in loss record 6 of 8
==32180==    at 0x4845888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x490F570: _IO_file_doallocate (filedoalloc.c:101)
==32180==    by 0x491D23F: _IO_doallocbuf (genops.c:347)
==32180==    by 0x491D23F: _IO_doallocbuf (genops.c:342)
==32180==    by 0x491C5C7: _IO_file_overflow@@GLIBC_2.2.5 (fileops.c:744)
==32180==    by 0x491B76D: _IO_new_file_xsputn (fileops.c:1243)
==32180==    by 0x491B76D: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1196)
==32180==    by 0x4906292: outstring_func (vfprintf-internal.c:239)
==32180==    by 0x4906292: __vfprintf_internal (vfprintf-internal.c:1263)
==32180==    by 0x48F18FE: printf (printf.c:33)
==32180==    by 0x10A22B: print_prompt_1 (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10A100: print_prompt (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x1096A6: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==
==32180== 1,024 bytes in 1 blocks are still reachable in loss record 7 of 8
==32180==    at 0x4845888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x490F570: _IO_file_doallocate (filedoalloc.c:101)
==32180==    by 0x491D23F: _IO_doallocbuf (genops.c:347)
==32180==    by 0x491D23F: _IO_doallocbuf (genops.c:342)
==32180==    by 0x491C35C: _IO_file_underflow@@GLIBC_2.2.5 (fileops.c:485)
==32180==    by 0x491D2F5: _IO_default_uflow (genops.c:362)
==32180==    by 0x10BFFD: get_string_from_input (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x10BDD5: read_from_input (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x1096B0: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==
==32180== 1,024 bytes in 1 blocks are still reachable in loss record 8 of 8
==32180==    at 0x4845888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==32180==    by 0x10B989: get_next_token (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109769: parse_and_execute (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==    by 0x109717: main (in /home/ruben/Dropbox/UNI_Basel/FS2022/Operating Systems/Project/shell/trshell.o)
==32180==
==32180== LEAK SUMMARY:
==32180==    definitely lost: 24 bytes in 4 blocks
==32180==    indirectly lost: 0 bytes in 0 blocks
==32180==      possibly lost: 0 bytes in 0 blocks
==32180==    still reachable: 3,152 bytes in 4 blocks
==32180==         suppressed: 0 bytes in 0 blocks
==32180==
==32180== For lists of detected and suppressed errors, rerun with: -s
==32180== ERROR SUMMARY: 5931441 errors from 11 contexts (suppressed: 0 from 0)
