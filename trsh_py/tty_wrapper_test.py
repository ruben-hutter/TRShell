from tty_wrapper import Wrapper
import sys
import os
import select

def main():
    wrapper = Wrapper(None)
    while True:
        r, w, e = select.select([sys.stdin], [], [])
        if sys.stdin in r:
            user_input = os.read(sys.stdin.fileno(), 10240)
            wrapper.push_to_shell(user_input)
            print(f'accept> {user_input}')

if __name__ == "__main__":
    main()