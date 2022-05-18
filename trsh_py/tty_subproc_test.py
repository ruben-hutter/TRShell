import os
import pty
import tty
import select
import subprocess
import sys

SHELL_EXEC_PATH = 'dummy_shell.o'
SHELL_WRAP_FLAG = '-w'

def main():
    master_fd, slave_fd = pty.openpty()
    tty.setraw(sys.stdin.fileno())
    curr_dir = os.path.dirname(os.getcwd())
    command = os.path.join(curr_dir, SHELL_EXEC_PATH)
   
    p = subprocess.Popen(command,
                         stdin=slave_fd,
                         stdout=slave_fd,
                         stderr=slave_fd,
                         # Run in a new process group to enable bash's job control.
                         preexec_fn=os.setsid,
                         # Run bash in "dumb" terminal.
                         env=dict(os.environ, TERM='dumb'))

    while p.poll() is None:
        r, w, e = select.select([sys.stdin, master_fd], [], [])
        if sys.stdin in r:
            user_input = os.read(sys.stdin.fileno(), 10240)
            os.write(master_fd, user_input)
        elif master_fd in r:
            output = os.read(master_fd, 10240)
            os.write(sys.stdout.fileno(), output)

if __name__ == "__main__":
    main()