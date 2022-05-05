# test code for the wrapper demo
from time import sleep
import wrapper as wrp

if __name__ == "__main__":
    # create wrapper
    wrap = wrp.Wrapper(None)
    # spam stdin
    for i in range(100):
        wrap.push_to_shell(f"Test String {i}!...")
        sleep(0.5)